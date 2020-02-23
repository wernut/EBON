#include "Game.h"
#include "Directives.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Primitives.h"
#include "ShaderFade.h"

#define _USE_MATH_DEFINES
#include "math.h"

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

    // Initalising the models:
    InitModels();

    // Creating a pointer to the GLFWwindow:
    m_window = m_application->getWindow();

    // Initalising vars:
    m_canReload = true;
    m_reloadTimer = 0.0f;
}

Game::~Game() 
{
    // Destroying the models:
    delete m_earth;
    m_earth = nullptr;
    delete m_objModel;
    m_objModel = nullptr;
    delete m_earthImage;
    m_earthImage = nullptr;
    delete m_sun;
    m_sun = nullptr;

    // Destroying the camera:
    delete m_camera;
    m_camera = nullptr;

    // Destorying the game manager:
    GameManager::Destroy();
}

void Game::InitModels()
{
    m_earthImage = new Image("..\\Textures\\earth_diffuse.jpg", GL_RGB);
    m_earth = new TexturedModel(m_earthImage, Primitives::generateSphere(1.0f, 36.0f, 18.0f), ShaderManager::TEXTURED);
    m_earth->setRotation(-60, glm::vec3(1, 0, 0));
    m_earth->setRotation(-45, glm::vec3(1, 0, 1));

    m_objModel = new RawModel("..\\Models\\Bunny.obj", ShaderManager::FADE);
    m_objModel->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    m_sun = new RawModel(Primitives::generateSphere(3.0f, 36.0f, 18.0f), ShaderManager::LIGHT);
    m_sun->setPosition(glm::vec3(15.0f, 0.0f, 0.0f));
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
    // Main game loop:
    while (!m_application->hasWindowClosed() && !m_application->isGameOver())
    {
        // Polling the events called in the GLFWwindow:
        m_application->PollEvents();

        // Updating the application:
        m_application->Update();

        // Getting the deltaTime between frames:
        float deltaTime = (float) (m_application->getDeltaTime());

        // Exitting the application if the escape key is pressed:
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_application->setGameOver(true);

        // Reloading the shaders:
        if (glfwGetKey(m_window, GLFW_KEY_0) == GLFW_PRESS && m_canReload)
        {
            m_shaderManager->ReloadAllShaders();
            m_canReload = false;
        }

        // Toggle wiremesh mode:
        if (glfwGetKey(m_window, GLFW_KEY_9) == GLFW_PRESS && m_canReload)
        {
            m_application->ToggleWiremeshMode();
            m_canReload = false;
        }

        // Reloading the shaders:
        if (glfwGetKey(m_window, GLFW_KEY_8) == GLFW_PRESS && m_canReload)
        {
            m_objModel->getShader()->toggleEffect();
            m_canReload = false;
        }

        // Timer to prevent calling the reload function in the same frame:
        if (!m_canReload)
        {
            m_reloadTimer += deltaTime;
            if (m_reloadTimer > 0.5f)
            {
                m_reloadTimer -= m_reloadTimer;
                m_canReload = true;
            }
        }

        // Updating the camera class:
        m_camera->update(deltaTime);

        // Updating models:
        // m_earth->setRotation(-deltaTime * 15, glm::vec3(0, 0, 1));

        // Updating obj shader:
        m_objModel->getShader()->update(deltaTime);

        // Rendering everything:
        Render();
    }
}

void Game::Render()
{
    // Clearing the buffers:
    m_application->ClearBuffers();

    // Rendering the models:
    m_objModel->renderOBJ(m_camera);
    //m_earth->render(m_camera);


    m_sun->render(m_camera);
    m_sun->getShader()->use();
    m_sun->getShader()->setVector4("color", glm::vec4(1.0f, 0.7f, 0.3f, 1.0f));
    m_sun->getShader()->stop();

    m_earth->getShader()->use();
    m_earth->getShader()->setVector4("lightPos", glm::vec4(m_sun->getPosition(), 1.0f));
    m_earth->getShader()->setVector3("viewPos", m_camera->getPosition());
    m_earth->render(m_camera);

    // Swapping the buffers:
    m_application->SwapBuffers();
}
