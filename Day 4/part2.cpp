//
// Created by Lucas on 04-12-2024.
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

std::vector<std::pair<int, int>>
checkCorners(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor);


bool checkOpposite(std::pair<int, int> match, char charToMatch, int i, int j, std::vector<std::vector<char>> &wordMap,
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
    std::vector<std::vector<char>> wordMapFiltered(wordMap.begin(), wordMap.end());
    for (auto &line: wordMapFiltered) {
        for (char &i: line) {
            i = '.';
        }
    }
    int xmasCount = 0;
    for (int i = 0; i < wordMap.size(); ++i) {
        for (int j = 0; j < wordMap[i].size(); ++j) {
            if (wordMap[i][j] == 'A') {
                int matchingChars = 0;
                std::vector<std::pair<int, int>> matches = checkCorners(i, j, wordMap, 'M');
                for (auto match: matches) {
                    bool hasXmas = checkOpposite(match, 'S', i, j, wordMap, wordMapFiltered);
                    if (hasXmas) {
                        matchingChars++;
                    }
                }
                if(matchingChars == 2){
                    wordMapFiltered[i][j] = 'A';
                    for (auto match: matches) {
                        wordMapFiltered[match.first][match.second] = 'M';
                        int x_vector = match.first - i;
                        int y_vector = match.second - j;
                        int o_x = i + x_vector * -1;
                        int o_y = j + y_vector * -1;
                        wordMapFiltered[o_x][o_y] = 'S';
                    }
                    xmasCount++;
                }
            }
        }
    }
//    for (int i = 0; i < wordMapFiltered.size(); ++i) {
//        for (int j = 0; j < wordMapFiltered[i].size(); ++j) {
//            std::cout << wordMapFiltered[i][j];
//        }
//        std::cout << std::endl;
//    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "XMAS Count: " << xmasCount << " Time: " << duration << " ms" << std::endl;
}

bool checkOpposite(std::pair<int, int> match, char charToMatch, int i, int j, std::vector<std::vector<char>> &wordMap,
                   std::vector<std::vector<char>> &wordMapFiltered) {
    int x_vector = match.first - i;
    int y_vector = match.second - j;
    int o_x = i + x_vector * -1;
    int o_y = j + y_vector * -1;
    if(wordMap.size() > o_x && wordMap[o_x].size() > o_y){
        if(wordMap[o_x][o_y] == charToMatch){
            return true;
        }
    }
    return false;
}


std::vector<std::pair<int, int>>
checkCorners(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor) {
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
    }

    return matches;
}
