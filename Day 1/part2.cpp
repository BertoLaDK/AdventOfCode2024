//
// Created by lucas on 01-12-2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>

bool ascending(int x, int y){
    return y >= x;
}
int method1(const std::vector<int>& firstList, const std::vector<int>& secondList);
int method2(const std::vector<int>& firstList, std::vector<int> secondList);

int main() {

    std::ifstream file("..\\Day 1\\input.txt");
    std::string str;
    std::vector<int> firstList, secondList;
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, str)) {
        auto first = std::stoi(str.substr(0, str.find("   ")));
        firstList.push_back(first);
        auto second = std::stoi(str.substr(str.find("   ") + 2));
        secondList.push_back(second);
    }

    int total = method2  (firstList, secondList);


    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Total: " << total << " Time: " << duration << " microseconds" << std::endl;
}

int method1(const std::vector<int>& firstList, const std::vector<int>& secondList){
    int total = 0;
    for (int num : firstList) {
        int multiplier = 0;
        for (int j : secondList) {
            if (j == num)
                multiplier++;

        }
        total += num * multiplier;
    }
    return total;
}

int method2(const std::vector<int>& firstList, std::vector<int> secondList){
    int total = 0;
    std::sort(secondList.begin(), secondList.end(), ascending);
    for (int num : firstList) {
        int multiplier = 0;
        int index = 0;
        while(secondList[index] != num && index < secondList.size()) index++;
        while(secondList[index] == num) {
            index++;
            multiplier++;
            if(index >= secondList.size())
                break;
        }
        total += num * multiplier;
    }
    return total;
}