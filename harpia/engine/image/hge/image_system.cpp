//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#include "image_system.h"

#include "hge/core_system.h"
#include "hge/debug.h"
#include <SDL_image.h>

namespace Harpia::Internal {
    int ImageSystem::Initialize(CoreSystem *coreSystem) {
        auto window = coreSystem->GetWindow();
        _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr) {
            DebugLogError("Renderer could not be created. SDL Error: %s", SDL_GetError());
            return -1;
        }

        auto result = SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        if (result < 0) {
            DebugLogError("Failed to set renderer color. SDL Error: %s", SDL_GetError());
            return result;
        }

        const auto imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            DebugLogError("Could not initialize IMG. Error: %s.", IMG_GetError());
            return -1;
        }

        return 0;
    }

    int ImageSystem::GetWindowFlags() {
        return 0;
    }

    int ImageSystem::GetInitFlags() {
        return 0;
    }

    void ImageSystem::Quit() {
        _loadedTextures.Clear([this](auto t) {
            DeleteTexture(t);
        });
        SDL_DestroyRenderer(_renderer);
        IMG_Quit();
    }

    TextureAsset *ImageSystem::LoadTexture(const std::string &path) {
        return _loadedTextures.LoadAsset(path, [this](auto p) -> TextureAsset * {
            SDL_Texture *ref = nullptr;

            SDL_Surface *surface = IMG_Load(p.c_str());
            if (surface == nullptr) {
                DebugLogError("Texture %s not loaded. SDL_image Error: %s", p.c_str(), IMG_GetError());
                return nullptr;
            }

            ref = SDL_CreateTextureFromSurface(_renderer, surface);

            SDL_FreeSurface(surface);

            if (ref == nullptr) {
                DebugLogError("Texture %s not created. SDL Error: %s", p.c_str(), IMG_GetError());
                return nullptr;
            }

            auto texture = new TextureAsset(ref, this);
            return texture;
        });
    }

    void ImageSystem::ReleaseTexture(Harpia::TextureAsset *asset) {
        _loadedTextures.ReleaseAsset(asset, [this](auto t) {
            DeleteTexture(t);
        });
    }

    void ImageSystem::DeleteTexture(TextureAsset *asset) {
        SDL_DestroyTexture(asset->ref);
    }
}// namespace Harpia::Internal