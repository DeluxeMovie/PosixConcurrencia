/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana 
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Implementación CORRECTA de variables de condición para
*    sincronizar dos hilos. Un hilo espera hasta que otro hilo modifica
*    una variable y lo notifica.
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

// Mecanismos de sincronización
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int valor = 100;        // Variable compartida
bool notificar = false; // Bandera de condición

/**
 * Hilo que reporta el valor - ESPERA hasta ser notificado
 * @param nousado No utilizado
 */
void *reportar(void *nousado) {
    // Adquirir el mutex antes de verificar la condición
    pthread_mutex_lock(&mutex);
    
    // Esperar mientras no haya notificación
    while(!notificar){
        pthread_cond_wait(&var_cond, &mutex);
    }
    
    // La condición se cumplió, imprimir el valor
    printf("El valor es: %d\n", valor);
    
    // Liberar el mutex
    pthread_mutex_unlock(&mutex);
    return NULL;
}

/**
 * Hilo que asigna un nuevo valor y NOTIFICA al hilo reportar
 * @param nousado No utilizado
 */
void *asignar(void *nousado){
    // Modificar el valor compartido
    valor = 20;
    
    // Adquirir el mutex para modificar la bandera y notificar
    pthread_mutex_lock(&mutex);
    notificar = true;           // Cambiar la condición
    pthread_cond_signal(&var_cond); // Despertar al hilo que espera
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

/**
 * Función principal
 * Crea y sincroniza dos hilos usando variables de condición
 */
int main(int argc, char *argv[]) {
    pthread_t reporte, asigne;
    
    // Crear los hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    // Esperar a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);
    
    return 0;
}
