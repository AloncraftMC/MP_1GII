#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date {

    private:

        int day;
        int month;
        int year;

    public:

        Date();
        Date(int day, int month, int year);

        inline int getDay() const   { return this->day; }
        inline int getMonth() const { return this->month; }
        inline int getYear() const  { return this->year; }

        inline void setDay(int day)     { this->day = day; }
        inline void setMonth(int month) { this->month = month; }
        inline void setYear(int year)   { this->year = year; }

        inline bool operator==(const Date& date) const {
            return this->day == date.day &&
                   this->month == date.month &&
                   this->year == date.year;
        }
        inline bool operator!=(const Date& date) const { return !(*this == date); }
               bool operator< (const Date& date) const;
        inline bool operator> (const Date& date) const { return date < *this; }
        inline bool operator>=(const Date& date) const { return !(*this < date); }
        inline bool operator<=(const Date& date) const { return !(date < *this); }

};

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