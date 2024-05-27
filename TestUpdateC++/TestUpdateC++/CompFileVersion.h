#pragma once
#include <iostream>
#include <curl.h>
#include <string>
class CompFileVersion
{
public:
	CompFileVersion();
	std::wstring StringToWideString(std::string& str);
	wchar_t tempPath[MAX_PATH] = { 0 };
	std::string STempTpath;
	;
	std::wstring WstrTempTpath;
	std::string* TempFilePath;
	const std::wstring LocalFilePath;
	const std::wstring WSTRLocalPath;
	std::string SLocalPath;
	std::string* SLocalVerions;
	std::string url = "https://api.github.com/repos/akamesnow/Winui3App/contents/ConsoleApp1/ConsoleApp1/bin/Release/net7.0?ref=main";
	
private: 
	
	DWORD pathLen;
	std::string ConvertWCharToString(wchar_t* wstr);
	void MyGetTempPath();
	std::string* GetFileVersion(const std::wstring& filePath);
	std::string getExecutablePath();
	bool SameVersion;
	bool VersionIsSame(std::string* LocalVersion, std::string* TempVersion);
	std::string GitHubContentList;
	void DowloadNewVersion(bool IsSameVersion);
	std::string getGitHubContentList(const std::string& url);
	void downloadFile(const std::string& url, const std::string& outputPath);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static size_t WriteFileCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

