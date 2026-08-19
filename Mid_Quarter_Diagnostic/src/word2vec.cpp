#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
#include "console.h"
#include "error.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"

#include <cctype>

using namespace std;

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

    for (int i = 1; i < words.size(); i++) {
        Set<string> curr = result.get(words[i]);
        curr.add(words[i - 1]);
        result.put(words[i], curr);
    }

    return result;
}

STUDENT_TEST("tokenize test: ") {
    string str_1 = "hello joe.";
    Vector<string> result_1 = { "hello", "joe" };
    EXPECT_EQUAL(tokenize(str_1), result_1);

    string str_2 = "Ask what you can do for your country, ask";
    Vector<string> result_2 = { "ask", "what", "you", "can", "do", "for", "your", "country", "ask" };
    EXPECT_EQUAL(tokenize(str_2), result_2);

    string str_3 = "hello joe. 1234";
    Vector<string> result_3 = { "hello", "joe", "" };
    EXPECT_EQUAL(tokenize(str_3), result_3);
}

STUDENT_TEST("Chat GPT 5.6 sol test: ") {
    Vector<string> input = { "hello world" };
    Map<string, Set<string>> expected = { { "world", { "hello" } } };
    EXPECT_EQUAL(predecessorMap(input), expected);
}

STUDENT_TEST("predecessorMap test: ") {
    cout << endl;
    cerr << string(20, '-') << endl;
    Vector<string> string_1 = { "“Ask not what your country can do for you;", "ask what you can do for your country,”" };
    cerr << string_1.toString() << endl;

    Map<string, Set<string>>
        result_1 = {
            { "not", { "ask" } },
            { "what", { "not", "ask" } },
            { "your", { "what", "for" } },
            { "country", { "your" } },
            { "can", { "country", "you" } },
            { "do", { "can" } },
            { "for", { "do" } },
            { "you", { "for", "what" } },
            { "ask", { "you" } }
        };

    cerr << result_1.toString() << endl;
    Map<string, Set<string>> resultOfFunction = predecessorMap(string_1);
    EXPECT_EQUAL(resultOfFunction, result_1);

    cerr << string(20, '-') << endl;
    cout << resultOfFunction.toString();
    cout << endl;
    cerr << string(20, '-') << endl;
}