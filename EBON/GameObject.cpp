/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       GameObject.h & GameObject.cpp
 * Purpose:     To simulate an object in world space.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "GameObject.h"

GameObject::GameObject(Model* model)
{
	m_model = model;
	m_parent = nullptr;
	m_globalTransform = glm::mat4(1.0f);
	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;
	m_scale = glm::vec3(0.0f);
}

GameObject::~GameObject()
{
	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}

	for (GameObject* child : m_childList)
	{
		if (child)
		{
			delete child;
			child = nullptr;
		}
	}
}

void GameObject::update(float deltaTime)
{
	for (GameObject* child : m_childList)
	{
		child->update(deltaTime);
	}
}

void GameObject::render(Camera* camera)
{
	for (GameObject* child : m_childList)
	{
		child->render(camera);
	}
}

void GameObject::UpdateGlobalTransform()
{
	if (m_parent)
		m_globalTransform = m_parent->m_globalTransform * m_model->m_transform;
	else
		m_globalTransform = m_model->getTransform();
}

GameObject* GameObject::getParent()
{
	return m_parent;
}

void GameObject::setParent(GameObject* parent)
{
	if (m_parent)
		m_parent->removeChild(this);

	m_parent = parent;

	if (parent)
		m_parent->addChild(this);
}

glm::mat4 GameObject::getLocalTransform()
{
	return m_model->m_transform;
}

glm::mat4 GameObject::getGlobalTransform()
{
	return m_globalTransform;
}

// sets locals:
void GameObject::setPosition(glm::vec3 position)
{
	std::cout << " + before translation: " << std::endl;
	printTransfom(m_model->m_transform);

	m_model->m_transform = glm::translate(m_model->m_transform, position);

	std::cout << " + after translation: " << std::endl;
	printTransfom(m_model->m_transform);
}

// Try to only set one axis at a time, or else the get values will be messed up.
// TODO: Extract the rotation from the transformation matrix correctly.
void GameObject::setRotation(float angle, glm::vec3 axis)
{
	// Store rotation:
	if (axis.x > 0)
		m_rotationX = angle;
	else if (axis.y > 0)
		m_rotationY = angle;
	else if (axis.z > 0)
		m_rotationZ = angle;

	// Rotate transform:
	m_model->m_transform = glm::rotate(m_model->m_transform, glm::radians(angle), axis);
}

// TODO: Fix scaling! Avoid this function as much as possible for the time being.
void GameObject::setScale(glm::vec3 scale)
{
	if (m_scale.x > 0)
		m_scale.x /= scale.x;
	if (m_scale.y > 0)
		m_scale.y /= scale.y;
	if (m_scale.z > 0)
		m_scale.z /= scale.z;

	if (m_scale.x == 0 && m_scale.y == 0 && m_scale.z == 0)
		m_scale = scale;

	m_model->m_transform = glm::scale(m_model->m_transform, scale);
}

// get globals:
glm::vec3 GameObject::getPosition()
{
	return glm::vec3(m_globalTransform[3]);
}

// Returns local rotation!
float GameObject::getRotation(glm::vec3 axis)
{
	if (axis.x > 0)
		return m_rotationX;
	else if (axis.y > 0)
		return m_rotationY;
	else if (axis.z > 0)
		return m_rotationZ;
}

// Returns local scale!!
glm::vec3 GameObject::getScale()
{
	return m_scale;
}

// get locals:
glm::vec3 GameObject::getLocalPosition()
{
	return glm::vec3(m_model->m_transform[3]);
}

float GameObject::getLocalRotation(glm::vec3 axis)
{
	if (axis.x > 0)
		return m_rotationX;
	else if (axis.y > 0)
		return m_rotationY;
	else if (axis.z > 0)
		return m_rotationZ;
}

glm::vec3 GameObject::getLocalScale()
{
	return m_scale;
}


void GameObject::addChild(GameObject* child)
{
	m_childList.push_back(child);
}

void GameObject::removeChild(GameObject* child)
{
	auto iter = std::find(m_childList.begin(), m_childList.end(), child);
	if (iter != m_childList.end())
	{
		m_childList.erase(iter);
	}
}

void GameObject::printTransfom(glm::mat4 value)
{
	float* data = glm::value_ptr(value);

	for (int i = 0; i < 16; ++i) 
	{
		if (i != 0 && (i % 4) == 0) printf("\n");
		printf("%.2f ", data[i]);
	}

	printf("\n"); printf("\n"); printf("\n");
}
