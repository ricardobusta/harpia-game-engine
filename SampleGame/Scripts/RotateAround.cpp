//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#include "RotateAround.h"
#include "Vector3.h"

namespace SampleGame {
    void RotateAround::Update() {
        target->GetRotation().Rotate(0.1f,Harpia::Vector3(1,0,0));
        target->GetRotation().Rotate(0.5f,Harpia::Vector3(0,1,0));
    }
} // SampleGame