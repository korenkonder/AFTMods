/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "glitter.hpp"
#include "../../KKdLib/prj/algorithm.hpp"
#include "../object.hpp"
#include "../texture.hpp"

namespace Glitter {
    EffectGroupX::EffectGroupX() : effects(), load_count(), hash(), scene(),
        resources_count(), resources_tex(), resources(), not_loaded(), scene_init() {
        emission = 1.0f;
        version = 0x0C;
    }

    EffectGroupX::~EffectGroupX() {
        for (MeshX& i : meshes)
            if (i.object_set != -1) {
                object_database_unload_set(i.object_set);
                i.load = false;
            }

        meshes.clear();

        if (resources) {
            texture_array_free(resources);
            resources = 0;
        }

        for (EffectX*& i : effects)
            if (i) {
                delete i;
                i = 0;
            }
        effects.clear();

        if (scene) {
            delete scene;
            scene = 0;
        }
    }
}
