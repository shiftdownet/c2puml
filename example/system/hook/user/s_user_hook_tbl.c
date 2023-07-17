/****************************************************************/
/**
 *	@file	s_hook_tbl.c
 *	@brief	�t�b�N�֐��e�[�u��
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
#include "s_user_hook_tbl.h"
#include "s_user_hook_cmn.h"
#include "s_user_hook_main.h"

#include "s_core_if.h"

/*** �O���R���|�[�l���g ***/
/* None */

/*==============================================================*/
/*	�����^��`													*/
/*==============================================================*/
#define L_DAT_ERR_TABLE_SEARCH		( 0xFFFF )					/* �e�[�u����񌟍��G���[�l				*/

/*==============================================================*/
/*	�����萔��`												*/
/*==============================================================*/

#define L_LEN_MSG_HOOK_FAILSAFE			( 1 )					/* ���b�Z�[�W��(�t�F�[���Z�[�t)			*/
#define L_LEN_MSG_HOOK_MAIN				( 7 )					/* ���b�Z�[�W��(���C���E�B���h�E)		*/
#define L_LEN_MSG_HOOK_ECTL				( 1 )					/* ���b�Z�[�W��(�G�f�B�g�R���g���[��)	*/

enum {															/* �e�[�u���C���f�b�N�X					*/
	L_IDX_MSG_HOOK_FAILSAFE	= 0,								/* �t�F�[���Z�[�t						*/
	L_IDX_MSG_HOOK_MAIN,										/* ���C���E�B���h�E						*/
	L_IDX_MSG_HOOK_ECTL,										/* �G�f�B�g�R���g���[��					*/
	L_IDX_MSG_HOOK_MAX											/* �e�[�u����							*/
};

#define L_IDX_MSG_HOOK_NORMAL_START		( L_IDX_MSG_HOOK_MAIN )	/* ���폈���̊J�n�C���f�b�N�X			*/

/*==============================================================*/
/*	�����֐��v���g�^�C�v										*/
/*==============================================================*/

/*==============================================================*/
/*	�����ϐ���`												*/
/*==============================================================*/
/* �t�b�N�֐��e�[�u��											*/
/* ���F�g�p���b�Z�[�W�ɉ����J�X�^�}�C�Y���邱��					*/

/* �t�F�[���Z�[�t�p���b�Z�[�WHook�֐��e�[�u��(�ҏW�֎~)			*/
static const xn_msg_hook l_msgHookFailsafeTbl[ L_LEN_MSG_HOOK_FAILSAFE ] =
{
	/* ���b�Z�[�W,	Hook�֐��|�C���^	*/
	{ 0,			NULL					}
};

/* ���C���E�B���h�E�p���b�Z�[�WHook�֐��e�[�u��					*/
static const xn_msg_hook l_msgHookMainTbl[ L_LEN_MSG_HOOK_MAIN ] =
{
	/* ���b�Z�[�W,	Hook�֐��|�C���^	*/
	{ WM_CREATE,	NULL					},
	{ WM_COMMAND,	NULL					},
	{ WM_NOTIFY,	NULL					},
	{ WM_SIZE,		NULL					},
	{ WM_PAINT,		NULL					},
	{ WM_DESTROY,	&g_lrHookMainWM_DESTROY	},
	{ WM_CLOSE,		&g_lrHookMainWM_CLOSE	}
};

/* �G�f�B�g�R���g���[���p���b�Z�[�WHook�֐��e�[�u��				*/
static const xn_msg_hook l_msgHookEctlTbl[ L_LEN_MSG_HOOK_ECTL ] =
{
	/* ���b�Z�[�W,	Hook�֐��|�C���^	*/
	{ 0,			NULL					}
};

/* �t�b�N���e�[�u�����X�g�ɓo�^								 */
static const xn_hook_info_tbl l_hookinfoTbls[ L_IDX_MSG_HOOK_MAX ] =
{
	/* �t�F�[���Z�[�t�p�֐��e�[�u�� */
	{
		NULL,
		L_LEN_MSG_HOOK_FAILSAFE,
		l_msgHookFailsafeTbl,
		&g_lrHookDefWindowProc
	},	
	/* ���C���E�B���h�E�p�֐��e�[�u�� */
	{
		&g_lrWndProc,
		L_LEN_MSG_HOOK_MAIN,
		l_msgHookMainTbl,
		&g_lrHookDefWindowProc
	},
	/* �G�f�B�g�R���g���[���p�֐��e�[�u�� */
	{
		&g_lrWndProcEctl,
		L_LEN_MSG_HOOK_ECTL,
		l_msgHookEctlTbl,
		&g_lrHookParentWindowProc
	}
};

/*==============================================================*/
/*	�֐�����													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		g_msgHooksGet
 *	@brief		Hook���e�[�u���擾
 *	@param		�Ăяo����WindowProcedure
 *	@return		Hook���e�[�u��
 *	@note		�Ȃ�
*/
/****************************************************************/
const xn_hook_info_tbl * g_hooktblGet( const WNDPROC a_wndproc )
{
	UINT a_cnt;													/**< �����p���[�v�J�E���^				*/
	UINT a_idx;													/**< �Ή�����e�[�u��Index				*/
	
	a_idx = L_DAT_ERR_TABLE_SEARCH;								/* ���s�ŏ�����							*/
	
	/* �Ăяo����WindowProcedure���e�[�u����񂩂猟��			*/
	/* @attention	�t�F�[���Z�[�t�p�e�[�u���͌����ΏۊO		*/
	for ( a_cnt = L_IDX_MSG_HOOK_NORMAL_START; a_cnt < L_IDX_MSG_HOOK_MAX; a_cnt++ )
	{
		if ( l_hookinfoTbls[a_cnt].m_wndproc == a_wndproc )		/* �Ăяo������WindowProcedure�𔭌�	*/
		{
			a_idx = a_cnt;										/* �e�[�u��Index�Ƃ��Đݒ�				*/
		}
		else
		{
			/* �����Ȃ� */
		}
	}
	
	if( a_idx == L_DAT_ERR_TABLE_SEARCH )						/* �������s								*/
	{
		// g_voAddError( G_SYS_ERR_GET_CLASS_LONG_PTR );		/* �G���[�ʒm���� 						*/
		
		a_idx = L_IDX_MSG_HOOK_FAILSAFE;						/* �t�F�[���Z�[�t�p�e�[�u���ݒ�			*/
	}
	else
	{
		/* �����Ȃ� */
	}
	
	return &l_hookinfoTbls[ a_idx ];
}

/* End of file **************************************************/
