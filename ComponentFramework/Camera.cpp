#include "Camera.h"
#include "MMath.h"
#include "Debug.h"

Camera::Camera(const float fovy, const float aspectRatio_, const float near_, const float far_) {
	//projection = MMath::perspective(fovy, aspectRatio_, near_, far_);
	view = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	Debug::Info("Camera is ready!", __FILE__, __LINE__);
}
Camera::~Camera() {}
Matrix4 Camera::setPerspective(float fovy_, float aspectRatio_, float near_, float far_) {
	projection = MMath::perspective(fovy_, aspectRatio_, near_, far_);
}
