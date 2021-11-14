#include "utility.hpp"

namespace aula {
    namespace zip {
        bool unz_rmdata(const std::string &filename) {
            auto arc = unz_open(filename);
            if (!arc) return false;

            // copy the file data except the zip field
            auto fp = fs::file_open(filename, "rb");
            if (!fp) return false;

            size_t size = fs::file_size(fp.get()) - arc->size;
            auto bin = fs::file_read(fp.get(), size);

            // overwrite
            if (nullptr == (fp = fs::file_open(filename, "wb"))) return false;
            return io::binary_size(bin.get()) == fs::file_write(fp.get(), bin.get());
        }

        /// @private compress the directory (base)
        static bool __compress(archiver_t *zip, const std::string &dir, size_t basedir_len, const std::string &root) {
            auto dirent = fs::dir_open(dir);
            if (!dirent) return false;
            do {
                if (dirent->current_name == "." || dirent->current_name == "..") continue;

                if (dirent->current_isdir) {
                    // process recursively
                    if (!__compress(zip, dirent->current_path, basedir_len, root)) return false;
                } else if (dirent->current_isfile) {
                    // append file into zip
                    if (!zip_appendfile(zip, dirent->current_path, root + dirent->current_path.substr(basedir_len))) return false;
                }
            } while (fs::dir_next(dirent.get()));
            return true;
        }

        bool zip_compress(
            const std::string &dir, const std::string &output, unsigned short level,
            const std::string &password, const std::string &mode,
            const std::string &comment, const std::string &root)
        {
            if (!path::isdir(dir)) return false;

            auto zip = zip_open(output, mode);
            if (!zip) return false;

            zip->compresslevel = level;
            zip->password = password;
            zip->comment = comment;
            return __compress(zip.get(), dir, path::append_slash(dir).size(), root);
        }

        bool unz_extract(const std::string &zipfile, const std::string &outputdir, const std::string &password) {
            auto unz = unz_open(zipfile);
            if (!unz) return false;

            do {
                auto info = unz_info(unz.get(), true, password);
                if (!info) return false;
                // extract to file
                if (!fs::writefile(path::append_slash(outputdir) + info->filename, info->content.get())) return false;
            } while (unz_locate_next(unz.get()));
            return true;
        }
    }
}