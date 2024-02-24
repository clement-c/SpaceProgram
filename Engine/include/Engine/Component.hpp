#pragma once
#include <bitset>
#include <limits>
#include <string>

using ComponentType = uint8_t;
static constexpr ComponentType kMaxComponents = std::numeric_limits<ComponentType>::max(); // 256 ids
using ComponentsSignature = std::bitset<kMaxComponents>;

struct Component
{

private:
    // std::vector<std::pair<std::string, std::tuple<DataType>>> m_data;

    /**
     * All static components are registered in batch at Engine initialization
     * ???
     * Register("")
     * Register("Transform", {
     *      Field<Xform>("transformMatrix")
     * })
     */

    static ComponentType Register(std::string const &name /* version, dataFields */);
    // static ComponentType Register(/*ComponentBlueprint*/); // ComponentBlueprint: created at runtime of from text/json to define structure

    // void* DataPtr(void* field_offset = nullptr);
};
