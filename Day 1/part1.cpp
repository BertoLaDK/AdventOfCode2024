//
// Created by lucas on 01-12-2024.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

bool descending(int x, int y){
   return x >= y;
}
bool ascending(int x, int y){
    return y >= x;
}
bool ascendingPairs(std::pair<int,int>a, std::pair<int,int>b){
    return b.first >= a.first;
}

int main() {

    std::ifstream file("..\\Day 1\\input.txt");
    std::string str;
    std::vector<int> firstList, secondList;
    std::clock_t time = std::clock();
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, str)){
        auto first = std::stoi(str.substr(0, str.find("   ")));
        firstList.push_back(first);
        auto second = std::stoi(str.substr(str.find("   ")+2));
        secondList.push_back(second);
    }

    std::sort(firstList.begin(), firstList.end(), ascending);
    std::sort(secondList.begin(), secondList.end(), ascending);

    int total = 0;

    for (int i = 0; i < firstList.size(); ++i) {
        total += std::abs(firstList[i] - secondList[i]);
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Total: " << total << " Time: " << duration << " ms" << std::endl;



    return 0;
}