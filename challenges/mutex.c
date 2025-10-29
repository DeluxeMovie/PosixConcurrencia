/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Demostración del uso de mutex para proteger el acceso
*    a una variable compartida entre múltiples hilos. Cada hilo incrementa
*    un contador global de manera segura usando exclusión mutua.
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10

// Mutex para proteger el acceso a la variable compartida 'counter'
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;  // Variable global compartida

/**
 * Función ejecutada por cada hilo
 * @param arg Puntero al número del hilo
 */
void *thread_function(void *arg) {
    int i = *(int *)(arg);
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());
    
    // Sección crítica, protegida por mutex
    pthread_mutex_lock(&mutex1);
    counter++;  // Incremento seguro del contador
    pthread_mutex_unlock(&mutex1);
    
    return NULL;
}

/**
 * Función principal
 * 
 */
int main() {
    pthread_t thread_id[NTHREADS];
    int thread_nums[NTHREADS];  // CORRECCIÓN: Array separado para evitar condición de carrera
    int i;

    // Crear NTHREADS hilos
    for(i = 0; i < NTHREADS; i++)
    {
        thread_nums[i] = i;  // Asignar número único a cada hilo
        pthread_create(&thread_id[i], NULL, thread_function, &thread_nums[i]);
    }

    // CORRECCIÓN: Esperar a que todos los hilos terminen
    for(i = 0; i < NTHREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    printf("Final counter value: %d\n", counter);
    return 0;
}
