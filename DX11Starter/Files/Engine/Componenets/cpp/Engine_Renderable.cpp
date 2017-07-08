#include <Engine\Componenets\Renderable.h>
using namespace  KEngine::KComponent;
#include <iostream>
Renderable::Renderable() {
	meshId = KEnum::MESH_SPHERE;
	m_scale = Vector3(1, 1, 1);
}
Matrix KEngine::KComponent::Renderable::getWorldMatrix()
{
	//std::cout << "scale " << m_scale.x << " " << m_scale.y << " " << m_scale.z << "\n";
	//std::cout << "position " <<m_position.x << " " << m_position.y << " " << m_position.z << "\n";
	if (m_isWorldMatrixDirty) {
		m_isWorldMatrixDirty = false;
		m_worldMatirx =
			DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z)*
			DirectX::XMMatrixRotationQuaternion(m_rotation)*
			DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	}
	return m_worldMatirx;
}

Vector3 KEngine::KComponent::Renderable::getPosition()
{
	return m_position;
}

Vector3 KEngine::KComponent::Renderable::getScale()
{
	return m_scale;
}

Quaternion KEngine::KComponent::Renderable::getRotation()
{
	return m_rotation;
}

void KEngine::KComponent::Renderable::setPosition(Vector3 position)
{
	m_isWorldMatrixDirty = true;
}

void KEngine::KComponent::Renderable::setScale(Vector3 position)
{
	m_isWorldMatrixDirty = true;
}

void KEngine::KComponent::Renderable::setRotation(Quaternion quaternion)
{
	m_isWorldMatrixDirty = true;
}