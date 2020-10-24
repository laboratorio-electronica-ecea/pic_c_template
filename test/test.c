#define TEST_IMP
#include <xc.h>
#include <stdio.h>
#include <pthread.h>

void user_main   ( void );
void setup_memory( void );
int  test        ( void );
int  test_config ( void );

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
int main( int arc, char *arcv[] ) {
    pthread_t test_thread;
    pthread_t main_thread;

    int ret1, ret2, result;

    setup_memory();
    
    ret1 = pthread_create( &test_thread, NULL, test_helper, NULL);
    ret2 = pthread_create( &main_thread, NULL, user_main_helper, NULL);

    pthread_join( test_thread, (void *)&result );

    if( result == 0 ) {
        printf("¡Felicitaciones! Las pruebas automáticas fueron exitosas.\n");
    } else {
        printf("Las pruebas automáticas fallaron, por favor revisa el código.\n");
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

    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
    TRISD = 0xFF;
    TRISE = 0xFF;

    INTCON = 0x00;
    ANSEL = 0xFF;
    ANSELH = 0xFF;
}

/**
 * @brief Pruebas de funcionamiento
 * 
 * @return int  Devuelve 0 si las pruebas fueron exitosas, distinto de 0
 *              si hubo un error.
 */
int test( void ) {

    __delay_ms(200);
    if( test_config() != 0 ) {
        return 1;
    }

    __delay_ms(10);
    PORTBbits.RB0 = 0;              // Presiono la TEC1
    __delay_ms(100);
    PORTBbits.RB0 = 1;              // Suelto la TEC1
    
    __delay_ms(10);
    if( PORTEbits.RE2 != 1 ) {
        printf("LED1 no queda encendido después de presionar la TEC1.\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Pruebas de configuración inicial de registros
 * 
 * @return int  Devuelve 0 si las pruebas fueron exitosas, distinto de 0
 *              si hubo un error.
 */
int test_config( void ) {
    int ret_value = 0;

    if( ANSELHbits.ANS12 != 0 ) {
        printf("TEC1 está configurado como entrada analógica.\n");
        ret_value = 1;
    }

    if( ANSELbits.ANS7 != 0 ) {
        printf("LED1 está configurado como entrada analógica.\n");
        ret_value = 1;
    }
    
    if( TRISEbits.TRISE2 != 0 ) {
        printf("LED1 no está configurado como salida.\n");
        ret_value = 1;
    }

    if( TRISBbits.TRISB0 != 1 ) {
        printf("TEC1 no está configurado como entrada.\n");
        ret_value = 1;
    }

    if( PORTEbits.RE2 != 0 ) {
        printf("LED1 no queda apagado al inicio.\n");
        ret_value = 1;
    }

    return ret_value;
}