﻿#pragma once

#define TEXTEDITINGEVENT_TEXT_SIZE (128)
#define TEXTINPUTEVENT_TEXT_SIZE (128)

namespace Aula {
    namespace SDL {
        /*** SDLイベントタイプ ***/
        enum EventID {
            FIRSTEVENT     = 0,     /**< Unused (do not remove) */

            /* Application events */
            QUIT           = 0x100, /**< User-requested quit */

            /* These application events have special meaning on iOS, see README-ios.txt for details */
            APP_TERMINATING,        /**< The application is being terminated by the OS
                                            Called on iOS in applicationWillTerminate()
                                            Called on Android in onDestroy()
                                    */
            APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
                                            Called on iOS in applicationDidReceiveMemoryWarning()
                                            Called on Android in onLowMemory()
                                    */
            APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                            Called on iOS in applicationWillResignActive()
                                            Called on Android in onPause()
                                    */
            APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
                                            Called on iOS in applicationDidEnterBackground()
                                            Called on Android in onPause()
                                    */
            APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                            Called on iOS in applicationWillEnterForeground()
                                            Called on Android in onResume()
                                    */
            APP_DIDENTERFOREGROUND, /**< The application is now interactive
                                            Called on iOS in applicationDidBecomeActive()
                                            Called on Android in onResume()
                                    */

            /* Window events */
            WINDOWEVENT    = 0x200, /**< Window state change */
            SYSWMEVENT,             /**< System specific event */

            /* Keyboard events */
            KEYDOWN        = 0x300, /**< Key pressed */
            KEYUP,                  /**< Key released */
            TEXTEDITING,            /**< Keyboard text editing (composition) */
            TEXTINPUT,              /**< Keyboard text input */

            /* Mouse events */
            MOUSEMOTION    = 0x400, /**< Mouse moved */
            MOUSEBUTTONDOWN,        /**< Mouse button pressed */
            MOUSEBUTTONUP,          /**< Mouse button released */
            MOUSEWHEEL,             /**< Mouse wheel motion */

            /* Joystick events */
            JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
            JOYBALLMOTION,          /**< Joystick trackball motion */
            JOYHATMOTION,           /**< Joystick hat position change */
            JOYBUTTONDOWN,          /**< Joystick button pressed */
            JOYBUTTONUP,            /**< Joystick button released */
            JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
            JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

            /* Game controller events */
            CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
            CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
            CONTROLLERBUTTONUP,            /**< Game controller button released */
            CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
            CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
            CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

            /* Touch events */
            FINGERDOWN      = 0x700,
            FINGERUP,
            FINGERMOTION,

            /* Gesture events */
            DOLLARGESTURE   = 0x800,
            DOLLARRECORD,
            MULTIGESTURE,

            /* Clipboard events */
            CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

            /* Drag and drop events */
            DROPFILE        = 0x1000, /**< The system requests a file open */

            /** Events ::USEREVENT through ::LASTEVENT are for your use,
             *  and should be allocated with RegisterEvents()
             */
            USEREVENT    = 0x8000,

            /**
             *  This last event is only for bounding internal arrays
             */
            LASTEVENT    = 0xFFFF
        };
        
        
        /*** WindowEventID ***/
        enum WindowEventID {
            WINDOWEVENT_NONE,           /**< Never used */
            WINDOWEVENT_SHOWN,          /**< Window has been shown */
            WINDOWEVENT_HIDDEN,         /**< Window has been hidden */
            WINDOWEVENT_EXPOSED,        /**< Window has been exposed and should be
                                                redrawn */
            WINDOWEVENT_MOVED,          /**< Window has been moved to data1, data2
                                         */
            WINDOWEVENT_RESIZED,        /**< Window has been resized to data1xdata2 */
            WINDOWEVENT_SIZE_CHANGED,   /**< The window size has changed, either as a result of an API call or through the system or user changing the window size. */
            WINDOWEVENT_MINIMIZED,      /**< Window has been minimized */
            WINDOWEVENT_MAXIMIZED,      /**< Window has been maximized */
            WINDOWEVENT_RESTORED,       /**< Window has been restored to normal size
                                                and position */
            WINDOWEVENT_ENTER,          /**< Window has gained mouse focus */
            WINDOWEVENT_LEAVE,          /**< Window has lost mouse focus */
            WINDOWEVENT_FOCUS_GAINED,   /**< Window has gained keyboard focus */
            WINDOWEVENT_FOCUS_LOST,     /**< Window has lost keyboard focus */
            WINDOWEVENT_CLOSE           /**< The window manager requests that the
                                                window be closed */
        };
        
        
        /**
         *  \brief Fields shared by every event
         */
        struct CommonEvent {
            unsigned long type;
            unsigned long timestamp;
        };
        
        /**
         *  \brief Window state change event data (event.window.*)
         */
        struct WindowEvent {
            unsigned long type;        /**< ::WINDOWEVENT */
            unsigned long timestamp;
            unsigned long windowID;    /**< The associated window */
            unsigned char event;       /**< ::WindowEventID */
            unsigned char padding1;
            unsigned char padding2;
            unsigned char padding3;
            long data1;       /**< event dependent data */
            long data2;       /**< event dependent data */
        };
        
        /**
         *  \brief The SDL keysym structure, used in key events.
         *
         *  \note  If you are looking for translated character input, see the ::TEXTINPUT event.
         */
        struct Keysym {
            long scancode;      /**< SDL physical key code - see ::Scancode for details */
            long sym;           /**< SDL virtual key code - see ::Keycode for details */
            unsigned short mod;                 /**< current key modifiers */
            unsigned long unused;
        };
        
        /**
         *  \brief Keyboard button event structure (event.key.*)
         */
        struct KeyboardEvent {
            unsigned long type;        /**< ::KEYDOWN or ::KEYUP */
            unsigned long timestamp;
            unsigned long windowID;    /**< The window with keyboard focus, if any */
            unsigned char state;       /**< ::PRESSED or ::RELEASED */
            unsigned char repeat;      /**< Non-zero if this is a key repeat */
            unsigned char padding2;
            unsigned char padding3;
            Keysym keysym;  /**< The key that was pressed or released */
        };
        
        /**
         *  \brief Keyboard text editing event structure (event.edit.*)
         */
        struct TextEditingEvent {
            unsigned long type;                                /**< ::TEXTEDITING */
            unsigned long timestamp;
            unsigned long windowID;                            /**< The window with keyboard focus, if any */
            char text[TEXTEDITINGEVENT_TEXT_SIZE];  /**< The editing text */
            long start;                             /**< The start cursor of selected editing text */
            long length;                            /**< The length of selected editing text */
        };
        
        /**
         *  \brief Keyboard text input event structure (event.text.*)
         */
        struct TextInputEvent {
            unsigned long type;                              /**< ::TEXTINPUT */
            unsigned long timestamp;
            unsigned long windowID;                          /**< The window with keyboard focus, if any */
            char text[TEXTINPUTEVENT_TEXT_SIZE];  /**< The input text */
        };
        
        /**
         *  \brief Mouse motion event structure (event.motion.*)
         */
        struct MouseMotionEvent {
            unsigned long type;        /**< ::MOUSEMOTION */
            unsigned long timestamp;
            unsigned long windowID;    /**< The window with mouse focus, if any */
            unsigned long which;       /**< The mouse instance id, or TOUCH_MOUSEID */
            unsigned long state;       /**< The current button state */
            long x;           /**< X coordinate, relative to window */
            long y;           /**< Y coordinate, relative to window */
            long xrel;        /**< The relative motion in the X direction */
            long yrel;        /**< The relative motion in the Y direction */
        };
        
        /**
         *  \brief Mouse button event structure (event.button.*)
         */
        struct MouseButtonEvent {
            unsigned long type;        /**< ::MOUSEBUTTONDOWN or ::MOUSEBUTTONUP */
            unsigned long timestamp;
            unsigned long windowID;    /**< The window with mouse focus, if any */
            unsigned long which;       /**< The mouse instance id, or TOUCH_MOUSEID */
            unsigned char button;      /**< The mouse button index */
            unsigned char state;       /**< ::PRESSED or ::RELEASED */
            unsigned char padding1;
            unsigned char padding2;
            long x;           /**< X coordinate, relative to window */
            long y;           /**< Y coordinate, relative to window */
        };
        
        /**
         *  \brief Mouse wheel event structure (event.wheel.*)
         */
        struct MouseWheelEvent {
            unsigned long type;        /**< ::MOUSEWHEEL */
            unsigned long timestamp;
            unsigned long windowID;    /**< The window with mouse focus, if any */
            unsigned long which;       /**< The mouse instance id, or TOUCH_MOUSEID */
            long x;           /**< The amount scrolled horizontally */
            long y;           /**< The amount scrolled vertically */
        };
        
        /**
         *  \brief Joystick axis motion event structure (event.jaxis.*)
         */
        struct JoyAxisEvent {
            unsigned long type;        /**< ::JOYAXISMOTION */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char axis;         /**< The joystick axis index */
            unsigned char padding1;
            unsigned char padding2;
            unsigned char padding3;
            short value;       /**< The axis value (range: -32768 to 32767) */
            unsigned short padding4;
        };
        
        /**
         *  \brief Joystick trackball motion event structure (event.jball.*)
         */
        struct JoyBallEvent {
            unsigned long type;        /**< ::JOYBALLMOTION */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char ball;         /**< The joystick trackball index */
            unsigned char padding1;
            unsigned char padding2;
            unsigned char padding3;
            short xrel;        /**< The relative motion in the X direction */
            short yrel;        /**< The relative motion in the Y direction */
        };
        
        /**
         *  \brief Joystick hat position change event structure (event.jhat.*)
         */
        struct JoyHatEvent {
            unsigned long type;        /**< ::JOYHATMOTION */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char hat;          /**< The joystick hat index */
            unsigned char value;        /**< The hat position value.
                                         *   \sa ::HAT_LEFTUP ::HAT_UP ::HAT_RIGHTUP
                                         *   \sa ::HAT_LEFT ::HAT_CENTERED ::HAT_RIGHT
                                         *   \sa ::HAT_LEFTDOWN ::HAT_DOWN ::HAT_RIGHTDOWN
                                         *
                                         *   Note that zero means the POV is centered.
                                         */
            unsigned char padding1;
            unsigned char padding2;
        };
        
        /**
         *  \brief Joystick button event structure (event.jbutton.*)
         */
        struct JoyButtonEvent {
            unsigned long type;        /**< ::JOYBUTTONDOWN or ::JOYBUTTONUP */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char button;       /**< The joystick button index */
            unsigned char state;        /**< ::PRESSED or ::RELEASED */
            unsigned char padding1;
            unsigned char padding2;
        };
        
        /**
         *  \brief Joystick device event structure (event.jdevice.*)
         */
        struct JoyDeviceEvent {
            unsigned long type;        /**< ::JOYDEVICEADDED or ::JOYDEVICEREMOVED */
            unsigned long timestamp;
            long which;       /**< The joystick device index for the ADDED event, instance id for the REMOVED event */
        };
        
        
        /**
         *  \brief Game controller axis motion event structure (event.caxis.*)
         */
        struct ControllerAxisEvent {
            unsigned long type;        /**< ::CONTROLLERAXISMOTION */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char axis;         /**< The controller axis (GameControllerAxis) */
            unsigned char padding1;
            unsigned char padding2;
            unsigned char padding3;
            short value;       /**< The axis value (range: -32768 to 32767) */
            unsigned short padding4;
        };
        
        
        /**
         *  \brief Game controller button event structure (event.cbutton.*)
         */
        struct ControllerButtonEvent {
            unsigned long type;        /**< ::CONTROLLERBUTTONDOWN or ::CONTROLLERBUTTONUP */
            unsigned long timestamp;
            long which; /**< The joystick instance id */
            unsigned char button;       /**< The controller button (GameControllerButton) */
            unsigned char state;        /**< ::PRESSED or ::RELEASED */
            unsigned char padding1;
            unsigned char padding2;
        };
        
        
        /**
         *  \brief Controller device event structure (event.cdevice.*)
         */
        struct ControllerDeviceEvent {
            unsigned long type;        /**< ::CONTROLLERDEVICEADDED, ::CONTROLLERDEVICEREMOVED, or ::CONTROLLERDEVICEREMAPPED */
            unsigned long timestamp;
            long which;       /**< The joystick device index for the ADDED event, instance id for the REMOVED or REMAPPED event */
        };
        
        
        /**
         *  \brief Touch finger event structure (event.tfinger.*)
         */
        struct TouchFingerEvent {
            unsigned long type;        /**< ::FINGERMOTION or ::FINGERDOWN or ::FINGERUP */
            unsigned long timestamp;
            long long touchId; /**< The touch device id */
            long long fingerId;
            float x;            /**< Normalized in the range 0...1 */
            float y;            /**< Normalized in the range 0...1 */
            float dx;           /**< Normalized in the range 0...1 */
            float dy;           /**< Normalized in the range 0...1 */
            float pressure;     /**< Normalized in the range 0...1 */
        };
        
        
        /**
         *  \brief Multiple Finger Gesture Event (event.mgesture.*)
         */
        struct MultiGestureEvent {
            unsigned long type;        /**< ::MULTIGESTURE */
            unsigned long timestamp;
            long long touchId; /**< The touch device index */
            float dTheta;
            float dDist;
            float x;
            float y;
            unsigned short numFingers;
            unsigned short padding;
        };
        
        
        /**
         * \brief Dollar Gesture Event (event.dgesture.*)
         */
        struct DollarGestureEvent {
            unsigned long type;        /**< ::DOLLARGESTURE */
            unsigned long timestamp;
            long long touchId; /**< The touch device id */
            long long gestureId;
            unsigned long numFingers;
            float error;
            float x;            /**< Normalized center of gesture */
            float y;            /**< Normalized center of gesture */
        };
        
        
        /**
         *  \brief An event used to request a file open by the system (event.drop.*)
         *         This event is disabled by default, you can enable it with EventState()
         *  \note If you enable this event, you must free the filename in the event.
         */
        struct DropEvent {
            unsigned long type;        /**< ::DROPFILE */
            unsigned long timestamp;
            char *file;         /**< The file name, which should be freed with free() */
        };
        
        
        /**
         *  \brief The "quit requested" event
         */
        struct QuitEvent {
            unsigned long type;        /**< ::QUIT */
            unsigned long timestamp;
        };
        
        /**
         *  \brief OS Specific event
         */
        struct OSEvent {
            unsigned long type;        /**< ::QUIT */
            unsigned long timestamp;
        };
        
        /**
         *  \brief A user-defined event type (event.user.*)
         */
        struct UserEvent {
            unsigned long type;        /**< ::USEREVENT through ::LASTEVENT-1 */
            unsigned long timestamp;
            unsigned long windowID;    /**< The associated window if any */
            long code;        /**< User defined event code */
            void *data1;        /**< User defined data pointer */
            void *data2;        /**< User defined data pointer */
        };
        
        /**
         *  \brief A video driver dependent system event (event.syswm.*)
         *         This event is disabled by default, you can enable it with EventState()
         *
         *  \note If you want to use this event, you should include syswm.h.
         */
        struct SysWMEvent {
            unsigned long type;        /**< ::SYSWMEVENT */
            unsigned long timestamp;
            void *msg;  /**< driver dependent data, defined in syswm.h */
        };
        
        /**
         *  \brief General event structure
         */
        union Event {
            unsigned long type;         /**< Event type, shared with all events */
            CommonEvent common;         /**< Common event data */
            WindowEvent window;         /**< Window event data */
            KeyboardEvent key;          /**< Keyboard event data */
            TextEditingEvent edit;      /**< Text editing event data */
            TextInputEvent text;        /**< Text input event data */
            MouseMotionEvent motion;    /**< Mouse motion event data */
            MouseButtonEvent button;    /**< Mouse button event data */
            MouseWheelEvent wheel;      /**< Mouse wheel event data */
            JoyAxisEvent jaxis;         /**< Joystick axis event data */
            JoyBallEvent jball;         /**< Joystick ball event data */
            JoyHatEvent jhat;           /**< Joystick hat event data */
            JoyButtonEvent jbutton;     /**< Joystick button event data */
            JoyDeviceEvent jdevice;     /**< Joystick device change event data */
            ControllerAxisEvent caxis;      /**< Game Controller axis event data */
            ControllerButtonEvent cbutton;  /**< Game Controller button event data */
            ControllerDeviceEvent cdevice;  /**< Game Controller device event data */
            QuitEvent quit;             /**< Quit request event data */
            UserEvent user;             /**< Custom event data */
            SysWMEvent syswm;           /**< System dependent window event data */
            TouchFingerEvent tfinger;   /**< Touch finger event data */
            MultiGestureEvent mgesture; /**< Gesture event data */
            DollarGestureEvent dgesture; /**< Gesture event data */
            DropEvent drop;             /**< Drag and drop event data */

            /* This is necessary for ABI compatibility between Visual C++ and GCC
               Visual C++ will respect the push pack pragma and use 52 bytes for
               this structure, and GCC will use the alignment of the largest datatype
               within the union, which is 8 bytes.

               So... we'll add padding to force the size to be 56 bytes for both.
            */
            unsigned char padding[56];
        };
    }
}
