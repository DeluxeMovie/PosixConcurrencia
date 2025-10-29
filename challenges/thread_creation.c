/*    ****  Pontificia Universidad Javeriana  ****
*    Autor: Angel Daniel Garcia Santana
*    Fecha: 28 de Octubre de 2025
*    Materia: Sistemas Operativos
*    Docente: John Corredor
*    Descripción: Ejemplo básico de creación de hilos. Dos hilos independientes
*    imprimen mensajes diferentes demostrando la ejecución concurrente.
*********************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Función que ejecuta cada hilo
 * @param ptr Puntero al mensaje que debe imprimir el hilo
 */
void *print_message_function(void *ptr){
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
    return NULL;
}

/**
 * Función principal
 * CORREGIDO: Se cambió void main() por int main() y se agregó return
 */
int main(){
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;
    
    /* Crear hilos independientes que ejecutarán la función */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

    // Esperar a que los hilos terminen antes de que el main finalice
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    
    return 0;
}
