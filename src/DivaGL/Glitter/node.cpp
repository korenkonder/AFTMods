/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "glitter.hpp"

namespace Glitter {
    NodeX::NodeX() : translation(), rotation() {
        scale = 1.0f;
        uniform_scale = 1.0f;
    }

    NodeX::~NodeX() {

    }

    NodeX& NodeX::operator=(const NodeX& node) {
        translation = node.translation;
        rotation = node.rotation;
        scale = node.scale;
        uniform_scale = node.uniform_scale;
        return *this;
    }
}
