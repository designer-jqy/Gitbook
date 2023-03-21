# 优先级队列

```go
package main

import (
	"container/heap" // go包中的heap为小顶堆
	"fmt"
)

type Item struct {
	val      string
	priority int
	index    int
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int           { return len(pq) }
func (pq PriorityQueue) Less(x, y int) bool { return pq[x].priority > pq[x].priority }
func (pq PriorityQueue) Swap(x, y int) {
	pq[x], pq[y] = pq[y], pq[x]
	pq[x].index = y
	pq[y].index = x
}

func (pq *PriorityQueue) Push(x interface{}) {
	n := len(*pq)
	item := x.(*Item)
	item.index = n
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	old[n-1] = nil
	item.index = -1
	*pq = old[0 : n-1]
	return item
}

func (pq *PriorityQueue) update(item *Item, value string, priority int) {
	item.val = value
	item.priority = priority
	heap.Fix(pq, item.index)
}

func main() {
	items := map[string]int{
		"banana": 3, "apple": 2, "pear": 4,
	}
	pq := PriorityQueue{}
	index := 0
	for val, priority := range items {
		pq[index] = &Item{
			val:      val,
			priority: priority,
			index:    index,
		}
		index++
	}

	heap.Init(&pq)
	item := &Item{
		val:      "orange",
		priority: 1,
	}
	heap.Push(&pq, item)
	pq.update(item, item.val, 5)

	for pq.Len() > 0 {
		item := heap.Pop(&pq).(*Item)
		fmt.Printf("%s %d\n", item.val, item.priority)
	}
}
```