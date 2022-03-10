# Data-Structures-and-Algorithms-II
Implementations of some common data structures and algorithms. These are based on the assignments that are offered in CSE208 course by BUET.

---

## About
Some of the implementations are based on the assignments that were offered in CSE208 course by BUET. In every folder the main methods are implemented in the corresponding `cpp` or `java` files. Some of the folders contain `.docx` or `.pdf` files that describe the assignments in details. However, the generic implementations are separated from the methods that were required to satisfy the assignment specifications. So, the data structures and algorithms are reusable.
### Watch out!!

- **Binomial Heap:**

    The `print` function that has been implemented here is not correct. Because it prints according to the order of the siblings. But during union operation the siblings are updated only for the first child of the new root but not for all the levels of the merged trees.

    However, it shows correct result upto `n = 16`

    Hopefully I will fix this later someday (or not).