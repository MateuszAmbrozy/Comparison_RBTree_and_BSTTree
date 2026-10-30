#include "BST.h"
#include "../common/Console.h"

int main() {
    BST tree;
    return tree_ui::run(tree, static_cast<Node*>(nullptr));
}
