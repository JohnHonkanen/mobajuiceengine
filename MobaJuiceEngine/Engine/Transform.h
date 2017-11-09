/*
	Transform class used for the generation of the model matrix. Also holds the heirachy information fór the game object.
	Dev: B00291253
*/
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <memory>
#include <vector>

using namespace glm;
using namespace std;
namespace Engine {
	class Transform : std::enable_shared_from_this<Transform>
	{
	public:
		Transform();
		~Transform();
		/*
			Sets the Rotation of the transform.
			@param angle vector of the rotation transform in euler angles
		*/
		void SetEulerAngle(vec3 angle);
		/*
			Sets the scale of the transform
			@param scale	Scale vector
		*/
		void SetScale(vec3 scale);
		/*
			Sets the scale of the transform
			@param x	Scale on X axis
			@param y	Scale on Y axis
			@param z	Scale on Z axis
		*/
		void SetScale(float x, float y, float z);
		/*
			Sets the local position of the transform
			@param position		position coordinates
		*/
		void SetPosition(vec3 position);
		/*
			Sets the local position of the transform
			@param x	x position
			@param y	y position
			@param z	z position
		*/
		void SetPosition(float x, float y, float z);

		//Get the local position
		vec3 GetPosition();
		//Get the local scale
		vec3 GetScale();
		//Get the local rotation in euler angles
		vec3 GetRotation();
		//Get the rotation quaternion
		quat GetQuaternion();

		/*
			Translate the position by translational distance
			@param translation	translational distance
		*/
		void Translate(vec3 translation);
		/*
			Rotate the rotation by an Euler Angle
			@param rotation	Euler angle
		*/
		void Rotate(vec3 rotation);
		/*
			Scale by a scaling value
			@param scale scaling value
		*/
		void Scale(vec3 scale);

		/*
			Calculates this Local To World Matrix using a matrixStack to build upon
			@param matrixStack	Stack to build upon;
		*/
		mat4 CalculateLocalToWorldMatrix(mat4 matrixStack);

		/*
		Calculates this Local To World Matrix
		*/
		mat4 CalculateLocalToWorldMatrix();
		/*
			Gets the local to world matrix transformation
		*/
		mat4 GetLocalToWorldMatrix();

		/*
			Get Local to World Matrix Transformation passing in a parent stack
		*/
		mat4 GetLocalToWorldMatrix(mat4 matrixStack);

		/*
			Set the Parent Transform
			@parem _parent The parent transform the attach to
		*/
		void SetParent(const Transform& _parent);

		/*
			Get the parent Transfor Read Only
		*/
		Transform* GetParent();

		/*
			Add Children to this transform
		*/
		void AddChildren(Transform& transform);
		/*
			Remove Children from this transform
			@param slot to remove;
		*/
		void RemoveChildren(int slot);

		/*
			Sets the Index of this Transform
			@param slot	Index
		*/
		void SetSlot(int _slot);

		/*
			Detach this transform from the parent
		*/
		void Detach();
		/*
			Get the front vector
		*/
		vec3 Front();
		/*
			Get the right vector
		*/
		vec3 Right();
		/*
			Get the top vector
		*/
		vec3 Up();
	private:
		int slot = -1;
		int numOfChildren = 0;
		shared_ptr<Transform> parent;
		vector<shared_ptr<Transform>> children;

		vec3 localPosition;
		vec3 localScale;
		vec3 localRotation;

		vec3 front;
		vec3 right;
		vec3 up;

		quat rotation;

		mat4 localToWorld;
		mat4 localToParent;
	};
}

