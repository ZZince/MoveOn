#include <OpenGL/GLFW/glfw3.h>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Mesh.hpp"

class Input{
    public:
        Input(Mesh *mesh, bool (*processInput)(Mesh*, float));
        bool process(float deltaTime);

    private:
        Mesh *mesh;
        bool (*processInput)(Mesh*, float);
};

class InputProcessor{
    public:
        InputProcessor(GLFWwindow *window);
        bool addInput(int glfw_key, Mesh* mesh, bool (*processInput)(Mesh*, float));
        bool processAll(float deltaTime);

    private:
        GLFWwindow *m_window;
        std::unordered_map<
        int,
        std::vector<std::unique_ptr<Input>>
    > m_inputs;


};
