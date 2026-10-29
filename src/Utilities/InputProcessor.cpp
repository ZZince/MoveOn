#include <OpenGL/GLFW/glfw3.h>

#include "Utilities/InputProcessor.hpp"
#include "Geometry/Mesh.hpp"

Input::Input(
    Mesh* mesh,
    bool (*processInput)(Mesh*, float))
    : mesh(mesh), processInput(processInput)
{
}

bool Input::process(float deltaTime){
    if (!mesh || !processInput){
        return false;
    }

    return processInput(mesh, deltaTime);
}

InputProcessor::InputProcessor(GLFWwindow* window)
    : m_window(window)
{
}

bool InputProcessor::addInput(int glfw_key, Mesh* mesh, bool (*processInput)(Mesh*, float)){
    if (!mesh || !processInput){
        return false;
    }

    m_inputs[glfw_key].push_back(std::make_unique<Input>(mesh, processInput));

    return true;

}

bool InputProcessor::processAll(float deltaTime){
    bool processed = false;

    for (auto& [key, inputs] : m_inputs){
        if (glfwGetKey(m_window, key) == GLFW_PRESS){
            for (auto& input : inputs){
                if (input->process(deltaTime)){
                    processed = true;
                }
            }
        }
    }

    return processed;
}