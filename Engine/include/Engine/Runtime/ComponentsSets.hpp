// Helper structs to group the components together, to register them by batch more easily

struct ComponentsSets
{
    static constexpr uint32_t kHierarchyComponents = 1 << 0;
    static constexpr uint32_t kRenderComponents = 1 << 1;
    static constexpr uint32_t kRenderComponentsB = 1 << 2;
};
