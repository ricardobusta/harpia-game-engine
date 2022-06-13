//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#ifndef HARPIAGAMEENGINE_ROTATEAROUND_H
#define HARPIAGAMEENGINE_ROTATEAROUND_H

#include "Component.h"

namespace SampleGame {

    class RotateAround: public Harpia::Component {
    public:
        Harpia::Transform * target;
    public:
        void Update() override;
    };

} // SampleGame

#endif //HARPIAGAMEENGINE_ROTATEAROUND_H
