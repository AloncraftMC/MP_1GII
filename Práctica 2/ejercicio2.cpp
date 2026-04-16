/**
 * @file Práctica 2 - Ejercicio 2
 * @author Alonso Hernández Robles (F1)
 */

#include <iostream>

using namespace std;

void trim(char array[]){

    int longitud = 0;

    while(array[longitud] != '\0')  longitud++;

    int posicionInicial = 0;
    int posicionFinal = longitud - 1;
 
    while(array[posicionInicial] == ' ' || array[posicionInicial] == '\t')  posicionInicial++;
    while(array[posicionFinal] == ' ' || array[posicionFinal] == '\t')  posicionFinal--;

    longitud = posicionFinal - posicionInicial;

    for(int i = 0; i <= longitud; i++)   array[i] = array[i + posicionInicial];

    array[longitud + 1] = '\0';

}

int split(const char cad[], char palabras[][50], char delimitador){

    int i = 0;
    int indice = 0;
    int numeroPalabras = 0;

    while(cad[i] != '\0'){

        if(cad[i] != delimitador){

            palabras[numeroPalabras][indice] = cad[i];
            indice++;

        }else{

            numeroPalabras++;
            indice = 0;

        }

        i++;

    }

    if(cad[i - 1] != delimitador)   numeroPalabras++;

    return numeroPalabras;

}

bool isPalindromeIgnoreCase(const char array[]){

    bool resultado = true;
    int longitudTotal = 0;

    while(array[longitudTotal] != '\0') longitudTotal++;

    char formateada[longitudTotal];
    int longitud = 0;

    for(int i = 0; i < longitudTotal; i++){

        if(array[i] != ' ' && array[i] != '.' && array[i] != ','){
            
            char minuscula = array[i];

            if(array[i] >= 'A' && array[i] <= 'Z')  minuscula = array[i] - 'A' + 'a';

            formateada[longitud] = minuscula;
            longitud++;

        }

    }

    for(int i = 0; i < longitud / 2 && resultado; i++){

        if(formateada[i] != formateada[longitud - i - 1])   resultado = false;

    }

    return resultado;

}

int main(){

    /* 1. Función trim() */

    char cadena1[] = "   hola mundo  ";

    cout << "=== 1. Función trim() ===" << endl;
    cout << "Entrada: \"" << cadena1 << "\"" << endl;

    trim(cadena1);

    cout << "Salida: \"" << cadena1 << "\"" << endl;
    cout << endl;

    /* 2. Función split() */

    char cadena2[] = "uno,dos,tres";
    char palabras[100][50];

    cout << "=== 2. Función split() ===" << endl;
    cout << "Entrada: \"" << cadena2 << "\"" << endl;

    int numeroPalabras = split(cadena2, palabras, ',');

    cout << "Salida: ";
    
    for(int i = 0; i < numeroPalabras; i++){
        
        cout << "\"" << palabras[i] << "\"";

        if(i < numeroPalabras - 1) cout << ", ";

    }

    cout << endl;
    cout << "Número de palabras: " << numeroPalabras << endl;
    cout << endl;

    /* 3. Función isPalindromeIgnoreCase() */

    char ejemplo1[] = "Anita lava la tina";
    char ejemplo2[] = "Dabale arroz a la zorra el abad";
    char ejemplo3[] = "Programacion";

    cout << "=== 3. Función isPalindromeIgnoreCase() ===" << endl;
    cout << "Ejemplo 1: \"" << ejemplo1 << "\"\t-> " << (isPalindromeIgnoreCase(ejemplo1) ? "true" : "false") << endl;
    cout << "Ejemplo 2: \"" << ejemplo2 << "\"\t-> " << (isPalindromeIgnoreCase(ejemplo2) ? "true" : "false") << endl;
    cout << "Ejemplo 3: \"" << ejemplo3 << "\"\t-> " << (isPalindromeIgnoreCase(ejemplo3) ? "true" : "false") << endl;
    cout << endl;

    return 0;

}