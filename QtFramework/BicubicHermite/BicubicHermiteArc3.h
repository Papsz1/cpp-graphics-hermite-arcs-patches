#ifndef BICUBICHERMITEARCS3_H
#define BICUBICHERMITEARCS3_H

#include "../Core/DCoordinates3.h"
#include "../Core/Constants.h"
#include "../Core/LinearCombination3.h"

namespace cagd
{
    class BicubicHermiteArc3: public LinearCombination3
    {
    public:
        // Ez a _data[4] mar az ososztalyban letre van hozva
        // DCoordinate3 _data[4];

        // special/default constructor
        BicubicHermiteArc3(GLenum data_usage_flag = GL_STATIC_DRAW);
        BicubicHermiteArc3(const BicubicHermiteArc3 &a);

        // inherited pure virtual methods have to be redeclared and defined
        GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const;
        GLboolean CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives& d) const;

        // project-dependent setters/getters, e.g.,
    
        // in the case of Hermite projects, one can also introduce the following (more intuitively named) methods (corner_index ∈ {0,1})
        /*
            _data[0] _data[1]  p0, and p1 Dcoords
            _data[2] _data[3]  t0, and t1, p0's tangent and p1's tangent
        */

        // Setter
        GLboolean SetCorner(GLuint corner_index, GLdouble x, GLdouble y, GLdouble z);
        GLboolean SetCorner(GLuint corner_index, const DCoordinate3 &position);

        GLboolean SetTangent(GLuint corner_index, GLdouble t_x, GLdouble t_y, GLdouble t_z);
        GLboolean SetTangent(GLuint corner_index, const DCoordinate3 &tangent);

        // Getter
        GLboolean GetCorner(GLuint corner_index, GLdouble &x, GLdouble &y, GLdouble &z);
        GLboolean GetCorner(GLuint corner_index, DCoordinate3 &position);

        GLboolean GetTangent(GLuint corner_index, GLdouble &t_x, GLdouble &t_y, GLdouble &t_z);
        GLboolean GetTangent(GLuint corner_index, DCoordinate3 &tangent);

        DCoordinate3 GetVectorElement(GLuint no)
        {
            if (no > 4)
             return DCoordinate3();

            return _data[no];
        }

        GLboolean SetVectorElement(GLuint no, const DCoordinate3 &c)
        {
             if (no > 4)
                 return GL_FALSE;

            _data[no] = c;
            return GL_TRUE;
        }

        // ...
        GLboolean RenderData(GLenum render_mode = GL_LINE_STRIP) const;
        GLboolean UpdateVertexBufferObjectsOfData(GLenum usage_flag = GL_STATIC_DRAW);
    };
}

#endif // BICUBICHERMITEARCS3_H
