#include "zipReader.h"

namespace Aula{
    /*** class ZipFileReader ***/
    bool ZipFileReader::open(const string &arcname, const string &filename){
        ZipArchiver arc(arcname, "r");
        ZipFileInformation info;
        
        if(getState(&arc) == FAILED){
            _state = FAILED;
            _message = "failed to open zip file '"+arcname+"'";
            return false;
        }
        if(!arc.locateFile(filename)){
            _state = FAILED;
            _message = "failed to open local file '"+filename+"' in zip file '"+arcname+"'";
            return false;
        }
        if(!arc.getCurrentFileInformation(&info)){
            _state = FAILED;
            _message = "failed to get local file '"+filename+"' information in zip file '"+arcname+"'";
            return false;
        }
        close();
        bin.resize(size = info.uncompressedSize);
        if(!arc.openReadCurrentFile((void*)&bin[0], size, password)){
            _state = FAILED;
            _message = "failed to read local file '"+filename+"' in zip file '"+arcname+"'";
            return false;
        }
        _state = ACTIVE;
        return true;
    }
    
    string ZipFileReader::readLine(){
        if(_state != ACTIVE) return "";
        
        string ret;
        u32 size = getSize();
        ret.reserve(128);
        for(; cur < size; ++cur){
            if(bin[cur] == '\r'){
                cur += 2; // 次の改行文字を飛ばす
                break;
            }else if(bin[cur] == '\n'){
                ++cur; // 改行を飛ばす
                break;
            }
            ret.push_back(bin[cur]);
        }
        return ret;
    }
    
    u32 ZipFileReader::read(void *dest, u32 _size, u32 n){
        if(_state != ACTIVE) return 0;
        
        u32 ret = ((cur + _size) > size? size - cur: _size);
        memcpy(dest, bin.c_str() + cur, _size);
        cur += _size;
        return ret;
    }
    
    string ZipFileReader::readAll(){
        if(_state != ACTIVE) return "";
        
        string ret;
        ret.resize(size);
        read((void*)&ret[0], size);
        return ret;
    }
    
    bool ZipFileReader::seek(s32 mov, u8 from){
        if(_state != ACTIVE) return false;
        switch(from){
        case SEEK_SET:
            if(mov < 0) cur = 0;
            else cur = (size <= (u32)mov? (size == 0? 0: size-1): mov);
            break;
        case SEEK_CUR:
            if(mov < 0){
                if((s32)cur + mov < 0) cur = 0;
                else cur += mov;
            }else{
                cur += mov;
                if(cur > size) cur = size;
            }
            break;
        case SEEK_END:
            if(mov > 0) cur = size;
            else cur = (size < (u32)(-mov)? 0: size + mov);
            break;
        }
        return true;
    }
    
    
    /*** class FileReader ***/
    bool FileReader::__open(const string &filename, const string &ext, const string &password){
        string path = Path::convert(filename); // ".", ".." を通常パスに変換
        
        // デフォルトアーカイブに対するopenを試行
        if(arcPathLen && Path::isSame(path, arcPath, arcPathLen)){
            string file = path.substr(arcPathLen + 1);
            
            pFile = new ZipFileReader(arcPath, file, arcKey);
            if(getState(pFile) == ACTIVE){
                curPath = Path::appendSlash(arcPath) + file;
                return true;
            }
            delete pFile; pFile = nullptr;
        }
        
        // 通常読み込み
        pFile = new File(filename, "rb");
        if(getState(pFile) == ACTIVE){
            curPath = filename;
            return true;
        }
        delete pFile; pFile = nullptr;
        
        // アーカイブ探索読み込み
        char *p = (char*)path.c_str();
        size_t i = 0, extlen = ext.size();
        
        while(*p){
            if(isSameString(p, ext, extlen) && (*(p+extlen) == '/'
                #ifdef _WINDOWS
                    || *(p+extlen) == '\\'
                #endif
            )){ // "ext/"の部分までをArchiveとしてopenを試行
                string arc = path.substr(0, i + extlen), file = path.substr(i + extlen + 1);
                
                pFile = new ZipFileReader(arc, file, password);
                if(getState(pFile) == ACTIVE){
                    curPath = Path::appendSlash(arc) + file;
                    return true;
                }
                delete pFile; pFile = nullptr;
                i += extlen;
                p += extlen;
            }
            ++i;
            ++p;
        }
        return false;
    }
    
    bool FileReader::open(const string &filename, const string &ext, const string &password){
        bool result;
        
        close();
        if(!(result = __open(filename, ext, password))){
            _state = FAILED;
            _message = "failed to open file '"+filename+"'";
            return result;
        }
        _state = ACTIVE;
        return result;
    }
    
    bool FileReader::openFile(const string &filename){
        close();
        pFile = new File(filename, "rb");
        if(getState(pFile) == FAILED){
            _state = FAILED;
            _message = getMessage(pFile);
            delete pFile; pFile = nullptr;
            return false;
        }
        curPath = filename;
        _state = ACTIVE;
        return true;
    }
    
    bool FileReader::openFileInZip(const string &arcname, const string &filename, const string &key){
        close();
        pFile = new ZipFileReader(arcname, filename, key);
        if(getState(pFile) == FAILED){
            _state = FAILED;
            _message = getMessage(pFile);
            delete pFile; pFile = nullptr;
            return false;
        }
        curPath = Path::appendSlash(arcname) + filename;
        _state = ACTIVE;
        return true;
    }
    
    void FileReader::close(){
        _state = NONE;
        _message.clear();
        if(pFile){
            pFile->close();
            delete pFile;
            pFile = nullptr;
            curPath.clear();
        }
    }
}
