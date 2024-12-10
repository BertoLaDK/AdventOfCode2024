#include <fstream>
#include <vector>
#include <chrono>

//
// Created by lucas on 07-12-2024.
//
int main(){
    std::ifstream file("..\\Day 6\\input.txt");
    std::string str;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> guardMap;
    int startX;
    while (std::getline(file, str)) {
        std::vector<char> line(str.begin(), str.end());
        guardMap.push_back(line);
        if (str.find('^'))
            startX = guardMap.size();
    }
}