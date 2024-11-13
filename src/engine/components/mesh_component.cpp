#include "engine/components/mesh_component.h"

#include <vector>

#include "loguru/loguru.hpp"
#include "glad/glad.h"

#include "engine/entity.h"
#include "engine/components/material_component.h"

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

  glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), &vertex_data[0], GL_STATIC_DRAW);
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
    if (data_->vertex_data.size() != 0) { data_->vertex_data.clear(); }

    data_->vertex_data = {
      -0.5f, -0.5f, 0.0f, // bottom left
      0.5f, -0.5f, 0.0f, // bottom right
      0.0f, 0.5f, 0.0f // top
    };

    data_->normal_data = {
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f
    };

    data_->index_data = {
      0, 1, 2
    };
  }
  data_->n_vertex = 3;
  data_->Bind();
}

void MeshComponent::Square() {
  if (data_ != nullptr) {
    if (data_->vertex_data.size() != 0) { data_->vertex_data.clear(); }
    data_->vertex_data = {
         -1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
         1.0f, 1.0f, 1.0f
    };

    data_->index_data = {
        0,1,3,
        1,2,3
    };

    data_->normal_data = {
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f
    };
    data_->uv_data = {
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f
    };

    data_->n_vertex = 6;

  }
  data_->Bind();
}

void MeshComponent::SkyBox() {
  if (data_ != nullptr) {
    if (data_->vertex_data.size() != 0) { data_->vertex_data.clear(); }
    data_->vertex_data = {
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

    data_->normal_data = {
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

    data_->uv_data = {
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

    data_->index_data = { //counter clockwise
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

    data_->n_vertex = 24;

    data_->Bind();
  }
}

void MeshComponent::Cube() {
  if (data_ != nullptr) {
    if (data_->vertex_data.size() != 0) { data_->vertex_data.clear(); }
    data_->vertex_data = {
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

    data_->normal_data = {
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

    data_->uv_data = {
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

    data_->index_data = { //Clockwise
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

    data_->n_vertex = 24;

    data_->Bind();
  }
}

void MeshComponent::Sphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
  double M_PI = 3.14159265358979323846;
  if (data_ != nullptr) {
    if (data_->vertex_data.size() != 0) { data_->vertex_data.clear(); }
    if (data_->normal_data.size() != 0) { data_->normal_data.clear(); }
    if (data_->uv_data.size() != 0) { data_->uv_data.clear(); }
    if (data_->index_data.size() != 0) { data_->index_data.clear(); }

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
    data_->vertex_data = vertices;
    data_->normal_data = normals;
    data_->uv_data = texCoords;
    data_->index_data = indices;
    data_->n_vertex = static_cast<unsigned int>(vertices.size() / 3);

    data_->Bind();
  }
}

/*void loadOBJ(const std::string& filename, std::vector<Mesh>& meshes, std::vector<Material>& materials) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> objMaterials;

    std::string err;
    if (!tinyobj::LoadObj(&attrib, &shapes, &objMaterials, &err, filename.c_str())) {
        std::cerr << "Error loading OBJ file: " << err << std::endl;
        return;
    }

    // Load each shape as a mesh
    for (size_t s = 0; s < shapes.size(); s++) {
        Mesh mesh;

        // Load vertex data (positions, normals, texcoords)
        for (size_t v = 0; v < shapes[s].mesh.indices.size(); v++) {
            tinyobj::index_t idx = shapes[s].mesh.indices[v];

            // Extract vertices, normals, texture coords, and create the Mesh
            mesh.vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
            mesh.vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
            mesh.vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

            // If texture coords exist
            if (idx.texcoord_index >= 0) {
                mesh.vertices.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
                mesh.vertices.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
            }

            // Add index
            mesh.indices.push_back(v);
        }

        // Setup mesh buffers (VAO, VBO, EBO)
        mesh.setupMesh();
        meshes.push_back(mesh);
        
        // Load the material for this mesh
        tinyobj::material_t mat = objMaterials[s]; // Get the corresponding material

        // Check if the material has a diffuse texture
        if (!mat.diffuse_texname.empty()) {
            Texture tex;
            tex.id = loadTexture(mat.diffuse_texname);  // Load the texture using stb_image
            tex.type = "diffuse";
            tex.path = mat.diffuse_texname;
            
            Material material(glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]), tex);
            materials.push_back(material);
        }
    }
}*/


bool MeshComponent::LoadOBJ(const std::string& obj_path, const std::string& texture_path) {
    
  objl::Loader loader;

  if (!loader.LoadFile(obj_path)) {
    std::cerr << "Failed to load OBJ file: " << obj_path << std::endl;
    return false;
  }

  // Process loaded vertices, normals, texture coordinates
  for (const auto& vertex : loader.LoadedVertices) {
    data_->vertex_data.push_back(vertex.Position.X);
    data_->vertex_data.push_back(vertex.Position.Y);
    data_->vertex_data.push_back(vertex.Position.Z);

    data_->normal_data.push_back(vertex.Normal.X);
    data_->normal_data.push_back(vertex.Normal.Y);
    data_->normal_data.push_back(vertex.Normal.Z);
       
    data_->uv_data.push_back(vertex.TextureCoordinate.X);
    data_->uv_data.push_back(vertex.TextureCoordinate.Y);
  }

  // Process indices
  for (const auto& index : loader.LoadedIndices) {
    data_->index_data.push_back(index);
  }

  // Process materials

  if (loader.LoadedMaterials.empty()) {
    LOG_F(INFO, "No materials loaded");
  }else{
    std::shared_ptr<MaterialComponent> material_component = entity.lock()->GetMaterialComponent();
    if (material_component == nullptr) {
      LOG_F(ERROR, "Material component not found");
    }
    else {
      entity.lock()->AddMaterialComponent();
      material_component = entity.lock()->GetMaterialComponent();
    }

    if (material_component == nullptr) {
      LOG_F(ERROR, "Material component not found");
    }
    else {
      for (const auto& material : loader.LoadedMaterials) {
        std::string path = material.map_Ka;
        std::string full_path = texture_path + path;
        path.erase(0, 3);
        if (path != "") {
         // int n = material_component->AddNewMaterial();
          material_component->LoadTexture(full_path);
          
          material_component->SetAmbient(material.Ka.X, material.Ka.Y, material.Ka.Z);
          material_component->SetDiffuse(material.Kd.X, material.Kd.Y, material.Kd.Z);
          material_component->SetSpecular(material.Ks.X, material.Ks.Y, material.Ks.Z);
          material_component->SetShininess(material.Ns);
          
          LOG_F(INFO, "Material loaded: %s", material.name.c_str());
          LOG_F(INFO, "Material Path: %s%s", texture_path.c_str(), path.c_str());
        }
      }
      material_component->ProcessAllMaterials();
    }
  }

  data_->n_vertex = loader.LoadedVertices.size();
  data_->Bind();

  return true;
}

float* MeshComponent::GetVertexData() {
  if (data_->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data retrieved");
    return data_->vertex_data.data();
  }
  return nullptr;
}

size_t MeshComponent::GetVertexSizeb() {
  if (data_->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data size retrieved");
    return data_->vertex_data.size() * sizeof(float);
  }
  return 0;
}

size_t MeshComponent::GetVertexCount() {
  return data_->n_vertex;
}

unsigned int MeshComponent::GetVAO() {
  return data_->vao;
}

unsigned int MeshComponent::GetVBO() {
  return data_->vbo;
}

unsigned int MeshComponent::GetIBO() {
  return data_->ibo;
}

void MeshComponent::SetBack(bool back)
{
  data_->back = back;
}

bool MeshComponent::RenderMode(){
  return data_->back;
}

void MeshComponent::CleanUp(){
  glDeleteBuffers(1, &data_->vbo);
  glDeleteBuffers(1, &data_->nbo);
  glDeleteBuffers(1, &data_->ubo);
  glDeleteBuffers(1, &data_->ibo);
  glDeleteVertexArrays(1, &data_->vao);
  data_.reset();
}
