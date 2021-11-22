#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
using namespace MATH;
class Camera {
public:
	Camera(const float fovy, const float aspectRatio_, const float near_, const float far_);
	~Camera();
	Matrix4 setPerspective(float fovy_, float aspectRatio_, float near_, float far_);
	inline Matrix4 getProjectionMatrix() { return projection; }
	inline Matrix4 getViewMatrix() { return view; }
	inline Matrix4 setRotation(float angle_, Vec3 rotation_) { rotation = MMath::rotate(angle_, rotation_); };
	inline Matrix4 getRotation() { return rotation; };
	inline Matrix4 setProjectionMatrix(Matrix4 projection_) { projection = projection_; };
	inline Matrix4 setViewMatrix(Matrix4 view_) { view = view_; };
	inline Vec3 setPosition(Vec3 pos_) { pos = pos_; };
private:
	Matrix4 projection, view, rotation, translate;
	Vec3 pos;
};
#endif