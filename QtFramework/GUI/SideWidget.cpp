#include "SideWidget.h"

namespace cagd
{
    SideWidget::SideWidget(QWidget *parent): QWidget(parent)
    {
        setupUi(this);

        QPalette p = rotate_x_slider->palette();

        p.setColor(QPalette::Highlight, QColor(255,50,10).lighter());

        rotate_x_slider->setPalette(p);

        p = rotate_y_slider->palette();

        p.setColor(QPalette::Highlight, QColor(50,255,10).lighter());

        rotate_y_slider->setPalette(p);

        p = rotate_z_slider->palette();

        p.setColor(QPalette::Highlight, QColor(10,10,255));

        rotate_z_slider->setPalette(p);

        p = derivatives_scale_slider->palette();

        p.setColor(QPalette::Highlight, QColor(255,255,0));

        derivatives_scale_slider->setPalette(p);

        texture_combo->addItem("Texture 1");
        texture_combo->addItem("Texture 2");
        texture_combo->addItem("Texture 3");
        texture_combo->addItem("Texture 4");
        texture_combo->addItem("Texture 5");
        texture_combo->addItem("Texture 6");
        texture_combo->addItem("Texture 7");
        texture_combo->addItem("Texture 8");
        texture_combo->addItem("Texture 9");
        texture_combo->addItem("Texture 10");
        texture_combo->addItem("Texture 11");
        texture_combo->addItem("Texture 12");
        texture_combo->addItem("Texture 13");

        material_combo->addItem("MatFBBrass");
        material_combo->addItem("MatFBGold");
        material_combo->addItem("MatFBSilver");
        material_combo->addItem("MatFBEmerald");
        material_combo->addItem("MatFBPearl");
        material_combo->addItem("MatFBRuby");
        material_combo->addItem("MatFBTurquoise");

        selected_shader_cb->addItem("Directional light");
        selected_shader_cb->addItem("Two sided lighting");
        selected_shader_cb->addItem("Toon");
        selected_shader_cb->addItem("Reflection lines");

        direction1_cb->addItem("Left");
        direction2_cb->addItem("Left");

        direction1_cb->addItem("Right");
        direction2_cb->addItem("Right");
    }
}
