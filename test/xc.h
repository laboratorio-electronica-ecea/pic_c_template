#ifndef __XC_H__
#define __XC_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define __delay_ms(x)   usleep(x * 1000)
#define __delay_us(x)   usleep(x)
#define interrupt

typedef union {
    struct {
        unsigned C          :1;
        unsigned DC         :1;
        unsigned Z          :1;
        unsigned nPD        :1;
        unsigned nTO        :1;
        unsigned RP         :2;
        unsigned IRP        :1;
    };
    struct {
        unsigned            :5;
        unsigned RP0        :1;
        unsigned RP1        :1;
    };
    struct {
        unsigned CARRY      :1;
        unsigned            :1;
        unsigned ZERO       :1;
    };
} STATUSbits_t;

typedef union {
    struct {
        unsigned RBIF       :1;
        unsigned INTF       :1;
        unsigned T0IF       :1;
        unsigned RBIE       :1;
        unsigned INTE       :1;
        unsigned T0IE       :1;
        unsigned PEIE       :1;
        unsigned GIE        :1;
    };
    struct {
        unsigned            :2;
        unsigned TMR0IF     :1;
        unsigned            :2;
        unsigned TMR0IE     :1;
    };
    unsigned char byte;
} INTCONbits_t;

typedef union {
    struct {
        unsigned RA0        :1;
        unsigned RA1        :1;
        unsigned RA2        :1;
        unsigned RA3        :1;
        unsigned RA4        :1;
        unsigned RA5        :1;
        unsigned RA6        :1;
        unsigned RA7        :1;
    };
    unsigned char byte;
} PORTAbits_t;

typedef union {
    struct {
        unsigned RB0        :1;
        unsigned RB1        :1;
        unsigned RB2        :1;
        unsigned RB3        :1;
        unsigned RB4        :1;
        unsigned RB5        :1;
        unsigned RB6        :1;
        unsigned RB7        :1;
    };
    unsigned char byte;
} PORTBbits_t;

typedef union {
    struct {
        unsigned RC0        :1;
        unsigned RC1        :1;
        unsigned RC2        :1;
        unsigned RC3        :1;
        unsigned RC4        :1;
        unsigned RC5        :1;
        unsigned RC6        :1;
        unsigned RC7        :1;
    };
    unsigned char byte;
} PORTCbits_t;

typedef union {
    struct {
        unsigned RD0        :1;
        unsigned RD1        :1;
        unsigned RD2        :1;
        unsigned RD3        :1;
        unsigned RD4        :1;
        unsigned RD5        :1;
        unsigned RD6        :1;
        unsigned RD7        :1;
    };
    unsigned char byte;
} PORTDbits_t;

typedef union {
    struct {
        unsigned RE0        :1;
        unsigned RE1        :1;
        unsigned RE2        :1;
        unsigned RE3        :1;
        unsigned RE4        :1;
        unsigned RE5        :1;
        unsigned RE6        :1;
        unsigned RE7        :1;
    };
    unsigned char byte;
} PORTEbits_t;

typedef union {
    struct {
        unsigned TRISA0     :1;
        unsigned TRISA1     :1;
        unsigned TRISA2     :1;
        unsigned TRISA3     :1;
        unsigned TRISA4     :1;
        unsigned TRISA5     :1;
        unsigned TRISA6     :1;
        unsigned TRISA7     :1;
    };
    unsigned char byte;
} TRISAbits_t;

typedef union {
    struct {
        unsigned TRISB0     :1;
        unsigned TRISB1     :1;
        unsigned TRISB2     :1;
        unsigned TRISB3     :1;
        unsigned TRISB4     :1;
        unsigned TRISB5     :1;
        unsigned TRISB6     :1;
        unsigned TRISB7     :1;
    };
    unsigned char byte;
} TRISBbits_t;

typedef union {
    struct {
        unsigned TRISC0     :1;
        unsigned TRISC1     :1;
        unsigned TRISC2     :1;
        unsigned TRISC3     :1;
        unsigned TRISC4     :1;
        unsigned TRISC5     :1;
        unsigned TRISC6     :1;
        unsigned TRISC7     :1;
    };
    unsigned char byte;
} TRISCbits_t;

typedef union {
    struct {
        unsigned TRISD0     :1;
        unsigned TRISD1     :1;
        unsigned TRISD2     :1;
        unsigned TRISD3     :1;
        unsigned TRISD4     :1;
        unsigned TRISD5     :1;
        unsigned TRISD6     :1;
        unsigned TRISD7     :1;
    };
    unsigned char byte;
} TRISDbits_t;

typedef union {
    struct {
        unsigned TRISE0     :1;
        unsigned TRISE1     :1;
        unsigned TRISE2     :1;
        unsigned TRISE3     :1;
        unsigned TRISE4     :1;
        unsigned TRISE5     :1;
        unsigned TRISE6     :1;
        unsigned TRISE7     :1;
    };
    unsigned char byte;
} TRISEbits_t;

typedef union {
    struct {
        unsigned ANS0       :1;
        unsigned ANS1       :1;
        unsigned ANS2       :1;
        unsigned ANS3       :1;
        unsigned ANS4       :1;
        unsigned ANS5       :1;
        unsigned ANS6       :1;
        unsigned ANS7       :1;
    };
    unsigned char byte;
} ANSELbits_t;

typedef union {
    struct {
        unsigned ANS8       :1;
        unsigned ANS9       :1;
        unsigned ANS10      :1;
        unsigned ANS11      :1;
        unsigned ANS12      :1;
        unsigned ANS13      :1;
    };
    unsigned char byte;
} ANSELHbits_t;

extern volatile STATUSbits_t STATUSbits;
extern volatile INTCONbits_t INTCONbits;
extern volatile ANSELbits_t ANSELbits;
extern volatile ANSELHbits_t ANSELHbits;
extern volatile PORTAbits_t PORTAbits;
extern volatile TRISAbits_t TRISAbits;
extern volatile PORTBbits_t PORTBbits;
extern volatile TRISBbits_t TRISBbits;
extern volatile PORTCbits_t PORTCbits;
extern volatile TRISCbits_t TRISCbits;
extern volatile PORTDbits_t PORTDbits;
extern volatile TRISDbits_t TRISDbits;
extern volatile PORTEbits_t PORTEbits;
extern volatile TRISEbits_t TRISEbits;

#define STATUS  STATUSbits.byte
#define INTCON  INTCONbits.byte
#define ANSEL   ANSELbits.byte
#define ANSELH  ANSELHbits.byte
#define PORTA   PORTAbits.byte
#define PORTB   PORTBbits.byte
#define PORTC   PORTCbits.byte
#define PORTD   PORTDbits.byte
#define PORTE   PORTEbits.byte
#define TRISA   TRISAbits.byte
#define TRISB   TRISBbits.byte
#define TRISC   TRISCbits.byte
#define TRISD   TRISDbits.byte
#define TRISE   TRISEbits.byte

// Si este no es el archivo de implementación de tests, 
// reemplazo el punto de entrada en el programa de usuario
#ifndef TEST_IMP
#define main    user_main
#endif

#endif