/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Ejemplo INCOMPLETO de uso de variables de condición.
*    Demuestra la necesidad de sincronización pero no la implementa correctamente.
*    El hilo reportar puede imprimir el valor antes de que asignar lo modifique.
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

// Variables de condición y mutex (no utilizados completamente)
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int valor = 100;        // Variable compartida
bool notificar = false; // Bandera de notificación

/**
 * Hilo que reporta el valor - NO ESTÁ SINCRONIZADO CORRECTAMENTE
 */
void *reportar(void *nousado) {
    /*
    // CÓDIGO COMENTADO: Esta es la implementación correcta que debería usarse
    pthread_mutex_lock(&mutex);
    while(!notificar){
        pthread_cond_wait(&var_cond, &mutex);
    }
    */
    printf("El valor es: %d\n", valor);  // Puede imprimir 100 o 20 aleatoriamente
    /*
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}

/**
 * Hilo que asigna un nuevo valor - NO ESTÁ SINCRONIZADO CORRECTAMENTE
 */
void *asignar(void *nousado){
    valor = 20;
    /* 
    // CÓDIGO COMENTADO: Esta es la implementación correcta
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
    */
    return NULL;
}

/**
 * Función principal
 * Crea dos hilos sin garantizar el orden de ejecución
 */
int main(int argc, char *argv[]) {
    pthread_t reporte, asigne;
    
    // El orden de creación no garantiza el orden de ejecución
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    // Esperar a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);
    
    return 0;
}
