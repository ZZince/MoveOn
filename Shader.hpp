#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int m_programID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void Use() const;

    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform3f(const std::string& name, float x, float y, float z) const;
    void setUniformMat4(const std::string& name, const glm::mat4& mat) const;

private:
    std::string LoadSourceFromFile(const char* filePath) const;
    unsigned int CompileShader(unsigned int type, const std::string& source) const;
    void CheckCompileErrors(unsigned int shader, const std::string& type) const;
};

#endif
