#pragma once
#include "Matrix.h"
#include "tgaimage.h"
#include "Const.h"

class Rasterizer {
public:
    Rasterizer(Matrix4* m_mvp, Matrix4* s_mvp, Matrix4* m_model, TGAImage* image, Vector3 lightDir, float* s_Buffer);
    Rasterizer(const Rasterizer&);
    ~Rasterizer() {};

    Vector4 Vertex(int id, const Vector4& modelPts, const Vector3& uv, const Vector4& normalDir);
    TGAColor Fragment(const Vector3& bar);

    Matrix4 GetModelMatrix(float yaw);
    Matrix4 GetViewMatrix(Vector3& eye);
    Matrix4 GetProjectionMatrix(float aspect);

public:
    Matrix3 uv;
    Matrix4 norlmal;
    Matrix4 clip;

private:
    TGAImage* tgaImage;
    Matrix4 mvpM;
    Matrix4 modelM;
    Matrix4 shadowM;
    Vector3 lightDir;
    float* shadowBuffer;
    bool depthPass;
};