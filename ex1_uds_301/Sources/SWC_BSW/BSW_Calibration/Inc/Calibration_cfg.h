#ifndef CALIBRATION_CFG_H
#define CALIBRATION_CFG_H


#include "Std_Types.h"
#include "Calibration.h"

enum{
CALIB_CCHVOLT = 1,
CALIB_CCLVOLT,
CALIB_CPVOLT,
CALIB_PFCOUTVOLT,
CALIB_HVVOLT,
CALIB_HVCURR,
CALIB_LVVOLT,
CALIB_LVCURR,
CALIB_LLCOUTVOLT,
CALIB_LLCOUTCUR,
CALIB_HIBATVOLT,
CALIB_LVVCC27V,
CALIB_AC220VOLT,
CALIB_ALLINPUT,
CALIB_OUTPUTVOLTAGEOFFSET=25,
CALIB_OUTPUTVOLTRATE,
CALIB_OUTPUTCUROFFSET,
CALIB_OUTPUTCURRATE,
CALIB_OUTPUTRESISTANCE,
CALIB_ALLOUTPUT,
CALIB_WRITEFLASH=35,
CALIB_READFLASH ,

};


typedef struct 
{
 uint8  u8Index;
 uint32 u32Section;
 uint32 u32Gain;
 sint32 u32Offset;
 uint32 au32Gain[2];
 sint32 au32Offset[2];
}CALIB_tstrCalibrationInput_t;

extern CALIB_tstrCalibrationInput_t CALIB_audtCalibrationInput[];

typedef struct 
{
 //uint8  u8Index;
 uint16 u16VoutOffset;
 uint16 u16VadjRate;
 uint16 u16IoutOffset;
 uint16 u16IadjRate;
 uint16 u16OutResistance;
 
}CALIB_tstrCalibrationOutput_t;

extern CALIB_tstrCalibrationOutput_t CALIB_tstrCalibrationOutput;
extern void CALIB_vidGetCalibInputData(uint8 idx, uint8* data);
extern void CALIB_vidSetCalibInputData(uint8 idx, uint8* data);
extern void CALIB_vidGetCalibOutputData(uint8 idx, uint8* data);
extern void CALIB_vidSetCalibOutputData(uint8 idx, uint8* data);
extern void CALIB_vidCalibration(uint8 *u8Rx ,uint8 *u8Tx );
extern uint16 CALIB_u16CalibrateCalc(uint8 u8Index,uint16 u16Phy);


#endif
