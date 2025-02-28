#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <cstdio>  
#include <cmath>  
#include <chrono>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Scene scene;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float rotationSpeed = 0.1f; // Vitesse de rotation
float cameraSpeed = 0.01f; // Vitesse de déplacement

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if (!scene.m_cameras.empty()) {
        float aspect = (float)width / (float)height;
        scene.m_cameras[0]->UpdateProjectionMatrix(45.0f, aspect, 0.1f, 100.0f);
    }
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (scene.m_cameras.empty()) return;
    Camera* cam = scene.m_cameras[0];

    float radPitch = glm::radians(cam->pitch);
    float radYaw = glm::radians(cam->yaw);

    glm::vec3 front;
    front.x = cos(radYaw) * cos(radPitch);
    front.y = sin(radPitch);
    front.z = sin(radYaw) * cos(radPitch);
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
    glm::vec3 up = glm::normalize(glm::cross(right, front));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam->x += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam->x -= cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam->x += front.x * cameraSpeed;
        cam->y += front.y * cameraSpeed;
        cam->z += front.z * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam->x -= front.x * cameraSpeed;
        cam->y -= front.y * cameraSpeed;
        cam->z -= front.z * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam->pitch += rotationSpeed;
        if (cam->pitch > 89.0f) cam->pitch = 89.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam->pitch -= rotationSpeed;
        if (cam->pitch < -89.0f) cam->pitch = -89.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam->yaw -= rotationSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam->yaw += rotationSpeed;
    }

    if (cam->yaw >= 360.0f)  cam->yaw -= 360.0f;
    if (cam->yaw < 0.0f)     cam->yaw += 360.0f;

    if (cam->pitch > 89.0f)  cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;

    cam->UpdateViewMatrix();
}

int main()
{
    if (!glfwInit()) {
        std::cerr << "Echec d'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Projet OpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Echec de creation de la fenetre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Echec d'initialisation de GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Camera* camera = new Camera(0.0f, 0.0f, 5.0f);
    scene.AddCamera(camera);

    Light* light = new Light(0.0f, 5.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    scene.AddLight(light);

    Light* light2 = new Light(25.0f, 7.0f, -8.0f, 1.0f, 1.0f, 1.0f);
    scene.AddLight(light2);

    Shader* basic_shader = new Shader("Basic_Vertex_Shader.glsl", "Basic_Fragment_Shader.glsl");
	Shader* cartoon_shader = new Shader("Cartoon_Vertex_Shader.glsl", "Cartoon_Fragment_Shader.glsl");
	Shader* phong_shader = new Shader("Phong_Vertex_Shader.glsl", "Phong_Fragment_Shader.glsl");

    Mesh recLight1;
	recLight1.CreateQuad({ 1.0f, 1.0f, 1.0f });
	recLight1.Translation(0.0f, 5.0f, 0.0f);
	recLight1.SetShader(basic_shader);
	recLight1.Change_Color(1.0f, 1.0f, 1.0f);
	recLight1.ComputeNormals();
	recLight1.SetupMesh();
	scene.AddMesh(&recLight1);

	Mesh recLight2;
	recLight2.CreateQuad({ 1.0f, 1.0f, 1.0f });
	recLight2.Translation(25.0f, 7.0f, -8.0f);
	recLight2.SetShader(basic_shader);
	recLight2.Change_Color(1.0f, 1.0f, 0.0f);
	recLight2.ComputeNormals();
	recLight2.SetupMesh();
	scene.AddMesh(&recLight2);

    Mesh rec;
    rec.CreateQuad({ 2.0f, 1.0f, 3.0f });
    rec.SetShader(basic_shader);
	rec.Change_Color(0.0f, 0.5f, 0.0f);
	rec.ComputeNormals();
	rec.SetupMesh();
    scene.AddMesh(&rec);

    /*
    Mesh ground;
	ground.CreateQuad({ 100.0f, 1.0f, 100.0f });
	ground.Translation(0.0f, -1.0f, 0.0f);
	ground.SetShader(basic_shader);
	ground.Change_Color(1.0f, 1.0f, 1.0f);
	ground.ComputeNormals();
	ground.SetupMesh();
	scene.AddMesh(&ground);
    */

    Mesh sphere;
    sphere.CreateSphere({4.0f, 64, 64});
    sphere.SetShader(cartoon_shader);
	sphere.Translation(10.0f, 1.0f, 0.0f);
	sphere.Change_Color(1.0f, 0.0f, 0.0f);
	sphere.ComputeNormals();
	sphere.SetupMesh();
    scene.AddMesh(&sphere);

	Mesh sphere2;
	sphere2.CreateSphere({ 4.0f, 64, 64 });
	sphere2.SetShader(phong_shader);
	sphere2.Translation(-10.0f, 8.0f, 1.0f);
	sphere2.Change_Color(0.0f, 0.0f, 1.0f);
	sphere2.ComputeNormals();
	sphere2.SetupMesh();
	scene.AddMesh(&sphere2);

    auto lastTime = std::chrono::high_resolution_clock::now();
    float fps = 0.0f;
    int frameCount = 0;
    Camera* cam = scene.m_cameras[0];

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastTime;

        if (elapsed.count() >= 1.0f) {
            fps = frameCount / elapsed.count(); 
            frameCount = 0;
            lastTime = currentTime; 
        }

        std::printf(
            "\rCamera Pos: (%.2f, %.2f, %.2f)  Rot(pitch,yaw): (%.2f, %.2f) FPS: %.0f  ",
            cam->x, cam->y, cam->z,
            cam->pitch, cam->yaw, fps
        );
        fflush(stdout);
    }

    glfwTerminate();
    return 0;
}