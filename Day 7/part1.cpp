//
// Created by lucas on 07-12-2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <valarray>
#include <chrono>

bool canEqualResult(long long result, const std::vector<int> &nums);

int main() {

    std::ifstream file("../Day 7/input.txt");
    std::string str;
    auto start =std::chrono::high_resolution_clock::now();

    long long total = 0;
    while (std::getline(file, str)) {
        size_t splitIndex = str.find(':');
        std::string resultStr = str.substr(0, splitIndex);
        auto result = std::stoll(resultStr);
        std::stringstream ss(str.substr(splitIndex + 1, str.size()));
        int num;
        std::vector<int> nums;
        while (ss >> num) {
            nums.push_back(num);
        }
        bool valid = canEqualResult(result, nums);
        if(valid){
            total += result;
        }
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Total: " << total << " Time: " << duration << " ms" << std::endl;
}

bool canEqualResult(long long result, const std::vector<int> &nums) {
    long long total;
    // 0 = +
    // 1 = *
    std::uint16_t operators = 0;
    for (int i = 0; i < pow(2, nums.size() - 1); ++i) {
        total = nums[0];
        for (int j = 1; j < nums.size(); ++j) {
            if((operators >> (j-1)) & 1){
                total *= nums[j];
            } else {
                total += nums[j];
            }
        }
        if(total == result){
            return true;
        }
        operators++;
    }
    return false;
}
