#include "Shader.hpp"
#include <glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = LoadSourceFromFile(vertexPath);
    std::string fragmentCode = LoadSourceFromFile(fragmentPath);

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);

    int success;
    char infoLog[1024];
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_programID, 1024, NULL, infoLog);
        std::cerr << "ERREUR DE LINKAGE DU PROGRAMME: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() const
{
    glUseProgram(m_programID);
}

void Shader::setUniform(const std::string& name, float value) const
{
    int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, int value) const
{
    int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1i(location, value);
}

void Shader::setUniform3f(const std::string& name, float x, float y, float z) const
{
    int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform3f(location, x, y, z);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat) const
{
    int location = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}


std::string Shader::LoadSourceFromFile(const char* filePath) const
{
    std::ifstream file;
    std::stringstream buffer;

    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "Impossible de lire le fichier " << filePath << std::endl;
        return std::string();
    }

    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    if (type == GL_VERTEX_SHADER)
        CheckCompileErrors(shader, "VERTEX");
    else if (type == GL_FRAGMENT_SHADER)
        CheckCompileErrors(shader, "FRAGMENT");

    return shader;
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) const
{
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERREUR DE COMPILATION SHADER " << type << ":\n" << infoLog << std::endl;
    }
}
