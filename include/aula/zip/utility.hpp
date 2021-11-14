#pragma once

#include "archiver.hpp"

namespace aula {
    namespace zip {
        /*** utility functions ***/

        /// remove embedded zip data from the file
        bool unz_rmdata(const std::string &filename);

        /// Compress the directory to zip
        bool zip_compress(
            const std::string &dir, const std::string &output, unsigned short compresslevel = 0,
            const std::string &password = "", const std::string &mode = "w",
            const std::string &comment = "", const std::string &root = ""
        );

        /// extract the zip into directory
        bool unz_extract(const std::string &zipfile, const std::string &outputdir, const std::string &password = "");
    }
}