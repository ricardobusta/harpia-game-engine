//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_H
#define HARPIAGAMEENGINE_RENDERER_H

namespace Harpia {

    class Renderer {
    public:
        virtual int WindowFlags();

        virtual int Initialize();
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERER_H
