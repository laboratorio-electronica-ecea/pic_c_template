#define TEST_IMP
#include <xc.h>

volatile STATUSbits_t STATUSbits;
volatile INTCONbits_t INTCONbits;
volatile ANSELbits_t  ANSELbits  = { .byte = 0xFF };
volatile ANSELHbits_t ANSELHbits = { .byte = 0xFF };
volatile PORTAbits_t  PORTAbits  = { .byte = 0xFF };
volatile TRISAbits_t  TRISAbits  = { .byte = 0xFF };
volatile PORTBbits_t  PORTBbits  = { .byte = 0xFF };
volatile TRISBbits_t  TRISBbits  = { .byte = 0xFF };
volatile PORTCbits_t  PORTCbits  = { .byte = 0xFF };
volatile TRISCbits_t  TRISCbits  = { .byte = 0xFF };
volatile PORTDbits_t  PORTDbits  = { .byte = 0xFF };
volatile TRISDbits_t  TRISDbits  = { .byte = 0xFF };
volatile PORTEbits_t  PORTEbits  = { .byte = 0xFF };
volatile TRISEbits_t  TRISEbits  = { .byte = 0xFF };

void user_main( void );
int test( void );

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
int main() {
    pthread_t test_thread;
    pthread_t main_thread;

    int ret1, ret2, result;
    
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