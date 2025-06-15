/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "task_movie.hpp"
#include "../AFTModsShared/sprite.hpp"
#include "../AFTModsShared/task.hpp"
#include "../AFTModsShared/texture.hpp"
#include "movie_play_lib/movie_play_lib.hpp"
#include "gl_state.hpp"
#include "static_var.hpp"
#include <map>
#include <vector>
#include <Helpers.h>

class TaskMovie : public app::Task {
public:
    enum class State {
        Wait = 0,
        Init,
        Disp,
        Stop,
        Max,
    };

    enum class DispType {
        None = 0,
        SpriteTextute,
        Textute,
        Max,
    };

    struct PlayerVideoParams {
        int64_t width;
        int64_t height;
        int64_t frame_size_width;
        int64_t frame_size_height;
    };

    static_assert(sizeof(TaskMovie::PlayerVideoParams) == 0x20, "\"TaskMovie::PlayerVideoParams\" struct should have a size of 0x20");

    struct DispParams {
        rectangle rect;
        resolution_mode resolution_mode;
        float_t scale;
        uint32_t field_18;
        int32_t index;
    };

    static_assert(sizeof(TaskMovie::DispParams) == 0x20, "\"TaskMovie::DispParams\" struct should have a size of 0x20");

    struct SprParams {
        DispParams disp;
        spr::SprPrio prio;
    };

    static_assert(sizeof(TaskMovie::SprParams) == 0x24, "\"TaskMovie::SprParams\" struct should have a size of 0x24");

    struct Player {
        bool pause;
        float_t volume;
        bool set_audio_params;
        State state;
        MoviePlayLib::IPlayer* player;
        MoviePlayLib::IMediaClock* external_clock;
        MoviePlayLib::State player_state;
        MoviePlayLib::VideoParams video_params;
        MoviePlayLib::IGLDXInteropTexture* interop_texture;
        double_t duration;
        double_t time;

        void Ctrl();
        void GetInteropTexture(texture*& ptr);
        void UpdateInteropTexture(TaskMovie::PlayerVideoParams* player_video_params);
    };

    static_assert(sizeof(TaskMovie::Player) == 0x58, "\"TaskMovie::Player\" struct should have a size of 0x58");

    prj::string path;
    DispType disp_type;
    SprParams spr_params;
    State state;
    Player* player;
    PlayerVideoParams* player_video_params;
    texture* tex;
    bool pause;
    bool wait_play;

    bool CheckState();
};

static_assert(sizeof(TaskMovie) == 0xD8, "\"TaskMovie\" struct should have a size of 0xD8");

struct TaskMoviePlayerNoInterop {
    ID3D11Device* d3d11_device;
    ID3D11DeviceContext* d3d11_device_context;
    ID3D11Texture2D* d3d11_texture;
    texture* d3d11_tex;
    std::vector<uint8_t> d3d11_tex_data;

    TaskMoviePlayerNoInterop();
    ~TaskMoviePlayerNoInterop();

    void Create();
    void Ctrl(TaskMovie* task_movie, TaskMovie::Player* player,
        TaskMovie::PlayerVideoParams* player_video_params);
    void GetD3D11Texture(TaskMovie::Player* player, texture*& ptr);
    void Release();
    void ReleaseTexture();
    void UpdateD3D11Texture(TaskMovie::Player* player, TaskMovie::PlayerVideoParams* player_video_params);

    static TaskMoviePlayerNoInterop* Get(TaskMovie::Player* player);
};

std::map<TaskMovie::Player*, TaskMoviePlayerNoInterop> task_movie_player_no_interop;

static texture* (FASTCALL* sub_14041E560)()
    = (texture * (FASTCALL*)())0x000000014041E560;

HOOK(bool, FASTCALL, TaskMovie__ctrl, 0x000000014041E570, TaskMovie* This) {
    This->state = TaskMovie::State::Wait;
    if (This->player) {
        This->player->Ctrl();
        This->state = This->player->state;
    }

    if (This->CheckState()) {
        TaskMoviePlayerNoInterop* no_interop = TaskMoviePlayerNoInterop::Get(This->player);
        if (no_interop) {
            no_interop->Ctrl(This, This->player, This->player_video_params);
            return false;
        }

        if (This->player->interop_texture) {
            This->player->interop_texture->Release();
            This->player->interop_texture = 0;
        }

        This->player->UpdateInteropTexture(This->player_video_params);
        if (This->player_video_params->frame_size_width && This->player_video_params->frame_size_height) {
            if (!This->tex)
                This->tex = (texture*)sub_14041E560();
            if (This->disp_type != TaskMovie::DispType::None)
                This->player->GetInteropTexture(This->tex);
        }

        if (This->player && !This->player->interop_texture
            && !no_interop && This->disp_type != TaskMovie::DispType::None) {
            HRESULT hr = This->player->player->GetGLDXIntreropTexture(&This->player->interop_texture);
            if (hr < S_FALSE)
                task_movie_player_no_interop.insert({ This->player, {} }).first->second.Create();
        }
    }
    return 0;
}

HOOK(void, FASTCALL, TaskMovie__Player__Destroy, 0x000000014041E6C0, TaskMovie::Player* ptr) {
    if (ptr) {
        auto elem = task_movie_player_no_interop.find(ptr);
        if (elem != task_movie_player_no_interop.end()) {
            elem->second.Release();
            task_movie_player_no_interop.erase(elem);
        }
    }

    originalTaskMovie__Player__Destroy(ptr);
}

HOOK(bool, FASTCALL, TaskMovie__Shutdown, 0x000000014041F500, TaskMovie* This) {
    TaskMovie::Player* player = This->player;

    bool res = false;
    if (player) {
        TaskMoviePlayerNoInterop* no_interop = TaskMoviePlayerNoInterop::Get(player);
        if (no_interop)
            no_interop->ReleaseTexture();

        if (player->interop_texture) {
            player->interop_texture->Release();
            player->interop_texture = 0;
        }

        This->tex = 0;

        if (no_interop)
            no_interop->ReleaseTexture();

        if (player->interop_texture) {
            player->interop_texture->Release();
            player->interop_texture = 0;
        }

        if (player->player) {
            player->player->Release();
            player->player = 0;
        }

        if (player->external_clock) {
            player->external_clock->Release();
            player->external_clock = 0;
        }

        res = true;
    }

    This->path.clear();
    return res;
}

void task_movie_patch() {
    if (sv_task_movie_player_no_interop) {
        INSTALL_HOOK(TaskMovie__ctrl);
        INSTALL_HOOK(TaskMovie__Player__Destroy);
        INSTALL_HOOK(TaskMovie__Shutdown);
    }
}

TaskMoviePlayerNoInterop::TaskMoviePlayerNoInterop() : d3d11_device(),
d3d11_device_context(), d3d11_texture(), d3d11_tex() {

}

TaskMoviePlayerNoInterop::~TaskMoviePlayerNoInterop() {

}

void TaskMoviePlayerNoInterop::Create() {
    D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,
        D3D11_SDK_VERSION, &d3d11_device, 0, &d3d11_device_context);
}

void TaskMoviePlayerNoInterop::Ctrl(TaskMovie* task_movie,
    TaskMovie::Player* player, TaskMovie::PlayerVideoParams* player_video_params) {
    UpdateD3D11Texture(player, player_video_params);

    if (player_video_params->frame_size_width && player_video_params->frame_size_height) {
        if (!task_movie->tex)
            task_movie->tex = sub_14041E560();

        if (task_movie->disp_type != TaskMovie::DispType::None)
            GetD3D11Texture(player, task_movie->tex);
    }
}

void TaskMoviePlayerNoInterop::GetD3D11Texture(TaskMovie::Player* player, texture*& ptr) {
    if (!d3d11_texture)
        return;

    texture* tex = d3d11_tex;
    if (!tex)
        return;

    D3D11_MAPPED_SUBRESOURCE mapped_res = {};
    if (SUCCEEDED(d3d11_device_context->Map(d3d11_texture, 0, D3D11_MAP_READ, 0, &mapped_res))) {
        const void* data = mapped_res.pData;
        const size_t dx_row_pitch = mapped_res.RowPitch;
        const size_t gl_row_pitch = sizeof(uint8_t) * 4 * tex->width;
        if (gl_row_pitch != dx_row_pitch) {
            if (d3d11_tex_data.size() < gl_row_pitch * tex->height)
                d3d11_tex_data.resize(gl_row_pitch * tex->height);

            const ssize_t row_pitch = min_def(dx_row_pitch, gl_row_pitch);
            const uint8_t* src = (const uint8_t*)data;
            uint8_t* dst = d3d11_tex_data.data();
            for (int32_t y = 0; y < tex->height; y++, dst += gl_row_pitch, src += dx_row_pitch)
                memcpy(dst, src, row_pitch);
            data = d3d11_tex_data.data();
        }

        glPixelStoreiDLL(GL_UNPACK_ALIGNMENT, 1);
        if (DIVA_GL_VERSION_4_5) {
            glTextureSubImage2D(tex->glid, 0, 0, 0, tex->width, tex->height,
                GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else {
            gl_state.bind_texture_2d(tex->glid);
            glTexSubImage2DDLL(GL_TEXTURE_2D, 0, 0, 0, tex->width, tex->height,
                GL_RGBA, GL_UNSIGNED_BYTE, data);
            gl_state.bind_texture_2d(0);
        }
        d3d11_device_context->Unmap(d3d11_texture, 0);
    }

    ptr = tex;
    ptr->width = player->video_params.frame_size_width;
    ptr->height = player->video_params.frame_size_height;
}

void TaskMoviePlayerNoInterop::Release() {
    d3d11_tex_data.clear();
    d3d11_tex_data.shrink_to_fit();

    if (d3d11_tex) {
        texture_release(d3d11_tex);
        d3d11_tex = 0;
    }

    if (d3d11_texture) {
        d3d11_texture->Release();
        d3d11_texture = 0;
    }

    if (d3d11_device_context) {
        d3d11_device_context->Release();
        d3d11_device_context = 0;
    }

    if (d3d11_device) {
        d3d11_device->Release();
        d3d11_device = 0;
    }
}

void TaskMoviePlayerNoInterop::ReleaseTexture() {
    d3d11_tex_data.clear();
    d3d11_tex_data.shrink_to_fit();

    if (d3d11_tex) {
        texture_release(d3d11_tex);
        d3d11_tex = 0;
    }

    if (d3d11_texture) {
        d3d11_texture->Release();
        d3d11_texture = 0;
    }
}

void TaskMoviePlayerNoInterop::UpdateD3D11Texture(TaskMovie::Player* player,
    TaskMovie::PlayerVideoParams* player_video_params) {
    ID3D11Texture2D* d3d_texture = 0;
    if (player->player)
        player->player->GetD3D11Texture(d3d11_device, &d3d_texture);

    if (!d3d_texture)
        return;

    D3D11_TEXTURE2D_DESC desc;
    d3d_texture->GetDesc(&desc);

    if (!d3d11_tex || (d3d11_tex->width != desc.Width || d3d11_tex->height != desc.Height)) {
        if (d3d11_texture) {
            d3d11_texture->Release();
            d3d11_texture = 0;
        }

        d3d11_tex_data.clear();
        d3d11_tex_data.shrink_to_fit();

        if (d3d11_tex) {
            texture_release(d3d11_tex);
            d3d11_tex = 0;
        }

        static uint32_t counter = 0x02;
        if (counter < 0x02 || counter > 0xFFFFFF)
            counter = 0x02;
        d3d11_tex = texture_load_tex_2d(0x2F000000 | counter, GL_RGBA8, desc.Width, desc.Height, 0, 0, 0);
        counter++;

        if (d3d11_tex) {
            gl_state.bind_texture_2d(d3d11_tex->glid);
            const GLint swizzle[] = { GL_BLUE, GL_GREEN, GL_RED, GL_ALPHA };
            glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
            gl_state.bind_texture_2d(0);
        }

        D3D11_TEXTURE2D_DESC tex_desc = {};
        tex_desc.Width = desc.Width;
        tex_desc.Height = desc.Height;
        tex_desc.MipLevels = 1;
        tex_desc.ArraySize = 1;
        tex_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        tex_desc.SampleDesc.Count = 1;
        tex_desc.SampleDesc.Quality = 0;
        tex_desc.Usage = D3D11_USAGE_STAGING;
        tex_desc.BindFlags = 0;
        tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        tex_desc.MiscFlags = 0;

        d3d11_device->CreateTexture2D(&tex_desc, 0, &d3d11_texture);
    }

    if (d3d11_texture)
        d3d11_device_context->CopyResource(d3d11_texture, d3d_texture);

    if (d3d_texture) {
        d3d_texture->Release();
        d3d_texture = 0;
    }

    if (!player_video_params)
        return;

    if (player->state == TaskMovie::State::Disp) {
        player_video_params->width = player->video_params.width;
        player_video_params->height = player->video_params.height;
        player_video_params->frame_size_width = player->video_params.frame_size_width;
        player_video_params->frame_size_height = player->video_params.frame_size_height;
    }
    else {
        player_video_params->width = 0;
        player_video_params->height = 0;
        player_video_params->frame_size_width = 0;
        player_video_params->frame_size_height = 0;
    }
}

inline TaskMoviePlayerNoInterop* TaskMoviePlayerNoInterop::Get(TaskMovie::Player* player) {
    auto elem = task_movie_player_no_interop.find(player);
    if (elem != task_movie_player_no_interop.end())
        return &elem->second;
    return 0;
}

void TaskMovie::Player::Ctrl() {
    player_state = MoviePlayLib::State::Wait;
    time = 0.0f;

    if (player && !*(uint32_t*)0x00000001411A1840) {
        player_state = player->GetState();
        time = player->GetTime();
    }

    switch (player_state) {
    case MoviePlayLib::State::None:
    case MoviePlayLib::State::Init:
        state = TaskMovie::State::Init;
        break;
    case MoviePlayLib::State::Open:
        player->GetVideoParams(&video_params);

        duration = player->GetDuration();
        player->Play();

        state = TaskMovie::State::Init;
        break;
    case MoviePlayLib::State::Wait:
        state = TaskMovie::State::Wait;
        break;
    case MoviePlayLib::State::Pause:
        if (!pause)
            player->Play();

        state = TaskMovie::State::Disp;
        break;
    case MoviePlayLib::State::Play:
        {
            TaskMoviePlayerNoInterop* no_interop = TaskMoviePlayerNoInterop::Get(this);
            if (no_interop) {
                if (no_interop->d3d11_texture && no_interop->d3d11_tex && pause)
                    player->Pause();

                state = TaskMovie::State::Disp;
                break;
            }
        }

        if (interop_texture && interop_texture->GetTexture() && pause)
            player->Pause();

        state = TaskMovie::State::Disp;
        break;
    case MoviePlayLib::State::Stop:
        if (time <= 0.0f || time >= duration)
            state = TaskMovie::State::Stop;
        break;
    }

    if (state == TaskMovie::State::Disp && player && set_audio_params) {
        MoviePlayLib::AudioParams audio_params;
        audio_params.spk_l_volume = volume;
        audio_params.spk_r_volume = volume;
        audio_params.field_8 = 0.0f;
        audio_params.field_C = 0.0f;
        audio_params.hph_l_volume = volume;
        audio_params.hph_r_volume = volume;
        if (player->SetAudioParams(&audio_params) >= 0)
            set_audio_params = false;
    }
}

void TaskMovie::Player::GetInteropTexture(texture*& ptr) {
    if (!interop_texture)
        return;

    texture* tex = interop_texture->GetTexture();
    if (!tex)
        return;

    ptr = tex;
    ptr->width = video_params.frame_size_width;
    ptr->height = video_params.frame_size_height;
}

void TaskMovie::Player::UpdateInteropTexture(TaskMovie::PlayerVideoParams* player_video_params) {
    if (interop_texture) {
        interop_texture->Release();
        interop_texture = 0;
    }

    if (player)
        player->GetGLDXIntreropTexture(&interop_texture);

    if (!player_video_params)
        return;

    if (state == TaskMovie::State::Disp) {
        player_video_params->width = video_params.width;
        player_video_params->height = video_params.height;
        player_video_params->frame_size_width = video_params.frame_size_width;
        player_video_params->frame_size_height = video_params.frame_size_height;
    }
    else {
        player_video_params->width = 0;
        player_video_params->height = 0;
        player_video_params->frame_size_width = 0;
        player_video_params->frame_size_height = 0;
    }
}

bool TaskMovie::CheckState() {
    return state == TaskMovie::State::Init || state == TaskMovie::State::Disp;
}
