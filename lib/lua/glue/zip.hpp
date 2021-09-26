#pragma once

#include "../../zip/base.hpp"

namespace Aula {
    inline void open_zip_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto zip = aula["Zip"].get_or_create<sol::table>();

        zip.new_usertype<Zip::GlobalInformation>("GlobalInformation",
            "entries", &Zip::GlobalInformation::entries,
            "commentSize", &Zip::GlobalInformation::commentSize,
            "comment", &Zip::GlobalInformation::comment
        );
        zip.new_usertype<Zip::DateTime>("DateTime",
            "sec", &Zip::DateTime::sec,
            "min", &Zip::DateTime::min,
            "hour", &Zip::DateTime::hour,
            "day", &Zip::DateTime::day,
            "month", &Zip::DateTime::month,
            "year", &Zip::DateTime::year
        );
        zip.new_usertype<Zip::FileInformation>("FileInformation",
            "version", &Zip::FileInformation::version,
            "neededVersion", &Zip::FileInformation::neededVersion,
            "flag", &Zip::FileInformation::flag,
            "compressionMethod", &Zip::FileInformation::compressionMethod,
            "dosDate", &Zip::FileInformation::dosDate,
            "crc", &Zip::FileInformation::crc,
            "compressedSize", &Zip::FileInformation::compressedSize,
            "uncompressedSize", &Zip::FileInformation::uncompressedSize,
            "fileNameSize", &Zip::FileInformation::fileNameSize,
            "fileExtraSize", &Zip::FileInformation::fileExtraSize,
            "fileCommentSize", &Zip::FileInformation::fileCommentSize,
            "diskNumStart", &Zip::FileInformation::diskNumStart,
            "internalFA", &Zip::FileInformation::internalFA,
            "externalFA", &Zip::FileInformation::externalFA,
            "date", &Zip::FileInformation::date,
            "fileName", &Zip::FileInformation::fileName,
            "comment", &Zip::FileInformation::comment,
            "uncompressedData", &Zip::FileInformation::uncompressedData
        );
        zip.new_usertype<Zip::Archiver>("Archiver",
            sol::constructors<
                Zip::Archiver(),
                Zip::Archiver(const std::string &, const std::string &type),
                Zip::Archiver(const std::string &)
            >(),
            "getState", &Zip::Archiver::getState,
            "getMessage", &Zip::Archiver::getMessage,
            "open", sol::overload(
                [](Zip::Archiver *self, const std::string &filename, const std::string &type) { return self->open(filename, type); },
                [](Zip::Archiver *self, const std::string &filename) { return self->open(filename); }
            ),
            "close", sol::overload(
                [](Zip::Archiver *self, const std::string &comment) { return self->close(comment); },
                [](Zip::Archiver *self) { return self->close(); }
            ),
            "append", sol::overload(
                [](Zip::Archiver *self, const IO::Binary &data, const std::string &destFileName, u32 datasize, std::string &password, u8 level, const std::string &comment) { return self->append(data, destFileName, datasize, password, level, comment); },
                [](Zip::Archiver *self, const IO::Binary &data, const std::string &destFileName, u32 datasize, std::string &password, u8 level) { return self->append(data, destFileName, datasize, password, level); },
                [](Zip::Archiver *self, const IO::Binary &data, const std::string &destFileName, u32 datasize) { return self->append(data, destFileName, datasize); },
                [](Zip::Archiver *self, const IO::Binary &data, const std::string &destFileName) { return self->append(data, destFileName); }
            ),
            "appendFile", sol::overload(
                [](Zip::Archiver *self, const std::string &srcFileName, const std::string &destFileName, std::string &password, u8 level, const std::string &comment) { return self->appendFile(srcFileName, destFileName, password, level, comment); },
                [](Zip::Archiver *self, const std::string &srcFileName, const std::string &destFileName, std::string &password, u8 level) { return self->appendFile(srcFileName, destFileName, password, level); },
                [](Zip::Archiver *self, const std::string &srcFileName, const std::string &destFileName) { return self->appendFile(srcFileName, destFileName); }
            ),
            "getGlobalInformation", &Zip::Archiver::getGlobalInformation,
            "getSize", &Zip::Archiver::getSize,
            "toFirstFile", &Zip::Archiver::toFirstFile,
            "toNextFile", &Zip::Archiver::toNextFile,
            "locateFile", &Zip::Archiver::locateFile,
            "getCurrentFileInformation", sol::overload(
                [](Zip::Archiver *self, bool getContent, const std::string &password) { return self->getCurrentFileInformation(getContent, password); },
                [](Zip::Archiver *self, bool getContent) { return self->getCurrentFileInformation(getContent); },
                [](Zip::Archiver *self) { return self->getCurrentFileInformation(); }
            ),
            "getCurrentOffset", &Zip::Archiver::getCurrentOffset
        );

        zip.set_function("removeEmbedData", Zip::removeEmbedData);
        zip.set_function("compress", sol::overload(
            [](const std::string &dirPath, const std::string &outputFile, const std::string &key, u8 level, const std::string &mode, const std::string &rootDir) { return Zip::compress(dirPath, outputFile, key, level, mode, rootDir); },
            [](const std::string &dirPath, const std::string &outputFile, const std::string &key, u8 level, const std::string &mode) { return Zip::compress(dirPath, outputFile, key, level, mode); },
            [](const std::string &dirPath, const std::string &outputFile, const std::string &key, u8 level) { return Zip::compress(dirPath, outputFile, key, level); },
            [](const std::string &dirPath, const std::string &outputFile, const std::string &key) { return Zip::compress(dirPath, outputFile, key); },
            [](const std::string &dirPath, const std::string &outputFile) { return Zip::compress(dirPath, outputFile); }
        ));
        zip.set_function("uncompress", sol::overload(
            [](const std::string &zipFile, const std::string &dirPath, const std::string &key) { return Zip::uncompress(zipFile, dirPath, key); },
            [](const std::string &zipFile, const std::string &dirPath) { return Zip::uncompress(zipFile, dirPath); }
        ));
    }
}