#pragma once
#include <random>

template <typename T,
    std::enable_if_t<std::is_integral_v<T>, int> = 0
>
T randm(T low, T high)
{
    static std::random_device seeder;
    static std::mt19937 gen(seeder());
    std::uniform_int_distribution<T> dis(low, high);
    return dis(gen);
}

template <typename T,
    std::enable_if_t<std::is_floating_point_v<T>, int> = 0
>
T randm(T low, T high)
{
    static std::random_device seeder;
    static std::mt19937 gen(seeder());
    std::uniform_real_distribution<T> dis(low, high);
    return dis(gen);
}