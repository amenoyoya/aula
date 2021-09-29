#include "../interception.hpp"
#include <iostream>

extern "C" {
    #include "../interception/library/interception.c"
}

/*
    @MEMO Aula::Encoding::initialize() + Aula::IO::Stdout->write(...) は遅い
        ただしそれは UTF-8 => wstring 変換処理の分やや遅いだけで
        std::cout を使っても速度的にそこまで変わらなそうなので気にしなくても良さそう
        - 比較: ./interception_test.cpp
*/
__main() {
    /// Interception context 生成
    Aula::Interception::Context context;

    if (context.getState() == 0) {
        Aula::IO::Stderr->write(context.getMessage());
        return 1;
    }

    /// プロセス優先度：高
    Aula::Interception::setCurrentProcessPriority(Aula::Interception::ProcessPriority::HIGH);

    /// 入力デバイス列挙
    auto devices = context.enumerateDevices();

    for (auto device = devices.begin(); device != devices.end(); ++device) {
        Aula::IO::Stdout->write(
            Aula::String::toString(device->index) + ": " + device->hardwareId
            + (device->isKeyboard ? " (Keyboard)" : (device->isMouse ? " (Mouse)" : ""))
        );
    }

    /// 入力フィルタ設定
    context.setKeyboardFilter(INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP | INTERCEPTION_KEY_E0 | INTERCEPTION_KEY_E1);
    context.setMouseFilter(INTERCEPTION_FILTER_MOUSE_ALL - INTERCEPTION_FILTER_MOUSE_MOVE);

    while (context.recieve()) {
        InterceptionKeyStroke *keyStroke;
        InterceptionMouseStroke *mouseStroke;

        if (keyStroke = context.getCurrentKeyStroke()) {
            Aula::IO::Stdout->write(
                "Keyboard: " + context.getHardwareId() +
                "\n\tcode: " + Aula::String::toString(keyStroke->code) +
                "\n\tstate: " + Aula::String::toString(keyStroke->state) +
                "\n\tinformation: " + Aula::String::toString(keyStroke->information)
            );
            if (keyStroke->code == 1) break; // Escape で終了
        } else if (mouseStroke = context.getCurrentMouseStroke()) {
            Aula::IO::Stdout->write(
                "Mouse: " + context.getHardwareId() +
                "\n\tstate: " + Aula::String::toString(mouseStroke->state) +
                "\n\tflags: " + Aula::String::toString(mouseStroke->flags) +
                "\n\trolling: " + Aula::String::toString(mouseStroke->rolling) +
                "\n\tx: " + Aula::String::toString(mouseStroke->x) +
                "\n\ty: " + Aula::String::toString(mouseStroke->y) +
                "\n\tinformation: " + Aula::String::toString(mouseStroke->information)
            );
        }
        context.pass(); // デバイス入力をそのまま送信してデフォルトの動作を行わせる
                        // ※ これを行わないとキーボード入力もマウス入力もできなくなってしまう
    }
    return 0;
}