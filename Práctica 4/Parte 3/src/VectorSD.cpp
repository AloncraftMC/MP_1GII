#include "VectorSD.h"

using namespace std;

VectorSD::VectorSD(int n){

    this->reservado = n;
    this->util = 0;

    this->info = new double[this->reservado];

}

VectorSD::~VectorSD(){

    delete[] this->info;
    this->info = nullptr;

}

void VectorSD::aniadir(double miInfo){

    if(this->util == this->reservado){

        double *aux = new double[this->reservado * 2];

        for(int i = 0; i < this->util; i++)  aux[i] = this->info[i];

        delete[] this->info;

        this->info = aux;
        this->reservado *= 2;

    }

    this->info[util] = miInfo;
    this->util++;

}

VectorSD *VectorSD::copiar() const{

    VectorSD *copia = new VectorSD(this->util);

    for(int i = 0; i < this->util; i++) copia->info[i] = this->info[i];

    copia->util = this->util;

    return copia;

}

void VectorSD::mostrar() const{

    cout << "Memoria reservada:\t" << this->reservado << endl << "Valores:\t";
    for(int i = 0; i < util; i++)   cout << this->info[i] << " ";

}