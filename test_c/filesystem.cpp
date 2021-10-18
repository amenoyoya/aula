#include <aula/core.hpp>

__main() {
    std::string dir = Aula::Path::complete(Aula::Path::getParentDirectory(argv[0], false));
    std::string file = Aula::Path::complete(argv[0]);
    
    Aula::IO::Stdout->write(dir + ": " + (Aula::Path::isDirectory(dir) ? "is directory" : "is not directory"));
    Aula::IO::Stdout->write(file + ": " + (Aula::Path::isFile(file) ? "is file" : "is not file"));

    Aula::IO::Stdout->write(
        file + "\n\tbase name: " + Aula::Path::getBaseName(file)
        + "\n\tstem: " + Aula::Path::getBaseStem(file)
        + "\n\textension: " + Aula::Path::getExtension(file)
    );
    Aula::IO::Stdout->write(Aula::Path::complete("/mnt/d/github/aula/test/base"));
    return 0;
}