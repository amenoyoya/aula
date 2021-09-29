#pragma once

#include "../lib/core.hpp"
#include <vector>
#include <windows.h>

#define INTERCEPTION_STATIC
#include "interception/library/interception.h"

namespace Aula {
    namespace Interception {
        /// ProcessPriority enum
        enum ProcessPriority {
            IDLE = IDLE_PRIORITY_CLASS,
            BELOW_NORMAL = BELOW_NORMAL_PRIORITY_CLASS,
            NORMAL = NORMAL_PRIORITY_CLASS,
            ABOVE_NORMAL = ABOVE_NORMAL_PRIORITY_CLASS,
            HIGH = HIGH_PRIORITY_CLASS,
            REALTIME = REALTIME_PRIORITY_CLASS,
        };

        /// Set current process priority
        bool setCurrentProcessPriority(ProcessPriority priority) {
            return FALSE != SetPriorityClass(GetCurrentProcess(), priority);
        }

        /// InterceptionDevice wrapper struct
        struct Device {
            unsigned long index;
            std::string hardwareId;
            bool isKeyboard, isMouse;
        };

        /// InterceptionContext wrapper class
        class Context: public Object {
        public:
            Context(): Object(), context(0), device(0) {
                open();
            }
            ~Context() {
                close();
            }

            bool open() {
                close();
                if (0 == (context = interception_create_context())) {
                    _state = FAILED;
                    _message = "failed to create interception context";
                    return false;
                };
                _state = ACTIVE;
                return true;
            }

            void close() {
                if (context) {
                    interception_destroy_context(context);
                    context = 0;
                    device = 0;
                    memset(stroke, 0, sizeof(stroke));
                }
                _state = NONE;
                _message.clear();
            }

            /// Enumerate all deveices
            std::vector<Device> enumerateDevices() {
                std::vector<Device> devices;

                for (unsigned long i = 0; i < INTERCEPTION_MAX_KEYBOARD; ++i) {
                    unsigned long index = INTERCEPTION_KEYBOARD(i);
                    std::string hardwareId = getHardwareId(index);

                    if (hardwareId != "") devices.push_back({ index, hardwareId, true, false });
                }
                for (unsigned long i = 0; i < INTERCEPTION_MAX_MOUSE; ++i) {
                    unsigned long index = INTERCEPTION_MOUSE(i);
                    std::string hardwareId = getHardwareId(index);

                    if (hardwareId != "") devices.push_back({ index, hardwareId, false, true });
                }
                return std::move(devices);
            }

            /// Set keyboard input filter
            void setKeyboardFilter(u32 filter) {
                if (context) interception_set_filter(context, interception_is_keyboard, (InterceptionFilter)filter);
            }

            /// Set mouse input filter
            void setMouseFilter(u32 filter) {
                if (context) interception_set_filter(context, interception_is_mouse, (InterceptionFilter)filter);
            }

            /// Get device and stroke of current input
            // Use for while-loop
            bool recieve() {
                return context? interception_receive(context, device = interception_wait(context), &stroke, 1) > 0: false;
            }

            /// Send current input as default input
            void pass() {
                if (context && device) interception_send(context, device, &stroke, 1);
            }

            /// Get current input as key stroke
            // nullptr will be return if the current input is not a key input
            InterceptionKeyStroke *getCurrentKeyStroke() const {
                if (!device || !interception_is_keyboard(device)) return nullptr;
                return (InterceptionKeyStroke *)&stroke;
            }

            /// Get current input as key stroke
            // nullptr will be return if the current input is not a key input
            InterceptionMouseStroke *getCurrentMouseStroke() const {
                if (!device || !interception_is_mouse(device)) return nullptr;
                return (InterceptionMouseStroke *)&stroke;
            }

            /// Get current device index
            unsigned long getCurrentDeviceIndex() const {
                return context ? (unsigned long)device : 0;
            }

            /// Get input device hardware_id
            // @param unsigned long deviceIndex: if unsigned(-1) is designated, get the current device hardware_id
            std::string getHardwareId(unsigned long deviceIndex = (unsigned long)(-1)) const {
                wchar_t hardwareId[512];
                if (interception_get_hardware_id(
                    context,
                    deviceIndex == (unsigned long)(-1) ? device : (InterceptionDevice)deviceIndex,
                    (void *)hardwareId,
                    sizeof(hardwareId)
                ) == 0) return "";
                return std::move(Encoding::toUTF8(hardwareId));
            }
        private:
            InterceptionContext context;
            InterceptionDevice  device;
            InterceptionStroke  stroke;
        };
    }
}