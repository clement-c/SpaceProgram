#pragma once
// FIXME: Work on an actual complete RNG solution

#include <array>
#include <algorithm>
#include <type_traits>

class RNG
{
public:
    template <typename T, size_t N>
    static void Fill(std::array<std::remove_reference_t<T>, N> &array);

    template <size_t N>
    static void Fill(std::array<uint8_t, N> &array)
    {
        std::generate_n(array.begin(), N, []() -> uint8_t
                        { return rand() % 255; });
    }
};
