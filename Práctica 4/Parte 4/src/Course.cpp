#include "Course.h"

using namespace std;

string *Course::mydeps(const Course &course){

    string *resultado = new string[course.getNumRequisites()];

    for(int i = 0; i < course.getNumRequisites(); i++)  resultado[i] = course.getRequisites()[i]->getName();

    return resultado;

}