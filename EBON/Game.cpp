#include "Game.h"
#include "Directives.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Camera.h"
#include "Primitives.h"
#include "RawModel.h"

Game::Game()
{
    // Creating the application:
    m_application = Application::Create("EBON", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Creating the shader manager:
    m_shaderManager = ShaderManager::Create();
}

Game::~Game() 
{
    // Destorying the shader manager:
    ShaderManager::Destroy();

    // Destroying the app, this should be done last:
    Application::Destroy();
}

void Game::Run()
{
    if (m_application)
    {
        // Setup game:
        m_application->setGameOver(false);

        // Update game:
        Update();
    }
}
  
void Game::Update()
{
    // Getting the window:
    auto window = glfwGetCurrentContext();

    // Creating a final color vector for the fragment shader:
    glm::vec4 color  = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    // Creating some test models with generated cubes:
    //RawModel* sphere_1 = new RawModel(Primitives::generateSphere(0.5f, 18, 9), ShaderManager::DEFAULT);

    int X = 10, Y = 10, Z = 10;

    RawModel* *** spheres = new RawModel* ** [X];
    for (int i = 0; i < X; i++) {
        spheres[i] = new RawModel* * [Y];

        for (int j = 0; j < Y; j++) {
            spheres[i][j] = new RawModel * [Z];

            for (int k = 0; k < Z; k++) {
                spheres[i][j][k] = new RawModel(Primitives::generateSphere(0.5f, 18.0f, 9.0f), ShaderManager::DEFAULT);
                spheres[i][j][k]->setPosition(glm::vec3(i * 2.0f, j * 2.0f, k * 2.0f));
            }
        }
    }

    // Set positions:
    //sphere_1->setPosition(glm::vec3(-1.0f, 4.0f, -5.0f));

    // Creating a test camera:
    Camera* camera = new Camera();

    // Enabling wiremesh mode:
    m_application->ToggleWiremeshMode();

    // Clearing the color:
    m_application->ClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_application->setGameOver(true);

        // Updating the camera class:
        camera->update(deltaTime);

        for (int x = 0; x < X; ++x)
        {
            for (int y = 0; y < Y; ++y)
            {
                for (int z = 0; z < Z; ++z)
                {
                    spheres[x][y][z]->render(camera);
                }
            }
        }

        // Rendering the spheres:
       // sphere_1->render(camera);

        // Swapping the buffers:
        m_application->SwapBuffers();
    }

    // Deleting the cameras:
    delete camera;


    for (int i = 0; i < X; i++) {
        delete[] spheres[i];

        for (int j = 0; j < Y; j++) {
            delete[] spheres[i][j];

            for (int k = 0; k < Z; k++) {
                delete[] spheres[i][j][k];
            }
        }
    }
    //delete[] spheres;
   // delete sphere_1;
}
