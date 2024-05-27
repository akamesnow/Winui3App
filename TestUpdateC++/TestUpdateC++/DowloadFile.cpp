#include "DowloadFile.h"
#include <curl.h>
#include <iostream>
#include <fstream>

DowloadFile::DowloadFile() {
    curl_global_init(CURL_GLOBAL_ALL);
}

DowloadFile::~DowloadFile() {
    curl_global_cleanup();
}

size_t DowloadFile::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool DowloadFile::downloadFile(const std::string& outputPath)
{
    std::string url = "https://raw.githubusercontent.com/akamesnow/Winui3App/main/ConsoleApp1/ConsoleApp1/bin/Release/net7.0/ConsoleApp1.exe";
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::ofstream outFile(outputPath, std::ios::binary);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return false;
        }
    }

    if (outFile.is_open()) {
        outFile << readBuffer;
        std::cerr << "File dowloaded" << std::endl;
        outFile.close();
    }
    else {
        std::cerr << "Could not open output file." << std::endl;
        return false;
    }

    return true;
}


