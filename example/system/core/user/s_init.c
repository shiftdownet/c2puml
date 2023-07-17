/****************************************************************/
/**
 *	@file	s_init.c
 *	@brief	�V�X�e��������
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
#include "s_core_if.h"
#include "s_hook_if.h"

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
/*==============================================================*/
/*	�����ϐ���`												*/
/*==============================================================*/
static LPCTSTR l_szAppName = TEXT("TkadEditor");				/**< �A�v���P�[�V������					*/

/*==============================================================*/
/*	�֐�����													*/
/*==============================================================*/
/****************************************************************/
/**
 *	@func		g_atomRegisterWcex
 *	@brief		�E�B���h�E�N���X�̓o�^
 *	@param		�C���X�^���X�n���h��
 *	@return		�o�^���ꂽ�N���X����ӓI�Ɏ��ʂ���A�g��
 *	@note		RegisterClassEx�̖߂�l���Ԃ�܂�
*/
/****************************************************************/
ATOM g_atomRegisterWcex( const HINSTANCE a_hApp )
{
	WNDCLASSEX	a_wcex;											/**< �E�B���h�E�N���XEX�\����			*/
	ATOM		a_atomResult;									/**< �E�B���h�E�N���XEX�o�^����			*/
	
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
 *	@brief		�E�B���h�E�쐬
 *	@param		�C���X�^���X�n���h��
 *	@param		�\�����
 *	@return		����:TRUE/���s:FALSE
 *	@note		�Ȃ�
*/
/****************************************************************/
HWND g_hwndCreateWindow( const HINSTANCE	a_hApp )
{
	HWND a_hWnd;												/**< �E�B���h�E�n���h��					*/

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
