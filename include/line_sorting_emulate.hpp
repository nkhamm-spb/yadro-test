#include "line_sorter.hpp"
#include "line_emulate.hpp"
#include <string>
#include <memory>

namespace YadroTest {

class LineSortingEmulate {
public:
    LineSortingEmulate(const std::string& inputPath, const std::string& outPath, int maxSize,
                       const std::string& configFilePath = "", std::string tempPath = "tmp/");
    ~LineSortingEmulate();
    void MakeSort();
    int GetInSize();
    int GetOutSize();

private:
    std::unique_ptr<ILine> GetTemporaryLine_(int id);

    std::string TempPath_;
    LineConfig Config_;  // We will use one config for all line during emulation
    LineSorter Sorter_;
};

}  // namespace YadroTest