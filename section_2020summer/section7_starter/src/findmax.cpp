/*
 * CS106B Section Handout Test Harness: Section 7
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "treenode.h"
#include "utility.h"
#include "vector.h"
using namespace std;

/*
 * Ultimate and Penultimate Values (Code Writing)
 * --------------------------------------------------------
 * Write a function that takes as input a pointer to the root
 * of a (nonempty) binary search tree, then returns a pointer
 * to the node containing the largest value in the BST. Then,
 * write a function that takes as input a pointer to the root
 * of a BST containing at least two nodes, then returns a
 * pointer to the node containing the second-largest value
 * in the BST.
 */

/*
TreeNode* biggestNodeIn(TreeNode* root) {
    // if (root == nullptr)
    //     return nullptr;

    TreeNode* maxLeft = nullptr;
    TreeNode* maxRight = nullptr;

    if (root->left != nullptr) {
        maxLeft = biggestNodeIn(root->left);
    }
    if (root->right != nullptr) {
        maxRight = biggestNodeIn(root->right);
    }

    TreeNode* maxChildren = nullptr;
    if (maxLeft != nullptr && maxRight != nullptr)
        maxChildren = maxLeft->data > maxRight->data ? maxLeft : maxRight;
    else if (maxLeft == nullptr)
        maxChildren = maxRight;
    else
        maxChildren = maxLeft;

    if (maxChildren != nullptr)
        return root->data > maxChildren->data ? root : maxChildren;
    return root;
}
 */
TreeNode *biggestNodeIn(TreeNode *root) {
    if (root == nullptr) error("error: root == nullptr");

    return root->right == nullptr ? root : biggestNodeIn(root->right);
}

TreeNode *secondBiggestNodeIn(TreeNode *root) {
    if (root == nullptr) error("error: root == nullptr");

    // only one node at begining
    if (root->right == nullptr) {
        if (root->left != nullptr) return biggestNodeIn(root->left);
        if (root->left == nullptr) return root;
    }

    if (root->right != nullptr && root->right->right == nullptr) {
        if (root->left != nullptr)
            return root;
        else {
            if (root->right->left == nullptr) return root;
            if (root->right->left != nullptr) return biggestNodeIn(root->right->left);
        }
    }

    return secondBiggestNodeIn(root->right);
}

PROVIDED_TEST("Simple tests for biggestNodeIn function"){
    TreeNode *tree = createTreeFromVector({/* Level 1 */ 5});
    EXPECT_EQUAL(tree, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6});

    EXPECT_EQUAL(tree->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, EMPTY});
    EXPECT_EQUAL(tree->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9});
    EXPECT_EQUAL(tree->right->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, EMPTY});
    EXPECT_EQUAL(tree->right->right, biggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9, /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, 10});
    EXPECT_EQUAL(tree->right->right->right, biggestNodeIn(tree));

    freeTree(tree);
}

PROVIDED_TEST("Simple tests for secondBiggestNodeIn function") {
    TreeNode *tree = createTreeFromVector({/* Level 1 */ 5, 3, EMPTY});
    EXPECT_EQUAL(tree->left, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6});
    EXPECT_EQUAL(tree, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector(
        {/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, EMPTY});
    EXPECT_EQUAL(tree, secondBiggestNodeIn(tree));

    freeTree(tree);
    tree = createTreeFromVector({/* Level 1 */ 5, /* Level 2 */ 3, 6, /* Level 3 */ 1, 4, EMPTY, 9});
    EXPECT_EQUAL(tree->right, secondBiggestNodeIn(tree));

    freeTree(tree);
    // clang-format off
    tree = createTreeFromVector({/* Level 1 */ 5,
                                 /* Level 2 */ 3, 6,
                                 /* Level 3 */ 1, 4, EMPTY, 9,
                                 /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, EMPTY});
    // clang-format on
    EXPECT_EQUAL(tree->right->right->left, secondBiggestNodeIn(tree));

    freeTree(tree);
    // clang-format off
    tree = createTreeFromVector({/* Level 1 */ 5,
                                 /* Level 2 */ 3, 6,
                                 /* Level 3 */ 1, 4, EMPTY, 9,
                                 /* Level 4 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 8, 10});
    // clang-format on
    EXPECT_EQUAL(tree->right->right, secondBiggestNodeIn(tree));

    freeTree(tree);
}
