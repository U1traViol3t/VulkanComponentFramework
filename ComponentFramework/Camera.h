#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
#include "MMath.h"
using namespace MATH;
class Camera {
public:
	Camera();
	~Camera();
	inline Matrix4 getProjectionMatrix() { return projection; }
	inline Matrix4 getViewMatrix() { return rotation * translate; }
	inline Matrix4 getRotation() { return rotation; };
	inline void setRotation(const float angle_, const Vec3& rotation_) { rotation = MMath::rotate(angle_, rotation_); };
	inline void setProjectionMatrix(Matrix4 projection_) { projection = projection_; };
	inline void setViewMatrix(Matrix4 view_) { view = view_; };
	inline void setPosition(const Vec3& pos_) { translate = MMath::translate(pos_); };
	inline void Perspective(const float fovy_, const float aspectRatio_, const float near_, const float far_) { projection = MMath::perspective(fovy_, aspectRatio_, near_, far_); };
	inline void lookAt(const Vec3& eye_, const Vec3& at_, const Vec3& up_) { view = MMath::lookAt(eye_, at_, up_); };
private:
	Matrix4 projection, view, rotation, translate;
};
#endif