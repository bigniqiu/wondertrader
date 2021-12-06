/*!
 * \file WtDtPorter.h
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 * 
 * \brief 
 */
#pragma once

#include "../Includes/WTSTypes.h"

NS_OTP_BEGIN
struct WTSBarStruct;
struct WTSTickStruct;
struct WTSOrdDtlStruct;
struct WTSOrdQueStruct;
struct WTSTransStruct;
NS_OTP_END

USING_NS_OTP;

typedef void(PORTER_FLAG *FuncLogCallback)(WtString message);
typedef void(PORTER_FLAG *FuncGetBarsCallback)(WTSBarStruct* bar, WtUInt32 count, bool isLast);
typedef void(PORTER_FLAG *FuncGetTicksCallback)(WTSTickStruct* tick, WtUInt32 count, bool isLast);
typedef void(PORTER_FLAG *FuncCountDataCallback)(WtUInt32 dataCnt);

//改成直接从python传内存块的方式
//typedef bool(PORTER_FLAG *FuncGetBarItem)(WTSBarStruct* curBar,int idx);
//typedef bool(PORTER_FLAG *FuncGetTickItem)(WTSTickStruct* curTick, int idx);

#ifdef __cplusplus
extern "C"
{
#endif
	EXPORT_FLAG	void		dump_bars(WtString binFolder, WtString csvFolder, WtString strFilter = "", FuncLogCallback cbLogger = NULL);
	EXPORT_FLAG	void		dump_ticks(WtString binFolder, WtString csvFolder, WtString strFilter = "", FuncLogCallback cbLogger = NULL);
	EXPORT_FLAG	void		trans_csv_bars(WtString csvFolder, WtString binFolder, WtString period, FuncLogCallback cbLogger = NULL);

	EXPORT_FLAG	WtUInt32	read_dsb_ticks(WtString tickFile, FuncGetTicksCallback cb, FuncCountDataCallback cbCnt, FuncLogCallback cbLogger = NULL);
	EXPORT_FLAG	WtUInt32	read_dsb_bars(WtString barFile, FuncGetBarsCallback cb, FuncCountDataCallback cbCnt, FuncLogCallback cbLogger = NULL);

	EXPORT_FLAG	WtUInt32	read_dmb_ticks(WtString tickFile, FuncGetTicksCallback cb, FuncCountDataCallback cbCnt, FuncLogCallback cbLogger = NULL);
	EXPORT_FLAG	WtUInt32	read_dmb_bars(WtString barFile, FuncGetBarsCallback cb, FuncCountDataCallback cbCnt, FuncLogCallback cbLogger = NULL);

	//EXPORT_FLAG bool		trans_bars(WtString barFile, FuncGetBarItem getter, int count, WtString period, FuncLogCallback cbLogger = NULL);
	//EXPORT_FLAG bool		trans_ticks(WtString tickFile, FuncGetTickItem getter, int count, FuncLogCallback cbLogger = NULL);

	EXPORT_FLAG bool		store_bars(WtString barFile, WTSBarStruct* firstBar, int count, WtString period, FuncLogCallback cbLogger = NULL);
	EXPORT_FLAG bool		store_ticks(WtString tickFile, WTSTickStruct* firstTick, int count, FuncLogCallback cbLogger = NULL);

	EXPORT_FLAG WtUInt32	resample_bars(WtString barFile, FuncGetBarsCallback cb, FuncCountDataCallback cbCnt, WtUInt64 fromTime, WtUInt64 endTime, WtString period, WtUInt32 times, WtString sessInfo, FuncLogCallback cbLogger = NULL);
#ifdef __cplusplus
}
#endif