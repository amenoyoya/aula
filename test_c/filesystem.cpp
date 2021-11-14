#define _USE_AULA_CORE
#include <aula/core.hpp>
#include <cassert>

inline std::string readfile(const std::string &filename) {
    auto fp = aula::fs::file_open(filename, "rb");
    assert(fp != nullptr);
    auto data = aula::fs::file_read(fp.get(), aula::fs::file_size(fp.get()));
    return data == nullptr ? "" : aula::io::binary_tostr(data.get());
}

inline bool writefile(const std::string &filename, const std::string &data) {
    auto fp = aula::fs::file_open(filename, "wb");
    assert(fp != nullptr);
    return data.size() == aula::fs::file_write(fp.get(), aula::io::binary_openstr(data.c_str()).get());
}

__main() {
    assert(aula::os::setcwd(aula::path::parentdir(args[0])));
    
    std::string cwd = std::move(aula::os::getcwd());
    assert(aula::path::basename(cwd) == "test_c");
    _fputs(stdout, "current dir: " + cwd);

    assert(nullptr == aula::fs::file_open("!!!this file not exist"));
    
    assert(writefile(_U8("✅utf8dir/⭕utf8file.txt"), _U8("✨⚡")));
    assert(writefile(_U8("✅utf8dir/❌u8subdir/subdir.file.txt"), _U8("⭐❗❓")));

    std::string readcontent = readfile(_U8("✅utf8dir/⭕utf8file.txt"));
    assert(readcontent == _U8("✨⚡"));
    _fputs(stdout, _U8("✅utf8dir/⭕utf8file.txt: ") + readcontent);
    
    assert(false == aula::fs::copydir("!!!this directory not exist", _U8("⚡copied")));
    assert(aula::fs::copydir(_U8("✅utf8dir"), _U8("⚡copied")));

    readcontent = readfile(_U8("⚡copied/⭕utf8file.txt"));
    assert(readfile(_U8("✅utf8dir/⭕utf8file.txt")) == readcontent);
    _fputs(stdout, _U8("⚡copied/⭕utf8file.txt: ") + readcontent);

    readcontent = readfile(_U8("⚡copied/❌u8subdir/subdir.file.txt"));
    assert(readfile(_U8("✅utf8dir/❌u8subdir/subdir.file.txt")) == readcontent);
    _fputs(stdout, _U8("⚡copied/❌u8subdir/subdir.file.txt: ") + readcontent);

    assert(aula::fs::rmdir(_U8("⚡copied")));
    assert(aula::fs::rmdir(_U8("✅utf8dir")));

    _fputs(stdout, "aula filesystem all OK");
    return 0;
}