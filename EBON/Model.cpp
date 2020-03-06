#include "Model.h"
#include "Game.h"

Model::Model() : TexturedModel() {}

Model::Model(Mesh* mesh, DirectionalLight* dirLight, ModelLight** modelLights) : TexturedModel(mesh, ShaderManager::E_MODEL)
{
    m_dirLight = dirLight;
    m_modelLights = modelLights;
}

Model::Model(const char* objLocation, DirectionalLight* dirLight, ModelLight** modelLights) : TexturedModel(objLocation, ShaderManager::E_MODEL)
{
    m_dirLight = dirLight;
    m_modelLights = modelLights;
}

Model::~Model(){}

void Model::update(float deltaTime){}

void Model::render(Camera* camera)
{
    m_shader->bind();
    m_shader->setMatrix3("normal_matrix", glm::inverseTranspose(glm::mat3(m_transform)));
    m_shader->setVector3("camera_position", camera->getPosition());
    m_shader->setVector3("dirLight.direction", m_dirLight->getDirection());
    m_shader->setVector3("dirLight.ambient", m_dirLight->getAmbient());
    m_shader->setVector3("dirLight.diffuse", m_dirLight->getDiffuse());
    m_shader->setVector3("dirLight.specular", m_dirLight->getSpecular());
    for (int i = 0; i < 2; ++i)
    {
        const std::string index = std::to_string(i);
        m_shader->setVector3("pointLights[" + index + "].position", m_modelLights[i]->getPosition());
        m_shader->setVector3("pointLights[" + index + "].ambient", m_modelLights[i]->getAmbient());
        m_shader->setVector3("pointLights[" + index + "].diffuse", m_modelLights[i]->getDiffuse());
        m_shader->setVector3("pointLights[" + index + "].specular", m_modelLights[i]->getSpecular());
        m_shader->setFloat("pointLights[" + index + "].constant", m_modelLights[i]->getConstant());
        m_shader->setFloat("pointLights[" + index + "].linear", m_modelLights[i]->getLinear());
        m_shader->setFloat("pointLights[" + index + "].quadratic", m_modelLights[i]->getQuadratic());
    }
    TexturedModel::render(camera);
}
