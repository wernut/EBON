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

    delete m_lampModel;
    m_lampModel = nullptr;
    
    delete m_grassModel;
    m_grassModel = nullptr;

    // Destroying the camera:
    delete m_camera;
    m_camera = nullptr;

    // Destorying the game manager:
    GameManager::Destroy();
}

void Game::InitModels()
{
    // Light properties
    m_light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
    m_light.diffuse = { 1, 1, 1 };
    m_light.specular = { 1, 1, 1 };
    m_ambientLight = { 0.25f, 0.25f, 0.25f };

    // Earth
    m_earthDiffuse   = new Image("..\\Textures\\Earth\\earth_diffuse.jpg", GL_RGB);
    m_earthSpecular  = new Image("..\\Textures\\Earth\\earth_specular.jpg", GL_RGB);
    m_earthNormal    = new Image("..\\Textures\\Earth\\earth_normal.jpg", GL_RGB);
    m_earthModel = new TexturedModel(Primitives::generateSphere(1.0f, 36.0f, 18.0f), ShaderManager::DIR_LIT_NM, m_earthDiffuse, m_earthSpecular, m_earthNormal);
    m_earthModel->setPosition(glm::vec3(3.0f));

    // Ivysaur
    m_ivyDiffuse = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Diffuse.jpg", GL_RGB);
    m_ivySpecular = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Specular.jpg", GL_RGB);
    m_ivyNormal = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Normal.jpg", GL_RGB);
    m_ivyModel = new TexturedModel("..\\Models\\Ivysaur\\Pokemon.obj", ShaderManager::DIR_LIT_NM, m_ivyDiffuse, m_ivySpecular, m_ivyNormal);
    m_ivyModel->setPosition(glm::vec3(2.0f, 0.0f, 0.7f));

    // Lamp
    m_lampTexture = new Image("..\\Textures\\grey-concrete-texture.jpg", GL_RGB);
    m_lampModel = new TexturedModel("..\\Models\\lamp_post.obj", ShaderManager::DIR_LIT, m_lampTexture);
    m_lampModel->setScale(glm::vec3(0.001f));
    m_lampModel->setPosition(glm::vec3(2.0f, 0.0f, 2.0f));

    // Grass
    m_grassTexture = new Image("..\\Textures\\grass.jpg", GL_RGB);
    m_grassModel = new TexturedModel(Primitives::generatePlane(25.0f), ShaderManager::DIR_LIT, m_grassTexture);
    m_grassModel->setPosition(glm::vec3(-(25.0f / 2.0f), 0.0f, -(25.0f / 2.0f)));
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
    //m_light.direction = glm::vec3(sin(time * 2), -1.0f, cos(time * 2));

    // Ivysaur
    m_ivyModel->getShader()->use();
    m_ivyModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_ivyModel->getTransform())));
    m_ivyModel->getShader()->setVector3("Ia", m_ambientLight);
    m_ivyModel->getShader()->setVector3("Id", m_light.diffuse);
    m_ivyModel->getShader()->setVector3("Is", m_light.specular);
    m_ivyModel->getShader()->setVector3("light_direction", m_light.direction);
    m_ivyModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_ivyModel->render(m_camera);
    m_ivyModel->getShader()->stop();

    // Lamp
    m_lampModel->getShader()->use();
    m_lampModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_lampModel->getTransform())));
    m_lampModel->getShader()->setVector3("Ia", m_ambientLight);
    m_lampModel->getShader()->setVector3("Id", m_light.diffuse);
    m_lampModel->getShader()->setVector3("Is", m_light.specular);
    m_lampModel->getShader()->setVector3("light_direction", m_light.direction);
    m_lampModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_lampModel->render(m_camera);
    m_lampModel->getShader()->stop();

    // Grass
    m_grassModel->getShader()->use();
    m_grassModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_grassModel->getTransform())));
    m_grassModel->getShader()->setVector3("Ia", m_ambientLight);
    m_grassModel->getShader()->setVector3("Id", m_light.diffuse);
    m_grassModel->getShader()->setVector3("Is", m_light.specular);    
    m_grassModel->getShader()->setVector3("light_direction", m_light.direction);
    m_grassModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_grassModel->render(m_camera);
    m_grassModel->getShader()->stop();

    // Earth
    m_earthModel->getShader()->use();
    m_earthModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_earthModel->getTransform())));
    m_earthModel->getShader()->setVector3("Ia", m_ambientLight);
    m_earthModel->getShader()->setVector3("Id", m_light.diffuse);
    m_earthModel->getShader()->setVector3("Is", m_light.specular);
    m_earthModel->getShader()->setVector3("light_direction", m_light.direction);
    m_earthModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_earthModel->render(m_camera);
    m_earthModel->getShader()->stop();

    // Swapping the buffers:
    m_application->SwapBuffers();
}
