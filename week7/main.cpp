//
// Created by Wojciech Ozimek on 12/05/2019.
//

#include <algorithm>
#include <chrono>
#include <execution>
#include <numeric>
#include <iostream>
#include <vector>
#include <mutex>

// 1)

template <typename F>
void Runner(const char* policyName, F func)
{
    auto start = std::chrono::steady_clock::now();
    auto result = func();
    auto stop = std::chrono::steady_clock::now();

    std::cout << policyName << " : " << std::chrono::duration<double, std::milli>(stop - start).count() << " time in ms" << std::endl;
}


// 3)
class Add
{
private:
    int value;
public:
    Add(int _value) : value(_value) {}
    int operator()(int adder) const
    {
        return value + adder;
    }
};

int main() {
// 1)
    std::cout << "Task 1: seq vs par vs par_unseq" << std::endl;
    std::vector<double> value(1000000, 1);

// std::execution::sequenced_policy
    Runner("seq", [&value] {
        return std::reduce(std::execution::seq, value.begin(), value.end());
    });

// std::execution::parallel_policy
    Runner("par", [&value] {
        return std::reduce(std::execution::par, value.begin(), value.end());
    });

// std::execution::parallel_unsequenced_policy
    Runner("par_unseq", [&value] {
        return std::reduce(std::execution::par_unseq, value.begin(), value.end());
    });

// 2)
//    std::cout << "Task 2: eliminate core dumped" << std::endl;
//    std::vector<int> vec(10'000'000);
//    std::iota(vec.begin(), vec.end(), 0);
//    std::vector<int> output;
//    // add mutex
//    std::mutex mutex;
//    std::for_each(std::execution::par, vec.begin(), vec.end(),
//                  [&output](int& elem)
//                  {
//                      // lock scope with mutex
//                      if (elem % 2 == 0)
//                      {
//                          std::lock_guard<std::mutex> lock(mutex);
//                          output.push_back(elem);
//                      }
//                  }
//    );

// 3)
    std::cout << "Task 3: for_each_n" << std::endl;
    std::vector<double> vector(1000000, 1);

    auto startSeq = std::chrono::steady_clock::now();
    for_each_n(std::execution::seq, vector.begin(), vector.size(), Add(1));
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    auto startPar = std::chrono::steady_clock::now();
    for_each_n(std::execution::par, vector.begin(), vector.size(), Add(1));
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;

    std::cout << "Task 3: find_first_of" << std::endl;
    std::vector<int> vector1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> vector2{5, 6, 7};

    startSeq = std::chrono::steady_clock::now();
    auto result = std::find_first_of(std::execution::seq, vector1.begin(), vector1.end(), vector2.begin(), vector2.end());
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    result = std::find_first_of(std::execution::par, vector1.begin(), vector1.end(), vector2.begin(), vector2.end());
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


}