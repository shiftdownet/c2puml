---
# Setting for Markdown Preview Enhanced v0.6.3
toc:                        # 目次設定
  depth_from: 1             # - 目次化する開始ネスト
  depth_to: 4               # - 目次化する終了ネスト
  ordered: false            # - オーダーを表示しない
html:                       # HTMLファイル出力に関する設定
  embed_local_images: true  # - ローカル埋め込み画像ファイルを有効にする
  embed_svg: true           # - SVGの埋め込みを有効にする
  offline: true             # - offlineでの生成を有効にする
  toc: true                 # - デフォルトでサイドバーにTOCを表示する
export_on_save:             # ファイル保存時の振る舞い
  html: true                # - htmlで出力(※Markdown PDF等他のAddinの自動保存機能は無効化してください)
---

```plantuml
@startuml
!include ./iuml/Sequence_Diagram_Library.iuml

'#-------------------------------------------------------
'#  setting
'#      set_function_level_lifeline()
'#          ... ライフラインを関数レベルで描画します(デフォルト:モジュールレベル)
'#      set_return_value_only()
'#          ... return時に戻り値のみを表示します(デフォルト:メッセージに'return'を明示)
'#      set_ommit_internal_function()
'#          ... ライフラインがモジュールレベルの時、内部の関数コール描画を省略します
'#      set_ommit_internal_function_alt
'#          ... ライフラインがモジュールレベルの時、内部の関数コール内のalt描画を省略します
'#      set_ommit_internal_function_loop()
'#          ... ライフラインがモジュールレベルの時、内部の関数コール内のloop描画を省略し'#  set_ommit_internal_function_alt
'#      set_ommit_internal_function_step()
'#          ... ライフラインがモジュールレベルの時、内部の関数コール内のstep描画を省略し'#  
'#  
'#  statement
'#      module_name( $name )
'#          ... procedure内で最初にコールしてください。$name:関数が所属するモジュール名
'#      call( $func )
'#          ... 関数を呼び出します $func:関数名
'#      return( $expression )
'#          ... 関数から戻ります $expression:戻り値
'#      その他色々
'#  
'#-------------------------------------------------------

!$discribeLevel = "func"
!$returnPrefix = ""
'!$omit_call_on_module_mode = "true"
'!$omit_alt_on_module_mode = "true"
'!$omit_loop_on_module_mode = "true"

!procedure $main() 
    $module_name("SystemService")
    $call("Os_Start")
!endprocedure

!procedure $Os_Start()
    $module_name("SystemService")
    $loop()
        $call("ActivateTaskWhenTimerElapsed")
    $endloop()
    $return("success")
!endprocedure

!procedure $ActivateTaskWhenTimerElapsed()
    $module_name("SystemService")
    $if("elapsed")
        $call("TaskLaunch")
        $return("elapsed")
    $else()
        $return("Not elapsed")
    $endif()
!endprocedure

!procedure $TaskLaunch()
    $module_name("SystemService")
    $call("userFunction")
!endprocedure

!procedure $userFunction()
    $module_name("UserCode")
    $step("Implements user code.")
    $call("userFunction2")
!endprocedure

!procedure $userFunction2()
    $module_name("UserCode2")
    $step("Implements user code.")
    $call("userFunction3")
    $return("abc")
!endprocedure

!procedure $userFunction3()
    $module_name("UserCode2")
    $step("Implements user code.")
    $return("abc")
!endprocedure

$call("main")


@enduml
```

