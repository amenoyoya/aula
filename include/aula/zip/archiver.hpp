#pragma once

#include "../core.hpp"

namespace aula {
    namespace zip {
        /// zip archiver structure
        struct archiver_t {
            unsigned long   handler;
            unsigned short  compresslevel;  // compression level: 0 - 9
            std::string     comment,        // if you designated this before archiver_close, global comment will be set
                            password;       // compress password
        };
        typedef std::unique_ptr<archiver_t, std::function<void(archiver_t*)>> archiver_ptr;

        /// zip extractor structure
        struct extractor_t {
            unsigned long   handler;
            size_t          size,           // total zip file size
                            entries,        // entry count
                            comment_size;   // global comment length
            std::string     comment;        // global comment
        };
        typedef std::unique_ptr<extractor_t, std::function<void(extractor_t*)>> extractor_ptr;

        /// date time structure
        struct datetime_t {
            unsigned long sec, min, hour, day, month, year;
        };

        /// file information in zip structure
        struct fileinfo_t {
            unsigned long   version, // created version
                            needed_version, // needed version for uncompression
                            flag, // bit flag
                            compression_method, // compression method
                            dos_date, // modified time (DOS)
                            crc32, // crc32
                            compressed_size, // compressed size
                            uncompressed_size, // uncompressed size
                            filename_size, // file name length
                            extra_size, // extra fields size
                            comment_size, // comment length
                            disknum_start, // start position of disk num
                            internal_attr, // internal file attribution
                            external_attr; // external file attribution
            datetime_t      created_at; // created date time
            std::string     filename, comment;
            io::binary_ptr  content; // uncompressed content data

            io::binary_t*   getcontent() { return this->content.get(); }
        };

        /// local file position in the zip file
        struct filepos_t {
            unsigned long   pos_in_zip,  // offset in zip file directory
                            num_of_file; // of file
        };

        /// open zip file (archiver)
        // @param mode:
        //         "w": create new file.
        //         "w+": embed zip data to the file
        //         "a": append data to the zip file
        //        * parent directories will be created automatically
        archiver_ptr zip_open(const std::string &filename, const std::string &mode = "w");

        /// release zip archiver explicitly
        inline void zip_close(archiver_ptr &self) {
            self.reset();
        }

        /// append data as a file into zip file
        bool zip_append(archiver_t *self, io::binary_t *data, const std::string &dest_filename, const std::string &comment = "");
        
        /// append file into zip file
        inline bool zip_appendfile(archiver_t *self, const std::string &src_filename, const std::string &dest_filename, const std::string &comment = "") {
            auto data = fs::readfile(src_filename);
            return data ? zip_append(self, data.get(), dest_filename, comment) : false;
        }


        /// open zip extractor
        extractor_ptr unz_open(const std::string &filename);

        /// release zip extractor explicitly
        inline void unz_close(extractor_ptr &self) {
            self.reset();
        }

        /// locate first entry file in the zip file
        bool unz_locate_first(extractor_t *self);

        /// locate next entry file in the zip file
        bool unz_locate_next(extractor_t *self);

        /// locate specified name of file in the zip file
        bool unz_locate_name(extractor_t *self, std::string name);

        /// get current file information in the zip data
        // @param isContentRequired: if true is designated => uncompressed content will be set to fileinfo_t.content
        // @param password: extracting password when isContentRequired == true
        std::unique_ptr<fileinfo_t> unz_info(extractor_t *self, bool isContentRequired = false, const std::string &password = "");

        /// get current file position in the zip data
        std::unique_ptr<filepos_t> unz_pos(extractor_t *self);

        /// locate to the designated position
        bool unz_locate(extractor_t *self, filepos_t *pos);

        /// get the zip file offset (if the data is embedded zip data, return larger than 0)
        size_t unz_offset(extractor_t *self);
    }
}