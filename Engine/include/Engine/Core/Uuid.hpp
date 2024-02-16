#pragma once
#include <array>
#include <string>
#include <stdint.h>
#include <sstream>
#include <iomanip>

#include "./Maths/RNG.hpp"

/* 16 * 16 */
struct Uuid
{
    static Uuid FromString(std::string const &str)
    {
        Uuid uuid;
        bool noHyphens = false;
        if (str.length() == 32)
            noHyphens = true;
        else if (str.length() != 36)
            throw std::invalid_argument("String must be of length 32 or 36 in order to convert to uuid");

        uint32_t pos = 0;
        for (uint32_t i = 0; i < 36; i++)
        {
            std::string byteString = str.substr(i, 2);
            if (str.at(i) == '-')
                continue;
            else
                i++;
            uuid.bytes[pos++] = (uint8_t)strtol(byteString.c_str(), NULL, 16);
        }

        return uuid;
    }

    std::string ToString() const noexcept
    {
        std::ostringstream ss;

        ss << std::hex << std::setfill('0');
        ss << std::setw(2) << static_cast<int>(bytes[0])
           << std::setw(2) << static_cast<int>(bytes[1])
           << std::setw(2) << static_cast<int>(bytes[2])
           << std::setw(2) << static_cast<int>(bytes[3])
           << '-'
           << std::setw(2) << static_cast<int>(bytes[4])
           << std::setw(2) << static_cast<int>(bytes[5])
           << '-'
           << std::setw(2) << static_cast<int>(bytes[6])
           << std::setw(2) << static_cast<int>(bytes[7])
           << '-'
           << std::setw(2) << static_cast<int>(bytes[8])
           << std::setw(2) << static_cast<int>(bytes[9])
           << '-'
           << std::setw(2) << static_cast<int>(bytes[10])
           << std::setw(2) << static_cast<int>(bytes[11])
           << std::setw(2) << static_cast<int>(bytes[12])
           << std::setw(2) << static_cast<int>(bytes[13])
           << std::setw(2) << static_cast<int>(bytes[14])
           << std::setw(2) << static_cast<int>(bytes[15]);
        return ss.str();
    }

    std::array<uint8_t, 16> bytes; // TODO: Global linear memory allocator? (pool of UUIDs)
};

/**
 * @brief UUID created from pseudo-random value
 *
 * Note: NOT cryptographic
 * TODO: Use C++11 RNGs
 *
 * @return Uuid
 */
Uuid Uuid_v4()
{
    Uuid uuid{};
    RNG::Fill(uuid.bytes);
    uuid.bytes[6] = (uuid.bytes[6] & 0x0f) | 0x40;
    uuid.bytes[8] = (uuid.bytes[8] & 0x3f) | 0x80;
    return uuid;
};

Uuid Uuid_v4(size_t seed)
{
    throw std::runtime_error("Uuid_v4(size_t seed) :: Not implemented yet");
    return Uuid{};
};

inline std::ostream &operator<<(std::ostream &os, Uuid const &uuid)
{
    return os << uuid.ToString();
}

namespace std
{
    template <>
    struct hash<Uuid>
    {
        size_t operator()(Uuid const &uuid) const
        {
            // 16 bytes = 128 bits = 2 x 64 bits
            // Following https://stackoverflow.com/a/2595226
            size_t seed = 0;
            auto hasher = std::hash<uint64_t>();
            seed ^= hasher(*reinterpret_cast<uint64_t const *>(uuid.bytes.data())) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed ^ (hasher(*reinterpret_cast<uint64_t const *>(uuid.bytes.data() + 8)) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
        }
    };

}
