/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       GameObject.h & GameObject.cpp
 * Purpose:     To simulate an object in world space.
 *
 *				Started working on not long ago, still in early development!
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "GameManager.h"
#include "Model.h"

class GameObject
{
protected:
	Model* m_model; // Local transform = model->m_transform
	glm::mat4 m_globalTransform;
	GameObject* m_parent;
	std::vector<GameObject*> m_childList;

	float m_rotationX, m_rotationY, m_rotationZ;
	glm::vec3 m_scale;

private:
	void addChild(GameObject* child);
	void removeChild(GameObject* child);

public:
	GameObject(Model* model);
	virtual ~GameObject();

	virtual void update(float deltaTime);
	virtual void render(Camera* camera);
	void UpdateGlobalTransform();

	GameObject* getParent();
	void setParent(GameObject* parent);

	glm::mat4 getLocalTransform();
	glm::mat4 getGlobalTransform();

	// sets locals:
	void setPosition(glm::vec3 position);
	void setRotation(float angle, glm::vec3 axis);
	void setScale(glm::vec3 scale);

	// get globals:
	glm::vec3 getPosition();
	float getRotation(glm::vec3 axis);
	glm::vec3 getScale();

	// get locals:
	glm::vec3 getLocalPosition();
	float getLocalRotation(glm::vec3 axis);
	glm::vec3 getLocalScale();


	void printTransfom(glm::mat4 value);

};

