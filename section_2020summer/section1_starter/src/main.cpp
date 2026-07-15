#include "console.h"
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include <iostream>
using namespace std;

void mirror(Grid<int>& nums);
void mirror_main() {
    cout << "mirror_main() run in main.cpp" << endl;
    Grid<int> g = { { 6, 1, 9, 4 },
        { -2, 5, 8, 12 },
        { 14, 39, -6, 18 },
        { 21, 55, 73, -3 } };
    mirror(g);
}
int crossSum(const Grid<int>& g, int row, int col);
void crossSum_main() {
    cout << "crossSum_main() run in main.cpp" << endl;
    Grid<int> g = { { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 } };

    Grid<int> h = { { 1, 6, 5, 4, 2, 73, 2, 9, 0, -4, 24, 7 },
        { 2, 43, 64, -53, 8, 4, 6, 78, 5, 1, 4, -6 },
        { 7, 8, 9, 10, 11, -12, 5, 65, 4, 0, -6, 13 },
        { 14, 52, 6, 8, 4, 2, -6, 5, 8, 3, 6, -33 } };
    crossSum(h, 2, 8);
}

int main() {
    // mirror_main();
    crossSum_main();

    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    return 0;
}