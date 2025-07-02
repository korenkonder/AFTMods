/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include <unknwn.h>
#include <mferror.h>
#include <mfobjects.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <atomic>

struct texture;

#define MOVIE_PLAY_LIB_TRACE_BEGIN MoviePlayLib::trace(L">%S(%p)\n", __FUNCTION__, this)
#define MOVIE_PLAY_LIB_TRACE_END   MoviePlayLib::trace(L"<%S(%p)\n", __FUNCTION__, this)

namespace MoviePlayLib {
    enum Status {
        Status_NotInitialized = 0,
        Status_Initializing,
        Status_Initialized,
        Status_Starting,
        Status_Started,
        Status_Stopping,
        Status_Stopped,
        Status_Shutdown,
    };

    struct AudioVolumes {
        float_t spk_l_volume;
        float_t spk_r_volume;
        float_t field_8;
        float_t field_C;
        float_t hph_l_volume;
        float_t hph_r_volume;
    };

    struct PlayerStat {
        double_t duration;
        bool enable_audio;
        bool enable_video;
        uint32_t present_width;
        uint32_t present_height;
        uint32_t raw_width;
        uint32_t raw_height;
        float_t framerate;
        float_t pixelaspect;
        uint32_t sample_freq;
        uint32_t channels;
        HRESULT error;
        void* error_object;
        uint32_t source_audio_queue_count;
        uint32_t source_video_queue_count;
        uint32_t decode_audio_queue_count;
        uint32_t decode_video_queue_count;
        double_t source_audio_sample_time;
        double_t source_video_sample_time;
        double_t decode_audio_sample_time;
        double_t decode_video_sample_time;
        double_t decode_audio_elapse;
        double_t decode_video_elapse;
        double_t decode_video_conv_elapse;
        double_t schedule_audio_drift;
        double_t schedule_video_drift;
        double_t audio_send_elapse;
        double_t video_lock_elapse;
    };

    struct VideoInfo {
        int32_t present_width;
        int32_t present_height;
        int32_t raw_width;
        int32_t raw_height;
        float_t framerate;
        float_t pixelaspect;
    };

    class DECLSPEC_UUID("BE82EF2E-4B9F-4470-9C6F-F78E002FCDEF")
        IMediaRenderer : public IUnknown {
    public:
        virtual HRESULT Shutdown() = 0;
        virtual HRESULT Close() = 0;
        virtual HRESULT Flush() = 0;
        virtual HRESULT Open() = 0;
        virtual HRESULT ProcessSample(IMFSample * pSample) = 0;
    };

    class DECLSPEC_UUID("4A5C73B9-FBFE-4A00-A298-FD3FAB0C5AF1")
        IAudioRenderer : public IMediaRenderer {
    public:
        virtual HRESULT GetVolumes(AudioVolumes * out_volumes) = 0;
        virtual HRESULT SetVolumes(const AudioVolumes * in_volumes) = 0;
    };

    class DECLSPEC_UUID("D19AC022-EA49-4B6F-9D51-673C1C15ECE8")
        IGLDXInteropTexture : public IUnknown {
    public:
        virtual texture* GetGLTexture() = 0;
    };

    class DECLSPEC_UUID("D4FA34F6-D03C-4F21-8591-6858161CA5D7")
        IMediaClock : public IUnknown {
    public:
        virtual HRESULT Stop() = 0;
        virtual HRESULT Start() = 0;
        virtual HRESULT SetTime(INT64 hnsTime) = 0;
        virtual INT64 GetTime() = 0;
    };

    class DECLSPEC_UUID("0D41578B-4514-407D-B654-870BCCDC630A")
        IMediaTransform : public IUnknown {
    public:
        virtual HRESULT Shutdown() = 0;
        virtual HRESULT Close() = 0;
        virtual HRESULT Flush() = 0;
        virtual HRESULT Open() = 0;
        virtual HRESULT GetMediaType(IMFMediaType * *pType) = 0;
        virtual void PushSample(IMFSample * pSample) = 0;
        virtual BOOL RequestSample() = 0;
        virtual BOOL IsEndOfStream() = 0;
        virtual UINT32 GetInputQueueCount() = 0;
        virtual UINT32 GetOutputQueueCount() = 0;
        virtual INT64 PeekSampleTime() = 0;
        virtual void GetSample(IMFSample * &ppOutSample) = 0;
    };

    class DECLSPEC_UUID("0D41578B-4514-407D-B654-870BCCDC630A")
        IMediaSource : public IUnknown {
    public:
        virtual HRESULT Shutdown() = 0;
        virtual HRESULT Stop() = 0;
        virtual HRESULT Start(INT64 hnsTime) = 0;
        virtual UINT64 GetDuration() = 0;
        virtual HRESULT GetAudioMediaType(IMFMediaType * *ppType) = 0;
        virtual HRESULT GetVideoMediaType(IMFMediaType * *ppType) = 0;
        virtual HRESULT SetAudioDecoder(IMediaTransform * pDecoder) = 0;
        virtual HRESULT SetVideoDecoder(IMediaTransform * pDecoder) = 0;
    };

    class DECLSPEC_UUID("12AC5FCE-C816-47FE-84B4-4915D6B42FA7")
        IPlayer : public IUnknown {
    public:
        virtual HRESULT Open(const wchar_t* filePath) = 0;
        virtual HRESULT Open(const char* filePath) = 0;
        virtual HRESULT Close() = 0;
        virtual HRESULT SetTimeSource(IMediaClock * pClock) = 0;
        virtual Status GetStatus() = 0;
        virtual HRESULT Play() = 0;
        virtual HRESULT Pause() = 0;
        virtual double_t GetDuration() = 0;
        virtual double_t GetCurrentPosition() = 0;
        virtual HRESULT SetCurrentPosition(double_t pos) = 0;
        virtual HRESULT GetVolumes(AudioVolumes * out_volumes) = 0;
        virtual HRESULT SetVolumes(const AudioVolumes * in_volumes) = 0;
        virtual HRESULT GetVideoInfo(VideoInfo * out_info) = 0;
        virtual HRESULT GetTextureD3D9Ex(IDirect3DDevice9 * pDevice, IDirect3DTexture9 * *ppOutTexture) = 0;
        virtual HRESULT GetTextureD3D11(ID3D11Device * pDevice, ID3D11Texture2D * *ppOutTexture) = 0;
        virtual HRESULT GetTextureOGL(IGLDXInteropTexture * *ppOutTexture) = 0;
    };

    extern void(FASTCALL* trace)(const wchar_t* fmt, ...);
}
