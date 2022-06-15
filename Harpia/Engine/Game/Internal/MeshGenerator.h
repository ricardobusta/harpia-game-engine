//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESHGENERATOR_H
#define HARPIAGAMEENGINE_MESHGENERATOR_H

#include "HarpiaMath.h"
#include <vector>

namespace Harpia::Internal {
        class MeshGenerator {
        public:
            static void BoxMesh(std::vector<float> &vertex, std::vector<int> &index, const Vector3 &pos,
                                const Vector3 &size);
        };
} // Harpia::Internal

#endif //HARPIAGAMEENGINE_MESHGENERATOR_H
