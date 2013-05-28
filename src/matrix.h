#ifndef MATRIX_H
#define MATRIX_H
#include <QtOpenGL>

typedef GLfloat Mat[4][4];
typedef GLfloat Vertex[3];

const Mat Identity =
    {{1,0,0,0},
     {0,1,0,0},
     {0,0,1,0},
     {0,0,0,1}};

    void CopyMat(const Mat src, Mat dest);
    void CopyVert(const Vertex src, Vertex dest);
    void XRot(GLfloat rx, Mat result);
    void YRot(GLfloat ry, Mat result);
    void ZRot(GLfloat rz, Mat result);
    void ApplyMatrix(Vertex Vert, const Mat M);
    void InvApplyMatrix(Vertex Vert, const Mat M);
    void ConcatMatrix(const Mat Ma, Mat Mb);

#endif // MATRIX_H
