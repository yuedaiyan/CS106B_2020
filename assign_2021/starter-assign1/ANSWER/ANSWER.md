**Q1. Roughly how long did it take your computer to do the search? How many perfect numbers were found and what were they?**

less than 0.1s.
4 numbers.

---

**Q2. Record the timing results for findPerfects that you observed into a table. (old-school table with text-based rows and columns is just fine!)**

Done searching up to 160000
= Correct
Line 128 TIME_OPERATION findPerfects(20000) (size = 20000) completed in 0.220 secs
Line 129 TIME_OPERATION findPerfects(40000) (size = 40000) completed in 0.838 secs
Line 130 TIME_OPERATION findPerfects(80000) (size = 80000) completed in 3.407 secs
Line 131 TIME_OPERATION findPerfects(160000) (size = 160000) completed in 13.607 secs

![graph](/ANSWER/截屏2026-07-06%2021.15.27.png)

---

**Q3. Does it take the same amount of work to compute isPerfect on the number 10 as it does on the number 1000? Why or why not? Does it take the same amount of work for findPerfects to search the range of numbers from 1-1000 as it does to search the numbers from 1000-2000? Why or why not?**

不一样.
对于验证单个数字来说,线性增长,数字越大,计算一个数字的因数也就越多,计算量就越大 → O(线性)
对于验证整个一个序列来说,数字越多,数字越大,验证的时间将是O(线性^2)

---

**Q4. Extrapolate from the data you gathered and make a prediction: how long will it take findPerfects to reach the fifth perfect number?**

第五个数字位置预测(已知第五个完美数大约是33000000大小的话) → 5.7916 × 10^8

![graph](/ANSWER//截屏2026-07-06%2023.45.59.png)

---

**Q5. Do any of the tests still pass even with this broken function? Why or why not?**

```cpp
// 通过的测试案例:
PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}
```

这里实际的改动意味着程序求出的答案会比被除数正好大1;这里应该是12和98765都没有符合要求.

```cpp
// 通过的测试案例:
PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
TIME_OPERATION(10000, findPerfects(10000));
TIME_OPERATION(20000, findPerfects(20000));
TIME_OPERATION(40000, findPerfects(40000));
}

STUDENT_TEST("Yue Dadiyan's test 1: "){
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
    TIME_OPERATION(80000, findPerfects(80000));
    TIME_OPERATION(160000, findPerfects(160000));
}
```

```cpp
// 完美数的定义改成一以后,符号要求的结果实际上是更多了.
Done searching up to 80000
Found perfect number: 1
Found perfect number: 2
Found perfect number: 4
Found perfect number: 8
Found perfect number: 16
Found perfect number: 32
Found perfect number: 64
Found perfect number: 128
Found perfect number: 256
Found perfect number: 512
Found perfect number: 1024
Found perfect number: 2048
Found perfect number: 4096
Found perfect number: 8192
.Found perfect number: 16384
..Found perfect number: 32768
...Found perfect number: 65536
.......Found perfect number: 131072
```

---

**Q6. Describe the testing strategy you used for your test cases to confirm smarterSum is working correctly.**

经GPT指导,将目标数的因数视为"一对"的状态,每次只枚举小因数,然后通过除法获得大因数,同时检测大因数不等于小因数和目标数,之后将大因数和小因数都放入结果之中.

---

**Q7. Record your timing results for findPerfectsSmarter into a table.**

```zsh
 =  Correct
    Line 192 TIME_OPERATION findPerfectsSmarter(20000) (size =    20000) completed in    0.019 secs
    Line 193 TIME_OPERATION findPerfectsSmarter(40000) (size =    40000) completed in    0.026 secs
    Line 194 TIME_OPERATION findPerfectsSmarter(80000) (size =    80000) completed in    0.043 secs
    Line 195 TIME_OPERATION findPerfectsSmarter(160000) (size =   160000) completed in    0.085 secs
    Line 196 TIME_OPERATION findPerfectsSmarter(320000) (size =   320000) completed in    0.195 secs
    Line 197 TIME_OPERATION findPerfectsSmarter(640000) (size =   640000) completed in    0.488 secs
```

---

**Q8. Make a prediction: how long will findPerfectsSmarter take to reach the fifth perfect number?**

604566
![graph](/ANSWER//截屏2026-07-06%2023.45.59.png)

---

**Q9. Explain how you chose your specific test cases and why they lead you to be confident findNthPerfectEuclid is working correctly.**
我在long的范围内,已经遍历了所有的可能,这给了我信心:

```zsh
i: 1 – 6
i: 2 – 6
i: 3 – 28
i: 4 – 496
i: 5 – 496
i: 6 – 8128
i: 7 – 8128
i: 8 – 33550336
i: 9 – 33550336
i: 10 – 33550336
i: 11 – 33550336
i: 12 – 33550336
i: 13 – 33550336
i: 14 – 8589869056
i: 15 – 8589869056
i: 16 – 8589869056
i: 17 – 8589869056
i: 18 – 137438691328
i: 19 - 137438691328
i: 20 - 2305843008139952128
```

---

**Q10. What is the Soundex code for "Angelou"? What is the code for your own surname?**

"Angelou": A524
"Yue": Y000

---

**Q11. Before writing any code, brainstorm your plan of attack and sketch how you might decompose the work into smaller tasks. Briefly describe your decomposition strategy.**

![graph](</ANSWER/截屏2026-07-09 16.04.33.png>)

---

**Q12. Think about one or more examples of a class of names that the Soundex system might not work well for. Explain what this class of names is and why the system might incorrectly group them or mis-categorize one of the names.**

类比中文,有许多没有关系的同音字,这种同音字在姓氏中也存在.
例如: 于、余、鱼
例如: 张、章
并且,此类问题在所有非表音语言中都有可能存在.毕竟soundex是为了表音语言开发的,尤其是拉丁系统的表音语言.

---

**Q13. Suppose you are a software engineer working for the U.S. government. You have been tasked with implementing a system that collects names as part of the Census survey and analyzes these names using a phonetic algorithm. Your boss suggests using Soundex and notes that the algorithm is only expected to work for ASCII-encoded strings, since supporting Unicode would require extra work and time. What would your response be and why? What representational harms might result from building a system that exclusively uses Soundex and/or ASCII?**

考虑按照语言学的分类进行开发.

如果就在soundex的基础上进行修改,考虑添加一个或多个字段用来表示"形",通过表型来解决表意字语言的问题.
计算方法需要考虑一定的模糊性,毕竟型的变化与音一样不完全准确,但又多有关联.
例如计算这个姓氏的unicode平均值,更甚至直接根据标准字体,生成一些表型的代码用来映射汉字,然后加入soundex中.
理想的编码应该是音型结合的.
