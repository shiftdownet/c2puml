/****************************************************************/
/**
 *	@file	s_hook_exe.c
 *	@brief	フック実行
*/
/****************************************************************/
/*==============================================================*/
/*	インクルード												*/
/*==============================================================*/
/*** 標準ライブラリ ***/
#include <windows.h>

/*** 内部コンポーネント ***/
#include "s_hook.h"
#include "s_hook_if.h"
#include "s_user_hook_tbl.h"
#include "s_user_hook_cmn.h"

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
static lrCallHook l_hookGet( xn_hook_prm_ptr		  a_prmHook,
							 const xn_hook_info_tbl * a_hookInfoTbl );
							 									/* 受信メッセージに割当てられたHook取得	*/

/*==============================================================*/
/*	内部変数定義												*/
/*==============================================================*/
/*==============================================================*/
/*	関数実態													*/
/*==============================================================*/

/****************************************************************/
/**
 *	@func		g_lrExeHook
 *	@brief		フック実行処理
 *	@param		呼び出し元のWindowProcedure
 *	@param		WNDPROC型引数
 *	@return		フック実行結果
 *	@note		なし
*/
/****************************************************************/
LRESULT g_lrExeHook( const WNDPROC	a_wndproc,
					 const HWND		a_hwnd,
					 const UINT		a_msg,
					 const WPARAM	a_wparam,
					 const LPARAM	a_lparam )
{
	lrCallHook					a_fptrHook;						/**< WindowProcedure関数ポインタ		*/
	xn_hook_prm					a_prmHook;						/**< WindowProcedure関数用引数セット	*/
	LRESULT						a_lrResult;						/**< WindowProcedure実行結果			*/
	const xn_hook_info_tbl *	a_hookInfoTbl;					/**< フック情報テーブルへのポインタ		*/
	
	/* WINPROC型パラメータをフック用パラメータとしてパッキング	*/
	a_prmHook.m_hwnd	= a_hwnd;
	a_prmHook.m_msg		= a_msg;
	a_prmHook.m_wparam	= a_wparam;
	a_prmHook.m_lparam	= a_lparam;
	
	a_hookInfoTbl = g_hooktblGet( a_wndproc );					/* 該当プロシージャ用テーブルを取得		*/

	a_fptrHook = l_hookGet( &a_prmHook, a_hookInfoTbl );		/* テーブルを元に実行すべきHookを決定	*/

	a_lrResult = (*a_fptrHook)( &a_prmHook );					/* 引き当てたHook関数を実行				*/
	
	return a_lrResult;
}

/****************************************************************/
/**
 *	@func		l_hookGet
 *	@brief		フック関数取得
 *	@param		フック用パラメータ
 *	@param		呼び出し元のWindowProcedure
 *	@return		フック関数ポインタ
 *	@note		なし
*/
/****************************************************************/
static lrCallHook l_hookGet( xn_hook_prm_ptr		  a_prmHook,
							 const xn_hook_info_tbl * a_hookInfoTbl )
{
	UINT			a_cnt;										/**< 検索用ループカウンタ				*/
	lrCallHook		a_fptrHook;									/**< 検索結果(Hook関数ポインタ)			*/
	size_t			a_lenTbl;									/**< Hook関数テーブル長					*/
	
	a_fptrHook = NULL;											/* 初期値NULL							*/
	
	/* 要求に該当するメッセージのフック関数を検索する			*/
	for ( a_cnt = 0; a_cnt < a_hookInfoTbl->m_len; a_cnt++ )
	{
		if ( a_hookInfoTbl->m_tbl[ a_cnt ].m_wndMsg == a_prmHook->m_msg )
																/* 一致するメッセージを発見				*/
		{
			a_fptrHook = a_hookInfoTbl->m_tbl[ a_cnt ].m_hook;	/* テーブルに登録されたHook関数を設定	*/
		}
		else
		{
			/* 処理なし */
		}
	}
	
	/* メッセージのフック関数検索後の処理						*/
	if ( a_fptrHook == NULL )									/* 検索結果がNULL						*/
	{
		if ( a_hookInfoTbl->m_hook == NULL )					/* 検索失敗時のHook関数もNULL			*/
		{
			// g_voAddError( G_SYS_ERR_HOOK_NOTFOUND );			/* エラー通知処理 						*/
			
			a_fptrHook = &g_lrHookDefWindowProc;				/* 処理継続のためフェールセーフとして	*/
																/* 規定のウィンドウプロシージャを返す	*/
		}
		else
		{
			a_fptrHook = a_hookInfoTbl->m_hook;					/* 検索失敗時のHook関数を返す			*/
		}
	}
	else
	{
		/* 処理なし */
	}
	
	return a_fptrHook;
}

/* End of file **************************************************/
