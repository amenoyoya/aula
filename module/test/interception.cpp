#include "../../lib/core.hpp"
#include "../interception.hpp"
#include <iostream>

extern "C" {
    #include "../interception/library/interception.c"
}

/*
    @TODO Aula::Encoding::initialize() 関数を使うとやけに遅くなる
        正確には setlocale(LC_ALL, "") を使ったときに遅くなる
        
        setlocale(LC_ALL, "C") を指定して std::cout 等でコンソール出力すれば早い
*/
__main() {
    setlocale(LC_ALL, "C");

    /// Interception context 生成
    Aula::Interception::Context context;

    if (context.getState() == 0) {
        // Aula::IO::Stderr->write(context.getMessage());
        std::cout << context.getMessage() << std::endl;
        return 1;
    }

    /// プロセス優先度：高
    Aula::Interception::setCurrentProcessPriority(Aula::Interception::ProcessPriority::HIGH);

    /// 入力デバイス列挙
    auto devices = context.enumerateDevices();

    for (auto device = devices->begin(); device != devices->end(); ++device) {
        // Aula::IO::Stdout->write(
        //     Aula::String::toString(device->index) + ": " + device->hardwareId
        //     + (device->isKeyboard ? " (Keyboard)" : (device->isMouse ? " (Mouse)" : ""))
        // );
        std::cout << device->index << ": " + device->hardwareId << (device->isKeyboard ? " (Keyboard)" : (device->isMouse ? " (Mouse)" : "")) << std::endl;
    }

    // while (context.receive()) {
    //     InterceptionKeyStroke *keyStroke;
    //     InterceptionMouseStroke *mouseStroke;

    //     if (keyStroke = context.getCurrentKeyStroke()) {
    //         Aula::IO::Stdout->write(
    //             "Keyboard: " //+ //context.getHardwareId() +
    //             "\n\tcode: " + Aula::String::toString(keyStroke->code) +
    //             "\n\tstate: " + Aula::String::toString(keyStroke->state) +
    //             "\n\tinformation: " + Aula::String::toString(keyStroke->information)
    //         );
    //         if (keyStroke->code == 1) break; // Escape で終了
    //     } else if (mouseStroke = context.getCurrentMouseStroke()) {
    //         Aula::IO::Stdout->write(
    //             "Mouse: " //+ context.getHardwareId() +
    //             "\n\tstate: " + Aula::String::toString(mouseStroke->state) +
    //             "\n\tflags: " + Aula::String::toString(mouseStroke->flags) +
    //             "\n\trolling: " + Aula::String::toString(mouseStroke->rolling) +
    //             "\n\tx: " + Aula::String::toString(mouseStroke->x) +
    //             "\n\ty: " + Aula::String::toString(mouseStroke->y) +
    //             "\n\tinformation: " + Aula::String::toString(mouseStroke->information)
    //         );
    //     }
    //     context.pass(); // デバイス入力をそのまま送信してデフォルトの動作を行わせる
    //                     // ※ これを行わないとキーボード入力もマウス入力もできなくなってしまう
    // }

    InterceptionStroke stroke;
    InterceptionDevice device;
    auto ctx = context.getRaw();
    while (interception_receive(ctx, device = interception_wait(ctx), &stroke, 1) > 0) {
        if (interception_is_keyboard(device)) {
            InterceptionKeyStroke& s = *(InterceptionKeyStroke*)&stroke;
            std::cout << "Keyboard Input "
                << "ScanCode=" << s.code
                << " State=" << s.state << std::endl;
        }
        else if (interception_is_mouse(device)) {
            InterceptionMouseStroke& s = *(InterceptionMouseStroke*)&stroke;
            std::cout << "Mouse Input"
                << " State=" << s.state
                << " Rolling=" << s.rolling
                << " Flags=" << s.flags
                << " (x,y)=(" << s.x << "," << s.y << ")"
                << std::endl;
        }
        
        // 全てのデバイスの入力を通過させる
        interception_send(ctx, device, &stroke, 1);
        if (interception_is_keyboard(device)) { // Escapeで終了
            InterceptionKeyStroke& s = *(InterceptionKeyStroke*)&stroke;
            if (s.code == 1) break;
        }
    }
    return 0;
}