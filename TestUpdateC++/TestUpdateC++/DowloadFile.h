#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#pragma once
#include <string>

class DowloadFile
{
public:
	DowloadFile();
	~DowloadFile();
	bool downloadFile(const std::string& outputPath);
private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};
#endif
