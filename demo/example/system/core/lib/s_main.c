/****************************************************************/
/**
 *	$FileName$
 *	@brief	�T���v��
 *	$Date:: 2017-02-14 01:17:45 +0900#$
 *	$Rev: 4 $
 *	$Author: ROKI $
*/
/****************************************************************/
/*==============================================================*/
/*	�v���C���^�t�F�[�X											*/
/*==============================================================*/
/*** �W�����C�u���� ***/
#include <windows.h>

/*** �����R���|�[�l���g ***/
#include "s_core_if.h"
#include "s_hook_if.h"

/*** �O���R���|�[�l���g ***/
/* None */

/*==============================================================*/
/*	�����^��`													*/
/*==============================================================*/

/*==============================================================*/
/*	�}�N����`													*/
/*==============================================================*/
/* GetMessage�֐��߂�l											*/
#define L_MOD_GM_FAILURE			( (int)-1 )					/**< GetMessage�֐����s					*/
#define L_MOD_GM_WM_QUIT			( (int)0  )					/**< WM_QUIT�ɂ�鐳��I��				*/
																/* ��L�ȊO(WM_QUIT�ȊO�̐���)�͖���`	*/
																/* ���F�V�X�e���ԋp�l�ɓK�����Ă��邽�� */
																/*     �l�̕ύX�s��						*/
/*==============================================================*/
/*	�����֐��v���g�^�C�v										*/
/*==============================================================*/
static int	l_modMsgLoop( void );								/* ���b�Z�[�W���[�v����					*/
static BOOL	l_boolInitSystem( const HINSTANCE a_hApp,
							  const int       a_modCmdShow );	/* �V�X�e��������						*/

/*==============================================================*/
/*	�����ϐ���`												*/
/*==============================================================*/
static HINSTANCE	l_hApp;										/**< �A�v���P�[�V�����n���h��			*/

/*==============================================================*/
/*	�֐�����													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		_tWinMain
 *	@brief		Windows���C���֐�
 *	@param		���݂̃C���X�^���X�n���h��
 *	@param		�ȑO�̃C���X�^���X�n���h��
 *	@param		�R�}���h���C��
 *	@param		�\�����
 *	@return		�I���R�[�h
 *	@note		EntryPoint
*/
/****************************************************************/
int WINAPI _tWinMain(	HINSTANCE a_hApp,
					HINSTANCE a_hAppPrev,
					LPSTR     a_szCmdLine,
					int       a_modCmdShow )
{
	int	a_modResult;											/**< WinMain�֐��I���R�[�h				*/

	a_modResult	= 0;											/* �I���R�[�h�����s�ŏ�����				*/

	l_voSetCmdLine( a_szCmdLine );
	l_voSetHndApp( a_hApp );

	if ( ( TRUE == l_boolInitSystem( a_hApp, a_modCmdShow ) ) &&
		 ( TRUE == g_boolHookInitApp()						) )
		 														/* �V�X�e���ƃA�v���P�[�V��������������	*/
	{
		a_modResult = l_modMsgLoop();							/* Windows���b�Z�[�W���[�v				*/

		g_voHookTermApp();										/* �A�v���P�[�V�����I������Hook			*/
	}
	else if ( ABC )
	{
		g_voHookTermApp();										/* �A�v���P�[�V�����I������Hook			*/

	}
	else if ( DEF )
	{
	}
	else														/* �V�X�e���������Ɏ��s					*/
	{
		/* �����Ȃ� */
	}
	
	return a_modResult;											/* �A�v���P�[�V�����I���R�[�h��Ԃ�		*/
}

/****************************************************************/
/**
 *	@func		l_modMsgLoop
 *	@brief		Windows���b�Z�[�W���[�v
 *	@param		�Ȃ�
 *	@return		WinMain�I���R�[�h
 *	@note		�Ȃ�
*/
/****************************************************************/
static int l_modMsgLoop( void )
{
	int		a_modResult;										/**< WinMain�֐��I���R�[�h				*/
	MSG		a_msg;												/**< ��M���b�Z�[�W						*/
	BOOL	a_bMsg;												/**< ���b�Z�[�W���[�v�p������			*/

	a_modResult	= 0;											/* ���s�ŏ�����							*/
	a_bMsg		= TRUE;											/* �p���ŏ�����							*/
	
	while ( a_bMsg == TRUE ) 									/* ��M���b�Z�[�W�����sor�I���܂Ń��[�v	*/
	{
		switch ( (int)GetMessage( &a_msg, NULL, 0, 0 ) )
		{
		case L_MOD_GM_FAILURE:									/* GetMessage�����s						*/
			a_bMsg = FALSE;
			/* @Attention																				*/
			/* REF:msdn.microsoft.com WinMain���														*/
			/* >> �֐���WM_QUIT���b�Z�[�W���󂯎���Đ���ɏI������ꍇ�́A���b�Z�[�W��					*/
			/* >> wParam�p�����[�^�Ɋi�[����Ă���I���R�[�h��Ԃ��Ă��������B							*/
			/* >> �֐������b�Z�[�W���[�v�ɓ���O�ɏI������ꍇ�́A0 ��Ԃ��Ă��������B					*/
			/* GetMessage�����s�����ꍇ�̓��b�Z�[�W���[�v�ɓ���Ȃ������Ɖ���							*/
			break;
			
		case L_MOD_GM_WM_QUIT:									/* GetMessage��WM_QUIT����M			*/
			a_bMsg		= FALSE;
			a_modResult	= (int)a_msg.wParam;					/* ���b�Z�[�W��wParam��ݒ�				*/
			break;
			
		default:												/* GetMessage��WM_QUIT�ȊO����M		*/
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
 *	@brief		�V�X�e��������
 *	@param		�C���X�^���X�n���h��
 *	@param		�\�����
 *	@return		����:TRUE/���s:FALSE
 *	@note		�Ȃ�
*/
/****************************************************************/
static BOOL l_boolInitSystem(	const HINSTANCE	a_hApp,
								const int		a_modCmdShow )
{
	BOOL	a_bInitSystem;										/**< �V�X�e���������e�X�g�ϐ�			*/
	HWND	a_hWnd;												/**< �E�B���h�E�n���h��					*/

	a_bInitSystem	= FALSE;									/* ���s�ŏ�����							*/

	if ( g_atomRegisterWcex( a_hApp ) != 0 )					/* �E�B���h�E�N���X�o�^�ɐ���			*/
	{
		a_hWnd = g_hwndCreateWindow( a_hApp  );					/* �E�B���h�E�쐬						*/
		
		if ( a_hWnd != NULL )									/* �E�B���h�E�n���h����NULL�Ȃ�ΐ���	*/
		{
			a_bInitSystem = TRUE;								/* ������ݒ�							*/
			( void )ShowWindow( a_hWnd, a_modCmdShow );			/* �E�B���h�E��\���ɐݒ�				*/
			( void )UpdateWindow( a_hWnd );						/* �E�B���h�E��`��						*/
		}
		else
		{
			/* �����Ȃ� */
		}
	}
	else														/* �E�B���h�E�N���X�̓o�^�Ɏ��s			*/
	{
		/* �����Ȃ� */
	}
	
	return a_bInitSystem;
}

/* End of file **************************************************/
