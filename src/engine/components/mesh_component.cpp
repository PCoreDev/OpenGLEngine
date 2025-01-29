#include "engine/components/mesh_component.h"

#include <vector>

#include "loguru/loguru.hpp"
#include "glad/glad.h"

#include "engine/entity.h"
#include "engine/components/material_component.h"

#include "OBJ_Loader.h"
#include "stb/stb_image.h"

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
};

struct Mesh {
  std::vector<Vertex> vertex;
  std::vector<unsigned int> index;
  unsigned int vao, vbo, ibo;
};

struct MeshData {
  std::vector<Mesh> meshes;
  void Bind();
};



void MeshData::Bind() {

  for (auto& mesh : meshes) {

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex.size() * sizeof(Vertex), &mesh.vertex[0], GL_STATIC_DRAW);

    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index.size() * sizeof(unsigned int), &mesh.index[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); //Be carrefull with this

  }
}

MeshComponent::MeshComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Mesh;
  data_ = std::make_unique<MeshData>();
}

MeshComponent::MeshComponent(const MeshComponent& other){
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<MeshData>(*other.data_);
}

MeshComponent::MeshComponent(MeshComponent&& other) noexcept  {
  this->id = other.id;
  this->type = other.type;
  data_ = std::move(other.data_);
}

MeshComponent::~MeshComponent() = default;

MeshComponent& MeshComponent::operator=(MeshComponent&& other) noexcept
{
  this->id = other.id;
  this->type = other.type;
  data_ = std::move(other.data_);
  return *this;
}

void MeshComponent::operator=(const MeshComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<MeshData>(*other.data_);
}

void MeshComponent::Triangle() {
  if (data_ != nullptr) {
    Mesh mesh;
    if (data_->meshes.size() != 0) { data_->meshes.clear(); }
    Vertex vertex_data[] = {
      {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}
    };
    unsigned int index_data[] = { 0, 1, 2 };
    mesh.vertex = std::vector<Vertex>(vertex_data, vertex_data + sizeof(vertex_data) / sizeof(Vertex));
    mesh.index = std::vector<unsigned int>(index_data, index_data + sizeof(index_data) / sizeof(unsigned int));
    data_->meshes.push_back(mesh);
    data_->Bind();
  }
}

void MeshComponent::Square() {
  if (data_ != nullptr) {
    Mesh mesh;
    if (data_->meshes.size() != 0) { data_->meshes.clear(); }
    Vertex vertex_data[] = {
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}
    };
    unsigned int index_data[] = {
      0,1,3,
      1,2,3
    };
    mesh.vertex = std::vector<Vertex>(vertex_data, vertex_data + sizeof(vertex_data) / sizeof(Vertex));
    mesh.index = std::vector<unsigned int>(index_data, index_data + sizeof(index_data) / sizeof(unsigned int));
    data_->meshes.push_back(mesh);
    data_->Bind();
  }
}

void MeshComponent::SkyBox() {
  if (data_ != nullptr) {
    Mesh mesh;
    if (data_->meshes.size() != 0) { data_->meshes.clear(); }

    Vertex vertex_data[] = {
      // Front
      {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      // Bottom
      {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
      {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      // Back
      {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      // Right
      {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // Left
      {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // Up
      {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
    };

    unsigned int index_data[] = {
      // Front
      1, 0, 3, 3, 2, 1,
      // Bottom
      5, 4, 7, 7, 6, 5,
      // Back
      9, 8, 11, 11, 10, 9,
      // Right
      13, 12, 15, 15, 14, 13,
      // Left
      17, 16, 19, 19, 18, 17,
      // Up
      21, 20, 23, 23, 22, 21
    };

    mesh.vertex.assign(std::begin(vertex_data), std::end(vertex_data));
    mesh.index.assign(std::begin(index_data), std::end(index_data));
    data_->meshes.push_back(mesh);
    data_->Bind();
  }
}

void MeshComponent::Cube() {
  if (data_ != nullptr) {
    Mesh mesh;
    if (data_->meshes.size() != 0) { data_->meshes.clear(); }

    Vertex vertex_data[] = {
      // Front
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{ 1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{ 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      // Bottom
      {{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
      {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
      {{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      // Back
      {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      // Right
      {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // Left
      {{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // Up
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      {{ 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ 1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
    };

    unsigned int index_data[] = { //Clockwise
      // Front 0, 1, 2, 3
      0,1,3,
      1,2,3,

      //Bottom 4, 5, 6, 7
      4,5,7,
      5,6,7,

      //Back 8, 9, 10, 11
      8,9,11,
      9,10,11,

      //Right 12, 13, 14, 15
      12,13,15,
      13,14,15,

      //Left 16, 17, 18, 19
      16,17,19,
      17,18,19,

      //Up 20, 21, 22, 23
      20,21,23,
      21,22,23
    };

    mesh.vertex.assign(std::begin(vertex_data), std::end(vertex_data));
    mesh.index.assign(std::begin(index_data), std::end(index_data));
    data_->meshes.push_back(mesh);
    data_->Bind();
  }
}

bool MeshComponent::LoadOBJ(const std::string& obj_path, const std::string& texture_path) {
    
  objl::Loader loader;

  if (!loader.LoadFile(obj_path)) {
    std::cerr << "Failed to load OBJ file: " << obj_path << std::endl;
    return false;
  }

  if (data_ != nullptr) {
    auto material_component = entity.lock()->GetMaterialComponent();
    if (material_component == nullptr) {
      entity.lock()->AddMaterialComponent();
      material_component = entity.lock()->GetMaterialComponent();
    }
    std::string path = texture_path + "textures/";

    if (data_->meshes.size() != 0) { data_->meshes.clear(); }
    for (const auto& shape : loader.LoadedMeshes) {
      Mesh mesh; //Create a new mesh to add to the vector

      //Create a new material for the new mesh
      material_component->AddNewMaterial(
        shape.MeshMaterial.name,
        path + shape.MeshMaterial.map_Kd,
        path + shape.MeshMaterial.map_Ka,
        path + shape.MeshMaterial.map_Ks,
        path + shape.MeshMaterial.map_d,
        path + shape.MeshMaterial.map_bump,
        path + shape.MeshMaterial.map_Ns,
        glm::vec3(shape.MeshMaterial.Ka.X, shape.MeshMaterial.Ka.Y, shape.MeshMaterial.Ka.Z),
        glm::vec3(shape.MeshMaterial.Kd.X, shape.MeshMaterial.Kd.Y, shape.MeshMaterial.Kd.Z),
        glm::vec3(shape.MeshMaterial.Ks.X, shape.MeshMaterial.Ks.Y, shape.MeshMaterial.Ks.Z),
        shape.MeshMaterial.Ns,
        shape.MeshMaterial.d,
        shape.MeshMaterial.Ni,
        shape.MeshMaterial.illum
      );

      //Loop through the vertices and indices of the shape and add them to the mesh
      for (const auto& vertex : shape.Vertices) {
        Vertex v;
        v.position = { vertex.Position.X, vertex.Position.Y, vertex.Position.Z };
        v.normal = { vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z };
        v.uv = { vertex.TextureCoordinate.X, -vertex.TextureCoordinate.Y };
        mesh.vertex.push_back(v);
      }
      for (const auto& index : shape.Indices) {
        mesh.index.push_back(index);
      }
      data_->meshes.push_back(mesh);
    }

    //Bind the data
    data_->Bind();
  }

  return true;
}

int MeshComponent::GetMeshCount() const
{
  return data_->meshes.size();
}

std::vector<size_t> MeshComponent::GetVertexCount(){
  std::vector<size_t> vertex_count;
  for (const auto& mesh : data_->meshes) {
    vertex_count.push_back(mesh.vertex.size());
  }
  return vertex_count;
}

std::vector<unsigned int> MeshComponent::GetVAO(){
  std::vector<unsigned int> vaos;
  for (const auto& mesh : data_->meshes) {
    vaos.push_back(mesh.vao);
  }
  return vaos;
}

std::vector<unsigned int> MeshComponent::GetVBO() {
  std::vector<unsigned int> vbos;
  for (const auto& mesh : data_->meshes) {
    vbos.push_back(mesh.vbo);
  }
  return vbos;
}

std::vector<unsigned int> MeshComponent::GetIBO() {
  std::vector<unsigned int> ibos;
  for (const auto& mesh : data_->meshes) {
    ibos.push_back(mesh.ibo);
  }
  return ibos;
}

void MeshComponent::CleanUp(){
  for (auto& mesh : data_->meshes) {
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ibo);
    glDeleteVertexArrays(1, &mesh.vao);
  }
  data_.reset();
}
