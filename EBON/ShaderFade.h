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
#pragma once
#include "ShaderProgram.h"

class ShaderFade : public ShaderProgram
{
private:
	// Timer values & properties:
	float m_timerSpeed, m_defaultSpeed;
	float m_timerMax, m_defaultMax, m_timerMin, m_defaultMin;
	float m_timer;
	bool  m_hasFaded;
public:
	/* Default constructor: */
	ShaderFade();

	/* Destructor: */
	~ShaderFade();

	// Functions that override the base class virtuals:
	void Update(float deltaTime);
	void ToggleEffect(float speed = 0.0f, float maxTime = 0.0f, float minTime = 0.0f);
	void StartEffect();
	void StopEffect();
	void ResetEffect();
};

