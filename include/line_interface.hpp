#pragma once

namespace YadroTest {

class ILine {
public:
    virtual ~ILine() = default;
    virtual bool ReadAndMove(int& data) = 0;
    virtual void WriteAndMove(int data) = 0;
    virtual bool MoveForward() = 0;
    virtual void MoveToBegin() = 0;
    virtual long long CalcTime() = 0;
};

}  // namespace YadroTest