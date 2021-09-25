#pragma once

#include "../encoding/base.h"

namespace Aula {
    namespace IO {
        enum SeekFrom {
            HEAD = SEEK_SET,
            CURRENT = SEEK_CUR,
            END = SEEK_END,
        };
    }
}