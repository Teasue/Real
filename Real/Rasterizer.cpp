#include "Rasterizer.h"

Rasterizer::Rasterizer(Matrix4* m_mvp, Matrix4* s_mvp, Matrix4* m_model, TGAImage* image, Vector3 light_dir, float* s_buffer) :
	mvpM(*m_mvp), tgaImage(image), lightDir(light_dir), shadowBuffer(s_buffer) {
	light_dir.Normalize();
	Matrix4 invertMVP = Matrix4(*m_mvp).invertGeneral();
	modelM = Matrix4(*m_model).invertGeneral().transpose();
	shadowM = (*s_mvp) * invertMVP;
	depthPass = false;
}

Vector4 Rasterizer::Vertex(int id, const Vector4& modelPts, const Vector3& uv, const Vector4& normalDir){
	return Vector4();
}

Matrix4 Rasterizer::GetModelMatrix(float yaw){
	Matrix4 rotation(Matrix4::identity);
	rotation.rotate(yaw, 0, 1, 0);
	Matrix4 transform(Matrix4::identity);
	Matrix4 scale(Matrix4::identity);

	return transform * rotation * scale;
}

Matrix4 Rasterizer::GetViewMatrix(Vector3& eye){
	Vector3 up(0, 1, 0);
	Vector3 target(0, 0, 0);
	Vector3 axis_z = (target - eye).Normalize();
	Vector3 axis_x = (up, axis_z).Normalize();
	Vector3 axis_y = (axis_z, axis_x).Normalize();
	Matrix4 t(Matrix4::identity);
	t[12] = -eye.x;
	t[13] = -eye.y;
	t[14] = -eye.z;
	Matrix4 r(axis_x.x, axis_x.y, axis_x.z, 0,
		axis_y.x, axis_y.y, axis_y.z, 0,
		axis_z.x, axis_z.y, axis_z.z, 0,
		0, 0, 0, 1);
	
	return r * t;
}

Matrix4 Rasterizer::GetProjectionMatrix(float aspect){
	float fov = 60 / 180 * 3.14;

	Matrix4 m(1 / tan(fov / 2) / aspect, 0, 0, 0,
		0, 1 / tan(fov / 2), 0, 0,
		0, 0, -(PROJECTION_VIEW_F + PROJECTION_VIEW_N) / (PROJECTION_VIEW_F - PROJECTION_VIEW_N), -1,
		0, 0, -2 * PROJECTION_VIEW_F * PROJECTION_VIEW_N / (PROJECTION_VIEW_F - PROJECTION_VIEW_N), 0);

	return m;
}
