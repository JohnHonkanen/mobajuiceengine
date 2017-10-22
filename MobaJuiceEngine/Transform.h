/*
Transform Class: TO be filled in later
*/
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <memory>

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

private:
	vec3 localPosition;
	vec3 localScale;
	vec3 localRotation;

	quat rotation;
};

