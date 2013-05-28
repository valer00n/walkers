#include "matrix.h"

void CopyVert(const Vertex src, Vertex dest) {
    for (int i = 0; i < 3; i++)
        dest[i] = src[i];
}

void CopyMat(const Mat src, Mat dest) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

void XRot(GLfloat rx, Mat result) {
    CopyMat(Identity, result);
    result[1][1] = cos(rx);
    result[2][1] = sin(rx);
    result[1][2] = -sin(rx);
    result[2][2] = cos(rx);
}

void YRot(GLfloat ry, Mat result) {
    CopyMat(Identity, result);
    result[0][0] = cos(ry);
    result[0][2] = sin(ry);
    result[2][0] = -sin(ry);
    result[2][2] = cos(ry);
}

void ZRot(GLfloat rz, Mat result) {
    CopyMat(Identity, result);
    result[0][0] = cos(rz);
    result[1][0] = sin(rz);
    result[0][1] = -sin(rz);
    result[1][1] = cos(rz);
}

void ConcatMatrix(const Mat Ma, Mat Mb) {
    Mat T;
    for (int c = 0;  c < 4; c++)
        for (int r = 0; r < 4; r++)
            T[c][r] = Ma[0][r] * Mb[c][0] +
                    Ma[1][r] * Mb[c][1] +
                    Ma[2][r] * Mb[c][2] +
                    Ma[3][r] * Mb[c][3];
    CopyMat(T, Mb);
}

void ApplyMatrix(Vertex Vert, const Mat M) {
    Vertex N;
    N[0] = Vert[0] * M[0][0] + Vert[1] * M[1][0] + Vert[2] * M[2][0] + M[3][0];
    N[1] = Vert[0] * M[0][1] + Vert[1] * M[1][1] + Vert[2] * M[2][1] + M[3][1];
    N[2] = Vert[0] * M[0][2] + Vert[1] * M[1][2] + Vert[2] * M[2][2] + M[3][2];
    CopyVert(N, Vert);
}

void InvApplyMatrix(Vertex Vert, const Mat M) {
    Vert[0] = Vert[0] - M[3][0];
    Vert[1] = Vert[1] - M[3][1];
    Vert[2] = Vert[2] - M[3][2];
    Vertex N;
    N[0] = Vert[0] * M[0][0] + Vert[1] * M[0][1] + Vert[2] * M[0][2];
    N[1] = Vert[0] * M[1][0] + Vert[1] * M[1][1] + Vert[2] * M[1][2];
    N[2] = Vert[0] * M[2][0] + Vert[1] * M[2][1] + Vert[2] * M[2][2];
    CopyVert(N, Vert);
}
