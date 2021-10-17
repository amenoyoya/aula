#pragma once

#include <aula/core/io/filesystem.hpp>

namespace Aula {
    namespace Zip {
        /// zipグローバル情報
        struct GlobalInformation {
            u32 entries,     // エントリー数
                commentSize; // グローバルコメントのバイト数
            std::string comment;  // グローバルコメント
        };

        /// 日付・時間
        struct DateTime {
            u32 sec, min, hour, day, month, year;
        };
        
        /// zip書庫内ファイル情報
        struct FileInformation {
            u32 version, // 作成されたバージョン
                neededVersion, // 解凍に必要なバージョン
                flag, // ビットフラグ
                compressionMethod, // 圧縮メソッド
                dosDate, // ファイル更新日(DOS)
                crc, // crc32
                compressedSize, // 圧縮時のサイズ
                uncompressedSize, // 解凍時のサイズ
                fileNameSize, // ファイル名のバイト数
                fileExtraSize, // エキストラフィールドのバイト数
                fileCommentSize, // コメントのバイト数
                diskNumStart, // disk num のスタート位置
                internalFA, // 内部ファイル属性
                externalFA; // 外部ファイル属性
            DateTime date; // ファイル作成日時
            std::string fileName, comment; // ファイル名，コメント
            IO::Binary  uncompressedData; // 解凍時のデータ内容
        };
        
        /// zipファイル管理クラス
        class Archiver: public Object {
        public:
            Archiver(): Object(), zip(0), unz(0), zipSize(0), compressLevel(6) {}
            explicit Archiver(const std::string &filename, const std::string &type = "w", const std::string &password = "")
                : Object(), zip(0), unz(0), zipSize(0), compressLevel(6)
            {
                open(filename, type, password);
            }
            ~Archiver(){
                close();
            }

            /// zipファイルオープン
            // @param type: 作成タイプ
            //         "w": 新規作成、 "w+":（ファイルに）埋め込み、 "a":（zipに）追加
            //         "r": 作成(埋め込み)したzipアーカイブを読み込む
            //      新規作成の場合，親ディレクトリも自動的につくる
            bool open(const std::string &filename, const std::string &type = "w", const std::string &password = "");

            /// zipファイルクローズ
            // close時に作成したzipファイルにコメントを付加できる
            bool close(const std::string &comment = "");

            /*** アウトプットモード用関数 ***/
            /// 圧縮レベル現在値取得
            const u8 &getCompressLevel() const { return compressLevel; }
            
            /// 圧縮レベル変更: 0-9
            Archiver &setCompressLevel(u8 level) {
                compressLevel = level;
                return *this;
            }

            /// zipファイルにデータをファイルとして追加
            bool append(const IO::Binary &data, const std::string &destFileName, u32 datasize = u32(-1), const std::string &comment = "");
            
            /// ファイルを追加
            bool appendFile(const std::string &srcFileName, const std::string &destFileName, const std::string &comment = "");


            /*** インプットモード用関数 ***/
            /// グローバル情報取得
            std::unique_ptr<GlobalInformation> getGlobalInformation() const;

            /// zip全体のサイズ
            const u32 &getSize() const { return zipSize; }
            
            /// 書庫内ファイルの最初の位置へ移動
            bool toFirstFile();

            /// 書庫内の次のファイルへ移動
            bool toNextFile();

            /// 指定ファイル名の書庫内ファイル位置に移動
            bool locateFile(std::string filename);

            /// 書庫内の現在位置のファイル情報取得
            // @param getContent(default: false): 解凍後のファイルデータを取得する場合は true
            std::unique_ptr<FileInformation> getCurrentFileInformation(bool getContent = false) const;

            /// 書庫内の現在位置取得
            u32 getCurrentOffset() const;
            
            /// 状態取得
            // 書庫内ファイルの読み込みが完了した場合FINISHEDを返す
            virtual u8 getState();
        private:
            u32         zip, unz; // 圧縮・解凍ハンドル
            u32         zipSize; // zipファイル全体のサイズ
            u8          compressLevel; // 圧縮レベル (append時使用)
            std::string compressPassword; // 圧縮・解凍用パスワード

            /// 書庫内の現在位置の解凍後ファイルデータ取得
            bool readCurrentFileData(IO::Binary *dest, u32 size) const;
        };
    }
}
