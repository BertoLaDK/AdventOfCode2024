//
// Created by Lucas on 04-12-2024.
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

std::vector<std::pair<int, int>>
checkAround(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor);

bool checkDirection(std::pair<int, int> match, int i, int j, std::vector<std::vector<char>> &wordMap,
                    std::vector<std::vector<char>> &wordMapFiltered);

int main() {

    std::ifstream file("..\\Day 4\\input.txt");
    std::string str;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> wordMap;
    while (std::getline(file, str)) {
        std::vector<char> line(str.begin(), str.end());
        wordMap.push_back(line);
    }
    std::vector<std::vector<char>> wordMapCopy(wordMap.begin(), wordMap.end());
    for (auto &line: wordMapCopy) {
        for (char &i: line) {
            i = '.';
        }
    }
    int xmasCount = 0;
    for (int i = 0; i < wordMap.size(); ++i) {
        for (int j = 0; j < wordMap[i].size(); ++j) {
            if (wordMap[i][j] == 'X') {
                std::vector<std::pair<int, int>> matches = checkAround(i, j, wordMap, 'M');
                for (auto match: matches) {
                    bool hasXmas = checkDirection(match, i, j, wordMap, wordMapCopy);
                    if (hasXmas) {
                        wordMapCopy[i][j] = 'X';
                        wordMapCopy[match.first][match.second] = 'M';
                        xmasCount++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < wordMapCopy.size(); ++i) {
        for (int j = 0; j < wordMapCopy[i].size(); ++j) {
            std::cout << wordMapCopy[i][j];
        }
        std::cout << std::endl;
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "XMAS Count: " << xmasCount << " Time: " << duration << " ms" << std::endl;
}

bool checkDirection(std::pair<int, int> match, int i, int j, std::vector<std::vector<char>> &wordMap,
                    std::vector<std::vector<char>> &wordMapFiltered) {
    int x_vector = match.first - i;
    int y_vector = match.second - j;
    int a_x = i + x_vector * 2;
    int a_y = j + y_vector * 2;
    if (wordMap.size() > a_x && wordMap[a_x].size() > a_y && wordMap[a_x][a_y] == 'A') {
        int s_x = 3 * x_vector + i;
        int s_y = 3 * y_vector + j;
        if (wordMap.size() > s_x && wordMap[s_x].size() > s_y && wordMap[s_x][s_y] == 'S') {
            wordMapFiltered[a_x][a_y] = 'A';
            wordMapFiltered[s_x][s_y] = 'S';
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>>
checkAround(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor) {
    std::vector<std::pair<int, int>> matches;
    if (i != 0) {
        int temp_i = i - 1;
        if (j != 0) {
            if (wordMap[temp_i][j - 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j - 1);
            }
        }
        if (j < wordMap[temp_i].size()) {
            if (wordMap[temp_i][j + 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j + 1);
            }
        }
        if (wordMap[temp_i][j] == charToCheckFor) {
            matches.emplace_back(temp_i, j);
        }
    }
    if (i < wordMap.size() - 1) {
        int temp_i = i + 1;
        if (j != 0) {
            if (wordMap[temp_i][j - 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j - 1);
            }
        }
        if (j < wordMap[temp_i].size()) {
            if (wordMap[temp_i][j + 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j + 1);
            }
        }
        if (wordMap[temp_i][j] == charToCheckFor) {
            matches.emplace_back(temp_i, j);
        }
    }
    if (wordMap[i][j - 1] == charToCheckFor) {
        matches.emplace_back(i, j - 1);
    }
    if (j < wordMap[i].size()) {
        if (wordMap[i][j + 1] == charToCheckFor) {
            matches.emplace_back(i, j + 1);
        }
    }

    return matches;
}
