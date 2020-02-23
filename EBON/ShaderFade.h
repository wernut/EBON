#pragma once
#include "ShaderProgram.h"

class ShaderFade : public ShaderProgram
{
private:
	float m_timerSpeed, m_defaultSpeed;
	float m_timerMax, m_defaultMax, m_timerMin, m_defaultMin;
	float m_timer;
	bool  m_hasFaded;
public:
	ShaderFade();
	~ShaderFade();

	virtual void update(float deltaTime);
	virtual void toggleEffect(float args0 = 0.0f, float args1 = 0.0f, float args2 = 0.0f);
	virtual void startEffect();
	virtual void stopEffect();
	virtual void resetEffect();
};

