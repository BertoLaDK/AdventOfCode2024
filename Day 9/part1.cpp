#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

//
// Created by lucas on 09-12-2024.
//
bool is_zero(int i) {
    return i == 0;
}

int main() {
    std::ifstream file("../Day 9/input.txt");
    std::string str;
    auto start = std::chrono::high_resolution_clock::now();
    std::getline(file, str);
    std::vector<int> disk;
    for (int i = 0; i < str.size(); ++i) {
        int size = (int) (str[i] - '0');
        if (i & 1) {
            for (int j = 0; j < size; ++j) {
                disk.emplace_back(0);
            }
        } else {
            for (int j = 0; j < size; ++j) {
                disk.emplace_back((i / 2) + 1);
            }
        }
    }

//    for (auto pos: disk) {
//        if (pos == 0) {
//            std::cout << '.';
//        } else {
//            std::cout << pos - 1;
//        }
//    }
    std::cout << std::endl;
    std::cout << "Size: " << disk.size() << std::endl;

    auto itf = std::find(disk.begin(), disk.end(), 0);
    auto itl = std::find_if_not(disk.rbegin(), disk.rend(), is_zero);
    auto startIndex = std::distance(disk.begin(), itf);
    auto endIndex = disk.size() - std::distance(disk.rbegin(), itl) - 1;
    while (startIndex < endIndex) {
        //std::cout << "Start: " << startIndex << " End: " << endIndex << std::endl;
        disk[startIndex] = disk[endIndex];
        disk[endIndex] = 0;
        itf = std::find(disk.begin(), disk.end(), 0);
        itl = std::find_if_not(disk.rbegin(), disk.rend(), is_zero);
        startIndex = std::distance(disk.begin(), itf);
        endIndex = disk.size() - std::distance(disk.rbegin(), itl) - 1;
//        for (auto pos: disk) {
//            if (pos == 0) {
//                std::cout << '.';
//            } else {
//                std::cout << pos - 1;
//            }
//        }
//        std::cout << std::endl;
    }
    long long total = 0;
    for (int i = 0; i < disk.size(); ++i) {
        if(disk[i] == 0)
            break;
        total += i * (disk[i]-1);
    }
    std::cout << "Total: " << total << std::endl;

}