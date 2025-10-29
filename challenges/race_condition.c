/*    ****  Pontificia Universidad Javeriana  **************************************
*    Autor: Angel Daniel Garcia Santana
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Demostración explícita de una condición de carrera. Múltiples hilos
*    acceden concurrentemente a una variable compartida sin mecanismos de sincronización,
*    lo que puede resultar en valores inconsistentes.
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

// Variable global compartida - objetivo de la condición de carrera
int acumulado = 0;

/**
 * Función que genera condición de carrera
 * Múltiples hilos acceden simultáneamente a 'acumulado'
 */
void *cuadrados(void *x) {
    int xi = (intptr_t)x;
    // CONDICIÓN DE CARRERA: Múltiples hilos leen-modifican-escriben simultáneamente
    acumulado += xi * xi;
    return NULL;
}

/**
 * Función principal
 * Crea 20 hilos que compiten por acceder a la variable 'acumulado'
 */
int main() {
    pthread_t hilos[20];
    
    // Crear 20 hilos que ejecutarán concurrentemente
    for(int i = 0; i < 20; i++){
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));
    }
    
    // Esperar a que todos los hilos terminen
    for(int i = 0; i < 20; i++){
        void *resultado;
        pthread_join(hilos[i], &resultado);
    }
    
    // El resultado puede ser inconsistente debido a la condición de carrera
    printf("Acumulado = %d\n", acumulado);
    return 0;
}
