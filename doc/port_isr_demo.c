#include "irq_api.h"
///<ע��io���õ��³�ͻ��������demo�����������м��
///<ע���ڲ�ʹ�õ�ʱ�� Ҫ����port_isr_exit,ȷ���жϲ����󴥷����������͹���ǰҪȷ���ⲿ�ж��ѹر�


#define PA14_ISR 0
#define PA10_ISR 1
#define PA8_ISR	 2

#define PORT_ISR_SEL	PA14_ISR
void port_isr(void)
{
#if (PORT_ISR_SEL == PA8_ISR)	
	JL_WAKEUP->CON2 |= BIT(2);
#elif (PORT_ISR_SEL == PA10_ISR)	
	JL_WAKEUP->CON2 |= BIT(3);
#elif (PORT_ISR_SEL == PA14_ISR)	
	JL_WAKEUP->CON2 |= BIT(4);
#endif


	printf("-------------\n");
}

IRQ_REGISTER(IRQ_PORT_IDX, port_isr);


void port_isr_init(void)
{
#if (PORT_ISR_SEL == PA8_ISR)	
	JL_PORTA->DIR |= BIT(8);
	JL_PORTA->DIE |= BIT(8);
	JL_PORTA->PU |= BIT(8);
	JL_PORTA->PD &= ~BIT(8);
	/* JL_PORTA->PU &= ~BIT(8); */
	/* JL_PORTA->PD |= BIT(8); */

	JL_WAKEUP->CON0 |= BIT(2);//���PA8��ƽ����
	JL_WAKEUP->CON1 |= BIT(2);//�½��ش���
	/* JL_WAKEUP->CON0 &= ~BIT(2);//�����ش��� */
	JL_WAKEUP->CON2 |= BIT(2);
#elif (PORT_ISR_SEL == PA10_ISR)	
	JL_PORTA->DIR |= BIT(10);
	JL_PORTA->DIE |= BIT(10);
	JL_PORTA->PU |= BIT(10);
	JL_PORTA->PD &= ~BIT(10);
	/* JL_PORTA->PU &= ~BIT(10); */
	/* JL_PORTA->PD |= BIT(10); */

	JL_WAKEUP->CON0 |= BIT(3);//���PA8��ƽ����
	JL_WAKEUP->CON1 |= BIT(3);//�½��ش���
	/* JL_WAKEUP->CON0 &= ~BIT(3);//�����ش��� */
	JL_WAKEUP->CON2 |= BIT(3);
#elif (PORT_ISR_SEL == PA14_ISR)	
	JL_PORTA->DIR |= BIT(14);
	JL_PORTA->DIE |= BIT(14);
	JL_PORTA->PU |= BIT(14);
	JL_PORTA->PD &= ~BIT(14);
	/* JL_PORTA->PU &= ~BIT(14); */
	/* JL_PORTA->PD |= BIT(14); */

	JL_WAKEUP->CON0 |= BIT(4);//���PA8��ƽ����
	JL_WAKEUP->CON1 |= BIT(4);//�½��ش���
	/* JL_WAKEUP->CON0 &= ~BIT(4);//�����ش��� */
	JL_WAKEUP->CON2 |= BIT(4);
#endif
    IRQ_REQUEST(IRQ_PORT_IDX, port_isr, 3);
}
void port_isr_exit(void)
{
    irq_handler_unregister(IRQ_PORT_IDX);
}



