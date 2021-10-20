#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
using namespace MATH;
class Camera {
public:
	Camera(const float fovy, const float aspectRatio_, const float near_, const float far_);
	~Camera();
	inline Matrix4 getProjectionMatrix() { return projection; }
	inline Matrix4 getViewMatrix() { return view; }
	inline Matrix4 setProjectionMatrix(Matrix4 projection_) { projection = projection_; };
	inline Matrix4 setViewMatrix(Matrix4 view_) { view = view_; };
private:
	Matrix4 projection, view, rotation, translate;

};
#endif