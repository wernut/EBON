/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ShaderFade.h & ShaderFade.cpp
 * Purpose:     Serves as an effect shader, made to help understand shaders a
 *				a bit better.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "ShaderFade.h"
#include "GameManager.h"

// Loading the shader from the effects folder:
ShaderFade::ShaderFade() : ShaderProgram("..\\Shaders\\Effects\\fade_vertex.glsl", "..\\Shaders\\Effects\\fade_fragment.glsl")
{
    // Setting the default values:
    m_defaultSpeed = 3.5f;
    m_defaultMax = 10.0f;
    m_defaultMin = -1.0f;

    // Setting all timer values to default:
    ResetEffect();
}

ShaderFade::~ShaderFade() {}

void ShaderFade::Update(float deltaTime)
{
    // Getting the application instance to get the time value:
    Application* application = GameManager::getInstance()->getApplication();
    float time = (float) application->getTime();

    // Binding the shader and setting the uniform values inside:
    bind();
    setBool("isRunning", m_effectStatus);
    setBool("hasFaded", m_hasFaded);
    setFloat("timer", m_timer);
    setFloat("appTime", time);

    if (m_effectStatus)
    {
        // If the object isn't showing. (Timer > the height of the object).
        if (m_hasFaded)
        {
            // If the timer is greater than the min value:
            if (m_timer > m_timerMin)
            {
                // Negating the timer value by the timer speed:
                m_timer -= m_timerSpeed * deltaTime;
            }
            else
            {
                // If the effect has successfully faded:
                StopEffect();
                m_hasFaded = false;
            }
        }
        else
        {
            // Doing the opposite of above to get a fade in effect:
            if (m_timer < m_timerMax)
            {
                m_timer += m_timerSpeed * deltaTime;
            }
            else
            {
                StopEffect();
                m_hasFaded = true;
            }
        }
    }
}

void ShaderFade::ToggleEffect(float speed, float maxTime, float minTime)
{
    // Sets the speed if parameter > 0:
    if (speed > 0.0f)
        m_defaultSpeed = speed;

    // Sets the min time if parameter > 0:
    if (maxTime > 0.0f)
        m_defaultMax = maxTime;

    // Sets the max time if parameter > 0:
    if (minTime > 0.0f)
        m_defaultMin = minTime;

    // Toggles the effect status:
    m_effectStatus = !m_effectStatus;
}

void ShaderFade::StartEffect()
{
    // Setting the effect status to true:
    m_effectStatus = true;
}

void ShaderFade::StopEffect()
{
    // Setting the effect status to false:
    m_effectStatus = false;
}

void ShaderFade::ResetEffect()
{
    // Setting all the timer values back to default:
    m_timerSpeed = m_defaultSpeed;
    m_timerMax = m_defaultMax;
    m_timerMin = m_defaultMin;
    m_timer = m_timerMax;
    m_hasFaded = true;
}