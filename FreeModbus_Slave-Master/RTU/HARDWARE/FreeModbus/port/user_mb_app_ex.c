
/* USER CODE BEGIN Includes */
#include "bsp.h"
#include "mb_m.h"
#include "user_mb_app.h"

//master
extern UCHAR    ucMDiscInBuf[];
extern UCHAR		ucMCoilBuf[];
extern USHORT 	usMRegInBuf[];	
extern USHORT		usMRegHoldBuf[];

//slave
extern UCHAR    ucSDiscInBuf[];
extern UCHAR		ucSCoilBuf[];
extern USHORT 	usSRegInBuf[];	
extern USHORT		usSRegHoldBuf[];
//////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------Master mode use these variables----------------------*/
#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
/*
 * MBSetCoil
 * Hàm này dùng d? ghi giá tr? 1 coil nào dó (giá tr? 0|1)
 * Tham s? bitOfset có nghia là v? trí c?a bit dó
 * Tham s? th? 2 là giá tr? d?t cho Coil (0-1)
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REC_COIL_START   30 -> T?c là vùng nh? Coil du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REC_COIL_START + REC_COIL_NREGS-1 thì hàm cung tr? v? l?i này
 * Write: STM32VN
 * Gmail: 
*/
eMBAccessDataCode M_MBSetCoil(USHORT bitOfset, char value)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Mybyte=0;
     
    /* ---------- Check Address Correction -------------*/
     
    #if M_COIL_START -1 >0
    if (bitOfset < M_COIL_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (M_COIL_START + M_COIL_NCOILS -1)) return ACCESS_ADDR_ERR;
     
    USHORT DeltaBitOffset = bitOfset - M_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
 
     
    Mybyte = 1;
    Mybyte = Mybyte << (BitAddr);
    if (value == 1)
    {
            ucMCoilBuf[ByteAddr]|= Mybyte;
    }
    else
    {
            Mybyte = ~ Mybyte;
            ucMCoilBuf[ByteAddr] &= Mybyte;
    }
     
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * MBGetCoil
 * Hàm này dùng d? l?y giá tr? c?a 1 coil trong thanh ghi
 * bitOfset là d?a ch? bit
 * GetValue là 1 con tr? tr? v? giá tr? c?a Bit c?n bi?t
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REC_COIL_START   30 -> T?c là vùng nh? Coil du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REC_COIL_START + REC_COIL_NREGS-1 thì hàm cung tr? v? l?i này
 * Write: STM32VN
 * Gmail: 
*/
eMBAccessDataCode M_MBGetCoil(USHORT bitOfset, UCHAR* GetValue)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Result  = 0;
     
    /* ---------- Check Address Correction -------------*/
    #if M_COIL_START - 1 >0
    if (bitOfset < M_COIL_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (M_COIL_START + M_COIL_NCOILS -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset - M_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
     
    Result = ucMCoilBuf[ByteAddr] >> BitAddr;
    Result &= (UCHAR)1;
     
    *GetValue = Result;
     
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * MBSetDescretesInputbit
 * Hàm này dùng d? ghi 1 bit vào Vùng nh? Descretes Input
 * bitOfset là v? trí bit c?n set
 * value là giá tr? c?n set cho bit
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REG_DESCRETES_INPUT_START   30 -> T?c là vùng nh? DescretesInput du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REG_DESCRETES_INPUT_START + REG_DESCRETES_INPUT_NREGS-1 thì hàm cung tr? v? l?i này
 
 * Write: STM32VN
*/
eMBAccessDataCode M_MBSetDescretesInputbit(USHORT bitOfset, char value)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Mybyte;
    /* ---------- Check Address Correction -------------*/
    #if M_DESCRETES_INPUT_START - 1 >0
    if (bitOfset < (M_DESCRETE_INPUT_START )) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (M_DISCRETE_INPUT_START + M_DISCRETE_INPUT_NDISCRETES -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset  - M_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
 
 
    Mybyte = 1;
    Mybyte = Mybyte << (BitAddr);
    if (value == 1)
    {
            ucMDiscInBuf[ByteAddr]|= Mybyte;
    }
    else
    {
            Mybyte = ~ Mybyte;
            ucMDiscInBuf[ByteAddr] &= Mybyte;
    }
     
    return ACCESS_NO_ERR;
 
}
//
 
/*
 * MBGetDescretesInputbit
 * Hàm này dùng d? l?y giá tr? c?a 1 bit trong thanh ghi DescretesInput (thanh ghi Bit, Master ch? d?c)
 * bitOfset là v? trí bit c?n set
 * GetValue là con tr? nh?n v? giá tr? c?a bit c?n l?y.
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REG_DESCRETES_INPUT_START   30 -> T?c là vùng nh? DescretesInput du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REG_DESCRETES_INPUT_START + REG_DESCRETES_INPUT_NREGS-1 thì hàm cung tr? v? l?i này
 
 * Write: STM32VN
*/
eMBAccessDataCode M_MBGetDescretesInputbit(USHORT bitOfset, UCHAR* GetValue)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Result  = 0;
     
    /* ---------- Check Address Correction -------------*/
    #if M_DISCRETE_INPUT_START - 1 > 0
    if (bitOfset < M_DISCRETE_INPUT_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (M_DISCRETE_INPUT_START + M_DISCRETE_INPUT_NDISCRETES -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset - M_DISCRETE_INPUT_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
     
    Result = ucMDiscInBuf[ByteAddr] >> BitAddr;
    Result &= (UCHAR)1;
     
    *GetValue = Result;
     
    return ACCESS_NO_ERR;
}

 
/*
 *  Write: STM32VN
 *  Hàm này dùng d? trích xu?t d? li?u 16bit t? các thanh ghi modbus
 *  Ví d? c?n l?y d? li?u 16 bit t?i d?a ch? 45 c?a thanh ghi REG INPUT
 *  MBGetData16Bits(REG_INPUT, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode M_MBGetData16Bits(MB_Data_Type DataType, USHORT Address, USHORT* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress16;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /* ---------Check Address Correction ------------ */
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress16 = M_REG_INPUT_START + M_REG_INPUT_NREGS -1;
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
 
            /* --------Assign Data ------------*/
            *Value = usMRegInBuf[Address - BeginAddress ];
         
            break;
         
        case REG_HOLDING:
            /* ------ Check Address correction --------*/
            BeginAddress = M_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress16 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -1;
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
         
            /* -------- Assign Data -------------*/
            *Value = usMRegHoldBuf[Address - BeginAddress];
         
            break;
         
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    return ACCESS_NO_ERR;
}
//
 
/*
 * Write: STM32VN
 *  Hàm này dùng d? trích xu?t d? li?u 32bit t? các thanh ghi modbus
 *  Ví d? c?n l?y d? li?u 32 bit t?i d?a ch? 45 c?a thanh ghi REG HOLDING
 *  MBGetData32Bits(REG_HOLDING, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode M_MBGetData32Bits(MB_Data_Type DataType, USHORT Address, ULONG* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
     
    USHORT HightData = 0;
    USHORT LowData = 0;
    ULONG Result = 0;
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = M_REG_INPUT_START + M_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
            LowData = usMRegInBuf[Address - BeginAddress ];
            HightData = usMRegInBuf[Address - BeginAddress + 1];
//						LowData = (usMRegInBuf[Address - BeginAddress ]>>8)|((usMRegInBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usMRegInBuf[Address - BeginAddress +1]>>8)|((usMRegInBuf[Address - BeginAddress +1]&0x00ff)<<8);
         
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            LowData = usMRegHoldBuf[Address - BeginAddress ];
            HightData = usMRegHoldBuf[Address - BeginAddress + 1];
//						LowData = (usMRegHoldBuf[Address - BeginAddress ]>>8)|((usMRegHoldBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usMRegHoldBuf[Address - BeginAddress +1]>>8)|((usMRegHoldBuf[Address - BeginAddress +1]&0x00ff)<<8);
         
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    Result = ((ULONG)HightData)<<16;
    Result += LowData;
     
    *Value = Result;
     
    return ACCESS_NO_ERR;
}
//
 
/*
*   Write: STM32VN
*   Hàm này dùng d? thay d?i d? li?u 16bit c?a thanh ghi Modbus
* Ví d? mu?n gán giá tr? 325 cho thanh ghi Holding t?i d?a ch? 170 thì th?c hi?n nhu sau:
* MBSetData16Bits(REG_HOLDING, 170, 325);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode M_MBSetData16Bits(MB_Data_Type DataType, USHORT Address, USHORT Value)
{
    USHORT BeginAddress;
    USHORT LastAddress16;
     
    switch (DataType)
    {
        case    REG_INPUT:
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1 )) return ACCESS_ADDR_ERR; 
            LastAddress16 = M_REG_INPUT_START + M_REG_INPUT_NREGS -1;
         
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
 
            usMRegInBuf[Address - BeginAddress ] = Value;
         
            break;
        case REG_HOLDING:
            BeginAddress = M_REG_HOLDING_START;
            if (Address <( BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress16 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -1;
         
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
         
            usMRegHoldBuf[Address - BeginAddress ] = Value;
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
*   Write: STM32VN
*   hàm này dùng d? thay d?i d? li?u 32bit c?a thanh ghi Modbus
* Ví d?: C?n ghi giá tr? 0x554433 vào d?a ch? 100 c?a thanh ghi HOLDING
* MBSetData32Bits(REG_HOLDING, 100, 0x554433);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode M_MBSetData32Bits(MB_Data_Type DataType, USHORT Address, ULONG Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
     
    USHORT HightData = (Value & 0xFFFF0000)>>16;
    USHORT LowData = (Value & 0x0000FFFF);
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = M_REG_INPUT_START + M_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
        usMRegInBuf[Address - BeginAddress ] = LowData;   // Origin: HightData//(LowData>>8)|((LowData&0x00ff)<<8);//
        usMRegInBuf[Address - BeginAddress + 1] = HightData;  // Origin: LowData//(HightData>>8)|((HightData&0x00ff)<<8);//
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            usMRegHoldBuf[Address - BeginAddress ] = LowData;//(LowData>>8)|((LowData&0x00ff)<<8);//
            usMRegHoldBuf[Address - BeginAddress + 1] = HightData;//(HightData>>8)|((HightData&0x00ff)<<8);//
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
*   Write: STM32VN
*   hàm này dùng d? thay d?i d? li?u float c?a thanh ghi Modbus
* Ví d?: C?n ghi giá tr? 324.434 vào d?a ch? 100 c?a thanh ghi HOLDING
* MBSetFloatData(REG_HOLDING, 100, 324.434);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
 
typedef union M_data {
  float f;
  char  s[4];
    uint32_t U32;
} M_myData;
 
 
eMBAccessDataCode M_MBSetFloatData(MB_Data_Type DataType, USHORT Address, float Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
 
    M_myData q;
    q.f = Value;
     
    USHORT *HightData;
    USHORT *LowData;
     
    HightData = (USHORT*)q.s +1;
    LowData = (USHORT *)q.s ;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = M_REG_INPUT_START + M_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
        usMRegInBuf[Address - BeginAddress ] = *LowData;   // Origin: HightData //(*LowData>>8)|((*LowData&0x00ff)<<8);//
        usMRegInBuf[Address - BeginAddress + 1] = *HightData; // Origin: LowData//(*HightData>>8)|((*HightData&0x00ff)<<8);//
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            usMRegHoldBuf[Address - BeginAddress ] = *LowData;//(*LowData>>8)|((*LowData&0x00ff)<<8);//
            usMRegHoldBuf[Address - BeginAddress + 1] = *HightData;//(*HightData>>8)|((*HightData&0x00ff)<<8);//
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * Write: 
 *  Hàm này dùng d? trích xu?t d? li?u float t? thanh ghi luu tr? d? li?u
 *  Ví d? c?n l?y d? li?u float  t?i d?a ch? 45 c?a thanh ghi REG HOLDING
 *  MBGetFloatData(REG_HOLDING, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
#include <math.h>
#include <float.h>
 
eMBAccessDataCode M_MBGetFloatData(MB_Data_Type DataType, USHORT Address, float* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
    char *P;
 
     
    USHORT HightData = 0;
    USHORT LowData = 0;
 
    M_myData  Result;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = M_REG_INPUT_START + M_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
//            LowData = (usMRegInBuf[Address - BeginAddress ]>>8)|((usMRegInBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usMRegInBuf[Address - BeginAddress +1]>>8)|((usMRegInBuf[Address - BeginAddress +1]&0x00ff)<<8);
							LowData = usMRegInBuf[Address - BeginAddress ];
							HightData = usMRegInBuf[Address - BeginAddress + 1];
				
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = M_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = M_REG_HOLDING_START + M_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            LowData = usMRegHoldBuf[Address - BeginAddress ];
            HightData = usMRegHoldBuf[Address - BeginAddress + 1];
//						LowData = (usMRegHoldBuf[Address - BeginAddress ]>>8)|((usMRegHoldBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usMRegHoldBuf[Address - BeginAddress +1]>>8)|((usMRegHoldBuf[Address - BeginAddress +1]&0x00ff)<<8);
         
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
 
     
    P = (char*)&LowData;
    Result.s[0] = *P;
    Result.s[1] = *(P +1);
     
    P = (char*)&HightData;
    Result.s[2] = *P;
    Result.s[3] = *(P + 1);
     
    *Value = Result.f;
    float val = Result.f;
        switch(fpclassify(*Value)) {
                case FP_INFINITE:  
                    *Value = 0; 
                    break;//return "Inf";
                case FP_NAN:       
                    *Value = 0; 
                break;//return "NaN";
                case FP_NORMAL:    
                    break;//return "normal";
                case FP_SUBNORMAL: 
                    *Value = 0; 
                    break;//return "subnormal";
                case FP_ZERO:       
                    break;//return "zero";
                default:
                    *Value = 0;
                    break;//return "unknown";
        }
     
    if (val > (float)10000.0)
        *Value = 0;
    if (val <(float)-10000.0)
        *Value = 0;
    if ((val > (float)0)&&(val < (float)0.0000001))   *Value = 0;
     
    return ACCESS_NO_ERR;
}
//

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/*
 * MBSetCoil
 * Hàm này dùng d? ghi giá tr? 1 coil nào dó (giá tr? 0|1)
 * Tham s? bitOfset có nghia là v? trí c?a bit dó
 * Tham s? th? 2 là giá tr? d?t cho Coil (0-1)
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REC_COIL_START   30 -> T?c là vùng nh? Coil du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REC_COIL_START + REC_COIL_NREGS-1 thì hàm cung tr? v? l?i này
 * Write: STM32VN
 * Gmail: 
*/
eMBAccessDataCode S_MBSetCoil(USHORT bitOfset, char value)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Mybyte=0;
     
    /* ---------- Check Address Correction -------------*/
     
    #if S_COIL_START -1 >0
    if (bitOfset < S_COIL_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (S_COIL_START + S_COIL_NCOILS -1)) return ACCESS_ADDR_ERR;
     
    USHORT DeltaBitOffset = bitOfset - S_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
 
     
    Mybyte = 1;
    Mybyte = Mybyte << (BitAddr);
    if (value == 1)
    {
            ucSCoilBuf[ByteAddr]|= Mybyte;
    }
    else
    {
            Mybyte = ~ Mybyte;
            ucSCoilBuf[ByteAddr] &= Mybyte;
    }
     
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * MBGetCoil
 * Hàm này dùng d? l?y giá tr? c?a 1 coil trong thanh ghi
 * bitOfset là d?a ch? bit
 * GetValue là 1 con tr? tr? v? giá tr? c?a Bit c?n bi?t
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REC_COIL_START   30 -> T?c là vùng nh? Coil du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REC_COIL_START + REC_COIL_NREGS-1 thì hàm cung tr? v? l?i này
 * Write: STM32VN
 * Gmail: 
*/
eMBAccessDataCode S_MBGetCoil(USHORT bitOfset, UCHAR* GetValue)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Result  = 0;
     
    /* ---------- Check Address Correction -------------*/
    #if S_COIL_START - 1 >0
    if (bitOfset < S_COIL_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (S_COIL_START + S_COIL_NCOILS -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset - S_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
     
    Result = ucSCoilBuf[ByteAddr] >> BitAddr;
    Result &= (UCHAR)1;
     
    *GetValue = Result;
     
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * MBSetDescretesInputbit
 * Hàm này dùng d? ghi 1 bit vào Vùng nh? Descretes Input
 * bitOfset là v? trí bit c?n set
 * value là giá tr? c?n set cho bit
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REG_DESCRETES_INPUT_START   30 -> T?c là vùng nh? DescretesInput du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REG_DESCRETES_INPUT_START + REG_DESCRETES_INPUT_NREGS-1 thì hàm cung tr? v? l?i này
 
 * Write: STM32VN
*/
eMBAccessDataCode S_MBSetDescretesInputbit(USHORT bitOfset, char value)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Mybyte;
    /* ---------- Check Address Correction -------------*/
    #if S_DESCRETES_INPUT_START - 1 >0
    if (bitOfset < (S_DESCRETE_INPUT_START )) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (S_DISCRETE_INPUT_START + S_DISCRETE_INPUT_NDISCRETES -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset  - S_COIL_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
 
 
    Mybyte = 1;
    Mybyte = Mybyte << (BitAddr);
    if (value == 1)
    {
            ucSDiscInBuf[ByteAddr]|= Mybyte;
    }
    else
    {
            Mybyte = ~ Mybyte;
            ucSDiscInBuf[ByteAddr] &= Mybyte;
    }
     
    return ACCESS_NO_ERR;
 
}
//
 
/*
 * MBGetDescretesInputbit
 * Hàm này dùng d? l?y giá tr? c?a 1 bit trong thanh ghi DescretesInput (thanh ghi Bit, Master ch? d?c)
 * bitOfset là v? trí bit c?n set
 * GetValue là con tr? nh?n v? giá tr? c?a bit c?n l?y.
 * Hàm tr? v? :
 *  ACCESS_NO_ERR: N?u không có l?i gì
 *  ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
 *              Ví d?: #define REG_DESCRETES_INPUT_START   30 -> T?c là vùng nh? DescretesInput du?c truy c?p t? d?a ch? 30 tr? lên
 *                  N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
 *                  N?u d?a ch? > REG_DESCRETES_INPUT_START + REG_DESCRETES_INPUT_NREGS-1 thì hàm cung tr? v? l?i này
 
 * Write: STM32VN
*/
eMBAccessDataCode S_MBGetDescretesInputbit(USHORT bitOfset, UCHAR* GetValue)
{
    UCHAR ByteAddr=0, BitAddr=0;
    UCHAR Result  = 0;
     
    /* ---------- Check Address Correction -------------*/
    #if S_DISCRETE_INPUT_START - 1 > 0
    if (bitOfset < S_DISCRETE_INPUT_START ) return ACCESS_ADDR_ERR;
    #endif
    if (bitOfset > (S_DISCRETE_INPUT_START + S_DISCRETE_INPUT_NDISCRETES -1)) return ACCESS_ADDR_ERR;
     
     
    USHORT DeltaBitOffset = bitOfset - S_DISCRETE_INPUT_START;
     
    ByteAddr = DeltaBitOffset/8;
    BitAddr = DeltaBitOffset %8;
     
    Result = ucSDiscInBuf[ByteAddr] >> BitAddr;
    Result &= (UCHAR)1;
     
    *GetValue = Result;
     
    return ACCESS_NO_ERR;
}

 
/*
 *  Write: STM32VN
 *  Hàm này dùng d? trích xu?t d? li?u 16bit t? các thanh ghi modbus
 *  Ví d? c?n l?y d? li?u 16 bit t?i d?a ch? 45 c?a thanh ghi REG INPUT
 *  MBGetData16Bits(REG_INPUT, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode S_MBGetData16Bits(MB_Data_Type DataType, USHORT Address, USHORT* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress16;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /* ---------Check Address Correction ------------ */
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress16 = S_REG_INPUT_START + S_REG_INPUT_NREGS -1;
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
 
            /* --------Assign Data ------------*/
            *Value = usSRegInBuf[Address - BeginAddress ];
         
            break;
         
        case REG_HOLDING:
            /* ------ Check Address correction --------*/
            BeginAddress = S_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress16 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -1;
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
         
            /* -------- Assign Data -------------*/
            *Value = usSRegHoldBuf[Address - BeginAddress];
         
            break;
         
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    return ACCESS_NO_ERR;
}
//
 
/*
 * Write: STM32VN
 *  Hàm này dùng d? trích xu?t d? li?u 32bit t? các thanh ghi modbus
 *  Ví d? c?n l?y d? li?u 32 bit t?i d?a ch? 45 c?a thanh ghi REG HOLDING
 *  MBGetData32Bits(REG_HOLDING, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode S_MBGetData32Bits(MB_Data_Type DataType, USHORT Address, ULONG* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
     
    USHORT HightData = 0;
    USHORT LowData = 0;
    ULONG Result = 0;
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = S_REG_INPUT_START + S_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
            LowData = usSRegInBuf[Address - BeginAddress ];
            HightData = usSRegInBuf[Address - BeginAddress + 1];
//						LowData = (usSRegInBuf[Address - BeginAddress ]>>8)|((usSRegInBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usSRegInBuf[Address - BeginAddress +1]>>8)|((usSRegInBuf[Address - BeginAddress +1]&0x00ff)<<8);
//         
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            LowData = usSRegHoldBuf[Address - BeginAddress ];
            HightData = usSRegHoldBuf[Address - BeginAddress + 1];
//						LowData = (usSRegHoldBuf[Address - BeginAddress ]>>8)|((usSRegHoldBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usSRegHoldBuf[Address - BeginAddress +1]>>8)|((usSRegHoldBuf[Address - BeginAddress +1]&0x00ff)<<8);
         
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    Result = ((ULONG)HightData)<<16;
    Result += LowData;
     
    *Value = Result;
     
    return ACCESS_NO_ERR;
}
//
 
/*
*   Write: STM32VN
*   Hàm này dùng d? thay d?i d? li?u 16bit c?a thanh ghi Modbus
* Ví d? mu?n gán giá tr? 325 cho thanh ghi Holding t?i d?a ch? 170 thì th?c hi?n nhu sau:
* MBSetData16Bits(REG_HOLDING, 170, 325);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode S_MBSetData16Bits(MB_Data_Type DataType, USHORT Address, USHORT Value)
{
    USHORT BeginAddress;
    USHORT LastAddress16;
     
    switch (DataType)
    {
        case    REG_INPUT:
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1 )) return ACCESS_ADDR_ERR; 
            LastAddress16 = S_REG_INPUT_START + S_REG_INPUT_NREGS -1;
         
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
 
            usSRegInBuf[Address - BeginAddress ] = Value;
         
            break;
        case REG_HOLDING:
            BeginAddress = S_REG_HOLDING_START;
            if (Address <( BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress16 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -1;
         
            if (Address > LastAddress16) return ACCESS_ADDR_ERR;
         
            usSRegHoldBuf[Address - BeginAddress ] = Value;
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
 
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
*   Write: STM32VN
*   hàm này dùng d? thay d?i d? li?u 32bit c?a thanh ghi Modbus
* Ví d?: C?n ghi giá tr? 0x554433 vào d?a ch? 100 c?a thanh ghi HOLDING
* MBSetData32Bits(REG_HOLDING, 100, 0x554433);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
eMBAccessDataCode S_MBSetData32Bits(MB_Data_Type DataType, USHORT Address, ULONG Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
     
    USHORT HightData = (Value & 0xFFFF0000)>>16;
    USHORT LowData = (Value & 0x0000FFFF);
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = S_REG_INPUT_START + S_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
        usSRegInBuf[Address - BeginAddress ] = LowData;   // Origin: HightData
        usSRegInBuf[Address - BeginAddress + 1] = HightData;  // Origin: LowData
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            usSRegHoldBuf[Address - BeginAddress ] = LowData;
            usSRegHoldBuf[Address - BeginAddress + 1] = HightData;
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
*   Write: STM32VN
*   hàm này dùng d? thay d?i d? li?u float c?a thanh ghi Modbus
* Ví d?: C?n ghi giá tr? 324.434 vào d?a ch? 100 c?a thanh ghi HOLDING
* MBSetFloatData(REG_HOLDING, 100, 324.434);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
 
typedef union S_data {
  float f;
  char  s[4];
    uint32_t U32;
} S_myData;
 
 
eMBAccessDataCode S_MBSetFloatData(MB_Data_Type DataType, USHORT Address, float Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
 
    S_myData q;
    q.f = Value;
     
    USHORT *HightData;
    USHORT *LowData;
     
    HightData = (USHORT*)q.s +1;
    LowData = (USHORT *)q.s ;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = S_REG_INPUT_START + S_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
        usSRegInBuf[Address - BeginAddress ] = *LowData;   // Origin: HightData
        usSRegInBuf[Address - BeginAddress + 1] = *HightData; // Origin: LowData
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            usSRegHoldBuf[Address - BeginAddress ] = *LowData;
            usSRegHoldBuf[Address - BeginAddress + 1] = *HightData;
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
    return ACCESS_NO_ERR;
}
//
 
 
/*
 * Write: 
 *  Hàm này dùng d? trích xu?t d? li?u float t? thanh ghi luu tr? d? li?u
 *  Ví d? c?n l?y d? li?u float  t?i d?a ch? 45 c?a thanh ghi REG HOLDING
 *  MBGetFloatData(REG_HOLDING, 45, &Value);
* Hàm tr? v? giá tr?
*   ACCESS_NO_ERR: N?u không có l?i gì
*   ACCESS_ADDR_ERR: N?u truy c?p vào 1 d?a ch? thanh ghi mà không du?c c?p phát b? nh?
*               Ví d?: #define REG_HOLDING_START       30 -> T?c là vùng nh? Holding du?c truy c?p t? d?a ch? 30 tr? lên
*                   N?u d?a ch? < 30 thì Hàm s? tr? v? l?i ACCESS_ADDR_ERR
*       ACCESS_WRONG_DATA_TYPE: Nghia là lo?i d? li?u b? sai, hàm này ch? du?c truy c?p vào 2 thanh ghi d? li?u là
*               REG_INPUT và REG_HOLDING
*/
#include <math.h>
#include <float.h>
 
eMBAccessDataCode S_MBGetFloatData(MB_Data_Type DataType, USHORT Address, float* Value)
{
    USHORT BeginAddress;
    USHORT LastAddress32;
    char *P;
 
     
    USHORT HightData = 0;
    USHORT LowData = 0;
 
    S_myData  Result;
     
    switch (DataType)
    {
        case    REG_INPUT:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_INPUT_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR; 
            LastAddress32 = S_REG_INPUT_START + S_REG_INPUT_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
 
         
            /* -------- Assign Value to Reg ----- */
            LowData = usSRegInBuf[Address - BeginAddress ];
            HightData = usSRegInBuf[Address - BeginAddress + 1];
//						LowData = (usSRegInBuf[Address - BeginAddress ]>>8)|((usSRegInBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usSRegInBuf[Address - BeginAddress +1]>>8)|((usSRegInBuf[Address - BeginAddress +1]&0x00ff)<<8);
//         
         
            break;
        case REG_HOLDING:
             
            /*  --- Check Address Correction --- */
            BeginAddress = S_REG_HOLDING_START;
            if (Address < (BeginAddress -1)) return ACCESS_ADDR_ERR;
            LastAddress32 = S_REG_HOLDING_START + S_REG_HOLDING_NREGS -2;
            if (Address > LastAddress32) return ACCESS_ADDR_ERR;
             
            /* -------- Assign Value to Reg ----- */
            LowData = usSRegHoldBuf[Address - BeginAddress ];
            HightData = usSRegHoldBuf[Address - BeginAddress + 1];
//						LowData = (usSRegHoldBuf[Address - BeginAddress ]>>8)|((usSRegHoldBuf[Address - BeginAddress ]&0x00ff)<<8);
//            HightData = (usSRegHoldBuf[Address - BeginAddress +1]>>8)|((usSRegHoldBuf[Address - BeginAddress +1]&0x00ff)<<8);
//         
         
            break;
        default:
            return ACCESS_WRONG_DATA_TYPE;
    }
 
     
    P = (char*)&LowData;
    Result.s[0] = *P;
    Result.s[1] = *(P +1);
     
    P = (char*)&HightData;
    Result.s[2] = *P;
    Result.s[3] = *(P + 1);
     
    *Value = Result.f;
    float val = Result.f;
        switch(fpclassify(*Value)) {
                case FP_INFINITE:  
                    *Value = 0; 
                    break;//return "Inf";
                case FP_NAN:       
                    *Value = 0; 
                break;//return "NaN";
                case FP_NORMAL:    
                    break;//return "normal";
                case FP_SUBNORMAL: 
                    *Value = 0; 
                    break;//return "subnormal";
                case FP_ZERO:       
                    break;//return "zero";
                default:
                    *Value = 0;
                    break;//return "unknown";
        }
     
    if (val > (float)10000.0)
        *Value = 0;
    if (val <(float)-10000.0)
        *Value = 0;
    if ((val > (float)0)&&(val < (float)0.0000001))   *Value = 0;
     
    return ACCESS_NO_ERR;
}
//



////////////////////////////////////////////////////////////////////////////////////////////////////////////

