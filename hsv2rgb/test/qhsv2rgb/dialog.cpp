#include <stdint.h>

#include "dialog.h"
#include "ui_dialog.h"

#include <QColor>
#include <QObject>

#include "hsv2rgb.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    init_hsv2rgb();

    ui->setupUi(this);

    QObject::connect( ui->horizontalSlider_H, SIGNAL(valueChanged(int)),
                      this, SLOT(updateUi(int)) );
    QObject::connect( ui->horizontalSlider_S, SIGNAL(valueChanged(int)),
                      this, SLOT(updateUi(int)) );
    QObject::connect( ui->horizontalSlider_V, SIGNAL(valueChanged(int)),
                      this, SLOT(updateUi(int)) );

    pixmap = new QPixmap( ui->label_color->width(), ui->label_color->height() );

    ui->horizontalSlider_H->setValue( 127 );
    ui->horizontalSlider_S->setValue( 127 );
    ui->horizontalSlider_V->setValue( 127 );
}

Dialog::~Dialog()
{
    delete pixmap;
    delete ui;
}

void Dialog::updateUi( int value ) {
    uint8_t r, g, b;
    int16_t f, hi, p, q, t;
    int h, s, v;
    QColor color;

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

    /*  update pixmap   */
    color.setRgb( r, g, b );
    pixmap->fill( color );
    ui->label_color->setPixmap( *pixmap );
}
