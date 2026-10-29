
#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>
#include <OpenGL/GLM/glm/glm.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <cmath>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "MoveOnObject.hpp"
#include "RendableComponent.hpp"
#include "FPScounter.hpp"
#include "Inputprocessor.hpp"

constexpr float cameraSpeed = 3.0f;
constexpr float rotationSpeed = 90.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    if (height <= 0)
        return;

    Camera *camera = static_cast<Camera *>(
        glfwGetWindowUserPointer(window));

    if (camera)
    {
        camera->UpdateProjectionMatrix(
            45.0f,
            static_cast<float>(width) / height,
            0.1f,
            100.0f);
    }
}

void processInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float movement = cameraSpeed * deltaTime;
    float rotation = rotationSpeed * deltaTime;

    float radPitch = glm::radians(camera.pitch);
    float radYaw = glm::radians(camera.yaw);

    glm::vec3 front(
        std::cos(radYaw) * std::cos(radPitch),
        std::sin(radPitch),
        std::sin(radYaw) * std::cos(radPitch));

    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(
        glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.x += movement;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.x -= movement;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.x += front.x * movement;
        camera.y += front.y * movement;
        camera.z += front.z * movement;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera.x -= front.x * movement;
        camera.y -= front.y * movement;
        camera.z -= front.z * movement;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.pitch += rotation;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.pitch -= rotation;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.yaw -= rotation;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.yaw += rotation;

    camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);

    if (camera.yaw >= 360.0f)
        camera.yaw -= 360.0f;

    if (camera.yaw < 0.0f)
        camera.yaw += 360.0f;

    camera.UpdateViewMatrix();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Echec d'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = monitor ? glfwGetVideoMode(monitor) : nullptr;

    int width = mode ? mode->width : 1280;
    int height = mode ? mode->height : 720;

    GLFWwindow *window = glfwCreateWindow(
        width,
        height,
        "MoveOn",
        nullptr,
        nullptr);

    if (!window)
    {
        std::cerr << "Echec de creation de la fenetre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Echec d'initialisation de GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    {
        Camera camera(0.0f, 0.0f, 8.0f);

        glfwSetWindowUserPointer(window, &camera);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        int framebufferWidth = 0;
        int framebufferHeight = 0;

        glfwGetFramebufferSize(
            window,
            &framebufferWidth,
            &framebufferHeight);

        glViewport(0, 0, framebufferWidth, framebufferHeight);

        if (framebufferHeight > 0)
        {
            camera.UpdateProjectionMatrix(
                45.0f,
                static_cast<float>(framebufferWidth) / framebufferHeight,
                0.1f,
                100.0f);
        }

        Shader basicShader(
            "shaders/Basic_Vertex_Shader.glsl",
            "shaders/Basic_Fragment_Shader.glsl");

        auto cubeMesh = std::make_shared<Mesh>();

        cubeMesh->CreateQuad({1.0f, 1.0f, 1.0f});
        cubeMesh->SetShader(&basicShader);
        cubeMesh->Change_Color(0.0f, 0.0f, 1.0f);
        cubeMesh->ComputeNormals();
        cubeMesh->SetupMesh();

        Scene scene;
        Renderer renderer;

        auto cube1 = std::make_unique<MoveOnObject>();

        cube1->getTransform().setPosition(
            glm::vec3(-2.0f, 0.0f, 0.0f));

        auto rendable1 = std::make_unique<RendableComponent>();
        rendable1->setMesh(cubeMesh);
        cube1->addComponent(std::move(rendable1));
        scene.addObject(std::move(cube1));

        auto cube2 = std::make_unique<MoveOnObject>();

        cube2->getTransform().setPosition(
            glm::vec3(2.0f, 0.0f, 0.0f));

        cube2->getTransform().rotate(
            45.0f,
            glm::vec3(0.0f, 0.0f, 1.0f));

        auto rendable2 = std::make_unique<RendableComponent>();
        rendable2->setColor({0.5f, 0.0f, 1.0f});
        rendable2->setMesh(cubeMesh);

        cube2->addComponent(std::move(rendable2));

        MoveOnObject *rotatingCube = cube2.get();

        scene.addObject(std::move(cube2));

        auto cube3 = std::make_unique<MoveOnObject>();
        cube3->getTransform().setPosition(
            glm::vec3(8.0f, 0.0f, 0.0f));
        cube3->getTransform().rotate(
            45.0f,
            glm::vec3(1.0f, 0.0f, 0.5f));
        cube3->getTransform().setScale(glm::vec3(0.5f, 0.2f, 0.5f));

        auto rendable3 = std::make_unique<RendableComponent>();
        rendable3->setMesh(cubeMesh);
        rendable3->setColor({1.0f, 0.0f, 0.0f});

        cube3->addComponent(std::move(rendable3));
        MoveOnObject *rotatingCube2 = cube3.get();
        scene.addObject(std::move(cube3));

        InputProcessor inputProcessor(window);
        FPSCounter fpsCounter(1.0);

        double lastFrameTime = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            double currentTime = glfwGetTime();

            float deltaTime = static_cast<float>(
                currentTime - lastFrameTime);

            lastFrameTime = currentTime;

            processInput(window, camera, deltaTime);
            inputProcessor.processAll(deltaTime);

            // rotatingCube->getTransform().rotate(
            //  45.0f * deltaTime,
            // glm::vec3(0.0f, 1.0f, 0.0f));

            // rotatingCube2->getTransform().rotate(165.0f * deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));

            scene.update(deltaTime);

            glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            renderer.render(&scene, &camera);

            glfwSwapBuffers(window);
            glfwPollEvents();

            if (fpsCounter.Update())
            {
                std::string title =
                    "MoveOn | FPS: " +
                    std::to_string(
                        static_cast<int>(fpsCounter.GetFPS())) +
                    " | Frame time: " +
                    std::to_string(fpsCounter.GetFrameTime()) +
                    " ms";

                glfwSetWindowTitle(window, title.c_str());
            }
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
