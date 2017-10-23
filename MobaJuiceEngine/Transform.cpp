#include "Transform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#define DEG_TO_RAD 0.017453293

Transform::Transform()
{
	localPosition = vec3(0);
	localScale = vec3(1);
	localRotation = vec3(0);
	localToWorld = mat4(1);
	rotation = quat();
	front = vec3(0, 0, 1);
	right = vec3(1, 0, 0);
	up = vec3(0, 1, 0);
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

mat4 Transform::calculateLocalToWorldMatrix(mat4 matrixStack)
{
	mat4 transformMatrix(1.0f);
	transformMatrix = translate(transformMatrix, localPosition);
	transformMatrix = transformMatrix * toMat4(rotation);
	transformMatrix = scale(transformMatrix, localScale);

	localToWorld = matrixStack * transformMatrix;

	return localToWorld;
}

mat4 Transform::calculateLocalToWorldMatrix()
{
	if (parent == nullptr)
		return calculateLocalToWorldMatrix(mat4(1.0));
	else
		return calculateLocalToWorldMatrix(Transform::parent->GetLocalToWorldMatrix());
}

mat4 Transform::GetLocalToWorldMatrix()
{
	if (parent) {
		return parent->calculateLocalToWorldMatrix(mat4(1.0)) * calculateLocalToWorldMatrix(mat4(1.0));
	}
	else {
		return calculateLocalToWorldMatrix(mat4(1.0));
	}
}

mat4 Transform::GetLocalToWorldMatrix(mat4 matrixStack)
{
	return matrixStack * calculateLocalToWorldMatrix(mat4(1.0));
}

void Transform::SetParent(const Transform& _parent)
{
	parent = make_shared<Transform>(_parent);
}

Transform * Transform::GetParent()
{
	return parent.get();
}

void Transform::AddChildren(Transform& transform)
{
	transform.slot = numOfChildren;
	transform.SetParent(*this);
	transform.calculateLocalToWorldMatrix();
	children.push_back(make_shared<Transform>(transform));
	numOfChildren++;
}

void Transform::RemoveChildren(int slot)
{
	children.erase(children.begin() + slot);
}

void Transform::SetSlot(int _slot)
{
	slot = _slot;
}

void Transform::Detach()
{
	if (parent == nullptr)
		return;

	parent->numOfChildren--;
	parent->RemoveChildren(slot);
	parent == nullptr;

	localToWorld = mat4(1.0);
}

vec3 Transform::Front()
{
	vec4 v = rotation * vec4(front, 1);
	return vec3(v.x, v.y, v.z);
}

vec3 Transform::Right()
{
	vec4 v = rotation * vec4(right, 1);
	return vec3(v.x, v.y, v.z);
}

vec3 Transform::Up()
{
	vec4 v = rotation * vec4(up, 1);
	return vec3(v.x, v.y, v.z);
}


//Privates
