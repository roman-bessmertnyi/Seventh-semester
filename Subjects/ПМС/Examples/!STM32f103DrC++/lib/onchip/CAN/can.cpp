#include "can.h"
#include "Interrupt.h"
/* 
  CAN_Mode_Normal          ����ģʽ
  CAN_Mode_LoopBack        ����ģʽ
  CAN_Mode_Silent          ��Ĭģʽ
  CAN_Mode_Silent_LoopBack ��Ĭ����ģʽ  
*/

/*
CAN_SJW ����������ͬ����Ծ���(SJW)������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥λ������
CAN_SJW_1tq ����ͬ����Ծ��� 1 ��ʱ�䵥λ
CAN_SJW_2tq ����ͬ����Ծ��� 2 ��ʱ�䵥λ
CAN_SJW_3tq ����ͬ����Ծ��� 3 ��ʱ�䵥λ
CAN_SJW_4tq ����ͬ����Ծ��� 4 ��ʱ�䵥λ

*/

/*
CAN_BS1 �趨��ʱ��� 1 ��ʱ�䵥λ��Ŀ
CAN_BS1_1tq ʱ��� 1 Ϊ 1 ��ʱ�䵥λ
�� ��
CAN_BS1_16tq ʱ��� 1 Ϊ 16 ��ʱ�䵥λ
*/

/*
CAN_BS2 �趨��ʱ��� 1 ��ʱ�䵥λ��Ŀ
CAN_BS2_1tq ʱ��� 2 Ϊ 1 ��ʱ�䵥λ
�� ��
CAN_BS2_8tq ʱ��� 2 Ϊ 8 ��ʱ�䵥λ
*/

/*
������ = (72000/2) / mPrescaler / (BS1 +BS2 +1)
*/

void CAN::NVIC_init()
{
	NVIC_InitTypeDef  NVIC_InitStructure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // �����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void CAN::init()
{

	 //GPIO ʱ�ӳ�ʼ��
   GPIO_InitTypeDef GPIO_InitStructure; 
	 CAN_InitTypeDef CAN_InitStructure;
	 CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��IO
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
   GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO
	
		 
	 //CAN��ʼ��	 
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
		
	CAN_InitStructure.CAN_TTCM=DISABLE;						 //��ʱ�䴥��ͨ��ģʽ  //
	CAN_InitStructure.CAN_ABOM=DISABLE;						 //����Զ����߹���	 //
	CAN_InitStructure.CAN_AWUM=DISABLE;						 //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
	CAN_InitStructure.CAN_NART=DISABLE;						 //��ֹ�����Զ����� //
	CAN_InitStructure.CAN_RFLM=DISABLE;						 //���Ĳ�����,�µĸ��Ǿɵ� // 
	CAN_InitStructure.CAN_TXFP=DISABLE;						 //���ȼ��ɱ��ı�ʶ������ //
	CAN_InitStructure.CAN_Mode= mMode;   //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
		
		  	//���ò�����
	CAN_InitStructure.CAN_SJW=mSjw;				   //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1=mBs1;         //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2=mBs2;         //Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler=mPrescaler;    //CAN_Prescaler �趨��һ��ʱ�䵥λ�ĳ��ȣ����ķ�Χ�� 1 �� 1024
	CAN_Init(CAN1, &CAN_InitStructure);       //��ʼ��CAN1 
	
	 //��������ʼ��	
	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0  ��Χ0-13
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; // CAN_FilterMode_IdMask ��ʶ������λģʽ   CAN_FilterMode_IdList ��ʶ���б�ģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; // ������λ�� CAN_FilterScale_Two16bit 2 �� 16 λ������  CAN_FilterScale_One32bit 1 �� 32 λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID  �趨��������ʶ��
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK �����趨���������α�ʶ�����߹�������ʶ��
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
   
	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0|CAN_IT_TME,ENABLE);
	//CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.	
	if(mUseNvic)
	{
		pCAN = this;
		NVIC_init();
	}
	
}

CAN::CAN(uint8_t mode,uint8_t bs1,uint8_t bs2,uint8_t pre ,bool useNvic)
{
	//���ݳ�ʼ��
	
	mUseNvic =useNvic; //�Ƿ�ʹ���жϷ�ʽ	
	mSjw =  CAN_SJW_1tq;//����������ͬ����Ծ���(SJW)������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥λ������
	mBs1 =  bs1;  
	mBs2 =  bs2;
	mMode = mode; 
	mPrescaler = pre;  
	init();
	buffer_R.Clear();
}  

//�жϷ�����			    
void CAN::Irq(void)
{
   CanRxMsg RxMessage;
   CAN_Receive(CAN1, 0, &RxMessage);
	 buffer_R.Puts(RxMessage.Data,RxMessage.DLC);//�����յ������ݴ���buffer
}


void CAN::ClearReceiveBuffer()
{
	buffer_R.Clear();
}

//��ȡbuffer����
u16 CAN::ReceivedBufferSize()
{
	return buffer_R.Size();
}

//�������
bool CAN::GetReceivedData(u8* buffer,u16 number)
{
	if(buffer_R.Size()<number)//û���㹻��������
		return false;
	else
	{
		buffer_R.Gets(buffer,number);//���ݳ���
		return true;
	}
}

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN::Can_Send_Msg(u8* msg,u8 len)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x00;					 // ��׼��ʶ�� 
  //TxMessage.ExtId=0x00;				   // ������չ��ʾ�� 
  TxMessage.IDE=CAN_Id_Standard; // ��׼֡
  TxMessage.RTR=CAN_RTR_Data;		 // ����֡
  TxMessage.DLC=len;					 	// Ҫ���͵����ݳ���
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];			          
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)
		return 1;
  return 0;		
}
//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN::Can_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<8;i++)
       buf[i]=RxMessage.Data[i];  
	  return RxMessage.DLC;	
}
