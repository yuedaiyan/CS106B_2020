#include "console.h"
#include "filelib.h"
#include "map.h"
#include "queue.h"
#include "set.h"
#include "simpio.h"
#include "stack.h"
#include "strlib.h"
#include <fstream>
#include <iostream>

using namespace std;

void populateDictionary(Set<string>& dictionary, string filename);
void wordLadderProgram();
Stack<string> findWordLadder(string startingWord, string destinationWord, Set<string>& dictionary);
Set<string> generateNeighboringWords(string currentWord, Set<string>& dictionary);

// 用于个人理解 Map 对象的自动排序功能
void learnMap() {
    Map<char, int> m;

    cout << "map: " << m << endl;
    m['k'] += 2;
    cout << "map: " << m << endl;
    m['k'] += 2;
    cout << "map: " << m << endl;
    m.put('b', 1);
    cout << "map: " << m << endl;
    m.put('c', 1);
    cout << "map: " << m << endl;
    m.put('a', 1);
    cout << "map: " << m << endl;
}

// 测试 Map 对象的自动排序性质,可以帮助我们实现英文字母排序功能
void sortChar() {
    string str = "banana";
    Map<char, int> m;
    cout << "map: " << m << endl;
    for (char c : str) {
        m[c] += 1;
    }
    for (char c : m) {
        for (int i = 0; i < m[c]; i++) {
            cout << c;
        }
    }
    cout << endl;
}

int main() 
{
    // learnMap();
    // sortChar();
    wordLadderProgram();

    cout << "All done!" << endl;
    return 0;
}

// 单词梯子 主程序
void wordLadderProgram(){
    cout << "Welcome to the Word Ladder Finder!" << endl;
    cout << "A powerful computer program that leverages many different" << endl;
    cout << "ADTs to solve a fun children's puzzle." << endl;
    cout << "Up, up, and away!" << endl << endl;

    Set<string> dictionary;
    populateDictionary(dictionary, "res/EnglishWords.txt");

    while (true) {
        string userInput = getLine("Please enter two words that you want to find "
                                   "a word ladder between, separated by a space: ");
        if (userInput == "") break;

        Vector<string> words = stringSplit(userInput, " ");
        Stack<string> wordLadder = findWordLadder(words[0], words[1], dictionary);

        if (wordLadder.isEmpty()){
            cout << "Coudn't find a word ladder between those two words!" << endl;
            continue;
        }

        cout << "Here is the word ladder from " << words[1] << " to " << words[0] << endl;
        while(!wordLadder.isEmpty()){
            cout << wordLadder.pop() << endl;
        }
        cout << endl;

    }

}

// 将 txt 文件中的所有单词,载入,传入的 dictionary 集合中
void populateDictionary(Set<string>& dictionary, string filename){
    ifstream in;
    openFile(in, filename);
    Vector<string> lines;
    readEntireFile(in, lines);
    for (string word: lines){
        dictionary.add(word);
    }
    cout << "Found " << dictionary.size() << " words in the dictionary file." << endl << endl;
}

// 辅助函数: 采用双重遍历的方法,暴力生成所有临近单词
Set<string> generateNeighboringWords(string currentWord, Set<string>& dictionary){
    Set<string> neighboringWords;
    for (int i = 0; i < currentWord.length(); i++){
        for (char ch = 'a'; ch <= 'z'; ch++){
            string newWord = currentWord;
            newWord[i] = ch;
            if (dictionary.contains(newWord)){
                neighboringWords.add(newWord);
            }
        }
    }
    return neighboringWords;
}

// 辅助函数: 根据提供的 起始单词 和 结束单词,使用广度优先算法(BFS), 获得链接路径
Stack<string> findWordLadder(string startingWord, string destinationWord, Set<string>& dictionary) {
    /*
     Create an empty queue and an empty set of visited locations
     Create an initial word ladder containing the starting word and add it to thequeue
     While the queue is not empty
                     Remove the next partial ladder from the queue
                     Set the current search word to be the word at the top of the ladder
                     If the current word is the destination, then return the current ladder
                     Generate all "neighboring" words that are valid English words and one
                     letter away from the current word
                     Loop over all neighbor words
                             If the neighbor hasn't yet been visited
                             Create a copy of the current ladder
                             Add the neighbor to the top of the new ladder and mark it visited
                             Add the new ladder to the back of the queue of partial ladders
    */

    //  Create an empty queue and an empty set of visited locations
    //  Create an initial word ladder containing the starting word and add it to thequeue
    Queue<Stack<string>> ladders = { { startingWord } };
    Set<string> visited = { startingWord };

    //  While the queue is not empty
    while (!ladders.isEmpty()) {
        //                  Remove the next partial ladder from the queue
        Stack<string> currQue = ladders.dequeue();
        //                  Set the current search word to be the word at the top of the ladder
        //                  If the current word is the destination, then return the current ladder
        //                  Generate all "neighboring" words that are valid English words and one
        //                  letter away from the current word
        Set<string> neighborWords = generateNeighboringWords(currQue.peek(), dictionary);
        //                  Loop over all neighbor words
        for (string str : neighborWords) {
            //                          If the neighbor hasn't yet been visited
            if (!visited.contains(str)) {
                //                          Create a copy of the current ladder
                Stack<string> newQue = currQue;
                //                          Add the neighbor to the top of the new ladder and mark it visited
                newQue.add(str);
                if (str == destinationWord) {
                    return newQue;
                }
                visited.add(str);
                //                          Add the new ladder to the back of the queue of partial ladders
                ladders.enqueue(newQue);
            }
        }
    }
    return { };
}
