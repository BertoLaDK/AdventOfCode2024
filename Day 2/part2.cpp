//
// Created by Lucas on 02-12-2024.
//



#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

bool isValidDiff(int num1, int num2) {
    int diff = std::abs(num1 - num2);
    if (diff > 3 || diff < 1) {
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

bool isValidAnyDir(int num1, int num2) {
    return isValidDecrease(num1, num2) || isValidIncrease(num1, num2);
}

int main() {

    std::ifstream file("..\\Day 2\\input.txt");
    std::string str;
    int safeReports = 0;
    while (std::getline(file, str)) {
        std::stringstream ss(str);
        std::istream_iterator<int> begin(ss);
        std::istream_iterator<int> end;
        std::vector<int> vints(begin, end);

        bool isIncreasing = false;
        bool isDecreasing = false;
        bool isValid = true;
        bool hasError = false;
        if (vints.front() > vints.back())
            isDecreasing = true;
        else if (vints.front() < vints.back())
            isIncreasing = true;
        else
            isValid = false;

        for (int i = 0; i < vints.size() - 1; ++i) {
            if (isIncreasing) {
                if (isValidIncrease(vints[i], vints[i + 1])) {
                    isValid = true;
                } else {
                    if (hasError) {
                        isValid = false;
                        break;
                    }
                    hasError = true;
                    if (i > 0 && isValidIncrease(vints[i - 1], vints[i + 1])) {
                        isValid = true;
                    } else isValid = i == vints.size() - 2;
                }
            } else if (isDecreasing) {
                if (isValidDecrease(vints[i], vints[i + 1])) {
                    isValid = true;
                } else {
                    if (hasError) {
                        isValid = false;
                        break;
                    }
                    hasError = true;
                    if (i > 0 && isValidDecrease(vints[i - 1], vints[i + 1])) {
                        isValid = true;
                    } else isValid = i == vints.size() - 2;
                }
            }
            if (!isValid) {
                break;
            }
        }
        if (isValid) {
            if (isIncreasing)
                std::cout << "Safe (Increasing): " << str << std::endl;
            if (isDecreasing)
                std::cout << "Safe (Decreasing): " << str << std::endl;
            safeReports++;
        } else {
            if (isIncreasing)
                std::cout << "Unsafe (Increasing): " << str << std::endl;
            if (isDecreasing)
                std::cout << "Unsafe (Decreasing): " << str << std::endl;
        }

    }
    std::cout << "Safe Reports: " << safeReports << std::endl;
}