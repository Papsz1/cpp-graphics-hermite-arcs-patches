#include "BasisFunctions.h"
#include "BicubicHermiteArc3.h"
#include "BicubicHermitePatches3.h"
#include "../Core/DCoordinates3.h"

using namespace cagd;

BicubicHermitePatch3::BicubicHermitePatch3(GLdouble u, GLdouble v):TensorProductSurface3(0.0, u, 0.0, v)
{}

GLboolean BicubicHermitePatch3::UBlendingFunctionValues(
       GLdouble u_knot, RowMatrix<GLdouble>& blending_values) const
{
    blending_values.ResizeColumns(4);

    blending_values[0] = BicubicHermiteBasisFunctions::F0(u_knot);
    blending_values[1] = BicubicHermiteBasisFunctions::F1(u_knot);
    blending_values[2] = BicubicHermiteBasisFunctions::F2(u_knot);
    blending_values[3] = BicubicHermiteBasisFunctions::F3(u_knot);

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::VBlendingFunctionValues(
       GLdouble v_knot, RowMatrix<GLdouble>& blending_values) const
{
    blending_values.ResizeColumns(4);

    blending_values[0] = BicubicHermiteBasisFunctions::F0(v_knot);
    blending_values[1] = BicubicHermiteBasisFunctions::F1(v_knot);
    blending_values[2] = BicubicHermiteBasisFunctions::F2(v_knot);
    blending_values[3] = BicubicHermiteBasisFunctions::F3(v_knot);

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::CalculatePartialDerivatives(
       GLuint maximum_order_of_partial_derivatives,
       GLdouble u, GLdouble v, PartialDerivatives& pd) const
{
    if (u < 0.0 || u > 1 || v < 0.0 || v > 1 || maximum_order_of_partial_derivatives > 2)
        return GL_FALSE;

    RowMatrix<GLdouble> u_blending_values(4), d1_u_blending_values(4), d2_u_blending_values(4);
    RowMatrix<GLdouble> v_blending_values(4), d1_v_blending_values(4), d2_v_blending_values(4);

    UBlendingFunctionValues(u, u_blending_values);
    VBlendingFunctionValues(v, v_blending_values);

    d1_u_blending_values(0) = BicubicHermiteBasisFunctions::d1F0(u);
    d1_u_blending_values(1) = BicubicHermiteBasisFunctions::d1F1(u);
    d1_u_blending_values(2) = BicubicHermiteBasisFunctions::d1F2(u);
    d1_u_blending_values(3) = BicubicHermiteBasisFunctions::d1F3(u);

    d1_v_blending_values(0) = BicubicHermiteBasisFunctions::d1F0(v);
    d1_v_blending_values(1) = BicubicHermiteBasisFunctions::d1F1(v);
    d1_v_blending_values(2) = BicubicHermiteBasisFunctions::d1F2(v);
    d1_v_blending_values(3) = BicubicHermiteBasisFunctions::d1F3(v);

    d2_u_blending_values(0) = BicubicHermiteBasisFunctions::d2F0(u);
    d2_u_blending_values(1) = BicubicHermiteBasisFunctions::d2F1(u);
    d2_u_blending_values(2) = BicubicHermiteBasisFunctions::d2F2(u);
    d2_u_blending_values(3) = BicubicHermiteBasisFunctions::d2F3(u);

    d2_v_blending_values(0) = BicubicHermiteBasisFunctions::d2F0(v);
    d2_v_blending_values(1) = BicubicHermiteBasisFunctions::d2F1(v);
    d2_v_blending_values(2) = BicubicHermiteBasisFunctions::d2F2(v);
    d2_v_blending_values(3) = BicubicHermiteBasisFunctions::d2F3(v);

    pd.ResizeRows(3);
    pd.LoadNullVectors();

    for(GLuint row = 0; row < 4; ++row)
    {
        DCoordinate3 aux_d0_v, aux_d1_v, aux_d2_v;
        for (GLuint column = 0; column < 4; ++column)
        {
            aux_d0_v += _data(row, column) * v_blending_values(column);
            aux_d1_v += _data(row, column) * d1_v_blending_values(column);
            aux_d2_v += _data(row, column) * d2_v_blending_values(column);
        }

        pd(0, 0) += aux_d0_v * u_blending_values(row);
        pd(1, 0) += aux_d0_v * d1_u_blending_values(row);
        pd(1, 1) += aux_d1_v * u_blending_values(row);
        
        // experiment
        pd(2, 0) += aux_d0_v * d2_u_blending_values(row);
        pd(2, 1) += aux_d1_v * d1_u_blending_values(row);
        pd(2, 2) += aux_d2_v * u_blending_values(row);
    }

    return GL_TRUE;
}


// _data(row, column) =         corner;
// _data(2 + row, column) =     u_tangent;
// _data(row, 2+column) =       v_tangent;
// _data(2 + row, 2 + column) = twist;

GLboolean BicubicHermitePatch3::SetCorner(GLuint row, GLuint column, GLdouble x, GLdouble y, GLdouble z)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row, column).x() = x;
    _data(row, column).y() = y;
    _data(row, column).z() = z;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetCorner(GLuint row, GLuint column, const DCoordinate3 &corner)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row, column) = corner;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetUTangent(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row + 2, column).x() = t_x;
    _data(row + 2, column).y() = t_y;
    _data(row + 2, column).z() = t_z;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetUTangent(GLuint row, GLuint column, const DCoordinate3 &u_tangent)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row + 2, column) = u_tangent;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetVTangent(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row, column + 2).x() = t_x;
    _data(row, column + 2).y() = t_y;
    _data(row, column + 2).z() = t_z;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetVTangent(GLuint row, GLuint column, const DCoordinate3 &v_tangent)
{
    if (row > 1 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row, column + 2) = v_tangent;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetTwistVector(GLuint row, GLuint column, GLdouble t_x, GLdouble t_y, GLdouble t_z)
{
    if (row > 1 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row + 2, column + 2).x() = t_x;
    _data(row + 2, column + 2).y() = t_y;
    _data(row + 2, column + 2).z() = t_z;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::SetTwistVector(GLuint row, GLuint column, const DCoordinate3 &twist)
{
    if (row < 0 || row > 1 || column < 0 || column > 1)
        return GL_FALSE;

    // Hogyan lehet igazabol set-elni az ertekeket
    _data(row + 2, column + 2) = twist;

    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::RenderData(GLenum render_mode) const
{
    if (!_vbo_data)
        return GL_FALSE;

    if (render_mode != GL_LINE_STRIP && render_mode != GL_LINE_LOOP && render_mode != GL_POINTS)
        return GL_FALSE;

    glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
            glVertexPointer(3, GL_FLOAT, 0, nullptr);

            // points
            glPointSize(15.0f);
            glColor3f(1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 1);

            glColor3f(1.0f, 0.4f, 0.0f);
            glDrawArrays(GL_POINTS, 1, 1);

            glColor3f(0.7f, 1.0f, 1.0f);
            glDrawArrays(GL_POINTS, 2, 1);

            glColor3f(0.2f, 0.4f, 0.3f);
            glDrawArrays(GL_POINTS, 3, 1);


            // lines
            //v tangents
            glPointSize(1.0f);
            glColor3f(0.0f, 1.0f, 1.0f);
            glDrawArrays(GL_LINES, 4, 8);
            //u tangents
            glColor3f(0.5f, 0.0f, 0.5f);
            glDrawArrays(GL_LINES, 12, 8);
            //twist tangents
            glColor3f(0.8f, 0.8f, 0.0f);
            glDrawArrays(GL_LINES, 20, 8);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);

    return GL_TRUE;
}


GLboolean BicubicHermitePatch3::UpdateVertexBufferObjectsOfData(GLenum usage_flag)
{
    GLuint data_count = _data.GetRowCount();
    if (!data_count)
        return GL_FALSE;

    if (usage_flag != GL_STREAM_DRAW  && usage_flag != GL_STREAM_READ  && usage_flag != GL_STREAM_COPY
     && usage_flag != GL_DYNAMIC_DRAW && usage_flag != GL_DYNAMIC_READ && usage_flag != GL_DYNAMIC_COPY
     && usage_flag != GL_STATIC_DRAW  && usage_flag != GL_STATIC_READ  && usage_flag != GL_STATIC_COPY)
        return GL_FALSE;

    DeleteVertexBufferObjectsOfData();

    glGenBuffers(1, &_vbo_data);
    if (!_vbo_data)
        return GL_FALSE;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);

    glBufferData(GL_ARRAY_BUFFER, 28 * 3 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);

    GLfloat *coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (!coordinate)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        DeleteVertexBufferObjectsOfData();
        return GL_FALSE;
    }

    // _data(row, column) =         corner;
    // _data(2 + row, column) =     u_tangent;
    // _data(row, 2 + column) =     v_tangent;
    // _data(2 + row, 2 + column) = twist;

    // p00
    coordinate[0] = _data(0, 0).x();
    coordinate[1] = _data(0, 0).y();
    coordinate[2] = _data(0, 0).z();

    // p01
    coordinate[3] = _data(0, 1).x();
    coordinate[4] = _data(0, 1).y();
    coordinate[5] = _data(0, 1).z();

    // p10
    coordinate[6] = _data(1, 0).x();
    coordinate[7] = _data(1, 0).y();
    coordinate[8] = _data(1, 0).z();

    // p11
    coordinate[9] = _data(1, 1).x();
    coordinate[10] = _data(1, 1).y();
    coordinate[11] = _data(1, 1).z();

    GLuint index = 12;

// Mas sorrendu felepites:
// Itt eloszor a p00 hoz tartozo vonalak jonnek, utana p01 es igy tovabb
//    for (GLuint i = 0; i < 2; ++i)
//    {
//        for (GLuint j = 0; j < 2; ++j)
//        {
//            // u_tangent derivate
//            // point
//            coordinate[index++] = _data(i, j).x();
//            coordinate[index++] = _data(i, j).y();
//            coordinate[index++] = _data(i, j).z();
//            // point, u_tangent sum
//            coordinate[index++] = _data(i, j + 2).x();
//            coordinate[index++] = _data(i, j + 2).y();
//            coordinate[index++] = _data(i, j + 2).z();


//            // v_tangent
//            // point
//            coordinate[index++] = _data(i, j).x();
//            coordinate[index++] = _data(i, j).y();
//            coordinate[index++] = _data(i, j).z();
//            // point, v_tangent sum
//            coordinate[index++] = _data(i + 2, j).x();
//            coordinate[index++] = _data(i + 2, j).y();
//            coordinate[index++] = _data(i + 2, j).z();

//            // twist
//            // point
//            coordinate[index++] = _data(i, j).x();
//            coordinate[index++] = _data(i, j).y();
//            coordinate[index++] = _data(i, j).z();
//            // point, twist sum
//            coordinate[index++] = _data(i + 2, j + 2).x();
//            coordinate[index++] = _data(i + 2, j + 2).y();
//            coordinate[index++] = _data(i + 2, j + 2).z();
//        }
            
//    }

// Itt pedig inkabb u, v es twist szerint kerulnek bele a vbo-ba
    for(GLuint i = 0; i < 2; i++) {
        for(GLuint j = 0; j < 2; j++) {
            coordinate[index++] = _data(i, j).x();
            coordinate[index++] = _data(i, j).y();
            coordinate[index++] = _data(i, j).z();
            // point, v_tangent sum
            coordinate[index++] = _data(i, j + 2).x();
            coordinate[index++] = _data(i, j + 2).y();
            coordinate[index++] = _data(i, j + 2).z();
        }
    }
    for(GLuint i = 0; i < 2; i++) {
        for(GLuint j = 0; j < 2; j++) {
            coordinate[index++] = _data(i, j).x();
            coordinate[index++] = _data(i, j).y();
            coordinate[index++] = _data(i, j).z();
            // point, u_tangent sum
            coordinate[index++] = _data(i + 2, j).x();
            coordinate[index++] = _data(i + 2, j).y();
            coordinate[index++] = _data(i + 2, j).z();
        }
    }
    for(GLuint i = 0; i < 2; i++) {
        for(GLuint j = 0; j < 2; j++) {
            coordinate[index++] = _data(i, j).x();
            coordinate[index++] = _data(i, j).y();
            coordinate[index++] = _data(i, j).z();
            // point, twist sum
            coordinate[index++] = _data(i + 2, j + 2).x();
            coordinate[index++] = _data(i + 2, j + 2).y();
            coordinate[index++] = _data(i + 2, j + 2).z();
        }
    }
    if (!glUnmapBuffer(GL_ARRAY_BUFFER))
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        DeleteVertexBufferObjectsOfData();
        return GL_FALSE;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return GL_TRUE;
}

DCoordinate3& BicubicHermitePatch3::GetCorner(GLuint row, GLuint column)
{
    DCoordinate3 *corner = new DCoordinate3(); 
    if (row > 1 || column > 1)
        return *corner;

    *corner = _data(row, column);
    return *corner;
}

DCoordinate3& BicubicHermitePatch3::GetUTangent(GLuint row, GLuint column)
{
    DCoordinate3 *u_tangent = new DCoordinate3(); 
    if (row > 1 || column > 1)
        return *u_tangent;

    *u_tangent = _data(row + 2, column);
    return *u_tangent;
}

DCoordinate3& BicubicHermitePatch3::GetVTangent(GLuint row, GLuint column)
{
    DCoordinate3 *v_tangent = new DCoordinate3(); 
    if (row > 1 || column > 1)
        return *v_tangent;

    *v_tangent = _data(row, column + 2);
    return *v_tangent;
}


DCoordinate3& BicubicHermitePatch3::GetTwistVector(GLuint row, GLuint column)
{
    DCoordinate3 *twist = new DCoordinate3(); 
    if (row > 1 || column > 1)
        return *twist;

    *twist = _data(row + 2, column + 2);
    return *twist;
}

GLboolean BicubicHermitePatch3::SetMatrixValue(GLuint row, GLuint column, const DCoordinate3 &point)
{
    if (row < 0 || row > 4 || column < 0 || column > 4)
        return GL_FALSE;

    _data(row, column) = point;
    return GL_TRUE;
}

GLboolean BicubicHermitePatch3::GetDataForInterpolation(GLuint row, GLuint column, DCoordinate3 &point)
{
    if(row < 0 || row > 3 || column < 0 || column > 3)
        return GL_FALSE;

    if(row >= 2 && column >= 2)
    {
        point = _data(row, column) + _data(row - 2, column - 2);
    }
    else if (row >= 2 && column < 2)
    {
        point = _data(row, column) + _data(row - 2, column);
    }
    else if (row < 2 && column >= 2)
    {
        point = _data(row, column) + _data(row, column - 2);
    }
    else
    {
        point = _data(row, column);
    }

    return GL_TRUE;   
}

GLboolean BicubicHermitePatch3::SetMatrixValue(GLuint row, GLuint column, const GLdouble x, const GLdouble y, const GLdouble z)
{
    if (row < 0 || row > 4 || column < 0 || column > 4)
        return GL_FALSE;

    _data(row, column).x() = x;
    _data(row, column).y() = y;
    _data(row, column).z() = z;

    return GL_TRUE;
}

DCoordinate3& BicubicHermitePatch3::GetMatrixValue(GLuint row, GLuint column) const
{
    DCoordinate3 *a = new DCoordinate3(); 
    if (row < 0 || row > 4 || column < 0 || column > 4)
        return *a;
    
    a->x() = _data(row, column).x();
    a->y() = _data(row, column).y();
    a->z() = _data(row, column).z();

    return *a;
}
