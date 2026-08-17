#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

struct BackpackItem {
    int survivalValue;  // You can assume this value will always >= 0
    int weight;         // You can assume this value will always >= 0
};

// 辅助函数:求背包价值
int getBackpackValue(Vector<BackpackItem> backpack) {
    int result = 0;
    for (BackpackItem curr : backpack) {
        result += curr.survivalValue;
    }
    return result;
}

// recursive function
Vector<BackpackItem> fillBackpackHelper_upgrade(
    Vector<BackpackItem>& items,
    int capacityRemaining,
    int index,
    Vector<BackpackItem>& bestBackpackArrangement) {

    // Base cases:
    if (capacityRemaining < 0) {
        return { };
    }
    if (index == items.size()) {
        return bestBackpackArrangement;
    }

    // Recursive case:
    Vector<BackpackItem> excludeCurrItem = fillBackpackHelper_upgrade(items, capacityRemaining, index + 1, bestBackpackArrangement);

    BackpackItem currItem = items[index];
    bestBackpackArrangement.insert(bestBackpackArrangement.size(), currItem);
    Vector<BackpackItem> includeCurrItem = fillBackpackHelper_upgrade(items, capacityRemaining - currItem.weight, index + 1, bestBackpackArrangement);

    // reset
    bestBackpackArrangement.remove(bestBackpackArrangement.size() - 1);

    // return max value backpack
    if (getBackpackValue(excludeCurrItem) > getBackpackValue(includeCurrItem)) {
        return excludeCurrItem;
    } else {
        return includeCurrItem;
    }
}

int fillBackpack_upgrade(Vector<BackpackItem>& items, int targetWeight, Vector<BackpackItem>& bestBackpackArrangement) {
    Vector<BackpackItem> result = fillBackpackHelper_upgrade(items, targetWeight, 0, bestBackpackArrangement);

    // cout
    cout << endl;
    cerr << "result size: " << result.size() << endl;
    cerr << "upgrade cout start" << endl;
    for (BackpackItem item : result) {
        cout << "Survival Value: " << item.survivalValue
             << ", Weight: " << item.weight << endl;
    }
    cerr << "upgrade cout closed" << endl;

    return getBackpackValue(result);
}

void knapsackDemo_upgrade() {
    // solution: 44
    // int targetWeight = 18;
    // Vector<BackpackItem> items = {
    //     { 12, 4 },
    //     { 10, 6 },
    //     { 8, 5 },
    //     { 11, 7 },
    //     { 14, 3 },
    //     { 7, 1 },
    //     { 9, 6 }
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
         << fillBackpack_upgrade(items, targetWeight, backpack) << endl;
    cout << endl;

    cout << "Original objects: " << endl;
    for (BackpackItem item : items) {
        cout << "Survival Value: " << item.survivalValue << endl;
        cout << "Weight: " << item.weight << endl;
        cout << endl;
    }

    cout << "Target weight: " << targetWeight << endl
         << endl;

    cout << "Best backpack: " << endl;
    for (BackpackItem item : backpack) {
        cout << "Survival Value: " << item.survivalValue << endl;
        cout << "Weight: " << item.weight << endl;
        cout << endl;
    }
}
