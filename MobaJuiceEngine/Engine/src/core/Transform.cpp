#include "core/Transform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#define DEG_TO_RAD 0.017453293

namespace Engine {

	Transform::Transform()
	{
		localPosition = vec3(0);
		localScale = vec3(1);
		localRotation = vec3(0);
		localToWorld = mat4(1);
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
		SetScale(vec3(x, y, z));

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

	void Transform::Translate(vec3 translation)
	{
		localPosition += translation;
	}

	void Transform::Rotate(vec3 rotation)
	{
		localRotation += rotation;
		Transform::rotation = quat(vec3(float(localRotation.x * DEG_TO_RAD), float(localRotation.y * DEG_TO_RAD), float(localRotation.z * DEG_TO_RAD)));
	}

	void Transform::Scale(vec3 scale)
	{
		localScale += scale;
	}

	mat4 Transform::CalculateLocalToWorldMatrix(mat4 matrixStack)
	{
		mat4 transformMatrix(1.0f);
		mat4 translationMatrix = translate(mat4(1.0), localPosition);
		mat4 rotationMatrix = toMat4(rotation);
		mat4 scaleMatrix = scale(mat4(1.0), localScale);

		transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		localToWorld = matrixStack * transformMatrix;

		return localToWorld;
	}

	mat4 Transform::CalculateLocalToWorldMatrix()
	{
		if (parent == nullptr)
			return CalculateLocalToWorldMatrix(mat4(1.0));
		else
			return CalculateLocalToWorldMatrix(Transform::parent->GetLocalToWorldMatrix());
	}

	mat4 Transform::GetLocalToWorldMatrix()
	{
		if (parent) {
			return parent->CalculateLocalToWorldMatrix(mat4(1.0)) * CalculateLocalToWorldMatrix(mat4(1.0));
		}
		else {
			return CalculateLocalToWorldMatrix(mat4(1.0));
		}
	}

	mat4 Transform::GetLocalToWorldMatrix(mat4 matrixStack)
	{
		return matrixStack * CalculateLocalToWorldMatrix(mat4(1.0));
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
		transform.CalculateLocalToWorldMatrix();
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
	void Transform::OnLoad()
	{
		InitializeQuat();
	}
	void Transform::InitializeQuat()
	{
		Transform::rotation = quat(vec3(float(localRotation.x * DEG_TO_RAD), float(localRotation.y * DEG_TO_RAD), float(localRotation.z * DEG_TO_RAD)));
	}
}
