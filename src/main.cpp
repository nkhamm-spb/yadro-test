#include "line_sorting_emulate.hpp"

int main() {
    const int maxSize = 1;

    YadroTest::LineSortingEmulate LineSorter("/home/outcast/work/yadro-test/input.txt",
                                             "/home/outcast/work/yadro-test/out.txt", maxSize);
    LineSorter.MakeSort();
}