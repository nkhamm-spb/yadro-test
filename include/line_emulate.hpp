#pragma once

#include "line_interface.hpp"
#include <string>
#include <fstream>

namespace YadroTest {

struct LineConfig {
    long long ReadTime = 1;
    long long WriteTime = 1;
    long long MoveTime = 1;
};

class LineEmulate : public ILine {
public:
    LineEmulate(const std::string& linePath, const LineConfig& config, bool isClear = false);

    bool Read(int& data) override;
    bool ReadAndMove(int& data) override;
    void WriteAndMove(int data) override;
    int GetSize() override;
    bool Move(int delta) override;
    bool MoveForward() override;
    bool MoveBackward() override;
    void MoveToBegin() override;
    long long CalcTime() const override;
    void RunLine() override;
    void StopLine() override;

private:
    void StartLine_(bool isClear);
    void UpdateSize_();

    long long CurrentTime_ = 0;
    int Size_ = 0;
    int Position_ = 0;

    LineConfig Config_;
    std::fstream LineStream_;
    std::string LinePath_;
};

}  // namespace YadroTest