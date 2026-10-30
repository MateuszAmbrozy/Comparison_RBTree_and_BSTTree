#include "RedBlackTree.h"
#include "../common/Console.h"

int main() {
    RedBlackTree tree;
    return tree_ui::run(tree, tree.getSentinel());
}
