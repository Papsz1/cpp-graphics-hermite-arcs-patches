/****************************************************************************
** Meta object code from reading C++ file 'GLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QtFramework/GUI/GLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cagd__GLWidget_t {
    QByteArrayData data[93];
    char stringdata0[1839];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cagd__GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cagd__GLWidget_t qt_meta_stringdata_cagd__GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "cagd::GLWidget"
QT_MOC_LITERAL(1, 15, 37), // "set_parametric_first_derivati..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "value"
QT_MOC_LITERAL(4, 60, 38), // "set_parametric_second_derivat..."
QT_MOC_LITERAL(5, 99, 25), // "set_cyclic_point_x_signal"
QT_MOC_LITERAL(6, 125, 25), // "set_cyclic_point_y_signal"
QT_MOC_LITERAL(7, 151, 25), // "set_cyclic_point_z_signal"
QT_MOC_LITERAL(8, 177, 24), // "HermitePatchPointChangeX"
QT_MOC_LITERAL(9, 202, 24), // "HermitePatchPointChangeY"
QT_MOC_LITERAL(10, 227, 24), // "HermitePatchPointChangeZ"
QT_MOC_LITERAL(11, 252, 25), // "HermitePatchPointChangeUX"
QT_MOC_LITERAL(12, 278, 25), // "HermitePatchPointChangeUY"
QT_MOC_LITERAL(13, 304, 25), // "HermitePatchPointChangeUZ"
QT_MOC_LITERAL(14, 330, 25), // "HermitePatchPointChangeVX"
QT_MOC_LITERAL(15, 356, 25), // "HermitePatchPointChangeVY"
QT_MOC_LITERAL(16, 382, 25), // "HermitePatchPointChangeVZ"
QT_MOC_LITERAL(17, 408, 25), // "HermitePatchPointChangeTX"
QT_MOC_LITERAL(18, 434, 25), // "HermitePatchPointChangeTY"
QT_MOC_LITERAL(19, 460, 25), // "HermitePatchPointChangeTZ"
QT_MOC_LITERAL(20, 486, 22), // "HermiteArcPointChangeX"
QT_MOC_LITERAL(21, 509, 22), // "HermiteArcPointChangeY"
QT_MOC_LITERAL(22, 532, 22), // "HermiteArcPointChangeZ"
QT_MOC_LITERAL(23, 555, 24), // "HermiteArcTangentChangeX"
QT_MOC_LITERAL(24, 580, 24), // "HermiteArcTangentChangeY"
QT_MOC_LITERAL(25, 605, 24), // "HermiteArcTangentChangeZ"
QT_MOC_LITERAL(26, 630, 7), // "set_tab"
QT_MOC_LITERAL(27, 638, 11), // "set_angle_x"
QT_MOC_LITERAL(28, 650, 11), // "set_angle_y"
QT_MOC_LITERAL(29, 662, 11), // "set_angle_z"
QT_MOC_LITERAL(30, 674, 15), // "set_zoom_factor"
QT_MOC_LITERAL(31, 690, 11), // "set_trans_x"
QT_MOC_LITERAL(32, 702, 11), // "set_trans_y"
QT_MOC_LITERAL(33, 714, 11), // "set_trans_z"
QT_MOC_LITERAL(34, 726, 21), // "set_derivatives_scale"
QT_MOC_LITERAL(35, 748, 32), // "set_parametric_first_derivatives"
QT_MOC_LITERAL(36, 781, 33), // "set_parametric_second_derivat..."
QT_MOC_LITERAL(37, 815, 11), // "set_texture"
QT_MOC_LITERAL(38, 827, 16), // "set_texture_type"
QT_MOC_LITERAL(39, 844, 12), // "set_material"
QT_MOC_LITERAL(40, 857, 17), // "set_material_type"
QT_MOC_LITERAL(41, 875, 7), // "set_red"
QT_MOC_LITERAL(42, 883, 8), // "set_blue"
QT_MOC_LITERAL(43, 892, 9), // "set_green"
QT_MOC_LITERAL(44, 902, 19), // "set_selected_shader"
QT_MOC_LITERAL(45, 922, 16), // "set_shader_scale"
QT_MOC_LITERAL(46, 939, 19), // "set_smooting_shader"
QT_MOC_LITERAL(47, 959, 20), // "set_shader_parameter"
QT_MOC_LITERAL(48, 980, 14), // "show_patch_uip"
QT_MOC_LITERAL(49, 995, 14), // "show_patch_vip"
QT_MOC_LITERAL(50, 1010, 14), // "insert_new_arc"
QT_MOC_LITERAL(51, 1025, 14), // "set_index_arc1"
QT_MOC_LITERAL(52, 1040, 14), // "set_index_arc2"
QT_MOC_LITERAL(53, 1055, 12), // "continue_arc"
QT_MOC_LITERAL(54, 1068, 10), // "delete_arc"
QT_MOC_LITERAL(55, 1079, 10), // "merge_arcs"
QT_MOC_LITERAL(56, 1090, 18), // "set_direction_arc1"
QT_MOC_LITERAL(57, 1109, 18), // "set_direction_arc2"
QT_MOC_LITERAL(58, 1128, 9), // "join_arcs"
QT_MOC_LITERAL(59, 1138, 22), // "set_paint_selected_arc"
QT_MOC_LITERAL(60, 1161, 18), // "set_paint_all_arcs"
QT_MOC_LITERAL(61, 1180, 14), // "continue_patch"
QT_MOC_LITERAL(62, 1195, 16), // "insert_new_patch"
QT_MOC_LITERAL(63, 1212, 16), // "set_index_patch1"
QT_MOC_LITERAL(64, 1229, 16), // "set_index_patch2"
QT_MOC_LITERAL(65, 1246, 20), // "set_direction_patch1"
QT_MOC_LITERAL(66, 1267, 20), // "set_direction_patch2"
QT_MOC_LITERAL(67, 1288, 12), // "join_patches"
QT_MOC_LITERAL(68, 1301, 24), // "set_paint_selected_patch"
QT_MOC_LITERAL(69, 1326, 21), // "set_paint_all_patches"
QT_MOC_LITERAL(70, 1348, 13), // "merge_patches"
QT_MOC_LITERAL(71, 1362, 12), // "show_normals"
QT_MOC_LITERAL(72, 1375, 12), // "delete_patch"
QT_MOC_LITERAL(73, 1388, 21), // "setHermitePatchPointX"
QT_MOC_LITERAL(74, 1410, 21), // "setHermitePatchPointY"
QT_MOC_LITERAL(75, 1432, 21), // "setHermitePatchPointZ"
QT_MOC_LITERAL(76, 1454, 22), // "setHermitePatchPointUX"
QT_MOC_LITERAL(77, 1477, 22), // "setHermitePatchPointUY"
QT_MOC_LITERAL(78, 1500, 22), // "setHermitePatchPointUZ"
QT_MOC_LITERAL(79, 1523, 22), // "setHermitePatchPointVX"
QT_MOC_LITERAL(80, 1546, 22), // "setHermitePatchPointVY"
QT_MOC_LITERAL(81, 1569, 22), // "setHermitePatchPointVZ"
QT_MOC_LITERAL(82, 1592, 22), // "setHermitePatchPointTX"
QT_MOC_LITERAL(83, 1615, 22), // "setHermitePatchPointTY"
QT_MOC_LITERAL(84, 1638, 22), // "setHermitePatchPointTZ"
QT_MOC_LITERAL(85, 1661, 16), // "setSelectedPoint"
QT_MOC_LITERAL(86, 1678, 19), // "setHermiteArcPointX"
QT_MOC_LITERAL(87, 1698, 19), // "setHermiteArcPointY"
QT_MOC_LITERAL(88, 1718, 19), // "setHermiteArcPointZ"
QT_MOC_LITERAL(89, 1738, 26), // "setHermiteArcTangentPointX"
QT_MOC_LITERAL(90, 1765, 26), // "setHermiteArcTangentPointY"
QT_MOC_LITERAL(91, 1792, 26), // "setHermiteArcTangentPointZ"
QT_MOC_LITERAL(92, 1819, 19) // "setSelectedPointArc"

    },
    "cagd::GLWidget\0set_parametric_first_derivatives_slot\0"
    "\0value\0set_parametric_second_derivatives_slot\0"
    "set_cyclic_point_x_signal\0"
    "set_cyclic_point_y_signal\0"
    "set_cyclic_point_z_signal\0"
    "HermitePatchPointChangeX\0"
    "HermitePatchPointChangeY\0"
    "HermitePatchPointChangeZ\0"
    "HermitePatchPointChangeUX\0"
    "HermitePatchPointChangeUY\0"
    "HermitePatchPointChangeUZ\0"
    "HermitePatchPointChangeVX\0"
    "HermitePatchPointChangeVY\0"
    "HermitePatchPointChangeVZ\0"
    "HermitePatchPointChangeTX\0"
    "HermitePatchPointChangeTY\0"
    "HermitePatchPointChangeTZ\0"
    "HermiteArcPointChangeX\0HermiteArcPointChangeY\0"
    "HermiteArcPointChangeZ\0HermiteArcTangentChangeX\0"
    "HermiteArcTangentChangeY\0"
    "HermiteArcTangentChangeZ\0set_tab\0"
    "set_angle_x\0set_angle_y\0set_angle_z\0"
    "set_zoom_factor\0set_trans_x\0set_trans_y\0"
    "set_trans_z\0set_derivatives_scale\0"
    "set_parametric_first_derivatives\0"
    "set_parametric_second_derivatives\0"
    "set_texture\0set_texture_type\0set_material\0"
    "set_material_type\0set_red\0set_blue\0"
    "set_green\0set_selected_shader\0"
    "set_shader_scale\0set_smooting_shader\0"
    "set_shader_parameter\0show_patch_uip\0"
    "show_patch_vip\0insert_new_arc\0"
    "set_index_arc1\0set_index_arc2\0"
    "continue_arc\0delete_arc\0merge_arcs\0"
    "set_direction_arc1\0set_direction_arc2\0"
    "join_arcs\0set_paint_selected_arc\0"
    "set_paint_all_arcs\0continue_patch\0"
    "insert_new_patch\0set_index_patch1\0"
    "set_index_patch2\0set_direction_patch1\0"
    "set_direction_patch2\0join_patches\0"
    "set_paint_selected_patch\0set_paint_all_patches\0"
    "merge_patches\0show_normals\0delete_patch\0"
    "setHermitePatchPointX\0setHermitePatchPointY\0"
    "setHermitePatchPointZ\0setHermitePatchPointUX\0"
    "setHermitePatchPointUY\0setHermitePatchPointUZ\0"
    "setHermitePatchPointVX\0setHermitePatchPointVY\0"
    "setHermitePatchPointVZ\0setHermitePatchPointTX\0"
    "setHermitePatchPointTY\0setHermitePatchPointTZ\0"
    "setSelectedPoint\0setHermiteArcPointX\0"
    "setHermiteArcPointY\0setHermiteArcPointZ\0"
    "setHermiteArcTangentPointX\0"
    "setHermiteArcTangentPointY\0"
    "setHermiteArcTangentPointZ\0"
    "setSelectedPointArc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cagd__GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      90,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  464,    2, 0x06 /* Public */,
       4,    1,  467,    2, 0x06 /* Public */,
       5,    1,  470,    2, 0x06 /* Public */,
       6,    1,  473,    2, 0x06 /* Public */,
       7,    1,  476,    2, 0x06 /* Public */,
       8,    1,  479,    2, 0x06 /* Public */,
       9,    1,  482,    2, 0x06 /* Public */,
      10,    1,  485,    2, 0x06 /* Public */,
      11,    1,  488,    2, 0x06 /* Public */,
      12,    1,  491,    2, 0x06 /* Public */,
      13,    1,  494,    2, 0x06 /* Public */,
      14,    1,  497,    2, 0x06 /* Public */,
      15,    1,  500,    2, 0x06 /* Public */,
      16,    1,  503,    2, 0x06 /* Public */,
      17,    1,  506,    2, 0x06 /* Public */,
      18,    1,  509,    2, 0x06 /* Public */,
      19,    1,  512,    2, 0x06 /* Public */,
      20,    1,  515,    2, 0x06 /* Public */,
      21,    1,  518,    2, 0x06 /* Public */,
      22,    1,  521,    2, 0x06 /* Public */,
      23,    1,  524,    2, 0x06 /* Public */,
      24,    1,  527,    2, 0x06 /* Public */,
      25,    1,  530,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      26,    1,  533,    2, 0x0a /* Public */,
      27,    1,  536,    2, 0x0a /* Public */,
      28,    1,  539,    2, 0x0a /* Public */,
      29,    1,  542,    2, 0x0a /* Public */,
      30,    1,  545,    2, 0x0a /* Public */,
      31,    1,  548,    2, 0x0a /* Public */,
      32,    1,  551,    2, 0x0a /* Public */,
      33,    1,  554,    2, 0x0a /* Public */,
      34,    1,  557,    2, 0x0a /* Public */,
      35,    1,  560,    2, 0x0a /* Public */,
      36,    1,  563,    2, 0x0a /* Public */,
      37,    1,  566,    2, 0x0a /* Public */,
      38,    1,  569,    2, 0x0a /* Public */,
      39,    1,  572,    2, 0x0a /* Public */,
      40,    1,  575,    2, 0x0a /* Public */,
      41,    1,  578,    2, 0x0a /* Public */,
      42,    1,  581,    2, 0x0a /* Public */,
      43,    1,  584,    2, 0x0a /* Public */,
      44,    1,  587,    2, 0x0a /* Public */,
      45,    1,  590,    2, 0x0a /* Public */,
      46,    1,  593,    2, 0x0a /* Public */,
      47,    1,  596,    2, 0x0a /* Public */,
      48,    1,  599,    2, 0x0a /* Public */,
      49,    1,  602,    2, 0x0a /* Public */,
      50,    1,  605,    2, 0x0a /* Public */,
      51,    1,  608,    2, 0x0a /* Public */,
      52,    1,  611,    2, 0x0a /* Public */,
      53,    1,  614,    2, 0x0a /* Public */,
      54,    1,  617,    2, 0x0a /* Public */,
      55,    1,  620,    2, 0x0a /* Public */,
      56,    1,  623,    2, 0x0a /* Public */,
      57,    1,  626,    2, 0x0a /* Public */,
      58,    1,  629,    2, 0x0a /* Public */,
      59,    1,  632,    2, 0x0a /* Public */,
      60,    1,  635,    2, 0x0a /* Public */,
      61,    1,  638,    2, 0x0a /* Public */,
      62,    1,  641,    2, 0x0a /* Public */,
      63,    1,  644,    2, 0x0a /* Public */,
      64,    1,  647,    2, 0x0a /* Public */,
      65,    1,  650,    2, 0x0a /* Public */,
      66,    1,  653,    2, 0x0a /* Public */,
      67,    1,  656,    2, 0x0a /* Public */,
      68,    1,  659,    2, 0x0a /* Public */,
      69,    1,  662,    2, 0x0a /* Public */,
      70,    1,  665,    2, 0x0a /* Public */,
      71,    1,  668,    2, 0x0a /* Public */,
      72,    1,  671,    2, 0x0a /* Public */,
      73,    1,  674,    2, 0x0a /* Public */,
      74,    1,  677,    2, 0x0a /* Public */,
      75,    1,  680,    2, 0x0a /* Public */,
      76,    1,  683,    2, 0x0a /* Public */,
      77,    1,  686,    2, 0x0a /* Public */,
      78,    1,  689,    2, 0x0a /* Public */,
      79,    1,  692,    2, 0x0a /* Public */,
      80,    1,  695,    2, 0x0a /* Public */,
      81,    1,  698,    2, 0x0a /* Public */,
      82,    1,  701,    2, 0x0a /* Public */,
      83,    1,  704,    2, 0x0a /* Public */,
      84,    1,  707,    2, 0x0a /* Public */,
      85,    1,  710,    2, 0x0a /* Public */,
      86,    1,  713,    2, 0x0a /* Public */,
      87,    1,  716,    2, 0x0a /* Public */,
      88,    1,  719,    2, 0x0a /* Public */,
      89,    1,  722,    2, 0x0a /* Public */,
      90,    1,  725,    2, 0x0a /* Public */,
      91,    1,  728,    2, 0x0a /* Public */,
      92,    1,  731,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void cagd::GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_parametric_first_derivatives_slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->set_parametric_second_derivatives_slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->set_cyclic_point_x_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->set_cyclic_point_y_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->set_cyclic_point_z_signal((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->HermitePatchPointChangeX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->HermitePatchPointChangeY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->HermitePatchPointChangeZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->HermitePatchPointChangeUX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->HermitePatchPointChangeUY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->HermitePatchPointChangeUZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->HermitePatchPointChangeVX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->HermitePatchPointChangeVY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->HermitePatchPointChangeVZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->HermitePatchPointChangeTX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->HermitePatchPointChangeTY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->HermitePatchPointChangeTZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->HermiteArcPointChangeX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->HermiteArcPointChangeY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->HermiteArcPointChangeZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->HermiteArcTangentChangeX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->HermiteArcTangentChangeY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->HermiteArcTangentChangeZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->set_tab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->set_angle_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->set_angle_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->set_angle_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->set_zoom_factor((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->set_trans_x((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->set_trans_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->set_trans_z((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->set_derivatives_scale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->set_parametric_first_derivatives((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->set_parametric_second_derivatives((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->set_texture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->set_texture_type((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->set_material((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->set_material_type((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->set_red((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 39: _t->set_blue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 40: _t->set_green((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 41: _t->set_selected_shader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->set_shader_scale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 43: _t->set_smooting_shader((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 44: _t->set_shader_parameter((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->show_patch_uip((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->show_patch_vip((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->insert_new_arc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->set_index_arc1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->set_index_arc2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->continue_arc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->delete_arc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->merge_arcs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 53: _t->set_direction_arc1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->set_direction_arc2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->join_arcs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->set_paint_selected_arc((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->set_paint_all_arcs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->continue_patch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->insert_new_patch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->set_index_patch1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 61: _t->set_index_patch2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: _t->set_direction_patch1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->set_direction_patch2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->join_patches((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->set_paint_selected_patch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->set_paint_all_patches((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->merge_patches((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 68: _t->show_normals((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 69: _t->delete_patch((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 70: _t->setHermitePatchPointX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 71: _t->setHermitePatchPointY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 72: _t->setHermitePatchPointZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 73: _t->setHermitePatchPointUX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 74: _t->setHermitePatchPointUY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 75: _t->setHermitePatchPointUZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 76: _t->setHermitePatchPointVX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 77: _t->setHermitePatchPointVY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 78: _t->setHermitePatchPointVZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 79: _t->setHermitePatchPointTX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 80: _t->setHermitePatchPointTY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 81: _t->setHermitePatchPointTZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 82: _t->setSelectedPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 83: _t->setHermiteArcPointX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 84: _t->setHermiteArcPointY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 85: _t->setHermiteArcPointZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 86: _t->setHermiteArcTangentPointX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 87: _t->setHermiteArcTangentPointY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 88: _t->setHermiteArcTangentPointZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 89: _t->setSelectedPointArc((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_parametric_first_derivatives_slot)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_parametric_second_derivatives_slot)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_cyclic_point_x_signal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_cyclic_point_y_signal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::set_cyclic_point_z_signal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeX)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeY)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeZ)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUX)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUY)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeUZ)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVX)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVY)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeVZ)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTX)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTY)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermitePatchPointChangeTZ)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcPointChangeX)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcPointChangeY)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcPointChangeZ)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcTangentChangeX)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcTangentChangeY)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::HermiteArcTangentChangeZ)) {
                *result = 22;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cagd::GLWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_cagd__GLWidget.data,
    qt_meta_data_cagd__GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cagd::GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cagd::GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cagd__GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int cagd::GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 90)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 90;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 90)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 90;
    }
    return _id;
}

// SIGNAL 0
void cagd::GLWidget::set_parametric_first_derivatives_slot(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cagd::GLWidget::set_parametric_second_derivatives_slot(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cagd::GLWidget::set_cyclic_point_x_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cagd::GLWidget::set_cyclic_point_y_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cagd::GLWidget::set_cyclic_point_z_signal(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void cagd::GLWidget::HermitePatchPointChangeX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void cagd::GLWidget::HermitePatchPointChangeY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void cagd::GLWidget::HermitePatchPointChangeZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void cagd::GLWidget::HermitePatchPointChangeUX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void cagd::GLWidget::HermitePatchPointChangeUY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void cagd::GLWidget::HermitePatchPointChangeUZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void cagd::GLWidget::HermitePatchPointChangeVX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void cagd::GLWidget::HermitePatchPointChangeVY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void cagd::GLWidget::HermitePatchPointChangeVZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void cagd::GLWidget::HermitePatchPointChangeTX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void cagd::GLWidget::HermitePatchPointChangeTY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void cagd::GLWidget::HermitePatchPointChangeTZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void cagd::GLWidget::HermiteArcPointChangeX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void cagd::GLWidget::HermiteArcPointChangeY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void cagd::GLWidget::HermiteArcPointChangeZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void cagd::GLWidget::HermiteArcTangentChangeX(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void cagd::GLWidget::HermiteArcTangentChangeY(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void cagd::GLWidget::HermiteArcTangentChangeZ(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
