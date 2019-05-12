//
// Created by Wojciech Ozimek on 12/05/2019.
//

#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <mutex>

int main()
{
    std::vector<int> vec(10'000'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::vector<int> output;
    std::for_each(std::execution::par, vec.begin(), vec.end(),
        [&output](int& elem)
            {
                if (elem % 2 == 0)
                {
                    output.push_back(elem);
                }
            }
    );
}