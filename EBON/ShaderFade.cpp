#include "ShaderFade.h"
#include "GameManager.h"

ShaderFade::ShaderFade() : ShaderProgram("..\\Shaders\\Effects\\fade_vertex.glsl", "..\\Shaders\\Effects\\fade_fragment.glsl")
{
    m_defaultSpeed = 3.5f;
    m_defaultMax = 10.0f;
    m_defaultMin = -1.0f;
    resetEffect();
}

ShaderFade::~ShaderFade() {}

void ShaderFade::update(float deltaTime)
{
    Application* application = GameManager::getInstance()->getApplication();
    float time = application->getTime();

    bind();
    setBool("isRunning", m_bEffectStatus);
    setBool("hasFaded", m_hasFaded);
    setFloat("timer", m_timer);
    setFloat("appTime", time);

    if (m_bEffectStatus)
    {
        if (m_hasFaded)
        {
            if (m_timer > m_timerMin)
            {
                m_timer -= m_timerSpeed * deltaTime;
            }
            else
            {
                stopEffect();
                m_hasFaded = false;
            }
        }
        else
        {
            if (m_timer < m_timerMax)
            {
                m_timer += m_timerSpeed * deltaTime;
            }
            else
            {
                stopEffect();
                m_hasFaded = true;
            }
        }
    }

    unbind();
}

void ShaderFade::toggleEffect(float args0, float args1, float args2)
{
    if (args0 > 0.0f)
        m_defaultSpeed = args0;

    if (args1 > 0.0f)
        m_defaultMax = args1;

    if (args2 > 0.0f)
        m_defaultMin = args2;

    m_bEffectStatus = !m_bEffectStatus;
}

void ShaderFade::startEffect()
{
    m_bEffectStatus = true;
}

void ShaderFade::stopEffect()
{
    m_bEffectStatus = false;
}

void ShaderFade::resetEffect()
{
    m_timerSpeed = m_defaultSpeed;
    m_timerMax = m_defaultMax;
    m_timerMin = m_defaultMin;
    m_timer = m_timerMax;
    m_hasFaded = true;
}