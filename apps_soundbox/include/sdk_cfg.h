/*********************************************************************************************
    *   Filename        : sdk_cfg.h

    *   Description     : Config for Sound Box Case

    *   Author          : Bingquan

    *   Email           : bingquan_cai@zh-jieli.com

    *   Last modifiled  : 2016-12-01 15:36

    *   Copyright:(c)JIELI  2011-2016  @ , All Rights Reserved.
*********************************************************************************************/

#ifndef _CONFIG_
#define _CONFIG_

#include "includes.h"


///�����ջ��С���ò���
#define VM_TASK_STACK_SIZE          (1024 * 1)
#define MAIN_TASK_STACK_SIZE        (1024 * 2) //(1024 * 1)����
#define MUSIC_TASK_STACK_SIZE       (1024 * 4)
#define MUSIC_PHY_TASK_STACK_SIZE   (1024 * 4)
#define TONE_TASK_STACK_SIZE        (1024 * 4)
#define TONE_PHY_TASK_STACK_SIZE    (1024 * 2)
#define UI_TASK_STACK_SIZE          (1024 * 2)

//���ö���
///< ��������ʹ��,������ʱ������.ble,��̨��app
#define   BT_TWS                      0   
///����ӻ������Ƿ���뱻���ӻ��ǻ���״̬
 #define    TWS_SLAVE_WAIT_CON         1  
///���������Ƿ�һ��ػ�
#define   BT_TWS_POWEROFF_TOGETHER    0 

///����û���ӳɹ�֮ǰ��ͨ�����������ɷ���ʹ��,������ͬʱ������԰����Ž������
#define    BT_TWS_SCAN_ENBLE         0 

/********************************************************************************/
/*
 *          --------����������
 */
////<����ϵͳ��ӡ���Թ���
 #define __DEBUG         

///<LEDָʾʹ��
#define LED_EN                  0       
///<��������
#define UART_UPDATA_EN          0      
///<�������
#define SYS_LVD_EN              1       

#if (BT_TWS == 1)
	#define BT_KTV_EN			0
#else
///<����K�豦
	#define BT_KTV_EN			0
#endif

///<����
#define PITCH_EN				0	///>���������Х������ͬʱʹ��

///<Х������
#define HOWLING_SUPPRESSION_EN	0	///>Х�в�������ͬʱʹ��

///<���ٱ��
#define SPEED_PITCH_EN			0	///>ע��ù��ܿ���Ҫ����оƬ���ܣ� ��Ӧ���ϵͳƵ�ʣ����Ҿ�����Ҫ������cpuռ���ʸߵ�Ӧ��ͬʱ��

/********************************************************************************/

/********************************************************************************/
/*
 *           --------�ֻ�app���� ���� 
 */
#if (BT_TWS == 1)
   #define SUPPORT_APP_RCSP_EN    0 
   #define RCSP_LIGHT_HW	      0	
   #define BLE_FINGER_SPINNER_EN  0	
#else
///�����Ƿ�֧���ֻ�app���ܣ�  (1-֧��,0-��֧��)
   #define SUPPORT_APP_RCSP_EN   0 
///�����Ƿ�֧��������Ӳ������ (1-֧��,0-��֧��)
   #define RCSP_LIGHT_HW	     0
///�����Ƿ�֧��ָ������BLE���ݴ��� (1-֧��,0-��֧��) //�����ú� SUPPORT_APP_RCSP_EN����ͬʱ��
   #define BLE_FINGER_SPINNER_EN 0 	
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------��Դ������
 */
///   0:  no change   
#define    PWR_NO_CHANGE        0     
///   1:  LDOIN 5v -> VDDIO 3.3v -> DVDD 1.2v
#define    PWR_LDO33            1     
///   2:  LDOIN 5v -> LDO   1.5v -> DVDD 1.2v, support bluetooth
#define    PWR_LDO15            2     
///   3:  LDOIN 5v -> DCDC  1.5v -> DVDD 1.2v, support bluetooth
#define    PWR_DCDC15           3     

///��ѡ���ã�PWR_NO_CHANGE/PWR_LDO33/PWR_LDO15/PWR_DCDC15
#define PWR_MODE_SELECT         PWR_LDO15

//DCDCʱBTAVDD,��LDOģʽʱ���Ժ��� 0:1.61v  1:1.51v  2:1.43v  3:1.35v
//AC6904��װҪ��1.51v,��Ӧ����Ϊ1
#define VDC15_LEV     3      

//0:0.703V  1:0.675V  2:0.631V  3:0.592V
//4:0.559V  5:0.527V  6:0.493V  7:0.462V 
//LC6904��װ��������Ϊ5
#define POWER_DOWN_DVDD_LEV      7

///�����������Զ��ػ���ʱ��u16���ͣ�0��ʾ���Զ��ػ�
#define AUTO_SHUT_DOWN_TIME    0//10*60*2               

///<����˫������
#define KEY_DOUBLE_CLICK        1  

///<��ص����ͣ��Ƿ��л���Դ�������
#define SWITCH_PWR_CONFIG		0
/*
	SYS_LDO_Level:3.53v-3.34v-3.18v-3.04v-2.87v-2.73v-2.62v-2.52v
	FM_LDO_Level:3.3v-3.04v-2.76v-2.5v
*/
///<Normal LDO level
#define SYS_LDO_NORMAL_LEVEL	1	//range:0~7:FM_LDO��VDDIO��һ�𣬽���:level=2
#define FM_LDO_NORMAL_LEVEL		0	//range:0~3
///<Reduce LDO level
#define SYS_LDO_REDUCE_LEVEL	3	//range:0~7
#define FM_LDO_REDUCE_LEVEL		1	//range:0~3

/********************************************************************************/

/********************************************************************************/
/*
 *           --------��Ч������
 */
///<EQģ�鿪��
#define EQ_EN			        1  
//���EQ,��1��������0�رգ���ϵͳʱ��Ҫ��ߣ�һ��Ҫ192M��
//�����󲻼�����ǰ��eq�ļ������µ�EQ���ߣ�ע��eq�ļ�����Ϊ"cfg_eq.bin"
//�������eq�ٶ�Ҫ��ߣ���֧�������ʽ����֧�ֶ���
#define USE_SOFTWARE_EQ   		0   
///<EQ uart online debug
#define EQ_UART_BDG	    		0       
///<dac�����ϲ�
#define DAC_SOUNDTRACK_COMPOUND 0       
///<�Զ�mute
#if BT_KTV_EN
	#define DAC_AUTO_MUTE_EN		0       
#else
	#define DAC_AUTO_MUTE_EN		1       
#endif
///<������
#define KEY_TONE_EN     	    1
///<��0��ʾʹ��Ĭ������
#define SYS_DEFAULT_VOL         20
///<��������
#define VOCAL_REMOVER			0


/********************************************************************************/


/********************************************************************************/
/*
 *           --------DAC VCOMO ����
 */
///�Ƿ�ѡ��VCMOֱ�ƶ���
#define VCOMO_EN 	            0	
///��ѡ���ã�DAC_L_R_CHANNEL/DAC_L_CHANNEL/DAC_R_CHANNEL  
#define DAC_CHANNEL_SLECT       DAC_L_R_CHANNEL
//DAC ���������IIS
#define DAC2IIS_EN                      0      //1:ʹ��DAC������IIS�Թ̶�������44.1K�����
  #if(DAC2IIS_EN == 1) 
     #define DAC2IIS_OUTCLK_AUTO_CLOSE  O    //1:��û������ʱ���Զ��ر�MCLK,SCLK,LRCLKʱ������� 0:���ر�
     #define IISCHIP_WM8978_EN          1    //1: ʹ��WM8978 IISоƬ��
  #else
     #define DAC2IIS_OUTCLK_AUTO_CLOSE  0    //1:��û������ʱ���Զ��ر�MCLK,SCLK,LRCLKʱ������� 0:���ر�
     #define IISCHIP_WM8978_EN          0    //1: ʹ��WM8978 IISоƬ��
  #endif
/********************************************************************************/

/********************************************************************************/
/*
 *           --------����������
 */
 #if (BT_TWS == 1)
	#define SDMMC0_EN           0
	#define SDMMC1_EN           0
	#define USB_DISK_EN         0
	#define USB_PC_EN           0
#else
    #define SDMMC0_EN           0
	#define SDMMC1_EN           0
	#define USB_DISK_EN         1
	#define USB_PC_EN           0
#endif

//usb_sd���Ÿ��ã���Ҫ���Լ�����
#define USB_SD0_MULT_EN     0	//<��Ҫ���Լ�����
#define USB_SD1_MULT_EN		0	//<��Ҫ���Լ�����

#if(USB_SD0_MULT_EN == 1)||(USB_SD1_MULT_EN == 1)
	#undef USB_PC_EN
	#define USB_PC_EN       0
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------����������
 */
#include "bluetooth/bluetooth_api.h"

#define NFC_EN          0  ///<NFC ENABLE

///��ѡ���ã�NORMAL_MODE/TEST_BQB_MODE/TEST_FCC_MODE/TEST_FRE_OFF_MODE/TEST_BOX_MODE
#define BT_MODE        NORMAL_MODE		//TEST_BQB_MODE//     

#if (BT_MODE == TEST_FCC_MODE)
  #undef UART_UPDATA_EN
  #define UART_UPDATA_EN    0
#endif

///ģ������
#define BT_ANALOG_CFG       0
#define BT_XOSC             0//

///<������̨
#if (SUPPORT_APP_RCSP_EN == 1)
#define BT_BACKMODE         1             
#else
#define BT_BACKMODE         0             
#endif
///dependency
#if (BT_BACKMODE == 0)
    ///<HID���յĶ���ģʽֻ֧�ַǺ�̨
    #define BT_HID_INDEPENDENT_MODE  0    
#endif

///<���籨��
#define BT_PHONE_NUMBER     0          


/*
 *           --------�����͹�������
 *   ʹ�ܸù��ܺ�ֻ���Ǵ��������ܣ�û����ʾ����  
 */
///��ѡ���ã�SNIFF_EN/SNIFF_TOW_CONN_ENTER_POWERDOWN_EN
#define SNIFF_MODE_CONF   0//  SNIFF_EN 

///��ѡ���ã�BT_POWER_DOWN_EN/BT_POWER_OFF_EN
#define BT_LOW_POWER_MODE  0// BT_POWER_DOWN_EN

#define BT_OSC              0
#define RTC_OSCH            1
#define RTC_OSCL            2

///��ѡ���ã�BT_OSC/RTC_OSCH/RTC_OSCL
#define LOWPOWER_OSC_TYPE   BT_OSC

///��ѡ���ã�32768L//24000000L
#define LOWPOWER_OSC_HZ     24000000L



///��ѡ���ã�BT_BREDR_EN/BT_BLE_EN/(BT_BREDR_EN|BT_BLE_EN)
#if (BT_TWS == 1)
	#define BLE_BREDR_MODE      (BT_BREDR_EN)
#elif (BT_KTV_EN == 1)
	#define BLE_BREDR_MODE      (BT_BREDR_EN)
#else
    #define BLE_BREDR_MODE      (BT_BREDR_EN)//(BT_BREDR_EN|BT_BLE_EN)
	#define BLE_GATT_ROLE_CFG    0 ///0--SERVER,1--CLIENT
#endif 

#if (BLE_BREDR_MODE == BT_BLE_EN) //����ģ�Ŵ�ble����,���滻֧��ble������uboot.bin
#define BLE_APP_UPDATE_SUPPORT_EN	0 
#else
#define BLE_APP_UPDATE_SUPPORT_EN   0
#endif

///TWS �̶����Ҷ�ѡ�� ��ѡ���ã�TWS_CHANNEL_LEFT/TWS_CHANNEL_RIGHT)
#define    BT_TWS_CHANNEL_SELECT         0////�̶����Ҷ�ʱ,���Ϊ��,�Ҷ��������������

/********************************************************************************/

/********************************************************************************/
/*
 *           --------оƬ��װ���� 
 */
///RTCVDD��û�а����Ҫ��1,Ŀǰ��Ӧ��װоƬAC6905
#define RTCVDD_TYPE              0          
#define BTAVDD_TYPE              0          

/********************************************************************************/


/********************************************************************************/
/*
 *           --------MUSIC MACRO
 */
//SMP�����ļ�֧��
#define MUSIC_DECRYPT_EN 		0	
//AB�ϵ�֧��
#define MUSIC_AB_RPT_EN 		0	

///<MP3
#define DEC_TYPE_MP3_ENABLE     1
///<SBC
#define DEC_TYPE_SBC_ENABLE     1
///<AAC
#define DEC_TYPE_AAC_ENABLE		0

///<3K_code_space
#define DEC_TYPE_WAV_ENABLE     1
///<5K_code_space
#define DEC_TYPE_FLAC_ENABLE    0
///<8K_code_space
#define DEC_TYPE_APE_ENABLE     0
///<30K_code_space
#define DEC_TYPE_WMA_ENABLE     0
///<30K_code_space
#define DEC_TYPE_F1A_ENABLE     0

/********************************************************************************/


/********************************************************************************/
/*
 *           --------FM MACRO
 */
///<��׼SDK
#if (BT_TWS == 1)
	#define FM_RADIO_EN         0 
#else
    #define FM_RADIO_EN         0
#endif 
      
///dependency
#if (FM_RADIO_EN == 1)
    ///<RDA5807FM
    #define RDA5807                 0       
    ///<BK1080FM
    #define BK1080                  0       
    ///<QN8035FM
    #define QN8035                  0       
    ///<оƬ�ڲ�FM
    #define FM_INSIDE               1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------RTC MACRO
 */
///<��׼SDK RTCʱ��ģʽ
 #if (BT_TWS == 1)
    #define RTC_CLK_EN          0       
#else
    #define RTC_CLK_EN          0       
#endif
///dependency
#if (RTC_CLK_EN == 1)
    ///<RTC����ģʽ
    #define RTC_ALM_EN          1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------ECHO MACRO
 *			�������죬����ر�	DAC_AUTO_MUTE_EN
 */
///dependency
#if (BT_BACKMODE == 1)
    ///<��֧����������̨��������
    #define ECHO_EN             0       
    ///<����ģʽ ��׼SDK
    #define ECHO_TASK_EN        0       
#else
	#if BT_KTV_EN
    	///<���칦�� KTV_SDK
    	#define ECHO_EN             1
	#else
    	///<���칦�� ��׼SDK
    	#define ECHO_EN             0
	#endif

    ///<����ģʽ ��׼SDK
    #define ECHO_TASK_EN        0       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------REC MACRO
 */
///dependency
#if (BT_BACKMODE == 1)
    ///<��֧����������̨����¼��
    #define REC_EN             0    
#else
    ///<��׼SDK¼������
    #define REC_EN             0    ///<K�豦����ʹ������ͨ��
#endif

///>����MIC¼��ģʽ
#define REC_MODE_EN				0

///>¼��Դѡ��,	0:other		1:dac
#if (BT_KTV_EN == 1)
	#define REC_SOURCE			1
#else
	#define REC_SOURCE			1
#endif

#if (REC_EN == 1)
    ///<����¼��ʹ��
	#define BT_REC_EN		1       
    ///<MIC¼��ʹ��
	#define MIC_REC_EN		1       
    ///<FM¼��ʹ��
	#define FM_REC_EN		1       
    ///<AUX¼��ʹ��
	#define AUX_REC_EN		1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------UI MACRO
 */
///<UI_��ʾ
#if (RCSP_LIGHT_HW == 1)
#define UI_ENABLE                0     
#else
#define UI_ENABLE                0     
#endif
///dependency
#if (UI_ENABLE == 1)
    #define LCD_128X64_EN        1      ///<lcd ֧��
    #define LED_7_EN             0      ///<led ֧��
#else
    ///����֧��
    #define LCD_128X64_EN        0
    #define LED_7_EN             0
#endif 
#if ((LCD_128X64_EN == 1) && (LED_7_EN == 1))
#error  "UI driver support only one"
#endif

#if (LCD_128X64_EN == 1)
    ///�˵���ʾ
    #define LCD_SUPPORT_MENU     1       
    ///LRC�����ʾ
    #define LRC_LYRICS_EN        1       
#else
    #define LCD_SUPPORT_MENU     0
    #define LRC_LYRICS_EN        0
#endif

/********************************************************************************/

 #if (BT_TWS == 1)
///<��������ʹ��,������ʱ������ble,��̨��app.
  #if ((BT_KTV_EN)||(SUPPORT_APP_RCSP_EN)||(BLE_BREDR_MODE&BT_BLE_EN))
  #error  "-------stereo not support this config ,please check sdk_cfg.h------------"
  #endif
#endif

#if (BT_LOW_POWER_MODE == BT_POWER_DOWN_EN)
  #if ((SDMMC0_EN)||(SDMMC1_EN)||(USB_DISK_EN)||(UI_ENABLE))
  #error  "-------powerdown not support this config ,please check sdk_cfg.h------------"
  #endif
#endif


#if (BT_MODE != NORMAL_MODE)
  #if ((SNIFF_MODE_CONF)||(BT_LOW_POWER_MODE))
  #error  "-------BT MODE not support this config ,please check sdk_cfg.h------------"
  #endif
#endif

#define PA_MUTE_EN               1//MUTE

#define AUX_ENABLE              0
#define AUX_DETECT_EN           0
#define AUX_AD_DETECT_EN       	0
#define AUX_IO_DETECT_EN       	0

#if AUX_IO_DETECT_EN
#define AUX_IO_BIT    BIT(1)
#define AUX_DIR_SET   (JL_PORTA->DIR |= AUX_IO_BIT)
#define AUX_PU_SET    (JL_PORTA->PU  |= AUX_IO_BIT)
#define AUX_IN_CHECK  (JL_PORTA->IN  &  AUX_IO_BIT)
#endif


#define POWERON_PR2       0   //ʹ��PR2����
#define POWERON_MOS_EN    0   //ʹ�������ܿ���

#if POWERON_MOS_EN
#define POWER_EN()    {JL_PORTC->PU &= ~BIT(5);JL_PORTC->PD &= ~BIT(5);JL_PORTC->DIR &= ~BIT(5);JL_PORTC->OUT |= BIT(5);}
#define POWER_DIS()   {JL_PORTC->PU &= ~BIT(5);JL_PORTC->PD &= ~BIT(5);JL_PORTC->DIR &= ~BIT(5);JL_PORTC->OUT &= ~ BIT(5);}
#else
#define POWER_EN(...)   
#define POWER_DIS(...)
#endif
//��ʾ������Ĭ������
#define SYS_DEFAULT_VOL_prompt   20

#define VOLMAX_SET     0
#define VOLMMIN_SET    0

//�����
#define USE_DC_CHECK       0
#if USE_DC_CHECK
#define DC_IN_GPIO_BIT    	15
#define DC_IN        		(JL_PORTA->IN & BIT(DC_IN_GPIO_BIT))
#define DC_IN_INPUT       	(JL_PORTA->DIR |= BIT(DC_IN_GPIO_BIT))
#define DC_IN_PU      	    (JL_PORTA->PU &= ~ BIT(DC_IN_GPIO_BIT))
#define DC_IN_PD            (JL_PORTA->PD &= ~ BIT(DC_IN_GPIO_BIT))
#endif


#define VM_AUX_MODE     0X01
#define VM_BT_MODE      0X02
#define VM_MUSIC_MODE   0X04
#define VM_FM_MODE      0X08
#define VM_IDLE_MODE    0X10
#define VM_RTC_MODE     0X20


#define PWM_LED_ONOFF      0
//��ȡAux ����ֵ
#define AUX_ENERGY_EN      0
//U�̺�SD���л�
#define MUSIC_U_SD_SWITCH   0
//Ĭ��ʹ��ƻ���ֻ���������
#define IPOHONE_RING_EN    0
#if  0

LVD  �͵縴λ��ѹ���Ϊ2.0V��Ĭ��2.2V
JL_SYSTEM->LVD_CON &= ~(BIT(1)|BIT(0));
JL_SYSTEM->LVD_CON |= BIT(0); ////<LVD ������ѹΪ 2.2V
// JL_SYSTEM->LVD_CON |= BIT(1); ////<LVD ������ѹΪ 2.4V
// JL_SYSTEM->LVD_CON |= (BIT(1)|BIT(0)); ////<LVD ������ѹΪ 2.6V

	

SDMMC0_EN ��Ӧ�����ѡ�� SD �����£�
SD0_IO_A��PA11(SD0DATA)��PA12(SD0CMDA)��PA13(SD0CLKA)
SD0_IO_B��PB10(SD0DATB)��PB11(SD0CMDB)��PB12(SD0CLKB)
SDMMC1_EN ��Ӧ�����ѡ�� SD �����£�
SD1_IO_A��PC3(SD1DATA)��PC4(SD1CMDA)��PC5(SD1CLKA)
SD1_IO_B��PB0(SD1DATB)��PB1(SD1CMDB)��PB2(SD1CLKB)


AC69 ϵ���������ù�������Ĺ��ʵ��ڶ�Ӧ��ʵ���������书�ʡ�
0         1        2        3        4       5        6        7    8      9

-24.9     -19.5    -15.7    -11.5    -8.6    -5.6     -3.2     0    2.8    3.1

���� AC69 ϵ�У����ʹ�õ� RTC ʱ�ӹ��ܣ������� RTC ˯�ߺ���ע��������Ϣ�Ƿ�
�д򿪡���Ȼ�ᵼ�»��Ѻ�ʱ�Ӳ��ܡ�
	set_keep_osci_flag(1);


---------------------------------------------------------------------------------------
          |   ��ͨ���  |    ǿ���  |   ��������  |  ��������        | ��ע
PA0-PA15  |             |            |             |                  |
PB13      |             |      16mA  |    10K      |   60K            |  1��PA3Ĭ������
PC0-PC15  |             |            |             |                  |
PR0-PR3   |             |            |             |                  |  2��PB6Ĭ������
----------------------------------------------------------------------|  3��PR0  ���0
PB0-PB12  |      8mA	|		24mA |    10K          60K            |
----------------------------------------------------------------------|
DM  DP    |      4mA    |        -   |    1.5K     |   15K            |
---------------------------------------------------------------------------------------

PORTR_PU(PORTR0,1);
PORTR_PD(PORTR0,0);
PORTR_DIR(PORTR0,1);
PORTR_DIE(PORTR0,1);
PORTR_HD(PORTR0,1);
����� PR1 �� PR2 ��Ϊ AD �ڣ���Ҫ��������䡣
PORTR1_ADCEN_CTL(1);�� PORTR2_ADCEN_CTL(1);


AC6901A PR0 ���� OSC32KO ��һ���õ� OSC32KO����Ҫ�� PR0 ����
Ϊ����̬��
///AC6901A PR0 ���� OSC32KO ��һ���õ� OSC32KO����Ҫ�� PR0 ����Ϊ��
��̬
///��ס����ڴ˴�����Ϊ����̬
PORTR_PU(PORTR0,0);
PORTR_PD(PORTR0,0);
PORTR_DIR(PORTR0,1);
PORTR_DIE(PORTR0,1);
PORTR_HD(PORTR0,1);

extern void __bt_set_hid_descriptor_flag(u8 flag);
__bt_set_hid_descriptor_flag(1);//��������պ󣬼���û����

extern u8 get_second_call_status();//����ͨ��״̬


//AC69 ϵ�п� DAC ������̬��
#define HP_L_EN(x) JL_AUDIO->DAA_CON0 = ((JL_AUDIO->DAA_CON0
& ~BIT(4)) | ((x & 0x1)<<4))
#define HP_R_EN(x) JL_AUDIO->DAA_CON0 = ((JL_AUDIO->DAA_CON0
& ~BIT(5)) | ((x & 0x1)<<5))




//ͨ����· timer ��� pwm
//Timer0 PWM0 PA1 (��ϵͳ timer��������)
//Timer1 PWM1 PA4
//Timer2 PWM2 PB3
//Timer3 PWM3 PB4

//outputchannel0 ����Ӧ IO �ڵ� DIE BIT ���ó� 0
//outputchannel1 ����Ӧ IO �ڵ� DIE BIT ���ó� 1


#define POWER_EN()  {usb_2_io();USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(1);} 
#define POWER_DIS()  {usb_2_io();USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(0);} 

#define POWER_EN()    {dac_ldo_set(LDO_1, 1);dac_ldo_set(LDO_2, 1);}  
#define POWER_DIS()   {dac_ldo_set(LDO_1, 0);dac_ldo_set(LDO_2, 0);}//JL_AUDIO->DAA_CON0 &= ~(BIT(2)|BIT(3));

//AC69 ϵ��ʵ�� IIC �� DAT �� CLK ������ SD �� CMD �� DAT �Ÿ��á����� FM �������о
//Ƭ��Ȼ�� FM �� IIC �� CLK �� DAT ������ SD0 �� DAT �� PA11 �� CMD �� PA12 ���á���ʱ SD
//�� �� CLK �� �� 


//AC69 ϵ�л�ȡ���� MAC ��ַ
extern void hook_get_mac_addr(u8* btaddr);
u8 local_mac_addr[6];
//hook_get_mac_addr(local_mac_addr);

#endif

#endif
