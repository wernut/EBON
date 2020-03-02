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

    for (int i = 0; i < 2; ++i)
    {
        delete m_modelLights[i].model;
        m_modelLights[i].model = nullptr;
    }

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

        // Enabling wiremesh mode:
        // m_application->ToggleWiremeshMode();

        glEnable(GL_DEPTH_TEST);

        // Update game:
        Update();
    }
}

void Game::InitModels()
{
    // Directional light properties
    m_dirLight.direction = glm::vec3(0.0f, 1.0f, 0.0f);
    m_dirLight.diffuse = { 1, 1, 1 };
    m_dirLight.specular = { 1, 1, 1 };
    m_dirLight.ambient = { 0.15f, 0.15f, 0.15f };

    for (int i = 0; i < 2; ++i)
    {
        // Light position:
        int pos = -1;
        if (i == 0)
            pos = 1;
        glm::vec3 position = glm::vec3(pos * 4, 4.0f, 0.0f);

        // Model:
        m_modelLights[i].model = new RawModel(Primitives::generateCube(), ShaderManager::E_DEFAULT);
        m_modelLights[i].model->setPosition(position);
        m_modelLights[i].model->setScale(glm::vec3(0.2f));

        // Light props:
        m_modelLights[i].light.position = position;
        m_modelLights[i].light.constant = 1.0f;
        m_modelLights[i].light.linear = 0.09f;
        m_modelLights[i].light.quadratic = 0.0075f;
        m_modelLights[i].light.diffuse =  { 1.0f, 1.0f, 1.0f };
        m_modelLights[i].light.specular = { 1.0f, 1.0f, 1.0f };
        m_modelLights[i].light.ambient =  { 0.15f, 0.15, 0.15f };
    }

    // Earth
    Image* earthDiffuse = new Image("..\\Textures\\Earth\\earth_diffuse.jpg", GL_RGB);
    Image* earthSpecular = new Image("..\\Textures\\Earth\\earth_specular.jpg", GL_RGB);
    Image* earthNormal = new Image("..\\Textures\\Earth\\earth_normal.jpg", GL_RGB);
    m_earthModel = new TexturedModel(Primitives::generateSphere(1.0f, 36.0f, 18.0f), ShaderManager::E_MODEL, 
                                    earthDiffuse, earthSpecular, earthNormal);
    m_earthModel->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
    m_earthModel->setRotation(270.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    // Ivysaur
    Image* ivyDiffuse = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Diffuse.png", GL_RGBA);
    Image* ivySpecular = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Specular.png", GL_RGBA);
    Image* ivyNormal = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Normal.png", GL_RGBA);
    Image* ivyAmbient = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Ambient_Occlusion.png", GL_RGBA);
    Image* ivyGloss = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Ambient_Occlusion.png", GL_RGBA);
    m_ivyModel = new TexturedModel("..\\Models\\Ivysaur\\Pokemon.obj", ShaderManager::E_MODEL, 
                                    ivyDiffuse, ivySpecular, ivyNormal, ivyAmbient, ivyGloss);
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
        m_earthModel->setRotation(0.003f, glm::vec3(0.0f, 0.0f, 1.0f));

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
        m_modelLights[i].model->render(m_camera);
    }

    // Earth
    m_earthModel->getShader()->bind();
    m_earthModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_earthModel->getTransform())));
    m_earthModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_earthModel->getShader()->setVector3("dirLight.direction", m_dirLight.direction);
    m_earthModel->getShader()->setVector3("dirLight.ambient", m_dirLight.ambient);
    m_earthModel->getShader()->setVector3("dirLight.diffuse", m_dirLight.diffuse);
    m_earthModel->getShader()->setVector3("dirLight.specular", m_dirLight.specular);
    for (int i = 0; i < 2; ++i)
    {
        const std::string index = std::to_string(i);
        m_earthModel->getShader()->setVector3("pointLights[" + index + "].position", m_modelLights[i].light.position);
        m_earthModel->getShader()->setVector3("pointLights[" + index + "].ambient",  m_modelLights[i].light.ambient);
        m_earthModel->getShader()->setVector3("pointLights[" + index + "].diffuse",  m_modelLights[i].light.diffuse);
        m_earthModel->getShader()->setVector3("pointLights[" + index + "].specular", m_modelLights[i].light.specular);
        m_earthModel->getShader()->setFloat  ("pointLights[" + index + "].constant", m_modelLights[i].light.constant);
        m_earthModel->getShader()->setFloat  ("pointLights[" + index + "].linear",   m_modelLights[i].light.linear);
        m_earthModel->getShader()->setFloat  ("pointLights[" + index + "].quadratic",m_modelLights[i].light.quadratic);
    }
    m_earthModel->render(m_camera);


    // Ivysaur
    m_ivyModel->getShader()->bind();
    m_ivyModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_ivyModel->getTransform())));
    m_ivyModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_ivyModel->getShader()->setVector3("dirLight.direction", m_dirLight.direction);
    m_ivyModel->getShader()->setVector3("dirLight.ambient", m_dirLight.ambient);
    m_ivyModel->getShader()->setVector3("dirLight.diffuse", m_dirLight.diffuse);
    m_ivyModel->getShader()->setVector3("dirLight.specular", m_dirLight.specular);
    for (int i = 0; i < 2; ++i)
    {
        const std::string index = std::to_string(i);
        m_ivyModel->getShader()->setVector3("pointLights[" + index + "].position",  m_modelLights[i].light.position);
        m_ivyModel->getShader()->setVector3("pointLights[" + index + "].ambient",   m_modelLights[i].light.ambient);
        m_ivyModel->getShader()->setVector3("pointLights[" + index + "].diffuse",   m_modelLights[i].light.diffuse);
        m_ivyModel->getShader()->setVector3("pointLights[" + index + "].specular",  m_modelLights[i].light.specular);
        m_ivyModel->getShader()->setFloat  ("pointLights[" + index + "].constant",  m_modelLights[i].light.constant);
        m_ivyModel->getShader()->setFloat  ("pointLights[" + index + "].linear",    m_modelLights[i].light.linear);
        m_ivyModel->getShader()->setFloat  ("pointLights[" + index + "].quadratic", m_modelLights[i].light.quadratic);
    }
    m_ivyModel->render(m_camera);

    // Swapping the buffers:
    m_application->SwapBuffers();
}
