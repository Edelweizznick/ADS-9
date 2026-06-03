// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& symbols) {
    n = symbols.size();
    root = new Node(0);
    std::vector<char> sorted = symbols;
    std::sort(sorted.begin(), sorted.end());
    buildTree(root, sorted);
}

PMTree::~PMTree() {
    deleteTree(root);
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (char c : remaining) {
        Node* child = new Node(c);
        node->children.push_back(child);
        std::vector<char> next;
        for (char r : remaining) if (r != c) next.push_back(r);
        buildTree(child, next);
    }
}

void PMTree::deleteTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) deleteTree(child);
    delete node;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    auto dfs = [&](auto&& self, Node* node) -> void {
        if (!node) return;
        if (node->value != 0) current.push_back(node->value);
        if (current.size() == tree.n) {
            result.push_back(current);
        } else {
            for (Node* child : node->children) self(self, child);
        }
        if (node->value != 0) current.pop_back();
    };
    for (Node* child : tree.root->children) dfs(dfs, child);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(all.size())) return {};
    return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num < 1) return {};
    std::vector<char> result;
    Node* curr = tree.root;
    int k = num;
    while (result.size() < tree.n) {
        if (curr->children.empty()) break;
        int fact = 1;
        for (int i = 1; i <= tree.n - result.size() - 1; ++i) fact *= i;
        int idx = (k - 1) / fact;
        if (idx >= static_cast<int>(curr->children.size())) return {};
        Node* next = curr->children[idx];
        result.push_back(next->value);
        curr = next;
        k = (k - 1) % fact + 1;
    }
    return result.size() == tree.n ? result : std::vector<char>{};
}
