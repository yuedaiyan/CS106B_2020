#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

struct BackpackItem {
    int survivalValue;  // You can assume this value will always >= 0
    int weight;         // You can assume this value will always >= 0
};

// 递归函数: curValue 记录重量, index 记录哪些物品已经被放入
// 返回: 只返最大值
int fillBackpackHelper(Vector<BackpackItem>& items, int capacityRemaining, int curValue, int index) {
    // Base cases:
    // • No remaining capacity in the knapsack → return O (not a valid combination with weight <= 5)
    // • No more items to choose from → return current value
    if (capacityRemaining < 0) {
        return 0;
    }
    if (index == items.size()) {
        return curValue;
    }

    // Recursive case:
    // • Select an unconsidered item based on the index.
    // • Recursively calculate the values both with and without the item.
    // • Return the higher value.
    int excludeCurrItem = fillBackpackHelper(items, capacityRemaining, curValue, index + 1);

    BackpackItem currItem = items[index];
    int includeCurrItem = fillBackpackHelper(items, capacityRemaining - currItem.weight, curValue + currItem.survivalValue, index + 1);

    return max(excludeCurrItem, includeCurrItem);
}

// 主函数: 根据背包限制求最优组合
int fillBackpack(Vector<BackpackItem>& items, int targetWeight) {
    return fillBackpackHelper(items, targetWeight, 0, 0);
}


void knapsackDemo() {
    // solution: 44
    // int targetWeight = 18;
    // Vector<BackpackItem> items = {
    //     {12, 4},
    //     {10,6},
    //     {8, 5},
    //     {11, 7},
    //     {14, 3},
    //     {7, 1},
    //     {9, 6}
    // };

    // solution: 67
    int targetWeight = 25;
    Vector<BackpackItem> items = {
        { 5, 6 },
        { 20, 15 },
        { 3, 11 },
        { 50, 12 },
        { 5, 6 },
        { 4, 11 },
        { 15, 13 },
        { 12, 7 },
        { 6, 17 },
        { 7, 13 }
    };

    // solution : 7
    // int targetWeight = 5;
    // Vector<BackpackItem> items = {
    //     { 3, 2 },
    //     { 4, 3 },
    //     { 5, 4 },
    //     { 6, 5 }
    // };

    Vector<BackpackItem> backpack;

    cout << "Best solution has a value of: "
         // 普通版本:
         << fillBackpack(items, targetWeight) << endl;
    cout << endl;

    cout << "Original objects: " << endl;
    for (BackpackItem item : items) {
        cout << "Survival Value: " << item.survivalValue << endl;
        cout << "Weight: " << item.weight << endl;
        cout << endl;
    }

    cout << "Target weight: " << targetWeight << endl << endl;

    cout << "Best backpack: " << endl;
    for (BackpackItem item: backpack) {
        cout << "Survival Value: " << item.survivalValue << endl;
        cout << "Weight: " << item.weight << endl;
        cout << endl;
    }
}
