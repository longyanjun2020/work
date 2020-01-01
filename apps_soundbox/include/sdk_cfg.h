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


///任务堆栈大小配置测试
#define VM_TASK_STACK_SIZE          (1024 * 1)
#define MAIN_TASK_STACK_SIZE        (1024 * 2) //(1024 * 1)可行
#define MUSIC_TASK_STACK_SIZE       (1024 * 4)
#define MUSIC_PHY_TASK_STACK_SIZE   (1024 * 4)
#define TONE_TASK_STACK_SIZE        (1024 * 4)
#define TONE_PHY_TASK_STACK_SIZE    (1024 * 2)
#define UI_TASK_STACK_SIZE          (1024 * 2)

//配置对箱
///< 蓝牙对箱使能,对箱暂时不开放.ble,后台和app
#define   BT_TWS                      0   
///对箱从机开机是否进入被连接还是回链状态
 #define    TWS_SLAVE_WAIT_CON         1  
///对箱主从是否一起关机
#define   BT_TWS_POWEROFF_TOGETHER    0 

///对箱没连接成功之前，通过按键开启可发现使能,即主从同时按下配对按键才进行配对
#define    BT_TWS_SCAN_ENBLE         0 

/********************************************************************************/
/*
 *          --------调试类配置
 */
////<开启系统打印调试功能
 #define __DEBUG         

///<LED指示使能
#define LED_EN                  0       
///<串口升级
#define UART_UPDATA_EN          0      
///<电量监测
#define SYS_LVD_EN              1       

#if (BT_TWS == 1)
	#define BT_KTV_EN			0
#else
///<蓝牙K歌宝
	#define BT_KTV_EN			0
#endif

///<变声
#define PITCH_EN				0	///>变调不能与啸叫抑制同时使能

///<啸叫抑制
#define HOWLING_SUPPRESSION_EN	0	///>啸叫不能与变调同时使能

///<变速变调
#define SPEED_PITCH_EN			0	///>注意该功能开启要考虑芯片性能， 相应提高系统频率，并且尽量不要跟其他cpu占用率高的应用同时打开

/********************************************************************************/

/********************************************************************************/
/*
 *           --------手机app控制 配置 
 */
#if (BT_TWS == 1)
   #define SUPPORT_APP_RCSP_EN    0 
   #define RCSP_LIGHT_HW	      0	
   #define BLE_FINGER_SPINNER_EN  0	
#else
///配置是否支持手机app功能，  (1-支持,0-不支持)
   #define SUPPORT_APP_RCSP_EN   0 
///配置是否支持蓝牙灯硬件控制 (1-支持,0-不支持)
   #define RCSP_LIGHT_HW	     0
///配置是否支持指尖陀螺BLE数据传输 (1-支持,0-不支持) //此配置和 SUPPORT_APP_RCSP_EN不能同时打开
   #define BLE_FINGER_SPINNER_EN 0 	
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------电源类配置
 */
///   0:  no change   
#define    PWR_NO_CHANGE        0     
///   1:  LDOIN 5v -> VDDIO 3.3v -> DVDD 1.2v
#define    PWR_LDO33            1     
///   2:  LDOIN 5v -> LDO   1.5v -> DVDD 1.2v, support bluetooth
#define    PWR_LDO15            2     
///   3:  LDOIN 5v -> DCDC  1.5v -> DVDD 1.2v, support bluetooth
#define    PWR_DCDC15           3     

///可选配置：PWR_NO_CHANGE/PWR_LDO33/PWR_LDO15/PWR_DCDC15
#define PWR_MODE_SELECT         PWR_LDO15

//DCDC时BTAVDD,用LDO模式时可以忽略 0:1.61v  1:1.51v  2:1.43v  3:1.35v
//AC6904封装要用1.51v,即应设置为1
#define VDC15_LEV     3      

//0:0.703V  1:0.675V  2:0.631V  3:0.592V
//4:0.559V  5:0.527V  6:0.493V  7:0.462V 
//LC6904封装建议设置为5
#define POWER_DOWN_DVDD_LEV      7

///蓝牙无连接自动关机计时，u16类型，0表示不自动关机
#define AUTO_SHUT_DOWN_TIME    0//10*60*2               

///<按键双击功能
#define KEY_DOUBLE_CLICK        1  

///<电池电量低，是否切换电源输出配置
#define SWITCH_PWR_CONFIG		0
/*
	SYS_LDO_Level:3.53v-3.34v-3.18v-3.04v-2.87v-2.73v-2.62v-2.52v
	FM_LDO_Level:3.3v-3.04v-2.76v-2.5v
*/
///<Normal LDO level
#define SYS_LDO_NORMAL_LEVEL	1	//range:0~7:FM_LDO和VDDIO绑一起，建议:level=2
#define FM_LDO_NORMAL_LEVEL		0	//range:0~3
///<Reduce LDO level
#define SYS_LDO_REDUCE_LEVEL	3	//range:0~7
#define FM_LDO_REDUCE_LEVEL		1	//range:0~3

/********************************************************************************/

/********************************************************************************/
/*
 *           --------音效类配置
 */
///<EQ模块开关
#define EQ_EN			        1  
//软件EQ,置1开启，置0关闭，对系统时钟要求高，一般要192M，
//开启后不兼容以前的eq文件，用新的EQ工具，注意eq文件名改为"cfg_eq.bin"
//由于软件eq速度要求高，不支持无损格式，不支持对箱
#define USE_SOFTWARE_EQ   		0   
///<EQ uart online debug
#define EQ_UART_BDG	    		0       
///<dac声道合并
#define DAC_SOUNDTRACK_COMPOUND 0       
///<自动mute
#if BT_KTV_EN
	#define DAC_AUTO_MUTE_EN		0       
#else
	#define DAC_AUTO_MUTE_EN		1       
#endif
///<按键音
#define KEY_TONE_EN     	    1
///<非0表示使用默认音量
#define SYS_DEFAULT_VOL         20
///<人声消除
#define VOCAL_REMOVER			0


/********************************************************************************/


/********************************************************************************/
/*
 *           --------DAC VCOMO 配置
 */
///是否选择VCMO直推耳机
#define VCOMO_EN 	            0	
///可选配置：DAC_L_R_CHANNEL/DAC_L_CHANNEL/DAC_R_CHANNEL  
#define DAC_CHANNEL_SLECT       DAC_L_R_CHANNEL
//DAC 声音输出到IIS
#define DAC2IIS_EN                      0      //1:使能DAC声音从IIS以固定采样率44.1K输出。
  #if(DAC2IIS_EN == 1) 
     #define DAC2IIS_OUTCLK_AUTO_CLOSE  O    //1:当没有声音时，自动关闭MCLK,SCLK,LRCLK时钟输出。 0:不关闭
     #define IISCHIP_WM8978_EN          1    //1: 使能WM8978 IIS芯片。
  #else
     #define DAC2IIS_OUTCLK_AUTO_CLOSE  0    //1:当没有声音时，自动关闭MCLK,SCLK,LRCLK时钟输出。 0:不关闭
     #define IISCHIP_WM8978_EN          0    //1: 使能WM8978 IIS芯片。
  #endif
/********************************************************************************/

/********************************************************************************/
/*
 *           --------外设类配置
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

//usb_sd引脚复用，需要测试兼容性
#define USB_SD0_MULT_EN     0	//<需要测试兼容性
#define USB_SD1_MULT_EN		0	//<需要测试兼容性

#if(USB_SD0_MULT_EN == 1)||(USB_SD1_MULT_EN == 1)
	#undef USB_PC_EN
	#define USB_PC_EN       0
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------蓝牙类配置
 */
#include "bluetooth/bluetooth_api.h"

#define NFC_EN          0  ///<NFC ENABLE

///可选配置：NORMAL_MODE/TEST_BQB_MODE/TEST_FCC_MODE/TEST_FRE_OFF_MODE/TEST_BOX_MODE
#define BT_MODE        NORMAL_MODE		//TEST_BQB_MODE//     

#if (BT_MODE == TEST_FCC_MODE)
  #undef UART_UPDATA_EN
  #define UART_UPDATA_EN    0
#endif

///模拟配置
#define BT_ANALOG_CFG       0
#define BT_XOSC             0//

///<蓝牙后台
#if (SUPPORT_APP_RCSP_EN == 1)
#define BT_BACKMODE         1             
#else
#define BT_BACKMODE         0             
#endif
///dependency
#if (BT_BACKMODE == 0)
    ///<HID拍照的独立模式只支持非后台
    #define BT_HID_INDEPENDENT_MODE  0    
#endif

///<来电报号
#define BT_PHONE_NUMBER     0          


/*
 *           --------蓝牙低功耗设置
 *   使能该功能后只能是纯蓝牙功能，没有显示功能  
 */
///可选配置：SNIFF_EN/SNIFF_TOW_CONN_ENTER_POWERDOWN_EN
#define SNIFF_MODE_CONF   0//  SNIFF_EN 

///可选配置：BT_POWER_DOWN_EN/BT_POWER_OFF_EN
#define BT_LOW_POWER_MODE  0// BT_POWER_DOWN_EN

#define BT_OSC              0
#define RTC_OSCH            1
#define RTC_OSCL            2

///可选配置：BT_OSC/RTC_OSCH/RTC_OSCL
#define LOWPOWER_OSC_TYPE   BT_OSC

///可选配置：32768L//24000000L
#define LOWPOWER_OSC_HZ     24000000L



///可选配置：BT_BREDR_EN/BT_BLE_EN/(BT_BREDR_EN|BT_BLE_EN)
#if (BT_TWS == 1)
	#define BLE_BREDR_MODE      (BT_BREDR_EN)
#elif (BT_KTV_EN == 1)
	#define BLE_BREDR_MODE      (BT_BREDR_EN)
#else
    #define BLE_BREDR_MODE      (BT_BREDR_EN)//(BT_BREDR_EN|BT_BLE_EN)
	#define BLE_GATT_ROLE_CFG    0 ///0--SERVER,1--CLIENT
#endif 

#if (BLE_BREDR_MODE == BT_BLE_EN) //仅单模才打开ble升级,需替换支持ble升级的uboot.bin
#define BLE_APP_UPDATE_SUPPORT_EN	0 
#else
#define BLE_APP_UPDATE_SUPPORT_EN   0
#endif

///TWS 固定左右耳选择 可选配置：TWS_CHANNEL_LEFT/TWS_CHANNEL_RIGHT)
#define    BT_TWS_CHANNEL_SELECT         0////固定左右耳时,左耳为主,右耳不进行搜索配对

/********************************************************************************/

/********************************************************************************/
/*
 *           --------芯片封装配置 
 */
///RTCVDD口没有绑出来要置1,目前对应封装芯片AC6905
#define RTCVDD_TYPE              0          
#define BTAVDD_TYPE              0          

/********************************************************************************/


/********************************************************************************/
/*
 *           --------MUSIC MACRO
 */
//SMP加密文件支持
#define MUSIC_DECRYPT_EN 		0	
//AB断点支持
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
///<标准SDK
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
    ///<芯片内部FM
    #define FM_INSIDE               1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------RTC MACRO
 */
///<标准SDK RTC时钟模式
 #if (BT_TWS == 1)
    #define RTC_CLK_EN          0       
#else
    #define RTC_CLK_EN          0       
#endif
///dependency
#if (RTC_CLK_EN == 1)
    ///<RTC闹钟模式
    #define RTC_ALM_EN          1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------ECHO MACRO
 *			开启混响，必须关闭	DAC_AUTO_MUTE_EN
 */
///dependency
#if (BT_BACKMODE == 1)
    ///<不支持与蓝牙后台开启混响
    #define ECHO_EN             0       
    ///<混响模式 标准SDK
    #define ECHO_TASK_EN        0       
#else
	#if BT_KTV_EN
    	///<混响功能 KTV_SDK
    	#define ECHO_EN             1
	#else
    	///<混响功能 标准SDK
    	#define ECHO_EN             0
	#endif

    ///<混响模式 标准SDK
    #define ECHO_TASK_EN        0       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------REC MACRO
 */
///dependency
#if (BT_BACKMODE == 1)
    ///<不支持与蓝牙后台开启录音
    #define REC_EN             0    
#else
    ///<标准SDK录音功能
    #define REC_EN             0    ///<K歌宝必须使用数字通道
#endif

///>独立MIC录音模式
#define REC_MODE_EN				0

///>录音源选择,	0:other		1:dac
#if (BT_KTV_EN == 1)
	#define REC_SOURCE			1
#else
	#define REC_SOURCE			1
#endif

#if (REC_EN == 1)
    ///<蓝牙录音使能
	#define BT_REC_EN		1       
    ///<MIC录音使能
	#define MIC_REC_EN		1       
    ///<FM录音使能
	#define FM_REC_EN		1       
    ///<AUX录音使能
	#define AUX_REC_EN		1       
#endif

/********************************************************************************/

/********************************************************************************/
/*
 *           --------UI MACRO
 */
///<UI_显示
#if (RCSP_LIGHT_HW == 1)
#define UI_ENABLE                0     
#else
#define UI_ENABLE                0     
#endif
///dependency
#if (UI_ENABLE == 1)
    #define LCD_128X64_EN        1      ///<lcd 支持
    #define LED_7_EN             0      ///<led 支持
#else
    ///都不支持
    #define LCD_128X64_EN        0
    #define LED_7_EN             0
#endif 
#if ((LCD_128X64_EN == 1) && (LED_7_EN == 1))
#error  "UI driver support only one"
#endif

#if (LCD_128X64_EN == 1)
    ///菜单显示
    #define LCD_SUPPORT_MENU     1       
    ///LRC歌词显示
    #define LRC_LYRICS_EN        1       
#else
    #define LCD_SUPPORT_MENU     0
    #define LRC_LYRICS_EN        0
#endif

/********************************************************************************/

 #if (BT_TWS == 1)
///<蓝牙对箱使能,对箱暂时不开放ble,后台和app.
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


#define POWERON_PR2       0   //使用PR2软开机
#define POWERON_MOS_EN    0   //使用三极管开机

#if POWERON_MOS_EN
#define POWER_EN()    {JL_PORTC->PU &= ~BIT(5);JL_PORTC->PD &= ~BIT(5);JL_PORTC->DIR &= ~BIT(5);JL_PORTC->OUT |= BIT(5);}
#define POWER_DIS()   {JL_PORTC->PU &= ~BIT(5);JL_PORTC->PD &= ~BIT(5);JL_PORTC->DIR &= ~BIT(5);JL_PORTC->OUT &= ~ BIT(5);}
#else
#define POWER_EN(...)   
#define POWER_DIS(...)
#endif
//提示音播放默认音量
#define SYS_DEFAULT_VOL_prompt   20

#define VOLMAX_SET     0
#define VOLMMIN_SET    0

//充电检测
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
//获取Aux 能量值
#define AUX_ENERGY_EN      0
//U盘和SD卡切换
#define MUSIC_U_SD_SWITCH   0
//默认使用苹果手机来电铃声
#define IPOHONE_RING_EN    0
#if  0

LVD  低电复位电压最低为2.0V，默认2.2V
JL_SYSTEM->LVD_CON &= ~(BIT(1)|BIT(0));
JL_SYSTEM->LVD_CON |= BIT(0); ////<LVD 启动电压为 2.2V
// JL_SYSTEM->LVD_CON |= BIT(1); ////<LVD 启动电压为 2.4V
// JL_SYSTEM->LVD_CON |= (BIT(1)|BIT(0)); ////<LVD 启动电压为 2.6V

	

SDMMC0_EN 对应两组可选的 SD 口如下：
SD0_IO_A：PA11(SD0DATA)、PA12(SD0CMDA)、PA13(SD0CLKA)
SD0_IO_B：PB10(SD0DATB)、PB11(SD0CMDB)、PB12(SD0CLKB)
SDMMC1_EN 对应两组可选的 SD 口如下：
SD1_IO_A：PC3(SD1DATA)、PC4(SD1CMDA)、PC5(SD1CLKA)
SD1_IO_B：PB0(SD1DATB)、PB1(SD1CMDB)、PB2(SD1CLKB)


AC69 系列蓝牙配置工具里面的功率调节对应的实际蓝牙发射功率。
0         1        2        3        4       5        6        7    8      9

-24.9     -19.5    -15.7    -11.5    -8.6    -5.6     -3.2     0    2.8    3.1

对于 AC69 系列，如果使用到 RTC 时钟功能，进入了 RTC 睡眠后，需注意如下消息是否
有打开。不然会导致唤醒后时钟不跑。
	set_keep_osci_flag(1);


---------------------------------------------------------------------------------------
          |   普通输出  |    强输出  |   上拉电阻  |  下拉电阻        | 备注
PA0-PA15  |             |            |             |                  |
PB13      |             |      16mA  |    10K      |   60K            |  1，PA3默认下拉
PC0-PC15  |             |            |             |                  |
PR0-PR3   |             |            |             |                  |  2，PB6默认上拉
----------------------------------------------------------------------|  3，PR0  输出0
PB0-PB12  |      8mA	|		24mA |    10K          60K            |
----------------------------------------------------------------------|
DM  DP    |      4mA    |        -   |    1.5K     |   15K            |
---------------------------------------------------------------------------------------

PORTR_PU(PORTR0,1);
PORTR_PD(PORTR0,0);
PORTR_DIR(PORTR0,1);
PORTR_DIE(PORTR0,1);
PORTR_HD(PORTR0,1);
如果把 PR1 或 PR2 作为 AD 口，需要加入下语句。
PORTR1_ADCEN_CTL(1);或 PORTR2_ADCEN_CTL(1);


AC6901A PR0 口语 OSC32KO 绑定一起，用到 OSC32KO，需要把 PR0 设置
为高阻态。
///AC6901A PR0 口语 OSC32KO 绑定一起，用到 OSC32KO，需要把 PR0 设置为高
阻态
///记住务必在此处设置为高阻态
PORTR_PU(PORTR0,0);
PORTR_PD(PORTR0,0);
PORTR_DIR(PORTR0,1);
PORTR_DIE(PORTR0,1);
PORTR_HD(PORTR0,1);

extern void __bt_set_hid_descriptor_flag(u8 flag);
__bt_set_hid_descriptor_flag(1);//解决打开拍照后，键盘没作用

extern u8 get_second_call_status();//三方通话状态


//AC69 系列开 DAC 开高阻态。
#define HP_L_EN(x) JL_AUDIO->DAA_CON0 = ((JL_AUDIO->DAA_CON0
& ~BIT(4)) | ((x & 0x1)<<4))
#define HP_R_EN(x) JL_AUDIO->DAA_CON0 = ((JL_AUDIO->DAA_CON0
& ~BIT(5)) | ((x & 0x1)<<5))




//通过四路 timer 输出 pwm
//Timer0 PWM0 PA1 (做系统 timer，不能用)
//Timer1 PWM1 PA4
//Timer2 PWM2 PB3
//Timer3 PWM3 PB4

//outputchannel0 ：对应 IO 口的 DIE BIT 设置成 0
//outputchannel1 ：对应 IO 口的 DIE BIT 设置成 1


#define POWER_EN()  {usb_2_io();USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(1);} 
#define POWER_DIS()  {usb_2_io();USB_DP_PU(0);USB_DP_PD(0);USB_DP_DIR(0);USB_DP_OUT(0);} 

#define POWER_EN()    {dac_ldo_set(LDO_1, 1);dac_ldo_set(LDO_2, 1);}  
#define POWER_DIS()   {dac_ldo_set(LDO_1, 0);dac_ldo_set(LDO_2, 0);}//JL_AUDIO->DAA_CON0 &= ~(BIT(2)|BIT(3));

//AC69 系列实现 IIC 的 DAT 和 CLK 引脚与 SD 卡 CMD 和 DAT 脚复用。例如 FM 外接收音芯
//片，然后 FM 的 IIC 的 CLK 和 DAT 引脚与 SD0 是 DAT 脚 PA11 和 CMD 脚 PA12 复用。这时 SD
//必 须 CLK 检 测 


//AC69 系列获取蓝牙 MAC 地址
extern void hook_get_mac_addr(u8* btaddr);
u8 local_mac_addr[6];
//hook_get_mac_addr(local_mac_addr);

#endif

#endif
