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


#define Modbus_Fun_Code_01                 0x1
#define Modbus_Fun_Code_02                 0x2
#define Modbus_Fun_Code_03                 0x3
#define Modbus_Fun_Code_04                 0x4
#define Modbus_Fun_Code_05                 0x5
#define Modbus_Fun_Code_06                 0x6
#define Modbus_Fun_Code_10                 0x10
#define Modbus_Fun_Code_64                 0x64
#define Modbus_Fun_Code_65                 0x65
#define MAX_LEN_MODBUSTCPDATA           (254)

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
        ushort uiHaltState:1;             //1-停机
        ushort uiStandbyState:1;          //1-待机
        ushort uiRunState:1;              //1-运行
        ushort uiFaultState:1;            //1-故障
        ushort uiAlarmState:1;            //1-告警
        ushort uiSetState:1;              //1-远程，0-就地
        ushort uiFarStopState:1;          //1-急停
        ushort uiOnGridState:1;           //1-并网
        ushort uiOffGridState:1;          //1-离网
        ushort uiOverLoadState:1;         //1-过载
        ushort uiRes1:3;                  //
        ushort uiBMSIn:1;                 //1-故障有效
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

/*Modbus响应报文结构体*/
typedef struct 
{
  Modbus_TCP head;
  unsigned char modbus_funcode;
  unsigned char data[252];
}SModbus_TCP_DataUnit_Rx;
typedef void (*ResponseAct)(SModbus_TCP_DataUnit_Rx*);
typedef struct 
{
    /* data */
};

void sSetFaultReset(ushort value);
ushort sGetFaultReset();
void sSetDeviceStart(ushort value);
ushort sGetDeviceStart();
void sSetDeviceHalt(ushort value);
ushort sGetDeviceHalt();
void sSetRemoteStop(ushort value);
ushort sGetRemoteStop();
void sSetClearCharge(ushort value);
ushort sGetClearCharge();
void sSetClearDischarge(ushort value);
ushort sGetClearDischarge();
void sSetRemoteMode(ushort value);
ushort sGetRemoteMode();

void sSetVolt_A(ushort value);
ushort sGetVolt_A();
void sSetVolt_B(ushort value);
ushort sGetVolt_B();
void sSetVolt_C(ushort value);
ushort sGetVolt_C();
void sSetCurr_A(ushort value);
ushort sGetCurr_A();
void sSetCurr_B(ushort value);
ushort sGetCurr_B();
void sSetCurr_C(ushort value);
ushort sGetCurr_C();
void sSetGridFreq(ushort value);
ushort sGetGridFreq();
void sSetActivePower_A(ushort value);
ushort sGetActivePower_A();
void sSetActivePower_B(ushort value);
ushort sGetActivePower_B();
void sSetActivePower_C(ushort value);
ushort sGetActivePower_C();
void sSetActivePower_ALL(ushort value);
ushort sGetActivePower_ALL();
void sSetReactivePower_A(ushort value);
ushort sGetReactivePower_A();
void sSetReactivePower_B(ushort value);
ushort sGetReactivePower_B();
void sSetReactivePower_C(ushort value);
ushort sGetReactivePower_C();
void sSetReactivePower_ALL(ushort value);
ushort sGetReactivePower_ALL();
void sSetApparentPower_A(ushort value);
ushort sGetApparentPower_A();
void sSetApparentPower_B(ushort value);
ushort sGetApparentPower_B();
void sSetApparentPower_C(ushort value);
ushort sGetApparentPower_C();
void sSetApparentPower_ALL(ushort value);
ushort sGetApparentPower_ALL();
void sSetPowerFactor_A(ushort value);
ushort sGetPowerFactor_A();
void sSetPowerFactor_B(ushort value);
ushort sGetPowerFactor_B();
void sSetPowerFactor_C(ushort value);
ushort sGetPowerFactor_C();
void sSetPowerFactor_ALL(ushort value);
ushort sGetPowerFactor_ALL();
void sSetImportPower(ushort value);
ushort sGetImportPower();
void sSetImportVolt(ushort value);
ushort sGetImportVolt();
void sSetImportCurr(ushort value);
ushort sGetImportCurr();
void sSetRadiatorTem(ushort value);
ushort sGetRadiatorTem();
void sSetRadiatorTem(ushort value);
ushort sGetRadiatorTem();

void sSetWorkingMode(ushort value);
ushort sGetWorkingMode();
void sSetConstant_Volt(ushort value);
ushort sGetConstant_Volt();
void sSetConstant_Curr(ushort value);
ushort sGetConstant_Curr();
void sSetConstantPower_ActivePowerExpect(ushort value);
ushort sGetConstantPower_ActivePowerExpect();
void sSetConstantPower_ReactivePowerExpect(ushort value);
ushort sGetConstantPower_ReactivePowerExpect();
void sSetOn_off_Grid(ushort value);
ushort sGetOn_off_Grid();
void sSetoff_Grid_Volt(ushort value);
ushort sGetoff_Grid_Volt();
void sSetoff_Grid_Freq(ushort value);
ushort sGetoff_Grid_Freq();


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
void TCP_Modbus_Analyze(unsigned char* src,unsigned char* pdata_modbus,SModbus_TCP_DataUnit_Rx* res);
//读离散输入寄存器
void Read_bit_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x02
//读保持寄存器
void Read_HoldingReg_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x03
//读输入寄存器
void Read_InputReg_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x04
//写单个线圈寄存器
void Write_bit_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x05
//写单个保持寄存器
void Write_SingleHoldingReg_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x06
//写多个保持寄存器
void Write_MultiHoldingReg_Act(SModbus_TCP_DataUnit_Rx* RsMsg);//0x10
//响应收到的报文
void ModbusRsData_Act(SModbus_TCP_DataUnit_Rx* RsMsg);

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
//函数功能：打印数组
//入参：*Arr——数据指针;Length——打印长度
//出参：无
//*****************************************************************************
void PrintfUcArr(const uchar *Arr, uchar Length);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
#endif

