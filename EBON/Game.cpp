#include "Game.h"
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
    
    // Init ImGui vars:
    m_movementSpeed = m_camera->getMovementSpeed();
    m_movementFastSpeed = m_camera->getMovementFastSpeed();
    m_sensitivity = m_camera->getSensitivity();

    // Initalising the models:
    InitModels();

    // Creating a pointer to the GLFWwindow:
    m_window = m_application->getWindow();
    m_modelTintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    // Initalising vars:
    m_canReload = true;
    m_reloadTimer = 0.0f;
}

Game::~Game() 
{
    // Destroying the models:
    for (int i = 0; i < 4; ++i)
    {
        delete m_modelList[i];
        m_modelList[i] = nullptr;
    }

    delete[] m_modelList;
    
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

        glm::vec3 position = glm::vec3(pos * 4, 7.0f, 0.0f);

        m_modelLights[i] = new ModelLight(new RawModel(Primitives::generateCube(), ShaderManager::E_DEFAULT),
                                       position, 1.0f, 0.09f, 0.0075f, 
                                       glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.15f));
        m_modelLights[i]->getModel()->setScale(glm::vec3(0.2f));
    }

    // Initialising the model list:
    m_modelList = new Model * [4];

    // Earth
    m_modelList[0] = new EarthModel(m_dirLight, m_modelLights);
    m_modelList[0]->addPosition(glm::vec3(0.0f, 3.0f, 0.0f));
    m_modelList[0]->addRotation(270.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    // Ivysaur
    m_modelList[1] = new IvysaurModel(m_dirLight, m_modelLights);

    // Sword and shield:
    if (!swordAndShield.load("..\\Models\\SwordAndShield\\meshSwordShield.obj"))
        std::cout << "ERROR_LOADING_SWORD&SHIELD_MODEL_" << std::endl;

    // Extracting shield from obj:
    m_modelList[2] = new ShieldModel(swordAndShield.m_meshChunks[0], m_dirLight, m_modelLights);
    m_modelList[2]->addRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelList[2]->addPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    m_modelList[2]->setScale(glm::vec3(0.5f));

    // Extracting sword from obj:
    m_modelList[3] = new SwordModel(swordAndShield.m_meshChunks[1], m_dirLight, m_modelLights);
    m_modelList[3]->addRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelList[3]->addPosition(glm::vec3(0.0f, 7.0f, 0.0f));
    m_modelList[3]->setScale(glm::vec3(0.5f));

}

void Game::RenderImGui()
{
    // ImGUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Info window:
    ImGui::Begin("Information");
    ImGui::Text("[ENTER] to unlock cursor.");
    ImGui::Text("[RSHIFT] to lock cursor.");
    ImGui::Text("[NUMPUD 1] to reload shaders.");
    ImGui::Text("[NUMPUD 2] to toggle wiremesh mode.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();   // Info window:

    // Camera adjustments:
    ImGui::Begin("Camera Options");
    ImGui::InputFloat("Speed", &m_movementSpeed, ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputFloat("Fast Speed", &m_movementFastSpeed, ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputFloat("Sensitivity", &m_sensitivity, ImGuiInputTextFlags_CharsDecimal);

    if (ImGui::Button("Confirm Changes"))
    {
        m_camera->setMovementSpeed(m_movementSpeed);
        m_camera->setMovementFastSpeed(m_movementFastSpeed);
        m_camera->setSensitivity(m_sensitivity);
    }
    ImGui::SameLine();
    if (ImGui::Button("Revert To Default"))
    {
        m_movementSpeed = m_camera->getDefaultMovementSpeed();
        m_movementFastSpeed = m_camera->getDefaultMovementFastSpeed();
        m_sensitivity = m_camera->getDefaultSensitivity();
        m_camera->setMovementSpeed(m_movementSpeed);
        m_camera->setMovementFastSpeed(m_movementFastSpeed);
        m_camera->setSensitivity(m_sensitivity);
    }
    ImGui::End();   // Camera adjustments:

    // Model adjustments window:
    ImGui::Begin("Model Adjustments");

    ImGui::Text("Model Shader Properties");
    ImGui::ColorEdit3("Tint", (float*)&m_modelTintColor);

    for (int i = 0; i < 4; ++i)
    {
        ShaderProgram* modelShader = m_modelList[i]->getShader();
        glm::vec3 lightColor = glm::vec3(m_modelTintColor.x, m_modelTintColor.y, m_modelTintColor.z);
        modelShader->bind();
        modelShader->setVector3("color", lightColor);
    }

    ImGui::End(); // Model adjustments window:

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        {
            m_application->setGameOver(true);
        }

        // Reloading the shaders:
        if (glfwGetKey(m_window, GLFW_KEY_KP_1) == GLFW_PRESS && m_canReload)
        {
            m_shaderManager->ReloadActiveShaders();
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
        m_modelList[0]->addRotation(0.006f, glm::vec3(0.0f, 0.0f, 1.0f));

        // Updating the camera class:
        m_camera->Update(deltaTime);

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
        m_modelLights[i]->Render(m_camera);
    }

    // Models:
    for (int i = 0; i < 4; ++i)
    {
        m_modelList[i]->Render(m_camera);
    }

    // Render ImGui:
    RenderImGui();

    // Swapping the buffers:
    m_application->SwapBuffers();
}

int Game::Wrap(int& index, int min, int max)
{
    if (index > max)
        index = min;
    else if (index < min)
        index = min;

    return index;
}
