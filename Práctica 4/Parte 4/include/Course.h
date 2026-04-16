#ifndef COURSE_H
#define COURSE_H

#include <iostream>

using namespace std;

class Course{

private:

    string name;
    Course **requisites;    // Vector dinámico de punteros a objetos Course
    int num_requisites;

public:

    Course(string n) : name(n), requisites(nullptr), num_requisites(0) {}

    // Métodos de acceso y modificación

    void setRequisites(Course **reqs, int n){

        this->requisites = reqs;
        this->num_requisites = n;

    }

    string getName() const { return name; }

    int getNumRequisites() const { return num_requisites; }

    Course **getRequisites() const { return requisites; }

    /**
     * @brief Devuelve un vector dinámico con los nombres de los prerrequisitos.
     * @param course Referencia al curso a consultar.
     * @return Puntero a un array de strings (debe ser liberado por el usuario).
     */
    string *mydeps(const Course &course);

};

#endif