#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

std::time_t to_time_t(const fs::file_time_type& ftime) {
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now()
        + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
}

int main() {
    std::ofstream file_list("file_list.txt");

    for (const auto& entry : fs::recursive_directory_iterator(".")) {
        if (entry.is_regular_file()) {
            auto ftime = fs::last_write_time(entry);
            std::time_t cftime = to_time_t(ftime);

            struct tm timeinfo;
            localtime_s(&timeinfo, &cftime);

            file_list << entry.path().filename().string() << " - "
                << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S")
                << std::endl;
        }
    }

    return 0;
}
