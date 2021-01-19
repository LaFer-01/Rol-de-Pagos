#include "principal.h"
#include "ui_principal.h"
#include "about.h"

#include <QDebug>
#include <QFileDialog>

#include "calculosalario.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    connect(ui->actionCalcular, SIGNAL(triggered(bool)),
            this, SLOT(on_cmdCalcular_released()));
    //Conexion para guardar presionando en el MENU guardar
    connect(ui->actionGuardar, SIGNAL(triggered(bool)),
            this, SLOT(guardar()));
    //Conexion para guardar presionando el BOTON guardar
    connect(ui->btnGuardar, SIGNAL(clicked(bool)),
            this, SLOT(guardar()));
    connect(ui->actionAbrir, SIGNAL(triggered(bool)),
            this, SLOT(abrir()));
    connect(ui->btnAbrir, SIGNAL(clicked(bool)),
            this, SLOT(abrir()));

}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_cmdCalcular_released()
{
    /*qDebug()<<"Calcular!";
    CalculoSalario calculo( "Juan", 47, 'v');
    calculo.calcular();
    qDebug() << calculo.salario() <<calculo.descuento() << calculo.salarioNeto();
*/
    //Obtener datos de la UI

    QString nombre = this->ui->inNombre->text();
    int horas = this->ui->inHoras->value();
    if (nombre == "" || horas == 0){
            ui->statusbar->showMessage("No se han ingresado datos para calcular.",5000);
            return;
        }else{
            ui->statusbar->clearMessage();
        }

    char jornada = 'm';

    if ( this->ui->inMatutino->isChecked()){
        jornada = 'm';
    }else if(this->ui->inVespertino->isChecked()){
        jornada = 'v';
    }else{
        jornada = 'n';
    }

   // qDebug() << "Jornada:" <<jornada;

    //Crear el objeto para calcular

    CalculoSalario rolPagos(nombre, horas, jornada);
    rolPagos.calcular();
    //qDebug() << rolPagos.salario() << rolPagos.descuento() << rolPagos.salarioNeto();

    // Imprimir resultados en la ventana outResultados
           QString resultado = "\nObrero: " + nombre + "\n " ;
           resultado += "\nSalario: $ " + QString::number(rolPagos.salario()) + "\n " ;
           resultado += "\nDescuento (9.5%): $ " + QString::number(rolPagos.descuento()) + "\n " ;
           resultado += "\nSalario neto: $ " + QString::number(rolPagos.salarioNeto()) + "\n" ;
           resultado += " --------------------------------------------------------\n " ;

           ui-> outResultado -> appendPlainText (resultado);

           limpiar();

}

void Principal::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                          "Guardar datos", QDir::home().absolutePath(), "Archivo de texto (*.txt)");
       QFile data(fileName);

       if (data.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream salida(&data);
           salida << ui->outResultado->toPlainText();
           ui->statusbar->showMessage("Datos almacenados en " + fileName,5000);
       }

       data.close();
}

void Principal::abrir()
{
    QString archivo = QFileDialog::getOpenFileName(this, "Abrir archivo",
                                                   "C:","Salario (*.txt)");
    QFile file(archivo);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList datos;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        datos << linea;
    }

    QStringList nombre = datos[0].split(":");
    QStringList horas = datos[1].split(":");
    /*QStringList mat = datos[2].split(":");
    QStringList ves = datos[3].split(":");
    QStringList noc = datos[4].split(":");*/

    ui->inNombre->setText(nombre[0]);
    ui->inHoras->setValue(horas[1].toInt());

    /*ui->inMatutino->setChecked(mat[2].toInt());
    ui->inVespertino->setChecked(ves[3].toInt());
    ui->inNocturno->setChecked(noc[4].toInt());*/


   qDebug()<<datos;
}

void Principal::on_actionAcerca_de_Salarios_triggered()
{
    About *about1 = new About;
    about1->show();
}

float Principal::limpiar()
{
        ui->inNombre->setText("");
        ui->inHoras->setValue(0);
        ui->inMatutino->setChecked(true);
        ui->inNombre->setFocus();

}
