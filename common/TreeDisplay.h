#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

namespace tree_ui {
inline bool terminal() {
#ifdef _WIN32
    return _isatty(_fileno(stdout)) != 0;
#else
    return isatty(STDOUT_FILENO) != 0;
#endif
}
inline void setup() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    DWORD mode = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleMode(handle, &mode))
        SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}
inline std::string color(const std::string& value, const std::string& code) {
    return terminal() ? "\033[" + code + "m" + value + "\033[0m" : value;
}
template<class Node, class Label>
void draw(Node* root, Node* nil, Label label, int indent = 0) {
    if (root == nil) { std::cout << "  (empty tree)\n"; return; }
    struct Entry { Node* node; std::string prefix; bool last; int depth; std::string edge; };
    std::vector<Entry> stack{{root, std::string(std::max(0, std::min(indent, 40)), ' '), true, 0, ""}};
    int shown = 0;
    while (!stack.empty() && shown < 80) {
        Entry e = stack.back(); stack.pop_back();
        std::cout << e.prefix << (e.depth ? (e.last ? "└── " : "├── ") : "◆ ")
                  << e.edge << label(e.node) << '\n';
        ++shown;
        if (e.depth >= 16) {
            if (e.node->left != nil || e.node->right != nil)
                std::cout << e.prefix << "    … (display depth limit reached)\n";
            continue;
        }
        std::string next = e.prefix + (e.depth ? (e.last ? "    " : "│   ") : "  ");
        bool right = e.node->right != nil;
        if (right) stack.push_back({e.node->right, next, true, e.depth + 1, "R: "});
        if (e.node->left != nil) stack.push_back({e.node->left, next, !right, e.depth + 1, "L: "});
    }
    if (!stack.empty()) std::cout << "  … (display limited to 80 nodes)\n";
}
template<class Node>
void statistics(Node* root, Node* nil) {
    std::vector<std::pair<Node*, std::size_t>> stack;
    if (root != nil) stack.push_back({root, 1});
    std::size_t count = 0, height = 0;
    while (!stack.empty()) {
        auto entry = stack.back(); stack.pop_back();
        ++count; height = std::max(height, entry.second);
        if (entry.first->left != nil) stack.push_back({entry.first->left, entry.second + 1});
        if (entry.first->right != nil) stack.push_back({entry.first->right, entry.second + 1});
    }
    std::cout << "  Nodes: " << count << "   Height (levels): " << height << '\n';
}
}
