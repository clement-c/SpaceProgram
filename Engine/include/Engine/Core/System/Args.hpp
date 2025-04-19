#pragma once

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

struct ArgsParsed
{
    Path ApplicationPath() const;

    std::vector<Value> Positionals() const;

    std::vector<Flag> const &DefinedFlags();
    bool HasFlag(std::string const &name);
    bool HasFlag(Flag const &flag);

    Value GetValue(Flag const &param_name);
    Value GetValue(std::string const &param_name);

private:
    std::vector<Flag> m_defined_flags;
    std::vector<Value> m_values;
};

struct ArgsDefinition
{

    ArgsDefinition &AddFlag(std::string shortNm)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        m_flags.emplace_back(shortNm);
        return *this;
    }
    ArgsDefinition &AddFlag(std::string shortNm, std::string const &longNm)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        if (HasFlag(longNm))
            throw std::runtime_error("A flag is already defined with the long name \"" + longNm + "\"");
        m_flags.emplace_back(shortNm, longNm);
        return *this;
    }
    ArgsDefinition &AddFlag(std::string shortNm, std::string const &longNm, std::string const &help)
    {
        if (HasFlag(shortNm))
            throw std::runtime_error("A flag is already defined with the short name \"" + shortNm + "\"");
        if (HasFlag(longNm))
            throw std::runtime_error("A flag is already defined with the long name \"" + longNm + "\"");
        m_flags.emplace_back(shortNm, longNm, help);
        return *this;
    }

    bool HasFlag(std::string const &flag) const
    {
        if (flag.substr(0, 1) == "-")
        {
            if (flag.substr(1, 1) == "-")
                return std::any_of(m_flags.cbegin(), m_flags.cend(), [&flag](Flag const &f) -> bool
                                   { return f.LongName == flag; });
            else
                return std::any_of(m_flags.cbegin(), m_flags.cend(), [&flag](Flag const &f) -> bool
                                   { return f.ShortName == flag; });
        }
        else
        {
            std::string sn = "-" + flag;
            std::string ln = "--" + flag;
            return std::any_of(m_flags.cbegin(), m_flags.cend(), [&](Flag const &f) -> bool
                               { return f.ShortName == sn || f.LongName == ln; });
        }
        return false;
    }

    ArgsDefinition &AddArgument(std::string shortNm, Type &type, bool multi = false)
    {
        m_args.emplace_back(Flag(shortNm), type, multi);
        return *this;
    }
    ArgsDefinition &AddArgument(std::string shortNm, std::string const &longNm, Type &type, bool multi = false)
    {
        m_args.emplace_back(Flag(shortNm, longNm), type, multi);
        return *this;
    }
    ArgsDefinition &AddArgument(std::string shortNm, std::string const &longNm, std::string const &help, Type &type, bool multi = false)
    {
        m_args.emplace_back(Flag(shortNm, longNm, help), type, multi);
        return *this;
    }
    ArgsDefinition &AddArgument(std::string shortNm, Value const &defaultValue)
    {                                                               // TODO: Multi
        m_args.emplace_back(Flag(shortNm), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
        return *this;
    }
    ArgsDefinition &AddArgument(std::string shortNm, std::string const &longNm, Value const &defaultValue)
    {                                                                       // TODO: Multi
        m_args.emplace_back(Flag(shortNm, longNm), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
        return *this;
    }
    ArgsDefinition &AddArgument(std::string shortNm, std::string const &longNm, Value const &defaultValue, std::string const &help)
    {                                                                             // TODO: Multi
        m_args.emplace_back(Flag(shortNm, longNm, help), defaultValue.GetType()); // FIXME: when value works, set value - currently only default values
        return *this;
    }

    bool PrintHelp(std::ostream &ostream) const;

    bool ParseArgs(int argc, char *argv[], ArgsParsed &out_results)
    {
        ;

        Path app_path{std::string(argv[0])};

        char *curr_flag = nullptr;
        for (auto i = 1u; i < argc; i++)
        {
            // std::cout << i << ": " << argv[i] << std::endl;
            char *curr_arg = argv[i];
            if (curr_arg[0] == '-')
            {
                if (HasFlag(curr_arg))
                {
                    curr_flag = curr_arg;
                    std::cout << '\n'
                              << curr_flag << ": ";
                }
            }
            else if (curr_flag)
            {
                std::cout << curr_arg << ", ";
            }
            else
            {
                std::cout << "\nPositional: " << curr_arg << std::endl;
            }
        }

        return true;
    }

private:
    std::vector<Flag> m_flags;
    std::vector<Argument> m_args; // TODO: Mendatory args
};
