#include "date.h"

Date::Date(){

    this->day = 01;
    this->month = 01;
    this->year = 1900;

}

Date::Date(int day, int month, int year){

    this->day = day;
    this->month = month;
    this->year = year;

}

bool Date::operator<(const Date& date) const {

    if(this->year != date.year)     return this->year < date.year;
    
    if(this->month != date.month)   return this->month < date.month;
    
    return this->day < date.day;

}