

struct RenderableSurface
{
    bool AddFaces();

    bool Upload();
    bool Bind() const;

  private:
    int vao_index = -1;
    bool m_dirty = false;
};

