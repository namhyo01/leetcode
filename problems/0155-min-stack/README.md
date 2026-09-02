# 155. Min Stack

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/min-stack/

## Problem

Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time.

Implement the `MinStack` class:

- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

You must implement a solution with `O(1)` time complexity for **each** function.

## Example

```
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```

## Constraints

```
-2^31 <= val <= 2^31 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
```

> `val` 이 `int` 의 **양쪽 끝까지** 온다. 최솟값 초기값을 잡을 때 주의할 것.

## Questions to sit with

- [ ] 이 문제가 지금까지 푼 것들과 다른 점은 무엇인가?
      한 번 호출로 끝나는 게 아니라 **상태가 이어진다**는 게 무엇을 바꾸는가?
- [ ] `getMin` 을 매번 훑으면 얼마인가? 지문이 요구하는 건?
- [ ] `push` 시점에 미리 계산해둘 수 있는 게 있는가?
      "지금까지 쌓인 것 중 최솟값" 은 push 하는 순간 정해지는가?
- [ ] `pop` 이 최솟값을 빼버리면 그 다음 최솟값을 어떻게 아는가?
      값 하나만 들고 있으면 왜 안 되는가?
- [ ] 같은 값이 여러 번 최솟값으로 들어오면? (`push(1); push(1); pop();`)
- [ ] 공간을 얼마나 쓰게 되는가? 더 줄일 여지가 있는가?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
