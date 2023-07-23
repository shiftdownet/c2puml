/****************************************************************/
/**
 *	$FileName$
 *	@brief	サンプル
*/
/****************************************************************/
/*==============================================================*/
/*	要求インタフェース											*/
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
/*	マクロ定義													*/
/*==============================================================*/
/* GetMessage関数戻り値											*/
#define L_MOD_GM_FAILURE			( (int)-1 )					/**< GetMessage関数失敗					*/
#define L_MOD_GM_WM_QUIT			( (int)0  )					/**< WM_QUITによる正常終了				*/
																/* 上記以外(WM_QUIT以外の成功)は未定義	*/
																/* 注：システム返却値に適合しているため */
																/*     値の変更不可						*/
/*==============================================================*/
/*	内部関数プロトタイプ										*/
/*==============================================================*/
static int	l_modMsgLoop( void );								/* メッセージループ処理					*/
static BOOL	l_boolInitSystem( const HINSTANCE a_hApp,
							  const int       a_modCmdShow );	/* システム初期化						*/

/*==============================================================*/
/*	内部変数定義												*/
/*==============================================================*/
static HINSTANCE	l_hApp;										/**< アプリケーションハンドル			*/

/*==============================================================*/
/*	関数実体													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		_tWinMain
 *	@brief		Windowsメイン関数
 *	@param		現在のインスタンスハンドル
 *	@param		以前のインスタンスハンドル
 *	@param		コマンドライン
 *	@param		表示状態
 *	@return		終了コード
 *	@note		EntryPoint
*/
/****************************************************************/
int WINAPI _tWinMain(	HINSTANCE a_hApp,
					HINSTANCE a_hAppPrev,
					LPSTR     a_szCmdLine,
					int       a_modCmdShow )
{
	int	a_modResult;											/**< WinMain関数終了コード				*/

	a_modResult	= 0;											/* 終了コードを失敗で初期化				*/

	l_voSetCmdLine( a_szCmdLine );
	l_voSetHndApp( a_hApp );

	if ( ( TRUE == l_boolInitSystem( a_hApp, a_modCmdShow ) ) &&
		 ( TRUE == g_boolHookInitApp()						) )
		 														/* システムとアプリケーション初期化成功	*/
	{
		a_modResult = l_modMsgLoop();							/* Windowsメッセージループ				*/

		g_voHookTermApp();										/* アプリケーション終了処理Hook			*/
	}
	else														/* システム初期化に失敗					*/
	{
		/* 処理なし */
	}
	
	return a_modResult;											/* アプリケーション終了コードを返す		*/
}

/****************************************************************/
/**
 *	@func		l_modMsgLoop
 *	@brief		Windowsメッセージループ
 *	@param		なし
 *	@return		WinMain終了コード
 *	@note		なし
*/
/****************************************************************/
static int l_modMsgLoop( void )
{
	int		a_modResult;										/**< WinMain関数終了コード				*/
	MSG		a_msg;												/**< 受信メッセージ						*/
	BOOL	a_bMsg;												/**< メッセージループ継続条件			*/

	a_modResult	= 0;											/* 失敗で初期化							*/
	a_bMsg		= TRUE;											/* 継続で初期化							*/
	
	while ( a_bMsg == TRUE ) 									/* 受信メッセージが失敗or終了までループ	*/
	{
		switch ( (int)GetMessage( &a_msg, NULL, 0, 0 ) )
		{
		case L_MOD_GM_FAILURE:									/* GetMessageが失敗						*/
			a_bMsg = FALSE;
			/* @Attention																				*/
			/* REF:msdn.microsoft.com WinMainより														*/
			/* >> 関数がWM_QUITメッセージを受け取って正常に終了する場合は、メッセージの					*/
			/* >> wParamパラメータに格納されている終了コードを返してください。							*/
			/* >> 関数がメッセージループに入る前に終了する場合は、0 を返してください。					*/
			/* GetMessageが失敗した場合はメッセージループに入らなかったと解釈							*/
			break;
			
		case L_MOD_GM_WM_QUIT:									/* GetMessageがWM_QUITを受信			*/
			a_bMsg		= FALSE;
			a_modResult	= (int)a_msg.wParam;					/* メッセージのwParamを設定				*/
			break;
			
		default:												/* GetMessageがWM_QUIT以外を受信		*/
			a_bMsg	= TRUE;
			( void )TranslateMessage( &a_msg );
			( void )DispatchMessage( &a_msg );
			break;
			
		}
	}
	
	return 	a_modResult;
}

/****************************************************************/
/**
 *	@func		l_boolInitSystem
 *	@brief		システム初期化
 *	@param		インスタンスハンドル
 *	@param		表示状態
 *	@return		成功:TRUE/失敗:FALSE
 *	@note		なし
*/
/****************************************************************/
static BOOL l_boolInitSystem(	const HINSTANCE	a_hApp,
								const int		a_modCmdShow )
{
	BOOL	a_bInitSystem;										/**< システム初期化テスト変数			*/
	HWND	a_hWnd;												/**< ウィンドウハンドル					*/

	a_bInitSystem	= FALSE;									/* 失敗で初期化							*/

	if ( g_atomRegisterWcex( a_hApp ) != 0 )					/* ウィンドウクラス登録に成功			*/
	{
		a_hWnd = g_hwndCreateWindow( a_hApp  );					/* ウィンドウ作成						*/
		
		if ( a_hWnd != NULL )									/* ウィンドウハンドル≠NULLならば成功	*/
		{
			a_bInitSystem = TRUE;								/* 成功を設定							*/
			( void )ShowWindow( a_hWnd, a_modCmdShow );			/* ウィンドウを表示に設定				*/
			( void )UpdateWindow( a_hWnd );						/* ウィンドウを描画						*/
		}
		else
		{
			/* 処理なし */
		}
	}
	else														/* ウィンドウクラスの登録に失敗			*/
	{
		/* 処理なし */
	}
	
	return a_bInitSystem;
}

/* End of file **************************************************/
