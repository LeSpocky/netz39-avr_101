#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPixmap>

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
    void updateUi( int value );

private:
    Ui::Dialog *ui;
    QPixmap *pixmap;
};

#endif // DIALOG_H
