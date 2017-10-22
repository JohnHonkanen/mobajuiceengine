#include "Transform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#define DEG_TO_RAD 0.017453293

Transform::Transform()
{
	localPosition = vec3(0);
	localScale = vec3(1);
	localRotation = vec3(0);

	rotation = quat();
}


Transform::~Transform()
{
}

void Transform::SetEulerAngle(vec3 angle)
{
	localRotation = angle;
	rotation = quat(vec3(float(angle.x * DEG_TO_RAD), float(angle.y * DEG_TO_RAD), float(angle.z * DEG_TO_RAD)));
}

void Transform::SetScale(vec3 scale)
{
	localScale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	SetScale(vec3(x,y,z));
	
}

void Transform::SetPosition(vec3 position)
{
	localPosition = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	SetPosition(vec3(x, y, z));
}

vec3 Transform::GetPosition()
{
	return localPosition;
}

vec3 Transform::GetScale()
{
	return localScale;
}

vec3 Transform::GetRotation()
{
	return localRotation;
}

quat Transform::GetQuaternion()
{
	return rotation;
}

mat4 Transform::GetModelMatrix(mat4 modelMatrix)
{

	modelMatrix = translate(modelMatrix, localPosition);
	modelMatrix = modelMatrix * toMat4(rotation);
	modelMatrix = scale(modelMatrix, localScale);

	return modelMatrix;
}

mat4 Transform::GetModelMatrix()
{
	return GetModelMatrix(mat4(1.0));
}
