#pragma once
#include <iostream>
#include "Type.hpp"
#include "Engine/Core/Maths/Vector3.hpp"
#include "Engine/Core/Maths/Matrix44.hpp"

struct Serializer;
struct Null
{
};

struct Value
{
    Value() = delete;
    template <typename T>
    Value(T value) : m_type{GetType_s<T>()}, m_impl{new internal_implementation<T>(std::move(value))} {}
    Value(Value const &value) : m_type{value.m_type}, m_impl{value.m_impl->Clone()} {}

    std::ostream &Print(std::ostream &os) const { return m_impl->Print(os); }

    float AsBool() const { return m_impl->AsBool(); }
    float AsFloat() const { return m_impl->AsFloat(); }
    double AsDouble() const { return m_impl->AsDouble(); }
    Vector3 AsVector3() const { return m_impl->AsVector3(); }
    Matrix44 AsMatrix44() const { return m_impl->AsMatrix44(); }
    std::string AsString() const { return m_impl->AsString(); }
    int32_t AsInt32() const { return m_impl->AsInt32(); }

    Type GetType() const { return m_type; }

protected:
    class internal_interface
    {
    public:
        virtual ~internal_interface() {}
        virtual std::ostream &Print(std::ostream &os) const = 0; // { return m_ptr->Print(os); }
        virtual bool AsBool() const = 0;
        virtual float AsFloat() const = 0;
        virtual double AsDouble() const = 0;
        virtual Vector3 AsVector3() const = 0;
        virtual Matrix44 AsMatrix44() const = 0;
        virtual std::string AsString() const = 0;
        virtual int32_t AsInt32() const = 0;

        virtual internal_interface *Clone() const = 0;
    };

    template <typename T>
    class internal_implementation : public internal_interface
    {
    public:
        // internal_implementation(T&& v) : value{std::forward<T>(v)} {}
        internal_implementation(T v) : value{std::move(v)} {}
        virtual ~internal_implementation() {}

        std::ostream &Print(std::ostream &os) const { return os << value; }

        bool AsBool() const final { return *((bool *)&value); }
        float AsFloat() const final { return *((float *)&value); }
        int32_t AsInt32() const final { return *((int32_t *)&value); };
        double AsDouble() const final { return *((double *)&value); }
        Vector3 AsVector3() const final { return *((Vector3 *)&value); }
        Matrix44 AsMatrix44() const final { return *((Matrix44 *)&value); };
        std::string AsString() const final { return *((std::string *)&value); };

        internal_implementation *Clone() const final { return new internal_implementation(value); }

        T value;
    };

private:
    Type m_type;
    std::unique_ptr<internal_interface> m_impl = nullptr;
};

inline std::ostream &operator<<(std::ostream &os, Value const &v) { return v.Print(os); }
