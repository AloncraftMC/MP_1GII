/**
 * @file Práctica 3 - Ejercicio 1
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

    int var = 10;
    int *p1, *p2;

    // Cambiar el valor de la variable var usando p1

    cout << "1. Cambiar el valor de la variable var usando p1" << endl;
    cout << "var antes:\t" << var << endl;

    p1 = &var;
    *p1 = 20;

    cout << "var después:\t" << var << endl;
    cout << endl;

    // Inicializa p2 para que apunte a la misma direccion que p1

    cout << "2. Inicializa p2 para que apunte a la misma direccion que p1" << endl;
    
    p2 = p1;

    cout << "*p2:\t" << *p2 << " (igual que *p1)" << endl;
    cout << endl;

    // Modifica el valor de var usando p2

    cout << "3. Modifica el valor de var usando p2" << endl;
    cout << "var antes:\t" << var << endl;

    *p2 = 30;

    cout << "var después:\t" << var << endl;
    cout << endl;

    // Comprueba en un If si el valor apuntado por p1 es igual al de p2

    cout << "4. Comprueba en un If si el valor apuntado por p1 es igual al de p2" << endl;

    if(*p1 == *p2)  cout << "Sí: El valor apuntado por p1 es igual al de p2" << endl;
    cout << endl;

    return 0;

}