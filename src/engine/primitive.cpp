//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class's implementation of the engine to render objectes.
#include "engine/primitive.h"

#include "loguru/loguru.hpp"

#include <vector>

unsigned int Primitive::current_primitives_ = 0;
#define MAX_PRIMITIVES 100

struct PData
{
  std::vector<float> vertex_data;
  int posx, posy, posz;
  PData() : posx(0), posy(0), posz(0) {}
};

Primitive::Primitive()
{
  LOG_F(INFO, "Constructing Primitive");
  pdata_ = std::make_unique<PData>();
}

std::unique_ptr<Primitive> Primitive::CreatePrimitive()
{
  if (Primitive::current_primitives_ < MAX_PRIMITIVES)
  {
    Primitive::current_primitives_++;
    std::unique_ptr<Primitive> p(new Primitive());
    LOG_F(INFO, "Primitive created");
    return p;
  }
  else
  {
    LOG_F(ERROR, "Max number of primitives reached");
    return nullptr;
  }
}

void Primitive::GenerateCube(){
  LOG_F(INFO, "Start Generateing Cube");
 SetVertexData(new float[9]{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}, 9);

}

void Primitive::SetVertexData(float* vertex, int nvertex)
{
  LOG_F(INFO, "Vertex data set");
  //Erase the previous data
  pdata_->vertex_data.clear();
  if(nvertex != pdata_->vertex_data.size())
  {
    //Resize the vector
    pdata_->vertex_data.resize(nvertex);
  }
  for (int i = 0; i < nvertex; i++)
  {
    pdata_->vertex_data[i] = vertex[i];
  }
}

float* Primitive::GetVertexData() const
{
  if (pdata_->vertex_data.size() > 0)
  {
    LOG_F(INFO, "Vertex data retrieved");
    return pdata_->vertex_data.data();
  }
  return nullptr;
}

unsigned int Primitive::GetVertexDataSizeb() const
{
  if (pdata_->vertex_data.size() > 0)
  {
    LOG_F(INFO, "Vertex data size retrieved");
    return pdata_->vertex_data.size() * sizeof(float);
  }
  return 0;
}

Primitive::~Primitive()
{
  Primitive::current_primitives_--;
  LOG_F(INFO, "Primitive destroyed");
}
