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
    delete m_earthModel;
    m_earthModel = nullptr;

    delete m_ivyModel;
    m_ivyModel = nullptr;

    delete m_shieldModel;
    m_shieldModel = nullptr;
    
    // Deleting lights:
    for (int i = 0; i < 2; ++i)
    {
        delete m_modelLights[i];
    }
    delete[] m_modelLights;

    delete m_dirLight;

    // Destroying the camera:
    delete m_camera;
    m_camera = nullptr;

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
        m_application->ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Enabling depth testing:
        glEnable(GL_DEPTH_TEST);

        // Update game:
        Update();
    }
}

void Game::InitModels()
{
    // Directional light properties
    m_dirLight = new DirectionalLight({ 0.0f, 1.0f, 0.0f }, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.15f));

    // Setting up the point lights:
    m_modelLights = new ModelLight * [2];
    for (int i = 0; i < 2; ++i)
    {
        // Position:
        int pos = -1;
        if (i == 0)
            pos = 1;
        glm::vec3 position = glm::vec3(pos * 4, 4.0f, 0.0f);

        m_modelLights[i] = new ModelLight(new RawModel(Primitives::generateCube(), ShaderManager::E_DEFAULT),
                                       position, 1.0f, 0.09f, 0.0075f, 
                                       glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.15f));
        m_modelLights[i]->getModel()->setScale(glm::vec3(0.2f));
    }

    // Earth
    m_earthModel = new EarthModel(m_dirLight, m_modelLights);
    m_earthModel->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
    m_earthModel->setRotation(270.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    // Ivysaur
    m_ivyModel = new IvysaurModel(m_dirLight, m_modelLights);

    // Shield
    aie::OBJMesh swordAndShield;
    if (!swordAndShield.load("..\\Models\\SwordAndSheild\\meshSwordShield.obj"))
        std::cout << "ERROR_LOADING_SWORD&SHIELD_MODEL_" << std::endl;

    m_shieldModel = new ShieldModel(swordAndShield.m_meshChunks[0], m_dirLight, m_modelLights);
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
        if (glfwGetKey(m_window, GLFW_KEY_KP_1) == GLFW_PRESS && m_canReload)
        {
            m_shaderManager->ReloadAllShaders();
            m_canReload = false;
        }

        // Toggle wiremesh mode:
        if (glfwGetKey(m_window, GLFW_KEY_KP_2) == GLFW_PRESS && m_canReload)
        {
            m_application->ToggleWiremeshMode();
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

        // Rotating earth:
        m_earthModel->setRotation(0.06f, glm::vec3(0.0f, 0.0f, 1.0f));

        // Updating the camera class:
        m_camera->update(deltaTime);

        // Rendering everything:
        Render();
    }
}

void Game::Render()
{
    // Clearing the buffers:
    m_application->ClearBuffers();

    // Light cubes:
    for (int i = 0; i < 2; ++i)
    {
        m_modelLights[i]->render(m_camera);
    }

    // Earth
    m_earthModel->render(m_camera);

    // Ivysaur
    m_ivyModel->render(m_camera);

    // Sheild
    m_shieldModel->render(m_camera);

    // Swapping the buffers:
    m_application->SwapBuffers();
}
