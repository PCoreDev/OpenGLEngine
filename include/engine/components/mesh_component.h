#ifndef __MESH_COMPONENT__
#define __MESH_COMPONENT__ 1

#include "engine/component.h"

#include "engine/entity.h"

class MeshComponent : public Component {
public:
  MeshComponent() = default;
  MeshComponent(std::weak_ptr<Entity> entity);
  MeshComponent(const MeshComponent& other);
  MeshComponent(MeshComponent&& other) noexcept;
  ~MeshComponent();
  MeshComponent& operator=(MeshComponent&& other) noexcept;
  void operator=(const MeshComponent& other);
  void Triangle();
  void Square();
  void Cube();
  void SkyBox();
  //void Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);
  bool LoadOBJ(const std::string& obj_path, const std::string& texture_path);

  //float* GetVertexData();
  //size_t GetVertexSizeb();
  int GetMeshCount() const;
  std::vector<size_t> GetVertexCount();
  std::vector<unsigned int> GetVAO();
  std::vector<unsigned int> GetVBO();
  std::vector<unsigned int> GetIBO();
  //void SetBack(bool back);
  //bool RenderMode();

  void CleanUp();

private:
  std::unique_ptr<class MeshData> data_;
};


#endif // !__MESH_COMPONENT__
