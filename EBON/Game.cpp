#include "Game.h"
#include "Directives.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Primitives.h"
#include "RawModel.h"

Game::Game()
{
    // Creating the game manager:
    m_gameManager = GameManager::Create("EBON", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Creating the application:
    m_application = m_gameManager->getApplication();

    // Creating the shader manager:
    m_shaderManager = m_gameManager->getShaderManager();

    // Creating the camera:
    m_camera = new Camera();

    // Creating a pointer to the GLFWwindow:
    m_window = m_application->getWindow();
}

Game::~Game() 
{
    // Destroying the camera:
    delete m_camera;

    // Destorying the game manager:
    GameManager::Destroy();
}

void Game::Run()
{
    if (m_application)
    {
        // Setup game:
        m_application->setGameOver(false);

        // Clearing the color: (Making the background white).
        m_application->ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Enabling wiremesh mode:
        m_application->ToggleWiremeshMode();

        // Update game:
        Update();
    }
}
  
void Game::Update()
{
    // Creating some test obj models:
    RawModel bunny ("..\\Models\\Bunny.obj",  ShaderManager::DEFAULT);
    RawModel buddha("..\\Models\\Buddha.obj", ShaderManager::DEFAULT);
    RawModel dragon("..\\Models\\Dragon.obj", ShaderManager::DEFAULT);
    RawModel lucy  ("..\\Models\\Lucy.obj",   ShaderManager::DEFAULT);

    bunny.setPosition(glm::vec3(-10.0f, 0.0f, 0.0f));
    buddha.setPosition(glm::vec3(-10.0f, 0.0f, -10.0f));
    dragon.setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
    lucy.setPosition(glm::vec3(  0.0f, 0.0f, 10.0f));


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
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_application->setGameOver(true);

        // Updating the camera class:
        m_camera->update(deltaTime);

        // Render models:
        bunny.renderOBJ(m_camera);
        buddha.renderOBJ(m_camera);
        dragon.renderOBJ(m_camera);
        lucy.renderOBJ(m_camera);

        // Swapping the buffers:
        m_application->SwapBuffers();
    }
}
