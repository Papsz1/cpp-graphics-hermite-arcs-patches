#include <QTimer>
#include "../Core/DCoordinates3.h"
#include "../Cyclic/CyclicCurves3.h"
#include "GLWidget.h"
#include "../Core/Materials.h"
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"
#include "../Core/Exceptions.h"
#include "../Core/Constants.h"
#include <new>
#include <string>

#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include <fstream>
#include <iostream>
using namespace std;


namespace cagd
{
    GLWidget::~GLWidget()
    {
        if(_dl)
        {
            delete _dl;
            _dl = nullptr;
        }
    }

    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
    {
        _current_tab = 1;
        _derivatives_scale = 1.0;

        _parametric_first_derivatives = false;
        _parametric_second_derivatives = false;

        _selected_material = 0;
        _apply_material = false;

        _selected_texture = 0;
        _apply_texture = false;

        _materials[0] = MatFBBrass;
        _materials[1] = MatFBGold;
        _materials[2] = MatFBSilver;
        _materials[3] = MatFBEmerald;
        _materials[4] = MatFBPearl;
        _materials[5] = MatFBRuby;
        _materials[6] = MatFBTurquoise;

        _red = 1.0;
        _blue = 1.0;
        _green = 1.0;
        _selected_point = 0;
        _scale_parameter = 10.0f;
        _smoothing_parameter = 1.0f;
        _shading_parameter = 100.0f;
        _selected_shader = 0;

        _show_uip = false;
        _show_vip = false;
        _show_normals = false;

        index1 = 0;
        index2 = 0;
        index1_direction = 0;
        index2_direction = 0;
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(width()) / static_cast<double>(height());
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...

            initializeTextures();

            initializeShaders();

//            readArcFromFile();
//            readPatchFromFile();

            HCoordinate3    direction(0.0, 0.0, 1.0, 0.0);
            Color4          ambient(0.4, 0.4, 0.4, 1.0);
            Color4          diffuse(0.8, 0.8, 0.8, 1.0);
            Color4          specular(1.0, 1.0, 1.0, 1.0);

            _dl = new (nothrow) DirectionalLight(GL_LIGHT0, direction, ambient, diffuse, specular);
            if (!_dl)
            {
                throw("Exception: Could Not Create The Directional Light!");
            }

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

            glEnable(GL_DEPTH_TEST);
        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

            switch(_current_tab) 
            {  
                case 0:
                if (_paint_all_arcs)
                {
                    glColor3f(1.0f, 1.0f, 1.0f);
                    _project_arc->RenderAllArcs(0, GL_LINE_STRIP);
                }
                else
                {
                    glColor3f(1.0f, 1.0f, 1.0f);
                    _project_arc->RenderSelectedArc(index1, 0, GL_LINE_STRIP);

                }
                if (_parametric_first_derivatives)
                {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    _project_arc->RenderSelectedArc(index1, 1, GL_LINES);
                }

                if (_parametric_second_derivatives)
                {
                    glColor3f(0.0f, 0.0f, 1.0f);
                    _project_arc->RenderSelectedArc(index1, 2, GL_LINES);
                }
                    break;
                case 1:
//                writePatchToFile();

                enableShaders();
                glEnable(GL_LIGHTING);
                glEnable(GL_NORMALIZE);
                _dl->Enable();

                if (_paint_all_patches)
                {
                    _materials[_selected_material].Apply();
                    _project_patch->RenderAllPatches(0, GL_LINE_STRIP);

//                    _materials[0].Apply();
//                    _project_patch->RenderSelectedPatch(_index_patch1, 0, GL_LINE_STRIP);
                }
                else
                {
                    _materials[1].Apply();
                    _project_patch->RenderSelectedPatch(_index_patch1, 0, GL_LINE_STRIP);
                }

                glDisable(GL_LIGHTING);
                glDisable(GL_NORMALIZE);
                _dl->Disable();
                disableShaders();

//                _project_patch->RenderAllFrames();


//                glColor3d(1.0, 0.8, 0.0);
//                _project_patch->RenderAllData();
                if (_show_normals)
                {
                    glColor3f(1.0f, 0.20f, 0.33f);
                    _project_patch->RenderAllNormals(_derivatives_scale);
                }

//                if (_apply_texture)
//                    texture[_selected_texture]->bind();
//                else
//                    texture[_selected_texture]->release();


                if (_paint_all_patches)
                {
                    _project_patch->RenderAllData();
                    if (_show_normals)
                    {
                        glColor3f(1.0f, 0.20f, 0.33f);
                        _project_patch->RenderAllNormals(_derivatives_scale);
                    }

                    glColor3f(1.0f, 0.0f, 0.0f);
                    if(_show_uip)
                    {
                        for (GLuint i = 0; i < _patch_uip->GetColumnCount(); i++)
                        {
                            GenericCurve3 *curve = (*_patch_uip)[i];
                            if (curve) {
                                curve->UpdateVertexBufferObjects(_derivatives_scale);
                                curve->RenderDerivatives(0,  GL_LINE_STRIP);
                                curve->RenderDerivatives(1,  GL_LINES);
//                                curve->RenderDerivatives(2,  GL_LINES);
                            }
                        }
                    }
                    glColor3f(0.0f, 0.5f, 0.0f);
                    if(_show_vip) {
                        for (GLuint i = 0; i < _patch_vip->GetColumnCount(); i++)
                        {
                            GenericCurve3 *curve = (*_patch_vip)[i];
                            if (curve) {
                                curve->UpdateVertexBufferObjects(_derivatives_scale);
                                curve->RenderDerivatives(0,  GL_LINE_STRIP);
                                curve->RenderDerivatives(1,  GL_LINES);
//                                curve->RenderDerivatives(2,  GL_LINES);
                            }
                        }
                    }

                }
                else
                {
                    _project_patch->RenderSelectedData(_index_patch1);
                    if (_show_normals)
                        _project_patch->RenderSelectedNormals(_index_patch1, _derivatives_scale);
                }

                break;
            }

        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored



        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(w) / static_cast<double>(h);

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        update();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            update();
        }
    }


    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            update();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            update();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            update();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            update();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            update();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            update();
        }
    }

    void GLWidget::set_derivatives_scale(int value)
    {
        double res = (double) value / 100.0;
        if (_derivatives_scale != res)
        {
            _derivatives_scale = res;
            double res = (double) value / 100.0;
            _project_arc->SetDerivativeScale(index1, res);

            // _image_of_cyclic_curve[_selected_cyclic_curve]->UpdateVertexBufferObjects(_derivatives_scale);
            update();
        }
    }

    void GLWidget::set_parametric_first_derivatives(bool value)
    {
        if (_parametric_first_derivatives != value)
        {
            _parametric_first_derivatives = value;
            update();
        }
    }

    void GLWidget::set_parametric_second_derivatives(bool value)
    {
        if (_parametric_second_derivatives != value)
        {
            _parametric_second_derivatives = value;
            update();
        }
    }

    void GLWidget::set_tab(int value)
    {
        _current_tab = value;
        update();
    }

    void GLWidget::initializeTextures()
    {
        texture[0] = new QOpenGLTexture(QImage("Textures/texture_01.jpg").mirrored());
        texture[0]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[0]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[1] = new QOpenGLTexture(QImage("Textures/texture_02.jpg").mirrored());
        texture[1]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[1]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[2] = new QOpenGLTexture(QImage("Textures/texture_02.jpg").mirrored());
        texture[2]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[2]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[3] = new QOpenGLTexture(QImage("Textures/texture_03.jpg").mirrored());
        texture[3]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[3]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[4] = new QOpenGLTexture(QImage("Textures/texture_04.jpg").mirrored());
        texture[4]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[4]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[5] = new QOpenGLTexture(QImage("Textures/texture_05.jpg").mirrored());
        texture[5]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[5]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[6] = new QOpenGLTexture(QImage("Textures/texture_06.jpg").mirrored());
        texture[6]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[6]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[7] = new QOpenGLTexture(QImage("Textures/texture_07.jpg").mirrored());
        texture[7]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[7]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[8] = new QOpenGLTexture(QImage("Textures/texture_08.jpg").mirrored());
        texture[8]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[8]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[9] = new QOpenGLTexture(QImage("Textures/texture_09.jpg").mirrored());
        texture[9]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[9]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[10] = new QOpenGLTexture(QImage("Textures/texture_10.jpg").mirrored());
        texture[10]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[10]->setMagnificationFilter(QOpenGLTexture::Linear);

        texture[11] = new QOpenGLTexture(QImage("Textures/texture_11.jpg").mirrored());
        texture[11]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[11]->setMagnificationFilter(QOpenGLTexture::Linear);
        
        texture[12] = new QOpenGLTexture(QImage("Textures/texture_12.jpg").mirrored());
        texture[12]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[12]->setMagnificationFilter(QOpenGLTexture::Linear);
        
        texture[13] = new QOpenGLTexture(QImage("Textures/texture_13.jpg").mirrored());
        texture[13]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture[13]->setMagnificationFilter(QOpenGLTexture::Linear);        
    }

    void GLWidget::set_texture(bool value)
    {
        if(_apply_texture != value)
        {
            _apply_texture = value;
            update();
        }
    }

    void GLWidget::set_texture_type(int value)
    {
        if(_selected_texture != value)
        {
            _selected_texture = value;
            update();
        }
    }

    void GLWidget::set_material(bool value)
    {
        if(_apply_material != value)
        {
            _apply_material = value;
            update();
        }
    }

    void GLWidget::set_material_type(int value)
    {
        if(_selected_material != value)
        {
            _selected_material = value;
            update();
        }

    }

    void GLWidget::enableShaders() 
    {
        _shaders[_selected_shader].Enable();
    }

    void GLWidget::disableShaders() 
    {
        _shaders[_selected_shader].Disable();
    }

    void GLWidget::initializeShaders() 
    {
        try {
            _shaders.ResizeColumns(4);
            if (!_shaders[0].InstallShaders("Shaders/directional_light.vert","Shaders/directional_light.frag"))
            {
                throw Exception("Directional light creation error");
            }

            if (!_shaders[1].InstallShaders("Shaders/two_sided_lighting.vert","Shaders/two_sided_lighting.frag"))
            {
                throw Exception("Two sided lighting creation error");
            }

            if (!_shaders[2].InstallShaders("Shaders/toon.vert","Shaders/toon.frag"))
            {
                throw Exception("Toon creation error.");
            }
            else
            {
                _shaders[2].Enable();
                _shaders[2].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
                _shaders[2].Disable();
            }

            if (!_shaders[3].InstallShaders("Shaders/reflection_lines.vert","Shaders/reflection_lines.frag"))
            {
                throw Exception("Reflection lines creation error");
            } else {
                _shaders[3].Enable();
                _shaders[3].SetUniformVariable1f("scale_factor", _scale_parameter);
                _shaders[3].SetUniformVariable1f("smoothing", _smoothing_parameter);
                _shaders[3].SetUniformVariable1f("shading", _shading_parameter);
                _shaders[3].Disable();
            }

        }
        catch (Exception& e)
        {
            std::cout << e << endl;
        }
    }

    void GLWidget::set_selected_shader(int value)
    {
        if(_selected_shader != value)
        {
            _selected_shader = value;
            update();
        }
    }

    void GLWidget::set_shader_scale(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_scale_parameter != value)
        {
            _scale_parameter = value;

            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }

            {
                _shaders[_selected_shader].SetUniformVariable1f("scale_factor", _scale_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("smoothing", _smoothing_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("shading", _shading_parameter);
            }
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::set_shader_parameter(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_shading_parameter != value) {
            _shading_parameter = value;

            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }
                _shaders[_selected_shader].SetUniformVariable1f("scale_factor", _scale_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("smoothing", _smoothing_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("shading", _shading_parameter);

            _shaders[_selected_shader].Disable();
            update();
        }

    }

    void GLWidget::set_smooting_shader(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_smoothing_parameter != value) {
            _smoothing_parameter = value;

            // Szinek
            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }

            if(_selected_shader == 3)
            {
                _shaders[_selected_shader].SetUniformVariable1f("scale_factor", _scale_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("smoothing", _smoothing_parameter);
                _shaders[_selected_shader].SetUniformVariable1f("shading", _shading_parameter);
            }
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::set_red(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_red != value)
        {
            _red = value;
//            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::set_blue(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_blue != value)
        {
            _blue = value;
//            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::set_green(double value)
    {
        _shaders[_selected_shader].Enable();
        if(_green != value)
        {
            _green = value;
//            if(_selected_shader == 2)
            {
                _shaders[_selected_shader].SetUniformVariable4f("default_outline_color", _red, _green, _blue, 1.0f);
            }
            _shaders[_selected_shader].Disable();
            update();
        }
    }

    void GLWidget::show_patch_uip(bool value)
    {
        _patch_uip = _project_patch->GenerateUISO(_index_patch1, 30, 2, 100, GL_STATIC_DRAW);

         if(_show_uip == value) return;
         _show_uip = value;
         if (!_show_uip) {update(); return;}

         if (_patch_uip) {
             for (GLuint i = 0; i < _patch_uip->GetColumnCount(); i++) {
                 GenericCurve3 *curve = (*_patch_uip)[i];
                 if (curve) {
                     curve->DeleteVertexBufferObjects();
                 }
             }
         }

         if (!_patch_uip) return;

         for (GLuint i = 0; i < _patch_uip->GetColumnCount(); i++) {
            GenericCurve3 *curve = (*_patch_uip)[i];
            if (curve) {
                curve->UpdateVertexBufferObjects();
            }
         }
         update();
    }

    void GLWidget::show_patch_vip(bool value)
    {
        _patch_vip = _project_patch->GenerateVISO(_index_patch1, 30, 2, 100, GL_STATIC_DRAW);

         if(_show_vip == value) return;
         _show_vip = value;
         if (!_show_vip) {update(); return;}

         if (_patch_vip) {
             for (GLuint i = 0; i < _patch_vip->GetColumnCount(); i++) {
                GenericCurve3 *curve = (*_patch_vip)[i];
                if (curve) {
                    curve->DeleteVertexBufferObjects();
                }
             }
         }

         if (!_patch_vip) return;

         for (GLuint i = 0; i < _patch_vip->GetColumnCount(); i++) {
            GenericCurve3 *curve = (*_patch_vip)[i];
            if (curve) {
                curve->UpdateVertexBufferObjects();
            }
         }
         update();
    }


    void GLWidget::insert_new_arc(bool value)
    {
        _project_arc->InsertNewArc(2, 200, GL_STATIC_DRAW);

        update();
    }

    void GLWidget::set_index_arc2(int value)
    {
        if(value != index2)
            index2 = value;
        update();
    }

    void GLWidget::continue_arc(bool value)
    {
        _project_arc->ContinueExisitingArc(index1, index1_direction);

        update();
    }

    void GLWidget::delete_arc(bool value)
    {
        _project_arc->DeleteExistingArc(index1);

        update();
    }

    void GLWidget::merge_arcs(bool value)
    {
        _project_arc->MergeExistingArcs(index1, index1_direction, index2, index2_direction);

        update();
    }

    void GLWidget::set_direction_arc1(int value)
    {
        if (value != index1_direction)
            index1_direction = value;
        update();
    }

    void GLWidget::set_direction_arc2(int value)
    {
        if (value != index2_direction)
            index2_direction = value;
        update();
    }

    void GLWidget::join_arcs(bool value)
    {
        _project_arc->JoinExistingArcs(index1, index1_direction, index2, index2_direction);
        update();
    }

    void GLWidget::set_paint_selected_arc(bool value)
    {
        _paint_all_arcs = false;
        update();
    }

    void GLWidget::set_paint_all_arcs(bool value)
    {
        _paint_all_arcs = true;
        update();
    }

    void GLWidget::insert_new_patch(bool)
    {
        _project_patch->InsertNewPatch();
        update();
    }

    void GLWidget::set_index_patch2(int value){
        _index_patch2 = value;
        update();
    }
    void GLWidget::set_direction_patch1(int value){
        _direction_patch1 = value;
        update();
    }
    void GLWidget::set_direction_patch2(int value){
        _direction_patch2 = value;
        update();
    }
    void GLWidget::continue_patch(bool value) {
        _project_patch->ContinueExistingPatch(_index_patch1, _direction_patch1);
        update();
    }

    void GLWidget::join_patches(bool value)
    {
        _project_patch->JoinExistingPatches(_index_patch1, _direction_patch1, _index_patch2, _direction_patch2);
        update();
    }

    void GLWidget::set_paint_selected_patch(bool value)
    {
        _paint_all_patches = false;
        update();
    }

    void GLWidget::set_paint_all_patches(bool value)
    {
        _paint_all_patches = true;
        update();
    }

    void GLWidget::merge_patches(bool value)
    {
        _project_patch->MergeExistingPatches(_index_patch1, _direction_patch1, _index_patch2, _direction_patch2);
        update();
    }

    void GLWidget::show_normals(bool value)
    {
        if (value != _show_normals)
        {
            _show_normals = value;
            update();
        }
    }

    void GLWidget::delete_patch(bool value)
    {
        _project_patch->DeleteExistingPatch(_index_patch1);
        update();
    }

    void GLWidget::setSelectedPoint(int value)
    {
        _selected_point = value;
        DCoordinate3 point = _project_patch->GetPointCoordinates(_index_patch1, _selected_point);
        DCoordinate3 U = _project_patch->GetUCoordinates(_index_patch1, _selected_point);
        DCoordinate3 V = _project_patch->GetVCoordinates(_index_patch1, _selected_point);
        DCoordinate3 T = _project_patch->GetTCoordinates(_index_patch1, _selected_point);
        emit HermitePatchPointChangeX(point.x());
        emit HermitePatchPointChangeY(point.y());
        emit HermitePatchPointChangeZ(point.z());

        emit HermitePatchPointChangeVX(V.x());
        emit HermitePatchPointChangeVY(V.y());
        emit HermitePatchPointChangeVZ(V.z());

        emit HermitePatchPointChangeUX(U.x());
        emit HermitePatchPointChangeUY(U.y());
        emit HermitePatchPointChangeUZ(U.z());

        emit HermitePatchPointChangeTX(T.x());
        emit HermitePatchPointChangeTY(T.y());
        emit HermitePatchPointChangeTZ(T.z());
    }

    void GLWidget::set_index_patch1(int value){
        if(value >= _project_patch->GetSize()) {
            return;
        }
        _index_patch1 = value;
        DCoordinate3 point = _project_patch->GetPointCoordinates(_index_patch1, _selected_point);
        DCoordinate3 U = _project_patch->GetUCoordinates(_index_patch1, _selected_point);
        DCoordinate3 V = _project_patch->GetVCoordinates(_index_patch1, _selected_point);
        DCoordinate3 T = _project_patch->GetTCoordinates(_index_patch1, _selected_point);
        emit HermitePatchPointChangeX(point.x());
        emit HermitePatchPointChangeY(point.y());
        emit HermitePatchPointChangeZ(point.z());

        emit HermitePatchPointChangeVX(V.x());
        emit HermitePatchPointChangeVY(V.y());
        emit HermitePatchPointChangeVZ(V.z());

        emit HermitePatchPointChangeUX(U.x());
        emit HermitePatchPointChangeUY(U.y());
        emit HermitePatchPointChangeUZ(U.z());

        emit HermitePatchPointChangeTX(T.x());
        emit HermitePatchPointChangeTY(T.y());
        emit HermitePatchPointChangeTZ(T.z());
    }

    void GLWidget::setHermitePatchPointX(double value) {
        DCoordinate3 point = _project_patch->GetPointCoordinates(_index_patch1, _selected_point);

        point.x() = value;
        _project_patch->SetPointCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointY(double value) {
        DCoordinate3 point = _project_patch->GetPointCoordinates(_index_patch1, _selected_point);
        point.y() = value;
        _project_patch->SetPointCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointZ(double value) {
        DCoordinate3 point = _project_patch->GetPointCoordinates(_index_patch1, _selected_point);
        point.z() = value;
        _project_patch->SetPointCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }


    void GLWidget::setHermitePatchPointVX(double value) {
        DCoordinate3 point = _project_patch->GetVCoordinates(_index_patch1, _selected_point);
        point.x() = value;
        _project_patch->SetVCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointVY(double value) {
        DCoordinate3 point = _project_patch->GetVCoordinates(_index_patch1, _selected_point);
        point.y() = value;
        _project_patch->SetVCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointVZ(double value) {
        DCoordinate3 point = _project_patch->GetVCoordinates(_index_patch1, _selected_point);
        point.z() = value;
        _project_patch->SetVCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }


    void GLWidget::setHermitePatchPointUX(double value) {
        DCoordinate3 point = _project_patch->GetUCoordinates(_index_patch1, _selected_point);
        point.x() = value;
        _project_patch->SetUCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointUY(double value) {
        DCoordinate3 point = _project_patch->GetUCoordinates(_index_patch1, _selected_point);
        point.y() = value;
        _project_patch->SetUCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointUZ(double value) {
        DCoordinate3 point = _project_patch->GetUCoordinates(_index_patch1, _selected_point);
        point.z() = value;
        _project_patch->SetUCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointTX(double value) {
        DCoordinate3 point = _project_patch->GetTCoordinates(_index_patch1, _selected_point);
        point.x() = value;
        _project_patch->SetTCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointTY(double value) {
        DCoordinate3 point = _project_patch->GetTCoordinates(_index_patch1, _selected_point);
        point.y() = value;
        _project_patch->SetTCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setHermitePatchPointTZ(double value) {
        DCoordinate3 point = _project_patch->GetTCoordinates(_index_patch1, _selected_point);
        point.z() = value;
        _project_patch->SetTCoordinates(_index_patch1, _selected_point, point);
        _project_patch->UpdatePatches(_index_patch1);
        update();
    }

    void GLWidget::setSelectedPointArc(int value) {
        if (selected_arc_point != value)
        {
            selected_arc_point = value;

            DCoordinate3 point = _project_arc->GetPointCoordinates(index1, selected_arc_point);
            DCoordinate3 T = _project_arc->GetTangentCoordinates(index1, selected_arc_point);

            emit HermiteArcPointChangeX(point.x());
            emit HermiteArcPointChangeY(point.y());
            emit HermiteArcPointChangeZ(point.z());

            emit HermiteArcTangentChangeX(T.x());
            emit HermiteArcTangentChangeY(T.y());
            emit HermiteArcTangentChangeZ(T.z());
        }
    }

    void GLWidget::set_index_arc1(int value)
    {
        if (index1 != value)
        {
            index1 = value;

            DCoordinate3 point = _project_arc->GetPointCoordinates(index1, selected_arc_point);
            DCoordinate3 T = _project_arc->GetTangentCoordinates(index1, selected_arc_point);

            emit HermiteArcPointChangeX(point.x());
            emit HermiteArcPointChangeY(point.y());
            emit HermiteArcPointChangeZ(point.z());

            emit HermiteArcTangentChangeX(T.x());
            emit HermiteArcTangentChangeY(T.y());
            emit HermiteArcTangentChangeZ(T.z());
        }
    }

    void GLWidget::setHermiteArcPointX(double value) {
        DCoordinate3 point = _project_arc->GetPointCoordinates(index1, selected_arc_point);
        if(value != point.x())
        {
            point.x() = value;
            _project_arc->SetPointCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }
    void GLWidget::setHermiteArcPointY(double value) {
        DCoordinate3 point = _project_arc->GetPointCoordinates(index1, selected_arc_point);
        if (value != point.y())
        {
            point.y() = value;
            _project_arc->SetPointCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }
    void GLWidget::setHermiteArcPointZ(double value) {
        DCoordinate3 point = _project_arc->GetPointCoordinates(index1, selected_arc_point);
        if (value != point.z())
        {
            point.z() = value;
            _project_arc->SetPointCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }
    void GLWidget::setHermiteArcTangentPointX(double value) {
        DCoordinate3 point = _project_arc->GetTangentCoordinates(index1, selected_arc_point);
        if (value != point.x())
        {
            point.x() = value;
            _project_arc->SetTangentCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }

    void GLWidget::setHermiteArcTangentPointY(double value) {
        DCoordinate3 point = _project_arc->GetTangentCoordinates(index1, selected_arc_point);
        if (value != point.y())
        {
            point.y() = value;
            _project_arc->SetTangentCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }

    void GLWidget::setHermiteArcTangentPointZ(double value) {
        DCoordinate3 point = _project_arc->GetTangentCoordinates(index1, selected_arc_point);
        if (value != point.z())
        {
            point.z() = value;
            _project_arc->SetTangentCoordinates(index1, selected_arc_point, point);
            _project_arc->UpdateArcs(index1);
            update();
        }
    }

    void GLWidget::writeArcToFile()
    {
        _project_arc->writeToFile();
    }

    void GLWidget::readArcFromFile()
    {
        _project_arc->readFromFile();
    }

    void GLWidget::writePatchToFile()
    {
        _project_patch->writeToFile();
    }

    void GLWidget::readPatchFromFile()
    {
        _project_patch->readFromFile();
    }
}
