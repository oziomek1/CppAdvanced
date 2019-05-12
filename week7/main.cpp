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
#include <experimental/numeric>
//#include <experimental/execution_policy>


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

int generator() {
    return rand() % 1000;
}

bool comp(int a, int b)
{
    return a > b;
}

// 4)
auto print_vector = [](const int& n) { std::cout << " " << n; };

int times(int x) {
    return x * 5;
}

int main() {
// 1)
    std::cout << "\nTask 1: seq vs par vs par_unseq" << std::endl;
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
    std::cout << "Task 2: eliminate core dumped" << std::endl;
    std::vector<int> vec(10'000'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::vector<int> output;
    // add mutex
    std::mutex mutex;
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [&output](int& elem)
                  {
                      // lock scope with mutex
                      if (elem % 2 == 0)
                      {
                          std::lock_guard<std::mutex> lock(mutex);
                          output.push_back(elem);
                      }
                  }
    );

// 3)
    std::cout << "\nTask 3.1: for_each_n" << std::endl;
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


    std::cout << "\nTask 3.2: find_first_of" << std::endl;
    std::vector<int> vector1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    startSeq = std::chrono::steady_clock::now();
    auto result = std::find_first_of(std::execution::seq, vector.begin(), vector.end(), vector1.begin(), vector1.end());
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    result = std::find_first_of(std::execution::par, vector.begin(), vector.end(), vector1.begin(), vector1.end());
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 3.3: transform" << std::endl;
    startSeq = std::chrono::steady_clock::now();
    result = std::transform(std::execution::seq, vector.begin(), vector.end(), vector.begin(),
                                 [](int i) -> int { return i + 5; });
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    result = std::transform(std::execution::par, vector.begin(), vector.end(), vector.begin(),
                                [](int i) -> int { return i + 5; });
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 3.4: replace_copy_if" << std::endl;
    std::vector<int> vector2;
    startSeq = std::chrono::steady_clock::now();
    result = std::replace_copy_if(std::execution::seq, vector.begin(), vector.end(), vector.begin(),
                                  [](int n) { return n > 5; }, 10);
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    result = std::replace_copy_if(std::execution::par, vector.begin(), vector.end(), vector.begin(),
                                   [](int n) { return n > 5; }, 10);
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 3.5: generate_n" << std::endl;
    srand(time(NULL));
    startSeq = std::chrono::steady_clock::now();
    result = std::generate_n(std::execution::seq, vector.begin(), vector.size(), generator);
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    result = std::generate_n(std::execution::par, vector.begin(), vector.size(), generator);
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;

// 4)
    std::cout << "\nTask 4.1: for_each_n" << std::endl;
    startSeq = std::chrono::steady_clock::now();
    for_each_n(std::execution::seq, vector.begin(), vector.size(), Add(1));
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    for_each_n(std::execution::par, vector.begin(), vector.size(), Add(1));
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.2: for_each" << std::endl;
    startSeq = std::chrono::steady_clock::now();
    for_each(std::execution::seq, vector.begin(), vector.end(), Add(1));
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startSeq = std::chrono::steady_clock::now();
    for_each(std::execution::par, vector.begin(), vector.end(), Add(1));
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;

    std::cout << "\nTask 4.3: exclusive_scan" << std::endl;
    vector2.clear();
    startSeq = std::chrono::steady_clock::now();
    std::exclusive_scan(std::execution::seq, vector.begin(), vector.end(), vector2.begin(), 1, std::plus<>{});
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    vector2.clear();
    startPar = std::chrono::steady_clock::now();
    std::exclusive_scan(std::execution::par, vector.begin(), vector.end(), vector2.begin(), 1, std::plus<>{});
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.4: inclusive_scan" << std::endl;
    vector2.clear();
    startSeq = std::chrono::steady_clock::now();
    std::inclusive_scan(std::execution::seq, vector.begin(), vector.end(), vector2.begin(), std::plus<>{}, 1);
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    vector2.clear();
    startPar = std::chrono::steady_clock::now();
    std::inclusive_scan(std::execution::par, vector.begin(), vector.end(), vector2.begin(), std::plus<>{}, 1);
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.5: transform_exclusive_scan" << std::endl;
    vector2.clear();
    startSeq = std::chrono::steady_clock::now();
    std::transform_exclusive_scan(std::execution::seq, vector.begin(), vector.end(), vector2.begin(), 1, std::plus<>{}, times);
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;
    startPar = std::chrono::steady_clock::now();
    std::transform_exclusive_scan(std::execution::par, vector.begin(), vector.end(), vector2.begin(), 1, std::plus<>{}, times);
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.6: transform_inclusive_scan" << std::endl;
    vector2.clear();
    startSeq = std::chrono::steady_clock::now();
    std::transform_inclusive_scan(std::execution::seq, vector.begin(), vector.end(), vector2.begin(), std::plus<>{}, times);
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;
    vector2.clear();
    startPar = std::chrono::steady_clock::now();
    std::transform_inclusive_scan(std::execution::par, vector.begin(), vector.end(), vector2.begin(), std::plus<>{}, times);
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.7: parallel::reduce" << std::endl;
    startSeq = std::chrono::steady_clock::now();
    std::experimental::parallel::reduce(std::execution::seq, vector.begin(), vector.end(), 0,
                                        [](auto fir, auto sec){ return fir + ":" + sec; }
    );
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    std::experimental::parallel::reduce(std::execution::par, vector.begin(), vector.end(), 0,
                                        [](auto fir, auto sec){ return fir + ":" + sec; }
    );
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


    std::cout << "\nTask 4.8: parallel::transform_reduce" << std::endl;
    startSeq = std::chrono::steady_clock::now();
    std::experimental::parallel::transform_reduce(std::execution::seq, vector.begin(), vector.end(), times, 0,
                                        [](auto fir, auto sec){ return fir + ":" + sec; }
    );
    std::cout << "seq : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startSeq).count()
              << " time in ms" << std::endl;

    startPar = std::chrono::steady_clock::now();
    std::experimental::parallel::transform_reduce(std::execution::par, vector.begin(), vector.end(), times, 0,
                                        [](auto fir, auto sec){ return fir + ":" + sec; }
    );
    std::cout << "par : "
              << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - startPar).count()
              << " time in ms" << std::endl;


}