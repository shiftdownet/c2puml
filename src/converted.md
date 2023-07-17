@startuml
'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\core\lib\s_main.c
'#==============================================================================================
$start_component("lib")
$start_module("s_main.c")

'#----------------------------------------------------
'# func : int WINAPI _tWinMain ( HINSTANCE a_hApp, HINSTANCE a_hAppPrev, LPSTR a_szCmdLine, int a_modCmdShow )
'#----------------------------------------------------
$start_func("_tWinMain")
!procedure $_tWinMain()
    $call("l_voSetCmdLine")
    $call("l_voSetHndApp")
    $if("( TRUE == l_boolInitSystem( a_hApp, a_modCmdShow ) ) && ( TRUE == g_boolHookInitApp() ) ")
        $call("l_modMsgLoop")
        $call("g_voHookTermApp")
    $elseif(" ABC ")
        $call("g_voHookTermApp")
    $elseif(" DEF ")
    $else()
    $endif()
    $return("a_modResult")
!endprocedure

'#----------------------------------------------------
'# func : static int l_modMsgLoop ( void )
'#----------------------------------------------------
$start_func("l_modMsgLoop")
!procedure $l_modMsgLoop()
    $while("a_bMsg == TRUE ")
        $switch("(int)GetMessage( &a_msg, NULL, 0, 0 ) ")
        $case("L_MOD_GM_FAILURE")
        $case("L_MOD_GM_WM_QUIT")
        $default()
            $call("TranslateMessage")
            $call("DispatchMessage")
        $endswitch()
    $endwhile()
    $return("a_modResult")
!endprocedure

'#----------------------------------------------------
'# func : static BOOL l_boolInitSystem ( const HINSTANCE a_hApp, const int a_modCmdShow )
'#----------------------------------------------------
$start_func("l_boolInitSystem")
!procedure $l_boolInitSystem()
    $if("g_atomRegisterWcex( a_hApp ) != 0 ")
        $call("g_hwndCreateWindow")
        $if("a_hWnd != NULL ")
            $call("ShowWindow")
            $call("UpdateWindow")
        $else()
        $endif()
    $else()
    $endif()
    $return("a_bInitSystem")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\core\user\s_init.c
'#==============================================================================================
$start_component("user")
$start_module("s_init.c")

'#----------------------------------------------------
'# func : ATOM g_atomRegisterWcex ( const HINSTANCE a_hApp )
'#----------------------------------------------------
$start_func("g_atomRegisterWcex")
!procedure $g_atomRegisterWcex()
    $call("sizeof")
    $call("LoadImage")
    $call("LoadCursor")
    $call("LoadImage")
    $call("RegisterClassEx")
    $return("a_atomResult")
!endprocedure

'#----------------------------------------------------
'# func : HWND g_hwndCreateWindow ( const HINSTANCE a_hApp )
'#----------------------------------------------------
$start_func("g_hwndCreateWindow")
!procedure $g_hwndCreateWindow()
    $call("CreateWindowEx")
    $return("a_hWnd")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\core\user\s_proc.c
'#==============================================================================================
$start_component("user")
$start_module("s_proc.c")

'#----------------------------------------------------
'# func : LRESULT CALLBACK g_lrWndProc ( const HWND a_hwnd, const UINT a_msg, const WPARAM a_wparam, const LPARAM a_lparam )
'#----------------------------------------------------
$start_func("g_lrWndProc")
!procedure $g_lrWndProc()
    $return("g_lrExeHook( &g_lrWndProc, a_hwnd, a_msg, a_wparam, a_lparam )")
!endprocedure

'#----------------------------------------------------
'# func : LRESULT CALLBACK g_lrWndProcEctl ( const HWND a_hwnd, const UINT a_msg, const WPARAM a_wparam, const LPARAM a_lparam )
'#----------------------------------------------------
$start_func("g_lrWndProcEctl")
!procedure $g_lrWndProcEctl()
    $return("g_lrExeHook( &g_lrWndProcEctl, a_hwnd, a_msg, a_wparam, a_lparam )")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\core\user\s_sys_info.c
'#==============================================================================================
$start_component("user")
$start_module("s_sys_info.c")

'#----------------------------------------------------
'# func : void l_voSetCmdLine ( const LPSTR a_szCmdLine )
'#----------------------------------------------------
$start_func("l_voSetCmdLine")
!procedure $l_voSetCmdLine()
!endprocedure

'#----------------------------------------------------
'# func : void l_voSetHndApp ( const HINSTANCE a_hApp )
'#----------------------------------------------------
$start_func("l_voSetHndApp")
!procedure $l_voSetHndApp()
!endprocedure

'#----------------------------------------------------
'# func : LPSTR l_lpstrGetCmdLine ( void )
'#----------------------------------------------------
$start_func("l_lpstrGetCmdLine")
!procedure $l_lpstrGetCmdLine()
    $return("l_szCmdLine")
!endprocedure

'#----------------------------------------------------
'# func : HINSTANCE l_hInstGetHndApp ( void )
'#----------------------------------------------------
$start_func("l_hInstGetHndApp")
!procedure $l_hInstGetHndApp()
    $return("l_hApp")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\hook\lib\s_hook_exe.c
'#==============================================================================================
$start_component("lib")
$start_module("s_hook_exe.c")

'#----------------------------------------------------
'# func : LRESULT g_lrExeHook ( const WNDPROC a_wndproc, const HWND a_hwnd, const UINT a_msg, const WPARAM a_wparam, const LPARAM a_lparam )
'#----------------------------------------------------
$start_func("g_lrExeHook")
!procedure $g_lrExeHook()
    $call("g_hooktblGet")
    $call("l_hookGet")
    $return("a_lrResult")
!endprocedure

'#----------------------------------------------------
'# func : static lrCallHook l_hookGet ( xn_hook_prm_ptr a_prmHook, const xn_hook_info_tbl * a_hookInfoTbl )
'#----------------------------------------------------
$start_func("l_hookGet")
!procedure $l_hookGet()
    $for("a_cnt = 0; a_cnt < a_hookInfoTbl->m_len; a_cnt++ ")
        $if("a_hookInfoTbl->m_tbl[ a_cnt ].m_wndMsg == a_prmHook->m_msg ")
        $else()
        $endif()
    $endfor()
    $if("a_fptrHook == NULL ")
        $if("a_hookInfoTbl->m_hook == NULL ")
        $else()
        $endif()
    $else()
    $endif()
    $return("a_fptrHook")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\hook\user\s_user_hook_cmn.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_cmn.c")

'#----------------------------------------------------
'# func : BOOL g_boolHookInitApp ( void )
'#----------------------------------------------------
$start_func("g_boolHookInitApp")
!procedure $g_boolHookInitApp()
    $return("TRUE")
!endprocedure

'#----------------------------------------------------
'# func : void g_voHookTermApp ( void )
'#----------------------------------------------------
$start_func("g_voHookTermApp")
!procedure $g_voHookTermApp()
!endprocedure

'#----------------------------------------------------
'# func : LRESULT g_lrHookDefWindowProc ( xn_hook_prm_ptr a_prmHook )
'#----------------------------------------------------
$start_func("g_lrHookDefWindowProc")
!procedure $g_lrHookDefWindowProc()
    $return("DefWindowProc( a_prmHook->m_hwnd, a_prmHook->m_msg, a_prmHook->m_wparam, a_prmHook->m_lparam )")
!endprocedure

'#----------------------------------------------------
'# func : LRESULT g_lrHookParentWindowProc ( xn_hook_prm_ptr a_prmHook )
'#----------------------------------------------------
$start_func("g_lrHookParentWindowProc")
!procedure $g_lrHookParentWindowProc()
    $call("GetClassLongPtr")
    $if("a_wproc == 0 ")
        $call("g_lrHookDefWindowProc")
    $else()
        $call("CallWindowProc")
    $endif()
    $return("a_lrResult")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\hook\user\s_user_hook_main.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_main.c")

'#----------------------------------------------------
'# func : LRESULT g_lrHookMainWM_DESTROY ( xn_hook_prm_ptr a_prmHook )
'#----------------------------------------------------
$start_func("g_lrHookMainWM_DESTROY")
!procedure $g_lrHookMainWM_DESTROY()
    $call("PostQuitMessage")
    $return("g_lrHookDefWindowProc( a_prmHook )")
!endprocedure

'#----------------------------------------------------
'# func : LRESULT g_lrHookMainWM_CLOSE ( xn_hook_prm_ptr a_prmHook )
'#----------------------------------------------------
$start_func("g_lrHookMainWM_CLOSE")
!procedure $g_lrHookMainWM_CLOSE()
    $return("g_lrHookDefWindowProc( a_prmHook )")
!endprocedure


'#==============================================================================================
'# file : C:\workspace\c2puml\example\system\hook\user\s_user_hook_tbl.c
'#==============================================================================================
$start_component("user")
$start_module("s_user_hook_tbl.c")

'#----------------------------------------------------
'# func : const xn_hook_info_tbl * g_hooktblGet ( const WNDPROC a_wndproc )
'#----------------------------------------------------
$start_func("g_hooktblGet")
!procedure $g_hooktblGet()
    $for("a_cnt = L_IDX_MSG_HOOK_NORMAL_START; a_cnt < L_IDX_MSG_HOOK_MAX; a_cnt++ ")
        $if("l_hookinfoTbls[a_cnt].m_wndproc == a_wndproc ")
        $else()
        $endif()
    $endfor()
    $if("a_idx == L_DAT_ERR_TABLE_SEARCH ")
    $else()
    $endif()
    $return("&l_hookinfoTbls[ a_idx ]")
!endprocedure


$box()
$call("EntryPoint")
@enduml

