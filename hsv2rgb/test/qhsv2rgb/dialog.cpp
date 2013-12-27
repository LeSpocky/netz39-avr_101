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
    uint8_t r, g, b;
    int16_t f, hi, p, q, t;
    int h, s, v;

    /*  get slider values   */
    h = ui->horizontalSlider_H->value();
    s = ui->horizontalSlider_S->value();
    v = ui->horizontalSlider_V->value();

    /*  calculate   */
    f = f8( h );
    hi = hi8( h );
    p = p8( v, s );
    q = q8( v, s, f );
    t = t8( v, s, f );

    rgb( h, s, v, &r, &g, &b );

    ui->lcdNumber_f->display( f );
    ui->lcdNumber_hi->display( hi );
    ui->lcdNumber_p->display( p );
    ui->lcdNumber_q->display( q );
    ui->lcdNumber_t->display( t );

    ui->lcdNumber_R->display( r );
    ui->lcdNumber_G->display( g );
    ui->lcdNumber_B->display( b );
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
