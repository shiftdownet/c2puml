/****************************************************************/
/**
 *	@file	s_hook_tbl.c
 *	@brief	フック関数テーブル
*/
/****************************************************************/
/*==============================================================*/
/*	インクルード												*/
/*==============================================================*/
/*** 標準ライブラリ ***/
#include <windows.h>

/*** 内部コンポーネント ***/
#include "s_hook.h"
#include "s_user_hook_tbl.h"
#include "s_user_hook_cmn.h"
#include "s_user_hook_main.h"

#include "s_core_if.h"

/*** 外部コンポーネント ***/
/* None */

/*==============================================================*/
/*	内部型定義													*/
/*==============================================================*/
#define L_DAT_ERR_TABLE_SEARCH		( 0xFFFF )					/* テーブル情報検索エラー値				*/

/*==============================================================*/
/*	内部定数定義												*/
/*==============================================================*/

#define L_LEN_MSG_HOOK_FAILSAFE			( 1 )					/* メッセージ数(フェールセーフ)			*/
#define L_LEN_MSG_HOOK_MAIN				( 7 )					/* メッセージ数(メインウィンドウ)		*/
#define L_LEN_MSG_HOOK_ECTL				( 1 )					/* メッセージ数(エディトコントロール)	*/

enum {															/* テーブルインデックス					*/
	L_IDX_MSG_HOOK_FAILSAFE	= 0,								/* フェールセーフ						*/
	L_IDX_MSG_HOOK_MAIN,										/* メインウィンドウ						*/
	L_IDX_MSG_HOOK_ECTL,										/* エディトコントロール					*/
	L_IDX_MSG_HOOK_MAX											/* テーブル数							*/
};

#define L_IDX_MSG_HOOK_NORMAL_START		( L_IDX_MSG_HOOK_MAIN )	/* 正常処理の開始インデックス			*/

/*==============================================================*/
/*	内部関数プロトタイプ										*/
/*==============================================================*/

/*==============================================================*/
/*	内部変数定義												*/
/*==============================================================*/
/* フック関数テーブル											*/
/* 注：使用メッセージに応じカスタマイズすること					*/

/* フェールセーフ用メッセージHook関数テーブル(編集禁止)			*/
static const xn_msg_hook l_msgHookFailsafeTbl[ L_LEN_MSG_HOOK_FAILSAFE ] =
{
	/* メッセージ,	Hook関数ポインタ	*/
	{ 0,			NULL					}
};

/* メインウィンドウ用メッセージHook関数テーブル					*/
static const xn_msg_hook l_msgHookMainTbl[ L_LEN_MSG_HOOK_MAIN ] =
{
	/* メッセージ,	Hook関数ポインタ	*/
	{ WM_CREATE,	NULL					},
	{ WM_COMMAND,	NULL					},
	{ WM_NOTIFY,	NULL					},
	{ WM_SIZE,		NULL					},
	{ WM_PAINT,		NULL					},
	{ WM_DESTROY,	&g_lrHookMainWM_DESTROY	},
	{ WM_CLOSE,		&g_lrHookMainWM_CLOSE	}
};

/* エディトコントロール用メッセージHook関数テーブル				*/
static const xn_msg_hook l_msgHookEctlTbl[ L_LEN_MSG_HOOK_ECTL ] =
{
	/* メッセージ,	Hook関数ポインタ	*/
	{ 0,			NULL					}
};

/* フック情報テーブルリストに登録								 */
static const xn_hook_info_tbl l_hookinfoTbls[ L_IDX_MSG_HOOK_MAX ] =
{
	/* フェールセーフ用関数テーブル */
	{
		NULL,
		L_LEN_MSG_HOOK_FAILSAFE,
		l_msgHookFailsafeTbl,
		&g_lrHookDefWindowProc
	},	
	/* メインウィンドウ用関数テーブル */
	{
		&g_lrWndProc,
		L_LEN_MSG_HOOK_MAIN,
		l_msgHookMainTbl,
		&g_lrHookDefWindowProc
	},
	/* エディトコントロール用関数テーブル */
	{
		&g_lrWndProcEctl,
		L_LEN_MSG_HOOK_ECTL,
		l_msgHookEctlTbl,
		&g_lrHookParentWindowProc
	}
};

/*==============================================================*/
/*	関数実態													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		g_msgHooksGet
 *	@brief		Hook情報テーブル取得
 *	@param		呼び出し元WindowProcedure
 *	@return		Hook情報テーブル
 *	@note		なし
*/
/****************************************************************/
const xn_hook_info_tbl * g_hooktblGet( const WNDPROC a_wndproc )
{
	UINT a_cnt;													/**< 検索用ループカウンタ				*/
	UINT a_idx;													/**< 対応するテーブルIndex				*/
	
	a_idx = L_DAT_ERR_TABLE_SEARCH;								/* 失敗で初期化							*/
	
	/* 呼び出し元WindowProcedureをテーブル情報から検索			*/
	/* @attention	フェールセーフ用テーブルは検索対象外		*/
	for ( a_cnt = L_IDX_MSG_HOOK_NORMAL_START; a_cnt < L_IDX_MSG_HOOK_MAX; a_cnt++ )
	{
		if ( l_hookinfoTbls[a_cnt].m_wndproc == a_wndproc )		/* 呼び出し元のWindowProcedureを発見	*/
		{
			a_idx = a_cnt;										/* テーブルIndexとして設定				*/
		}
		else
		{
			/* 処理なし */
		}
	}
	
	if( a_idx == L_DAT_ERR_TABLE_SEARCH )						/* 検索失敗								*/
	{
		// g_voAddError( G_SYS_ERR_GET_CLASS_LONG_PTR );		/* エラー通知処理 						*/
		
		a_idx = L_IDX_MSG_HOOK_FAILSAFE;						/* フェールセーフ用テーブル設定			*/
	}
	else
	{
		/* 処理なし */
	}
	
	return &l_hookinfoTbls[ a_idx ];
}

/* End of file **************************************************/
