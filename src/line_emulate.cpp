#include "line_emulate.hpp"
#include <string>
#include <cmath>
#include <fstream>
#include <algorithm>

namespace YadroTest {

LineEmulate::LineEmulate(const std::string& linePath, const LineConfig& config, bool isClear)
    : LinePath_(linePath), Config_(config) {
    StartLine_(isClear);
}

void LineEmulate::MoveToBegin() {
    CurrentTime_ += Position_ * Config_.MoveTime;
    Position_ = 0;
    LineStream_.seekg(0);
}

bool LineEmulate::Move(int delta) {
    if (Position_ + delta >= 0) {
        CurrentTime_ += Config_.MoveTime * std::abs(delta);
        Position_ += delta;
        UpdateSize_();
        LineStream_.seekg(delta * 4, std::ios::cur);
        return true;
    }

    return false;
}

bool LineEmulate::MoveBackward() {
    return Move(-1);
}

bool LineEmulate::MoveForward() {
    return Move(1);
}

int LineEmulate::GetSize() {
    if (LineStream_.is_open()) {
        LineStream_.seekg(0, std::ios::end);
        int size = LineStream_.tellg() / 4;
        LineStream_.seekg(Position_ * 4, std::ios::beg);
        return size;
    } else {
        return Size_;
    }
}

void LineEmulate::UpdateSize_() {
    Size_ = std::max(Position_, Size_);
}

void LineEmulate::WriteAndMove(int value) {
    CurrentTime_ += Config_.WriteTime;
    ++Position_;
    UpdateSize_();
    LineStream_.write(reinterpret_cast<const char*>(&value), sizeof(int));
}

bool LineEmulate::Read(int& value) {
    if (Position_ < Size_) {
        CurrentTime_ += Config_.ReadTime;
        LineStream_.read(reinterpret_cast<char*>(&value), sizeof(int));
        ++Position_;
        MoveBackward();
        return true;
    }

    return false;
}

bool LineEmulate::ReadAndMove(int& value) {
    bool status = Read(value);

    if (status) {
        MoveForward();
    }
    return status;
}

long long LineEmulate::CalcTime() const {
    return CurrentTime_;
}

void LineEmulate::StartLine_(bool isClear) {
    if (!LineStream_.is_open()) {
        if (isClear) {
            LineStream_.open(LinePath_, std::fstream::in | std::fstream::out |
                                            std::fstream::binary | std::fstream::trunc);
        } else {
            LineStream_.open(LinePath_, std::fstream::in | std::fstream::out |
                                            std::fstream::binary | std::fstream::app);
        }
        LineStream_.seekg(Position_ * 4, std::ios::beg);
        Size_ = GetSize();
    }
}

void LineEmulate::RunLine() {
    StartLine_(false);
}

void LineEmulate::StopLine() {
    if (LineStream_.is_open()) {
        LineStream_.close();
    }
}

}  // namespace YadroTest