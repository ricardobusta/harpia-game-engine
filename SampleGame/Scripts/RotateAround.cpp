//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#include "RotateAround.h"
#include "Quaternion.h"
#include "Vector3.h"

namespace SampleGame {
    void RotateAround::Update() {
        target->GetRotation().Rotate(1,Harpia::Vector3(0,1,0));
    }
} // SampleGame