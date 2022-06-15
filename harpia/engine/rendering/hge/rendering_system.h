//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_H

#include <list>
#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include "hge/mesh_asset.h"
#include "hge/material_asset.h"

namespace Harpia::Internal {
    class RenderingSystem : public Internal::IApplicationSystem {
    protected:
        std::list<Camera_Internal *> _cameras;
        std::list<Renderer_Internal *> _renderers;
        SDL_Window *_window = nullptr;
    public:
        int Initialize(GameConfiguration &configuration, Internal::CoreSystem *coreSystem);
        virtual void RenderFrame() = 0;
        void AddCamera(Camera_Internal *camera);
        void AddRenderer(Renderer_Internal *renderer);
        virtual ~RenderingSystem() = default;

        virtual MeshAsset *LoadMesh(const std::vector<GLfloat> &vertex, const std::vector<GLint> &index) = 0;
        virtual void ReleaseMesh(MeshAsset *mesh) = 0;
        virtual void UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                                GLuint *indexBufferId, GLuint indexCount, GLint indexData[]) = 0;
        virtual ShaderAsset *LoadShader() = 0;
        virtual void ReleaseShader(ShaderAsset *shader) = 0;
    private:
        virtual int RenderingInitialize() = 0;
        int GetInitFlags() override;
    };

} // Harpia::Internal

#endif //HARPIAGAMEENGINE_RENDERING_SYSTEM_H
