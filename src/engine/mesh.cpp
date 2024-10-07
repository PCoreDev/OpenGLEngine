//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.
#include "engine/mesh.h"
#include "loguru/loguru.hpp"
#include <vector>

struct MeshData {
  std::vector<float> vertex_data;
  std::vector<unsigned int> index_data;
  MeshData() {}
};

Mesh::Mesh() {
  LOG_F(INFO, "Constructing Mesh");
  mesh_data_ = std::make_unique<MeshData>();
}
