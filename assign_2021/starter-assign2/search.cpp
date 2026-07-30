// 搜索程序(根据网页内容搜索网址)
#include "search.h"
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <ctype.h>
#include <fstream>
#include <iostream>

using namespace std;

// 清除传入字符串的头部和尾部标点符号(ctype.h ispunct()),不处理字符串内部的标点符号, 同时所有字符转换为小写
string cleanToken(string str) {
    // remove from start
    int strLength = str.length();
    int startRemoveIndex = 0;
    for (int i = 0; i < strLength; i++) {
        if (ispunct(str[i])) {
            startRemoveIndex++;
        } else {
            break;
        }
    }

    // remove from end
    int endRemoveIndex = 0;
    for (int i = strLength - 1; i > 0; i--) {
        if (ispunct(str[i])) {
            endRemoveIndex++;
        } else {
            break;
        }
    }
    // cout << endl;
    // cout << "string: " << str << "\nStart remove index: " << startRemoveIndex << "\nEnd remove index: " << endRemoveIndex << endl;
    // cout << "string before remove: " << str << endl;

    string result = "";
    bool isIncludeAlpha = false;
    for (int i = startRemoveIndex; i < strLength - endRemoveIndex; i++) {
        if (isalpha(str[i])) {
            isIncludeAlpha = true;
        }
        result += str[i];
    }

    // Confirm the token contains at least one letter character
    if (!isIncludeAlpha) {
        return "";
    }

    // cout << "string after remove: " << result << endl;

    result = toLowerCase(result);

    // cout << "string lowercase: " << result << endl;
    // cout << endl;
    return result;
}

// 从字符串中提取所有非重复 token
Set<string> gatherTokens(string text) {
    Set<string> tokens;
    Vector<string> v = stringSplit(text, " ");
    for (string token : v) {
        token = cleanToken(token);
        if (token != "") {
            tokens.add(token);
        }
    }
    // cout << endl;
    // cout << "string to token: " << "\nstring: " << text << "\ntoken: " << tokens.toString() << endl;
    // cout << endl;
    return tokens;
}

/* 建立文件 token-网址 索引系统, 并返回 int 索引数量
 * 索引系统形如:
 * {
 * {"apple":"url_1","url_2"},
 * {"peack":"url_2}
 * }
 */
int buildIndex(string dbfile, Map<string, Set<string>>& index) {
    cout << "Stand by while building index..." << endl;

    ifstream in;
    if (!openFile(in, dbfile)) {
        error("Cannot open file named " + dbfile);
    }
    Vector<string> lines;
    readEntireFile(in, lines);

    int urlNum = lines.size() / 2;
    for (int i = 0; i < urlNum; i++) {
        int currUrl = i * 2;
        Set<string> tokenSet = gatherTokens(lines[currUrl + 1]);

        for (const string& token : tokenSet) {
            Set<string> newUrls = index.get(token);
            newUrls.add(lines[currUrl]);
            index.put(token, newUrls);
        }
    }
    // cout << endl;
    // cout << endl;
    // cout << index.toString() << endl;
    // cout << endl;
    // cout << endl;
    return urlNum;
}

// 根据 query(1或多) 在 index 中查找对应的 Set<string>
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {

    Set<string> result;
    Vector<string> searchTerms = stringSplit(query, " ");
    Vector<string> cleanedSearchTerms;

    cout << endl;
    cout << endl;
    cout << "search query: \n"
         << query << endl;

    // clean searchTerms
    for (string& term : searchTerms) {
        string cleanedTerm = cleanToken(term);
        if (cleanedTerm != "") {
            cleanedSearchTerms.add(term);
        }
    }

    cout << "cleanedSearchTerms: " << cleanedSearchTerms << endl;
    for (string& term : cleanedSearchTerms) {
        cout << "term:" << term << endl;

        // single situation
        if (cleanedSearchTerms.size() == 1) {
            result = index.get(query);
            cout << "search result:\n"
                 << result.toString() << endl;
            cout << endl;
            cout << endl;
            return result;
            // compound situation
        } else {
            string basicTerm = cleanedSearchTerms.get(0);
            cleanedSearchTerms.remove(0);

            result = index.get(basicTerm);
            cout << "basic term( " << basicTerm << " )'s Set:\n"
                 << result << endl;
            cout << "result:\n"
                 << result << endl;

            cout << "cleanedSearchTerms in compound situation: " << cleanedSearchTerms << endl;
            for (string term : cleanedSearchTerms) {
                cout << "for loop: " << term << endl;

                if (term[0] != '+' && term[0] != '-') {
                    Set<string> resultAdd = index.get(term);
                    cout << "or term( " << term << " )'s Set:\n"
                         << resultAdd << endl;
                    result += resultAdd;
                    cout << "result:\n"
                         << result << endl;

                } else if (term[0] == '+') {
                    cout << "go into =='+'" << endl;
                    cout << "before substr(1): " << term << endl;
                    term = term.substr(1);
                    cout << "after substr(1): " << term << endl;
                    Set<string> resultAdd = index.get(term);
                    cout << "term( " << term << " )'s Set:\n"
                         << resultAdd << endl;
                    result *= resultAdd;
                    cout << "result after add( " << term << " ):\n"
                         << result << endl;

                } else if (term[0] == '-') {
                    cout << "go into =='-'" << endl;
                    cout << "before substr(1): " << term << endl;
                    term = term.substr(1);
                    cout << "after substr(1): " << term << endl;
                    Set<string> resultSub = index.get(term);
                    cout << "term( " << term << " )'s Set:\n"
                         << resultSub << endl;
                    result -= resultSub;
                    cout << "result after sub( " << term << " ):\n"
                         << result << endl;
                }
            }
            cout << "return result: \n"
                 << result.toString() << endl;
            cout << endl;
            cout << endl;
            return result;
        }
    }
    // will never use
    return result;
}

// main search engine
void searchEngine(string dbfile) {
    Map<string, Set<string>> index;
    int urlsNum = buildIndex(dbfile, index);
    cout << "Inexed " << urlsNum << " pages containing " << index.size() << " unique terms" << endl;

    while (1) {
        cout << endl;
        cout << endl;
        string query = getLine("Enter query sentence (RETURN/ENTER to quit): ");
        if (query == "") {
            return;
        }
        Set<string> result = findQueryMatches(index, query);
        cout << "Found " << result.size() << " matching pages" << endl;
        for (const string& str : result) {
            cout << str << endl;
        }
    }
}

/* * * * * * Test Cases * * * * * */
PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}
PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}
PROVIDED_TEST("cleanToken on non-word strings (no letters)") {
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}
STUDENT_TEST("cleanToken on strings whit no change") {
    EXPECT_EQUAL(cleanToken("section's"), "section's");
    EXPECT_EQUAL(cleanToken("section-10"), "section-10");
}
STUDENT_TEST("cleanToken on strings whit punct in str") {
    EXPECT_EQUAL(cleanToken("i eat apple section's"), "i eat apple section's");
    EXPECT_EQUAL(cleanToken("i eat apple section's."), "i eat apple section's");
    EXPECT_EQUAL(cleanToken("i eat apple, section's."), "i eat apple, section's");
}
STUDENT_TEST("cleanToken on strings whit sace") {
    EXPECT_EQUAL(cleanToken(" section-10"), " section-10");
    EXPECT_EQUAL(cleanToken("section-10 "), "section-10 ");
    EXPECT_EQUAL(cleanToken("section-10 -"), "section-10 ");
    EXPECT_EQUAL(cleanToken("section-10 ------"), "section-10 ");
    EXPECT_EQUAL(cleanToken("------------- section-10 ------"), " section-10 ");
    EXPECT_EQUAL(cleanToken("se cti on-10 "), "se cti on-10 ");
    EXPECT_EQUAL(cleanToken("se  cti  on-10 "), "se  cti  on-10 ");
}
STUDENT_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("section"), "section");
    EXPECT_EQUAL(cleanToken("section!"), "section");
    EXPECT_EQUAL(cleanToken("<<section>>"), "section");
}
PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = { "go", "gophers" };
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}
PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = { "i", "love", "cs*106b" };
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}
PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}
STUDENT_TEST("gatherTokens with normal sentence") {
    Set<string> expected = { "i", "like", "eat", "apple" };
    EXPECT_EQUAL(gatherTokens("I like eat Apple "), expected);
}
STUDENT_TEST("gatherTokens with complex sentence") {
    Set<string> expected = { "i", "like", "eat", "apple", "do", "you" };
    EXPECT_EQUAL(gatherTokens("I -like- eat 'Apple' !!! Do you?  "), expected);
}
STUDENT_TEST("gatherTokens with empty input") {
    Set<string> expected = { };
    EXPECT_EQUAL(gatherTokens(" "), expected);
}
STUDENT_TEST("buildIndex from tiny.txt, include test") {
    Map<string, Set<string>> index;
    (void)buildIndex("res/tiny.txt", index);
    EXPECT(index.containsKey("red"));
    EXPECT(index.containsKey("blue"));
    EXPECT(index.containsKey("two"));
    EXPECT(index.containsKey("green"));
}
STUDENT_TEST("buildIndex from tiny.txt, time test") {
    Map<string, Set<string>> index;
    TIME_OPERATION(0, (void)buildIndex("res/tiny.txt", index));
}
PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}
PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}
PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}