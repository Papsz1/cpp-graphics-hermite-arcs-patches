#pragma once

#include <QWidget>
#include "ui_SideWidget.h"

namespace cagd
{
    class SideWidget: public QWidget, public Ui::SideWidget
    {
    public:
        // special and default constructor
        SideWidget(QWidget *parent = 0);

    public slots:
        void set_cyclic_x_slot(double);
        void set_cyclic_y_slot(double);
        void set_cyclic_z_slot(double);
    };
}
