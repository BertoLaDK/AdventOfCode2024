//
// Created by Lucas on 02-12-2024.
//



#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

int main(){

    std::ifstream file("..\\Day 2\\input.txt");
    std::string str;
    int safeReports = 0;
    while(std::getline(file, str)){
        std::stringstream ss(str);
        std::istream_iterator<int> begin(ss);
        std::istream_iterator<int> end;
        std::vector<int> vstrings(begin, end);

        bool isIncreasing = false;
        bool isDecreasing = false;
        bool isValid = true;
        for (int i = 0; i < vstrings.size() - 1; ++i) {
            if(vstrings[i] < vstrings[i+1]){
                if(isDecreasing){
                    isValid = false;
                }
                int diff = vstrings[i+1] - vstrings[i];
                if(diff > 3 || diff < 1){
                    isValid = false;
                }
                isIncreasing = true;
            } else if(vstrings[i] > vstrings[i+1]) {
                if(isIncreasing){
                    isValid = false;
                }
                int diff = vstrings[i] - vstrings[i+1];
                if(diff > 3 || diff < 1){
                    isValid = false;
                }
                isDecreasing = true;
            } else {
                isValid = false;
            }
            if(!isValid){
                break;
            }
        }

        if(isValid){
            std::cout << "Safe: " << str << std::endl;
            safeReports++;
        }

    }
    std::cout << "Safe Reports: " << safeReports << std::endl;
}