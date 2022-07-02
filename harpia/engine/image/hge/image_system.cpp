//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#include "image_system.h"

#include "hge/debug.h"
#include "hge/texture_asset.h"
#include <SDL_image.h>

int Harpia::Internal::ImageSystem::Initialize() {
    const auto imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        DebugLogError("Could not initialize IMG. Error: %s.", IMG_GetError());
        return -1;
    }

    return 0;
}

int Harpia::Internal::ImageSystem::GetWindowFlags() {
    return 0;
}

int Harpia::Internal::ImageSystem::GetInitFlags() {
    return 0;
}

void Harpia::Internal::ImageSystem::Quit() {
    IMG_Quit();
}

Harpia::TextureAsset *Harpia::Internal::ImageSystem::LoadTexture() {
    return new TextureAsset(this);
}
