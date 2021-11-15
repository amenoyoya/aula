#include <aula/core/io.hpp>
#include <cassert>

inline bool writefile(const std::string &filename, aula::io::binary_t *binary) {
    FILE *fp = fopen(filename.c_str(), "wb");
    bool result = 0 < fwrite(aula::io::binary_tostr(binary), 1, binary->size, fp);
    fclose(fp);
    return result;
}

inline std::unique_ptr<aula::io::binary_t> readfile(const std::string &filename) {
    FILE *fp = fopen(filename.c_str(), "rb");
    fseek(fp, 0, aula::io::seekfrom::tail);
    
    size_t size = ftell(fp);
    auto bin = aula::io::binary_new(0, size);

    fseek(fp, 0, aula::io::seekfrom::head);
    fread((void*)binary_addr(bin.get()), 1, size, fp);
    fclose(fp);
    return std::move(bin);
}

int main() {
    auto bin = aula::io::binary_new(0, 0); // create empty binary

    aula::io::binary_pushrune(bin.get(), "Hello, world");
    aula::io::binary_pushint(bin.get(), 123);

    assert(aula::io::binary_encrypt(bin.get(), "password"));

    writefile("database", bin.get());

    auto data = readfile("database");
    assert(aula::io::binary_decrypt(data.get(), "xxxxxxxx") == false);
    assert(aula::io::binary_decrypt(data.get(), "password"));

    auto str = aula::io::binary_getrune(data.get());
    auto val = aula::io::binary_geti32(data.get());

    assert(str == "Hello, world");
    assert(val == 123);
    printf("%s\t%d\n", str.c_str(), val);

    assert(0 == remove("database"));
    return 0;
}

#include <aula/core/io.cpp>
