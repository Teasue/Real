#pragma once
#include <math.h>
#include "Vector3.h"

using namespace std;

class Camera {
public:
	Vector3 pos;
	Vector3 target;
	Vector3 up;

	Camera(const Vector3& pos, const Vector3& target, const Vector3& up);
	~Camera();
};