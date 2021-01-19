#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_cmdCalcular_released();
    void guardar();
    void abrir();

    void on_actionAcerca_de_Salarios_triggered();
    float limpiar();

private:
    Ui::Principal *ui;
};
#endif // PRINCIPAL_H
