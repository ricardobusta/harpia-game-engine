//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/07/2022.
//

#include "player_spaceship_controller.h"

#include "hge/harpia_math.h"
#include "hge/key_code.h"

namespace SampleGame {
    bool rotating = false;
    float rotateStart = 0;
    float rotationDuration = 1;
    bool shooting = false;
    float shootingStart = 0;
    float shootingDuration = 1.5f;
    float bulletSize = 0.3f;
    float bulletOffset = 1.5f;
    float bulletSpeed = -20.0f;

    void PlayerSpaceshipController::Update() {
        auto speed = 10.0f * Time()->deltaTime;
        auto x = Input()->GetKeyIsDown(Harpia::KeyCode::D) - Input()->GetKeyIsDown(Harpia::KeyCode::A) +
                 Input()->GetKeyIsDown(Harpia::KeyCode::Right) - Input()->GetKeyIsDown(Harpia::KeyCode::Left);
        auto z = Input()->GetKeyIsDown(Harpia::KeyCode::S) - Input()->GetKeyIsDown(Harpia::KeyCode::W) +
                 Input()->GetKeyIsDown(Harpia::KeyCode::Down) - Input()->GetKeyIsDown(Harpia::KeyCode::Up);

        auto obj = GetObject();

        auto pos = obj->transform.GetPosition();
        pos.x += x * speed;
        pos.z += z * speed;

        obj->transform.SetPosition(pos);

        if (!shooting && Input()->GetKeyDown(Harpia::KeyCode::Space)) {
            shooting = true;
            shootingStart = Time()->now;
            bullet1->transform.SetScale({bulletSize, bulletSize, bulletSize});
            bullet1->transform.SetRotation(180 * Harpia::Math::Deg2Rad, {0, 1, 0});
            bullet1->transform.SetPosition(pos + Harpia::Vector3{bulletOffset, 0, 0});
            bullet2->transform.SetScale({bulletSize, bulletSize, bulletSize});
            bullet2->transform.SetPosition(pos + Harpia::Vector3{-bulletOffset, 0, 0});
            bullet2->transform.SetRotation(180 * Harpia::Math::Deg2Rad, {0, 1, 0});
        }

        auto bulletVelocity = Harpia::Vector3{0, 0, Time()->deltaTime * bulletSpeed};
        if (shooting) {
            if (Time()->now - shootingStart < shootingDuration) {
                bullet1->transform.SetPosition(bullet1->transform.GetPosition() + bulletVelocity);
                bullet2->transform.SetPosition(bullet2->transform.GetPosition() + bulletVelocity);
            }else{
                shooting = false;
                bullet1->transform.SetPosition({1000,0,0});
                bullet1->transform.SetScale(Harpia::Vector<3>::zero);
                bullet2->transform.SetPosition({1000,0,0});
                bullet2->transform.SetScale(Harpia::Vector<3>::zero);
            }
        }

        if (!rotating && Input()->GetKeyDown(Harpia::KeyCode::LeftCtrl)) {
            rotating = true;
            rotateStart = Time()->now;
        }

        if (rotating) {
            if (Time()->now - rotateStart < rotationDuration) {
                obj->transform.Rotate(6 * Time()->deltaTime, {0, 0, 1});
            } else {
                rotating = false;
                obj->transform.SetRotation(180 * Harpia::Math::Deg2Rad, {0, 1, 0});
            }
        }
    }
}// namespace SampleGame