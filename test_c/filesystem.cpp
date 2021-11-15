#define _USE_AULA_CORE
#define _USE_AULA_ZIP
#include <aula/zip.hpp>
#include <cassert>

inline std::string readfile(const std::string &filename) {
    auto fp = aula::fs::file_open(filename, "rb");
    assert(fp != nullptr);
    auto data = aula::fs::file_read(fp.get(), fp->size);
    return data == nullptr ? "" : aula::io::binary_tostr(data.get());
}

inline bool writefile(const std::string &filename, const std::string &data) {
    auto fp = aula::fs::file_open(filename, "wb");
    assert(fp != nullptr);
    return data.size() == aula::fs::file_write(fp.get(), aula::io::binary_openstr(data.c_str()).get());
}

__main() {
    /// os.setcwd, os.getcwd
    assert(aula::os::setcwd(aula::path::parentdir(args[0])));
    
    std::string cwd = std::move(aula::os::getcwd());
    assert(aula::path::basename(cwd) == "test_c");
    _fputs(stdout, "current dir: " + cwd);

    /// file status
    auto stat = aula::path::stat(args[0]);
    assert(stat);
    _fputs(stdout, args[0] + " status:");
    _fprintf(stdout, "\tdevice id: %d\n", stat->device_id);
    _fprintf(stdout, "\tinode: %d\n", stat->inode);
    _fprintf(stdout, "\taccess mode: %d\n", stat->access_mode);
    _fprintf(stdout, "\tlinks count: %d\n", stat->nlinks);
    _fprintf(stdout, "\towner uid: %d\n", stat->user_id);
    _fprintf(stdout, "\towner gid: %d\n", stat->group_id);
    _fprintf(stdout, "\tspecial device id: %d\n", stat->special_device_id);
    _fprintf(stdout, "\tsize: %d\n", stat->size);
    _fprintf(stdout, "\tlast accessed: %d\n", stat->last_accessed_seconds);
    _fprintf(stdout, "\tlast modified: %d\n", stat->last_modified_seconds);
    _fprintf(stdout, "\tlast changed: %d\n", stat->last_changed_seconds);

    /// case: file not found
    assert(nullptr == aula::fs::file_open("!!!this file not exist"));

    /// write UTF-8 string to file
    assert(writefile(_U8("✅utf8dir/⭕utf8file.txt"), _U8("✨⚡")));
    assert(writefile(_U8("✅utf8dir/❌u8subdir/subdir.file.txt"), _U8("⭐❗❓")));

    /// test: read data == written data
    std::string readcontent = readfile(_U8("✅utf8dir/⭕utf8file.txt"));
    assert(readcontent == _U8("✨⚡"));
    _fputs(stdout, _U8("✅utf8dir/⭕utf8file.txt: ") + readcontent);

    /// fs.copydir
    assert(false == aula::fs::copydir("!!!this directory not exist", _U8("⚡copied")));
    assert(aula::fs::copydir(_U8("✅utf8dir"), _U8("⚡copied")));

    readcontent = readfile(_U8("⚡copied/⭕utf8file.txt"));
    assert(readfile(_U8("✅utf8dir/⭕utf8file.txt")) == readcontent);
    _fputs(stdout, _U8("⚡copied/⭕utf8file.txt: ") + readcontent);

    readcontent = readfile(_U8("⚡copied/❌u8subdir/subdir.file.txt"));
    assert(readfile(_U8("✅utf8dir/❌u8subdir/subdir.file.txt")) == readcontent);
    _fputs(stdout, _U8("⚡copied/❌u8subdir/subdir.file.txt: ") + readcontent);

    /// zip.zip_compress
    assert(aula::zip::zip_compress(
        _U8("⚡copied"), _U8("❗archive.zip"), 9, "password", "w", _U8("✅this archive is created by zip_compress")
    ));

    /// test: zip global comment
    auto unz = aula::zip::unz_open(_U8("❗archive.zip"));
    assert(unz != nullptr);
    assert(unz->comment == _U8("✅this archive is created by zip_compress"));
    _fputs(stdout, _U8("❗archive.zip global comment: ") + unz->comment);
    aula::zip::unz_close(unz);

    /// zip.unz_extract
    assert(false == aula::zip::unz_extract(_U8("❗archive.zip"), _U8("⭕extracted"), "wrong password"));
    assert(aula::zip::unz_extract(_U8("❗archive.zip"), _U8("⭕extracted"), "password"));

    readcontent = readfile(_U8("⭕extracted/⭕utf8file.txt"));
    assert(readfile(_U8("✅utf8dir/⭕utf8file.txt")) == readcontent);
    _fputs(stdout, _U8("⭕extracted/⭕utf8file.txt: ") + readcontent);

    readcontent = readfile(_U8("⭕extracted/❌u8subdir/subdir.file.txt"));
    assert(readfile(_U8("✅utf8dir/❌u8subdir/subdir.file.txt")) == readcontent);
    _fputs(stdout, _U8("⭕extracted/❌u8subdir/subdir.file.txt: ") + readcontent);

    /// clean up
    assert(aula::fs::rmdir(_U8("⚡copied")));
    assert(aula::fs::rmdir(_U8("✅utf8dir")));
    assert(aula::fs::rmfile(_U8("❗archive.zip")));
    assert(aula::fs::rmdir(_U8("⭕extracted")));

    _fputs(stdout, "aula filesystem all OK");
    return 0;
}