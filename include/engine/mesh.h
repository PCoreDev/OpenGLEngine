//Author: Pablo "Pau" Core Palmero
//Date: 7-October-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.

#pragma once
#include <memory>

class Mesh
{
public:
  Mesh();
  ~Mesh();

  float* GetVertexData() const;

  unsigned int GetVertexDataSizeb() const;

  void Triangle();
  void Square();
  void Cube();
  void Sphere();


private:
  std::unique_ptr<class MeshData> mesh_data_;
};
