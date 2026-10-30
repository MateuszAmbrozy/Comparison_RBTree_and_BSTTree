#pragma once
#include "TreeDisplay.h"
#include <sstream>
#include <limits>

namespace tree_ui {
inline bool numbers(const std::string& line, std::vector<int>& result) {
    std::istringstream in(line);
    std::string token;
    while (in >> token) {
        std::istringstream number(token);
        long long value;
        char extra;
        if (!(number >> value) || (number >> extra) ||
            value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) return false;
        result.push_back(static_cast<int>(value));
    }
    return !result.empty();
}
template<class Tree, class Node>
int run(Tree& tree, Node* nil) {
    setup();
    std::string message = "Add numbers or load the demo dataset.";
    for (;;) {
        if (terminal()) std::cout << "\033[2J\033[H";
        std::cout << color("╔══════════════════════════════════════════════╗\n"
                           "║             TREE EXPLORER                    ║\n"
                           "╚══════════════════════════════════════════════╝\n", "1;36");
        tree.print();
        statistics(tree.getRoot(), nil);
        std::cout << "\n  " << message << "\n\n"
                  << "  1  Add numbers      2  Remove numbers\n"
                  << "  3  Find a number    4  Clear tree\n"
                  << "  5  Load demo        0  Exit\n\n> " << std::flush;
        std::string choice;
        if (!std::getline(std::cin, choice)) return 0;
        std::vector<int> command;
        if (!numbers(choice, command) || command.size() != 1 || command[0] < 0 || command[0] > 5) {
            message = "Choose an option from 0 to 5."; continue;
        }
        int action = command[0];
        if (!action) return 0;
        if (action == 4) { tree.clear(tree.getRoot()); message = "Tree cleared."; continue; }
        if (action == 5) {
            tree.clear(tree.getRoot());
            for (int value : {30, 15, 50, 8, 22, 40, 60, 5, 10, 18, 25, 35, 45}) tree.add(value);
            message = "Loaded 13 sample numbers."; continue;
        }
        std::cout << (action == 3 ? "Number: " : "Space-separated integers (negative values allowed): ") << std::flush;
        std::string line;
        if (!std::getline(std::cin, line)) return 0;
        std::vector<int> values;
        if (!numbers(line, values) || (action == 3 && values.size() != 1)) {
            message = "Invalid input. Enter integers within the int range."; continue;
        }
        if (action == 3) {
            message = std::to_string(values[0]) + (tree.checkIfExist(values[0]) ? " — found." : " — not found.");
        } else {
            std::size_t changed = 0;
            for (int value : values) {
                if (action == 1) { tree.add(value); ++changed; }
                else if (tree.checkIfExist(value)) { tree.remove(value); ++changed; }
            }
            message = std::string(action == 1 ? "Added: " : "Removed: ") + std::to_string(changed) +
                      ". Duplicates are separate nodes; removal deletes one occurrence.";
        }
    }
}
}
