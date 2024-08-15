/******************************************************************
 CopyRight:   H3C ALL rights reserved
 File name:   can.h
 Description: Communication by can 2.0B
 Author:      Zhang Jiawei
 Version:     V00
 Data:        2023-10
 *****************************************************************/
//#include "Module\include\includes.h"

typedef unsigned char    uchar;
typedef unsigned short   ushort;
typedef unsigned int     uint;
typedef unsigned long    ulong;

typedef int (*pGet)(void);
typedef void (*pSet)(int);


typedef struct  {
    ushort Addr;
    short Length;
    pGet    iGet;
}CanSt3X;

typedef struct  {
    ushort Addr;
    short Length;
    int imin;
    int imax;
    pSet    iSet;
    pGet    iGet;
}CanSt4X;



#define CAN_Fun_Code_02                 0x2
#define CAN_Fun_Code_03                 0x3
#define CAN_Fun_Code_04                 0x4
#define CAN_Fun_Code_05                 0x5
#define CAN_Fun_Code_06                 0x6
#define CAN_Fun_Code_10                 0x10
#define CAN_Fun_Code_64                 0x64
#define CAN_Fun_Code_65                 0x65
#define MAX_LEN_MODBUSTCPDATA           (252)
#define MPBA_LENGTH                     (7)
#define MODBUSFUNCODE_LENTH             (1)

extern volatile ushort Fun_Code ;
extern volatile ushort Start_address ;
extern volatile ushort Modbus_Length ;
extern volatile ushort End_address ;

extern ushort w3xLen;
extern ushort w4xLen;

extern ushort ModbusProcFlag;
extern ushort ModbusProcLength;

typedef struct  {
    ushort usSerialNum;
    ushort usRes;
    ushort usLength;
    uchar  unit_id;
}Modbus_TCP;
extern Modbus_TCP stModbus_TCPHead;

typedef union{
    ushort FAULT_WORD;
    struct {
        ushort uiFaultReset:1;            //
        ushort uiEquipOpen:1;             //
        ushort uiEquipHalt:1;             //
        ushort uiFarStop:1;               //
        ushort uiChargePowerClean:1;      //
        ushort uiDischargePowerClean:1;   //
        ushort uiSetMode:1;               //
        ushort ucBagCom:9;                //
    } BIT;
} CAN_FAULT_WORD;

typedef union{
    ushort YX_WORD;
    struct {
        ushort uiHaltState:1;             //
        ushort uiStandbyState:1;          //
        ushort uiRunState:1;              //
        ushort uiFaultState:1;            //
        ushort uiAlarmState:1;            //
        ushort uiSetState:1;              //
        ushort uiFarStopState:1;          //
        ushort uiOnGridState:1;           //
        ushort uiOffGridState:1;          //
        ushort uiOverLoadState:1;         //
        ushort uiRes1:3;                  //
        ushort uiBMSIn:1;                 //
        ushort uiRes2:2;                  //
    } BIT;
} CAN_YX_WORD;

typedef struct  {
unsigned char ucAddrField;
unsigned char ucFun_Code;            //
unsigned char ucAddr_H;
unsigned char ucAddr_L;
unsigned char ucRegNum_H;
unsigned char ucRegNum_L;
unsigned char ucCRC_H;
unsigned char ucCRC_L;
}Can_Message_Modbus;

/*Modbus报文结构体*/
typedef struct 
{
  Modbus_TCP head;
  unsigned char modbus_funcode;
  uchar modbus_addr;
  unsigned char data[MAX_LEN_MODBUSTCPDATA];
}SModbus_TCP_DataUnit;
typedef void (*ResponseAct)(SModbus_TCP_DataUnit*);
typedef void (*GetAnswerFrame)(SModbus_TCP_DataUnit*,SModbus_TCP_DataUnit*);


void sSetYear(ushort value);
ushort sGetYear();
void sSetMonth(ushort value);
ushort sGetMonth();
void sSetDay(ushort value);
ushort sGetDay();
void sSetActivePower(uint value);
uint sGetActivePower();
void sSetReactivePower(uint value);
uint sGetReactivePower();

void sFlashControl(ushort value);
ushort sFlashGet();

//*****************************************************************************
//函数功能：Modbus数据初始化
//入参：无
//出参：无
//*****************************************************************************
extern void Modbus_Initial();
//*****************************************************************************
//函数功能：解析4x数据
//入参：arrar4X——数据指针;length——包长;pdata——数据指针
//出参：无
//*****************************************************************************
void sSetParamData(const CanSt4X* arrar4X,ushort length,unsigned char *pdata);
//*****************************************************************************
//函数功能：打包3x数据
//入参：arrar3X——数据指针;length——包长;pdata——数据指针
//出参：无
//*****************************************************************************
void sPackage3xData(const CanSt3X * arrar3X,ushort length,unsigned char *pdata);
//*****************************************************************************
//函数功能：解析数据
//入参：*pdata——数据指针;len——包长
//出参：无
//*****************************************************************************
ushort Modbus_Proc_Data(unsigned char *pdata, const ushort len);

void TCP_Modbus_Send(ushort FunCode, ushort startaddr, ushort len, unsigned char * SendData);

ushort strlen_uc(const unsigned char* ustr);
void get_MBAP_FromTCPdata(unsigned char* data,Modbus_TCP* head);
void TCP_Modbus_Analyze(unsigned char* src,unsigned char* pdata_modbus,SModbus_TCP_DataUnit* res);
//读离散输入寄存器
void Read_bit_Act(SModbus_TCP_DataUnit* RxMsg);//0x02
//读保持寄存器
void Read_HoldingReg_Act(SModbus_TCP_DataUnit* RxMsg,SModbus_TCP_DataUnit* TxMsg);//0x03
//读输入寄存器
void Read_InputReg_Act(SModbus_TCP_DataUnit* RxMsg);//0x04
//写单个线圈寄存器
void Write_bit_Act(SModbus_TCP_DataUnit* RxMsg);//0x05
//写单个保持寄存器
void Write_SingleHoldingReg_Act(SModbus_TCP_DataUnit* RxMsg);//0x06
//写多个保持寄存器
void Write_MultiHoldingReg_Act(SModbus_TCP_DataUnit* RxMsg);//0x10
//响应收到的报文
void ModbusRsData_Act(SModbus_TCP_DataUnit* RxMsg);

////*****************************************************************************
////函数功能：连续8位合成16位
////入参：*pdata——数据指针
////出参：Data值
////*****************************************************************************
ushort iDataCom_8to16(unsigned char *pdata);
////*****************************************************************************
////函数功能：连续8位合成32位
////入参：*pdata——数据指针
////出参：Data值
////*****************************************************************************
uint iDataCom_8to32(unsigned char *pdata);
////*****************************************************************************
////函数功能：16位拆成8位
////入参：Selfdata——自身数据,*pdata——数据指针
////出参：无
////*****************************************************************************
void iDataCom_16to8(ushort Selfdata ,unsigned char *pdata);
////*****************************************************************************
////函数功能：16位长数据拆成8位
////入参：Selfdata——自身数据,*pdata——数据指针,len——长度
////出参：无
////*****************************************************************************
void iLongDataCom_16to8(ushort *Selfdata ,uchar *pdata ,ushort len);
////*****************************************************************************
////函数功能：32位拆成8位
////入参：Selfdata——自身数据,*pdata——数据指针
////出参：无
////*****************************************************************************
void iDataCom_32to8(uint Selfdata ,unsigned char *pdata);
//*****************************************************************************
//函数功能：解析4x数据
//入参：P4X——数据指针;length——包长;pdata——数据指针
//出参：无
//*****************************************************************************
void sSetParamData(const CanSt4X* P4X,ushort length,unsigned char *pdata);
//*****************************************************************************
//函数功能：解析数据
//入参：*pdata——数据指针;len——包长
//出参：无
//*****************************************************************************
extern ushort Modbus_Proc_Data(unsigned char *pdata, const ushort len);
//*****************************************************************************
//函数功能：CRC16位校验
//入参：*puchMsg——数据指针;usDataLen——数据包长度
//出参：crc校验值
//*****************************************************************************
extern ushort CRC16_MODBUS(unsigned char *puchMsg, uint usDataLen);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
#endif

