#include "CompFileVersion.h"
#include "DowloadFile.h"
#include <vector>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

CompFileVersion::CompFileVersion() 
{
	MyGetTempPath();
	DowloadFile Dow;
	Dow.downloadFile(STempTpath);
    WstrTempTpath = StringToWideString(STempTpath);
    TempFilePath = GetFileVersion(WstrTempTpath);
    SLocalPath = getExecutablePath();
    SLocalPath = SLocalPath + "\\net7.0\\ConsoleApp1.exe";
    WSTRLocalPath == StringToWideString(SLocalPath);
    SLocalVerions = GetFileVersion(WstrTempTpath);
    SameVersion = VersionIsSame(SLocalVerions, TempFilePath);
    GitHubContentList = getGitHubContentList(url);
    std::string jsonResponse = getGitHubContentList(url);
    json responseJson = json::parse(jsonResponse);
    // Parcourir les fichiers et les télécharger
    for (const auto& item : responseJson) {
        if (item["type"] == "file") {
            std::string downloadUrl = item["download_url"];
            std::string fileName = item["name"];
            std::cout << "Downloading: " << fileName << " from URL: " << downloadUrl << std::endl;
            downloadFile(downloadUrl, "./Fichier/" + fileName);
        }
    }
};

std::wstring CompFileVersion::StringToWideString(std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string CompFileVersion::ConvertWCharToString(wchar_t* wstr)
{
	std::wstring ws(wstr);
	std::string str(ws.begin(), ws.end());
	return str;
}

std::string wstring_to_string(const std::wstring& wstr) {
    // Utilise wstring_convert pour convertir wstring en string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

void CompFileVersion::MyGetTempPath()
{
	pathLen = GetTempPathW(MAX_PATH, tempPath);
	STempTpath = ConvertWCharToString(tempPath);
	STempTpath = STempTpath + "ConsoleApp1.exe";
}

std::string* CompFileVersion::GetFileVersion(const std::wstring& filePath) {

    DWORD dummy;
    DWORD versionSize = GetFileVersionInfoSize(filePath.c_str(), &dummy);
    if (versionSize == 0) {
        return NULL;
    }

    std::vector<BYTE> versionInfoBuffer(versionSize);
    if (!GetFileVersionInfo(filePath.c_str(), 0, versionSize, &versionInfoBuffer[0])) {
        return NULL;
    }

    VS_FIXEDFILEINFO* fileInfo;
    UINT fileInfoSize;
    if (!VerQueryValue(&versionInfoBuffer[0], L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoSize)) {
        return NULL;
    }

    std::wstring version;
    version += std::to_wstring((fileInfo->dwFileVersionMS >> 16) & 0xFFFF);
    version += L".";
    version += std::to_wstring((fileInfo->dwFileVersionMS) & 0xFFFF);
    version += L".";
    version += std::to_wstring((fileInfo->dwFileVersionLS >> 16) & 0xFFFF);
    version += L".";
    version += std::to_wstring((fileInfo->dwFileVersionLS) & 0xFFFF);
    std::string StrVersion = wstring_to_string(version);


    return &StrVersion;

}

std::string CompFileVersion::getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

bool CompFileVersion::VersionIsSame(std::string* LocalVersion, std::string* TempVersion)
{
    if (LocalVersion == TempVersion)
    {
        return false;
    }
    else
    {
        return false;
    }
}

void CompFileVersion::DowloadNewVersion(bool IsSameVersion)
{
    if (IsSameVersion)
    {

    }
}

std::string CompFileVersion::getGitHubContentList(const std::string& url)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return readBuffer;
}

void CompFileVersion::downloadFile(const std::string& url, const std::string& outputPath) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        std::ofstream outFile(outputPath, std::ios::binary);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        outFile.close();
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

size_t CompFileVersion::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fonction d'écriture de données pour les fichiers
size_t CompFileVersion::WriteFileCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::ofstream*)userp)->write((char*)contents, size * nmemb);
    return size * nmemb;
}



