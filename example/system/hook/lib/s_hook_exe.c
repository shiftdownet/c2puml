/****************************************************************/
/**
 *	@file	s_hook_exe.c
 *	@brief	�t�b�N���s
 *	$Date:: 2017-02-14 01:17:45 +0900#$
 *	$Rev: 4 $
 *	$Author: ROKI $
*/
/****************************************************************/
/*==============================================================*/
/*	�C���N���[�h												*/
/*==============================================================*/
/*** �W�����C�u���� ***/
#include <windows.h>

/*** �����R���|�[�l���g ***/
#include "s_hook.h"
#include "s_hook_if.h"
#include "s_user_hook_tbl.h"
#include "s_user_hook_cmn.h"

/*** �O���R���|�[�l���g ***/
/* None */

/*==============================================================*/
/*	�����^��`													*/
/*==============================================================*/
/*==============================================================*/
/*	�����萔��`												*/
/*==============================================================*/
/*==============================================================*/
/*	�����֐��v���g�^�C�v										*/
/*==============================================================*/
static lrCallHook l_hookGet( xn_hook_prm_ptr		  a_prmHook,
							 const xn_hook_info_tbl * a_hookInfoTbl );
							 									/* ��M���b�Z�[�W�Ɋ����Ă�ꂽHook�擾	*/

/*==============================================================*/
/*	�����ϐ���`												*/
/*==============================================================*/
/*==============================================================*/
/*	�֐�����													*/
/*==============================================================*/

/****************************************************************/
/**
 *	@func		g_lrExeHook
 *	@brief		�t�b�N���s����
 *	@param		�Ăяo������WindowProcedure
 *	@param		WNDPROC�^����
 *	@return		�t�b�N���s����
 *	@note		�Ȃ�
*/
/****************************************************************/
LRESULT g_lrExeHook( const WNDPROC	a_wndproc,
					 const HWND		a_hwnd,
					 const UINT		a_msg,
					 const WPARAM	a_wparam,
					 const LPARAM	a_lparam )
{
	lrCallHook					a_fptrHook;						/**< WindowProcedure�֐��|�C���^		*/
	xn_hook_prm					a_prmHook;						/**< WindowProcedure�֐��p�����Z�b�g	*/
	LRESULT						a_lrResult;						/**< WindowProcedure���s����			*/
	const xn_hook_info_tbl *	a_hookInfoTbl;					/**< �t�b�N���e�[�u���ւ̃|�C���^		*/
	
	/* WINPROC�^�p�����[�^���t�b�N�p�p�����[�^�Ƃ��ăp�b�L���O	*/
	a_prmHook.m_hwnd	= a_hwnd;
	a_prmHook.m_msg		= a_msg;
	a_prmHook.m_wparam	= a_wparam;
	a_prmHook.m_lparam	= a_lparam;
	
	a_hookInfoTbl = g_hooktblGet( a_wndproc );					/* �Y���v���V�[�W���p�e�[�u�����擾		*/

	a_fptrHook = l_hookGet( &a_prmHook, a_hookInfoTbl );		/* �e�[�u�������Ɏ��s���ׂ�Hook������	*/

	a_lrResult = (*a_fptrHook)( &a_prmHook );					/* �������Ă�Hook�֐������s				*/
	
	return a_lrResult;
}

/****************************************************************/
/**
 *	@func		l_hookGet
 *	@brief		�t�b�N�֐��擾
 *	@param		�t�b�N�p�p�����[�^
 *	@param		�Ăяo������WindowProcedure
 *	@return		�t�b�N�֐��|�C���^
 *	@note		�Ȃ�
*/
/****************************************************************/
static lrCallHook l_hookGet( xn_hook_prm_ptr		  a_prmHook,
							 const xn_hook_info_tbl * a_hookInfoTbl )
{
	UINT			a_cnt;										/**< �����p���[�v�J�E���^				*/
	lrCallHook		a_fptrHook;									/**< ��������(Hook�֐��|�C���^)			*/
	size_t			a_lenTbl;									/**< Hook�֐��e�[�u����					*/
	
	a_fptrHook = NULL;											/* �����lNULL							*/
	
	/* �v���ɊY�����郁�b�Z�[�W�̃t�b�N�֐�����������			*/
	for ( a_cnt = 0; a_cnt < a_hookInfoTbl->m_len; a_cnt++ )
	{
		if ( a_hookInfoTbl->m_tbl[ a_cnt ].m_wndMsg == a_prmHook->m_msg )
																/* ��v���郁�b�Z�[�W�𔭌�				*/
		{
			a_fptrHook = a_hookInfoTbl->m_tbl[ a_cnt ].m_hook;	/* �e�[�u���ɓo�^���ꂽHook�֐���ݒ�	*/
		}
		else
		{
			/* �����Ȃ� */
		}
	}
	
	/* ���b�Z�[�W�̃t�b�N�֐�������̏���						*/
	if ( a_fptrHook == NULL )									/* �������ʂ�NULL						*/
	{
		if ( a_hookInfoTbl->m_hook == NULL )					/* �������s����Hook�֐���NULL			*/
		{
			// g_voAddError( G_SYS_ERR_HOOK_NOTFOUND );			/* �G���[�ʒm���� 						*/
			
			a_fptrHook = &g_lrHookDefWindowProc;				/* �����p���̂��߃t�F�[���Z�[�t�Ƃ���	*/
																/* �K��̃E�B���h�E�v���V�[�W����Ԃ�	*/
		}
		else
		{
			a_fptrHook = a_hookInfoTbl->m_hook;					/* �������s����Hook�֐���Ԃ�			*/
		}
	}
	else
	{
		/* �����Ȃ� */
	}
	
	return a_fptrHook;
}

/* End of file **************************************************/
