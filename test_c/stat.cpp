#include <aula/core.hpp>

__main() {
    auto stat = Aula::Path::getFileStatus(Aula::Encoding::toUTF8(argv[0]));
    if (!stat) {
        Aula::IO::Stderr->write("failed to get status of this file");
        return 1;
    }
    Aula::IO::Stdout->write(_U8("デバイスID : ") + Aula::Encoding::toString(stat->deviceId));
    Aula::IO::Stdout->write(_U8("inode番号 : ") + Aula::Encoding::toString(stat->inode));
    Aula::IO::Stdout->write(_U8("アクセス保護 : ") + Aula::Encoding::toString(stat->accessMode));
    Aula::IO::Stdout->write(_U8("ハードリンクの数 : ") + Aula::Encoding::toString(stat->nLinks));
    Aula::IO::Stdout->write(_U8("所有者のユーザID : ") + Aula::Encoding::toString(stat->userId));
    Aula::IO::Stdout->write(_U8("所有者のグループID : ") + Aula::Encoding::toString(stat->groupId));
    Aula::IO::Stdout->write(_U8("デバイスID（特殊ファイルの場合） : ") + Aula::Encoding::toString(stat->specialDeviceId));
    Aula::IO::Stdout->write(_U8("容量（バイト単位） : ") + Aula::Encoding::toString(stat->size));
    Aula::IO::Stdout->write(_U8("最終アクセス時刻 : ") + Aula::Encoding::toString(stat->lastAccessedSeconds));
    Aula::IO::Stdout->write(_U8("最終修正時刻 :") + Aula::Encoding::toString(stat->lastModifiedSeconds));
    Aula::IO::Stdout->write(_U8("最終状態変更時刻 : ") + Aula::Encoding::toString(stat->lastChangedSeconds));
    return 0;
}