//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#ifndef HARPIAGAMEENGINE_ROTATE_AROUND_H
#define HARPIAGAMEENGINE_ROTATE_AROUND_H

#include <hge/component.h>

namespace SampleGame {
    class RotateAround : public Harpia::Component {
    private:
        float _t = 0;

    public:
        Harpia::Vector3 speed;
        Harpia::Transform *target;

    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_ROTATE_AROUND_H
