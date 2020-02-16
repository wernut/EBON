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
        m_application->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Enabling wiremesh mode:
        // m_application->ToggleWiremeshMode();

        glEnable(GL_DEPTH_TEST);

        // Update game:
        Update();
    }
}
  
void Game::Update()
{
    // Creating some test obj models:
    //RawModel bunny ("..\\Models\\Bunny.obj",  ShaderManager::DEFAULT);

    //RawModel texturedCube(Primitives::generateCube("..\\Textures\\container.jpg"), ShaderManager::TEXTURED);
   // RawModel texturedPlane(Primitives::generatePlane(50, "..\\Textures\\grass.jpg"), ShaderManager::TERRAIN);
    RawModel sphere(Primitives::generateSphere(1.0f, 36.0f, 18.0f, "..\\Textures\\earth_diffuse.jpg"), ShaderManager::TEXTURED);

    sphere.setRotation(-60, glm::vec3(1, 0, 0));
    sphere.setRotation(-45, glm::vec3(1, 0, 1));
    //texturedPlane.setPosition(glm::vec3(-25, -2, -25));

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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 1);
        sphere.setRotation(-deltaTime * 10, glm::vec3(0, 0, 1));
        sphere.render(m_camera);

        /*glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 1);
        texturedCube.render(m_camera);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 2);
        texturedPlane.render(m_camera);*/

        // Swapping the buffers:
        m_application->SwapBuffers();
    }
}
