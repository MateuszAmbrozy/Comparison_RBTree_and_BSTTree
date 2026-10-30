#ifdef TEST_RB
#include "../RB/RedBlackTree.h"
using Tree = RedBlackTree;
#else
#include "../BST/BST.h"
using Tree = BST;
#endif
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>
#include <set>
#include <type_traits>
#include <vector>

static_assert(!std::is_copy_constructible<Tree>::value, "Tree must not share ownership via copying");
static_assert(!std::is_copy_assignable<Tree>::value, "Tree must not share ownership via assignment");
void require(bool ok, const char* reason) {
    if (!ok) { std::cerr << reason << '\n'; std::exit(1); }
}
Node* nil(Tree& tree) {
#ifdef TEST_RB
    return tree.getSentinel();
#else
    (void)tree;
    return nullptr;
#endif
}
int visit(Node* node, Node* parent, Node* empty, long long low, long long high,
          std::vector<int>& values, std::set<Node*>& visited) {
    if (node == empty) return 1;
    require(node != nullptr, "Unexpected null node");
    require(visited.insert(node).second, "Cycle or shared subtree");
    require(node->parent == parent, "Incorrect parent pointer");
    require(node->key >= low && node->key <= high, "Invalid search ordering");
#ifdef TEST_RB
    require(node->color == BLACK || node->color == RED, "Invalid node color");
    if (node->color == RED)
        require(node->left->color == BLACK && node->right->color == BLACK, "Adjacent red nodes");
#endif
    int left = visit(node->left, node, empty, low, node->key, values, visited);
    values.push_back(node->key);
    int right = visit(node->right, node, empty, node->key, high, values, visited);
#ifdef TEST_RB
    require(left == right, "Unequal black heights");
    return left + (node->color == BLACK);
#else
    return std::max(left, right) + 1;
#endif
}
void verify(Tree& tree, const std::multiset<int>& expected) {
    Node* empty = nil(tree);
#ifdef TEST_RB
    require(empty->color == BLACK, "Sentinel must remain black");
    require(empty->left == empty && empty->right == empty, "Invalid sentinel links");
    require(tree.getRoot()->color == BLACK, "Root must be black");
#endif
    std::vector<int> values;
    std::set<Node*> visited;
    visit(tree.getRoot(), empty, empty, std::numeric_limits<long long>::min(),
          std::numeric_limits<long long>::max(), values, visited);
    require(values == std::vector<int>(expected.begin(), expected.end()), "Contents differ from multiset");
}
int main() {
    Tree tree;
    std::multiset<int> expected;
    tree.remove(42);
    require(!tree.checkIfExist(42), "Empty lookup failed");
    verify(tree, expected);
    for (int value : {10, 5, 15, 2, 7, 1}) { tree.add(value); expected.insert(value); verify(tree, expected); }
    for (int value : {15, 7, 10, 1, 2, 5}) {
        tree.remove(value); expected.erase(expected.find(value)); verify(tree, expected);
    }
    std::mt19937 random(42);
    for (int i = 0; i < 20000; ++i) {
        int value = static_cast<int>(random() % 201) - 100;
        if (random() % 2) { tree.add(value); expected.insert(value); }
        else {
            tree.remove(value);
            auto found = expected.find(value);
            if (found != expected.end()) expected.erase(found);
        }
        require(tree.checkIfExist(value) == (expected.count(value) != 0), "Incorrect lookup");
        verify(tree, expected);
        if (i % 1000 == 999) { tree.clear(tree.getRoot()); expected.clear(); verify(tree, expected); }
    }
    tree.clear(tree.getRoot()); expected.clear();
    for (int value : {std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max(), 0}) {
        tree.add(value); expected.insert(value); verify(tree, expected);
    }
    while (!expected.empty()) {
        int value = *expected.begin(); tree.remove(value); expected.erase(expected.begin()); verify(tree, expected);
    }
    // Clearing a subtree must leave the remaining tree accessible.
    tree.add(2); tree.add(1); tree.add(3);
    tree.clear(tree.find(1));
    require(!tree.find(1) && tree.find(2) && tree.find(3), "Subtree clear failed");
    tree.clear(tree.getRoot()); tree.clear(tree.getRoot());
    // A skewed BST must be cleared without consuming one stack frame per node.
    for (int i = 0; i < 12000; ++i) tree.add(i);
    tree.clear(tree.getRoot());
    verify(tree, {});
    tree.add(9); require(tree.find(9) != nullptr, "Reuse after clear failed");
    std::cout << "All tree checks passed\n";
}
