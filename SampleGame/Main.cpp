//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "Application.h"

using namespace Harpia;

int main(int argc, char **argv) {
    auto app = Engine::Application(Engine::Configuration());

    while(app.Execute()){}

    return app.Result();
}