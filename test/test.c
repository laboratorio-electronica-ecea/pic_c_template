#define TEST_IMP
#include <xc.h>
#include <stdio.h>
#include <pthread.h>

void user_main   ( void );
int  test        ( void );
void setup_memory( void );

static void* test_helper( void *ptr ) {
    return (void*) test();
}

static void* user_main_helper( void *ptr ) {
    user_main();
}

/**
 * @brief Esta función reemplaza al punto de entrada original del proyecto
 * 
 * Crea dos threads, uno para el programa de usuario y otro para el programa
 * de pruebas.
 * Termina cuando el thread de pruebas finalice. No espera al programa de 
 * usuario porque este tiene un loop infinito.
 * 
 * @return int  Devuelve 0 si las pruebas fueron exitosas, distinto de 0
 *              si hubo un error.
 */
int main( void ) {
    pthread_t test_thread;
    pthread_t main_thread;

    int ret1, ret2, result;

    setup_memory();
    
    ret1 = pthread_create( &test_thread, NULL, test_helper, NULL);
    ret2 = pthread_create( &main_thread, NULL, user_main_helper, NULL);

    pthread_join( test_thread, (void *)&result );

    if( result == 0 ) {
        printf("Test successful\n");
    } else {
        printf("Test failed\n");
    }
    
    return result;
}

/**
 * @brief Configuración de memoria después del reset
 * 
 */
void setup_memory( void ) {
    PORTA = 0xFF;
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
    PORTE = 0xFF;

    INTCON = 0x00;
}

/**
 * @brief Pruebas de funcionamiento
 * 
 * @return int  Devuelve 0 si las pruebas fueron exitosas, distinto de 0
 *              si hubo un error.
 */
int test( void ) {

    __delay_ms(200);
    if( PORTEbits.RE2 != 0 ) {      // Verifico que el LED1 esté apagado
        return 1;
    }

    __delay_ms(10);
    PORTBbits.RB0 = 0;              // Presiono la TEC1
    
    __delay_ms(10);
    if( PORTEbits.RE2 != 1 ) {      // Verifico que el LED1 esté encendido
        return 1;
    }

    return 0;
}