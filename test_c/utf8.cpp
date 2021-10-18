#include <aula/core.hpp>

__main() {
    // (Windows only) _setmode(_fileno(stdout), _O_U16TEXT) により機種依存文字が出力されるようになっているか確認
    Aula::IO::Stdout->write(_U8("✅ Hello, 世界♥"));

    // Aula::IO::File::write の動作確認
    std::string dir = Aula::Path::getParentDirectory(Aula::Encoding::toUTF8(argv[0]));
    auto file = Aula::IO::File(dir + "/utf8.txt", "w");
    if (file.getState() == Aula::Object::FAILED) {
        Aula::IO::Stdout->write(file.getMessage());
        return 1;
    }
    file.write(_U8("✅ Hello, 世界❤\n⭕ UTF-8 エンコーディングされたファイル"));
    file.flush();

    // Aula::IO::File::read 系の動作確認
    file.open(dir + "/utf8.txt");
    Aula::IO::Stdout->write("readLine: " + file.readLine()); // => "✅ Hello, 世界❤"

    file.seek(0, Aula::IO::SeekFrom::HEAD);
    Aula::IO::Stdout->write("readString:");
    Aula::IO::Stdout->write(file.readString(file.getSize())); // => "✅ Hello, 世界❤\n⭕ UTF-8 エンコーディングされたファイル"

    // stdin の動作確認
    Aula::IO::Stdout->write(_U8("あなたの名前は？ > "), false);
    Aula::IO::Stdout->write(Aula::IO::Stdin->readString(256) + _U8(" ですね"));
    return 0;
}