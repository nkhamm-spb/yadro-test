#include "line_emulate.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace YadroTest {

LineEmulate::LineEmulate(const std::string& linePath, const std::string& configFilePath,
                         bool clear) {

    if (clear) {
        LineStream_.open(linePath, std::ios::in | std::ios::out | std::ios::trunc);

    } else {
        LineStream_.open(linePath, std::ios::in | std::ios::out | std::ios::app);
    }

    std::cout << linePath << std::endl;
    if (!configFilePath.empty()) {
        std::ifstream configFile;
        configFile.open(configFilePath);

        // We assume that in config file consist duration of read write and move in this oreder
        configFile >> Config_.ReadTime >> Config_.WriteTime >> Config_.MoveTime;
        configFile.close();
    }
}

LineEmulate::LineEmulate(const std::string& linePath, const LineConfig& config, bool clear)
    : Config_(config) {
    if (clear) {
        LineStream_.open(linePath, std::ios::in | std::ios::out | std::ios::trunc);

    } else {
        LineStream_.open(linePath, std::ios::in | std::ios::out | std::ios::app);
    }
    std::cout << linePath << std::endl;
}

void LineEmulate::MoveToBegin() {
    CurrentTime_ += Position_ * Config_.MoveTime;
    Position_ = 0;
    LineStream_.seekg(0);
}

// We do nothing because we move automticaly while make read or write
bool LineEmulate::Move() {
    CurrentTime_ += Config_.MoveTime;
    return true;
}

void LineEmulate::WriteAndMove(int value) {
    CurrentTime_ += Config_.WriteTime;
    CurrentTime_ += Config_.MoveTime;
    ++Position_;
    LineStream_ << value << " ";
}

bool LineEmulate::ReadAndMove(int& value) {
    if (LineStream_ >> value) {
        CurrentTime_ += Config_.WriteTime;
        CurrentTime_ += Config_.MoveTime;
        ++Position_;

        return true;
    }

    return false;
}

long long LineEmulate::CalcTime() {
    return CurrentTime_;
}

LineEmulate::~LineEmulate() {
    LineStream_.close();
}

}  // namespace YadroTest