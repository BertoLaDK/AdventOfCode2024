cmake_minimum_required(VERSION 3.27)
project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 20)

set(DAYS 1 2 3 4 5 6 7)

foreach(day ${DAYS})
    add_executable(Day${day}_Part1
            "Day ${day}/part1.cpp")
    add_executable(Day${day}_Part2
            "Day ${day}/part2.cpp")
endforeach ()