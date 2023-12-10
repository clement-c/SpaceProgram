#pragma once

#include <string>


struct Component
{

private:
    // std::vector<std::pair<std::string, std::tuple<DataType>>> m_data;

    /**
     * All static components are registered in batch at Engine initialization
     * Register("Transform", {
     *      Field<Xform>("transformMatrix")
     * })
     */

    struct TypeId {};

    static TypeId Register(std::string const& name /*, dataFields */);

    void* DataPtr(void* field_offset = nullptr);

};
