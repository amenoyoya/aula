#pragma once

#include "../../../core/encoding/base.hpp"

namespace Aula {
    inline void open_encoding_library(sol::state &lua) {
        auto aula = lua["Aula"].get_or_create<sol::table>();
        auto encoding = aula["Encoding"].get_or_create<sol::table>();

        encoding.new_enum("Type",
            "UNKNOWN", Encoding::Type::UNKNOWN,
            "BINARY", Encoding::Type::BINARY,
            "ANSI", Encoding::Type::ANSI,
            "SJIS", Encoding::Type::SJIS,
            "JIS", Encoding::Type::JIS,
            "EUC", Encoding::Type::EUC,
            "ISO2022JP", Encoding::Type::ISO2022JP,
            "UTF8", Encoding::Type::UTF8,
            "UTF16BE", Encoding::Type::UTF16BE,
            "UTF16LE", Encoding::Type::UTF16LE,
            "UTF32BE", Encoding::Type::UTF32BE,
            "UTF32LE", Encoding::Type::UTF32LE
        );
        encoding.set_function("getEncodingName", Encoding::getEncodingName);
        encoding.set_function("isUTF8", Encoding::isUTF8);
        encoding.set_function("encode", sol::overload(
            [](const std::string &target, u8 toEncoding, u8 fromEncoding) { return Encoding::encode(target, toEncoding, fromEncoding); },
            [](const std::string &target, u8 toEncoding) { return Encoding::encode(target, toEncoding); }
        ));
    }
}