// Threads.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>


//Creamos una funcion que recibe un arreglo, el tamaño de celdas para el arreglo, 
//y el minimo y maximo para llenarlo con numeros aleatorios
void generateRandomArray(int arr[], int size, int min, int max) {
    for (int i = 0; i < size; ++i) {
        arr[i] = min + rand() % (max - min + 1);
    }
}


int main() {


    std::srand(std::time(0)); // Seed for random number generation

    #ifdef _OPENMP
        std::cout << "OMP disponible y funcionando ";
        std::cout << std::endl;
    #endif


    //Declaramos el tamaño de los arreglos de entrada y el arreglo de resultados
    const int SIZE = 10000;
    int arregloA[SIZE];
    int arregloB[SIZE];
    int arregloR[SIZE];
    int total_hilos;


    //Genereamos los arreglos A y B con números aleatorios del 1 al 100
    generateRandomArray(arregloA, SIZE, 1, 100);
    generateRandomArray(arregloB, SIZE, 1, 100);

    //Mostramos la medida de los arreglos como información
    std::cout << "Medida de los arreglos: " << SIZE;
    std::cout << std::endl;
    std::cout << std::endl;

    //Imprimimos los primeros 10 y últimos 10 registros del arreglo A
    std::cout << "Arreglo A: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arregloA[i] << " ";
    }
    std::cout << " ..... ";
    for (int i = SIZE-10; i < SIZE; ++i) {
        std::cout << arregloA[i] << " ";
    }
    std::cout << std::endl;

    //Imprimimos los primeros 10 y últimos 10 registros del arreglo B
    std::cout << "Arreglo B: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arregloB[i] << " ";
    }
    std::cout << " ..... ";
    for (int  i = SIZE - 10; i < SIZE; ++i) {
        std::cout << arregloB[i] << " ";
    }
    std::cout << std::endl;

    

    std::cout <<"Cuantos hilos quieres utilizar? " << std::endl;
    std::cin >> total_hilos;

    #pragma omp parallel num_threads(total_hilos)
    {   
        //Obtenemos el hilo actual
        int nt = omp_get_thread_num();

        //Realizamos la suma de la celda del arreglo dependiendo del hilo que se este usando
        for (int i = nt; i < SIZE; i = i + total_hilos) {
            arregloR[i] = arregloA[i] + arregloB[i];
        }
        
    }
    

        /*
        //Realizamos la suma de la primer mitad del arreglo con el primer hilo
        if (i == 0) {
            //Llenamos el arreglo R (resultados) con la suma de los arreglos A y B
            for (int i = 0; i < SIZE/2; i++) {
                arregloR[i] = arregloA[i] + arregloB[i];
            }
        }

        //Realizamos la suma de la segunda mitad del arreglo con el segundo hilo
        else if (i == 1) {            
            //Llenamos el arreglo R (resultados) con la suma de los arreglos A y B
            for (int i = 10; i < SIZE; i++) {
                arregloR[i] = arregloA[i] + arregloB[i];
            }
        } */




    std::cout << "----------------------------------------------------------------------------------------";
    std::cout << std::endl;

    //Imprimimos los primeros 10 y últimos 10 registros del arreglo de resultados
    std::cout << "Arreglo R: ";
    for (int i = 0; i < 10; i++) {
        std::cout << arregloR[i] << " ";
    }
    std::cout << " ..... ";
    for (int i = SIZE - 10; i < SIZE; i++) {
        std::cout << arregloR[i] << " ";
    }

    std::cout << std::endl;


    return 0;
}