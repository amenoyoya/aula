#pragma once

#include "../../zip.hpp"

namespace aula {
    namespace zip {
        template<typename State>
        void openlib(State &lua) {
            auto fs = lua["fs"].get_or_create<sol::table>();
            auto zip = fs["zip"].get_or_create<sol::table>();
            auto unz = fs["unz"].get_or_create<sol::table>();

            zip.new_usertype<aula::zip::archiver_t>("archiver_t",
                "handler", &aula::zip::archiver_t::handler,
                "compresslevel", &aula::zip::archiver_t::compresslevel,
                "comment", &aula::zip::archiver_t::comment,
                "password", &aula::zip::archiver_t::password,
                "close", aula::zip::zip_close,
                "append", sol::overload(
                    [](aula::zip::archiver_t *self, aula::io::binary_t *data, const std::string &dest_filename, const std::string &comment) { return aula::zip::zip_append(self, data, dest_filename, comment); },
                    [](aula::zip::archiver_t *self, aula::io::binary_t *data, const std::string &dest_filename) { return aula::zip::zip_append(self, data, dest_filename); }
                ),
                "appendfile", sol::overload(
                    [](aula::zip::archiver_t *self, const std::string &src_filename, const std::string &dest_filename, const std::string &comment) { return aula::zip::zip_appendfile(self, src_filename, dest_filename, comment); },
                    [](aula::zip::archiver_t *self, const std::string &src_filename, const std::string &dest_filename) { return aula::zip::zip_appendfile(self, src_filename, dest_filename); }
                )
            );
            zip.set_function("open", sol::overload(
                [](const std::string &filename, const std::string &mode) { return aula::zip::zip_open(filename, mode); },
                [](const std::string &filename) { return aula::zip::zip_open(filename); }
            ));

            unz.new_usertype<aula::zip::datetime_t>("datetime_t",
                "sec", &aula::zip::datetime_t::sec,
                "min", &aula::zip::datetime_t::min,
                "hour", &aula::zip::datetime_t::hour,
                "day", &aula::zip::datetime_t::day,
                "month", &aula::zip::datetime_t::month,
                "year", &aula::zip::datetime_t::year
            );
            unz.new_usertype<aula::zip::fileinfo_t>("fileinfo_t",
                "version", &aula::zip::fileinfo_t::version,
                "needed_version", &aula::zip::fileinfo_t::needed_version,
                "flag", &aula::zip::fileinfo_t::flag,
                "compression_method", &aula::zip::fileinfo_t::compression_method,
                "dos_date", &aula::zip::fileinfo_t::dos_date,
                "crc32", &aula::zip::fileinfo_t::crc32,
                "compressed_size", &aula::zip::fileinfo_t::compressed_size,
                "uncompressed_size", &aula::zip::fileinfo_t::uncompressed_size,
                "filename_size", &aula::zip::fileinfo_t::filename_size,
                "extra_size", &aula::zip::fileinfo_t::extra_size,
                "comment_size", &aula::zip::fileinfo_t::comment_size,
                "disknum_start", &aula::zip::fileinfo_t::disknum_start,
                "internal_attr", &aula::zip::fileinfo_t::internal_attr,
                "external_attr", &aula::zip::fileinfo_t::external_attr,
                "created_at", &aula::zip::fileinfo_t::created_at,
                "filename", &aula::zip::fileinfo_t::filename,
                "comment", &aula::zip::fileinfo_t::comment
                // "content", &aula::zip::fileinfo_t::content
            );
            unz.new_usertype<aula::zip::filepos_t>("filepos_t",
                "pos_in_zip", &aula::zip::filepos_t::pos_in_zip,
                "num_of_file", &aula::zip::filepos_t::num_of_file
            );
            unz.new_usertype<aula::zip::extractor_t>("extractor_t",
                "handler", &aula::zip::extractor_t::handler,
                "size", &aula::zip::extractor_t::size,
                "entries", &aula::zip::extractor_t::entries,
                "comment_size", &aula::zip::extractor_t::comment_size,
                "comment", &aula::zip::extractor_t::comment,
                "close", aula::zip::unz_close,
                "locate_first", aula::zip::unz_locate_first,
                "locate_next", aula::zip::unz_locate_next,
                "locate_name", aula::zip::unz_locate_name,
                "info", sol::overload(
                    [](aula::zip::extractor_t *self, bool isContentRequired, const std::string &password) { return aula::zip::unz_info(self, isContentRequired, password); },
                    [](aula::zip::extractor_t *self, bool isContentRequired) { return aula::zip::unz_info(self, isContentRequired); },
                    [](aula::zip::extractor_t *self) { return aula::zip::unz_info(self); }
                ),
                "pos", aula::zip::unz_pos,
                "locate", aula::zip::unz_locate,
                "offset", aula::zip::unz_offset
            );
            unz.set_function("open", aula::zip::unz_open);

            unz.set_function("rmdata", aula::zip::unz_rmdata);
            zip.set_function("compress", sol::overload(
                [](const std::string &dir, const std::string &output, unsigned short compresslevel, const std::string &password, const std::string &mode, const std::string &comment, const std::string &root) { return aula::zip::zip_compress(dir, output, compresslevel, password, mode, comment, root); },
                [](const std::string &dir, const std::string &output, unsigned short compresslevel, const std::string &password, const std::string &mode, const std::string &comment) { return aula::zip::zip_compress(dir, output, compresslevel, password, mode, comment); },
                [](const std::string &dir, const std::string &output, unsigned short compresslevel, const std::string &password, const std::string &mode) { return aula::zip::zip_compress(dir, output, compresslevel, password, mode); },
                [](const std::string &dir, const std::string &output, unsigned short compresslevel, const std::string &password) { return aula::zip::zip_compress(dir, output, compresslevel, password); },
                [](const std::string &dir, const std::string &output, unsigned short compresslevel) { return aula::zip::zip_compress(dir, output, compresslevel); },
                [](const std::string &dir, const std::string &output) { return aula::zip::zip_compress(dir, output); }
            ));
            unz.set_function("extract", sol::overload(
                [](const std::string &zipfile, const std::string &outputdir, const std::string &password) { return aula::zip::unz_extract(zipfile, outputdir, password); },
                [](const std::string &zipfile, const std::string &outputdir) { return aula::zip::unz_extract(zipfile, outputdir); }
            ));
        }
    }
}