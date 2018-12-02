/*
PA11  CANRX
PA12  CANTX
*/

#ifndef _CAN_H_
#define _CAN_H_

#include "stm32f10x.h"
#include "GPIO.h"
#include "stm32f10x_can.h"
#include "FIFOBuffer.h"

#define CAN_RX_BUFF 20    //����buffer����

class CAN{
  private:  
    FIFOBuffer<u8,CAN_RX_BUFF>  buffer_R;	//�������buferr
	  //�жϷ�ʽ
		void NVIC_init();
    void init();   
    bool mUseNvic; //�Ƿ�ʹ���жϷ�ʽ	
	  uint8_t mSjw;//����������ͬ����Ծ���(SJW)������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥λ������
	  uint8_t mBs1;
	  uint8_t mBs2;
	  uint8_t mMode;//ģʽ
	  uint8_t mPrescaler;
	
	public:
	  //������ mode :  1�ػ�ģʽ  0������ģʽ
	  //������ = (72000/2) / mPrescaler / (BS1 +BS2 +1)  36M/((1+8+7)*5)=450Kbp
	  //�Ƿ�ʹ���жϷ�ʽ
   	CAN(uint8_t mode=1,uint8_t bs1 =8 ,uint8_t bs2 =7 ,uint8_t pre =5 ,bool useNvic = true);
    void Irq();
	  u8 Can_Send_Msg(u8* msg,u8 len);//����
	  u16 ReceivedBufferSize();//��ȡbuffer����
	  bool GetReceivedData(u8* buffer,u16 number);//ȡ������
	  void ClearReceiveBuffer();//��ս���buffer
	  u8 Can_Receive_Msg(u8 *buf);//��ѯ��ʽ��ȡ
}; 
#endif
