# Practice Diagnostic

```
https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1208/assessments/diagnostic/practice/
```

本.md文件保留第一遍独立完成答案,qt项目中部分题目代码已经修改.

总分:

```
30.5/50
```

---

## Problem 1: Interpreting Code (10 points)

### Part A: Analyzing Code Output and Runtime (7 points)

原始未订正答案:

```
1.
The Big-O for function1 is: O(1)
The Big-O for function2 is: O(1)
The Big-O for function3 is: O(N)
The Big-O for function4 is: O(N)

2.
Could function1 have produced the provided output? No
Could function2 have produced the provided output? Yes
Could function3 have produced the provided output? Yes
Could function4 have produced the provided output? Yes

3.
The timing results and output were produced by:
function4

Your justification here (50 words or less):
通过第一题和第二题的内容的判断，
我可以锁定答案必然在函数3和函数4之中。
同时，函数3的Set建立时，时间为O(log N)；函数3和函数4的.get都是O(N)。
结合输出的时间来看，整体呈现，并没有对数函数的收敛感，因此判断为函数4。
```

订正答案:

```
1.  The runtimes are as follows:
function1 runs in time O(n).
function2 runs in time O(n).
function3 runs in time O(n log n).
function4 runs in time O(n^2).

Some explanations: In function1, we do n pushes followed by n pops. The cost of each stack operation is O(1), so this means we’re doing 2n operations at an effective cost of O(1) each, for a net total of O(n). The same is true about queue operations: each one takes time O(1), which is why function2 takes time O(n) as well.
For function3, inserting an element into a set takes time O(log n). This means that the cost of inserting n elements is O(n log n). The cost of iterating over the set is also O(n) so the net runtime is O(n log n).
For function4, adding n elements to the end of a vector takes time O(n). However, removing from the front of a vector with n elements also takes time O(n), since we have to shift all the other elements back one position. This means that the overall runtime is O(n^2).

1.The answers: function1 cannot produce the given output. function2 will always produce this output. function3 will always produce this output. function4 will always produce this output.
Some explanations: In function1, since elements are stored in a stack, the last element popped is the first element pushed, which would always be zero. Therefore, we’d expect to see a column of zeros in the table, which doesn’t match what’s actually there.
In function2, the last element removed from the queue is the last element added to the queue, which, here, would be n – 1, matching the output.
In function3, the Set type stores its elements in sorted order. Iterating over the set, therefore, will visit the elements in ascending order, so the last element iterated over by the loop would be n – 1, matching the output.

Finally, in function4, we remove elements from the vector in the reverse order in which they’re added, matching the queue’s ordering and making the last element visited exactly n – 1.
1.  First, notice that the runtime appears to be O(n); doubling the size of the inputs roughly doubles the runtime. That leaves function1 and function2 as choices, and function1 has the wrong return value. Therefore, we must have run function2.
```

ChatGPT打分:

```
按这份标准答案严格评分，我会给你 1 / 7 分。你这题的主要问题非常集中：你把“单次操作的复杂度”和“整个函数的复杂度”混在了一起。
```

---

### Part B: Tracing a Recursive Function (3 points, 1 per part)

原始未订正答案:

```
a) The output of recursionMystery(8); is:
0 0 0 : 2 4 8

b) The output of recursionMystery(25); is:
1 0 0 1 : 3 6 12 25

c) The output of recursionMystery(46); is:
0 1 1 1 0 : 2 5 11 23 46
```

订正答案:

```
Call	Output
a) recursionMystery2(8);	0 0 0 : 2 4 8
b) recursionMystery2(25);	1 0 0 1 : 3 6 12 25
c) recursionMystery2(46);	0 1 1 1 0 : 2 5 11 23 46
```

ChatGPT 5.6 Sol 打分:

```
三小题全部正确，应该是 3 / 3 分。
```

## Problem 2: C++ Fundamentals (10 points)

原始未订正答案:

```cpp
// 辅助函数:返回指定数量的重复字符组成的字符串
string multiCharacter(string input, int times) {
    string result;
    for (int i = 0; i < times; i++) {
        result += input;
    }
    return result;
}

// 辅助函数:将字符串转换为首字母大写
void caseChange(string& input) {
    // 先将字母全部转换为小写
    input = toLowerCase(input);
    // 字符串首字符大写(如果是字母的话,不是字母不处理)
    if (isalpha(input[0])) {
        input[0] = toupper(input[0]);
    }
}

void printBox(Vector<string> lines, int width) {
    cout << multiCharacter("#", width) << endl;

    for (string line : lines) {
        // 移除前后空白
        line = trim(line);
        // 字母大小写变换
        caseChange(line);

        // 添加 '#' 相关格式
        string currLine = "#";
        currLine += line;
        int diff = width - currLine.length();
        currLine += multiCharacter(" ", diff);
        currLine[currLine.length() - 1] = '#';

        // print
        cout << currLine << endl;
    }

    cout << multiCharacter("#", width) << endl;
}
```

订正答案:

```cpp
void printPoundLine(int width) {
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
}

void printBox(Vector<string> lines, int width) {
    printPoundLine(width);
    for (string line: lines) {
        string output = "#";
        if (line != ""){
            output = output + toUpperCase(line.substr(0, 1)) + toLowerCase(line.substr(1));
        }
        while (output.length() < width - 1) {
            output += " ";
        }
        cout << output << "#" << endl;
    }
    printPoundLine(width);
}
```

ChatGPT 5.6 Sol 打分:

```
这份答案整体写得很好，核心逻辑是正确的，而且你自己设计了两个辅助函数，结构也很清晰。如果按 10 分制评分，我会给你大约 9/10；宽松一点甚至可以 9.5/10。
扣分点主要不是 box 的宽度计算，而是这一句：

line = trim(line);

题目没有要求删除每一行开头和结尾的空格，因此这实际上改变了原文件内容。
```

## Problem 3: ADTs (15 points)

原始未订正答案:

```cpp
// 辅助函数:分词用(同时提供小写转换功能)
Vector<string> tokenize(string& line) {
    // convert string to lowercase
    line = toLowerCase(line);
    Vector<string> strs = stringSplit(line, " ");
    for (string& str : strs) {
        // auto skip empty string
        if (str.length() == 0) {
            continue;
        }
        // clean string
        string cleaned;
        for (char ch : str) {
            if (isalpha(ch)) {
                cleaned += ch;
            }
        }
        str = cleaned;
    }
    return strs;
}

// 主函数: 根据句子组返回word2vec预测表
Map<string, Set<string>> predecessorMap(Vector<string>& input) {
    Map<string, Set<string>> result;
    // 获得总词组列表
    Vector<string> words;
    for (string line : input) {
        words += tokenize(line);
    }
    for (int i = 1; i < words.size() - 1; i++) {
        Set<string> curr = result.get(words[i]);
        curr.add(words[i - 1]);
        result.put(words[i], curr);
    }

    return result;
}
```

订正答案:

```cpp
Map<string, Set<string>> predecessorMap(Vector<string>& input) {
    Map<string, Set<string>> result;
    string lastWord;  // Most-recently-read string, initially empty as a sentinel.

    /* Loop over all lines */
    for (string line: input) {
        Vector<string> tokens = tokenize(line);
        for (string token: tokens) {
            if (token != "") {
                token = toLowerCase(token);
                if (lastWord != "") {
                    result[token].add(lastWord);
                }
                lastWord = token;
            }
        }
    }
    return result;
}
```

ChatGPT 5.6 Sol 打分:

```
我会给你的答案大约 11/15 分。如果老师对 off-by-one 比较宽松，可能到 12/15；如果测试非常严格，可能是 10/15。你的核心 ADT 思路是对的，主要不是“不会做”，而是两个边界条件让结果不完全正确。
```

## Problem 4: Recursion (10 points)

原始未订正答案:

```cpp
int countPaths(int street, int avenue) {
    // base case
    if (street == 1 && avenue == 1) {
        return 1;
    }
    // recursive case
    else {
        return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
    }
}
```

订正答案:

```cpp
int countPaths(int street, int avenue)
{
    // base case: if at western/southern wall, only one path to home from there
    if (street == 1 || avenue == 1) {
        return 1;
    }
    // recursive case: move either south or west
    return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
}
```

ChatGPT 5.6 Sol 打分:

```
如果这是一道 10 分的递归编程题，而你的核心代码就是刚才这样，我觉得大概率能拿到 5～7 分左右，具体取决于老师的评分 rubric。

因为你的思路其实已经完成了很大一部分：
* 知道使用递归解决问题：✓
* 正确写出了“两个方向路径数相加”：
    countPaths(street - 1, avenue) + countPaths(street, avenue - 1)
这是这道题的核心递推关系：✓
* 知道需要 base case：✓
* (1,1) 返回 1 这个理解本身也有道理：✓
* 但 base case 不完整，导致程序无限递归、最终崩溃：✗
* 因此测试无法通过：✗
```

## Problem 5: Recursive Backtracking (Bonus, Extra Credit, 5 points)

原始未订正答案:

```cpp
Vector<string> divideHelp(int depth, Lexicon& dict, string& s1, string& s2, int index) {
    Vector<string> result;
    int s2Length = s2.length();
    if (dict.contains(s1) && dict.contains(s2)) {
        cerr << string(20, '=') << " find s1, s2 " << string(20, '=') << endl;
        return Vector { s1, s2 };
    } else if (index == s2Length) {
        return { };
    }

    else {
        for (int i = index; i < s2Length; i++) {
            s1 += s2[i];
            s2.erase(i, 1);
            result = divideHelp(depth + 1, dict, s1, s2, i);
            if (!result.isEmpty()) {
                return result;
            }
            s2.insert(i, 1, s1[s1.length() - 1]);
            s1.erase(s1.length() - 1, 1);
        }
    }
    return result;
}

Vector<string> divide(Lexicon& dict, string word) {
    string s1 = "";
    string s2 = word;
    Vector<string> result = divideHelp(0, dict, s1, s2, 0);
    cerr << "find s1,s2: " << result.toString() << endl;
    return result;
}

```

订正答案:

```cpp
void divide(Lexicon& lex, string input) {
    divideHelper(lex, input, "", "");
}

bool divideHelper(Lexicon& lex, string input, string left, string right) {
    if (input.empty()) {
        if (lex.contains(left) && lex.contains(right)) {
            cout << left << " + " << right << endl;
            return true;
        } else {
            return false;
        }
    } else if (!lex.containsPrefix(left) || !lex.containsPrefix(right)) {
        return false;
    } else {
        char ch = input[0];
        string rest = input.substr(1);
        if (divideHelper(lex, rest, left + ch, right) || divideHelper(lex, rest, left, right + ch)) {
            return true;
        }
    }
    return false;
}
```

ChatGPT 5.6 Sol 打分:

```text
如果按这道题 Bonus 5 分题 的要求来判，我会给你的答案大约 3 / 5 分。你的递归 + 回溯核心其实已经写出来了，而且能够找到不少正确答案；主要丢分点不是“不会回溯”，而是没有按题目明确要求使用 Lexicon::containsPrefix 做剪枝，以及输出/函数接口没有完全符合题意。
```
