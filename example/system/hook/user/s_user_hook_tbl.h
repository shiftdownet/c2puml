/****************************************************************/
/**
 *	@file	s_user_hook_tbl.h
 *	@brief	�t�b�N�e�[�u�����J��`
 *	$Date:: 2017-02-14 01:17:45 +0900#$
 *	$Rev: 4 $
 *	$Author: ROKI $
*/
/****************************************************************/
#ifndef S_USER_HOOK_TBL_H
#define S_USER_HOOK_TBL_H

/*==============================================================*/
/*	�C���N���[�h												*/
/*==============================================================*/
/*==============================================================*/
/*	�O���^��`													*/
/*==============================================================*/

typedef struct xn_msg_hook_t {									/* ���b�Z�[�WHook�^						*/
	const UINT			m_wndMsg;								/**< �E�B���h�E���b�Z�[�W				*/
	const lrCallHook	m_hook;									/**< �Ή�����Hook�֐�					*/
} xn_msg_hook;

typedef struct xn_hook_info_tbl_t {								/* Hook���e�[�u���^					*/
	const WNDPROC		m_wndproc;								/**< �Ăяo����WindowProcedure			*/
	const size_t		m_len;									/**< ���b�Z�[�W��						*/
	const xn_msg_hook *	m_tbl;									/**< ���b�Z�[�WHook						*/
	const lrCallHook	m_hook;									/**< �������s����Hook�֐�				*/
} xn_hook_info_tbl;

/*==============================================================*/
/*	�O���萔��`												*/
/*==============================================================*/
/*==============================================================*/
/*	�O���֐��v���g�^�C�v										*/
/*==============================================================*/
extern const xn_hook_info_tbl * g_hooktblGet( const WNDPROC a_wndproc );
																/* Hook���e�[�u���擾					*/

#endif /* S_USER_HOOK_TBL_H */
/* End of file *************************************************/