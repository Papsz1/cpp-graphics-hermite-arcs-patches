#include "MainWindow.h"
#include "qobjectdefs.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        connect(_side_widget->tabWidget, SIGNAL(currentChanged(int)), _gl_widget, SLOT(set_tab(int)));

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->derivatives_scale_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_derivatives_scale(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

        connect(_side_widget->chb_first_der, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_parametric_first_derivatives(bool)));
        connect(_side_widget->chb_second_der, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_parametric_second_derivatives(bool)));

        connect(_gl_widget, SIGNAL(set_parametric_first_derivatives_slot(bool)), _side_widget->chb_first_der, SLOT(setChecked(bool)));
        connect(_gl_widget, SIGNAL(set_parametric_second_derivatives_slot(bool)), _side_widget->chb_second_der, SLOT(setChecked(bool)));
        // Signals that sets the spinbox values

        connect(_side_widget->texture_cb, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_texture(bool)));
        connect(_side_widget->texture_combo, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_texture_type(int)));
        connect(_side_widget->material_cb, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_material(bool)));
        connect(_side_widget->material_combo, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_material_type(int)));

        connect(_side_widget->shader_scale_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_shader_scale(double)));
        connect(_side_widget->shading_param_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_shader_parameter(double)));
        connect(_side_widget->smooting_shader_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_smooting_shader(double)));
        connect(_side_widget->selected_shader_cb, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_selected_shader(int)));

        connect(_side_widget->red_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_red(double)));
        connect(_side_widget->blue_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_blue(double)));
        connect(_side_widget->green_sb, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_green(double)));

        connect(_side_widget->patch_u_iso_cb, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_patch_uip(bool)));
        connect(_side_widget->patch_v_iso_cb, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_patch_vip(bool)));
        connect(_side_widget->normal_vectors_cb, SIGNAL(clicked(bool)), _gl_widget, SLOT(show_normals(bool)));

        connect(_side_widget->index1_sb, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_arc1(int)));
        connect(_side_widget->index2_sb, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_arc2(int)));
        connect(_side_widget->direction1_cb, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_arc1(int)));
        connect(_side_widget->direction2_cb, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_arc2(int)));

        connect(_side_widget->insertArc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(insert_new_arc(bool)));
        connect(_side_widget->continueArc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(continue_arc(bool)));
        connect(_side_widget->deleteArc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(delete_arc(bool)));
        connect(_side_widget->mergeArcs_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(merge_arcs(bool)));
        connect(_side_widget->joinArc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(join_arcs(bool)));
        connect(_side_widget->render_selected_arc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_paint_selected_arc(bool)));
        connect(_side_widget->render_all_arc_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_paint_all_arcs(bool)));

        connect(_side_widget->insertPatch_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(insert_new_patch(bool)));
        connect(_side_widget->patch_sb1_2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_patch1(int)));
        connect(_side_widget->patch_sb2_2, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_index_patch2(int)));
        connect(_side_widget->patch_dir_cb1_2, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_patch1(int)));
        connect(_side_widget->patch_dir_cb2_2, SIGNAL(currentIndexChanged(int)), _gl_widget, SLOT(set_direction_patch2(int)));
        connect(_side_widget->continuePatches_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(continue_patch(bool)));

        connect(_side_widget->joinPatches_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(join_patches(bool)));
        connect(_side_widget->render_selected_patch_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_paint_selected_patch(bool)));
        connect(_side_widget->render_all_patch_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(set_paint_all_patches(bool)));
        connect(_side_widget->mergePatches_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(merge_patches(bool)));
        connect(_side_widget->deletePatch_bt, SIGNAL(clicked(bool)), _gl_widget, SLOT(delete_patch(bool)));

        connect(_gl_widget, SIGNAL(HermitePatchPointChangeX(double)), _side_widget->hermite_patch_x, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeY(double)), _side_widget->hermite_patch_y, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeZ(double)), _side_widget->hermite_patch_z, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUX(double)), _side_widget->hermite_patch_ux, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUY(double)), _side_widget->hermite_patch_uy, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeUZ(double)), _side_widget->hermite_patch_uz, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVX(double)), _side_widget->hermite_patch_vx, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVY(double)), _side_widget->hermite_patch_vy, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeVZ(double)), _side_widget->hermite_patch_vz, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTX(double)), _side_widget->hermite_patch_tx, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTY(double)), _side_widget->hermite_patch_ty, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermitePatchPointChangeTZ(double)), _side_widget->hermite_patch_tz, SLOT(setValue(double)));

        connect(_side_widget->hermite_patch_x, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointX(double)));
        connect(_side_widget->hermite_patch_y, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointY(double)));
        connect(_side_widget->hermite_patch_z, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointZ(double)));
        connect(_side_widget->hermite_patch_vx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVX(double)));
        connect(_side_widget->hermite_patch_vy, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVY(double)));
        connect(_side_widget->hermite_patch_vz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointVZ(double)));
        connect(_side_widget->hermite_patch_ux, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUX(double)));
        connect(_side_widget->hermite_patch_uy, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUY(double)));
        connect(_side_widget->hermite_patch_uz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointUZ(double)));
        connect(_side_widget->hermite_patch_tx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTX(double)));
        connect(_side_widget->hermite_patch_ty, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTY(double)));
        connect(_side_widget->hermite_patch_tz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermitePatchPointTZ(double)));

        connect(_side_widget->selected_point, SIGNAL(valueChanged(int)), _gl_widget, SLOT(setSelectedPoint(int)));

        connect(_gl_widget, SIGNAL(HermiteArcPointChangeX(double)), _side_widget->hermite_arc_x, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermiteArcPointChangeY(double)), _side_widget->hermite_arc_y, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermiteArcPointChangeZ(double)), _side_widget->hermite_arc_z, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermiteArcTangentChangeX(double)), _side_widget->hermite_arc_tx, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermiteArcTangentChangeY(double)), _side_widget->hermite_arc_ty, SLOT(setValue(double)));
        connect(_gl_widget, SIGNAL(HermiteArcTangentChangeZ(double)), _side_widget->hermite_arc_tz, SLOT(setValue(double)));

        connect(_side_widget->hermite_arc_x, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcPointX(double)));
        connect(_side_widget->hermite_arc_y, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcPointY(double)));
        connect(_side_widget->hermite_arc_z, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcPointZ(double)));
        connect(_side_widget->hermite_arc_tx, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcTangentPointX(double)));
        connect(_side_widget->hermite_arc_ty, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcTangentPointY(double)));
        connect(_side_widget->hermite_arc_tz, SIGNAL(valueChanged(double)), _gl_widget, SLOT(setHermiteArcTangentPointZ(double)));

        connect(_side_widget->selected_point_arc, SIGNAL(valueChanged(int)), _gl_widget, SLOT(setSelectedPointArc(int)));

    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
