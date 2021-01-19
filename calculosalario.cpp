#include "calculosalario.h"

float CalculoSalario::salario() const
{
    return m_salario;
}

float CalculoSalario::descuento() const
{
    return m_descuento;
}

float CalculoSalario::salarioNeto() const
{
    return m_salarioNeto;
}



CalculoSalario::CalculoSalario(QObject *parent) : QObject(parent)
{
}

CalculoSalario::CalculoSalario(QString nombre, int horas, char jornada) : QObject(nullptr)
{

    this->m_nombre = nombre;
    this->m_horas = horas;
    this->m_jornada = jornada;
}

void CalculoSalario::calcular()
{
    float valorHora = 0;
    switch (this->m_jornada) {
    case 'v':
        valorHora = VALOR_HORA_VESPERTINO;
        break;
    case 'm':
        valorHora = VALOR_HORA_MATUTINO;
        break;
    case 'n':
        valorHora = VALOR_HORA_NOCTURNO;
        break;
    default:
        break;
    }

    int extra = 0;
    if(m_horas > 40){
        extra = m_horas -40;
        m_horas=40;
    }
    m_salario = m_horas * valorHora +(extra* HORA_EXTRA) ;
    m_descuento = m_salario * PORCENTAJE_DESCUENTO / 100;
    m_salarioNeto = m_salario - m_descuento;
}
