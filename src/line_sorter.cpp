#include "line_sorter.hpp"
#include <algorithm>
#include <vector>
#include <queue>

namespace YadroTest {
LineSorter::LineSorter(std::unique_ptr<ILine> inLine, std::unique_ptr<ILine> outLine,
                       std::function<std::unique_ptr<ILine>(int)> makeTempFunction, int maxSize)
    : InLine_(std::move(inLine)),
      OutLine_(std::move(outLine)),
      MakeTempFunction_(makeTempFunction),
      Id_(0) {
    std::vector<int> temp(maxSize);
    int counter = 0;
    int buffer = 0;
    while (InLine_->ReadAndMove(buffer)) {
        temp[counter] = buffer;
        ++counter;

        if (counter == maxSize) {
            std::unique_ptr tempLine = MakeTempFunction_(Id_);
            std::sort(temp.begin(), temp.end());

            for (int element : temp) {
                tempLine->WriteAndMove(element);
            }

            tempLine->MoveToBegin();
            tempLine->StopLine();
            TemporaryLines_.push_back(std::move(tempLine));
            counter = 0;
            ++Id_;
        }
    }

    if (counter > 0) {
        std::unique_ptr tempLine = MakeTempFunction_(Id_);
        std::sort(temp.begin(), temp.begin() + counter);
        for (int i = 0; i < counter; ++i) {
            tempLine->WriteAndMove(temp[i]);
        }

        tempLine->MoveToBegin();
        TemporaryLines_.push_back(std::move(tempLine));
        ++Id_;
    }
}

void LineSorter::Merge_(std::unique_ptr<ILine>& out, std::unique_ptr<ILine>& left,
                        std::unique_ptr<ILine>& right) {
    int leftValue = 0;
    int rightValue = 0;

    left->RunLine();
    right->RunLine();

    while (left->Read(leftValue) && right->Read(rightValue)) {
        if (leftValue < rightValue) {
            out->WriteAndMove(leftValue);
            left->MoveForward();
        } else {
            out->WriteAndMove(rightValue);
            right->MoveForward();
        }
    }

    while (left->ReadAndMove(leftValue)) {
        out->WriteAndMove(leftValue);
    }

    while (right->ReadAndMove(rightValue)) {
        out->WriteAndMove(rightValue);
    }

    out->MoveToBegin();

    left->StopLine();
    right->StopLine();
    out->StopLine();
}

void LineSorter::MakeSort() {
    std::queue<int> tempLinesIdQueue;
    for (int i = 0; i < Id_; ++i) {
        tempLinesIdQueue.push(i);
    }

    while (tempLinesIdQueue.size() > 2) {
        int tempLineIdLeft = tempLinesIdQueue.front();
        tempLinesIdQueue.pop();

        int tempLineIdRight = tempLinesIdQueue.front();
        tempLinesIdQueue.pop();

        std::unique_ptr tempLine = MakeTempFunction_(Id_);
        Merge_(tempLine, TemporaryLines_[tempLineIdLeft], TemporaryLines_[tempLineIdRight]);

        TemporaryLines_.push_back(std::move(tempLine));
        tempLinesIdQueue.push(Id_);
        ++Id_;
    }
    if (tempLinesIdQueue.size() == 2) {
        int tempLineIdLeft = tempLinesIdQueue.front();
        tempLinesIdQueue.pop();

        int tempLineIdRight = tempLinesIdQueue.front();
        tempLinesIdQueue.pop();

        Merge_(OutLine_, TemporaryLines_[tempLineIdLeft], TemporaryLines_[tempLineIdRight]);
    } else if (tempLinesIdQueue.size() == 1) {
        int buffer = 0;
        int tempLineId = tempLinesIdQueue.front();
        tempLinesIdQueue.pop();
        while (TemporaryLines_[tempLineId]->ReadAndMove(buffer)) {
            OutLine_->WriteAndMove(buffer);
        }
    }
}

long long LineSorter::CalcTime() const {
    long long time = 0;
    for (const std::unique_ptr<ILine>& current : TemporaryLines_) {
        time += current->CalcTime();
    }

    time += InLine_->CalcTime();
    time += OutLine_->CalcTime();

    return time;
}

int LineSorter::GetInSize() {
    return InLine_->GetSize();
}

int LineSorter::GetOutSize() {
    return OutLine_->GetSize();
}

}  // namespace YadroTest