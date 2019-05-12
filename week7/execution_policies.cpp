//
// Created by Wojciech Ozimek on 12/05/2019.
//

#include <algorithm>
#include <chrono>
#include <execution>
#include <numeric>
#include <iostream>
#include <vector>

// 1)

template <typename F>
void Runner(F func)
{
    auto start = std::chrono::steady_clock::now();
    auto result = func();
    auto stop = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration<double, std::milli>(stop - start).count() << " time in ms" << std::endl;
}

int main()
{
// 1)
    std::vector<double> value(1000000, 1);

// std::execution::sequenced_policy
    Runner([&value] {
        return std::reduce(std::execution::seq, value.begin(), value.end());
    });

// std::execution::parallel_policy
    Runner([&value] {
        return std::reduce(std::execution::par, value.begin(), value.end());
    });

// std::execution::parallel_unsequenced_policy
    Runner([&value] {
        return std::reduce(std::execution::par_unseq, value.begin(), value.end())
    });
}