﻿#pragma once

#undef KEY_EXECUTE

#define SDLK_KEY_MASK (1<<30)
#define KEY_TO_KEYCODE(X)  (X | SDLK_KEY_MASK)

namespace Aula {
    namespace SDL {
        /*** ブレンドモード ***/
        enum BlendMode {
            BLEND_NONE = 0x00000000, BLEND_ALPHA = 0x00000001,
            BLEND_ADD = 0x00000002, BLENDMODE_MOD = 0x00000004
        };
        
        /*** FontStyle ***/
        enum FontStyle {
            FONT_NORMAL = 0x00, FONT_BOLD = 0x01, FONT_ITALIC = 0x02,
            FONT_UNDERLINE = 0x04, FONT_STRIKETHROUGH = 0x08
        };
        
        /*** テクスチャタイプ ***/
        enum TextureType {
            TEXTURE_STATIC, // Changes rarely, not lockable
            TEXTURE_STREAMING, // Changes frequently, lockable
            TEXTURE_TARGET // Texture can be used as a render target
        };
        
        /*** 画像保存タイプ ***/
        enum SaveType {
            SAVE_BMP, SAVE_PNG
        };
        
        /*** マウスボタン ***/
        enum MouseButton {
            MOUSE_LEFT = 0, MOUSE_MIDDLE, MOUSE_RIGHT
        };
        
        /*** ジョイスティック十字ボタン ***/
        enum CrossButton {
            JOY_LEFT=0, JOY_UP, JOY_RIGHT, JOY_DOWN
        };
        
        /*** スキャンコード ***/
        enum ScanCode {
            KEY_UNKNOWN = 0,

            KEY_A = 4,
            KEY_B = 5,
            KEY_C = 6,
            KEY_D = 7,
            KEY_E = 8,
            KEY_F = 9,
            KEY_G = 10,
            KEY_H = 11,
            KEY_I = 12,
            KEY_J = 13,
            KEY_K = 14,
            KEY_L = 15,
            KEY_M = 16,
            KEY_N = 17,
            KEY_O = 18,
            KEY_P = 19,
            KEY_Q = 20,
            KEY_R = 21,
            KEY_S = 22,
            KEY_T = 23,
            KEY_U = 24,
            KEY_V = 25,
            KEY_W = 26,
            KEY_X = 27,
            KEY_Y = 28,
            KEY_Z = 29,

            KEY_1 = 30,
            KEY_2 = 31,
            KEY_3 = 32,
            KEY_4 = 33,
            KEY_5 = 34,
            KEY_6 = 35,
            KEY_7 = 36,
            KEY_8 = 37,
            KEY_9 = 38,
            KEY_0 = 39,

            KEY_RETURN = 40,
            KEY_ESCAPE = 41,
            KEY_BACKSPACE = 42,
            KEY_TAB = 43,
            KEY_SPACE = 44,

            KEY_MINUS = 45,
            KEY_EQUALS = 46,
            KEY_LEFTBRACKET = 47,
            KEY_RIGHTBRACKET = 48,
            KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                 *   key on ISO keyboards and at the right end
                                 *   of the QWERTY row on ANSI keyboards.
                                 *   Produces REVERSE SOLIDUS (backslash) and
                                 *   VERTICAL LINE in a US layout, REVERSE
                                 *   SOLIDUS and VERTICAL LINE in a UK Mac
                                 *   layout, NUMBER SIGN and TILDE in a UK
                                 *   Windows layout, DOLLAR SIGN and POUND SIGN
                                 *   in a Swiss German layout, NUMBER SIGN and
                                 *   APOSTROPHE in a German layout, GRAVE
                                 *   ACCENT and POUND SIGN in a French Mac
                                 *   layout, and ASTERISK and MICRO SIGN in a
                                 *   French Windows layout.
                                 */
            KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                 *   instead of 49 for the same key, but all
                                 *   OSes I've seen treat the two codes
                                 *   identically. So, as an implementor, unless
                                 *   your keyboard generates both of those
                                 *   codes and your OS treats them differently,
                                 *   you should generate KEY_BACKSLASH
                                 *   instead of this code. As a user, you
                                 *   should not rely on this code because SDL
                                 *   will never generate it with most (all?)
                                 *   keyboards.
                                 */
            KEY_SEMICOLON = 51,
            KEY_APOSTROPHE = 52,
            KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                             *   and ISO keyboards). Produces GRAVE ACCENT and
                             *   TILDE in a US Windows layout and in US and UK
                             *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                             *   and NOT SIGN in a UK Windows layout, SECTION
                             *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                             *   layouts on ISO keyboards, SECTION SIGN and
                             *   DEGREE SIGN in a Swiss German layout (Mac:
                             *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                             *   DEGREE SIGN in a German layout (Mac: only on
                             *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                             *   French Windows layout, COMMERCIAL AT and
                             *   NUMBER SIGN in a French Mac layout on ISO
                             *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                             *   SIGN in a Swiss German, German, or French Mac
                             *   layout on ANSI keyboards.
                             */
            KEY_COMMA = 54,
            KEY_PERIOD = 55,
            KEY_SLASH = 56,

            KEY_CAPSLOCK = 57,

            KEY_F1 = 58,
            KEY_F2 = 59,
            KEY_F3 = 60,
            KEY_F4 = 61,
            KEY_F5 = 62,
            KEY_F6 = 63,
            KEY_F7 = 64,
            KEY_F8 = 65,
            KEY_F9 = 66,
            KEY_F10 = 67,
            KEY_F11 = 68,
            KEY_F12 = 69,

            KEY_PRINTSCREEN = 70,
            KEY_SCROLLLOCK = 71,
            KEY_PAUSE = 72,
            KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but does send code 73, not 117) */
            KEY_HOME = 74,
            KEY_PAGEUP = 75,
            KEY_DELETE = 76,
            KEY_END = 77,
            KEY_PAGEDOWN = 78,
            KEY_RIGHT = 79,
            KEY_LEFT = 80,
            KEY_DOWN = 81,
            KEY_UP = 82,

            KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards */
            KEY_KP_DIVIDE = 84,
            KEY_KP_MULTIPLY = 85,
            KEY_KP_MINUS = 86,
            KEY_KP_PLUS = 87,
            KEY_KP_ENTER = 88,
            KEY_KP_1 = 89,
            KEY_KP_2 = 90,
            KEY_KP_3 = 91,
            KEY_KP_4 = 92,
            KEY_KP_5 = 93,
            KEY_KP_6 = 94,
            KEY_KP_7 = 95,
            KEY_KP_8 = 96,
            KEY_KP_9 = 97,
            KEY_KP_0 = 98,
            KEY_KP_PERIOD = 99,

            KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                       *   keyboards have over ANSI ones,
                                       *   located between left shift and Y.
                                       *   Produces GRAVE ACCENT and TILDE in a
                                       *   US or UK Mac layout, REVERSE SOLIDUS
                                       *   (backslash) and VERTICAL LINE in a
                                       *   US or UK Windows layout, and
                                       *   LESS-THAN SIGN and GREATER-THAN SIGN
                                       *   in a Swiss German, German, or French
                                       *   layout. */
            KEY_APPLICATION = 101, /**< windows contextual menu, compose */
            KEY_POWER = 102, /**< The USB document says this is a status flag,
                              *   not a physical key - but some Mac keyboards
                              *   do have a power key. */
            KEY_KP_EQUALS = 103,
            KEY_F13 = 104,
            KEY_F14 = 105,
            KEY_F15 = 106,
            KEY_F16 = 107,
            KEY_F17 = 108,
            KEY_F18 = 109,
            KEY_F19 = 110,
            KEY_F20 = 111,
            KEY_F21 = 112,
            KEY_F22 = 113,
            KEY_F23 = 114,
            KEY_F24 = 115,
            KEY_EXECUTE = 116,
            KEY_HELP = 117,
            KEY_MENU = 118,
            KEY_SELECT = 119,
            KEY_STOP = 120,
            KEY_AGAIN = 121,   /**< redo */
            KEY_UNDO = 122,
            KEY_CUT = 123,
            KEY_COPY = 124,
            KEY_PASTE = 125,
            KEY_FIND = 126,
            KEY_MUTE = 127,
            KEY_VOLUMEUP = 128,
            KEY_VOLUMEDOWN = 129,
        /* not sure whether there's a reason to enable these */
        /*     KEY_LOCKINGCAPSLOCK = 130,  */
        /*     KEY_LOCKINGNUMLOCK = 131, */
        /*     KEY_LOCKINGSCROLLLOCK = 132, */
            KEY_KP_COMMA = 133,
            KEY_KP_EQUALSAS400 = 134,

            KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                    footnotes in USB doc */
            KEY_INTERNATIONAL2 = 136,
            KEY_INTERNATIONAL3 = 137, /**< Yen */
            KEY_INTERNATIONAL4 = 138,
            KEY_INTERNATIONAL5 = 139,
            KEY_INTERNATIONAL6 = 140,
            KEY_INTERNATIONAL7 = 141,
            KEY_INTERNATIONAL8 = 142,
            KEY_INTERNATIONAL9 = 143,
            KEY_LANG1 = 144, /**< Hangul/English toggle */
            KEY_LANG2 = 145, /**< Hanja conversion */
            KEY_LANG3 = 146, /**< Katakana */
            KEY_LANG4 = 147, /**< Hiragana */
            KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
            KEY_LANG6 = 149, /**< reserved */
            KEY_LANG7 = 150, /**< reserved */
            KEY_LANG8 = 151, /**< reserved */
            KEY_LANG9 = 152, /**< reserved */

            KEY_ALTERASE = 153, /**< Erase-Eaze */
            KEY_SYSREQ = 154,
            KEY_CANCEL = 155,
            KEY_CLEAR = 156,
            KEY_PRIOR = 157,
            KEY_RETURN2 = 158,
            KEY_SEPARATOR = 159,
            KEY_OUT = 160,
            KEY_OPER = 161,
            KEY_CLEARAGAIN = 162,
            KEY_CRSEL = 163,
            KEY_EXSEL = 164,

            KEY_KP_00 = 176,
            KEY_KP_000 = 177,
            KEY_THOUSANDSSEPARATOR = 178,
            KEY_DECIMALSEPARATOR = 179,
            KEY_CURRENCYUNIT = 180,
            KEY_CURRENCYSUBUNIT = 181,
            KEY_KP_LEFTPAREN = 182,
            KEY_KP_RIGHTPAREN = 183,
            KEY_KP_LEFTBRACE = 184,
            KEY_KP_RIGHTBRACE = 185,
            KEY_KP_TAB = 186,
            KEY_KP_BACKSPACE = 187,
            KEY_KP_A = 188,
            KEY_KP_B = 189,
            KEY_KP_C = 190,
            KEY_KP_D = 191,
            KEY_KP_E = 192,
            KEY_KP_F = 193,
            KEY_KP_XOR = 194,
            KEY_KP_POWER = 195,
            KEY_KP_PERCENT = 196,
            KEY_KP_LESS = 197,
            KEY_KP_GREATER = 198,
            KEY_KP_AMPERSAND = 199,
            KEY_KP_DBLAMPERSAND = 200,
            KEY_KP_VERTICALBAR = 201,
            KEY_KP_DBLVERTICALBAR = 202,
            KEY_KP_COLON = 203,
            KEY_KP_HASH = 204,
            KEY_KP_SPACE = 205,
            KEY_KP_AT = 206,
            KEY_KP_EXCLAM = 207,
            KEY_KP_MEMSTORE = 208,
            KEY_KP_MEMRECALL = 209,
            KEY_KP_MEMCLEAR = 210,
            KEY_KP_MEMADD = 211,
            KEY_KP_MEMSUBTRACT = 212,
            KEY_KP_MEMMULTIPLY = 213,
            KEY_KP_MEMDIVIDE = 214,
            KEY_KP_PLUSMINUS = 215,
            KEY_KP_CLEAR = 216,
            KEY_KP_CLEARENTRY = 217,
            KEY_KP_BINARY = 218,
            KEY_KP_OCTAL = 219,
            KEY_KP_DECIMAL = 220,
            KEY_KP_HEXADECIMAL = 221,

            KEY_LCTRL = 224,
            KEY_LSHIFT = 225,
            KEY_LALT = 226, /**< alt, option */
            KEY_LGUI = 227, /**< windows, command (apple), meta */
            KEY_RCTRL = 228,
            KEY_RSHIFT = 229,
            KEY_RALT = 230, /**< alt gr, option */
            KEY_RGUI = 231, /**< windows, command (apple), meta */

            KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                         *   by any of the above, but since there's a
                                         *   special KMOD_MODE for it I'm adding it here
                                         */
            KEY_AUDIONEXT = 258,
            KEY_AUDIOPREV = 259,
            KEY_AUDIOSTOP = 260,
            KEY_AUDIOPLAY = 261,
            KEY_AUDIOMUTE = 262,
            KEY_MEDIASELECT = 263,
            KEY_WWW = 264,
            KEY_MAIL = 265,
            KEY_CALCULATOR = 266,
            KEY_COMPUTER = 267,
            KEY_AC_SEARCH = 268,
            KEY_AC_HOME = 269,
            KEY_AC_BACK = 270,
            KEY_AC_FORWARD = 271,
            KEY_AC_STOP = 272,
            KEY_AC_REFRESH = 273,
            KEY_AC_BOOKMARKS = 274,

            KEY_BRIGHTNESSDOWN = 275,
            KEY_BRIGHTNESSUP = 276,
            KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                                   switch, video mode switch */
            KEY_KBDILLUMTOGGLE = 278,
            KEY_KBDILLUMDOWN = 279,
            KEY_KBDILLUMUP = 280,
            KEY_EJECT = 281,
            KEY_SLEEP = 282,

            KEY_APP1 = 283,
            KEY_APP2 = 284,

            /* Add any other keys here. */

            NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                        for array bounds */
        };
        
        /*** キーコード ***/
        enum KeyCode {
            SDLK_UNKNOWN = 0,
            SDLK_RETURN = '\r',
            SDLK_ESCAPE = '\033',
            SDLK_BACKSPACE = '\b',
            SDLK_TAB = '\t',
            SDLK_SPACE = ' ',
            SDLK_EXCLAIM = '!',
            SDLK_QUOTEDBL = '"',
            SDLK_HASH = '#',
            SDLK_PERCENT = '%',
            SDLK_DOLLAR = '$',
            SDLK_AMPERSAND = '&',
            SDLK_QUOTE = '\'',
            SDLK_LEFTPAREN = '(',
            SDLK_RIGHTPAREN = ')',
            SDLK_ASTERISK = '*',
            SDLK_PLUS = '+',
            SDLK_COMMA = 44,
            SDLK_MINUS = '-',
            SDLK_PERIOD = '.',
            SDLK_SLASH = '/',
            SDLK_0 = '0',
            SDLK_1 = '1',
            SDLK_2 = '2',
            SDLK_3 = '3',
            SDLK_4 = '4',
            SDLK_5 = '5',
            SDLK_6 = '6',
            SDLK_7 = '7',
            SDLK_8 = '8',
            SDLK_9 = '9',
            SDLK_COLON = ':',
            SDLK_SEMICOLON = ';',
            SDLK_LESS = '<',
            SDLK_EQUALS = '=',
            SDLK_GREATER = '>',
            SDLK_QUESTION = '?',
            SDLK_AT = '@',
            /*
               Skip uppercase letters
             */
            SDLK_LEFTBRACKET = '[',
            SDLK_BACKSLASH = '\\',
            SDLK_RIGHTBRACKET = ']',
            SDLK_CARET = '^',
            SDLK_UNDERSCORE = '_',
            SDLK_BACKQUOTE = '`',
            SDLK_a = 'a',
            SDLK_b = 'b',
            SDLK_c = 'c',
            SDLK_d = 'd',
            SDLK_e = 'e',
            SDLK_f = 'f',
            SDLK_g = 'g',
            SDLK_h = 'h',
            SDLK_i = 'i',
            SDLK_j = 'j',
            SDLK_k = 'k',
            SDLK_l = 'l',
            SDLK_m = 'm',
            SDLK_n = 'n',
            SDLK_o = 'o',
            SDLK_p = 'p',
            SDLK_q = 'q',
            SDLK_r = 'r',
            SDLK_s = 's',
            SDLK_t = 't',
            SDLK_u = 'u',
            SDLK_v = 'v',
            SDLK_w = 'w',
            SDLK_x = 'x',
            SDLK_y = 'y',
            SDLK_z = 'z',
            SDLK_CAPSLOCK = KEY_TO_KEYCODE(KEY_CAPSLOCK),
            SDLK_F1 = KEY_TO_KEYCODE(KEY_F1),
            SDLK_F2 = KEY_TO_KEYCODE(KEY_F2),
            SDLK_F3 = KEY_TO_KEYCODE(KEY_F3),
            SDLK_F4 = KEY_TO_KEYCODE(KEY_F4),
            SDLK_F5 = KEY_TO_KEYCODE(KEY_F5),
            SDLK_F6 = KEY_TO_KEYCODE(KEY_F6),
            SDLK_F7 = KEY_TO_KEYCODE(KEY_F7),
            SDLK_F8 = KEY_TO_KEYCODE(KEY_F8),
            SDLK_F9 = KEY_TO_KEYCODE(KEY_F9),
            SDLK_F10 = KEY_TO_KEYCODE(KEY_F10),
            SDLK_F11 = KEY_TO_KEYCODE(KEY_F11),
            SDLK_F12 = KEY_TO_KEYCODE(KEY_F12),
            SDLK_PRINTSCREEN = KEY_TO_KEYCODE(KEY_PRINTSCREEN),
            SDLK_SCROLLLOCK = KEY_TO_KEYCODE(KEY_SCROLLLOCK),
            SDLK_PAUSE = KEY_TO_KEYCODE(KEY_PAUSE),
            SDLK_INSERT = KEY_TO_KEYCODE(KEY_INSERT),
            SDLK_HOME = KEY_TO_KEYCODE(KEY_HOME),
            SDLK_PAGEUP = KEY_TO_KEYCODE(KEY_PAGEUP),
            SDLK_DELETE = '\177',
            SDLK_END = KEY_TO_KEYCODE(KEY_END),
            SDLK_PAGEDOWN = KEY_TO_KEYCODE(KEY_PAGEDOWN),
            SDLK_RIGHT = KEY_TO_KEYCODE(KEY_RIGHT),
            SDLK_LEFT = KEY_TO_KEYCODE(KEY_LEFT),
            SDLK_DOWN = KEY_TO_KEYCODE(KEY_DOWN),
            SDLK_UP = KEY_TO_KEYCODE(KEY_UP),
            SDLK_NUMLOCKCLEAR = KEY_TO_KEYCODE(KEY_NUMLOCKCLEAR),
            SDLK_KP_DIVIDE = KEY_TO_KEYCODE(KEY_KP_DIVIDE),
            SDLK_KP_MULTIPLY = KEY_TO_KEYCODE(KEY_KP_MULTIPLY),
            SDLK_KP_MINUS = KEY_TO_KEYCODE(KEY_KP_MINUS),
            SDLK_KP_PLUS = KEY_TO_KEYCODE(KEY_KP_PLUS),
            SDLK_KP_ENTER = KEY_TO_KEYCODE(KEY_KP_ENTER),
            SDLK_KP_1 = KEY_TO_KEYCODE(KEY_KP_1),
            SDLK_KP_2 = KEY_TO_KEYCODE(KEY_KP_2),
            SDLK_KP_3 = KEY_TO_KEYCODE(KEY_KP_3),
            SDLK_KP_4 = KEY_TO_KEYCODE(KEY_KP_4),
            SDLK_KP_5 = KEY_TO_KEYCODE(KEY_KP_5),
            SDLK_KP_6 = KEY_TO_KEYCODE(KEY_KP_6),
            SDLK_KP_7 = KEY_TO_KEYCODE(KEY_KP_7),
            SDLK_KP_8 = KEY_TO_KEYCODE(KEY_KP_8),
            SDLK_KP_9 = KEY_TO_KEYCODE(KEY_KP_9),
            SDLK_KP_0 = KEY_TO_KEYCODE(KEY_KP_0),
            SDLK_KP_PERIOD = KEY_TO_KEYCODE(KEY_KP_PERIOD),
            SDLK_APPLICATION = KEY_TO_KEYCODE(KEY_APPLICATION),
            SDLK_POWER = KEY_TO_KEYCODE(KEY_POWER),
            SDLK_KP_EQUALS = KEY_TO_KEYCODE(KEY_KP_EQUALS),
            SDLK_F13 = KEY_TO_KEYCODE(KEY_F13),
            SDLK_F14 = KEY_TO_KEYCODE(KEY_F14),
            SDLK_F15 = KEY_TO_KEYCODE(KEY_F15),
            SDLK_F16 = KEY_TO_KEYCODE(KEY_F16),
            SDLK_F17 = KEY_TO_KEYCODE(KEY_F17),
            SDLK_F18 = KEY_TO_KEYCODE(KEY_F18),
            SDLK_F19 = KEY_TO_KEYCODE(KEY_F19),
            SDLK_F20 = KEY_TO_KEYCODE(KEY_F20),
            SDLK_F21 = KEY_TO_KEYCODE(KEY_F21),
            SDLK_F22 = KEY_TO_KEYCODE(KEY_F22),
            SDLK_F23 = KEY_TO_KEYCODE(KEY_F23),
            SDLK_F24 = KEY_TO_KEYCODE(KEY_F24),
            SDLK_EXECUTE = KEY_TO_KEYCODE(KEY_EXECUTE),
            SDLK_HELP = KEY_TO_KEYCODE(KEY_HELP),
            SDLK_MENU = KEY_TO_KEYCODE(KEY_MENU),
            SDLK_SELECT = KEY_TO_KEYCODE(KEY_SELECT),
            SDLK_STOP = KEY_TO_KEYCODE(KEY_STOP),
            SDLK_AGAIN = KEY_TO_KEYCODE(KEY_AGAIN),
            SDLK_UNDO = KEY_TO_KEYCODE(KEY_UNDO),
            SDLK_CUT = KEY_TO_KEYCODE(KEY_CUT),
            SDLK_COPY = KEY_TO_KEYCODE(KEY_COPY),
            SDLK_PASTE = KEY_TO_KEYCODE(KEY_PASTE),
            SDLK_FIND = KEY_TO_KEYCODE(KEY_FIND),
            SDLK_MUTE = KEY_TO_KEYCODE(KEY_MUTE),
            SDLK_VOLUMEUP = KEY_TO_KEYCODE(KEY_VOLUMEUP),
            SDLK_VOLUMEDOWN = KEY_TO_KEYCODE(KEY_VOLUMEDOWN),
            SDLK_KP_COMMA = KEY_TO_KEYCODE(KEY_KP_COMMA),
            SDLK_KP_EQUALSAS400 =
                KEY_TO_KEYCODE(KEY_KP_EQUALSAS400),
            SDLK_ALTERASE = KEY_TO_KEYCODE(KEY_ALTERASE),
            SDLK_SYSREQ = KEY_TO_KEYCODE(KEY_SYSREQ),
            SDLK_CANCEL = KEY_TO_KEYCODE(KEY_CANCEL),
            SDLK_CLEAR = KEY_TO_KEYCODE(KEY_CLEAR),
            SDLK_PRIOR = KEY_TO_KEYCODE(KEY_PRIOR),
            SDLK_RETURN2 = KEY_TO_KEYCODE(KEY_RETURN2),
            SDLK_SEPARATOR = KEY_TO_KEYCODE(KEY_SEPARATOR),
            SDLK_OUT = KEY_TO_KEYCODE(KEY_OUT),
            SDLK_OPER = KEY_TO_KEYCODE(KEY_OPER),
            SDLK_CLEARAGAIN = KEY_TO_KEYCODE(KEY_CLEARAGAIN),
            SDLK_CRSEL = KEY_TO_KEYCODE(KEY_CRSEL),
            SDLK_EXSEL = KEY_TO_KEYCODE(KEY_EXSEL),
            SDLK_KP_00 = KEY_TO_KEYCODE(KEY_KP_00),
            SDLK_KP_000 = KEY_TO_KEYCODE(KEY_KP_000),
            SDLK_THOUSANDSSEPARATOR =
                KEY_TO_KEYCODE(KEY_THOUSANDSSEPARATOR),
            SDLK_DECIMALSEPARATOR =
                KEY_TO_KEYCODE(KEY_DECIMALSEPARATOR),
            SDLK_CURRENCYUNIT = KEY_TO_KEYCODE(KEY_CURRENCYUNIT),
            SDLK_CURRENCYSUBUNIT =
                KEY_TO_KEYCODE(KEY_CURRENCYSUBUNIT),
            SDLK_KP_LEFTPAREN = KEY_TO_KEYCODE(KEY_KP_LEFTPAREN),
            SDLK_KP_RIGHTPAREN = KEY_TO_KEYCODE(KEY_KP_RIGHTPAREN),
            SDLK_KP_LEFTBRACE = KEY_TO_KEYCODE(KEY_KP_LEFTBRACE),
            SDLK_KP_RIGHTBRACE = KEY_TO_KEYCODE(KEY_KP_RIGHTBRACE),
            SDLK_KP_TAB = KEY_TO_KEYCODE(KEY_KP_TAB),
            SDLK_KP_BACKSPACE = KEY_TO_KEYCODE(KEY_KP_BACKSPACE),
            SDLK_KP_A = KEY_TO_KEYCODE(KEY_KP_A),
            SDLK_KP_B = KEY_TO_KEYCODE(KEY_KP_B),
            SDLK_KP_C = KEY_TO_KEYCODE(KEY_KP_C),
            SDLK_KP_D = KEY_TO_KEYCODE(KEY_KP_D),
            SDLK_KP_E = KEY_TO_KEYCODE(KEY_KP_E),
            SDLK_KP_F = KEY_TO_KEYCODE(KEY_KP_F),
            SDLK_KP_XOR = KEY_TO_KEYCODE(KEY_KP_XOR),
            SDLK_KP_POWER = KEY_TO_KEYCODE(KEY_KP_POWER),
            SDLK_KP_PERCENT = KEY_TO_KEYCODE(KEY_KP_PERCENT),
            SDLK_KP_LESS = KEY_TO_KEYCODE(KEY_KP_LESS),
            SDLK_KP_GREATER = KEY_TO_KEYCODE(KEY_KP_GREATER),
            SDLK_KP_AMPERSAND = KEY_TO_KEYCODE(KEY_KP_AMPERSAND),
            SDLK_KP_DBLAMPERSAND =
                KEY_TO_KEYCODE(KEY_KP_DBLAMPERSAND),
            SDLK_KP_VERTICALBAR =
                KEY_TO_KEYCODE(KEY_KP_VERTICALBAR),
            SDLK_KP_DBLVERTICALBAR =
                KEY_TO_KEYCODE(KEY_KP_DBLVERTICALBAR),
            SDLK_KP_COLON = KEY_TO_KEYCODE(KEY_KP_COLON),
            SDLK_KP_HASH = KEY_TO_KEYCODE(KEY_KP_HASH),
            SDLK_KP_SPACE = KEY_TO_KEYCODE(KEY_KP_SPACE),
            SDLK_KP_AT = KEY_TO_KEYCODE(KEY_KP_AT),
            SDLK_KP_EXCLAM = KEY_TO_KEYCODE(KEY_KP_EXCLAM),
            SDLK_KP_MEMSTORE = KEY_TO_KEYCODE(KEY_KP_MEMSTORE),
            SDLK_KP_MEMRECALL = KEY_TO_KEYCODE(KEY_KP_MEMRECALL),
            SDLK_KP_MEMCLEAR = KEY_TO_KEYCODE(KEY_KP_MEMCLEAR),
            SDLK_KP_MEMADD = KEY_TO_KEYCODE(KEY_KP_MEMADD),
            SDLK_KP_MEMSUBTRACT =
                KEY_TO_KEYCODE(KEY_KP_MEMSUBTRACT),
            SDLK_KP_MEMMULTIPLY =
                KEY_TO_KEYCODE(KEY_KP_MEMMULTIPLY),
            SDLK_KP_MEMDIVIDE = KEY_TO_KEYCODE(KEY_KP_MEMDIVIDE),
            SDLK_KP_PLUSMINUS = KEY_TO_KEYCODE(KEY_KP_PLUSMINUS),
            SDLK_KP_CLEAR = KEY_TO_KEYCODE(KEY_KP_CLEAR),
            SDLK_KP_CLEARENTRY = KEY_TO_KEYCODE(KEY_KP_CLEARENTRY),
            SDLK_KP_BINARY = KEY_TO_KEYCODE(KEY_KP_BINARY),
            SDLK_KP_OCTAL = KEY_TO_KEYCODE(KEY_KP_OCTAL),
            SDLK_KP_DECIMAL = KEY_TO_KEYCODE(KEY_KP_DECIMAL),
            SDLK_KP_HEXADECIMAL =
                KEY_TO_KEYCODE(KEY_KP_HEXADECIMAL),
            SDLK_LCTRL = KEY_TO_KEYCODE(KEY_LCTRL),
            SDLK_LSHIFT = KEY_TO_KEYCODE(KEY_LSHIFT),
            SDLK_LALT = KEY_TO_KEYCODE(KEY_LALT),
            SDLK_LGUI = KEY_TO_KEYCODE(KEY_LGUI),
            SDLK_RCTRL = KEY_TO_KEYCODE(KEY_RCTRL),
            SDLK_RSHIFT = KEY_TO_KEYCODE(KEY_RSHIFT),
            SDLK_RALT = KEY_TO_KEYCODE(KEY_RALT),
            SDLK_RGUI = KEY_TO_KEYCODE(KEY_RGUI),
            SDLK_MODE = KEY_TO_KEYCODE(KEY_MODE),
            SDLK_AUDIONEXT = KEY_TO_KEYCODE(KEY_AUDIONEXT),
            SDLK_AUDIOPREV = KEY_TO_KEYCODE(KEY_AUDIOPREV),
            SDLK_AUDIOSTOP = KEY_TO_KEYCODE(KEY_AUDIOSTOP),
            SDLK_AUDIOPLAY = KEY_TO_KEYCODE(KEY_AUDIOPLAY),
            SDLK_AUDIOMUTE = KEY_TO_KEYCODE(KEY_AUDIOMUTE),
            SDLK_MEDIASELECT = KEY_TO_KEYCODE(KEY_MEDIASELECT),
            SDLK_WWW = KEY_TO_KEYCODE(KEY_WWW),
            SDLK_MAIL = KEY_TO_KEYCODE(KEY_MAIL),
            SDLK_CALCULATOR = KEY_TO_KEYCODE(KEY_CALCULATOR),
            SDLK_COMPUTER = KEY_TO_KEYCODE(KEY_COMPUTER),
            SDLK_AC_SEARCH = KEY_TO_KEYCODE(KEY_AC_SEARCH),
            SDLK_AC_HOME = KEY_TO_KEYCODE(KEY_AC_HOME),
            SDLK_AC_BACK = KEY_TO_KEYCODE(KEY_AC_BACK),
            SDLK_AC_FORWARD = KEY_TO_KEYCODE(KEY_AC_FORWARD),
            SDLK_AC_STOP = KEY_TO_KEYCODE(KEY_AC_STOP),
            SDLK_AC_REFRESH = KEY_TO_KEYCODE(KEY_AC_REFRESH),
            SDLK_AC_BOOKMARKS = KEY_TO_KEYCODE(KEY_AC_BOOKMARKS),
            SDLK_BRIGHTNESSDOWN =
                KEY_TO_KEYCODE(KEY_BRIGHTNESSDOWN),
            SDLK_BRIGHTNESSUP = KEY_TO_KEYCODE(KEY_BRIGHTNESSUP),
            SDLK_DISPLAYSWITCH = KEY_TO_KEYCODE(KEY_DISPLAYSWITCH),
            SDLK_KBDILLUMTOGGLE =
                KEY_TO_KEYCODE(KEY_KBDILLUMTOGGLE),
            SDLK_KBDILLUMDOWN = KEY_TO_KEYCODE(KEY_KBDILLUMDOWN),
            SDLK_KBDILLUMUP = KEY_TO_KEYCODE(KEY_KBDILLUMUP),
            SDLK_EJECT = KEY_TO_KEYCODE(KEY_EJECT),
            SDLK_SLEEP = KEY_TO_KEYCODE(KEY_SLEEP)
        };

        /// Point structure
        struct Point {
            i32 x, y;

            Point(): x(0), y(0) {}
            Point(const Point &point): x(point.x), y(point.y) {}
            explicit Point(i32 _x, i32 _y): x(_x), y(_y) {}
        };

        /// Size structure
        struct Size {
            i32 width, height;

            Size(): width(0), height(0) {}
            Size(const Size &size): width(size.width), height(size.height) {}
            explicit Size(i32 w, i32 h): width(w), height(h) {}
        };

        /// Color structure
        struct Color {
            u8 red, green, blue, alpha;

            Color(): red(0), green(0), blue(0), alpha(255) {}
            Color(const Color &color): red(color.red), green(color.green), blue(color.blue) {}
            explicit Color(u8 r, u8 g, u8 b, u8 a = 255): red(r), green(g), blue(b), alpha(a) {}
        };
    }
}
