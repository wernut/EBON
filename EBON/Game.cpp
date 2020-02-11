#include "Game.h"
#include "Directives.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Camera.h"
#include "Primitives.h"
#include "RawModel.h"

Game::Game()
{
    // Creating the application:
    m_application = Application::Create("EBON", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Creating the shader manager:
    m_shaderManager = ShaderManager::Create();
}

Game::~Game() 
{
    // Destorying the shader manager:
    ShaderManager::Destroy();

    // Destroying the app, this should be done last:
    Application::Destroy();
}

void Game::Run()
{
    if (m_application)
    {
        // Setup game:
        m_application->setGameOver(false);

        // Update game:
        Update();
    }
}
  
void Game::Update()
{
    // Getting the window:
    auto window = glfwGetCurrentContext();

    // Creating a final color vector for the fragment shader:
    glm::vec4 color  = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    // Testing some OBJ models:
    RawModel buddha("..\\models\\Buddha.obj", ShaderManager::DEFAULT);
    RawModel bunny ("..\\models\\Bunny.obj",  ShaderManager::DEFAULT);
    RawModel dragon("..\\models\\Dragon.obj", ShaderManager::DEFAULT);
    RawModel lucy  ("..\\models\\Lucy.obj",   ShaderManager::DEFAULT);

    // Set positions:
    buddha.setPosition(glm::vec3(-10.0f, 0.0f, -10.0f));
    bunny.setPosition(glm::vec3 ( 10.0f, 0.0f,  10.0f));
    dragon.setPosition(glm::vec3(-10.0f, 0.0f,  10.0f));
    lucy.setPosition(glm::vec3(   10.0f, 0.0f, -10.0f));

    // Creating a test camera:
    Camera* camera = new Camera();

    // Enabling wiremesh mode:
    m_application->ToggleWiremeshMode();

    // Clearing the color:
    m_application->ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Main game loop:
    while (!m_application->hasWindowClosed() && !m_application->isGameOver())
    {
        // Clearing the buffers:
        m_application->ClearBuffers();

        // Polling the events called in the GLFWwindow:
        m_application->PollEvents();

        // Updating the application:
        m_application->Update();

        // Getting the deltaTime between frames:
        float deltaTime = (float) (m_application->getDeltaTime());

        // Do stuff here! -------------------------------------
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_application->setGameOver(true);

        // Updating the camera class:
        camera->update(deltaTime);

        buddha.draw(camera);
        bunny.draw(camera);
        dragon.draw(camera);
        lucy.draw(camera);

        // Swapping the buffers:
        m_application->SwapBuffers();
    }

    // Deleting the cameras:
    delete camera;
}
