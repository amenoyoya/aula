#pragma once

#include <aula/core/encoding/base.hpp>
#include <memory>

namespace Aula {
    /// ファイルパスライブラリ
    namespace Path {
        /// ファイル名を抽出
        std::string getBaseName(const std::string &path);
        
        /// 拡張子を抜いたファイル名を抽出
        std::string getBaseStem(const std::string &path);

        /// 拡張子を抽出
        std::string getExtension(const std::string &path);
        
        /// ".."や"."などを上位，カレントディレクトリに変換したパスを取得
        std::string convert(const std::string &path);
        
        /// 同一パスかどうか判定
        // len: -1以外を指定するとlenバイト分だけ比較する（-1なら全て比較）
        bool isSame(const std::string &path1, const std::string &path2, u32 len = (u32)-1);
        
        /// 親ディレクトリを取得
        // real: trueなら実際の親ディレクトリ, falseなら一番後ろの'/'まで単なる文字列の切り出し
        std::string getParentDirectory(const std::string &path, bool real = true);
        
        /// 指定パスがファイルか判定
        bool isFile(const std::string &path);

        /// 指定パスがディレクトリか判定
        bool isDirectory(const std::string &path);
        
        /// フルパス取得
        std::string complete(const std::string &path);
        
        /// パスの末尾が'/\'でないなら'/\'を末尾に追加
        std::string appendSlash(const std::string &path);
        
        /// パスの末尾の'/\'を削除
        std::string removeSlash(std::string path);

        /// structure FileStatus
        struct FileStatus {
            u32 deviceId, inode;
            u16 accessMode;
            i16 nLinks, userId, groupId;
            u32 specialDeviceId;
            u64 size, // file size
                lastAccessedSeconds, // last accessed time (sec)
                lastModifiedSeconds, // last modified time (sec)
                lastChangedSeconds;  // last file status changed time (sec)
        };

        /// Get the file status
        std::unique_ptr<FileStatus> getFileStatus(const std::string &path);
    }
}