//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 26/08/2022.
//

#ifndef INC_1JAMCHOICES_POOL_H
#define INC_1JAMCHOICES_POOL_H

#include <stack>

namespace Harpia {
    template<class T>
    class Pool {
    public:
        void Push(T *object) {
            _stack.push(object);
        }

        T *Pop() {
            if (_stack.empty()) {
                return nullptr;
            }
            auto object = _stack.top();
            _stack.pop();
            return object;
        }

        [[nodiscard]] bool Empty() const {
            return _stack.empty();
        }

        [[nodiscard]] int Size() const{
            return _stack.size();
        }
    private:
        std::stack<T *> _stack;
    };
}// namespace Harpia

#endif//INC_1JAMCHOICES_POOL_H
