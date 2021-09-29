#pragma once

#include <aula/core/encoding/base.hpp>

namespace Aula {
    namespace IO {
        enum SeekFrom {
            HEAD = SEEK_SET,
            CURRENT = SEEK_CUR,
            END = SEEK_END,
        };
    }
}