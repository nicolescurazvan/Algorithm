# Sorting algorithms

An essential class of algorithms in computer science is sorting algorithms. They are used
to put (*sort*) elements from a list in a certain order (increasing, decreasing, by string
length or any other criteria that can be ordered like numbers or words in a dictionary, for
more details, see (Partially ordered set)[https://en.wikipedia.org/wiki/Partially_ordered_set]).

Sorting algorithms on short and long contiguous lists (vectors) are analysed. The criteria for a
sorting algorithm include:
* **Time complexity:** How does the number of operations depend on the input size. We strive for 
$O(n\log(n))$ operations in all cases or almost certainly.
* **Additional memory:** How much additional memory is needed.
* **Stability:** If multiple elements have the same value, does the algorithm change their relative
order (or, in plain language, mangles them).

---

### Insertion sort

**Insertion sort** is a classical sorting algorithm, but it's inefficient for large lists, because
it has $O(n^2)$ complexity (10.000 for n=100, 100.000.000 for n=10.000 and so on), allowing
reasonable times for no more than 10.000-20.000 elements.
It works by moving each element to its desired position as it comes.

---

### Merge sort

**Merge sort** is an efficient sort that works as following:
1. If length is small enough, sort trivially.
2. Else, the vector is split in two halves.
3. Each half gets sorted recursively.
4. The sorted halves are combined (merged).

---
