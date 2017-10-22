/*
Transform Class: TO be filled in later
*/
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <memory>
#include <vector>

using namespace glm;
using namespace std;
class Transform;
class Transform
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
		Calculate the Model Matrix using the matrix provided
		@param modelMatrix		Matrix to stack transformation on
	*/
	mat4 GetModelMatrix(mat4 modelMatrix);
	/*
		Calculat the MOdel matrix using an identity matrix
	*/
	mat4 GetModelMatrix();

	/*
		Gets the local to world matrix transformation
	*/
	mat4 GetLocalToWorldMatrix();

	/*
		Set the Parent Transform
		@parem _parent The parent transform the attach to
	*/
	void SetParent(shared_ptr<Transform> _parent);

	/*
		Get the parent Transfor Read Only
	*/
	const Transform* const GetParent();

	/*
		Add Children to this transform
	*/
	void AddChildren(shared_ptr<Transform> transform);
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
private:
	int slot = -1;
	int numOfChildren = 0;
	shared_ptr<Transform> parent;
	vector<shared_ptr<Transform>> children;

	vec3 localPosition;
	vec3 localScale;
	vec3 localRotation;

	quat rotation;

	mat4 localToWorld;
};

