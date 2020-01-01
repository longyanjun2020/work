#ifndef _LED_H_
#define _LED_H_

#include "includes.h"
#include "sys_detect.h"
#include "sdk_cfg.h"

#if 1
#define LED_BIT           BIT(5) ///PB11
#define LED_INIT_EN()     {JL_PORTC->PU &= ~LED_BIT;JL_PORTC->PD &= ~LED_BIT;JL_PORTC->DIR &= ~LED_BIT;}
#define LED_INIT_DIS()    {JL_PORTC->PU &= ~LED_BIT;JL_PORTC->PD &= ~LED_BIT;JL_PORTC->DIR |= LED_BIT;}
#define B_LED_ON()        JL_PORTC->OUT |= LED_BIT;
#define B_LED_OFF()       JL_PORTC->OUT &= ~LED_BIT;
#define R_LED_ON(...)
#define R_LED_OFF(...)
#endif
#if 0
#define LED_BIT           BIT(11) ///PB11
#define LED_INIT_EN()     {JL_PORTB->PU &= ~LED_BIT;JL_PORTB->PD &= ~LED_BIT;JL_PORTB->DIR &= ~LED_BIT;USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(0);}
#define LED_INIT_DIS()    {JL_PORTB->PU &= ~LED_BIT;JL_PORTB->PD &= ~LED_BIT;JL_PORTB->DIR |= LED_BIT;USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(0);}
#define B_LED_ON()        JL_PORTB->OUT |= LED_BIT;
#define B_LED_OFF()       JL_PORTB->OUT &= ~LED_BIT;
#define R_LED_ON()        {USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(1);}
#define R_LED_OFF()       {USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(0);}
#endif
#if 0
#define R_LED_BIT         BIT(12) ///PB11
#define LED_BIT           BIT(11) ///PB11
#define LED_INIT_EN()     {JL_PORTB->PU &= ~LED_BIT;JL_PORTB->PD &= ~LED_BIT;JL_PORTB->DIR &= ~LED_BIT;\
	                       JL_PORTB->PU &= ~R_LED_BIT;JL_PORTB->PD &= ~R_LED_BIT;JL_PORTB->DIR &= ~R_LED_BIT;}
#define LED_INIT_DIS()    {JL_PORTB->PU &= ~LED_BIT;JL_PORTB->PD &= ~LED_BIT;JL_PORTB->DIR |= LED_BIT;\
	                      JL_PORTB->PU &= ~R_LED_BIT;JL_PORTB->PD &= ~R_LED_BIT;JL_PORTB->DIR |= R_LED_BIT;}
#define B_LED_ON()        JL_PORTB->OUT |= LED_BIT;
#define B_LED_OFF()       JL_PORTB->OUT &= ~LED_BIT;
#define R_LED_ON()        JL_PORTB->OUT |= R_LED_BIT;
#define R_LED_OFF()       JL_PORTB->OUT &= ~R_LED_BIT;
#endif


extern u32 g_led_fre;

void led_init(void);
void led_close(void);
void led_open(void);
void led_fre_set(u32 fre,u8 led_flash);
void led_scan(void *param);

void RGB_LedInit(void);

typedef struct __rgbpwm
{
    u16 r;
    u16 g;
    u16 b;
}_rgbpwm;
_rgbpwm rgbpwm;
enum
{
	 PWM_R_SEL=0,
	 PWM_G_SEL,
	 PWM_B_SEL,
	 PWM_R_G_SEL,
	 PWM_R_B_SEL,
	 PWM_G_B_SEL,
	 PWM_G_R_B_SEL,
};


enum
{
    ALLCOLORSCAN_MODEFULL,
    ALLCOLORSCAN_WHILE,
    ALLCOLORSCAN_BT,
    ALLCOLORSCAN_BTWAIT,
    ALLCOLORSCAN_RGB,
    ALLCOLORSCAN_WORK_MUSIC,
};
#define RGBRLEDPWM(x)   do{JL_TIMER0->PWM = x;}while(0)
#define RGBBLEDPWM(x)   do{JL_TIMER2->PWM = x;}while(0)
#define RGBGLEDPWM(x)   do{JL_TIMER1->PWM = x;}while(0)

#endif/*_LED_H_*/

