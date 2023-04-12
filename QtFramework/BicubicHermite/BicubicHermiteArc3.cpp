#include "BasisFunctions.h"
#include "BicubicHermiteArc3.h"

using namespace std;
using namespace cagd;

GLboolean BicubicHermiteArc3::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const
{
    values.ResizeColumns(4);

    values[0] = BicubicHermiteBasisFunctions::F0(u);
    values[1] = BicubicHermiteBasisFunctions::F1(u);
    values[2] = BicubicHermiteBasisFunctions::F2(u);
    values[3] = BicubicHermiteBasisFunctions::F3(u);

    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const
{
    d.ResizeRows(max_order_of_derivatives + 1);
    d.LoadNullVectors();

    d[0] = BicubicHermiteBasisFunctions::F0(u) * _data[0] + BicubicHermiteBasisFunctions::F1(u) * _data[1] 
    // data[2] es data[3] -- a pontokban huzott derivaltjaik
            + BicubicHermiteBasisFunctions::F2(u) * _data[2] + BicubicHermiteBasisFunctions::F3(u) * _data[3];

    if(max_order_of_derivatives >= 1) 
    {
        d[1] = BicubicHermiteBasisFunctions::d1F0(u) * _data[0] + BicubicHermiteBasisFunctions::d1F1(u) * _data[1] 
                + BicubicHermiteBasisFunctions::d1F2(u) * _data[2] + BicubicHermiteBasisFunctions::d1F3(u) * _data[3];
    }

    if(max_order_of_derivatives == 2) 
    {
        d[2] = BicubicHermiteBasisFunctions::d2F0(u) * _data[0] + BicubicHermiteBasisFunctions::d2F1(u) * _data[1] 
                + BicubicHermiteBasisFunctions::d2F2(u) * _data[2] + BicubicHermiteBasisFunctions::d2F3(u) * _data[3];
    }
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;
        
    _data[corner_index].x() = x;
    _data[corner_index].y() = y;
    _data[corner_index].z() = z;
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::SetCorner(GLuint corner_index, const DCoordinate3 &position)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;
    
    _data[corner_index] = position;
    return GL_TRUE;   
}

GLboolean BicubicHermiteArc3::SetTangent(GLuint corner_index, GLdouble t_x, GLdouble t_y, GLdouble t_z)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    _data[corner_index + 2].x() = t_x;
    _data[corner_index + 2].y() = t_y;
    _data[corner_index + 2].z() = t_z;
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::SetTangent(GLuint corner_index, const DCoordinate3 &tangent)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    _data[corner_index + 2] = tangent;
    return GL_TRUE;   
}

BicubicHermiteArc3::BicubicHermiteArc3(/*GLdouble alpha, */GLenum data_usage_flag):LinearCombination3(0.0, 1.0, 4, data_usage_flag)
{}

BicubicHermiteArc3::BicubicHermiteArc3(const BicubicHermiteArc3 &a):
    LinearCombination3(a)
{}


GLboolean BicubicHermiteArc3::RenderData(GLenum render_mode) const
{
    if (!_vbo_data)
        return GL_FALSE;

    if (render_mode != GL_LINE_STRIP && render_mode != GL_LINE_LOOP && render_mode != GL_POINTS && render_mode != GL_LINES)
        return GL_FALSE;

    glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
            glVertexPointer(3, GL_FLOAT, 0, nullptr);

            // 2 darab DCoord 1-1 pontglPointSize(100.0f);
            glPointSize(15.0f);
            glColor3f(1.0, 0.0, 0.0);
            glDrawArrays(GL_POINTS, 0, 2);

            // 2 darab szakasz 1-1 szakasz (4 pontot)
            glPointSize(1.0f);
            glColor3f(1.0, 1.0, 1.0);
            glDrawArrays(GL_LINES, 2, 4);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);

    return GL_TRUE;
}


// _data[0] _data[1]  p0, and p1 Dcoords
// _data[2] _data[3]  t0, and t1, p0's tangent and p1's tangent

GLboolean BicubicHermiteArc3::UpdateVertexBufferObjectsOfData(GLenum usage_flag)
{
    GLuint data_count = _data.GetRowCount();
    if (!data_count)
        return GL_FALSE;

    if (usage_flag != GL_STREAM_DRAW  && usage_flag != GL_STREAM_READ  && usage_flag != GL_STREAM_COPY
     && usage_flag != GL_DYNAMIC_DRAW && usage_flag != GL_DYNAMIC_READ && usage_flag != GL_DYNAMIC_COPY
     && usage_flag != GL_STATIC_DRAW  && usage_flag != GL_STATIC_READ  && usage_flag != GL_STATIC_COPY)
        return GL_FALSE;

    _data_usage_flag = usage_flag;

    DeleteVertexBufferObjectsOfData();

    glGenBuffers(1, &_vbo_data);
    if (!_vbo_data)
        return GL_FALSE;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_data);
    glBufferData(GL_ARRAY_BUFFER, (data_count / 2 * 3 * sizeof(GLfloat) + data_count * 3 * sizeof(GLfloat)), nullptr, _data_usage_flag);

    GLfloat *coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (!coordinate)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        DeleteVertexBufferObjectsOfData();
        return GL_FALSE;
    }

    DCoordinate3 p0, p1, t0, t1;

    // p0
    GetCorner(0, p0);
    // p1
    GetCorner(1, p1);
    // t0
    GetTangent(0, t0);
    // t1
    GetTangent(1, t1);

    // p0
    coordinate[0] = static_cast<GLfloat>(p0.x());
    coordinate[6]  = static_cast<GLfloat>(p0.x());

    coordinate[1] = static_cast<GLfloat>(p0.y());
    coordinate[7] = static_cast<GLfloat>(p0.y());

    coordinate[2] = static_cast<GLfloat>(p0.z());
    coordinate[8] = static_cast<GLfloat>(p0.z());

    // p1
    coordinate[3] = static_cast<GLfloat>(p1.x());
    coordinate[12]  = static_cast<GLfloat>(p1.x());

    coordinate[4] = static_cast<GLfloat>(p1.y());
    coordinate[13] = static_cast<GLfloat>(p1.y());

    coordinate[5] = static_cast<GLfloat>(p1.z());
    coordinate[14] = static_cast<GLfloat>(p1.z());

    // p0 + t0 sum
    coordinate[9] = static_cast<GLfloat>(p0.x() + t0.x());
    coordinate[10] = static_cast<GLfloat>(p0.y() + t0.y());
    coordinate[11] = static_cast<GLfloat>(p0.z() + t0.z());

    // p1 + t1 sum
    coordinate[15] = static_cast<GLfloat>(p1.x() + t1.x());
    coordinate[16] = static_cast<GLfloat>(p1.y() + t1.y());
    coordinate[17] = static_cast<GLfloat>(p1.z() + t1.z());

    if (!glUnmapBuffer(GL_ARRAY_BUFFER))
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        DeleteVertexBufferObjectsOfData();
        return GL_FALSE;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::GetCorner(GLuint corner_index, GLdouble &x, GLdouble &y, GLdouble &z)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    x = _data[corner_index].x();
    y = _data[corner_index].y();
    z = _data[corner_index].z();
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::GetCorner(GLuint corner_index, DCoordinate3 &position)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    position = _data[corner_index];
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::GetTangent(GLuint corner_index, GLdouble &t_x, GLdouble &t_y, GLdouble &t_z)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    t_x = _data[corner_index + 2].x();
    t_y = _data[corner_index + 2].y();
    t_z = _data[corner_index + 2].z();
    return GL_TRUE;
}

GLboolean BicubicHermiteArc3::GetTangent(GLuint corner_index, DCoordinate3 &tangent)
{
    if(corner_index > 1 || corner_index < 0)
        return GL_FALSE;

    tangent = _data[corner_index + 2];
    return GL_TRUE;
}
