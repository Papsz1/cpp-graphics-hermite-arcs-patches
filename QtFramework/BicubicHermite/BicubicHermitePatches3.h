#ifndef BICUBICHERMITEPATCHES3_H
#define BICUBICHERMITEPATCHES3_H

#include "../Core/Constants.h"
#include "../Core/TensorProductSurfaces3.h"

namespace cagd
{
    enum Variable{U, V};

    class BicubicHermitePatch3: public TensorProductSurface3
    {

    public:
        BicubicHermitePatch3(GLdouble u = 1.0, GLdouble v = 1.0);

        // inherited pure virtual methods have to be redeclared and defined
        GLboolean UBlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &blending_values) const;
        GLboolean VBlendingFunctionValues(GLdouble v, RowMatrix<GLdouble> &blending_values) const;
        GLboolean CalculatePartialDerivatives(
                        GLuint maximum_order_of_partial_derivatives,
                        GLdouble u, GLdouble v, PartialDerivatives &pd) const;

        // other setters/getters, e.g., in the case of Hermite projects, one can also
        // introduce the next (more intuitively named) methods (row ∈ {0,1}, column ∈ {0,1})
        GLboolean SetCorner(GLuint row, GLuint column, GLdouble x, GLdouble y, GLdouble z);
        GLboolean SetCorner(GLuint row, GLuint column, const DCoordinate3 &corner);

        GLboolean SetUTangent(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z);
        GLboolean SetUTangent(GLuint row, GLuint column, const DCoordinate3 &u_tangent);

        GLboolean SetVTangent(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z);
        GLboolean SetVTangent(GLuint row, GLuint column, const DCoordinate3 &v_tangent);

        GLboolean SetTwistVector(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z);
        GLboolean SetTwistVector(GLuint row, GLuint column, const DCoordinate3 &twist);

        GLboolean SetMatrixValue(GLuint row, GLuint column, const DCoordinate3 &twist);
        GLboolean SetMatrixValue(GLuint row, GLuint column, const GLdouble x, const GLdouble y, const GLdouble z);

        DCoordinate3& GetCorner(GLuint row, GLuint column);
        DCoordinate3& GetUTangent(GLuint row, GLuint column);
        DCoordinate3& GetVTangent(GLuint row, GLuint column);
        DCoordinate3& GetTwistVector(GLuint row, GLuint column);

        DCoordinate3& GetMatrixValue(GLuint row, GLuint column) const;

        GLboolean GetDataForInterpolation(GLuint row, GLuint column, DCoordinate3 &point);

        GLboolean RenderData(GLenum render_mode = GL_LINE_STRIP) const;
        GLboolean UpdateVertexBufferObjectsOfData(GLenum usage_flag = GL_STATIC_DRAW);
    };

    inline std::ostream& operator <<(std::ostream& lhs, const BicubicHermitePatch3& rhs)
    {
        return lhs<< " " << rhs.GetMatrixValue(0, 0) << " " << rhs.GetMatrixValue(0, 1) << " " << rhs.GetMatrixValue(0, 2) <<  " " << rhs.GetMatrixValue(0, 3)
                  << " " << rhs.GetMatrixValue(1, 0) << " " << rhs.GetMatrixValue(1, 1) << " " << rhs.GetMatrixValue(1, 2) <<  " " << rhs.GetMatrixValue(1, 3)
                  << " " << rhs.GetMatrixValue(2, 0) << " " << rhs.GetMatrixValue(2, 1) << " " << rhs.GetMatrixValue(2, 2) <<  " " << rhs.GetMatrixValue(2, 3)
                  << " " << rhs.GetMatrixValue(3, 0) << " " << rhs.GetMatrixValue(3, 1) << " " << rhs.GetMatrixValue(3, 2) <<  " " << rhs.GetMatrixValue(3, 3);
    }

    // input from stream
    inline std::istream& operator >>(std::istream& lhs, BicubicHermitePatch3& rhs)
    {
        DCoordinate3 tmp;
        for (GLuint i = 0; i < 4; ++i)
        {
            for (GLuint j = 0; j < 4; ++j)
            {
                lhs >> tmp;
                rhs.SetMatrixValue(i, j, tmp);
            }
        }

        return lhs;
    }

}

#endif // BICUBICHERMITEPATCHES3_H
