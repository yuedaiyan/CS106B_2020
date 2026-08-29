/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
// #include "cs106libAll.h"
#include "recursion.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <iostream> // for cout, endl
#include <string> // for string class

using namespace std;

// 清除字符串中除括号的所有字符,按原始顺寻输入由括号组成的字符串
string operatorsFrom(string str) {
    if (str.size() == 0) {
        return "";
    } else {
        char c = str[0];
        str = str.substr(1);
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            return c + operatorsFrom(str);
        } else {
            return operatorsFrom(str);
        }
    }
}

// 辅助函数:测试两个括号字符是否匹配
bool parenthesesHelp(char c1, char c2) {
    if (c1 == '(' || c1 == '[' || c1 == '{') {
        if (c1 == '(') {
            if (c2 == ')') {
                return true;
            }
        } else if (c1 == '[') {
            if (c2 == ']') {
                return true;
            }
        } else if (c1 == '{') {
            if (c2 == '}') {
                return true;
            }
        } else {
            return false;
        }
    }
    error("paraenthesesHepl(): ");
    error("程序应该永远不会执行到这里!");
    return false;
}

// 递归函数: 接受仅由三种括号组成的字符串, 检测是否匹配, bool输出
bool operatorsAreMatched(string ops) {

    cerr << "before erase: " << ops << endl;
    if (ops.size() == 0) {
        return true;
    } else {
        size_t index;
        index = ops.find("()");
        if (index != string::npos) {
            ops.erase(index, 2);
            return operatorsAreMatched(ops);
        }
        index = ops.find("[]");
        if (index != string::npos) {
            ops.erase(index, 2);
            return operatorsAreMatched(ops);
        }
        index = ops.find("{}");
        if (index != string::npos) {
            ops.erase(index, 2);
            return operatorsAreMatched(ops);
        }

        /*
        // 老版本代码,同样非常好,不过用了for(),可能不够符合题意,但一样优雅
        int opsLength = ops.length();
        for (int i = 0; i < opsLength - 1; i++) {
            string ss = ops.substr(i, 2);
            if (ss == "()" || ss == "[]" || ss == "{}") {
                ops.erase(i, 2);
                cerr << "after  erase: " << ops << endl;
                return operatorsAreMatched(ops);
            }
        }
        return false;
        */
    }
    error("operatorsAreMatched(): ");
    error("程序应该永远不会执行到这里!");
    return false;
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    cerr << "---------" << endl;
    cerr << str << endl;
    string ops = operatorsFrom(str);
    cout << endl;
    cerr << ops << endl;
    return operatorsAreMatched(ops);
}

/* * * * * * Test Cases * * * * * */
STUDENT_TEST("LEARN substr()") {
    cout << endl;
    string str = "hello";
    char curr = str[0];
    str = str.substr(1);
    cout << "c: " << curr << endl;
    cout << "substr: " << str << endl;
    EXPECT(true);
}

STUDENT_TEST("LEARN index separate string") {
    cout << endl;
    string str = "0123456";
    size_t index = 3;
    str.erase(index, 1);
    string v1 = str.substr(0, index);
    string v2 = str.substr(index);
    cerr << v1 << endl;
    cerr << v2 << endl;
    EXPECT(true);
}

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

STUDENT_TEST("operatorsFrom(): more text") {
    EXPECT_EQUAL(operatorsFrom("vec[!@#$!3]!#@@@!#@!$(SVSH)SSSVD(@#$!@#%)(JBJCS)"), "[]()()()");
    EXPECT_EQUAL(operatorsFrom("vec[3]()}}}"), "[]()}}}");
}

STUDENT_TEST("operatorsFrom(): combination ") {
    EXPECT_EQUAL(operatorsFrom("(13412)3{1341213124134[(13241341)]134123421}13414312"), "(){[()]}");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    cout << endl;
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    cout << endl;
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    cout << endl;
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("isBalanced() test: ") {
    EXPECT(isBalanced("()(222222)(){{qe[(ahhhd())]}}"));
    string test1 = "     if (ops.size() == 0) { return true; } else { int opsLength = ops.length(); for (int i = 0; i < opsLength - 1; i++) { string ss = ops.substr(i, 2); } return false; } ";
    EXPECT(isBalanced(test1));
    string test2 = " void confirmFunctionPrototypes() { string str; int i = 0; bool b; b = isBalanced(str); str = operatorsFrom(str); b = operatorsAreMatched(str); GPoint pt; GWindow win; drawSierpinskiTriangle(win, pt, pt, pt, i); Queue<int> q; Vector<Queue<int>> v; q = binaryMerge(q, q); q = naiveMultiMerge(v); q = recMultiMerge(v); }  ";
    EXPECT(isBalanced(test2));
}