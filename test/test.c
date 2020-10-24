#define TEST_IMP
#include <xc.h>
#include <stdio.h>
#include <pthread.h>

/**
 * @brief Macro para simular rebotes mecánicos en un gpio
 * 
 * Al finalizar termina en el estado opuesto al inicial.
 * 
 * @param pin       GPIO seleccionado
 * @param times     Cantidad de rebotes
 */
#define gpio_toggle_bounce(pin, times)  \
    for (int gpio_i = 0; gpio_i < (times * 2) + 1; gpio_i++) { pin = !pin; __delay_ms(3); }    

#define PIN_LED1    PORTEbits.RE2
#define TRIS_LED1   TRISEbits.TRISE2
#define ANS_LED1    ANSELbits.ANS7

#define PIN_TEC1    PORTBbits.RB0
#define TRIS_TEC1   TRISBbits.TRISB0
#define ANS_TEC1    ANSELHbits.ANS12

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
    ANSEL  = 0xFF;
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

    PIN_TEC1 = 1;

    for( int i = 0 ; i < 5 ; i++ ) {
        __delay_ms(100);
        gpio_toggle_bounce(PIN_TEC1, i);
        __delay_ms(100);
        gpio_toggle_bounce(PIN_TEC1, i);

        __delay_ms(100);
        if( PIN_LED1 == i%2 ) {
            printf(
                "El LED1 no queda %s después de presionar la TEC1 por %d° vez.\n",
                i%2 == 0 ? "encendido" : "apagado",
                i+1
            );
            return 1;
        }
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

    if( ANS_TEC1 != 0 ) {
        printf("La TEC1 está configurada como entrada analógica.\n");
        ret_value = 1;
    }

    if( TRIS_TEC1 != 1 ) {
        printf("La TEC1 no está configurada como entrada.\n");
        ret_value = 1;
    }

    if( ANS_LED1 != 0 ) {
        printf("El LED1 está configurado como entrada analógica.\n");
        ret_value = 1;
    }
    
    if( TRIS_LED1 != 0 ) {
        printf("El LED1 no está configurado como salida.\n");
        ret_value = 1;
    }

    if( PIN_LED1 != 0 ) {
        printf("El LED1 no queda apagado al inicio.\n");
        ret_value = 1;
    }

    return ret_value;
}