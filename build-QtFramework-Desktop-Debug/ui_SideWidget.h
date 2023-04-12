/********************************************************************************
** Form generated from reading UI file 'SideWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEWIDGET_H
#define UI_SIDEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *rotate_x_slider;
    QLabel *label_2;
    QSlider *rotate_y_slider;
    QLabel *label_3;
    QSlider *rotate_z_slider;
    QLabel *label_8;
    QSlider *derivatives_scale_slider;
    QLabel *label_4;
    QDoubleSpinBox *zoom_factor_spin_box;
    QLabel *label_5;
    QDoubleSpinBox *trans_x_spin_box;
    QLabel *label_6;
    QDoubleSpinBox *trans_y_spin_box;
    QLabel *label_7;
    QDoubleSpinBox *trans_z_spin_box;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chb_first_der;
    QCheckBox *chb_second_der;
    QTabWidget *tabWidget;
    QWidget *tab_0;
    QPushButton *insertArc_bt;
    QPushButton *deleteArc_bt;
    QPushButton *continueArc_bt;
    QPushButton *joinArc_bt;
    QPushButton *mergeArcs_bt;
    QSpinBox *index1_sb;
    QSpinBox *index2_sb;
    QLabel *label_36;
    QLabel *label_37;
    QComboBox *direction1_cb;
    QComboBox *direction2_cb;
    QPushButton *render_selected_arc_bt;
    QPushButton *render_all_arc_bt;
    QLabel *label_51;
    QLabel *label_52;
    QDoubleSpinBox *hermite_arc_z;
    QLabel *label_53;
    QDoubleSpinBox *hermite_arc_x;
    QDoubleSpinBox *hermite_arc_y;
    QSpinBox *selected_point_arc;
    QLabel *label_85;
    QLabel *label_54;
    QDoubleSpinBox *hermite_arc_ty;
    QLabel *label_55;
    QDoubleSpinBox *hermite_arc_tx;
    QLabel *label_56;
    QDoubleSpinBox *hermite_arc_tz;
    QWidget *tab_1;
    QPushButton *continuePatches_bt;
    QPushButton *mergePatches_bt;
    QPushButton *joinPatches_bt;
    QPushButton *insertPatch_bt;
    QPushButton *deletePatch_bt;
    QCheckBox *material_cb;
    QCheckBox *texture_cb;
    QComboBox *texture_combo;
    QComboBox *material_combo;
    QLabel *label_21;
    QDoubleSpinBox *red_sb;
    QComboBox *selected_shader_cb;
    QDoubleSpinBox *shading_param_sb;
    QLabel *label_24;
    QDoubleSpinBox *shader_scale_sb;
    QLabel *label_19;
    QLabel *label_22;
    QLabel *label_23;
    QDoubleSpinBox *green_sb;
    QLabel *label_25;
    QLabel *label_20;
    QDoubleSpinBox *smooting_shader_sb;
    QDoubleSpinBox *blue_sb;
    QCheckBox *patch_v_iso_cb;
    QCheckBox *patch_u_iso_cb;
    QComboBox *patch_dir_cb1_2;
    QSpinBox *patch_sb2_2;
    QSpinBox *patch_sb1_2;
    QLabel *label_78;
    QLabel *label_77;
    QComboBox *patch_dir_cb2_2;
    QLabel *label_75;
    QLabel *label_76;
    QPushButton *render_all_patch_bt;
    QPushButton *render_selected_patch_bt;
    QSpinBox *selected_point;
    QLabel *label_79;
    QLabel *label_26;
    QLabel *label_15;
    QLabel *label_13;
    QDoubleSpinBox *hermite_patch_vz;
    QLabel *label_9;
    QLabel *label_12;
    QDoubleSpinBox *hermite_patch_ty;
    QLabel *label_27;
    QLabel *label_10;
    QLabel *label_18;
    QLabel *label_17;
    QDoubleSpinBox *hermite_patch_uz;
    QDoubleSpinBox *hermite_patch_y;
    QDoubleSpinBox *hermite_patch_uy;
    QDoubleSpinBox *hermite_patch_x;
    QDoubleSpinBox *hermite_patch_vx;
    QLabel *label_14;
    QDoubleSpinBox *hermite_patch_ux;
    QDoubleSpinBox *hermite_patch_tx;
    QLabel *label_11;
    QLabel *label_16;
    QDoubleSpinBox *hermite_patch_vy;
    QDoubleSpinBox *hermite_patch_tz;
    QDoubleSpinBox *hermite_patch_z;
    QCheckBox *normal_vectors_cb;

    void setupUi(QWidget *SideWidget)
    {
        if (SideWidget->objectName().isEmpty())
            SideWidget->setObjectName(QString::fromUtf8("SideWidget"));
        SideWidget->resize(508, 988);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideWidget->sizePolicy().hasHeightForWidth());
        SideWidget->setSizePolicy(sizePolicy);
        SideWidget->setMinimumSize(QSize(269, 0));
        groupBox = new QGroupBox(SideWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 491, 981));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 21, 361, 315));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        rotate_x_slider = new QSlider(layoutWidget);
        rotate_x_slider->setObjectName(QString::fromUtf8("rotate_x_slider"));
        rotate_x_slider->setMinimum(-180);
        rotate_x_slider->setMaximum(180);
        rotate_x_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, rotate_x_slider);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rotate_y_slider = new QSlider(layoutWidget);
        rotate_y_slider->setObjectName(QString::fromUtf8("rotate_y_slider"));
        rotate_y_slider->setMinimum(-180);
        rotate_y_slider->setMaximum(180);
        rotate_y_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, rotate_y_slider);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rotate_z_slider = new QSlider(layoutWidget);
        rotate_z_slider->setObjectName(QString::fromUtf8("rotate_z_slider"));
        rotate_z_slider->setMinimum(-180);
        rotate_z_slider->setMaximum(180);
        rotate_z_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(2, QFormLayout::FieldRole, rotate_z_slider);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        derivatives_scale_slider = new QSlider(layoutWidget);
        derivatives_scale_slider->setObjectName(QString::fromUtf8("derivatives_scale_slider"));
        derivatives_scale_slider->setMaximum(200);
        derivatives_scale_slider->setValue(100);
        derivatives_scale_slider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(3, QFormLayout::FieldRole, derivatives_scale_slider);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        zoom_factor_spin_box = new QDoubleSpinBox(layoutWidget);
        zoom_factor_spin_box->setObjectName(QString::fromUtf8("zoom_factor_spin_box"));
        zoom_factor_spin_box->setDecimals(5);
        zoom_factor_spin_box->setMinimum(0.000100000000000);
        zoom_factor_spin_box->setMaximum(10000.000000000000000);
        zoom_factor_spin_box->setSingleStep(0.100000000000000);
        zoom_factor_spin_box->setValue(1.000000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, zoom_factor_spin_box);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        trans_x_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_x_spin_box->setObjectName(QString::fromUtf8("trans_x_spin_box"));
        trans_x_spin_box->setMinimum(-100.000000000000000);
        trans_x_spin_box->setMaximum(100.000000000000000);
        trans_x_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, trans_x_spin_box);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        trans_y_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_y_spin_box->setObjectName(QString::fromUtf8("trans_y_spin_box"));
        trans_y_spin_box->setMinimum(-100.000000000000000);
        trans_y_spin_box->setMaximum(100.000000000000000);
        trans_y_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(6, QFormLayout::FieldRole, trans_y_spin_box);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        trans_z_spin_box = new QDoubleSpinBox(layoutWidget);
        trans_z_spin_box->setObjectName(QString::fromUtf8("trans_z_spin_box"));
        trans_z_spin_box->setMinimum(-100.000000000000000);
        trans_z_spin_box->setMaximum(100.000000000000000);
        trans_z_spin_box->setSingleStep(0.100000000000000);

        formLayout->setWidget(7, QFormLayout::FieldRole, trans_z_spin_box);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(11, QFormLayout::SpanningRole, horizontalSpacer);

        chb_first_der = new QCheckBox(layoutWidget);
        chb_first_der->setObjectName(QString::fromUtf8("chb_first_der"));
        chb_first_der->setChecked(false);

        formLayout->setWidget(8, QFormLayout::LabelRole, chb_first_der);

        chb_second_der = new QCheckBox(layoutWidget);
        chb_second_der->setObjectName(QString::fromUtf8("chb_second_der"));
        chb_second_der->setChecked(false);

        formLayout->setWidget(8, QFormLayout::FieldRole, chb_second_der);

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 330, 481, 651));
        tab_0 = new QWidget();
        tab_0->setObjectName(QString::fromUtf8("tab_0"));
        insertArc_bt = new QPushButton(tab_0);
        insertArc_bt->setObjectName(QString::fromUtf8("insertArc_bt"));
        insertArc_bt->setGeometry(QRect(40, 50, 171, 28));
        deleteArc_bt = new QPushButton(tab_0);
        deleteArc_bt->setObjectName(QString::fromUtf8("deleteArc_bt"));
        deleteArc_bt->setGeometry(QRect(40, 80, 171, 28));
        continueArc_bt = new QPushButton(tab_0);
        continueArc_bt->setObjectName(QString::fromUtf8("continueArc_bt"));
        continueArc_bt->setGeometry(QRect(40, 110, 171, 28));
        joinArc_bt = new QPushButton(tab_0);
        joinArc_bt->setObjectName(QString::fromUtf8("joinArc_bt"));
        joinArc_bt->setGeometry(QRect(40, 140, 171, 28));
        mergeArcs_bt = new QPushButton(tab_0);
        mergeArcs_bt->setObjectName(QString::fromUtf8("mergeArcs_bt"));
        mergeArcs_bt->setGeometry(QRect(40, 170, 171, 31));
        index1_sb = new QSpinBox(tab_0);
        index1_sb->setObjectName(QString::fromUtf8("index1_sb"));
        index1_sb->setGeometry(QRect(240, 90, 44, 28));
        index2_sb = new QSpinBox(tab_0);
        index2_sb->setObjectName(QString::fromUtf8("index2_sb"));
        index2_sb->setGeometry(QRect(330, 90, 44, 28));
        label_36 = new QLabel(tab_0);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(230, 60, 59, 20));
        label_37 = new QLabel(tab_0);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(230, 130, 71, 20));
        direction1_cb = new QComboBox(tab_0);
        direction1_cb->setObjectName(QString::fromUtf8("direction1_cb"));
        direction1_cb->setGeometry(QRect(230, 160, 61, 28));
        direction2_cb = new QComboBox(tab_0);
        direction2_cb->setObjectName(QString::fromUtf8("direction2_cb"));
        direction2_cb->setGeometry(QRect(320, 160, 61, 28));
        render_selected_arc_bt = new QPushButton(tab_0);
        render_selected_arc_bt->setObjectName(QString::fromUtf8("render_selected_arc_bt"));
        render_selected_arc_bt->setGeometry(QRect(40, 200, 171, 28));
        render_all_arc_bt = new QPushButton(tab_0);
        render_all_arc_bt->setObjectName(QString::fromUtf8("render_all_arc_bt"));
        render_all_arc_bt->setGeometry(QRect(40, 230, 171, 28));
        label_51 = new QLabel(tab_0);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setGeometry(QRect(50, 450, 63, 20));
        label_52 = new QLabel(tab_0);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setGeometry(QRect(50, 410, 63, 20));
        hermite_arc_z = new QDoubleSpinBox(tab_0);
        hermite_arc_z->setObjectName(QString::fromUtf8("hermite_arc_z"));
        hermite_arc_z->setGeometry(QRect(150, 450, 62, 26));
        hermite_arc_z->setMinimum(-99.000000000000000);
        hermite_arc_z->setSingleStep(0.100000000000000);
        label_53 = new QLabel(tab_0);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setGeometry(QRect(50, 370, 63, 20));
        hermite_arc_x = new QDoubleSpinBox(tab_0);
        hermite_arc_x->setObjectName(QString::fromUtf8("hermite_arc_x"));
        hermite_arc_x->setGeometry(QRect(150, 370, 62, 26));
        hermite_arc_x->setMinimum(-99.000000000000000);
        hermite_arc_x->setSingleStep(0.100000000000000);
        hermite_arc_y = new QDoubleSpinBox(tab_0);
        hermite_arc_y->setObjectName(QString::fromUtf8("hermite_arc_y"));
        hermite_arc_y->setGeometry(QRect(150, 410, 62, 26));
        hermite_arc_y->setMinimum(-99.000000000000000);
        hermite_arc_y->setSingleStep(0.100000000000000);
        selected_point_arc = new QSpinBox(tab_0);
        selected_point_arc->setObjectName(QString::fromUtf8("selected_point_arc"));
        selected_point_arc->setGeometry(QRect(160, 320, 48, 26));
        selected_point_arc->setMaximum(1);
        label_85 = new QLabel(tab_0);
        label_85->setObjectName(QString::fromUtf8("label_85"));
        label_85->setGeometry(QRect(40, 320, 101, 21));
        label_54 = new QLabel(tab_0);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setGeometry(QRect(250, 370, 63, 20));
        hermite_arc_ty = new QDoubleSpinBox(tab_0);
        hermite_arc_ty->setObjectName(QString::fromUtf8("hermite_arc_ty"));
        hermite_arc_ty->setGeometry(QRect(350, 410, 62, 26));
        hermite_arc_ty->setMinimum(-99.000000000000000);
        hermite_arc_ty->setSingleStep(0.100000000000000);
        label_55 = new QLabel(tab_0);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setGeometry(QRect(250, 450, 63, 20));
        hermite_arc_tx = new QDoubleSpinBox(tab_0);
        hermite_arc_tx->setObjectName(QString::fromUtf8("hermite_arc_tx"));
        hermite_arc_tx->setGeometry(QRect(350, 370, 62, 26));
        hermite_arc_tx->setMinimum(-99.000000000000000);
        hermite_arc_tx->setSingleStep(0.100000000000000);
        label_56 = new QLabel(tab_0);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(250, 410, 63, 20));
        hermite_arc_tz = new QDoubleSpinBox(tab_0);
        hermite_arc_tz->setObjectName(QString::fromUtf8("hermite_arc_tz"));
        hermite_arc_tz->setGeometry(QRect(350, 450, 62, 26));
        hermite_arc_tz->setMinimum(-99.000000000000000);
        hermite_arc_tz->setSingleStep(0.100000000000000);
        tabWidget->addTab(tab_0, QString());
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        continuePatches_bt = new QPushButton(tab_1);
        continuePatches_bt->setObjectName(QString::fromUtf8("continuePatches_bt"));
        continuePatches_bt->setGeometry(QRect(10, 70, 171, 28));
        mergePatches_bt = new QPushButton(tab_1);
        mergePatches_bt->setObjectName(QString::fromUtf8("mergePatches_bt"));
        mergePatches_bt->setGeometry(QRect(10, 130, 171, 28));
        joinPatches_bt = new QPushButton(tab_1);
        joinPatches_bt->setObjectName(QString::fromUtf8("joinPatches_bt"));
        joinPatches_bt->setGeometry(QRect(10, 100, 171, 28));
        insertPatch_bt = new QPushButton(tab_1);
        insertPatch_bt->setObjectName(QString::fromUtf8("insertPatch_bt"));
        insertPatch_bt->setGeometry(QRect(10, 10, 171, 28));
        deletePatch_bt = new QPushButton(tab_1);
        deletePatch_bt->setObjectName(QString::fromUtf8("deletePatch_bt"));
        deletePatch_bt->setGeometry(QRect(10, 40, 171, 28));
        material_cb = new QCheckBox(tab_1);
        material_cb->setObjectName(QString::fromUtf8("material_cb"));
        material_cb->setGeometry(QRect(200, 50, 87, 26));
        texture_cb = new QCheckBox(tab_1);
        texture_cb->setObjectName(QString::fromUtf8("texture_cb"));
        texture_cb->setGeometry(QRect(200, 10, 87, 26));
        texture_combo = new QComboBox(tab_1);
        texture_combo->setObjectName(QString::fromUtf8("texture_combo"));
        texture_combo->setGeometry(QRect(310, 10, 111, 28));
        material_combo = new QComboBox(tab_1);
        material_combo->setObjectName(QString::fromUtf8("material_combo"));
        material_combo->setGeometry(QRect(310, 50, 111, 28));
        label_21 = new QLabel(tab_1);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(188, 170, 71, 20));
        red_sb = new QDoubleSpinBox(tab_1);
        red_sb->setObjectName(QString::fromUtf8("red_sb"));
        red_sb->setGeometry(QRect(400, 130, 63, 28));
        red_sb->setMaximum(1.000000000000000);
        red_sb->setSingleStep(0.010000000000000);
        red_sb->setValue(1.000000000000000);
        selected_shader_cb = new QComboBox(tab_1);
        selected_shader_cb->setObjectName(QString::fromUtf8("selected_shader_cb"));
        selected_shader_cb->setGeometry(QRect(310, 90, 121, 28));
        shading_param_sb = new QDoubleSpinBox(tab_1);
        shading_param_sb->setObjectName(QString::fromUtf8("shading_param_sb"));
        shading_param_sb->setGeometry(QRect(260, 220, 63, 28));
        shading_param_sb->setSingleStep(0.100000000000000);
        label_24 = new QLabel(tab_1);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(370, 170, 31, 20));
        shader_scale_sb = new QDoubleSpinBox(tab_1);
        shader_scale_sb->setObjectName(QString::fromUtf8("shader_scale_sb"));
        shader_scale_sb->setGeometry(QRect(270, 130, 63, 28));
        shader_scale_sb->setMaximum(100.000000000000000);
        shader_scale_sb->setSingleStep(0.100000000000000);
        label_19 = new QLabel(tab_1);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(200, 130, 59, 20));
        label_22 = new QLabel(tab_1);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(120, 220, 131, 20));
        label_23 = new QLabel(tab_1);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(370, 130, 21, 20));
        green_sb = new QDoubleSpinBox(tab_1);
        green_sb->setObjectName(QString::fromUtf8("green_sb"));
        green_sb->setGeometry(QRect(400, 170, 63, 28));
        green_sb->setMaximum(1.000000000000000);
        green_sb->setSingleStep(0.010000000000000);
        green_sb->setValue(1.000000000000000);
        label_25 = new QLabel(tab_1);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(370, 200, 21, 20));
        label_20 = new QLabel(tab_1);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(200, 90, 111, 20));
        smooting_shader_sb = new QDoubleSpinBox(tab_1);
        smooting_shader_sb->setObjectName(QString::fromUtf8("smooting_shader_sb"));
        smooting_shader_sb->setGeometry(QRect(270, 170, 63, 28));
        smooting_shader_sb->setMaximum(1.000000000000000);
        smooting_shader_sb->setSingleStep(0.100000000000000);
        blue_sb = new QDoubleSpinBox(tab_1);
        blue_sb->setObjectName(QString::fromUtf8("blue_sb"));
        blue_sb->setGeometry(QRect(400, 200, 63, 28));
        blue_sb->setMaximum(1.000000000000000);
        blue_sb->setSingleStep(0.010000000000000);
        blue_sb->setValue(1.000000000000000);
        patch_v_iso_cb = new QCheckBox(tab_1);
        patch_v_iso_cb->setObjectName(QString::fromUtf8("patch_v_iso_cb"));
        patch_v_iso_cb->setGeometry(QRect(110, 240, 71, 26));
        patch_u_iso_cb = new QCheckBox(tab_1);
        patch_u_iso_cb->setObjectName(QString::fromUtf8("patch_u_iso_cb"));
        patch_u_iso_cb->setGeometry(QRect(10, 240, 87, 26));
        patch_dir_cb1_2 = new QComboBox(tab_1);
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->addItem(QString());
        patch_dir_cb1_2->setObjectName(QString::fromUtf8("patch_dir_cb1_2"));
        patch_dir_cb1_2->setGeometry(QRect(400, 230, 71, 25));
        patch_sb2_2 = new QSpinBox(tab_1);
        patch_sb2_2->setObjectName(QString::fromUtf8("patch_sb2_2"));
        patch_sb2_2->setGeometry(QRect(190, 310, 48, 26));
        patch_sb1_2 = new QSpinBox(tab_1);
        patch_sb1_2->setObjectName(QString::fromUtf8("patch_sb1_2"));
        patch_sb1_2->setGeometry(QRect(60, 310, 48, 26));
        label_78 = new QLabel(tab_1);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(10, 310, 61, 21));
        label_77 = new QLabel(tab_1);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setGeometry(QRect(310, 240, 81, 21));
        patch_dir_cb2_2 = new QComboBox(tab_1);
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->addItem(QString());
        patch_dir_cb2_2->setObjectName(QString::fromUtf8("patch_dir_cb2_2"));
        patch_dir_cb2_2->setGeometry(QRect(400, 260, 71, 25));
        label_75 = new QLabel(tab_1);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setGeometry(QRect(310, 260, 81, 21));
        label_76 = new QLabel(tab_1);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setGeometry(QRect(130, 310, 51, 21));
        render_all_patch_bt = new QPushButton(tab_1);
        render_all_patch_bt->setObjectName(QString::fromUtf8("render_all_patch_bt"));
        render_all_patch_bt->setGeometry(QRect(10, 190, 171, 28));
        render_selected_patch_bt = new QPushButton(tab_1);
        render_selected_patch_bt->setObjectName(QString::fromUtf8("render_selected_patch_bt"));
        render_selected_patch_bt->setGeometry(QRect(10, 160, 171, 28));
        selected_point = new QSpinBox(tab_1);
        selected_point->setObjectName(QString::fromUtf8("selected_point"));
        selected_point->setGeometry(QRect(380, 310, 48, 26));
        selected_point->setMaximum(3);
        label_79 = new QLabel(tab_1);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setGeometry(QRect(260, 310, 101, 21));
        label_26 = new QLabel(tab_1);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(260, 520, 63, 20));
        label_15 = new QLabel(tab_1);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(60, 560, 63, 20));
        label_13 = new QLabel(tab_1);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(260, 400, 63, 20));
        hermite_patch_vz = new QDoubleSpinBox(tab_1);
        hermite_patch_vz->setObjectName(QString::fromUtf8("hermite_patch_vz"));
        hermite_patch_vz->setGeometry(QRect(160, 560, 62, 26));
        hermite_patch_vz->setMinimum(-99.000000000000000);
        hermite_patch_vz->setSingleStep(0.100000000000000);
        label_9 = new QLabel(tab_1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(60, 360, 63, 20));
        label_12 = new QLabel(tab_1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(260, 440, 63, 20));
        hermite_patch_ty = new QDoubleSpinBox(tab_1);
        hermite_patch_ty->setObjectName(QString::fromUtf8("hermite_patch_ty"));
        hermite_patch_ty->setGeometry(QRect(350, 520, 62, 26));
        hermite_patch_ty->setMinimum(-99.000000000000000);
        hermite_patch_ty->setSingleStep(0.100000000000000);
        label_27 = new QLabel(tab_1);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(260, 480, 63, 20));
        label_10 = new QLabel(tab_1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(60, 400, 63, 20));
        label_18 = new QLabel(tab_1);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(260, 560, 63, 20));
        label_17 = new QLabel(tab_1);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(60, 480, 63, 20));
        hermite_patch_uz = new QDoubleSpinBox(tab_1);
        hermite_patch_uz->setObjectName(QString::fromUtf8("hermite_patch_uz"));
        hermite_patch_uz->setGeometry(QRect(350, 440, 62, 26));
        hermite_patch_uz->setMinimum(-99.000000000000000);
        hermite_patch_uz->setSingleStep(0.100000000000000);
        hermite_patch_y = new QDoubleSpinBox(tab_1);
        hermite_patch_y->setObjectName(QString::fromUtf8("hermite_patch_y"));
        hermite_patch_y->setGeometry(QRect(160, 400, 62, 26));
        hermite_patch_y->setMinimum(-99.000000000000000);
        hermite_patch_y->setSingleStep(0.100000000000000);
        hermite_patch_uy = new QDoubleSpinBox(tab_1);
        hermite_patch_uy->setObjectName(QString::fromUtf8("hermite_patch_uy"));
        hermite_patch_uy->setGeometry(QRect(350, 400, 62, 26));
        hermite_patch_uy->setMinimum(-99.000000000000000);
        hermite_patch_uy->setSingleStep(0.100000000000000);
        hermite_patch_x = new QDoubleSpinBox(tab_1);
        hermite_patch_x->setObjectName(QString::fromUtf8("hermite_patch_x"));
        hermite_patch_x->setGeometry(QRect(160, 360, 62, 26));
        hermite_patch_x->setMinimum(-99.000000000000000);
        hermite_patch_x->setSingleStep(0.100000000000000);
        hermite_patch_vx = new QDoubleSpinBox(tab_1);
        hermite_patch_vx->setObjectName(QString::fromUtf8("hermite_patch_vx"));
        hermite_patch_vx->setGeometry(QRect(160, 480, 62, 26));
        hermite_patch_vx->setMinimum(-99.000000000000000);
        hermite_patch_vx->setSingleStep(0.100000000000000);
        label_14 = new QLabel(tab_1);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(260, 360, 63, 20));
        hermite_patch_ux = new QDoubleSpinBox(tab_1);
        hermite_patch_ux->setObjectName(QString::fromUtf8("hermite_patch_ux"));
        hermite_patch_ux->setGeometry(QRect(350, 360, 62, 26));
        hermite_patch_ux->setMinimum(-99.000000000000000);
        hermite_patch_ux->setSingleStep(0.100000000000000);
        hermite_patch_tx = new QDoubleSpinBox(tab_1);
        hermite_patch_tx->setObjectName(QString::fromUtf8("hermite_patch_tx"));
        hermite_patch_tx->setGeometry(QRect(350, 480, 62, 26));
        hermite_patch_tx->setMinimum(-99.000000000000000);
        hermite_patch_tx->setSingleStep(0.100000000000000);
        label_11 = new QLabel(tab_1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(60, 440, 63, 20));
        label_16 = new QLabel(tab_1);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(60, 520, 63, 20));
        hermite_patch_vy = new QDoubleSpinBox(tab_1);
        hermite_patch_vy->setObjectName(QString::fromUtf8("hermite_patch_vy"));
        hermite_patch_vy->setGeometry(QRect(160, 520, 62, 26));
        hermite_patch_vy->setMinimum(-99.000000000000000);
        hermite_patch_vy->setSingleStep(0.100000000000000);
        hermite_patch_tz = new QDoubleSpinBox(tab_1);
        hermite_patch_tz->setObjectName(QString::fromUtf8("hermite_patch_tz"));
        hermite_patch_tz->setGeometry(QRect(350, 560, 62, 26));
        hermite_patch_tz->setMinimum(-99.000000000000000);
        hermite_patch_tz->setSingleStep(0.100000000000000);
        hermite_patch_z = new QDoubleSpinBox(tab_1);
        hermite_patch_z->setObjectName(QString::fromUtf8("hermite_patch_z"));
        hermite_patch_z->setGeometry(QRect(160, 440, 62, 26));
        hermite_patch_z->setMinimum(-99.000000000000000);
        hermite_patch_z->setSingleStep(0.100000000000000);
        normal_vectors_cb = new QCheckBox(tab_1);
        normal_vectors_cb->setObjectName(QString::fromUtf8("normal_vectors_cb"));
        normal_vectors_cb->setGeometry(QRect(50, 270, 121, 26));
        tabWidget->addTab(tab_1, QString());
#ifndef QT_NO_SHORTCUT
        label->setBuddy(rotate_x_slider);
        label_2->setBuddy(rotate_y_slider);
        label_3->setBuddy(rotate_z_slider);
        label_4->setBuddy(zoom_factor_spin_box);
        label_5->setBuddy(trans_x_spin_box);
        label_6->setBuddy(trans_y_spin_box);
        label_7->setBuddy(trans_z_spin_box);
#endif // QT_NO_SHORTCUT

        retranslateUi(SideWidget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SideWidget);
    } // setupUi

    void retranslateUi(QWidget *SideWidget)
    {
        SideWidget->setWindowTitle(QApplication::translate("SideWidget", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("SideWidget", "Transformations", nullptr));
        label->setText(QApplication::translate("SideWidget", "Rotate around x", nullptr));
        label_2->setText(QApplication::translate("SideWidget", "Rotate around y", nullptr));
        label_3->setText(QApplication::translate("SideWidget", "Rotate around z", nullptr));
        label_8->setText(QApplication::translate("SideWidget", "Derivate Scale", nullptr));
        label_4->setText(QApplication::translate("SideWidget", "Zoom factor", nullptr));
#ifndef QT_NO_TOOLTIP
        zoom_factor_spin_box->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SideWidget", "Translate along x", nullptr));
        label_6->setText(QApplication::translate("SideWidget", "Translate along y", nullptr));
        label_7->setText(QApplication::translate("SideWidget", "Translate along z", nullptr));
        chb_first_der->setText(QApplication::translate("SideWidget", "First derivative", nullptr));
        chb_second_der->setText(QApplication::translate("SideWidget", "Second derivative", nullptr));
        insertArc_bt->setText(QApplication::translate("SideWidget", "Insert New Arc", nullptr));
        deleteArc_bt->setText(QApplication::translate("SideWidget", "Delete Arc", nullptr));
        continueArc_bt->setText(QApplication::translate("SideWidget", "Continue Arc", nullptr));
        joinArc_bt->setText(QApplication::translate("SideWidget", "Joining Arcs", nullptr));
        mergeArcs_bt->setText(QApplication::translate("SideWidget", "Merge Arcs", nullptr));
        label_36->setText(QApplication::translate("SideWidget", "Indexes", nullptr));
        label_37->setText(QApplication::translate("SideWidget", "Directions", nullptr));
        render_selected_arc_bt->setText(QApplication::translate("SideWidget", "Render Selected Arc", nullptr));
        render_all_arc_bt->setText(QApplication::translate("SideWidget", "Render All Arcs", nullptr));
        label_51->setText(QApplication::translate("SideWidget", "z", nullptr));
        label_52->setText(QApplication::translate("SideWidget", "y", nullptr));
        label_53->setText(QApplication::translate("SideWidget", "x", nullptr));
        label_85->setText(QApplication::translate("SideWidget", "Selected Point", nullptr));
        label_54->setText(QApplication::translate("SideWidget", "tangent_x", nullptr));
        label_55->setText(QApplication::translate("SideWidget", "tangent_z", nullptr));
        label_56->setText(QApplication::translate("SideWidget", "tangent_y", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_0), QApplication::translate("SideWidget", "Hermite Arc", nullptr));
        continuePatches_bt->setText(QApplication::translate("SideWidget", "Continue Patch", nullptr));
        mergePatches_bt->setText(QApplication::translate("SideWidget", "Merge Patch", nullptr));
        joinPatches_bt->setText(QApplication::translate("SideWidget", "Joining Patch", nullptr));
        insertPatch_bt->setText(QApplication::translate("SideWidget", "Insert New Patch", nullptr));
        deletePatch_bt->setText(QApplication::translate("SideWidget", "Delete Patch", nullptr));
        material_cb->setText(QApplication::translate("SideWidget", "Material", nullptr));
        texture_cb->setText(QApplication::translate("SideWidget", "Texture", nullptr));
        label_21->setText(QApplication::translate("SideWidget", "Smooting", nullptr));
        label_24->setText(QApplication::translate("SideWidget", "G", nullptr));
        label_19->setText(QApplication::translate("SideWidget", "Scale:", nullptr));
        label_22->setText(QApplication::translate("SideWidget", "Shading parameter", nullptr));
        label_23->setText(QApplication::translate("SideWidget", "R", nullptr));
        label_25->setText(QApplication::translate("SideWidget", "B", nullptr));
        label_20->setText(QApplication::translate("SideWidget", "Selected shader", nullptr));
        patch_v_iso_cb->setText(QApplication::translate("SideWidget", "V Iso", nullptr));
        patch_u_iso_cb->setText(QApplication::translate("SideWidget", "U Iso", nullptr));
        patch_dir_cb1_2->setItemText(0, QApplication::translate("SideWidget", "NORTH", nullptr));
        patch_dir_cb1_2->setItemText(1, QApplication::translate("SideWidget", "EAST", nullptr));
        patch_dir_cb1_2->setItemText(2, QApplication::translate("SideWidget", "SOUTH", nullptr));
        patch_dir_cb1_2->setItemText(3, QApplication::translate("SideWidget", "WEST", nullptr));
        patch_dir_cb1_2->setItemText(4, QApplication::translate("SideWidget", "NORTHEAST", nullptr));
        patch_dir_cb1_2->setItemText(5, QApplication::translate("SideWidget", "SOUTHEAST", nullptr));
        patch_dir_cb1_2->setItemText(6, QApplication::translate("SideWidget", "SOUTHWEST", nullptr));
        patch_dir_cb1_2->setItemText(7, QApplication::translate("SideWidget", "NORTHWEST", nullptr));

        label_78->setText(QApplication::translate("SideWidget", "Patch1", nullptr));
        label_77->setText(QApplication::translate("SideWidget", "Patch1Dir", nullptr));
        patch_dir_cb2_2->setItemText(0, QApplication::translate("SideWidget", "NORTH", nullptr));
        patch_dir_cb2_2->setItemText(1, QApplication::translate("SideWidget", "EAST", nullptr));
        patch_dir_cb2_2->setItemText(2, QApplication::translate("SideWidget", "SOUTH", nullptr));
        patch_dir_cb2_2->setItemText(3, QApplication::translate("SideWidget", "WEST", nullptr));
        patch_dir_cb2_2->setItemText(4, QApplication::translate("SideWidget", "NORTHEAST", nullptr));
        patch_dir_cb2_2->setItemText(5, QApplication::translate("SideWidget", "SOUTHEAST", nullptr));
        patch_dir_cb2_2->setItemText(6, QApplication::translate("SideWidget", "SOUTHWEST", nullptr));
        patch_dir_cb2_2->setItemText(7, QApplication::translate("SideWidget", "NORTHWEST", nullptr));

        label_75->setText(QApplication::translate("SideWidget", "Patch2Dir", nullptr));
        label_76->setText(QApplication::translate("SideWidget", "Patch2", nullptr));
        render_all_patch_bt->setText(QApplication::translate("SideWidget", "Render All Patches", nullptr));
        render_selected_patch_bt->setText(QApplication::translate("SideWidget", "Render Selected Patch", nullptr));
        label_79->setText(QApplication::translate("SideWidget", "Selected Point", nullptr));
        label_26->setText(QApplication::translate("SideWidget", "t_y", nullptr));
        label_15->setText(QApplication::translate("SideWidget", "v_z", nullptr));
        label_13->setText(QApplication::translate("SideWidget", "u_v", nullptr));
        label_9->setText(QApplication::translate("SideWidget", "x", nullptr));
        label_12->setText(QApplication::translate("SideWidget", "u_z", nullptr));
        label_27->setText(QApplication::translate("SideWidget", "t_x", nullptr));
        label_10->setText(QApplication::translate("SideWidget", "y", nullptr));
        label_18->setText(QApplication::translate("SideWidget", "t_z", nullptr));
        label_17->setText(QApplication::translate("SideWidget", "v_x", nullptr));
        label_14->setText(QApplication::translate("SideWidget", "u_x", nullptr));
        label_11->setText(QApplication::translate("SideWidget", "z", nullptr));
        label_16->setText(QApplication::translate("SideWidget", "v_y", nullptr));
        normal_vectors_cb->setText(QApplication::translate("SideWidget", "Normal Vectors", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("SideWidget", "Bicubic Hermite Patch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideWidget: public Ui_SideWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEWIDGET_H
