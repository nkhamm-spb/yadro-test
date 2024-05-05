#include "line_sorting_emulate.hpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>

const std::string inFilePath = "../../input.txt";
const std::string outFilePath = "../../out.txt";

static std::mt19937 mt(time(nullptr));

long long SortSomeNumbers(int num, int maxSize, std::vector<int> &in, std::vector<int> &out,
                          const std::string &config = "") {
    std::fstream inputFile(inFilePath, std::ios::out | std::ios::trunc | std::ios::binary);
    for (int i = 0; i < num; ++i) {
        int val = static_cast<int>(mt());
        inputFile.write(reinterpret_cast<const char *>(&val), sizeof(int));
        in.push_back(val);
    }
    std::sort(in.begin(), in.end());
    inputFile.close();

    YadroTest::LineSortingEmulate LineSorter(inFilePath, outFilePath, maxSize, config);
    long long sortTime = LineSorter.MakeSort();
    std::fstream outputFile(outFilePath, std::ios::in | std::ios::binary);
    for (int i = 0, size = LineSorter.GetOutSize(); i < size; ++i) {
        int val;
        outputFile.read(reinterpret_cast<char *>(&val), sizeof(int));
        out.push_back(val);
    }
    
    return sortTime;
}

TEST(YadroSortTest, EmptyFile) {
    std::vector<int> in, out;
    SortSomeNumbers(0, 1, in, out);
    ASSERT_EQ(true, out.empty());
}

TEST(YadroSortTest, Test100nums) {
    std::vector<int> in, out;
    SortSomeNumbers(100, 1, in, out);
    ASSERT_EQ(in, out);
}

TEST(YadroSortTest, Test100000nums) {
    std::vector<int> in, out;
    SortSomeNumbers(100000, 1, in, out);
    ASSERT_EQ(in, out);
}

TEST(YadroSortTest, BigMaxSize) {
    std::vector<int> in, out;
    SortSomeNumbers(10, 10000, in, out);
    ASSERT_EQ(in, out);
}

TEST(YadroSortTest, Config) {
    std::vector<int> in, out;

    std::ofstream configFile("../../config.txt");
    configFile << "5 4 2";
    configFile.close();

    long long sortTime = SortSomeNumbers(10, 10000, in, out, "../../config.txt");

    ASSERT_EQ(280, sortTime);
    ASSERT_EQ(in, out);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}