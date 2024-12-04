//
// Created by Lucas on 04-12-2024.
//

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<std::pair<int, int>>
checkAround(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor);

bool checkDirection(std::pair<int, int> match, int i, int j, std::vector<std::vector<char>> &wordMap);

int main() {

    std::ifstream file("..\\Day 4\\input.txt");
    std::string str;
    std::vector<std::vector<char>> wordMap;
    while (std::getline(file, str)) {
        std::vector<char> line(str.begin(), str.end());
        wordMap.push_back(line);
    }
    std::vector<std::vector<char>> wordMapCopy(wordMap.begin(),wordMap.end());
    for (auto& line : wordMapCopy) {
        for (char & i : line) {
            i = '.';
        }
    }
    int xmasCount = 0;
    for (int i = 0; i < wordMap.size(); ++i) {
        for (int j = 0; j < wordMap[i].size(); ++j) {
            if (wordMap[i][j] == 'X') {
                std::vector<std::pair<int, int>> matches = checkAround(i, j, wordMap, 'M');
                for (auto match: matches) {
                    bool hasXmas = checkDirection(match, i, j, wordMap);
                    if(hasXmas){
                        wordMapCopy[i][j] = 'X';
                        wordMapCopy[match.first][match.second] = 'M';
                        xmasCount++;
                    }
                }
            }
        }
    }
    std::cout << "xmas count: " << xmasCount << std::endl;
}

bool checkDirection(std::pair<int, int> match, int i, int j, std::vector<std::vector<char>> &wordMap) {
    int x_vector = match.first - i;
    int y_vector = match.second - j;
    int next_x = i+x_vector*2;
    int next_y = j+y_vector*2;
    if(wordMap.size() > next_x && wordMap[next_x].size() > next_y && wordMap[next_x][next_y] == 'A'){
        next_x = 3*x_vector+i;
        next_y = 3*y_vector+j;
        if(wordMap.size() > next_x && wordMap[next_x].size() > next_y && wordMap[next_x][next_y] == 'S'){
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> checkAround(int i, int j, std::vector<std::vector<char>> &wordMap, char charToCheckFor) {
    std::vector<std::pair<int, int>> matches;
    if (i != 0) {
        int temp_i = i - 1;
        if (j != 0) {
            if (wordMap[temp_i][j - 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j - 1);
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
    }
    if (i < wordMap.size()-1) {
        int temp_i = i + 1;
        if (j != 0) {
            if (wordMap[temp_i][j - 1] == charToCheckFor) {
                matches.emplace_back(temp_i, j - 1);
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
