# minishell
## 概要
42Tokyoの課題の一つ。tiny版bash。

## 機能
- コマンド
  - echo (-nオプション付き）
  - cd 
  - pwd
  - export
  - unset
  - env
  - exit
- ;によるコマンド分割
- '', ""によるエスケープ
- リダイレクト（<, >, >>）
- パイプ
- 環境変数$
- 特殊変数$?
- シグナル（Ctrl-C, Ctrl-D, Ctrl-\）
- 入力コマンドのヒストリー機能
- ヒアドキュメント(<<)
- カーソル機能（移動、編集、コピー＆ペースト、home、end）
- &&, ||
- ワイルドカード

## 実行
```
$ git clone https://github.com/kayo289/minishell
$ cd minishell
$ make
$ ./minishell
```
