/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Calcula la suma de los cuadrados de los números del 1 al 20
*    utilizando 20 hilos. Cada hilo calcula el cuadrado de un número y lo suma
*    a una variable global compartida. ¡ADVERTENCIA: Este código tiene condición
*    de carrera al acceder a la variable 'acumulado'!
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

// Variable global compartida entre todos los hilos
int acumulado = 0;

/**
 * Función ejecutada por cada hilo
 * Calcula el cuadrado de un número y lo suma a la variable acumulado
 * @param x Puntero al número que se va a elevar al cuadrado
 */
void *cuadrados(void *x)
{
    // Convertimos el puntero void* a int de manera segura
    int xi = (intptr_t)x;
    acumulado += xi * xi;
    return NULL;
}

/**
 * Función principal
 * Crea 20 hilos para calcular la suma de cuadrados del 1 al 20
 */
int main()
{
    pthread_t hilos[20];  // Array para almacenar los identificadores de los hilos
    
    // Crear 20 hilos, cada uno calcula el cuadrado de un número diferente
    for (int i = 0; i < 20; i++)
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));

    // Esperar a que todos los hilos terminen su ejecución
    for (int i = 0; i < 20; i++)
    {
        void *resultado;
        pthread_join(hilos[i], &resultado);
    }
    
    // Imprimir el resultado final
    printf("Suma de cuadrados = %d\n", acumulado);

    return 0;
}
