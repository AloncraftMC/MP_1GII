#include <iostream>
#include "Course.h"

using namespace std;

int main(){

    const int NUM_CURSOS = 4;
    Course **cursos = new Course*[NUM_CURSOS];

    Course *fp = new Course("FP");
    Course *mp = new Course("MP");
    Course *cal = new Course("CAL");
    Course *ed = new Course("ED");

    cursos[0] = fp;
    cursos[1] = mp;
    cursos[2] = cal;
    cursos[3] = ed;

    Course *dependenciasFP[1] = {mp};
    fp->setRequisites(dependenciasFP, 1);

    Course *dependenciasED[2] = {fp, mp};
    ed->setRequisites(dependenciasED, 2);

    cal->setRequisites(nullptr, 0);

    // Muestro las asignaturas y sus dependencias

    cout << "Asignaturas: ";

    for(int i = 0; i < NUM_CURSOS; i++){

        cout << cursos[i]->getName();
        if(i < NUM_CURSOS - 1)  cout << ", ";
        
    }

    cout << endl << endl;
    cout << "Dependencias: " << endl;

    for(int i = 0; i < NUM_CURSOS; i++){

        Course* curso = cursos[i];
        string* dependencias = curso->mydeps(*curso);

        cout << curso->getName() << ": ";

        if(curso->getNumRequisites() == 0){

            cout << "Sin prerrequisitos.";

        }else{

            for(int j = 0; j < curso->getNumRequisites(); j++){

                cout << dependencias[j];
                if(j < curso->getNumRequisites() - 1) cout << ", ";

            }

        }

        cout << endl;
        delete[] dependencias;

    }

    // Libero memoria
    
    for(int i = 0; i < NUM_CURSOS; i++) delete cursos[i];

    delete[] cursos;

    return 0;

}