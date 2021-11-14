#pragma once

#include "io.hpp"

namespace aula {
    namespace path {
        /// structure of file status
        struct stat_t {
            unsigned long device_id, inode;
            unsigned short access_mode;
            short nlinks, user_id, group_id;
            unsigned long special_device_id;
            unsigned long long size, // file size
                last_accessed_seconds, // last accessed time (sec)
                last_modified_seconds, // last modified time (sec)
                last_changed_seconds;  // last file status changed time (sec)
        };

        /// get file name
        // e.g. "/path/to/sample.txt" => "sample.txt"
        std::string basename(const std::string &path);

        /// get file name without extension
        // e.g. "/path/to/sample.txt" => "sample"
        std::string stem(const std::string &path);

        /// get file extension
        // e.g. "/path/to/sample.txt" => ".txt"
        std::string ext(const std::string &path);

        /// get parent directory
        // e.g. "/path/to/sample.txt" => "/path/to"
        std::string parentdir(const std::string &path, bool isFullPathRequired = true);

        /// identifies if the path is file
        bool isfile(const std::string &path);

        /// identifies if the path is directory
        bool isdir(const std::string &path);

        /// get full path
        std::string complete(const std::string &path);

        /// get the file|directory status
        std::unique_ptr<stat_t> stat(const std::string &path);

        /// append '/' or '\\' to the end
        inline std::string append_slash(const std::string &path) {
            auto it = path.end() - 1;
            const char *slash =
                #ifdef _WINDOWS
                    "\\";
                #else
                    "/";
                #endif
            if (*it != '/' && *it != '\\') return std::move(path + slash);
            return std::move(path);
        }

        /// remove '/' or '\\' from the end
        inline std::string remove_slash(std::string path) {
            auto it = path.end() - 1;
            if (*it == '/' || *it == '\\') path.erase(it);
            return std::move(path);
        }
    }
}