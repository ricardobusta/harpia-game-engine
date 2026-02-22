//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_KEY_CODE_H
#define HARPIAGAMEENGINE_KEY_CODE_H

namespace Harpia {
    enum class KeyCode {
        Unknown = 0,

        // Letters
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // Number row
        Alpha0, Alpha1, Alpha2, Alpha3, Alpha4,
        Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,

        // Function keys
        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,

        // Arrow keys
        Up, Down, Left, Right,

        // Special keys
        Space,
        Return,
        Escape,
        Tab,
        Backspace,
        Delete,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,

        // Modifiers
        LeftShift, RightShift,
        LeftCtrl, RightCtrl,
        LeftAlt, RightAlt,
        LeftSuper, RightSuper,
        CapsLock,
        NumLock,
        ScrollLock,

        // Numpad
        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
        Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        NumpadEnter,
        NumpadPlus,
        NumpadMinus,
        NumpadMultiply,
        NumpadDivide,
        NumpadPeriod,

        // Punctuation / symbols
        Minus,
        Equals,
        LeftBracket,
        RightBracket,
        Backslash,
        Semicolon,
        Apostrophe,
        Grave,
        Comma,
        Period,
        Slash,

        // Media / extra
        PrintScreen,
        Pause,
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_KEY_CODE_H
