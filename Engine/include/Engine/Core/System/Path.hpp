#pragma once
#include <string_view>
#include <filesystem>

struct Path
{

    Path(std::string_view path) : m_p{path} {}
    Path(std::string const &path) : m_p{path} {}
    explicit Path(std::filesystem::path const &path) : m_p{path} {}

    bool Exists() const
    {
        return std::filesystem::exists(m_p);
    }

    bool IsFile() const
    {
        return std::filesystem::is_regular_file(m_p);
    }

    bool IsDirectory() const
    {
        return std::filesystem::is_directory(m_p);
    }

    bool IsLink() const
    {
        return std::filesystem::is_symlink(m_p);
    }

    Path Filename() const
    {
        if (IsDirectory())
            return *this;
        return Path(std::filesystem::path(m_p).filename());
    }

    /**
     * @brief Returns the extension of the path (with its ".")
     *
     * @return std::string
     */
    std::string Extension() const
    {
        return Filename().m_p.extension().string();
    }

    Path Directory() const
    {
        if (IsDirectory())
            return *this;
        return Path(std::filesystem::path(m_p).remove_filename());
    }

    Path Catenate(Path const &tailPath) const
    {
        return Path(m_p / tailPath.m_p);
    }

    Path Catenate(std::string const &tailPath) const
    {
        return Path(m_p / std::filesystem::path(tailPath));
    }

    Path &CatenateInPlace(Path const &tailPath)
    {
        m_p /= tailPath.m_p;
        return *this;
    }

    Path &Normalize()
    {
        std::filesystem::path canonicalPath = std::filesystem::weakly_canonical(m_p);
        m_p = canonicalPath.make_preferred();
    }

    Path Normalized() const
    {
        return Path(std::filesystem::weakly_canonical(m_p).make_preferred());
    }

    inline std::string ToString() const
    {
        return Normalized().m_p.string();
    }

    bool operator==(Path const &other) { return m_p == other.m_p; }
    Path operator/(Path const &other) { return Path(m_p / other.m_p); }

protected:
    std::filesystem::path m_p;
};
