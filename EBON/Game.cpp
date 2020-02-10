#include "Game.h"

Game::Game()
{
    Application::Create();
    m_app = Application::getInstance();
}

Game::~Game() 
{
    Application::Destroy();
}

void Game::Run()
{
    if (m_app)
    {
        // Setup game:
        m_app->setGameOver(false);

        // Update game:
        Update(m_app->getDeltaTime());
    }
}
  
void Game::Update(float deltaTime)
{
    // While the app hasn't closed:
    while (!m_app->hasWindowClosed())
    {
        // Updating the application:
        m_app->Update();

        // - Drawing test square with triangles:
        m_app->ClearBuffers();
    }
}
