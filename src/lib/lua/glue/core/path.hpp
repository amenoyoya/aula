#pragma once

#include <aula/core/path/base.hpp>

namespace Aula {
    inline void open_path_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto path = aula["Path"].get_or_create<sol::table>();

        path.set_function("getBaseName", Path::getBaseName);
        path.set_function("getBaseStem", Path::getBaseStem);
        path.set_function("getExtension", Path::getExtension);
        path.set_function("convert", Path::convert);
        path.set_function("isSame", sol::overload(
            [](const std::string &path1, const std::string &path2, u32 len) { return Path::isSame(path1, path2, len); },
            [](const std::string &path1, const std::string &path2) { return Path::isSame(path1, path2); }
        ));
        path.set_function("getParentDirectory", sol::overload(
            [](const std::string &path, bool real) { return Path::getParentDirectory(path, real); },
            [](const std::string &path) { return Path::getParentDirectory(path); }
        ));
        path.set_function("isFile", Path::isFile);
        path.set_function("isDirectory", Path::isDirectory);
        path.set_function("complete", Path::complete);
        path.set_function("appendSlash", Path::appendSlash);
        path.set_function("removeSlash", Path::removeSlash);

        path.new_usertype<Path::FileStatus>("FileStatus",
            "deviceId", &Path::FileStatus::deviceId,
            "inode", &Path::FileStatus::inode,
            "accessMode", &Path::FileStatus::accessMode,
            "nLinks", &Path::FileStatus::nLinks,
            "userId", &Path::FileStatus::userId,
            "groupId", &Path::FileStatus::groupId,
            "specialDeviceId", &Path::FileStatus::specialDeviceId,
            "size", &Path::FileStatus::size,
            "lastAccessedSeconds", &Path::FileStatus::lastAccessedSeconds,
            "lastModifiedSeconds", &Path::FileStatus::lastModifiedSeconds,
            "lastChangedSeconds", &Path::FileStatus::lastChangedSeconds
        );
        path.set_function("getFileStatus", Path::getFileStatus);
    }
}