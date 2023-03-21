# 链表


```go	
package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func (n *ListNode) AppendNode(x int, next *ListNode) {
	if n == nil {
		return
	}
	for n.Next != nil {
		n = n.Next
	}
	n.Next = &ListNode{Val: x, Next: next}
}

func (n *ListNode) Traverse() {
	if n == nil {
		return
	}
	fmt.Print(n.Val)
	for n.Next != nil {
		n = n.Next
		fmt.Print("->")
		fmt.Print(n.Val)
	}
	fmt.Println()
}

func main() {
	head := makeCycleList()
	head.Traverse()
}

func makeCycleList() *ListNode {
	head := &ListNode{Val: 1}
	head.AppendNode(2, nil)
	head.AppendNode(3, nil)
	head.AppendNode(5, head.Next)
	return head
}
```