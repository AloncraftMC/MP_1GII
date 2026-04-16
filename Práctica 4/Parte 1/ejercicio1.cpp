#include <iostream>

using namespace std;

int main(){

    int numPalabras;
    string *vector;

    do{

        cout << "¿Cuántas palabras vas a escribir? ";
        cin >> numPalabras;

    }while(numPalabras <= 0);

    // Reservo memoria

    vector = new string[numPalabras];

    // Leo las palabras

    for(int i = 0; i < numPalabras; i++){

        cout << "Palabra " << i+1 << ": ";
        cin >> vector[i];

    }

    // Escribo las palabras

    for(int i = numPalabras - 1; i >= 0; i--) cout << "Palabra " << i+1 << ": " << vector[i] << endl;

    // Libero memoria

    delete[] vector;
    vector = nullptr;

    return 0;

}