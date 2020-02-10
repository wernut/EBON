#include "Game.h"
#include "Directives.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Primitives.h"

Game::Game()
{
    // Creating the application:
    m_app = Application::Create("EBON", SCREEN_WIDTH, SCREEN_HEIGHT);
}

Game::~Game() 
{
    // Destroying the app, this should be done last:
    Application::Destroy();
}

void Game::Run()
{
    if (m_app)
    {
        // Setup game:
        m_app->setGameOver(false);

        // Update game:
        Update();
    }
}
  
void Game::Update()
{
    // Getting the window:
    auto window = glfwGetCurrentContext();

    // Creating a final color vector for the fragment shader:
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    // Creating the sphere mesh for testing:
    Mesh* sphereMesh = Primitives::generateSphereMesh(1.0f, 36.0f, 18.0f);
    glm::mat4 sphereTransform = glm::mat4(1.0f);

    // Creating a shader for testing:
    Shader shader("..\\Shaders\\simple_vertex.glsl", "..\\Shaders\\simple_fragment.glsl");

    // Creating a test camera:
    Camera camera;

    // Enabling wiremesh mode:
    m_app->ToggleWiremeshMode();

    // Clearing the color:
    m_app->ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Main game loop:
    while (!m_app->hasWindowClosed() && !m_app->isGameOver())
    {
        // Clearing the buffers:
        m_app->ClearBuffers();

        // Polling the events called in the GLFWwindow:
        m_app->PollEvents();

        // Updating the application:
        m_app->Update();

        // Getting the deltaTime between frames:
        float deltaTime = m_app->getDeltaTime();

        // Do stuff here! -------------------------------------
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_app->setGameOver(true);

        camera.update(deltaTime);

        shader.use();
        shader.setMatrix4("projection_view_matrix", camera.getProjectionView());
        shader.setMatrix4("model_matrix", sphereTransform);
        shader.setVector4("color", color);

        sphereMesh->render();

        // ----------------------------------------------------
        // Swapping the buffers:
        m_app->SwapBuffers();
    }

    delete sphereMesh;
}
