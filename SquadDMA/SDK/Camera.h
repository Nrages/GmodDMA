#pragma once
#include "Engine.h"

class Camera
{
public:
	static Vector2 WorldToScreen(ViewMatrixStruct viewinfo, Vector3 world);
};