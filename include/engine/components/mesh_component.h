#ifndef __MESH_COMPONENT__
#define __MESH_COMPONENT__ 1

#include "engine/component.h"

#include "engine/entity.h"

class MeshComponent : public Component {
public:
  MeshComponent() = default;
  MeshComponent(std::weak_ptr<Entity> entity);
  MeshComponent(const MeshComponent& other);
  MeshComponent(MeshComponent&& other);
  ~MeshComponent() = default;
  MeshComponent& operator=(MeshComponent&& other);
  void operator=(const MeshComponent& other);
  void Triangle();
  void Square();
  void Cube();
  void SkyBox();
  void Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);
  bool LoadOBJ(const std::string& path);
  float* GetVertexData();
  size_t GetVertexSizeb();
  size_t GetVertexCount();
  unsigned int GetVAO();
  unsigned int GetVBO();
  unsigned int GetIBO();
  void SetBack(bool back);
  bool RenderMode();

private:
  std::unique_ptr<class MeshData> data;
};


#endif // !__MESH_COMPONENT__
