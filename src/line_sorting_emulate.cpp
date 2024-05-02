#include "line_sorting_emulate.hpp"
#include "line_emulate.hpp"
#include <fstream>
#include <iostream>

namespace YadroTest {

LineSortingEmulate::LineSortingEmulate(const std::string& inputPath, const std::string& outPath,
                                       int maxSize, const std::string& configFilePath,
                                       std::string tempPath)
    : TempPath_(std::move(tempPath)) {

    if (!configFilePath.empty()) {
        std::ifstream configFile;
        configFile.open(configFilePath);

        // We assume that in config file consist duration of read write and move in this oreder
        configFile >> Config_.ReadTime >> Config_.WriteTime >> Config_.MoveTime;
        configFile.close();
    }

    std::unique_ptr<ILine> inputLine = std::make_unique<LineEmulate>(inputPath, Config_);
    std::unique_ptr<ILine> outLine = std::make_unique<LineEmulate>(outPath, Config_);

    maxSize = std::max(maxSize - 512, 1);  // We reserve 0.5 Kbyte for program data
    Sorter_ = LineSorter(
        std::move(inputLine), std::move(outLine),
        [this](int id) { return this->GetTemporaryLine_(id); }, maxSize);
}

void LineSortingEmulate::MakeSort() {
    Sorter_.MakeSort();
    std::cout << "Total time: " << Sorter_.CalcTime() << std::endl;
}

std::unique_ptr<ILine> LineSortingEmulate::GetTemporaryLine_(int id) {
    std::cout << "HERE " << TempPath_ + "temp" + std::to_string(id) << std::endl;
    return std::make_unique<LineEmulate>(TempPath_ + "temp" + std::to_string(id), Config_, true);
}

}  // namespace YadroTest