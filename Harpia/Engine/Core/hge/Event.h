//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_EVENT_H
#define HARPIAGAMEENGINE_EVENT_H

#include <list>
#include <functional>
#include "hge/Debug.h"

namespace Harpia {
    template<typename... Args>
    class Event {
    private:
        std::list<std::function<void(Args...)>> _listeners;
    public:
        void AddListener(const std::function<void(Args...)> &listener) {
            _listeners.push_back(listener);
        }

        void RemoveListener(const std::function<void(Args...)> &listener) {
            auto it = std::find(_listeners.begin(), _listeners.end(), listener);
            if (it != _listeners.end()) {
                _listeners.erase(it);
            } else {
                DebugLogWarning("Trying to remove a listener that was not assigned.");
            }
        }

        void Invoke(Args... args) {
            for (auto l: _listeners) {
                if (l != nullptr) {
                    l(args...);
                }
            }
        }

        void operator+=(const std::function<void(Args...)> &listener) {
            AddListener(listener);
        }

        void operator-=(const std::function<void(Args...)> &listener) {
            RemoveListener(listener);
        }
    };

} // Harpia

#endif //HARPIAGAMEENGINE_EVENT_H
