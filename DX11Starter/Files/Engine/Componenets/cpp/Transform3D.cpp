#include <Engine\Componenets\Transform3D.h>
using namespace KEngine::KComponent;
void Transform3D::setPosition(float x, float y, float z)
{
	position = Vector3(x, y, z);
	isDirty = true;
}