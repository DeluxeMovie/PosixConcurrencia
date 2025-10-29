/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana 
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Ejemplo avanzado de sincronización usando mutex y variables
*    de condición. Dos hilos incrementan un contador de manera coordinada:
*    un hilo trabaja en rangos específicos mientras el otro espera.
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Mutex y variable de condición para sincronización
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int count = 0;  // Contador compartido

#define COUNT_DONE 15   // Valor máximo del contador
#define COUNT_HALT1 4   // Límite inferior del rango de espera
#define COUNT_HALT2 11  // Límite superior del rango de espera

/**
 * Hilo 1: Incrementa el contador excepto en el rango [COUNT_HALT1, COUNT_HALT2]
 * En ese rango, espera a que el hilo 2 lo despierte
 */
void *count01() {
    for(;;){
        pthread_mutex_lock(&condition_mutex);
        // Esperar mientras el contador esté en el rango prohibido
        while(count >= COUNT_HALT1 && count <= COUNT_HALT2)
        {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);
        
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);
        
        if(count >= COUNT_DONE) return(NULL);
    }
}

/**
 * Hilo 2: Incrementa el contador principalmente en el rango [COUNT_HALT1, COUNT_HALT2]
 * y notifica al hilo 1 cuando sale de ese rango
 */
void *count02() {
    for(;;){
        pthread_mutex_lock(&condition_mutex);
        // Notificar al hilo 1 cuando el contador esté fuera del rango
        while(count < COUNT_HALT1 || count > COUNT_HALT2)
        {
            pthread_cond_signal(&condition_cond);
        }
        pthread_mutex_unlock(&condition_mutex);
        
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 02 <==: %d\n",count);
        pthread_mutex_unlock(&count_mutex);

        if(count >= COUNT_DONE) return(NULL);
    }
}

/**
 * Función principal
 */
int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &count01, NULL);
    pthread_create(&thread2, NULL, &count02, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    exit(0);
}
