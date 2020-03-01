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
        m_application->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Enabling wiremesh mode:
        // m_application->ToggleWiremeshMode();

        glEnable(GL_DEPTH_TEST);

        // Update game:
        Update();
    }
}

void Game::InitModels()
{
    // Light properties
    m_light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
    m_light.diffuse = { 1, 1, 1 };
    m_light.specular = { 1, 1, 1 };
    m_ambientLight = { 0.15f, 0.15f, 0.15f };

    // Earth
    Image* earthDiffuse = new Image("..\\Textures\\Earth\\earth_diffuse.jpg", GL_RGB);
    Image* earthSpecular = new Image("..\\Textures\\Earth\\earth_specular.jpg", GL_RGB);
    Image* earthNormal = new Image("..\\Textures\\Earth\\earth_normal.jpg", GL_RGB);
    m_earthModel = new TexturedModel(Primitives::generateSphere(1.0f, 36.0f, 18.0f), ShaderManager::DIR_LIT_NM, earthDiffuse, earthSpecular, earthNormal);
    m_earthModel->setPosition(glm::vec3(3.0f));

    // Ivysaur
    Image* ivyDiffuse = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Diffuse.png", GL_RGBA);
    Image* ivySpecular = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Specular.png", GL_RGBA);
    Image* ivyNormal = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Normal.png", GL_RGBA);
    Image* ivyAmbient = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Ambient_Occlusion.png", GL_RGBA);
    Image* ivyGloss = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Ambient_Occlusion.png", GL_RGBA);
    m_ivyModel = new TexturedModel("..\\Models\\Ivysaur\\Pokemon.obj", ShaderManager::DIR_LIT_NM, ivyDiffuse, ivySpecular, ivyNormal, ivyAmbient, ivyGloss);
    m_ivyModel->setPosition(glm::vec3(2.0f, 0.0f, 0.7f));
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

    float time = m_application->getTime();
    m_light.direction = glm::vec3(sin(time * 2), -1.0f, cos(time * 2));

    // Earth
    m_earthModel->getShader()->bind();
    m_earthModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_earthModel->getTransform())));
    m_earthModel->getShader()->setVector3("Ia", m_ambientLight);
    m_earthModel->getShader()->setVector3("Id", m_light.diffuse);
    m_earthModel->getShader()->setVector3("Is", m_light.specular);
    m_earthModel->getShader()->setVector3("light_direction", m_light.direction);
    m_earthModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_earthModel->render(m_camera);
    m_earthModel->getShader()->unbind();

    // Ivysaur
    m_ivyModel->getShader()->bind();
    m_ivyModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_ivyModel->getTransform())));
    m_ivyModel->getShader()->setVector3("Ia", m_ambientLight);
    m_ivyModel->getShader()->setVector3("Id", m_light.diffuse);
    m_ivyModel->getShader()->setVector3("Is", m_light.specular);
    m_ivyModel->getShader()->setVector3("light_direction", -m_light.direction);
    m_ivyModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_ivyModel->render(m_camera);
    m_ivyModel->getShader()->unbind();

    // Swapping the buffers:
    m_application->SwapBuffers();
}
