// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "getAllPerms:\n";
    auto perms = getAllPerms(tree);
    for (auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << "\n";
    }

    std::cout << "\ngetPerm1(1): ";
    for (char c : getPerm1(tree, 1)) std::cout << c;
    std::cout << "\ngetPerm2(2): ";
    for (char c : getPerm2(tree, 2)) std::cout << c << "\n";

    // === Вычислительный эксперимент ===
    std::ofstream out("result/times.txt");
    out << "n getAllPerms getPerm1 getPerm2\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 3; n <= 10; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) symbols.push_back('0' + i);

        auto start = std::chrono::high_resolution_clock::now();
        PMTree t(symbols);
        auto all = getAllPerms(t);
        auto end = std::chrono::high_resolution_clock::now();
        double t_all =
            std::chrono::duration<double, std::milli>(end - start).count();

        std::uniform_int_distribution<> dis(1, all.size());
        int num = dis(gen);

        start = std::chrono::high_resolution_clock::now();
        getPerm1(t, num);
        end = std::chrono::high_resolution_clock::now();
        double t1 =
            std::chrono::duration<double, std::milli>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(t, num);
        end = std::chrono::high_resolution_clock::now();
        double t2 =
            std::chrono::duration<double, std::milli>(end - start).count();

        out << n << " " << t_all << " " << t1 << " " << t2 << "\n";
    }
    out.close();

    std::cout << "Experiment finished → result/times.txt\n";
    return 0;
}
