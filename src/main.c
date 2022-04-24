#include "stm8s.h"
#include "milis.h"
#include "spse_stm8.h"
//#include "stm8_hd44780.h"

#include "delay.h"
#include "stdio.h"
//#include "../lib/uart.c"*/
#include  "assert.h"


#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_HIGH   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_LOW  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_REVERSE GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET)

#define BRANA_PORT GPIOB
#define BRANA_PIN GPIO_PIN_1
#define BRANA GPIO_ReadInputPin(BRANA_PORT, BRANA_PIN)

#define VYCHOD_PORT GPIOB
#define VYCHOD_PIN GPIO_PIN_0
#define VYCHOD GPIO_ReadInputPin(VYCHOD_PORT, VYCHOD_PIN)


#define BZUCAK_PORT GPIOB
#define BZUCAK_PIN GPIO_PIN_3
#define bzuci GPIO_WriteHigh(BZUCAK_PORT, BZUCAK_PIN)
#define nebzuci GPIO_WriteLow(BZUCAK_PORT ,BZUCAK_PIN)

uint32_t time1 = 0;
uint32_t time2 = 0;
uint32_t time3 = 0;
_Bool aktualni = 0;
_Bool minuly = 0;
_Bool aktualni_e = 0;
_Bool minuly_e = 0;
_Bool zmena = 0;
_Bool zmena_e = 0;
uint8_t pocet = 0;


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(BRANA_PORT, BRANA_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(VYCHOD_PORT, VYCHOD_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(BZUCAK_PORT, BZUCAK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    init_milis();
    
    //init_uart();
}

int main(void)
{
  
    setup();

    while (1) {
        if (milis() - time1 > 10){
            time1=milis();
            if(BRANA){
                aktualni=1;
            }else{
                aktualni=0;
            }
        if (minuly==1 && aktualni==0){
            minuly=0;
            pocet++;
            zmena=1;
        }
        minuly = aktualni;
        }

        if (milis() - time3 > 10){
            time3=milis();
            if(VYCHOD){
                aktualni_e=1;
            }else{
                aktualni_e=0;
            }
        if (minuly_e==1 && aktualni_e==0){
            minuly_e=0;
            pocet--;
            zmena_e=1;
        }
        minuly_e = aktualni_e;
        }
        if (milis()-time2 > 150){
            time2 = milis();
            if(zmena==1){
                //prinf("Počet: %ld \n \r",pocet);
                bzuci;
                delay_ms(200);
                nebzuci;
                zmena=0;
            }
            if(zmena_e==1){
                //prinf("Počet: %ld \n \r",pocet);
                bzuci;
                delay_ms(200);
                nebzuci;
                delay_ms(100);
                bzuci;
                delay_ms(200);
                nebzuci;
                zmena_e=0;
            }
        }
        if (BTN_PUSH){
            pocet=0;
            zmena=1;
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
