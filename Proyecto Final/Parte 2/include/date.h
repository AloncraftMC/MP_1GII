/**
 * @file date.h
 * @author Alonso Hernández Robles (F1)
 * @brief Declaración de la clase Date.
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

/**
 * @class Date
 * @brief Representa una fecha con día, mes y año.
 */
class Date {

    private:

        int day;    ///< Día (1-31)
        int month;  ///< Mes (1-12)
        int year;   ///< Año (ej. 2026)

    public:

        // CONSTRUCTORES

        /**
         * @brief Constructor por defecto.
         */
        Date();

        /**
         * @brief Constructor con parámetros.
         * @param day Día
         * @param month Mes
         * @param year Año
         */
        Date(int day, int month, int year);

        /**
         * @brief Obtiene el día.
         * @return Día.
         */
        inline int getDay() const { return this->day; }

        /**
         * @brief Obtiene el mes.
         * @return Mes.
         */
        inline int getMonth() const { return this->month; }

        /**
         * @brief Obtiene el año.
         * @return Año.
         */
        inline int getYear() const { return this->year; }

        /**
         * @brief Establece el día.
         * @param day Día.
         */
        inline void setDay(int day) { this->day = day; }

        /**
         * @brief Establece el mes.
         * @param month Mes.
         */
        inline void setMonth(int month) { this->month = month; }

        /**
         * @brief Establece el año.
         * @param year Año.
         */
        inline void setYear(int year) { this->year = year; }

        // SOBRECARGAS DE OPERADORES

        /**
         * @brief Sobrecarga del operador de igualdad.
         * @param date Fecha a comparar.
         * @return true si las fechas son iguales, false en caso contrario.
         */
        inline bool operator==(const Date& date) const {
            return this->day == date.day &&
                   this->month == date.month &&
                   this->year == date.year;
        }

        /**
         * @brief Sobrecarga del operador de desigualdad.
         * @param date Fecha a comparar.
         * @return true si las fechas son diferentes, false en caso contrario.
         */
        inline bool operator!=(const Date& date) const { return !(*this == date); }

        /**
         * @brief Sobrecarga del operador de comparación menor que.
         * @param date Fecha a comparar.
         * @return true si esta fecha es anterior a la fecha dada, false en caso contrario.
         */
        bool operator<(const Date& date) const;

        /**
         * @brief Sobrecarga del operador de comparación mayor que.
         * @param date Fecha a comparar.
         * @return true si esta fecha es posterior a la fecha dada, false en caso contrario.
         */
        inline bool operator>(const Date& date) const { return date < *this; }

        /**
         * @brief Sobrecarga del operador de comparación mayor o igual que.
         * @param date Fecha a comparar.
         * @return true si esta fecha es posterior o igual a la fecha dada, false en caso contrario.
         */
        inline bool operator>=(const Date& date) const { return !(*this < date); }

        /**
         * @brief Sobrecarga del operador de comparación menor o igual que.
         * @param date Fecha a comparar.
         * @return true si esta fecha es anterior o igual a la fecha dada, false en caso contrario.
         */
        inline bool operator<=(const Date& date) const { return !(date < *this); }

};

/**
 * @brief Sobrecarga del operador de inserción para imprimir una fecha en formato dd/mm/yyyy.
 * @param flujo Flujo de salida.
 * @param date Fecha a imprimir.
 * @return Referencia al flujo de salida.
 */
inline ostream& operator<<(ostream& flujo, const Date& date){
    
    return flujo << (date.getDay() < 10 ? "0" : "")         // Mostrar 0 si d < 10
                 <<  date.getDay() << "/"                   // Día (-> dd)
                 << (date.getMonth() < 10 ? "0" : "")       // Mostrar 0 si m < 10
                 <<  date.getMonth() << "/"                 // Mes (-> mm)
                 << (date.getYear() < 10 ? "0" : "")        // Mostrar 0 si y < 10
                 << (date.getYear() < 100 ? "0" : "")       // Mostrar 0 si y < 100
                 << (date.getYear() < 1000 ? "0" : "")      // Mostrar 0 si y < 1000
                 <<  date.getYear();                        // Año (-> yyyy)

}

#endif