/****************************************************************/
/**
 *	@file	s_init.c
 *	@brief	システム初期化
 *	$Date:: 2017-02-14 01:17:45 +0900#$
 *	$Rev: 4 $
 *	$Author: ROKI $
*/
/****************************************************************/
/*==============================================================*/
/*	インクルード												*/
/*==============================================================*/
/*** 標準ライブラリ ***/
#include <windows.h>

/*** 内部コンポーネント ***/
#include "s_core_if.h"
#include "s_hook_if.h"

/*** 外部コンポーネント ***/
/* None */

/*==============================================================*/
/*	内部型定義													*/
/*==============================================================*/
/*==============================================================*/
/*	内部定数定義												*/
/*==============================================================*/
/*==============================================================*/
/*	内部関数プロトタイプ										*/
/*==============================================================*/
/*==============================================================*/
/*	内部変数定義												*/
/*==============================================================*/
static LPCTSTR l_szAppName = TEXT("TkadEditor");				/**< アプリケーション名					*/

/*==============================================================*/
/*	関数実体													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		g_atomRegisterWcex
 *	@brief		ウィンドウクラスの登録
 *	@param		インスタンスハンドル
 *	@return		登録されたクラスを一意的に識別するアトム
 *	@note		RegisterClassExの戻り値が返ります
*/
/****************************************************************/
ATOM g_atomRegisterWcex( const HINSTANCE a_hApp )
{
	WNDCLASSEX	a_wcex;											/**< ウィンドウクラスEX構造体			*/
	ATOM		a_atomResult;									/**< ウィンドウクラスEX登録結果			*/
	
	a_wcex.cbSize 			= sizeof(WNDCLASSEX); 
	a_wcex.style			= CS_HREDRAW | CS_VREDRAW;
	a_wcex.lpfnWndProc		= (WNDPROC)&g_lrWndProc;
	a_wcex.cbClsExtra		= 0;
	a_wcex.cbWndExtra		= 0;
	a_wcex.hInstance		= a_hApp;
	a_wcex.hIcon			= (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);//NULL;
	a_wcex.hCursor			= LoadCursor(NULL, IDC_ARROW);
	a_wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	a_wcex.lpszMenuName		= NULL;
	a_wcex.lpszClassName	= l_szAppName;
	a_wcex.hIconSm			= (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED);//NULL;
	
	a_atomResult = RegisterClassEx( &a_wcex );

	return a_atomResult;
}

/****************************************************************/
/**
 *	@func		g_hwndCreateWindow
 *	@brief		ウィンドウ作成
 *	@param		インスタンスハンドル
 *	@param		表示状態
 *	@return		成功:TRUE/失敗:FALSE
 *	@note		なし
*/
/****************************************************************/
HWND g_hwndCreateWindow( const HINSTANCE	a_hApp )
{
	HWND a_hWnd;												/**< ウィンドウハンドル					*/

	a_hWnd = CreateWindowEx( WS_EX_ACCEPTFILES,
							 l_szAppName,
							 l_szAppName,
							 WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 300,
							 200,
							 NULL,
							 NULL,
							 a_hApp,
							 NULL );

	return a_hWnd;
}

/* End of file **************************************************/
