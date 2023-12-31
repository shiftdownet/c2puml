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




# 1. サンプルコード

本plantumlライブラリを用いて、以下のようなC言語を模したコードを記述します。

ハンドコードしてもいいですが、[./../converter/c2puml.ps1](./../converter/c2puml.ps1) を利用することで、(精度は低いですが)自動的にCソースコードから以下のようなplantumlコードを生成することが可能です。


[./sample_code.iuml](./sample_code.iuml)
@import "./sample_code.iuml" {code_block=true class="line-numbers" as="c"}

上記のコードを、様々なコンフィグを用いてplantumlダイアグラムとして描画してみましょう。


# 2. シーケンス図

先ほどのサンプルコードを　`Sequence_Diagram_Library.iuml` と一緒に読み込ませることで、シーケンス図を出力することが可能です。

## 2.1. 標準の出力

何もコンフィグをせずに、単に描画した場合以下のようになります。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

## 2.2. 出力粒度の変更

### 2.2.1. モジュールレベルの出力

関数レベルの情報は不要で、モジュールレベルの情報のみがほしい場合、以下のように描画できます。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "module"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

### 2.2.2. コンポーネントレベルの出力

コンポーネントレベルも可能です。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

## 2.3. 省略された処理の表示

コンポーネントレベル、モジュールレベルで表示する場合、デフォルトでは関数レベルの詳細記述が省略されますが、オプションを指定することで表示可能です。

### 2.3.1. 省略されたエレメント内の関数コールを表示

以下の例では SystemServiceコンポーネント内の関数コールの情報が示されています。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!$sdlConf_display_detail_unfocused_element_for_call = %true()
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

### 2.3.2. 省略されたループや分岐、ステップを表示

関数コール以外の情報を省略せずに出力することも可能です。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!$sdlConf_display_detail_unfocused_element_for_loop = %true()
!$sdlConf_display_detail_unfocused_element_for_alt = %true()
!$sdlConf_display_detail_unfocused_element_for_step = %true()
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

## 2.4. 特定のエレメントのみ詳細表示

一部のコンポーネントだけ詳しく表示することも可能です。

### 2.4.1. 特定のコンポーネントをモジュールレベルで表示

userコンポーネントをモジュールレベルまで詳細に表示した例です。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!$sdlConf_display_lifeline_focused_element = "system.core.user"
!$sdlConf_display_lifeline_focused_element_level = "module"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

### 2.4.2. 特定のコンポーネントを関数レベルで表示

userコンポーネントを関数レベルまで詳細に表示した例です。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!$sdlConf_display_lifeline_focused_element = "system.core.user"
!$sdlConf_display_lifeline_focused_element_level = "func"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```


### 2.4.3. 特定のモジュールを関数レベルで表示

s_main.cを関数レベルまで詳細に表示した例です。
**現バージョンではs_main.cが属するコンポーネントが描画されません。**

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$iumlLib_display_level = "component"
!$sdlConf_display_lifeline_focused_element = "s_main_c"
!$sdlConf_display_lifeline_focused_element_level = "func"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```


## 2.5. 組み合わせは自由

以下の例では基本的にコンポーネントレベルで描画しますが、関数コールは省略せず、またuserモジュールだけは関数レベルで描画するように設定した例です。

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Sequence_Diagram_Library.iuml
!$sdlConf_display_detail_unfocused_element_for_call = %true()
!$iumlLib_display_level = "component"
!$sdlConf_display_lifeline_focused_element = "system.core.user"
!$sdlConf_display_lifeline_focused_element_level = "func"
!include ./sample_code.iuml
$display_outline()
$call("_tWinMain")

@enduml
```

# 3. クラス図


`Class_Diagram_Library.iuml` を読み込むことで、同じソースコードをインプットにしてクラス図を描画することが可能です。
**本機能はプロトタイプ版です。**

## 3.1. コンポーネントレベル

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Class_Diagram_Library.iuml
!include ./sample_code.iuml
!$iumlLib_display_level = "component"
$display_outline()
$call("_tWinMain")
@enduml
```

## 3.2. モジュールレベル

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Class_Diagram_Library.iuml
!include ./sample_code.iuml
!$iumlLib_display_level = "module"
$display_outline()
$call("_tWinMain")
@enduml
```


# 4. アクティビティ図

`Activity_Diagram_Library.iuml` を読み込むことで、同じソースコードをインプットにしてアクティビティ図を描画することが可能です。
**本機能はプロトタイプ版です。**

```plantuml {code_block=true class="line-numbers" }
@startuml
!include ./../iumlLibrary/Activity_Diagram_Library.iuml
!include ./sample_code.iuml
!$iumlLib_display_level = "func"
$display_outline()
$call("_tWinMain")
@enduml
```



# 5. API仕様

ごめんなさい、詳細の仕様は定義されていません。
しかし、各ライブラリファイルの `Provided interface` から概ね読み取ることが可能です。
以下は`Sequence_Diagram_Library.iuml`の内容を表示しています。

**インタフェース仕様は今後変更される可能性があります。**


[./../iumlLibrary/Sequence_Diagram_Library.iuml](./../iumlLibrary/Sequence_Diagram_Library.iuml)
@import "./../iumlLibrary/Sequence_Diagram_Library.iuml" {code_block=true class="line-numbers" as="pu"}




<header id="header"><div id="title">{meta.documentName}</div><div id="document_info"><div id="document_id">{meta.documentID}-{meta.version}</div><div id="version">{meta.version}</div></div></header>
<footer id="footer">- {meta.issued} - CONFIDENTIAL</footer>
<style> header { position:fixed !important; height: 60px; width:100%; z-index:3000; top: 0px; left:0px; background-color: rgba(255,255,255,0.8); border-bottom: 1px solid gray !important; box-sizing: border-box;} #title { padding-left:0.5em; font-size:20px; font-weight:bold; } #document_info { display:block; position:fixed; top:0.5em; right:1em; font-weight:bold; color:#666, font-size:14px; text-align:right;} #document_id::before {content:"DOCUMENT ID: "} #version { display:inline;} #version::before { content: "VERSION: "} footer { position:fixed !important; bottom:0px; left:0px; width:100%; height:20px; z-index:3500; background-color:white; border-top: 1px solid slategray; text-align:center; font-size:15px; color:#333; font-weight:bold; } .md-sidebar-toc{ top:60px !important; height: calc(100% - 60px - 20px) !important; overflow:scroll !important; white-space:nowrap; font-size:12px !important; } .markdown-preview { margin:0 !important; padding: 1em 1em 1em 1em !important; position:fixed !important; top:60px !important; height:calc(100% - 60px) !important; overflow:scroll !important;} html body[for="html-export"]:not([data-presentation-mode]):not([html-show-sidebar-toc]) .markdown-preview{left:0% !important; transform: initial !important;} .md-sidebar-toc::-webkit-scrollbar { height:8px !important; } #sidebar-toc-btn { bottom:0px !important; top:60px;} h1, h2, h3, h4, h5, h6 { border-bottom: solid 2px #333 !important; font-weight:bold; margin:2em 0em 0em 0em !important; } h1 + h2 { page-break-before:auto; margin-top : 0.5em !important; } h2 + h3 { page-break-before: auto; margin-top: 0.5em !important; } h3 + h4 { page-break-before: auto; margin-top: 0.5em !important; }  h3 + h4 { page-break-before: auto; margin-top: 0.5em !important; }  h4 + h5 { page-break-before: auto; margin-top: 0.5em !important; }  h5 + h6 { page-break-before: auto; margin-top: 0.5em !important; } h1,h2,h3{ font-size:24px !important;} h4,h5,h6 { font-size:22px !important; } .column-left{ float: left; width: calc(50% - 10px); text-align: left;} .column-right{ float: right; width: calc(50% - 10px);text-align: left;}  .three-column{ float: left; width: calc(33% - 15px); text-align: left; margin-left: 10px;} .clearfix::after{ content: ""; clear: both; display: block; } pre, code, var, samp, kbd, .mono { font-family: 'ＭＳ ゴシック', Consolas, 'Courier New', Courier, Monaco, monospace !important; line-height: 1.2 !important;}
</style>
