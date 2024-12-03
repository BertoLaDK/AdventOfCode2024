//
// Created by Lucas on 03-12-2024.
//
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <chrono>

int main() {
    std::ifstream file("..\\Day 3\\input.txt");
    auto start = std::chrono::high_resolution_clock::now();
    std::stringstream ss;
    while (file >> ss.rdbuf());

    std::string s = ss.str();
    std::vector<std::string> multiplies;
    std::regex regex(R"(mul\(\d+,\d+\))");
    std::smatch match;
    bool mulsEnabled = true;
    while (std::regex_search(s, match, regex)) {
        size_t mulIndex = s.find(match.str());
        size_t dontIndex = s.find("don't()");
        size_t doIndex = s.find("do()");

        if (dontIndex != std::string::npos && dontIndex < mulIndex) {
            mulsEnabled = false;
        } else if (doIndex != std::string::npos && doIndex < mulIndex) {
            mulsEnabled = true;
        }
        if (mulsEnabled) {
            multiplies.push_back(match.str());
        }
        s.erase(0, s.find(match.str()) + match.str().size());
    }
    int total = 0;
    for (const auto& mul: multiplies) {
        size_t commaIndex = mul.find(",");
        int first = std::stoi(mul.substr(4, commaIndex - 4));
        int second = std::stoi(mul.substr(commaIndex + 1, mul.find(")") - (commaIndex + 1)));
        int result = first * second;
        total += result;
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Total: " << total << " Time: " << duration << " ms" << std::endl;
    return 0;
}