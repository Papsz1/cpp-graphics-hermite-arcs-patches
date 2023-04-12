#pragma once

#include <GL/glew.h>
#include <QOpenGLTexture>
#include <QTimer>
#include <QOpenGLWidget>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include "../Core/Lights.h"
#include "../Core/Materials.h"
#include "../Core/TriangulatedMeshes3.h"
#include "../Parametric/ParametricCurves3.h"
#include "../Parametric/ParametricSurfaces3.h"
#include "../Cyclic/CyclicCurves3.h"
#include "../Core/ShaderPrograms.h"
#include "Core/Matrices.h"
#include "../BicubicHermite/BicubicHermiteArc3.h"
#include "../BicubicHermite/BicubicHermitePatches3.h"
#include "../BicubicHermite/BicubicHermiteCompositeCurves.h"
#include "../BicubicHermite/BicubicHermiteCompositeSurfaces3.h"

namespace cagd
{
    class GLWidget: public QOpenGLWidget
    {
        Q_OBJECT

    private:
        int _current_tab;

        // variables defining the projection matrix
        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        double      _derivatives_scale;
        bool        _parametric_first_derivatives;
        bool        _parametric_second_derivatives;
        int         _selected_material;


        // your other declarations

//        QTimer *_timer;



        bool                _apply_texture;
        bool                _apply_material;
        int                 _selected_texture;

        QOpenGLTexture *texture[20];
        Material _materials[7];
        DirectionalLight *_dl = nullptr;
//        DCoordinate3 _normal[3];

        RowMatrix<ShaderProgram>    _shaders;
        GLdouble                    _scale_parameter;
        GLdouble                    _smoothing_parameter;
        GLdouble                    _shading_parameter;
        GLint                       _selected_shader;
        GLdouble                    _red;
        GLdouble                    _green;
        GLdouble                    _blue;

        // project
        GLuint  index1;
        GLuint  index2;
        GLuint  index1_direction;
        GLuint  index2_direction;
        GLboolean _paint_all_arcs=true;
        int         _selected_point;
        GLuint _index_patch1 = 0;
        GLuint _index_patch2 = 0;
        GLuint _direction_patch1 = 0;
        GLuint _direction_patch2 = 0;
        bool _show_uip;
        bool _show_vip;
        bool _show_normals;
        RowMatrix<GenericCurve3*>* _patch_uip;
        RowMatrix<GenericCurve3*>* _patch_vip;
        GLboolean _paint_all_patches= true;
        GLuint selected_arc_point = 0;

        BicubicHermiteCompositeCurve3 *_project_arc = new BicubicHermiteCompositeCurve3();
        BicubicHermiteCompositeSurface3 *_project_patch = new BicubicHermiteCompositeSurface3();

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);


        void enableShaders();
        void disableShaders();
        void initializeShaders();
        void initializeTextures();

        virtual ~GLWidget();

        void writePatchToFile();
        void readPatchFromFile();

        void writeArcToFile();
        void readArcFromFile();

    public slots:
        // public event handling methods/slots
        void set_tab(int value);
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        void set_derivatives_scale(int value);

        void set_parametric_first_derivatives(bool value);
        void set_parametric_second_derivatives(bool value);

        void set_texture(bool value);
        void set_texture_type(int value);

        void set_material(bool value);
        void set_material_type(int value);

        void set_red(double value);
        void set_blue(double value);
        void set_green(double value);
        void set_selected_shader(int);
        void set_shader_scale(double);
        void set_smooting_shader(double);
        void set_shader_parameter(double);

        void show_patch_uip(bool value);
        void show_patch_vip(bool value);

        // project arc
        void insert_new_arc(bool value);
        void set_index_arc1(int value);
        void set_index_arc2(int value);
        void continue_arc(bool value);
        void delete_arc(bool value);
        void merge_arcs(bool value);
        void set_direction_arc1(int value);
        void set_direction_arc2(int value);
        void join_arcs(bool value);
        void set_paint_selected_arc(bool value);
        void set_paint_all_arcs(bool value);

        // project patch
        void continue_patch(bool);
        void insert_new_patch(bool);
        void set_index_patch1(int value);
        void set_index_patch2(int value);
        void set_direction_patch1(int value);
        void set_direction_patch2(int value);

        void join_patches(bool value);
        void set_paint_selected_patch(bool value);
        void set_paint_all_patches(bool value);
        void merge_patches(bool);
        void show_normals(bool);
        void delete_patch(bool value);

        void setHermitePatchPointX(double value);
        void setHermitePatchPointY(double value);
        void setHermitePatchPointZ(double value);
        void setHermitePatchPointUX(double value);
        void setHermitePatchPointUY(double value);
        void setHermitePatchPointUZ(double value);
        void setHermitePatchPointVX(double value);
        void setHermitePatchPointVY(double value);
        void setHermitePatchPointVZ(double value);
        void setHermitePatchPointTX(double value);
        void setHermitePatchPointTY(double value);
        void setHermitePatchPointTZ(double value);
        void setSelectedPoint(int value);

        void setHermiteArcPointX(double value);
        void setHermiteArcPointY(double value);
        void setHermiteArcPointZ(double value);
        void setHermiteArcTangentPointX(double value);
        void setHermiteArcTangentPointY(double value);
        void setHermiteArcTangentPointZ(double value);
        void setSelectedPointArc(int value);

    signals:
        void set_parametric_first_derivatives_slot(bool value);
        void set_parametric_second_derivatives_slot(bool value);

        void set_cyclic_point_x_signal(double value);
        void set_cyclic_point_y_signal(double value);
        void set_cyclic_point_z_signal(double value);

        void HermitePatchPointChangeX(double value);
        void HermitePatchPointChangeY(double value);
        void HermitePatchPointChangeZ(double value);
        void HermitePatchPointChangeUX(double value);
        void HermitePatchPointChangeUY(double value);
        void HermitePatchPointChangeUZ(double value);
        void HermitePatchPointChangeVX(double value);
        void HermitePatchPointChangeVY(double value);
        void HermitePatchPointChangeVZ(double value);
        void HermitePatchPointChangeTX(double value);
        void HermitePatchPointChangeTY(double value);
        void HermitePatchPointChangeTZ(double value);

        void HermiteArcPointChangeX(double value);
        void HermiteArcPointChangeY(double value);
        void HermiteArcPointChangeZ(double value);
        void HermiteArcTangentChangeX(double value);
        void HermiteArcTangentChangeY(double value);
        void HermiteArcTangentChangeZ(double value);
    };
}
