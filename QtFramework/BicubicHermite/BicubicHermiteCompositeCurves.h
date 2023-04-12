
#ifndef BICUBICHERMITECOMPOSITECURVES3_H
#define BICUBICHERMITECOMPOSITECURVES3_H

#include "../Core/Colors4.h"
#include "BicubicHermiteArc3.h"
#include <fstream>

namespace cagd
{
    class BicubicHermiteCompositeCurve3
    {
    public:
        enum Direction{LEFT, RIGHT};
        // Errol meg beszelunk
        BicubicHermiteArc3 *_default_arc = new BicubicHermiteArc3();

        class ArcAttributes
        {
        public:
            BicubicHermiteArc3          *arc;
            GenericCurve3               *image;
            Color4                      *color;

            // use pointers to pre-defined colors, e.g., Color4 *color = &red;
            // other arc attributes
            // ...
            
            ArcAttributes   *previous, *next; // pointers to neighboring arc attributes
            GLuint       previous_connection_type, next_connection_type;

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
            ArcAttributes();
            ArcAttributes(const ArcAttributes &a);
            // ArcAttributes(BicubicHermiteArc3 *Arc, GenericCurve3 *Image, Color4 *Color, ArcAttributes *Previous, ArcAttributes *Next);

            ArcAttributes& operator =(const ArcAttributes &a);
            ~ArcAttributes();
        };

    protected:
        std::vector<ArcAttributes> _attributes;          // sequence of arc attributes
        // please help me im under the water gulugulugulu
    public:
        // special/default ctor
        BicubicHermiteCompositeCurve3(GLuint minimal_arc_count_to_be_reserved = 1000);
        BicubicHermiteCompositeCurve3(BicubicHermiteCompositeCurve3 &bhcc);

//        GLboolean  (...);
        void UpdateArcs(GLuint index);
        void SetPointCoordinates(GLuint index, GLuint no, DCoordinate3 point);
        void SetTangentCoordinates(GLuint index, GLuint no, DCoordinate3 point);
        DCoordinate3 GetPointCoordinates(GLuint index, GLuint no);
        DCoordinate3 GetTangentCoordinates(GLuint index, GLuint no);

        GLboolean SetDerivativeScale(GLuint index, GLdouble res);
        GLboolean DeleteExistingArc(GLuint index);
        GLboolean ContinueExisitingArc(GLuint index, GLuint direction);
        GLboolean JoinExistingArcs(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1);
        GLboolean MergeExistingArcs(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1);
        GLboolean InsertNewArc(     GLuint maximum_order_of_derivatives = 2,
                                    GLuint point_count = 0,
                                    GLenum usage_flag = GL_STATIC_DRAW,
                                    const DCoordinate3 corner1 = DCoordinate3(), const DCoordinate3 corner2 = DCoordinate3(), 
                                    const DCoordinate3 tangent1 = DCoordinate3(), const DCoordinate3 tangent2 = DCoordinate3());
        
        GLboolean RenderAllArcs(GLuint order, GLenum render_mode);
        GLboolean RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const;
        
        // other setters and getters
        // ...

        void readFromFile()
        {
            std::ifstream fin;

            fin.open("Project/arcs.txt");

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
                this->_attributes[k].arc = new BicubicHermiteArc3();

                for (GLuint i = 0; i < 4; ++i)
                {
                    fin >> tmp;
                    this->_attributes[k].arc->SetVectorElement(i, tmp);
                }
            }
        }

        void writeToFile()
        {
            std::ofstream fout;

            fout.open("Project/arcs.txt");

            if (!fout.is_open())
            {
                return;
            }


            GLuint count = this->_attributes.size();
            fout << count << std::endl;

            for (GLuint k = 0; k < count; ++k)
            {
                for (GLuint i = 0; i < 4; ++i)
                    fout << this->_attributes[k].arc->GetVectorElement(i) << " ";
                fout << std::endl;
            }
        }
    };
}

#endif // BICUBICHERMITECOMPOSITECURVES3_H

 
