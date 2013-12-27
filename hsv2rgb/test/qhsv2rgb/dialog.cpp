#include <stdint.h>

#include "dialog.h"
#include "ui_dialog.h"

#include "hsv2rgb.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateUi( void ) {
    int16_t f;
    int h, s, v;

    /*  get slider values   */
    h = ui->horizontalSlider_H->value();
    s = ui->horizontalSlider_S->value();
    v = ui->horizontalSlider_V->value();

    f = f8( h );

    ui->lcdNumber_f->display( f );
}

void Dialog::on_horizontalSlider_H_valueChanged(int value)
{
    updateUi();
}

void Dialog::on_horizontalSlider_S_valueChanged(int value)
{
    updateUi();
}

void Dialog::on_horizontalSlider_V_valueChanged(int value)
{
    updateUi();
}
