/****************************************************************/
/**
 *	@file	s_user_hook_cmn.c
 *	@brief	???????
 *	$Date:2017-02-11 04:04:19 +0900#$
 *	$Rev:3 $
 *	$Author:ROKI $
*/
/****************************************************************/
/*==============================================================*/
/*	??????												*/
/*==============================================================*/
/*** ??????? ***/
#include <windows.h>

/*** ????????? ***/
#include "s_hook.h"
#include "s_hook_if.h"
#include "s_user_hook_cmn.h"

/*** ????????? ***/
/* None */

/*==============================================================*/
/*	?????													*/
/*==============================================================*/
/*==============================================================*/
/*	??????												*/
/*==============================================================*/
/*==============================================================*/
/*	??????????										*/
/*==============================================================*/
/*==============================================================*/
/*	??????												*/
/*==============================================================*/
/*==============================================================*/
/*	????													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		g_boolInitApp_Hook
 *	@brief		??????????????
 *	@param		
 *	@return		
 *	@note		
*/
/****************************************************************/
BOOL g_boolHookInitApp( void )
{
	return TRUE;
}

/****************************************************************/
/**
 *	@func		g_voTermApp_Hook
 *	@brief		?????????????
 *	@param		
 *	@return		
 *	@note		
*/
/****************************************************************/
void g_voHookTermApp( void )
{

}

/****************************************************************/
/**
 *	@func		g_lrHookDefWindowProc
 *	@brief		??????????????????
 *	@param		
 *	@return		
 *	@note		
*/
/****************************************************************/
LRESULT g_lrHookDefWindowProc( xn_hook_prm_ptr a_prmHook )
{
	return DefWindowProc( a_prmHook->m_hwnd,
						  a_prmHook->m_msg,
						  a_prmHook->m_wparam,
						  a_prmHook->m_lparam );
}

/****************************************************************/
/**
 *	@func		g_lrHookParentWindowProc
 *	@brief		??????????????????
 *	@param		
 *	@return		
 *	@note		
*/
/****************************************************************/
LRESULT g_lrHookParentWindowProc( xn_hook_prm_ptr a_prmHook )
{
	WNDPROC a_wproc;
	LRESULT a_lrResult;
	
	a_wproc = (WNDPROC)GetClassLongPtr( a_prmHook->m_hwnd, GCLP_WNDPROC );
																
	
	if ( a_wproc == 0 )
	{
		// g_voAddError( G_SYS_ERR_GET_CLASS_LONG_PTR );		
		
		a_lrResult = g_lrHookDefWindowProc( a_prmHook );		

	}
	else
	{
		a_lrResult = CallWindowProc( a_wproc,
									 a_prmHook->m_hwnd,
									 a_prmHook->m_msg,
									 a_prmHook->m_wparam,
									 a_prmHook->m_lparam );
	}

	return a_lrResult;
}

/* End of file **************************************************/
