#include "engine/components/mesh_component.h"

#include <vector>

#include "loguru/loguru.hpp"
#include "glad/glad.h"

#include "engine/entity.h"
#include "OBJ_Loader/OBJ_Loader.h"

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

void MeshData::Bind() {
  //TODO: Change all to one buffer (vertex, normal, uv)

  glCreateBuffers(1, &vbo); //vertex buffer object
  glCreateBuffers(1, &nbo); //normal buffer object
  glCreateBuffers(1, &ubo); //uv buffer object
  glCreateBuffers(1, &ibo); //index buffer object



  glNamedBufferStorage(vbo, static_cast<GLsizei>(vertex_data.size() * sizeof(float)), vertex_data.data(), GL_DYNAMIC_STORAGE_BIT);
  glNamedBufferStorage(nbo, static_cast<GLsizei>(normal_data.size() * sizeof(float)), normal_data.data(), GL_DYNAMIC_STORAGE_BIT);
  glNamedBufferStorage(ubo, static_cast<GLsizei>(uv_data.size() * sizeof(float)), uv_data.data(), GL_DYNAMIC_STORAGE_BIT);
  glNamedBufferStorage(ibo, static_cast<GLsizei>(index_data.size() * sizeof(unsigned int)), index_data.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float)); //Vertex
  glVertexArrayVertexBuffer(vao, 1, nbo, 0, 3 * sizeof(float)); //Normals
  glVertexArrayVertexBuffer(vao, 2, ubo, 0, 2 * sizeof(float)); //UV

  glEnableVertexArrayAttrib(vao, 0);
  glEnableVertexArrayAttrib(vao, 1);
  glEnableVertexArrayAttrib(vao, 2);

  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
  glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, false, 0);
  glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, false, 0);

  glVertexArrayAttribBinding(vao, 0, 0);
  glVertexArrayAttribBinding(vao, 1, 1);
  glVertexArrayAttribBinding(vao, 2, 2);
}

MeshComponent::MeshComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Mesh;
  data = std::make_unique<MeshData>();
}

MeshComponent::MeshComponent(const MeshComponent& other){
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<MeshData>(*other.data);
}

MeshComponent::MeshComponent(MeshComponent&& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
}

MeshComponent& MeshComponent::operator=(MeshComponent&& other)
{
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
  return *this;
}

void MeshComponent::operator=(const MeshComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<MeshData>(*other.data);
}

void MeshComponent::Triangle() {
  if (data != nullptr) {
    if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }

    data->vertex_data = {
      -0.5f, -0.5f, 0.0f, // bottom left
      0.5f, -0.5f, 0.0f, // bottom right
      0.0f, 0.5f, 0.0f // top
    };

    data->normal_data = {
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f
    };

    data->index_data = {
      0, 1, 2
    };
  }
  data->n_vertex = 3;
  data->Bind();
}

void MeshComponent::Square() {
  if (data != nullptr) {
    if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    data->vertex_data = {
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, 1.0f, 1.0f
    };

    data->index_data = {
        1,0,3,
        3,2,1
    };

    data->normal_data = {
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f
    };
    data->uv_data = {
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f
    };

    data->n_vertex = 6;

  }
  data->Bind();
}

void MeshComponent::SkyBox() {
  if (data != nullptr) {
    if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    data->vertex_data = {
      //Front
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,

         //Bottom
         -1.0f, -1.0f, 1.0f,
         -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, 1.0f,

         //Back
         1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, 1.0f, -1.0f,

         //Right
         1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,

         //Left
         -1.0f, 1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, 1.0f,
         -1.0f, 1.0f, 1.0f,

         //UP
         -1.0f, 1.0f, -1.0f,
         -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, -1.0f
    };

    data->normal_data = {
      //Front
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,

          //Bottom
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,

          //Back
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,

          //Right
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,

          //Left
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,

          //Up
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f
    };

    data->uv_data = {
      //Front
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Bottom
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Back
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Right
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Left
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Up
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f
    };

    data->index_data = { //counter clockwise
      //Front 0, 1, 2, 3
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

    data->n_vertex = 24;

    data->Bind();
  }
}

void MeshComponent::Cube() {
  if (data != nullptr) {
    if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    data->vertex_data = {
      //Front
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,

         //Bottom
         -1.0f, -1.0f, 1.0f,
         -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, 1.0f,

         //Back
         1.0f, 1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, 1.0f, -1.0f,

         //Right
         1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,

         //Left
         -1.0f, 1.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,
         -1.0f, -1.0f, 1.0f,
         -1.0f, 1.0f, 1.0f,

         //UP
         -1.0f, 1.0f, -1.0f,
         -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, -1.0f
    };

    data->normal_data = {
      //Front
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,

          //Bottom
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,
          0.0f, -1.0f, 0.0f,

          //Back
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,
          0.0f, 0.0f, -1.0f,

          //Right
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,

          //Left
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,
          -1.0f, 0.0f, 0.0f,

          //Up
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f
    };

    data->uv_data = {
      //Front
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Bottom
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Back
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Right
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Left
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Up
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f
    };

    data->index_data = { //Clockwise
      //Front 0, 1, 2, 3
        1,0,3,
        3,2,1,

        //Bottom 4, 5, 6, 7
        5,4,7,
        7,6,5,

        //Back 8, 9, 10, 11
        9,8,11,
        11,10,9,

        //Right 12, 13, 14, 15
        13,12,15,
        15,14,13,

        //Left 16, 17, 18, 19
        17,16,19,
        19,18,17,

        //Up 20, 21, 22, 23
        21,20,23,
        23,22,21
    };

    data->n_vertex = 24;

    data->Bind();
  }
}

void MeshComponent::Sphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
  double M_PI = 3.14159265358979323846;
  if (data != nullptr) {
    if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    if (data->normal_data.size() != 0) { data->normal_data.clear(); }
    if (data->uv_data.size() != 0) { data->uv_data.clear(); }
    if (data->index_data.size() != 0) { data->index_data.clear(); }

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (unsigned int i = 0; i <= stackCount; ++i) {
      stackAngle = M_PI / 2 - i * stackStep;        // from pi/2 to -pi/2
      xy = radius * cosf(stackAngle);             // r * cos(u)
      z = radius * sinf(stackAngle);              // r * sin(u)

      for (unsigned int j = 0; j <= sectorCount; ++j) {
        sectorAngle = j * sectorStep;           // from 0 to 2pi

        // vertex position (x, y, z)
        x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
        y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);

        // normalized vertex normal (nx, ny, nz)
        nx = x * lengthInv;
        ny = y * lengthInv;
        nz = z * lengthInv;
        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);

        // vertex tex coord (s, t)
        s = (float)j / sectorCount;
        t = (float)i / stackCount;
        texCoords.push_back(s);
        texCoords.push_back(t);
      }
    }

    // indices
    unsigned int k1, k2;
    for (unsigned int i = 0; i < stackCount; ++i) {
      k1 = i * (sectorCount + 1);     // start of current stack
      k2 = k1 + sectorCount + 1;      // start of next stack

      for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
        // 2 triangles per sector except at the top and bottom
        if (i != 0) {
          indices.push_back(k1);
          indices.push_back(k2);
          indices.push_back(k1 + 1);
        }

        if (i != (stackCount - 1)) {
          indices.push_back(k1 + 1);
          indices.push_back(k2);
          indices.push_back(k2 + 1);
        }
      }
    }

    // Store data in MeshComponent object
    data->vertex_data = vertices;
    data->normal_data = normals;
    data->uv_data = texCoords;
    data->index_data = indices;
    data->n_vertex = static_cast<unsigned int>(vertices.size() / 3);

    data->Bind();
  }
}

bool MeshComponent::LoadOBJ(const std::string& path) {
  FILE* file = fopen(path.c_str(), "r");
  if (file == NULL) {
    LOG_F(ERROR, "Impossible to open the file !");
    return false;
  }

  int res = 0;
  do {
    char lineHeader[128];
    res = fscanf(file, "%s", lineHeader);

    if (strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      data->vertex_data.push_back(vertex.x);
      data->vertex_data.push_back(vertex.y);
      data->vertex_data.push_back(vertex.z);
    }
    else if (strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      data->uv_data.push_back(uv.x);
      data->uv_data.push_back(uv.y);
    }
    else if (strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      data->normal_data.push_back(normal.x);
      data->normal_data.push_back(normal.y);
      data->normal_data.push_back(normal.z);
    }
    else if (strcmp(lineHeader, "f") == 0) {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
      }

      data->index_data.push_back(vertexIndex[0]);
      data->index_data.push_back(vertexIndex[1]);
      data->index_data.push_back(vertexIndex[2]);
      data->index_uv.push_back(uvIndex[0]);
      data->index_uv.push_back(uvIndex[1]);
      data->index_uv.push_back(uvIndex[2]);
      data->index_normals.push_back(normalIndex[0]);
      data->index_normals.push_back(normalIndex[1]);
      data->index_normals.push_back(normalIndex[2]);
    }
  } while (res != EOF);

  data->Bind();

  return true;

  //objl::Loader Loader;
  //bool loadout = Loader.LoadFile(path);
  //if (loadout) {
  //  for (int i = 0; i < Loader.LoadedVertices.size(); i++) {
  //    data->vertex_data.push_back(Loader.LoadedVertices[i].Position.X);
  //    data->vertex_data.push_back(Loader.LoadedVertices[i].Position.Y);
  //    data->vertex_data.push_back(Loader.LoadedVertices[i].Position.Z);

  //    data->normal_data.push_back(Loader.LoadedVertices[i].Normal.X);
  //    data->normal_data.push_back(Loader.LoadedVertices[i].Normal.Y);
  //    data->normal_data.push_back(Loader.LoadedVertices[i].Normal.Z);

  //    data->uv_data.push_back(Loader.LoadedVertices[i].TextureCoordinate.X);
  //    data->uv_data.push_back(Loader.LoadedVertices[i].TextureCoordinate.Y);

  //    data->index_data.push_back(Loader.LoadedIndices[i]);

  //  }
  //  //entity.lock()->GetMaterialComponent()->LoadTexture("../../data/models/Overlord/lord_head_and_back_BaseColor.jpeg");

  //  data->n_vertex = Loader.LoadedVertices.size();
  //  data->Bind();
  //  return true;
  //}

}

float* MeshComponent::GetVertexData() {
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data retrieved");
    return data->vertex_data.data();
  }
  return nullptr;
}

size_t MeshComponent::GetVertexSizeb() {
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data size retrieved");
    return data->vertex_data.size() * sizeof(float);
  }
  return 0;
}

size_t MeshComponent::GetVertexCount() {
  return data->n_vertex;
}

unsigned int MeshComponent::GetVAO() {
  return data->vao;
}

unsigned int MeshComponent::GetVBO() {
  return data->vbo;
}

unsigned int MeshComponent::GetIBO() {
  return data->ibo;
}

void MeshComponent::SetBack(bool back)
{
  data->back = back;
}

bool MeshComponent::RenderMode(){
  return data->back;
}
