#pragma once
#include <memory>

class Mesh
{
public:
  Mesh();
  ~Mesh();

private:
  std::unique_ptr<class MeshData> mesh_data_;
};
