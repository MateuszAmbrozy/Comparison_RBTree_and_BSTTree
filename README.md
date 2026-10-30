# Red-black tree and binary search tree comparison

## Build and run

Requirements: a C++17 compiler and CMake 3.16 or later. The programs support
Linux and Windows terminals with UTF-8 support.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/bst
./build/rbtree
```

With the Visual Studio generator on Windows, executables are usually placed
in `build/Debug/` (`bst.exe` and `rbtree.exe`).

The console displays `L` (left child) and `R` (right child) branches, the node
count, and the height measured in levels (0 for an empty tree). In RBTree,
`[R]` marks a red node and `[B]` a black node. Terminal colors supplement
these labels.

- `1`: add one or more space-separated integers, such as `10 -5 20 10`.
- `2`: remove one occurrence of each supplied number; missing values are skipped.
- `3`: find a number.
- `4`: clear the tree.
- `5`: replace the contents with a demo dataset.
- `0`: exit.

Duplicates are stored as separate nodes. RBTree rotations can move an equal
key into the left subtree; inorder traversal remains nondecreasing.
The display is limited to 80 nodes and a depth of 16. Data and statistics
cover the entire tree. Tree operations do not print messages or introduce
delays. Benchmark the algorithms separately from the console, which also
calculates statistics and renders the tree.

## Tests

```sh
ctest --test-dir build --output-on-failure
```

For Visual Studio, add `-C Debug`. Tests compare each tree against
`std::multiset` after 20,000 random operations and check parent pointers,
key ordering, duplicates, `int` limits, clearing, and reuse. RBTree tests
also check the black root, node colors, and equal black height.
If Python 3 is available, CTest also checks the menu, invalid input, and
end-of-input handling.

## Introduction

This project compares red-black trees with binary search trees by measuring
insertion, search, and deletion times. Each measurement was repeated 20 times
and averaged. The experiments used two types of datasets:

- Random datasets containing 50,000, 100,000, 300,000, 600,000, 1,000,000,
  1,500,000, 2,000,000, and 2,500,000 elements.
- Ascending datasets containing 500, 1,000, 1,500, 2,000, and 2,500 elements.

## Data structures

### Binary search tree

A binary search tree (BST) is a dynamic binary tree. The left subtree of each
node contains smaller keys, while the right subtree contains keys greater
than or equal to the node's key. Each node stores a key and pointers to its
left child, right child, and parent. This ordering supports search and sorted
traversal.

A balanced BST can be constructed from sorted data by repeatedly choosing
the middle element as the subtree root. In a balanced tree, search, insertion,
and deletion take O(log n) time. This implementation uses ordinary BST
insertion without rebalancing. A highly unbalanced tree can have height
proportional to its node count, making these operations O(n) in the worst case.

### Red-black tree

A red-black tree is a self-balancing binary search tree. Each node has an
additional color attribute, either red or black. It maintains these properties:

1. Each node is red or black.
2. The root is black.
3. All NIL leaves are black and hold no data.
4. Both children of a red node are black.
5. Every path from a node to a descendant NIL leaf contains the same number
   of black nodes.

These properties keep the tree balanced enough to guarantee O(log n) search,
insertion, and deletion, where n is the number of nodes.

Red-black trees need additional storage for node colors. A single bit is
sufficient in principle; this implementation stores the color in an `int`.
They are commonly used to implement ordered maps and sets because they
maintain balance and predictable operation times.

## Results for random datasets

![BST with random data](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/fd178cf1-b3a2-4222-b719-fa8d0cd68aad)
![Red-black tree with random data](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/742f0ad2-554f-4782-9831-b9b3ce4a7e78)

## Results for ascending datasets

![BST with ascending data](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/65e9fe7c-fc12-4cd7-ac1a-8e46106e16db)
![Red-black tree with ascending data](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/e09843c3-6a5f-4e68-a311-57cea5dbf755)

## Conclusions

Red-black trees maintain logarithmic operation times even for ascending
input, which produces a highly unbalanced ordinary BST. An ordinary BST's
performance depends on the insertion order and resulting tree height.

## Figures

1. BST with random data.
2. Red-black tree with random data.
3. BST with ascending data.
4. Red-black tree with ascending data.
