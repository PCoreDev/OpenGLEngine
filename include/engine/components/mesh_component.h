#ifndef __MESH_COMPONENT__
#define __MESH_COMPONENT__ 1

#include "engine/component.h"

#include "engine/entity.h"

struct MeshData {
  std::vector<float> vertex_data;
  std::vector<float> normal_data;
  std::vector<float> uv_data;
  std::vector<unsigned int> index_data;
  std::vector<unsigned int> index_uv;
  std::vector<unsigned int> index_normals;
  int n_vertex = 0;
  unsigned int vao, vbo, ibo, nbo, ubo;
  void Bind();
  bool cube;
  bool back = false;

};

class MeshComponent : public Component {
public:
  MeshComponent() = default;
  MeshComponent(std::weak_ptr<Entity> entity);
  MeshComponent(const MeshComponent& other);
  MeshComponent(MeshComponent&& other) noexcept;
  ~MeshComponent() = default;
  MeshComponent& operator=(MeshComponent&& other) noexcept;
  void operator=(const MeshComponent& other);
  void Triangle();
  void Square();
  void Cube();
  void SkyBox();
  void Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);
  bool LoadOBJ(const std::string& obj_path, const std::string& texture_path);

  float* GetVertexData();
  size_t GetVertexSizeb();
  size_t GetVertexCount();
  unsigned int GetVAO();
  unsigned int GetVBO();
  unsigned int GetIBO();
  void SetBack(bool back);
  bool RenderMode();

  void CleanUp();

private:
  std::unique_ptr<MeshData> data_;
};


#endif // !__MESH_COMPONENT__
