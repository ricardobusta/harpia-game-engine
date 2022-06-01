//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//
#include "Configuration.h"

namespace Harpia {
    Configuration::Configuration() {
        mappedKeys = new std::list<int>();
    }

    Configuration::~Configuration() {
        delete mappedKeys;
    }
}
