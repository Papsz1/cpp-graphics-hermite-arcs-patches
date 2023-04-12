#ifndef BICUBICHERMITECOMPOSITESURFACES3_H
#define BICUBICHERMITECOMPOSITESURFACES3_H

#include "../Core/Lights.h"
#include "../Core/Materials.h"
#include "BicubicHermitePatches3.h"
#include <QOpenGLTexture>
#include <iostream>
#include <fstream>

namespace cagd
{
    class BicubicHermiteCompositeSurface3
    {
    public:
        enum Direction{N, NW, W, SW, S, SE, E, NE};

        class PatchAttributes
        {
        public:
            BicubicHermitePatch3            *patch;
            TriangulatedMesh3               *image;
            Material                        *material; // use pointers to pre-defined materials
            QOpenGLTexture                  *texture;  // use pointers to pre-defined textures
            // ShaderProgram       *shader;   // use pointers to pre-defined shader programs

            // other attributes
            // ...

            PatchAttributes     *neighbours[8];
            GLuint              connection_type[8];

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
            PatchAttributes();
            PatchAttributes(const PatchAttributes &a);

            PatchAttributes& operator =(const PatchAttributes &a);
            ~PatchAttributes();
        };
    private:
        //non-composite (0-3), composite (4, 7)
        // 0 - N, 1 - E, 2 - S, 3 - W
        std::vector<std::pair<GLuint, GLuint>> _compass_left =  { {0,0}, {0,1}, {1,1}, {1,0},
                                                                  {0,0}, {0,1}, {1,1}, {1,0} };
        std::vector<std::pair<GLuint, GLuint>> _compass_right = { {0,1}, {1,1}, {1,0}, {0,0},
                                                                  {1,1}, {1,0}, {0,0}, {0, 1} };

        std::vector<std::pair<GLuint, GLuint>> _corner_points = { {0,1}, {1,1}, {0,1}, {0,0} };

        std::vector<std::pair<GLuint, GLuint>> _compass_left_join = { {0,0}, {0,1}, {1,0}, {0,0} };
        std::vector<std::pair<GLuint, GLuint>> _compass_right_join = { {0,1}, {1,1}, {1,1}, {1,0} };

        std::vector<std::pair<GLuint, GLuint>> _compass_left_join_origin = { {1,0}, {0,0}, {0,0}, {0,1} };
        std::vector<std::pair<GLuint, GLuint>> _compass_right_join_origin = { {1,1}, {1,0}, {0,1}, {1,1} };

    protected:
        std::vector<PatchAttributes> _attributes;

    public:
        // special/default ctor
        BicubicHermiteCompositeSurface3(GLuint minimial_patch_count_to_be_reserved = 1000);

        // operations
        GLboolean InsertNewPatch(   GLuint maximum_order_of_derivatives = 2,
                                    GLuint u_div_point_count = 50,
                                    GLuint v_div_point_count = 50,
                                    GLenum usage_flag = GL_STATIC_DRAW,
                                    const BicubicHermitePatch3& a = 0);

        GLboolean RenderAllData();
        GLboolean RenderSelectedData(GLuint index);

        GLboolean RenderAllNormals(GLdouble derivaive_scale);
        GLboolean RenderSelectedNormals(GLuint index, GLdouble derivaive_scale);
        void RenderAllFrames();


        RowMatrix<GenericCurve3*>* GenerateUISO(GLuint index, GLuint iso_line_count,
                                                GLuint maximum_order_of_derivatives,
                                                GLuint div_point_count,
                                                GLenum usage_flag) const;

        RowMatrix<GenericCurve3*>* GenerateVISO(GLuint index, GLuint iso_line_count,
                                                GLuint maximum_order_of_derivatives,
                                                GLuint div_point_count,
                                                GLenum usage_flag = GL_STATIC_DRAW) const;

        DCoordinate3 GetPointCoordinates(GLuint index, GLuint no);
        DCoordinate3 GetUCoordinates(GLuint index, GLuint no);
        DCoordinate3 GetVCoordinates(GLuint index, GLuint no);
        DCoordinate3 GetTCoordinates(GLuint index, GLuint no);

        int GetSize();

        void UpdatePatches(GLuint index);
        void SetPointCoordinates(GLuint index, GLuint no, DCoordinate3 point);
        void SetUCoordinates(GLuint index, GLuint no, DCoordinate3 point);
        void SetVCoordinates(GLuint index, GLuint no, DCoordinate3 point);
        void SetTCoordinates(GLuint index, GLuint no, DCoordinate3 point);

        GLboolean DeleteExistingPatch(GLuint index);
        GLboolean ContinueExistingPatch(GLuint index, GLuint direction);
        GLboolean JoinExistingPatches(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1);
        GLboolean MergeExistingPatches(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1);

        GLboolean RenderAllPatches(GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const;

        void RotateMatrixClockwise(BicubicHermitePatch3 &patch, GLuint count);
        void RotateMatrixNotClockwise(BicubicHermitePatch3 &patch, GLuint count);

        void readFromFile()
        {
            std::ifstream fin;

            fin.open("Project/patches.txt");

            if (!fin.is_open())
            {
                return;
            }

            GLuint count;
            fin >> count;

            this->_attributes.resize(count);

            DCoordinate3 tmp;
            for (GLuint k = 0; k < count; ++k)
            {
                this->_attributes[k].patch = new BicubicHermitePatch3();

                for (GLuint i = 0; i < 4; ++i)
                {
                    for (GLuint j = 0; j < 4; ++j)
                    {
                        fin >> tmp;
                        this->_attributes[k].patch->SetMatrixValue(i, j, tmp);
                    }
                    std::cout << std::endl;
                }
            }
        }

        void writeToFile()
        {
            std::ofstream fout;

            fout.open("Project/patches.txt");

            if (!fout.is_open())
            {
                return;
            }


            GLuint count = this->_attributes.size();
            fout << count << std::endl;

            for (GLuint k = 0; k < count; ++k)
            {
                for (GLuint i = 0; i < 4; ++i)
                {
                    for (GLuint j = 0; j < 4; ++j)
                    {
                        fout << this->_attributes[k].patch->GetMatrixValue(i, j) << " ";
                    }
                }

                fout << std::endl;
            }
        }
    };
}

#endif // BICUBICHERMITECOMPOSITESURFACES3_H
