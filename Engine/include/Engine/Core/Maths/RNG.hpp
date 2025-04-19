#pragma once
// FIXME: Work on an actual complete RNG solution

#include <array>
#include <algorithm>
#include <type_traits>
#include <random>

class RNG
{
public:
    template <typename T, size_t N>
    static void Fill(std::array<std::remove_reference_t<T>, N> &array);

    template <size_t N>
    static void Fill(std::array<uint8_t, N> &array)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint8_t> dist(0, 255);
        std::generate_n(array.begin(), N, [&gen, &dist]() -> uint8_t
                        { return dist(gen); });
    }

    template <size_t N>
    static void Fill(std::array<uint8_t, N> &array, uint32_t seed)
    {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<uint8_t> dist(0, 255);
        std::generate_n(array.begin(), N, [&gen, &dist]() -> uint8_t
                        { return dist(gen); });
    }
};
