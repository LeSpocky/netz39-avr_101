#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_horizontalSlider_H_valueChanged(int value);
    void on_horizontalSlider_S_valueChanged(int value);
    void on_horizontalSlider_V_valueChanged(int value);

private:
    Ui::Dialog *ui;
    void updateUi( void );
};

#endif // DIALOG_H
