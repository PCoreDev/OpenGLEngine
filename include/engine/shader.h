//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the shader class of the engine.
#ifndef __SHADER_H__
#define __SHADER_H__ 1

#include <string>

class Shader{
    public:
        Shader();
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void LoadShader(const char* path, std::string& shader_data);
        unsigned int VBO, VAO, EBO;
        int vertex_, fragment_, program_;
    private:
        std::string vertex_data_;
        std::string fragment_data_;

};

#endif // !__SHADER_H__
