#include "stm8s.h"
#include "milis.h"
#include "spse_stm8.h"
#include "stm8_hd44780.h"

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

#define START_PORT GPIOB
#define START_PIN GPIO_PIN_1
#define KONEC_PORT GPIOB
#define KONEC_PIN GPIO_PIN_2

#define BRANA_START GPIO_ReadInputPin(START_PORT, START_PIN)
#define BRANA_KONEC GPIO_ReadInputPin(KONEC_PORT, KONEC_PIN)

uint32_t time1 = 0;
uint32_t time2 = 0;
uint32_t time3 = 0;
uint32_t time4 = 0;
uint32_t time5 = 0;
uint32_t cas = 0;
uint32_t milisekundy = 0;
uint32_t sekundy = 0;
_Bool casovac = 0;
char text[32];


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(START_PORT, START_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(KONEC_PORT, KONEC_PIN, GPIO_MODE_IN_FL_NO_IT);
    lcd_init();
    init_milis();
    
    //init_uart1();
}
uint32_t stopky(void){
    cas=milis();
    if (cas - milis() >= 1000){
        sekundy++;
    }
    if (cas - milis() >= 1){
        milisekundy++;
        if (milisekundy == 1000){
            milisekundy=0;
        }
    }
    lcd_gotoxy(0,0);
    sprintf(text,"Čas: %2u",sekundy);
    lcd_puts(text);
    lcd_gotoxy(0,6);
    sprintf(text,":%3u",milisekundy);

}

void main(void)
{
  
    setup();

    while (1) {

        if (BRANA_START && milis()-time1 > 200){
           casovac=1;  
        }
        if (BRANA_KONEC && milis()-time2 > 5){
            casovac=0;
        }
        if (casovac==1 && milis()-time3 > 5){
            stopky();
        }
        if (BTN_PUSH && milis()-time4 > 200 ){
            sekundy = 0;
            milisekundy = 0; 
        }
        if (milis()-time5 > 500)
            lcd_clear();
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
