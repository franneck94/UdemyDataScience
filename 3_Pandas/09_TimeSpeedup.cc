#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Timer.h"

constexpr static std::size_t LEN = 10000;

float gen()
{
    static auto seed = std::random_device{};
    static auto gen = std::mt19937{seed()};
    static auto dist = std::normal_distribution<float>{0.0f, 1.0f};

    return dist(gen);
}

void head(std::vector<float> &arr, std::size_t n = 10)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cout << arr[i] << ", ";
    }

    std::cout << "\n";
}

void apply(std::vector<float> &arr)
{
    for (auto &val : arr)
    {
        if (val < 0.5f)
        {
            val = 0.0f;
        }
    }
}

void transform(std::vector<float> &arr)
{
    for (auto &val : arr)
    {
        val += 1.0f;
    }
}

int main()
{
    int num_runs = 10000;
    double total_time = 0.0f;
    auto A = std::vector<float>(LEN, 0.0);

    total_time = 0.0f;
    std::generate(A.begin(), A.end(), gen);
    for (int i = 0; i < num_runs; ++i)
    {
        cpptiming::Timer t;
        apply(A);
        total_time += t.elapsed_time<cpptiming::nanosecs, double>();
    }
    std::cout << "Mean time apply: " << total_time / num_runs << " ns" << std::endl;
    head(A);

    total_time = 0.0f;
    std::generate(A.begin(), A.end(), gen);
    for (int i = 0; i < num_runs; ++i)
    {
        cpptiming::Timer t;
        transform(A);
        total_time += t.elapsed_time<cpptiming::nanosecs, double>();
    }
    std::cout << "Mean time transform: " << total_time / num_runs << " ns" << std::endl;
    head(A);

    return 0;
}
