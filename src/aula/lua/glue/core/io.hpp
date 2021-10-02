#pragma once

#include <aula/core/io/filesystem.hpp>

namespace Aula {
    inline void open_io_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto io = aula["IO"].get_or_create<sol::table>();

        io.new_enum("SeekFrom",
            "HEAD", IO::SeekFrom::HEAD,
            "CURRENT", IO::SeekFrom::CURRENT,
            "END", IO::SeekFrom::END
        );
        
        io.new_usertype<IO::Binary>(
            "Binary",
            sol::constructors<
                IO::Binary(),
                IO::Binary(void *),
                IO::Binary(u32),
                IO::Binary(const void *, u32),
                IO::Binary(const std::string &, u32)
            >(),
            "getState", &IO::Binary::getState,
            "getMessage", &IO::Binary::getMessage,
            "set", &IO::Binary::set,
            "allocate", &IO::Binary::allocate,
            "resize", &IO::Binary::resize,
            "release", &IO::Binary::release,
            "reserve", &IO::Binary::reserve,
            "getPointer", sol::overload(
                [](IO::Binary *self, u32 head) { return self->getPointer(head); },
                [](IO::Binary *self) { return self->getPointer(); }
            ),
            "toString", &IO::Binary::toString,
            "getSize", &IO::Binary::getSize,
            "getPosition", &IO::Binary::getPosition,
            "push", &IO::Binary::push,
            "pushValue", sol::overload(
                [](IO::Binary *self, i32 data, u8 size) { return self->pushValue(data, size); },
                [](IO::Binary *self, i32 data) { return self->pushValue(data); }
            ),
            "pushNumber", sol::overload(
                [](IO::Binary *self, double data, u8 precision) { return self->pushNumber(data, precision); },
                [](IO::Binary *self, double data) { return self->pushNumber(data); }
            ),
            "pushString", sol::overload(
                [](IO::Binary *self, const std::string &data, u32 size) { return self->pushString(data, size); },
                [](IO::Binary *self, const std::string &data) { return self->pushString(data); }
            ),
            "pushStringData", &IO::Binary::pushStringData,
            "getI32", &IO::Binary::getI32,
            "getU32", &IO::Binary::getU32,
            "getI16", &IO::Binary::getI16,
            "getU16", &IO::Binary::getU16,
            "getI8", &IO::Binary::getI8,
            "getU8", &IO::Binary::getU8,
            "getNumber", &IO::Binary::getNumber,
            "getString", &IO::Binary::getString,
            "getStringData", &IO::Binary::getStringData,
            "get", &IO::Binary::get,
            "seek", sol::overload(
                [](IO::Binary *self, i32 mov, u8 mode) { return self->seek(mov, mode); },
                [](IO::Binary *self, i32 mov) { return self->seek(mov); }
            ),
            "encode", sol::overload(
                [](IO::Binary *self, const std::string &key, u32 keysize) { return self->encode(key, keysize); },
                [](IO::Binary *self, const std::string &key) { return self->encode(key); }
            ),
            "decode", sol::overload(
                [](IO::Binary *self, const std::string &key, u32 keysize) { return self->decode(key, keysize); },
                [](IO::Binary *self, const std::string &key) { return self->decode(key); }
            ),
            "getCRC32", sol::overload(
                [](const IO::Binary &buffer, u32 bufferlen, u32 crc32_start) { return IO::Binary::getCRC32(buffer, bufferlen, crc32_start); },
                [](const IO::Binary &buffer, u32 bufferlen) { return IO::Binary::getCRC32(buffer, bufferlen); }
            )
        );
        io["Binary"].get_or_create<sol::table>().new_enum("Mode",
            "CONTROL", IO::Binary::Mode::CONTROL,
            "ALLOCATE", IO::Binary::Mode::ALLOCATE
        );

        io.new_usertype<IO::File>(
            "File",
            sol::constructors<
                IO::File(),
                IO::File(const std::string &, const std::string &),
                IO::File(const std::string &)
            >(),
            "getState", &IO::File::getState,
            "getMessage", &IO::File::getMessage,
            "open", sol::overload(
                [](IO::File *self, const std::string &path, const std::string &mode) { return self->open(path, mode); },
                [](IO::File *self, const std::string &path) { return self->open(path); }
            ),
            "close", &IO::File::close,
            "getSize", &IO::File::getSize,
            "readLine", &IO::File::readLine,
            "readString", &IO::File::readString,
            "readChar", &IO::File::readChar,
            "writeChar", &IO::File::writeChar,
            "read", sol::overload(
                [](IO::File *self, u32 n, u32 size) { return self->read(n, size); },
                [](IO::File *self, u32 n) { return self->read(n); }
            ),
            "write", sol::overload(
                [](IO::File *self, const std::string &text, bool appendLF) { return self->write(text, appendLF); },
                [](IO::File *self, const std::string &text) { return self->write(text); },
                [](IO::File *self, const IO::Binary &data, u32 n, u32 size) { return self->write(data, n, size); },
                [](IO::File *self, const IO::Binary &data, u32 n) { return self->write(data); },
                [](IO::File *self, const IO::Binary &data) { return self->write(data); }
            ),
            "seek", &IO::File::seek,
            "getPosition", &IO::File::getPosition,
            "flush", &IO::File::flush
        );

        io["readFile"].set_function(sol::overload(
            [](const std::string &filename, u32 size) { return IO::readFile(filename, size); },
            [](const std::string &filename) { return IO::readFile(filename); }
        ));
        io["writeFile"].set_function(sol::overload(
            [](const std::string &filename, const IO::Binary &data, u32 size) { return IO::writeFile(filename, data, size); },
            [](const std::string &filename, const IO::Binary &data) { return IO::writeFile(filename, data); }
        ));

        io["Stdout"] = IO::Stdout.get();
        io["Stderr"] = IO::Stderr.get();
        io["Stdin"] = IO::Stdin.get();

        io.new_usertype<IO::FileEnumerator>(
            "FileEnumerator",
            sol::constructors<IO::FileEnumerator(), IO::FileEnumerator(const std::string &)>(),
            "getState", &IO::FileEnumerator::getState,
            "getMessage", &IO::FileEnumerator::getMessage,
            "open", &IO::FileEnumerator::open,
            "close", &IO::FileEnumerator::close,
            "toNext", &IO::FileEnumerator::toNext,
            "getName", &IO::FileEnumerator::getName,
            "getPath", &IO::FileEnumerator::getPath
        );

        io.new_enum("EnumFileOption",
            "DIR", IO::EnumFileOption::DIR,
            "FILE", IO::EnumFileOption::FILE,
            "ALL", IO::EnumFileOption::ALL
        );
        io.new_usertype<IO::FileInfo>("FileInfo",
            "path", &IO::FileInfo::path,
            "isFile", &IO::FileInfo::isFile,
            "isDirectory", &IO::FileInfo::isDirectory
        );
        io["enumerateFiles"].set_function(sol::overload(
            [](const std::string &dir, i32 nest, IO::EnumFileOption opt) { return IO::enumerateFiles(dir, nest, opt); },
            [](const std::string &dir, i32 nest) { return IO::enumerateFiles(dir, nest); },
            [](const std::string &dir) { return IO::enumerateFiles(dir); }
        ));

        io.set_function("copyFile", sol::overload(
            [](const std::string &src, const std::string &dest, bool overwrite) { return IO::copyFile(src, dest, overwrite); },
            [](const std::string &src, const std::string &dest) { return IO::copyFile(src, dest); }
        ));
        io.set_function("removeFile", IO::removeFile);
        io.set_function("moveFile", sol::overload(
            [](const std::string &src, const std::string &dest, bool overwrite) { return IO::moveFile(src, dest, overwrite); },
            [](const std::string &src, const std::string &dest) { return IO::moveFile(src, dest); }
        ));
        io.set_function("createDirectory", IO::createDirectory);
        io.set_function("copyDirectory", IO::copyDirectory);
        io.set_function("removeDirectory", IO::removeDirectory);
        io.set_function("moveDirectory", IO::moveDirectory);
    }
}