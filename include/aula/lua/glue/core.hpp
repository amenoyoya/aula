#pragma once

#include "../../core.hpp"

namespace aula {
    namespace core {
        template<typename State>
        void openlib(State &lua) {
            /*** string library ***/
            auto string = lua["string"].get_or_create<sol::table>();
            string.set_function("u8towcs", aula::string::u8towcs);
            string.set_function("wcstou8", aula::string::wcstou8);

            /*** io library ***/
            auto io = lua["io"].get_or_create<sol::table>();
            io.set_function("initlocale", aula::io::initlocale);
            io.set_function("print", [](const std::string &str) { return aula::io::putstr(stdout, str); });
            io.set_function("eprint", [](const std::string &str) { return aula::io::putstr(stderr, str); });
            io.set_function("getstr", sol::overload(
                [](size_t size) { return aula::io::getstr(stdin, size); },
                []() { return aula::io::getstr(stdin); }
            ));
            io.new_enum("seekfrom",
                "head", aula::io::seekfrom::head,
                "cur", aula::io::seekfrom::cur,
                "tail", aula::io::seekfrom::tail
            );
            io.new_usertype<aula::io::binary_t>("binary_t",
                "data", &aula::io::binary_t::data,
                "head", &aula::io::binary_t::head,
                "iter", &aula::io::binary_t::iter,
                "size", &aula::io::binary_t::size,
                "close", aula::io::binary_close,
                "resize", aula::io::binary_resize,
                "reserve", aula::io::binary_reserve,
                "push", aula::io::binary_push,
                "pushint", sol::overload(
                    [](aula::io::binary_t *self, int data, size_t size) { return aula::io::binary_pushint(self, data, size); },
                    [](aula::io::binary_t *self, int data) { return aula::io::binary_pushint(self, data); }
                ),
                "pushstr", sol::overload(
                    [](aula::io::binary_t *self, const std::string &data, size_t size) { return aula::io::binary_pushstr(self, data, size); },
                    [](aula::io::binary_t *self, const std::string &data) { return aula::io::binary_pushstr(self, data); }
                ),
                "pushrune", aula::io::binary_pushrune,
                "pushnum", sol::overload(
                    [](aula::io::binary_t *self, double data, unsigned short precision) { return aula::io::binary_pushnum(self, data, precision); },
                    [](aula::io::binary_t *self, double data) { return aula::io::binary_pushnum(self, data); }
                ),
                "seek", sol::overload(
                    [](aula::io::binary_t *self, long pos, aula::io::seekfrom from) { return aula::io::binary_seek(self, pos, from); },
                    [](aula::io::binary_t *self, long pos) { return aula::io::binary_seek(self, pos); }
                ),
                "geti32", aula::io::binary_geti32,
                "getu32", aula::io::binary_getu32,
                "geti16", aula::io::binary_geti16,
                "getu16", aula::io::binary_getu16,
                "geti8", aula::io::binary_geti8,
                "getu8", aula::io::binary_getu8,
                "getstr", aula::io::binary_getstr,
                "getrune", aula::io::binary_getrune,
                "getnum", aula::io::binary_getnum,
                "crc32", sol::overload(
                    [](aula::io::binary_t *self, unsigned long start) { return aula::io::binary_crc32(self, start); },
                    [](aula::io::binary_t *self) { return aula::io::binary_crc32(self); }
                ),
                "encrypt", sol::overload(
                    [](aula::io::binary_t *self, const std::string &key, size_t keysize) { return aula::io::binary_encrypt(self, key, keysize); },
                    [](aula::io::binary_t *self, const std::string &key) { return aula::io::binary_encrypt(self, key); }
                ),
                "decrypt", sol::overload(
                    [](aula::io::binary_t *self, const std::string &key, size_t keysize) { return aula::io::binary_decrypt(self, key, keysize); },
                    [](aula::io::binary_t *self, const std::string &key) { return aula::io::binary_decrypt(self, key); }
                )
            );
            // aula::io::binary_t::tostr
            lua.safe_script(R"(
                io.binary_t.tostr = function(self, from)
                    from = from or 0
                    return ffi.string(ffi.cast("const char*", self.head + from), self.size - from)
                end
            )", "@stdlib://io");
            io.set_function("binary_new", aula::io::binary_new);
            io.set_function("binary_newstr", sol::overload(
                [] (const char *data, size_t size) { return aula::io::binary_newstr(data, size); },
                [] (const char *data) { return aula::io::binary_newstr(data); }
            ));
            io.set_function("binary_open", aula::io::binary_open);
            io.set_function("binary_openstr", sol::overload(
                [] (const char *data, size_t size) { return aula::io::binary_openstr(data, size); },
                [] (const char *data) { return aula::io::binary_openstr(data); }
            ));

            /*** os library ***/
            auto os = lua["os"].get_or_create<sol::table>();
            os.set_function("execute", aula::os::execute);
            os.set_function("sleep", aula::os::sleep);
            os.set_function("systime", aula::os::systime);
            os.set_function("setenv", aula::os::setenv);
            os.set_function("getenv", aula::os::getenv);
            os.set_function("setcwd", aula::os::setcwd);
            os.set_function("getcwd", aula::os::getcwd);

            /*** path library ***/
            auto fs = lua["fs"].get_or_create<sol::table>();
            auto path = fs["path"].get_or_create<sol::table>();
            path.new_usertype<aula::path::stat_t>("stat_t",
                "device_id", &aula::path::stat_t::device_id,
                "inode", &aula::path::stat_t::inode,
                "access_mode", &aula::path::stat_t::access_mode,
                "nlinks", &aula::path::stat_t::nlinks,
                "user_id", &aula::path::stat_t::user_id,
                "group_id", &aula::path::stat_t::group_id,
                "special_device_id", &aula::path::stat_t::special_device_id,
                "size", &aula::path::stat_t::size,
                "last_accessed_seconds", &aula::path::stat_t::last_accessed_seconds,
                "last_modified_seconds", &aula::path::stat_t::last_modified_seconds,
                "last_changed_seconds", &aula::path::stat_t::last_changed_seconds
            );
            path.set_function("basename", aula::path::basename);
            path.set_function("stem", aula::path::stem);
            path.set_function("ext", aula::path::ext);
            path.set_function("parentdir", sol::overload(
                [](const std::string &path, bool isFullPathRequired) { return aula::path::parentdir(path, isFullPathRequired); },
                [](const std::string &path) { return aula::path::parentdir(path); }
            ));
            path.set_function("isfile", aula::path::isfile);
            path.set_function("isdir", aula::path::isdir);
            path.set_function("complete", aula::path::complete);
            path.set_function("stat", aula::path::stat);
            path.set_function("append_slash", aula::path::append_slash);
            path.set_function("remove_slash", aula::path::remove_slash);

            /*** filesystem library ***/
            fs.set_function("copyfile", sol::overload(
                [](const std::string &src, const std::string &dest, bool isOverwrite) { return aula::fs::copyfile(src, dest, isOverwrite); },
                [](const std::string &src, const std::string &dest) { return aula::fs::copyfile(src, dest); }
            ));
            fs.set_function("rmfile", aula::fs::rmfile);
            fs.set_function("mkdir", aula::fs::mkdir);
            fs.set_function("copydir", aula::fs::copydir);
            fs.set_function("rmdir", aula::fs::rmdir);
            fs.set_function("rename", sol::overload(
                [](const std::string &src, const std::string &dest, bool isOverwrite) { return aula::fs::rename(src, dest, isOverwrite); },
                [](const std::string &src, const std::string &dest) { return aula::fs::rename(src, dest); }
            ));
            fs.new_usertype<aula::fs::file_t>("file_t",
                "handler", &aula::fs::file_t::handler,
                "size", &aula::fs::file_t::size,
                "close", aula::fs::file_close,
                "readchar", aula::fs::file_readchar,
                "readline", aula::fs::file_readline,
                "read", aula::fs::file_read,
                "writechar", aula::fs::file_writechar,
                "write", aula::fs::file_write,
                "seek", sol::overload(
                    [](aula::fs::file_t *self, long offset, aula::io::seekfrom from) { return aula::fs::file_seek(self, offset, from); },
                    [](aula::fs::file_t *self, long offset) { return aula::fs::file_seek(self, offset); }
                ),
                "pos", aula::fs::file_pos,
                "flush", aula::fs::file_flush
            );
            fs.set_function("file_open", sol::overload(
                [](const std::string &filename, const std::string &mode) { return aula::fs::file_open(filename, mode); },
                [](const std::string &filename) { return aula::fs::file_open(filename); }
            ));
            fs.set_function("pipe_open", sol::overload(
                [](const std::string &procname, const std::string &mode) { return aula::fs::pipe_open(procname, mode); },
                [](const std::string &procname) { return aula::fs::pipe_open(procname); }
            ));
            fs.set_function("readfile", aula::fs::readfile);
            fs.set_function("writefile", aula::fs::writefile);
            fs.new_usertype<aula::fs::dirent_t>("dirent_t",
                "handler", &aula::fs::dirent_t::handler,
                "dir", &aula::fs::dirent_t::dir,
                "current_name", &aula::fs::dirent_t::current_name,
                "current_path", &aula::fs::dirent_t::current_path,
                "current_isfile", &aula::fs::dirent_t::current_isfile,
                "current_isdir", &aula::fs::dirent_t::current_isdir,
                "close", aula::fs::dir_close,
                "next", aula::fs::dir_next
            );
            fs.set_function("dir_open", aula::fs::dir_open);
        }
    }
}