//Author: Pablo "Pau" Core Palmero
//Date: 7-Obtober-2024
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

Mesh::~Mesh() {
  LOG_F(INFO, "Destructing Mesh");
}

float* Mesh::GetVertexData() const {
  return mesh_data_->vertex_data.data();
}

unsigned int Mesh::GetVertexDataSizeb() const {
  return mesh_data_->vertex_data.size() * sizeof(float);
}

void Mesh::Triangle() {
    if(mesh_data_ != nullptr) {
        if(mesh_data_->vertex_data.size() != 0) { mesh_data_->vertex_data.clear(); }

        mesh_data_->vertex_data = {
            -0.5f, -0.5f, 0.0f, // bottom left
            0.5f, -0.5f, 0.0f, // bottom right
            0.0f, 0.5f, 0.0f // top
        };
    }
}

void Mesh::Square() {
    if(mesh_data_ != nullptr) {
        if(mesh_data_->vertex_data.size() != 0) { mesh_data_->vertex_data.clear(); }
    mesh_data_->vertex_data = {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, // top right

        -0.5f, -0.5f, 0.0f, // top right
        0.5f, 0.5f, 0.0f, // top left
        -0.5f, 0.5f, 0.0f // bottom left
    };

    }
}

void Mesh::Cube(){
    /*
    if(mesh_data_ != nullptr) {
        if(mesh_data_->vertex_data.size() != 0) { mesh_data_->vertex_data.clear(); }

        mesh_data_->vertex_data = {
            // Cara frontal
            -0.5f, -0.5f, 0.5f, // bottom left
            0.5f, -0.5f, 0.5f, // bottom right
            0.5f, 0.5f, 0.5f, // top right
            0.5f, 0.5f, 0.5f, // top right
            -0.5f, 0.5f, 0.5f, // top left
            -0.5f, -0.5f, 0.5f, // bottom left

            // Cara trasera
            -0.5f, -0.5f, -0.5f, // bottom left
            0.5f, -0.5f, -0.5f, // bottom right
            0.5f, 0.5f, -0.5f, // top right
            0.5f, 0.5f, -0.5f, // top right
            -0.5f, 0.5f, -0.5f, // top left
            -0.5f, -0.5f, -0.5f, // bottom left

            // Cara izquierda
            -0.5f, -0.5f, -0.5f, // bottom left
            -0.5f, -0.5f, 0.5f, // bottom right
            -0.5f, 0.5f, 0.5f, // top right
            -0.5f, 0.5f, 0.5f, // top right
            -0.5f, 0.5f, -0.5f, // top left
            -0.5f, -0.5f, -0.5f, // bottom left

            // Cara derecha
            0.5f, -0.5f, -0.5f, // bottom left
            0.5f, -0.5f, 0.5f, // bottom right
            0.5f, 0.5f, 0.5f, // top right
            0.5f, 0.5f, 0.5f, // top right
            0.5f, 0.5f, -0.5f, // top left
            0.5f, -0.5f, -0.5f, // bottom left

            // Cara superior
            -0.5f, 0.5f, -0.5f, // bottom left
            0.5f, 0.5f, -0.5f, // bottom right
            0.5f, 0.5f, 0.5f, // top right
            0.5f, 0.5f, 0.5f, // top right
            -0.5f, 0.5f, 0.5f, // top left
            -0.5f, 0.5f, -0.5f, // bottom left

            // Cara inferior
            -0.5f, -0.5f, -0.5f, // bottom left
            0.5f, -0.5f, -0.5f, // bottom right
            0.5f, -0.5f, 0.5f, // top right
            0.5f, -0.5f, 0.5f, // top right
            -0.5f, -0.5f, 0.5f, // top left
            -0.5f, -0.5f, -0.5f // bottom left
        };
    }
    */
}

void Mesh::Sphere(){
    /*
    if(mesh_data_ != nullptr) {
        if(mesh_data_->vertex_data.size() != 0) { mesh_data_->vertex_data.clear(); }

        float M_PI = 3.14159265358979323846f;
        const int num_latitude = 20; // Número de divisiones en latitud
        const int num_longitude = 20; // Número de divisiones en longitud
        const float radius = 0.5f; // Radio de la esfera

        for (int i = 0; i <= num_latitude; ++i) {
            float theta = i * M_PI / num_latitude; // Ángulo de latitud
            float sin_theta = sinf(theta);
            float cos_theta = cosf(theta);

            for (int j = 0; j <= num_longitude; ++j) {
                float phi = j * 2.0f * M_PI / num_longitude; // Ángulo de longitud
                float sin_phi = sinf(phi);
                float cos_phi = cosf(phi);

                float x = radius * cos_phi * sin_theta;
                float y = radius * cos_theta;
                float z = radius * sin_phi * sin_theta;

                mesh_data_->vertex_data.push_back(x);
                mesh_data_->vertex_data.push_back(y);
                mesh_data_->vertex_data.push_back(z);
            }
        }

    }
    */
}

