#include "Camera.h"
#include "MMath.h"

Camera::Camera(const float fovy, const float aspectRatio_, const float near_, const float far_)
{
	projection = MMath::perspective(fovy, aspectRatio_, near_, far_);
	view = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	std::cout << "Camera is ready!\n";
}

Camera::~Camera() {}