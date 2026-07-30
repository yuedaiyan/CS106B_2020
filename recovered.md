Before submitting this file, make sure that there are no more TODO
placeholders remaining in the file (and remove this comment too).

## Warmup

**Q1. The display of the Stack in the debugger uses the labels `top` and `bottom` to mark the two ends of the stack. How are the contents labeled when the Stack contains only one element?**

```txt
bottom/top
```

**Q2. For which type of inputs does the function go into an infinite loop?**

```txt
单一负数会造成程序无限循环
```

**Q3. Show your edited code for duplicateNegatives that fixes the problem with the infinite loop**

```cpp
void duplicateNegatives(Queue<int>& q) {
    int qSize = q.size();
    for (int i = 0; i < qSize; i++) {
        int val = q.dequeue();
        q.enqueue(val);
        if (val < 0) {
            q.enqueue(val);   // double up on negative numbers
        }
    }
}
```

**Q4. What is the better fix to `sumStack` that corrects the bug?**

```cpp
 int total = 0;
```

## Maze

**Q5. In lecture, Cynthia noted the convention is to pass large data structures by reference for reasons of efficiency. Why then do you think `validatePath` passes `path` by value instead of by reference?**

```txt
因为会不停地 .pop, 一般来说我们不希望改变原始答案;
同时,path的大小远远小于maze;
```

**Q6. After you have written your tests, describe your testing strategy to determine that your `validatePath` works as intended.**

```txt
两个正确测试案例;
一个错误测试案例,测试包括: 答案过短\答案过长\两次访问相同位置\撞墙\错误的结尾\错误的起点
```

## Search Engine

**Q7. Sketch the contents of the inverted index built from the `res/tiny.txt` database file.**

```txt
{"5lb_m&ms":{"www.shoppinglist.com"}, "blue":{"www.dr.seuss.net", "www.rainbow.org"}, "bread":{"www.shoppinglist.com"}, "eat":{"www.bigbadwolf.com"}, "fish":{"www.bigbadwolf.com", "www.dr.seuss.net", "www.shoppinglist.com"}, "green":{"www.rainbow.org"}, "i":{"www.bigbadwolf.com"}, "milk":{"www.shoppinglist.com"}, "one":{"www.dr.seuss.net"}, "red":{"www.dr.seuss.net", "www.rainbow.org"}, "two":{"www.dr.seuss.net"}}
```

## Beyond Algorithmic Analysis

**Q8. In a short paragraph, describe a real or plausible scenario not previously presented in lecture in which using techniques like Big-O or Asymptotic Analysis to improve the performance of an algorithm might benefit the environment. Include your thoughts on how a software engineer working on this piece of code might identify such potential benefits and take them into consideration when designing the code.**

```txt

```

**Q9. According to the contract that IBM struck with the state of Indiana, the criteria for optimization were improving efficiency of the overall welfare system and reducing fraud. Criteria for reducing wait times and wrongful denials were not included. However, wrongfully denying benefits has a huge negative impact on the citizens who rely on the system. If criteria like minimizing wrongful denials were not included in the contract, should engineers have included them in their optimization algorithm? Why or why not?**

```txt

```

**Q10. Imagine that after completing CS106B you are hired at IBM as an engineer working on this system. How might you have approached designing and setting the goals of this system? How might you apply algorithmic analysis tools to build a system that achieved the desired goals? Could you do so in a way that avoids the severe negative impacts on users of the system that are outlined in the case study?**

```txt

```
