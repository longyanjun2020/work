#include "ui/led/led.h"
#include "timer.h"
#include "rtc/rtc_api.h"
#include "dac/dac_api.h"

extern tbool is_sniff_mode();
u32 g_led_fre = 0; ///<led fre
u8 g_led_flash = 0;///<b_led and r_led flash

/*----------------------------------------------------------------------------*/
/**@brief   LED³õÊ¼»¯º¯Êý
   @param   void
   @return  void
   @note    void led_init(void)
*/
/*----------------------------------------------------------------------------*/
void led_init(void)
{
#if LED_EN
    LED_INIT_EN();
    //B_LED_ON();
    //R_LED_ON();
    s32 ret;
	ret = timer_reg_isr_fun(timer0_hl,5,led_scan,NULL);
	if(ret != TIMER_NO_ERR)
	{
		printf("led_scan err = %x\n",ret);
	}
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   LED¹Ø±Õº¯Êý
   @param   void
   @return  void
   @note    void led_close(void)
*/
/*----------------------------------------------------------------------------*/
void led_close(void)
{
    LED_INIT_DIS();
}

/*----------------------------------------------------------------------------*/
/**@brief   LED´ò¿ªº¯Êý
   @param   void
   @return  void
   @note    void led_open(void)
*/
/*----------------------------------------------------------------------------*/
void led_open(void)
{
    LED_INIT_EN();
}

/*----------------------------------------------------------------------------*/
/**@brief   LEDÆµÂÊÉèÖÃº¯Êý(50ms*fre = Êµ¼ÊÉÁË¸ÆµÂÊ)
   @param   fre:ledÉÁË¸ÆµÂÊ £¨×¢£ºµ±fre = 0Ê±£¬±íÊ¾led³£ÁÁ£©
            led_flash:±íÊ¾B_ledºÍR_ledÊÇ·ñ»¥ÉÁ
   @return  void
   @note    Êµ¼ÊÉÁË¸ÆµÂÊ = fre*5*scan_fre
            ÀýÈçscan_fre = 10ms
                led_fre_set(10,0)
            Ôò£º
                ledÊµ¼ÊÉÁË¸ÆµÂÊ = 10*5*10 = 500ms = 0.5s
*/
/*----------------------------------------------------------------------------*/
void led_fre_set(u32 fre,u8 led_flash)
{
    g_led_fre = fre*5;
    g_led_flash = led_flash;
}
volatile u8 led_rg_flag=0;
u32 led_on_sniff(u32 led_flash)
{
    if(!g_led_fre) /*ºìÀ¶µÆ³£ÁÁ*/
	{
        B_LED_ON();
        R_LED_ON();
			
    }
	else if(led_flash)/*ºìÀ¶µÆ»¥ÉÁ*/
	{
		if(led_rg_flag)
		 {
		     R_LED_ON();
		     B_LED_OFF();
		     led_rg_flag=0;
		 }
		else
		{	
		    B_LED_ON();
		    R_LED_OFF();
		    led_rg_flag=1;
		 }	

    }else
	{ /*À¶µÆ¶ÀÉÁ*/
        B_LED_ON();
        R_LED_OFF();

	}
	return 1;	
}
u32 led_off_sniff(u32 led_flash)
{
    if(!g_led_fre) /*ºìÀ¶µÆ³£ÁÁ*/
	{
        B_LED_ON();
        R_LED_ON();
			
    }else if(led_flash){ /*ºìÀ¶µÆ»¥ÉÁ*/
        B_LED_OFF();
        R_LED_OFF();

    }else{ /*À¶µÆ¶ÀÉÁ*/
        B_LED_OFF();
        R_LED_OFF();
	}
	return 1;	
}


/*----------------------------------------------------------------------------*/
/**@brief   ledÉ¨Ãèº¯Êý
   @param   void
   @return  void
   @note    void led_scan(void *param)
*/
/*----------------------------------------------------------------------------*/
extern u8 is_pwrtimer_en();
extern volatile u8 low_power_flag;
extern void pwr_timer_control_led(u8 led_flash_mode,u32 led_on_ms,u32 led_off_ms,u32 (*led_off)(u32 mode) , u32 (*led_on)(u32 mode));
extern void pwr_timer_control_led_close();
void led_scan(void *param)
{
#if LED_EN
    static u32 led_cnt;

    if(is_sniff_mode()||is_pwrtimer_en())
	{
        if(!g_led_fre) /*ºìÀ¶µÆ³£ÁÁ*/
		{
			/*
			         led_on_sniff     led_off_sniff    led_on_sniff
				  |_______________|_________________|_____________
				  |     0(20)     |     0(20)       |   0(20)
		          |               |                 |

			*/
			pwr_timer_control_led(0,0,0,led_off_sniff ,led_on_sniff);
				
        }else if(g_led_flash){ /*ºìÀ¶µÆ»¥ÉÁ*/
			/*
			       led_on_sniff(ºì)                    led_on_sniff(À¶)
			       _________________                  ___________________
				  |(g_led_fre*2*10) |led_off_sniff 50|  (g_led_fre*2*10  |led_off_sniff 50
			______|                 |________________|                   |__________________

			*/
			pwr_timer_control_led(g_led_flash,(g_led_fre*2*10),50,led_off_sniff ,led_on_sniff);///
        }else{ /*À¶µÆ¶ÀÉÁ*/

			/*
			       led_on_sniff(À¶)                                  led_on_sniff(À¶)
			       _______________                                 _________________
				  |     (10*10)   |  led_off_sniff (g_led_fre*10) |   (10*10) 
			______|               |_______________________________|

			*/
			pwr_timer_control_led(g_led_flash,10*10,g_led_fre*10,led_off_sniff ,led_on_sniff);
		}
        return;
	}
	else
	{
        pwr_timer_control_led_close();
	}
    if(!g_led_fre){ /*ºìÀ¶µÆ³£ÁÁ*/
        led_cnt = 0;
        B_LED_ON();
        R_LED_ON();
    }else if(g_led_flash){ /*ºìÀ¶µÆ»¥ÉÁ*/
        led_cnt++;
        if(led_cnt > g_led_fre){
            if(led_cnt >= g_led_fre*2)
                led_cnt = 0;
            B_LED_ON();
            R_LED_OFF();
        }else if(led_cnt > 0){
            B_LED_OFF();
            R_LED_ON();
        }
    }else{ /*À¶µÆ¶ÀÉÁ*/
        led_cnt++;
        R_LED_OFF();
        if(led_cnt > g_led_fre){
            if(led_cnt >= g_led_fre*2)
                led_cnt = 0;
            B_LED_ON();
        }
        else if(led_cnt > 0){
            B_LED_OFF();
        }
    }
#endif
}


///88888888888888888888888888888888888888888888888888888888888888888888888888888
const  u16 PWM_FRE_NUMBER[] =
{  
    0,
    0,
    1,
	1,// 
	2,
	2,// 
	3,
	3,// 
	5,
	5,// 10
	
	7,
	7,// 
	9,
	10,// 
	12,
	15,// 
	20,
	25,// 
	30,
	35,// 20
	
	40,
	45,// 
	50,
	55,// 
	75,
	85,// 
	95,
	110,// 
	120,
	130,// 30
	
	140,
	150,// 
	160,// 
	170,// 
	180,
	190,// 
	200,
	210,// 
	220,
	230,// 40
	
	240,
	250,// 
	260,
	270,// 
	280,
	290,// 
	300,
	310,// 
	320,
	330,//50
	
	340,
	350,// 
	360,
	370,// 
	380,
	400,// 
	410,
	420,// 
	430,
	440,// 60
	
	450,
	460,// 
	470,// 
	480,// 
	490,// 
	500,// 
	510,// 
	520,// 
	530,// 
	540,// 70	
	
	550,
	560,// 
	570,// 
	580,// 
	590,// 
	600,// 
	610,// 
	620,// 
	630,// 
	640,// 80
	
	650,
	660,// 
	670,// 
	680,// 
	690,// 
	700,// 
	710,// 
	720,// 
	730,// 
	740,// 90
		
	750,
	760,// 
	770,// 
	780,// 
	790,// 
	800,// 
	810,// 
	820,// 
	830,// 
	840,// 100
			
	850,
	860,// 
	870,// 
	880,// 
	890,// 
	900,// 
	910,// 
	920,// 
	930,// 
	940,// 110
	
	950,
	960,// 
	970,// 
	980,// 
	990,// 
	1000,// 
	1010,// 
	1020,// 
	1030,// 
	1040,// 120

	1050,
	1060,// 
	1070,// 
	1080,// 
	1090,// 
	1100,// 
	1110,// 
	1120,// 
	1130,// 
	1140,// 130
		
	1150,
	1160,// 
	1170,// 
	1180,// 
	1190,// 
	1200,// 
	1210,// 
	1220,// 
	1230,// 
	1240,// 140

	1250,
	1260,// 
	1270,// 
	1280,// 
	1290,// 
	1300,// 
	1310,// 
	1320,// 
	1330,// 
	1340,// 140

	1350,
	1360,// 
	1370,// 
	1380,// 
	1390,// 
	1400,// 
	1410,// 
	1420,// 
	1430,// 
	1440,// 150

	1450,
	1460,// 
	1470,// 
	1480,// 
	1490,// 
	1500,// 
	1510,// 
	1520,// 
	1530,// 
	1540,// 160

};
u16 led_pwm_cnt=2000;

#define R_Bit  BIT(3) 
#define G_Bit  BIT(4) 
#define B_Bit  BIT(5) 

#define Rled_pwm_on()         do{JL_PORTC->DIR &= ~R_Bit;JL_PORTC->PU |=R_Bit;JL_PORTC->PD |=R_Bit;\
                                JL_PORTC->DIE |= R_Bit;}while(0);

#define Rled_pwm_off()       do{JL_PORTC->DIR |=R_Bit;JL_PORTC->PU &= ~R_Bit;JL_PORTC->PD &= ~R_Bit;\
                                JL_PORTC->DIE |= R_Bit;}while(0);

#define Gled_pwm_on()         do{JL_PORTC->DIR &= ~G_Bit;JL_PORTC->PU |=G_Bit;JL_PORTC->PD |=G_Bit;\
                                JL_PORTC->DIE |= G_Bit;}while(0);

#define Gled_pwm_off()       do{JL_PORTC->DIR |=G_Bit;JL_PORTC->PU &= ~G_Bit;JL_PORTC->PD &= ~G_Bit;\
                                JL_PORTC->DIE |= G_Bit;}while(0);

#define Bled_pwm_on()         do{JL_PORTC->DIR &= ~B_Bit;JL_PORTC->PU |=B_Bit;JL_PORTC->PD |=B_Bit;\
                                JL_PORTC->DIE |= B_Bit;}while(0);

#define Bled_pwm_off()       do{JL_PORTC->DIR |=B_Bit;JL_PORTC->PU &= ~B_Bit;JL_PORTC->PD &= ~B_Bit;\
                                JL_PORTC->DIE |= B_Bit;}while(0);


#define Rled_on()         do{JL_PORTC->DIR &= ~R_Bit;JL_PORTC->PU &= ~R_Bit;JL_PORTC->PD &= ~R_Bit;\
                                JL_PORTC->OUT |=R_Bit; }while(0);

#define Rled_off()       do{JL_PORTC->DIR &= ~R_Bit;JL_PORTC->PU &= ~R_Bit;JL_PORTC->PD &= ~R_Bit;\
                                JL_PORTC->OUT &= ~R_Bit;}while(0);

#define Gled_on()         do{JL_PORTC->DIR &= ~G_Bit;JL_PORTC->PU |=G_Bit;JL_PORTC->PD |=G_Bit;\
                                JL_PORTC->OUT |=G_Bit;}while(0);

#define Gled_off()       do{JL_PORTC->DIR &= ~G_Bit;JL_PORTC->PU &= ~G_Bit;JL_PORTC->PD &= ~G_Bit;\
                                JL_PORTC->OUT &= ~G_Bit;}while(0);

#define Bled_on()         do{JL_PORTC->DIR &= ~B_Bit;JL_PORTC->PU |=B_Bit;JL_PORTC->PD |=B_Bit;\
                                JL_PORTC->OUT |=B_Bit;}while(0);

#define Bled_off()       do{JL_PORTC->DIR &= ~B_Bit;JL_PORTC->PU &= ~B_Bit;JL_PORTC->PD &= ~B_Bit;\
                                JL_PORTC->OUT &= ~B_Bit;}while(0);

u8 rgbMode = ALLCOLORSCAN_RGB;
u8 scanLedModeIndex;
u8 rgb_scan_mode=0;
bool pwm_dir=0;
void pwm_timer2_led_init(void)
{
#if 1
	//printf("clk=%u\n",clock_get_lsb_freq());//´òÓ¡LSBÊ±ÖÓ  60M
	JL_IOMAP->CON1|=BIT(12);//Ê¹ÓÃÊä³öÍ¨µÀ TMR2_PWM_OUTÊä³ö
	

	JL_TIMER2->CNT=0;
	//JL_TIMER2->PWM=led_pwm_cnt;//1200/6000*100%=20%   Õ¼¿Õ±È20%
	JL_TIMER2->PRD=1500;//ÖÜÆÚÆµÂÊ	6000/60M==100us
	JL_TIMER2->CON=BIT(8)|BIT(0);// 1·ÖÆµ Ê¹ÄÜPWM
#else

	 ///pwm1 pa4
	 JL_TIMER1->CON = 0x0000;
	 //JL_TIMER1->PRD = 24000000L/(4*fre);
	 //JL_TIMER1->PWM = (JL_TIMER1->PRD*duty)/100;
	 JL_TIMER1->PRD = 6000;
	 //JL_TIMER1->PWM = 20;
	 JL_TIMER1->CON = (1<<4) | (1<<8)| (1<<0) |(2<<2);
	 JL_PORTA->PU &= ~BIT(4);
	 JL_PORTA->PD &= ~BIT(4);
	 JL_PORTA->DIR &= ~BIT(4);

     ///DM,outch0
    JL_IOMAP->CON1 &= ~(0x0700);
    JL_IOMAP->CON1 |= 0x0200;//pwm1
    JL_TIMER0->CON = 0x0000;
    //JL_TIMER0->PRD = 24000000L/(4*fre);
    //JL_TIMER0->PWM = (JL_TIMER1->PRD*duty)/100;
    JL_TIMER0->PRD = 6000;
    //JL_TIMER0->PWM = 1000;
    JL_TIMER0->CON = (1<<4) | (1<<8)| (1<<0) |(2<<2);
    JL_PORTC->PU |= BIT(3);JL_PORTC->PD|=BIT(3);JL_PORTC->DIR&=~BIT(3);JL_PORTC->DIE&=~BIT(3);

	    ///pc4 outch1
    JL_IOMAP->CON1 &= ~(0x3800);
    JL_IOMAP->CON1 |= 0x1000;//pwm1
    JL_TIMER2->CON = 0x0000;
    //JL_TIMER2->PRD = 24000000L/(4*fre);
    //JL_TIMER2->PWM = (JL_TIMER1->PRD*duty)/100;
    //JL_TIMER2->PWM = duty;
    JL_TIMER2->PRD = 6000;
    //JL_TIMER2->PWM = 6000;
    JL_TIMER2->CON = (1<<4) | (1<<8)| (1<<0) |(2<<2);
    JL_PORTC->PU |= BIT(4);JL_PORTC->PD|=BIT(4);JL_PORTC->DIR&=~BIT(4);JL_PORTC->DIE|=BIT(4);

#endif


          
}
//RGB Ñ­»·ºôÎüÐ§¹û
#define pwm_value   4
u8 pwm_sel=PWM_R_SEL;

void pwm_mode_scan_rgb(void)
{

#if 0
   static u32 time=0;
   static u8 pwm_mode=0;
   pwm_timer2_led_init();

	if(pwm_mode==0)
	{
		rgbpwm.r+=pwm_value;
		if(rgbpwm.r>=6000)
			pwm_mode=1;
	}
	else if(pwm_mode==1)
	{
		rgbpwm.r-=pwm_value;
		if(rgbpwm.r==0)
			pwm_mode=2;
	}
    else if(pwm_mode==2)
	{
		rgbpwm.g+=pwm_value;
		if(rgbpwm.g>=6000)
			pwm_mode=3;
	}
	else if(pwm_mode==3)
	{
		rgbpwm.g-=pwm_value;
		if(rgbpwm.g==0)
			pwm_mode=4;
	} 
	else if(pwm_mode==4)
	{
		rgbpwm.b+=pwm_value;
		if(rgbpwm.b>=6000)
			pwm_mode=5;
	}
	else if(pwm_mode==5)
	{
		rgbpwm.b-=pwm_value;
		if(rgbpwm.b==0)
			pwm_mode=6;
	}
	else if(pwm_mode==6)
	{
		rgbpwm.r+=pwm_value;
		rgbpwm.g=rgbpwm.r;
		if(rgbpwm.r>=6000)
			pwm_mode=7;
	}
	else if(pwm_mode==7)
	{
		rgbpwm.r-=pwm_value;
		rgbpwm.g=rgbpwm.r;
		if(rgbpwm.r==0)
			pwm_mode=8;
	}
	else if(pwm_mode==8)
	{
		rgbpwm.r+=pwm_value;
		rgbpwm.b=rgbpwm.r;
		if(rgbpwm.r>=6000)
			pwm_mode=9;
	}
	else if(pwm_mode==9)
	{
		rgbpwm.r-=pwm_value;
		rgbpwm.b=rgbpwm.r;
		if(rgbpwm.r==0)
			pwm_mode=10;
	}
	else if(pwm_mode==10)
	{
		rgbpwm.g+=pwm_value;
		rgbpwm.b=rgbpwm.g;
		if(rgbpwm.g>=6000)
			pwm_mode=11;
	}
	else if(pwm_mode==11)
	{
		rgbpwm.g-=pwm_value;
		rgbpwm.b=rgbpwm.g;
		if(rgbpwm.g==0)
			pwm_mode=12;
	}
	else if(pwm_mode==12)
	{
		rgbpwm.g+=pwm_value;
		rgbpwm.b=rgbpwm.g;
		rgbpwm.r=rgbpwm.g;
		if(rgbpwm.g>=6000)
			pwm_mode=13;
	}
	else if(pwm_mode==13)
	{
		rgbpwm.g-=pwm_value;
		rgbpwm.b=rgbpwm.g;
		rgbpwm.r=rgbpwm.g;
		if(rgbpwm.g==0)
			pwm_mode=0;
	}
	else
		pwm_mode=0;

	RGBRLEDPWM(rgbpwm.r);
    RGBBLEDPWM(rgbpwm.b);
    RGBGLEDPWM(rgbpwm.g);
#else
    
    static u8 cnt=0;
	cnt++;
	if(cnt>20)
	{
		cnt=0;
		pwm_timer2_led_init();
		if(pwm_dir==0)
	    {
	   		led_pwm_cnt-=1;
			if(led_pwm_cnt==0 || led_pwm_cnt>150)
			{
			    led_pwm_cnt=0;
				if(++pwm_sel>PWM_G_R_B_SEL)  pwm_sel=PWM_R_SEL;
				
				if(pwm_sel==PWM_R_SEL)
				{
					Rled_pwm_on();
					Gled_pwm_off();
					Bled_pwm_off();
				}
				else if(pwm_sel==PWM_G_SEL)
				{
					Rled_pwm_off();
					Gled_pwm_on();
					Bled_pwm_off();
				}
				else if(pwm_sel==PWM_B_SEL)
				{
					Rled_pwm_off();
					Gled_pwm_off();
					Bled_pwm_on();
				}
				else if(pwm_sel==PWM_R_G_SEL)
				{
					Rled_pwm_on();
					Gled_pwm_on();
					Bled_pwm_off();
				}
				else if(pwm_sel==PWM_R_B_SEL)
				{
					Rled_pwm_on();
					Gled_pwm_off();
					Bled_pwm_on();
				}
				else if(pwm_sel==PWM_G_B_SEL)
				{
					Rled_pwm_off();
					Gled_pwm_on();
					Bled_pwm_on();
				}
				else if(pwm_sel==PWM_G_R_B_SEL)
				{
					Rled_pwm_on();
					Gled_pwm_on();
					Bled_pwm_on();
				}
				pwm_dir=1;
			}

	    }
		else
		{
			led_pwm_cnt+=1;
			if(led_pwm_cnt>150)
			{
			    pwm_dir=0;
				led_pwm_cnt=150;
			}
		}

		//printf("%d\n",led_pwm_cnt);
		JL_TIMER2->PWM=PWM_FRE_NUMBER[led_pwm_cnt];
	}
#endif
}
//RGB  ËæÒôÀÖÉÁ
u32 max_energy_value;

void pwm_mode_work_music(void)
{
    static u8 cnt=0;
	u32 dac_val;
	static u8 led_falg_cnt=0;
	cnt++;
	if(cnt>5)  cnt=0;
	else
	{
		return;
	}
	dac_val=get_dac_energy_value();
	u8 energy_spectrum_level;
	if(dac_val > 3500000)
	{
		energy_spectrum_level = 7;
	}
	else if(dac_val > 2800000)
	{
		energy_spectrum_level = 6;
	}
	else if(dac_val > 2000000)
	{
		energy_spectrum_level = 5;
	}
	else if(dac_val >1500000)
	{
		energy_spectrum_level = 4;
	}
	else if(dac_val > 1000000)
	{
		energy_spectrum_level = 3;
	}
	else if(dac_val > 500000)
	{
		energy_spectrum_level = 2;
	}
	else if(dac_val > 300000)
	{
		energy_spectrum_level = 1;
	}
	else
	{
		energy_spectrum_level = 0;
	}

	switch( energy_spectrum_level )
	{
		case 7:
			Rled_on();
			led_falg_cnt = 3;
			break;
		case 6:
			if( led_falg_cnt < 4 )
			{
				Rled_on();
			}
			else
			{
				Rled_off();
			}
			led_falg_cnt = 4;
			break;
		case 5:
			Rled_off();
			led_falg_cnt = 3;
			break;
		case 4:
			if( led_falg_cnt < 2 )
			{
				Rled_on();
			}
			else
			{
				Rled_off();
			}
			led_falg_cnt = 2;
			break;
		case 3:
			Rled_on();
			led_falg_cnt = 1;
			break;
		case 2:
			if( led_falg_cnt < 1 )
			{
				Rled_on();
			}
			else
			{
				Rled_off();
			}
			led_falg_cnt = 1;
			break;
		case 1:
			Rled_on();
			led_falg_cnt = 0;
			break;
		case 0:
			Rled_off();
			led_falg_cnt = 0;
			break;
	}

#if 0
    static u8 cnttt=0;
	static u8 cnt=0;
	u32 dac_val;
	u8 speed;
	cnttt++;
	if(cnttt>30)
	{
		cnttt=0;
		
		max_energy_value = get_dac_energy_value() > max_energy_value ? get_dac_energy_value() : max_energy_value;
		
		speed = (get_dac_energy_value() * 5 / max_energy_value) + 1;
	
		cnt += speed;
		if(cnt > 40)
		{
			cnt = 0;
		}
		Rled_off();
		Gled_off();
		Bled_off();

		switch(cnt)
		{
			case   0 ... 10:
				Rled_on();
				break;
			case  11 ... 20:
				Gled_on();
				break;
			case  21 ... 30:
				Bled_on();
				break;
			case  31 ... 40:

				break;
			default:
				break;
		}
	}
#endif
}







void pwm_rgb_led_scan(void *param)
{
     switch(rgbMode)
     {
     	case ALLCOLORSCAN_RGB:
			pwm_mode_scan_rgb();
			break;
		case ALLCOLORSCAN_WORK_MUSIC:
			pwm_mode_work_music();

			break;
     }
}

void RGB_LedInit(void)
{
    s32 ret;
	
	ret = timer_reg_isr_fun(timer0_hl,1,pwm_rgb_led_scan,NULL);
	if(ret != TIMER_NO_ERR)
	{
		printf("led_scan err = %x\n",ret);
	}
}

