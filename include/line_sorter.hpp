#pragma once

#include "line_interface.hpp"
#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace YadroTest {

class LineSorter {

    // We will use merge sort to sorting line. Each each sorting layer will be recorded in a
    // separate time line.
    // Total time line number will be n - m, with summary size O(nlog(n))
    // Complexity will be O(nlog(n))

public:
    LineSorter(std::unique_ptr<ILine> inLine, std::unique_ptr<ILine> outLine,
               std::function<std::unique_ptr<ILine>(int)> makeTempFunction, int maxSize);
    LineSorter() = default;

    void MakeSort();
    long long CalcTime();

private:
    void Merge_(std::unique_ptr<ILine>& out, std::unique_ptr<ILine>& left,
                std::unique_ptr<ILine>& right);
    void SortPrepare_();

    std::function<std::unique_ptr<ILine>(int)> MakeTempFunction_;
    std::vector<std::unique_ptr<ILine> > TemporaryLines_;
    std::unique_ptr<ILine> InLine_;
    std::unique_ptr<ILine> OutLine_;
    int Id_;
    // int MaxSize_;
};
}  // namespace YadroTest
