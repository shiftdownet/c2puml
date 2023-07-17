/****************************************************************/
/**
 *	@file	s_core_if.h
 *	@brief	S_CORE外部公開I/F
 *	$Date:: 2017-02-14 01:17:45 +0900#$
 *	$Rev: 4 $
 *	$Author: ROKI $
*/
/****************************************************************/
#ifndef S_CORE_IF_H
#define S_CORE_IF_H

/*==============================================================*/
/*	インクルード												*/
/*==============================================================*/
/*==============================================================*/
/*	外部型定義													*/
/*==============================================================*/
/*==============================================================*/
/*	外部定数定義												*/
/*==============================================================*/
/*==============================================================*/
/*	外部関数プロトタイプ										*/
/*==============================================================*/
extern LRESULT CALLBACK g_lrWndProc(	 const HWND		a_hwnd,
										 const UINT		a_msg,
										 const WPARAM	a_wparam,
										 const LPARAM	a_lparam );
										 						/* メインウィンドウプロシージャ				*/

extern LRESULT CALLBACK g_lrWndProcEctl( const HWND		a_hwnd,
										 const UINT		a_msg,
										 const WPARAM	a_wparam,
										 const LPARAM	a_lparam );
										 						/* サブウィンドウプロシージャ				*/


extern void			l_voSetCmdLine(		const LPSTR a_szCmdLine );
extern void			l_voSetHndApp(		const HINSTANCE a_hApp );
extern LPSTR		l_lpstrGetCmdLine(	void );
extern HINSTANCE	l_hInstGetHndApp(	void );

#endif /* S_CORE_IF_H */
/* End of file *************************************************/
