#include <iostream>
#include <fstream>
#include <curl.h>
#include "CompFileVersion.h"
#include "DowloadFile.h"

int main() {
    CompFileVersion Comp;
    std::cout << "TempFile" << Comp.STempTpath <<std::endl;
    std::cout << "TempFile Version =" << Comp.TempFilePath << std::endl;
    std::cout << "Repertoire locale =" << Comp.SLocalPath << std::endl;
    /*if (downloadFile(url, outputPath)) {
        std::cout << "File downloaded successfully." << std::endl;
    }
    else {
        std::cerr << "File download failed." << std::endl;
    }*/

    return 0;
}
