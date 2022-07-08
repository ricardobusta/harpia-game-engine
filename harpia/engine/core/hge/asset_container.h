//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#ifndef HARPIAGAMEENGINE_ASSET_CONTAINER_H
#define HARPIAGAMEENGINE_ASSET_CONTAINER_H

#include "asset.h"
#include "hge/debug.h"
#include <functional>
#include <map>
#include <string>

namespace Harpia::Internal {
    template<class TAsset>
    class AssetContainerEntry {
    public:
        TAsset *asset;
        int useCount;
    };

    template<class TAsset>
    class AssetContainer {
    private:
        std::map<std::string, AssetContainerEntry<TAsset> *> _assetMap;

    public:
        AssetContainer() {
            static_assert(std::is_base_of<Asset, TAsset>::value, "Type expected to inherit from Asset.");
        }

        TAsset *LoadAsset(const std::string &path, std::function<TAsset *(const std::string &)> loadFunction) {
            auto it = _assetMap.find(path);
            if (it != _assetMap.end()) {
                it->second->useCount++;
                DebugLog("Loading existing %s %s use count: %d", typeid(TAsset).name(), path.c_str(), it->second->useCount);
                return it->second->asset;
            }
            auto asset = loadFunction(path);
            if (asset == nullptr) {
                return nullptr;
            }
            auto entry = new AssetContainerEntry<TAsset>();
            static_cast<Asset *>(asset)->path = path;
            entry->asset = asset;
            entry->useCount = 1;
            _assetMap[path] = entry;
            return asset;
        }

        void ReleaseAsset(TAsset *asset, std::function<void(TAsset *asset)> deleteAsset) {
            if (asset == nullptr) {
                DebugLogError("%s reference was null.", typeid(TAsset).name());
                return;
            }

            auto path = static_cast<Asset *>(asset)->path;
            auto it = _assetMap.find(path);
            if (it == _assetMap.end()) {
                DebugLogError("Trying to release %s %s, but asset was not loaded.", typeid(TAsset).name(), path.c_str());
                return;
            }

            it->second->useCount--;
            if (it->second->useCount <= 0) {
                deleteAsset(asset);
                delete it->second;
                _assetMap.erase(path);
            }
            DebugLog("%s released. Usages: %d", typeid(TAsset).name(), it->second->useCount);
        }

        void Clear(std::function<void(TAsset *asset)> deleteAsset) {
            for (auto it = _assetMap.begin(); it != _assetMap.end(); it++) {
                deleteAsset(it->second->asset);
                delete it->second;
            }
            _assetMap.clear();
        }
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_ASSET_CONTAINER_H
