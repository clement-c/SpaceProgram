#pragma once
#include <stdint.h>
#include <cstddef>
#include <string>

// #include "Enum.hpp"

struct Null;
struct Enum;

struct Vector2;
struct Vector3;
struct Vector4;
struct Matrix33;
struct Matrix44;
struct Quaternion;
struct Euler;

struct Type
{
    enum : std::size_t
    {
        kUnknown = 0,
        kNull = 1,
        kBool = 2,
        kEnum = 3,
        kInt8 = 5,
        kInt16,
        kInt32,
        kInt64,
        kUInt8,
        kUInt16,
        kUInt32,
        kUInt64,
        kFloat,
        kDouble,

        kVector2 = 32,
        kVector3,
        kVector4,
        kMatrix33,
        kMatrix44,
        kQuaternion,
        kEuler,

        kString = 64
    };

    Type() = default;
    constexpr Type(std::size_t id) : TypeId{id} {}
    constexpr Type(Type const &tp) : TypeId{tp.TypeId} {}

    std::string ToString() const
    {
        switch (TypeId)
        {
        case kUnknown:
            return "Unknown";
        case kNull:
            return "Null";
        case kBool:
            return "Bool";
        case kEnum:
            return "Enum";
        case kInt8:
            return "Int8";
        case kInt16:
            return "Int16";
        case kInt32:
            return "Int32";
        case kInt64:
            return "Int64";
        case kUInt8:
            return "UInt8";
        case kUInt16:
            return "UInt16";
        case kUInt32:
            return "UInt32";
        case kUInt64:
            return "UInt64";
        case kFloat:
            return "Float";
        case kDouble:
            return "Double";
        case kVector2:
            return "Vector2";
        case kVector3:
            return "Vector3";
        case kVector4:
            return "Vector4";
        case kMatrix33:
            return "Matrix33";
        case kMatrix44:
            return "Matrix44";
        case kQuaternion:
            return "Quaternion";
        case kEuler:
            return "Euler";
        case kString:
            return "String";
        default:
            return "TYPE_HAS_NO_STRING_EQUIVALENT";
        }
    }

    std::size_t TypeId;

    bool operator==(Type const &other) { return TypeId == other.TypeId; }
};

template <typename T>
static constexpr Type GetType_s() { return Type::kUnknown; }

template <>
static constexpr Type GetType_s<Null>() { return Type::kNull; }

template <>
static constexpr Type GetType_s<bool>() { return Type::kBool; }

template <>
static constexpr Type GetType_s<Enum>() { return Type::kEnum; }

template <>
static constexpr Type GetType_s<int8_t>() { return Type::kInt8; }

template <>
static constexpr Type GetType_s<int16_t>() { return Type::kInt16; }

template <>
static constexpr Type GetType_s<int32_t>() { return Type::kInt32; }

template <>
static constexpr Type GetType_s<int64_t>() { return Type::kInt64; }

template <>
static constexpr Type GetType_s<uint8_t>() { return Type::kUInt8; }

template <>
static constexpr Type GetType_s<uint16_t>() { return Type::kUInt16; }

template <>
static constexpr Type GetType_s<uint32_t>() { return Type::kUInt32; }

template <>
static constexpr Type GetType_s<uint64_t>() { return Type::kUInt64; }

template <>
static constexpr Type GetType_s<float>() { return Type::kFloat; }

template <>
static constexpr Type GetType_s<double>() { return Type::kDouble; }

template <>
static constexpr Type GetType_s<Vector2>() { return Type::kVector2; }

template <>
static constexpr Type GetType_s<Vector3>() { return Type::kVector3; }

template <>
static constexpr Type GetType_s<Vector4>() { return Type::kVector4; }

template <>
static constexpr Type GetType_s<Matrix33>() { return Type::kMatrix33; }

template <>
static constexpr Type GetType_s<Matrix44>() { return Type::kMatrix44; }

template <>
static constexpr Type GetType_s<Quaternion>() { return Type::kQuaternion; }

template <>
static constexpr Type GetType_s<Euler>() { return Type::kEuler; }

template <>
static constexpr Type GetType_s<std::string>() { return Type::kString; }

namespace std
{
    template <>
    struct hash<Type>
    {
        std::size_t operator()(Type const &tp) const
        {
            return static_cast<size_t>(tp.TypeId);
        }
    };
}
