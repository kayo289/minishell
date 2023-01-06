# minishell
## 概要
42Tokyo[^1]の課題の一つ。tiny版bash[^2]。

[^1]:42Tokyo:https://42tokyo.jp/
[^2]:document:https://linuxjm.osdn.jp/html/GNU_bash/man1/bash.1.html

## 実行
```
$ git clone https://github.com/kayo289/minishell
$ cd minishell
$ make
$ ./minishell
```

## 機能
- コマンド
  - echo (-nオプション付き）
  - cd 
  - pwd
  - export
  - unset
  - env
  - exit
- '', ""によるエスケープ
- リダイレクト（<, >, >>）
- パイプ
- シェル変数
- 環境変数
- 特殊変数$?
- ヒアドキュメント(<<)
- カーソル機能（移動、編集、コピー＆ペースト、home、end）
  - 範囲選択:Ctrl+Shift+Space
  - ペースト:Ctrl+v
  - コピー:Ctrl+y
- &&, ||
- ワイルドカード
- その他
  - シグナル（Ctrl-C, Ctrl-D, Ctrl-\）
  - 入力コマンドのヒストリー機能

## デモ
https://user-images.githubusercontent.com/57135683/210828009-2e360f77-690c-455e-8083-5b90acc57b52.mp4

## 実行環境
Ubuntu 18.04.4 LTS
