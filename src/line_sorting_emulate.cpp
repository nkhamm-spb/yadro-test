#include "line_sorting_emulate.hpp"
#include "line_emulate.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace YadroTest {

LineSortingEmulate::LineSortingEmulate(const std::string& inputPath, const std::string& outPath,
                                       int maxSize, const std::string& configFilePath,
                                       std::string tempPath)
    : TempPath_(std::move(tempPath)) {

    std::filesystem::create_directories(TempPath_);

    if (!configFilePath.empty()) {
        std::ifstream configFile;
        configFile.open(configFilePath);

        // We assume that in config file consist duration of read write and move in this oreder
        configFile >> Config_.ReadTime >> Config_.WriteTime >> Config_.MoveTime;
        configFile.close();
    }

    std::unique_ptr<ILine> inputLine = std::make_unique<LineEmulate>(inputPath, Config_);
    std::unique_ptr<ILine> outLine = std::make_unique<LineEmulate>(outPath, Config_, true);

    // We reserve 0.5 Kbyte for program data and divide by 4 because int is 4 bytes
    maxSize = std::max((maxSize - 512) / 4, 1);
    Sorter_ = LineSorter(
        std::move(inputLine), std::move(outLine),
        [this](int id) { return this->GetTemporaryLine_(id); }, maxSize);
}

long long LineSortingEmulate::MakeSort() {
    Sorter_.MakeSort();

    long long time = Sorter_.CalcTime();
    std::cout << "Total time: " << time << std::endl;

    return time;
}

std::unique_ptr<ILine> LineSortingEmulate::GetTemporaryLine_(int id) {
    return std::make_unique<LineEmulate>(TempPath_ + "temp" + std::to_string(id), Config_, true);
}

int LineSortingEmulate::GetInSize() {
    return Sorter_.GetInSize();
}

int LineSortingEmulate::GetOutSize() {
    return Sorter_.GetOutSize();
}

LineSortingEmulate::~LineSortingEmulate() {
    for (const auto& entry : std::filesystem::directory_iterator(TempPath_)) {
        std::filesystem::remove_all(entry.path());
    }
}

}  // namespace YadroTest