#include "KeyAxis.h"

Engine::KeyAxis::KeyAxis()
{
}

Engine::KeyAxis::KeyAxis(string name, string positive, string negative)
{
	KeyAxis::name = name;
	KeyAxis::positive = positive;
	KeyAxis::negative = negative;


}

int Engine::KeyAxis::GetValue()
{

	return positivePressed - negativePressed;
}

void Engine::KeyAxis::GetKeys(string & positive, string & negative)
{
	positive = KeyAxis::positive;
	negative = KeyAxis::negative;
}

void Engine::KeyAxis::SetPress(int positivePressed, int negativePressed)
{
	KeyAxis::positivePressed = positivePressed;

	KeyAxis::negativePressed = negativePressed;
}
