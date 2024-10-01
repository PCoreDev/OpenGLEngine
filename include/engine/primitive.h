//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.
#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__ 1

#include <memory>

class Primitive
{
public:
	static unsigned int current_primitives_;
	static std::unique_ptr<Primitive> CreatePrimitive();
    void GenerateCube();
	void SetVertexData(float* vertex, int nvertex);
	float* GetVertexData() const;
	unsigned int GetVertexDataSizeb() const;
	~Primitive();

private:
	Primitive();

	std::unique_ptr<class PData> pdata_;
};


#endif // !__PRIMITIVE_H__
