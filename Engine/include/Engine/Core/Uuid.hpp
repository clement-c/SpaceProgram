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
    /**
     * @brief Converts a string representation of a UUID to a Uuid object.
     * 
     * @param str The string representation of the UUID. It must be either 32 characters
     *            (without dashes) or 36 characters (with dashes in the format 8-4-4-4-12).
     * @return Uuid The Uuid object created from the string.
     * 
     * @throws std::invalid_argument If the input string is empty.
     * @throws std::invalid_argument If the input string is not of length 32 or 36.
     * @throws std::invalid_argument If the input string does not follow the UUID format
     *                                (e.g., invalid characters or misplaced dashes).
     */
    static Uuid FromString(std::string const &str)
    {
        if (str.empty())
            throw std::invalid_argument("String is empty");

        // Check if the string is a valid UUID format (8-4-4-4-12)
        if (str.length() != 36 && str.length() != 32)
            throw std::invalid_argument("String must be of length 32 or 36 in order to convert to uuid");

        for (size_t i = 0; i < str.length(); i++)
        {
            if ((i + 1) % 3 == 0 && str.at(i) != '-')
                throw std::invalid_argument("Invalid UUID format, expected '-' at position " + std::to_string(i));
            else if ((i + 1) % 3 != 0 && !isxdigit(str.at(i)))
                throw std::invalid_argument("Invalid UUID format, expected hex digit at position " + std::to_string(i));
        }

        Uuid uuid;

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

    /**
     * @brief Converts the UUID to its string representation.
     * 
     * This function formats the UUID as a string in the standard 8-4-4-4-12
     * hexadecimal format, separated by hyphens. Each byte of the UUID is
     * represented as a two-digit hexadecimal number.
     * 
     * @return A string representing the UUID in the format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.
     *         For example: "123e4567-e89b-12d3-a456-426614174000".
     * 
     * @note This function is marked as `noexcept` and guarantees not to throw exceptions.
     */
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
    // Set the variant field to RFC 4122-compliant (10xxxxxx).
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
