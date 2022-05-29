//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Core.h"

int main(){
    Harpia::Core core;
    Harpia::Configuration configuration;
    configuration.windowSize.x = 640;
    configuration.windowSize.y = 480;
    return core.HelloWorld(configuration);
}