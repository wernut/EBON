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
    delete m_texturedModel;
    m_texturedModel = nullptr;

    delete m_objModel;
    m_objModel = nullptr;

    delete m_lampModel;
    m_lampModel = nullptr;

    delete m_sun;
    m_sun = nullptr;

    delete m_lightCube;
    m_lightCube = nullptr;
    
    delete m_grassPlane;
    m_grassPlane = nullptr;

    // Destorying the textures:
    delete m_modelTexture;
    m_modelTexture = nullptr;

    delete m_objTexture;
    m_objTexture = nullptr;   

    delete m_lampTexture;
    m_lampTexture = nullptr;

    delete m_grassTexture;
    m_grassTexture = nullptr;

    // Destroying the camera:
    delete m_camera;
    m_camera = nullptr;

    // Destorying the game manager:
    GameManager::Destroy();
}

void Game::InitModels()
{
    // Geometry, light and texturing test models:
    m_modelTexture = new Image("..\\Textures\\earth_diffuse.jpg", GL_RGB);
    m_texturedModel = new TexturedModel(m_modelTexture, Primitives::generateSphere(1.0f, 36.0f, 18.0f), ShaderManager::TEXTURED);
    m_texturedModel->setRotation(-60, glm::vec3(1, 0, 0));
    m_texturedModel->setRotation(-45, glm::vec3(1, 0, 1));
    m_sun = new RawModel(Primitives::generateSphere(3.0f, 36.0f, 18.0f), ShaderManager::LIGHT);
    m_sun->setPosition(glm::vec3(15.0f, 0.0f, 0.0f));
    // ---------------------------------------------------

    // OBJ Testing:
    m_objTexture = new Image("..\\Textures\\Ivysaur\\Final_Pokemon_Diffuse.jpg", GL_RGB);
    m_objModel = new TexturedModel(m_objTexture, "..\\Models\\Ivysaur\\Pokemon.obj", ShaderManager::DEFAULT);
    m_objModel->setPosition(glm::vec3(2.0f, 0.0f, 0.7f));

    m_lampTexture = new Image("..\\Textures\\grey-concrete-texture.jpg", GL_RGB);
    m_lampModel = new TexturedModel(m_lampTexture, "..\\Models\\lamp_post.obj", ShaderManager::DEFAULT);
    m_lampModel->setScale(glm::vec3(0.001f));
    m_lampModel->setPosition(glm::vec3(2.0f, 0.0f, 2.0f));

    m_lightCube = new RawModel(Primitives::generateCube(), ShaderManager::LIGHT);
    m_lightCube->setPosition(glm::vec3(0.0f, 3.30f, 0.0f));
    m_lightCube->setScale(glm::vec3(0.1f));

    m_grassTexture = new Image("..\\Textures\\grass.jpg", GL_RGB);
    m_grassPlane = new TexturedModel(m_grassTexture, Primitives::generatePlane(25.0f), ShaderManager::DEFAULT);
    m_grassPlane->setPosition(glm::vec3(-(25.0f / 2.0f), 0.0f, -(25.0f / 2.0f)));


    m_light.diffuse  = { 1, 1, 1 };
    m_light.specular = { 1, 1, 0 };
    m_ambientLight   = { 0.25f, 0.25f, 0.25f };
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

        //  Toggling the effect on the OBJ shader:
        //if (glfwGetKey(m_window, GLFW_KEY_KP_3) == GLFW_PRESS && m_canReload)
        //{
        //    m_objModel->getShader()->toggleEffect();
        //    m_canReload = false;
        //}

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
        // m_texturedModel->setRotation(-deltaTime * 15, glm::vec3(0, 0, 1));

        // Updating obj shader:
        // m_warriorModel->getShader()->update(deltaTime);

        // Rendering everything:
        Render();
    }
}

void Game::Render()
{
    // Clearing the buffers:
    m_application->ClearBuffers();

    //glm::vec4 lightPos = glm::vec4(m_lightCube->getPosition().x, -m_lightCube->getPosition().y, m_lightCube->getPosition().z, 1.0f);

    //float time = m_application->getTime();
    //lightPos.x += cos(time) * 4;
    //lightPos.z += sin(time) * 4;

    m_light.direction = glm::vec3(0.0f, -1.0f, 0);

    m_lightCube->render(m_camera);

    // OBJ models
    m_objModel->getShader()->use();
    m_objModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_objModel->getTransform())));
    m_objModel->getShader()->setVector3("Ia", m_ambientLight);
    m_objModel->getShader()->setVector3("Id", m_light.diffuse);
    m_objModel->getShader()->setVector3("Is", m_light.specular);
    m_objModel->getShader()->setVector3("light_direction", m_light.direction);
    m_objModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_objModel->render(m_camera);
    m_objModel->getShader()->stop();

    m_lampModel->getShader()->use();
    m_lampModel->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_lampModel->getTransform())));
    m_lampModel->getShader()->setVector3("Ia", m_ambientLight);
    m_lampModel->getShader()->setVector3("Id", m_light.diffuse);
    m_lampModel->getShader()->setVector3("Is", m_light.specular);
    m_lampModel->getShader()->setVector3("light_direction", m_light.direction);
    m_lampModel->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_lampModel->render(m_camera);
    m_lampModel->getShader()->stop();

    m_grassPlane->getShader()->use();
    m_grassPlane->getShader()->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_grassPlane->getTransform())));
    m_grassPlane->getShader()->setVector3("Ia", m_ambientLight);
    m_grassPlane->getShader()->setVector3("Id", m_light.diffuse);
    m_grassPlane->getShader()->setVector3("Is", m_light.specular);    
    m_grassPlane->getShader()->setVector3("light_direction", m_light.direction);
    m_grassPlane->getShader()->setVector3("camera_position", m_camera->getPosition());
    m_grassPlane->render(m_camera);
    m_grassPlane->getShader()->stop();

    // Sun
    //m_sun->render(m_camera);
    //m_sun->getShader()->use();
    //m_sun->getShader()->setVector4("color", glm::vec4(1.0f, 0.7f, 0.3f, 1.0f));
    //m_sun->getShader()->stop();

    // Earth
    //m_texturedModel->getShader()->use();
    //m_texturedModel->getShader()->setVector4("lightPos", glm::vec4(m_sun->getPosition(), 1.0f));
    //m_texturedModel->getShader()->setVector4("lightColor", glm::vec4(1.0f));
    //m_texturedModel->getShader()->setVector3("viewPos", m_camera->getPosition());
    //m_texturedModel->render(m_camera);
    //m_texturedModel->getShader()->stop();

    // Swapping the buffers:
    m_application->SwapBuffers();
}
