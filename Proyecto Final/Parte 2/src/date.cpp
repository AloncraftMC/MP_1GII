/**
 * @file date.cpp
 * @author Alonso Hernández Robles (F1)
 * @brief Implementación de la clase Date.
 */

#include "date.h"

/**
 * @brief Constructor por defecto.
 */
Date::Date(){

    this->day = 01;
    this->month = 01;
    this->year = 1900;

}

/**
 * @brief Constructor con parámetros.
 * @param day Día (1-31)
 * @param month Mes (1-12)
 * @param year Año (ej. 2026)
 */
Date::Date(int day, int month, int year){

    this->day = day;
    this->month = month;
    this->year = year;

}

/**
 * @brief Sobrecarga del operador de comparación menor que.
 * @param date Fecha a comparar.
 * @return true si esta fecha es anterior a la fecha dada, false en caso contrario.
 */
bool Date::operator<(const Date& date) const {

    if(this->year != date.year)     return this->year < date.year;
    if(this->month != date.month)   return this->month < date.month;
    return this->day < date.day;

}