@startuml
'#==============================================================================================
'# C:\workspace\c2puml\example\system\core\lib\s_main.c
'#==============================================================================================
$start_component("lib")
$start_module("s_main.c")

'#===============================================
'# int WINAPI _tWinMain (HINSTANCEa_hApp,HINSTANCEa_hAppPrev,LPSTRa_szCmdLine,inta_modCmdShow)
'#===============================================
$start_func("_tWinMain")
!procedure $_tWinMain()
$call("l_voSetCmdLine")
$call("l_voSetHndApp")
$if("( TRUE == l_boolInitSystem( a_hApp, a_modCmdShow ) ) && ( TRUE == g_boolHookInitApp() ) ")
$call("l_modMsgLoop")
$call("g_voHookTermApp")
$endif()
$return("a_modResult")
!endprocedure

'#===============================================
'# static int l_modMsgLoop (void)
'#===============================================
$start_func("l_modMsgLoop")
!procedure $l_modMsgLoop()
$while("a_bMsg == TRUE ")
$switch("(int)GetMessage( &a_msg, NULL, 0, 0 ) ")
$case("L_MOD_GM_FAILURE: a_bMsg = FALSE; break; case L_MOD_GM_WM_QUIT: a_bMsg = FALSE; a_modResult = (int)a_msg.wParam; break; default")
$call("TranslateMessage")
$call("DispatchMessage")
$endswitch()
$endwhile()
$return("a_modResult")
!endprocedure

'#===============================================
'# static BOOL l_boolInitSystem (constHINSTANCEa_hApp,constinta_modCmdShow)
'#===============================================
$start_func("l_boolInitSystem")
!procedure $l_boolInitSystem()
$if("g_atomRegisterWcex( a_hApp ) != 0 ")
$call("g_hwndCreateWindow")
$if("a_hWnd != NULL ")
$call("ShowWindow")
$call("UpdateWindow")
$endif()
$else()
$endif()
$return("a_bInitSystem")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\core\user\s_init.c
'#==============================================================================================
$start_component("user")
$start_module("s_init.c")

'#===============================================
'# ATOM g_atomRegisterWcex (constHINSTANCEa_hApp)
'#===============================================
$start_func("g_atomRegisterWcex")
!procedure $g_atomRegisterWcex()
$call("sizeof")
$call("LoadImage")
$call("LoadCursor")
$call("LoadImage")
$call("RegisterClassEx")
$return("a_atomResult")
!endprocedure

'#===============================================
'# HWND g_hwndCreateWindow (constHINSTANCEa_hApp)
'#===============================================
$start_func("g_hwndCreateWindow")
!procedure $g_hwndCreateWindow()
$call("CreateWindowEx")
$return("a_hWnd")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\core\user\s_proc.c
'#==============================================================================================
$start_component("user")
$start_module("s_proc.c")

'#===============================================
'# LRESULT CALLBACK g_lrWndProc (constHWNDa_hwnd,constUINTa_msg,constWPARAMa_wparam,constLPARAMa_lparam)
'#===============================================
$start_func("g_lrWndProc")
!procedure $g_lrWndProc()
$return("g_lrExeHook( &g_lrWndProc, a_hwnd, a_msg, a_wparam, a_lparam )")
!endprocedure

'#===============================================
'# LRESULT CALLBACK g_lrWndProcEctl (constHWNDa_hwnd,constUINTa_msg,constWPARAMa_wparam,constLPARAMa_lparam)
'#===============================================
$start_func("g_lrWndProcEctl")
!procedure $g_lrWndProcEctl()
$return("g_lrExeHook( &g_lrWndProcEctl, a_hwnd, a_msg, a_wparam, a_lparam )")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\core\user\s_sys_info.c
'#==============================================================================================
$start_component("user")
$start_module("s_sys_info.c")

'#===============================================
'# void l_voSetCmdLine (constLPSTRa_szCmdLine)
'#===============================================
$start_func("l_voSetCmdLine")
!procedure $l_voSetCmdLine()
!endprocedure

'#===============================================
'# void l_voSetHndApp (constHINSTANCEa_hApp)
'#===============================================
$start_func("l_voSetHndApp")
!procedure $l_voSetHndApp()
!endprocedure

'#===============================================
'# LPSTR l_lpstrGetCmdLine (void)
'#===============================================
$start_func("l_lpstrGetCmdLine")
!procedure $l_lpstrGetCmdLine()
$return("l_szCmdLine")
!endprocedure

'#===============================================
'# HINSTANCE l_hInstGetHndApp (void)
'#===============================================
$start_func("l_hInstGetHndApp")
!procedure $l_hInstGetHndApp()
$return("l_hApp")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\hook\lib\s_hook_exe.c
'#==============================================================================================
$start_component("lib")
$start_module("s_hook_exe.c")

'#===============================================
'# LRESULT g_lrExeHook (constWNDPROCa_wndproc,constHWNDa_hwnd,constUINTa_msg,constWPARAMa_wparam,constLPARAMa_lparam)
'#===============================================
$start_func("g_lrExeHook")
!procedure $g_lrExeHook()
$call("g_hooktblGet")
$call("l_hookGet")
$return("a_lrResult")
!endprocedure

'#===============================================
'# static lrCallHook l_hookGet (xn_hook_prm_ptra_prmHook,constxn_hook_info_tbl*a_hookInfoTbl)
'#===============================================
$start_func("l_hookGet")
!procedure $l_hookGet()
$for("a_cnt = 0; a_cnt < a_hookInfoTbl->m_len; a_cnt++ ")
$if("a_hookInfoTbl->m_tbl[ a_cnt ].m_wndMsg == a_prmHook->m_msg ")
$endif()
$endfor()
$if("a_fptrHook == NULL ")
$if("a_hookInfoTbl->m_hook == NULL ")
$endif()
$else()
$endif()
$return("a_fptrHook")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\hook\user\s_user_hook_cmn.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_cmn.c")

'#===============================================
'# BOOL g_boolHookInitApp (void)
'#===============================================
$start_func("g_boolHookInitApp")
!procedure $g_boolHookInitApp()
$return("TRUE")
!endprocedure

'#===============================================
'# void g_voHookTermApp (void)
'#===============================================
$start_func("g_voHookTermApp")
!procedure $g_voHookTermApp()
!endprocedure

'#===============================================
'# LRESULT g_lrHookDefWindowProc (xn_hook_prm_ptra_prmHook)
'#===============================================
$start_func("g_lrHookDefWindowProc")
!procedure $g_lrHookDefWindowProc()
$return("DefWindowProc( a_prmHook->m_hwnd, a_prmHook->m_msg, a_prmHook->m_wparam, a_prmHook->m_lparam )")
!endprocedure

'#===============================================
'# LRESULT g_lrHookParentWindowProc (xn_hook_prm_ptra_prmHook)
'#===============================================
$start_func("g_lrHookParentWindowProc")
!procedure $g_lrHookParentWindowProc()
$call("GetClassLongPtr")
$if("a_wproc == 0 ")
$call("g_lrHookDefWindowProc")
$call("CallWindowProc")
$endif()
$return("a_lrResult")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\hook\user\s_user_hook_main.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_main.c")

'#===============================================
'# LRESULT g_lrHookMainWM_DESTROY (xn_hook_prm_ptra_prmHook)
'#===============================================
$start_func("g_lrHookMainWM_DESTROY")
!procedure $g_lrHookMainWM_DESTROY()
$call("PostQuitMessage")
$return("g_lrHookDefWindowProc( a_prmHook )")
!endprocedure

'#===============================================
'# LRESULT g_lrHookMainWM_CLOSE (xn_hook_prm_ptra_prmHook)
'#===============================================
$start_func("g_lrHookMainWM_CLOSE")
!procedure $g_lrHookMainWM_CLOSE()
$return("g_lrHookDefWindowProc( a_prmHook )")
!endprocedure


'#==============================================================================================
'# C:\workspace\c2puml\example\system\hook\user\s_user_hook_tbl.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_tbl.c")

'#===============================================
'# const xn_hook_info_tbl * g_hooktblGet (constWNDPROCa_wndproc)
'#===============================================
$start_func("g_hooktblGet")
!procedure $g_hooktblGet()
$for("a_cnt = L_IDX_MSG_HOOK_NORMAL_START; a_cnt < L_IDX_MSG_HOOK_MAX; a_cnt++ ")
$if("l_hookinfoTbls[a_cnt].m_wndproc == a_wndproc ")
$endif()
$endfor()
$if("a_idx == L_DAT_ERR_TABLE_SEARCH ")
$endif()
$return("&l_hookinfoTbls[ a_idx ]")
!endprocedure


$box()
$call("EntryPoint")
@enduml

