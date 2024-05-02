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
    LineEmulate(const std::string& linePath, const std::string& configFilePath = "", bool clear = false);
    LineEmulate(const std::string& linePath, const LineConfig& config, bool clear = false);
    ~LineEmulate() override;

    bool ReadAndMove(int& data) override;
    void WriteAndMove(int data) override;
    bool MoveForward() override;
    void MoveToBegin() override;
    long long CalcTime() override;

private:
    long long CurrentTime_ = 0;
    int Position_ = 0;

    LineConfig Config_;
    std::fstream LineStream_;
};

}  // namespace YadroTest