//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#include "RotateAround.h"

namespace SampleGame {
    void RotateAround::Update() {
        auto tr = target->GetTrMatrix();
        tr = glm::rotate(tr, 0.1f, {1,0,0});
        tr = glm::rotate(tr, 0.5f, {0,1,0});
        target->SetTrMatrix(tr);
    }
} // SampleGame