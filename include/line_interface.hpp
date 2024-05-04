#pragma once

namespace YadroTest {

class ILine {
public:
    virtual ~ILine() = default;
    virtual bool Read(int& data) = 0;
    virtual bool ReadAndMove(int& data) = 0;
    virtual void WriteAndMove(int data) = 0;  // Write without move looks strange
    virtual bool Move(int delta) = 0;
    virtual bool MoveForward() = 0;
    virtual bool MoveBackward() = 0;
    virtual int GetSize() = 0;
    virtual void MoveToBegin() = 0;
    virtual long long CalcTime() const = 0;
    virtual void RunLine() = 0;  // We suggest that there is no point in keeping multiple lines on
    virtual void StopLine() = 0;
};

}  // namespace YadroTest