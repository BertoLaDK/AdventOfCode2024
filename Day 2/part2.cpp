//
// Created by Lucas on 02-12-2024.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <chrono>

bool isRecordSafe(std::vector<int> &recordValues);

int getTotalDifference(std::vector<int> &recordValues);

bool handleErrorRecord(std::vector<int> &recordValues);

bool verifyRecord(std::vector<int> &recordValues, int difference);

bool isValidDiff(int num1, int num2) {
    int diff = std::abs(num1 - num2);
    if (3 < diff || diff < 1) {
        return false;
    }
    return true;
}

bool isValidIncrease(int num1, int num2) {
    if (num1 < num2) {
        return isValidDiff(num1, num2);
    }
    return false;
}

bool isValidDecrease(int num1, int num2) {
    if (num1 > num2) {
        return isValidDiff(num1, num2);
    }
    return false;
}

int main() {
    std::ifstream file("..\\Day 2\\input.txt");
    std::string str;
    int safeReports = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (std::getline(file, str)) {
        std::stringstream ss(str);
        std::istream_iterator<int> begin(ss);
        std::istream_iterator<int> end;
        std::vector<int> vints(begin, end);

        if (isRecordSafe(vints)) {
            safeReports++;
        }

    }
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Safe Reports: " << safeReports << " Time: " << duration << " microseconds" << std::endl;
}

bool isRecordSafe(std::vector<int> &recordValues) {
    int difference = getTotalDifference(recordValues);
    if (difference == 0) {
        return false;
    }
    bool hasError = !verifyRecord(recordValues, difference);
    if(hasError){
        return handleErrorRecord(recordValues);
    } else {
        return true;
    }
}

bool verifyRecord(std::vector<int> &recordValues, int difference) {

    int isIncreasing = difference < 0;
    for (int i = 0; i < recordValues.size() - 1; ++i) {
        if (isIncreasing) {
            if (!isValidIncrease(recordValues[i], recordValues[i + 1])) {
                return false;
            }
        } else {
            if (!isValidDecrease(recordValues[i], recordValues[i + 1])) {
                return false;
            }
        }
    }
    return true;
}

bool handleErrorRecord(std::vector<int> &recordValues) {
    for (int i = 0; i < recordValues.size(); ++i) {
        std::vector<int> trimmedValues;
        std::copy(recordValues.begin(), recordValues.end(), std::back_inserter(trimmedValues));
        trimmedValues.erase(trimmedValues.begin() + i);

        int difference = getTotalDifference(recordValues);
        if (difference == 0) {
            continue;
        }
        if(verifyRecord(trimmedValues, difference)){
            return true;
        }
    }
    return false;
}

int getTotalDifference(std::vector<int> &recordValues) {
    int totalDiff = 0;
    for (int i = 0; i < recordValues.size() - 1; ++i) {
        totalDiff += recordValues[i] - recordValues[i + 1];
    }
    return totalDiff;
}