#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

#include "../Data/Value.hpp"
#include "./Path.hpp"

struct Flag
{
    Flag(std::string shortNm) : ShortName{shortNm}, LongName{shortNm} {}
    Flag(std::string shortNm, std::string const &longNm) : ShortName{shortNm}, LongName{longNm} {}
    Flag(std::string shortNm, std::string const &longNm, std::string const &help) : ShortName{shortNm}, LongName{longNm}, Help{help} {}

    std::string const ShortName, LongName;
    std::string Help;

    bool operator==(Flag const &other)
    {
        return other.ShortName == ShortName;
    }

    bool operator==(std::string const &s)
    {
        return ShortName == s || LongName == s;
    }
};

struct Argument
{
    Argument(Flag const &flag, Type type = Type::kString, bool multi = false) : m_flag{flag}, m_type{type}, m_multi{multi}, m_defaultValue{type} {}
    bool IsMulti() const { return m_multi; }
    Type GetType() const { return m_type; }
    Value GetDefaultValue() const { return m_defaultValue; }

protected:
    Flag m_flag;
    bool m_multi = false;
    Type m_type = Type::kString;
    Value m_defaultValue;
};

struct ArgumentsDefinition
{

    Flag &AddFlag(std::string shortNm)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        return m_flags.emplace_back(shortNm);
    }
    Flag &AddFlag(std::string shortNm, std::string const &longNm)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        if (HasFlag(longNm))
            throw std::runtime_error("A flag is already defined with the long name \"" + longNm + "\"");
        return m_flags.emplace_back(shortNm, longNm);
    }
    Flag &AddFlag(std::string shortNm, std::string const &longNm, std::string const &help)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        if (HasFlag(longNm))
            throw std::runtime_error("A flag is already defined with the long name \"" + longNm + "\"");
        return m_flags.emplace_back(shortNm, longNm, help);
    }

    bool HasFlag(std::string const &flag) const
    {
        if (flag.substr(0, 1) == "-")
        {
            if (flag.substr(1, 1) == "-")
                return std::any_of(m_flags.cbegin(), m_flags.cend(), [&flag](Flag const &f) -> bool
                                   { f.LongName == flag; });
            else
                return std::any_of(m_flags.cbegin(), m_flags.cend(), [&flag](Flag const &f) -> bool
                                   { f.ShortName == flag; });
        }
        else
        {
            std::string sn = "-" + flag;
            std::string ln = "--" + flag;
            return std::any_of(m_flags.cbegin(), m_flags.cend(), [&](Flag const &f) -> bool
                               { f.ShortName == sn || f.LongName == ln; });
        }
        return false;
    }

    Argument &AddArgument(std::string shortNm, Type &type)
    { // TODO: Multi
        return m_args.emplace_back(Flag(shortNm), type);
    }
    Argument &AddArgument(std::string shortNm, std::string const &longNm, Type &type)
    { // TODO: Multi
        return m_args.emplace_back(Flag(shortNm, longNm), type);
    }
    Argument &AddArgument(std::string shortNm, std::string const &longNm, std::string const &help, Type &type)
    { // TODO: Multi
        return m_args.emplace_back(Flag(shortNm, longNm, help), type);
    }
    Argument &AddArgument(std::string shortNm, Value const &defaultValue)
    {                                                                      // TODO: Multi
        return m_args.emplace_back(Flag(shortNm), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
    }
    Argument &AddArgument(std::string shortNm, std::string const &longNm, Value const &defaultValue)
    {                                                                              // TODO: Multi
        return m_args.emplace_back(Flag(shortNm, longNm), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
    }
    Argument &AddArgument(std::string shortNm, std::string const &longNm, std::string const &help, Value const &defaultValue)
    {                                                                                    // TODO: Multi
        return m_args.emplace_back(Flag(shortNm, longNm, help), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
    }

private:
    std::vector<Flag> m_flags;
    std::vector<Argument> m_args; // TODO: Mendatory args
};

bool Parse(ArgumentsDefinition const &definition, int argc, char const *argv[])
{
    Path app_path{std::string(argv[0])};

    return false;
}
