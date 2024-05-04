#include "line_sorting_emulate.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv) {
    const int maxSize = 1024;

    std::string inFilePath;
    std::string outFilePath;
    std::cin >> inFilePath >> outFilePath;

    YadroTest::LineSortingEmulate LineSorter(inFilePath, outFilePath, maxSize);
    LineSorter.MakeSort();
}