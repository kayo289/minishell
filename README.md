# minishell
## 概要
42Tokyoの課題の一つ。tiny版bash。

## 実行
```
$ git clone https://github.com/kayo289/minishell
$ cd minishell
$ make
$ ./minishell
```
<img width="145" alt="image" src="https://user-images.githubusercontent.com/57135683/210717224-8bd656d9-acd9-4035-b5d8-9ac10be0dd67.png">

## 機能
- コマンド
  - echo (-nオプション付き）
    - <img width="151" alt="image" src="https://user-images.githubusercontent.com/57135683/210717608-92df6560-e8b7-4cb0-869f-02a80415fdff.png">
  - cd 
  - pwd
    - <img width="95" alt="image" src="https://user-images.githubusercontent.com/57135683/210717799-407758fb-d457-462d-a822-90895622fdd7.png">
  - export
    - <img width="89" alt="image" src="https://user-images.githubusercontent.com/57135683/210717930-ca8269d3-5057-4b6c-aecc-1738616ae498.png">
  - unset
    - <img width="82" alt="image" src="https://user-images.githubusercontent.com/57135683/210718278-ab8e9646-23ce-4066-be64-1f003468c69c.png">
  - env
    - <img width="260" alt="image" src="https://user-images.githubusercontent.com/57135683/210718085-5050b94b-ecb9-4642-8885-9a296452b591.png">
  - exit
    - <img width="143" alt="image" src="https://user-images.githubusercontent.com/57135683/210718119-1f603591-e608-4f16-899d-882b0002716f.png">

- '', ""によるエスケープ
  - <img width="101" alt="image" src="https://user-images.githubusercontent.com/57135683/210718646-c2c6671c-3091-4490-abcc-372782e80685.png">

- リダイレクト（<, >, >>）
  - <img width="134" alt="image" src="https://user-images.githubusercontent.com/57135683/210718760-1d87a4a5-28cd-4add-a2c1-0a8b744ee675.png">

- パイプ
  - <img width="158" alt="image" src="https://user-images.githubusercontent.com/57135683/210719161-4fa400ae-7ea4-40c2-a253-e18a153dae00.png">

- 環境変数$
  - <img width="95" alt="image" src="https://user-images.githubusercontent.com/57135683/210719339-62d67461-7a00-47b0-b240-a4b1421ba585.png">

- 特殊変数$?
  - <img width="133" alt="image" src="https://user-images.githubusercontent.com/57135683/210719443-9accaf6e-33d1-4079-bd2b-6aebd5afa0ff.png">

- ヒアドキュメント(<<)
  - <img width="140" alt="image" src="https://user-images.githubusercontent.com/57135683/210719821-81188546-e22c-48f2-a05f-b4c88cb1c4e3.png">

- カーソル機能（移動、編集、コピー＆ペースト、home、end）
  - <img width="171" alt="image" src="https://user-images.githubusercontent.com/57135683/210719948-35d6a735-90ea-4c72-b937-60975e4c8c0c.png">

- &&, ||
  - <img width="172" alt="image" src="https://user-images.githubusercontent.com/57135683/210720133-f178dbb5-de97-409f-a77a-56075f92632f.png">

- ワイルドカード
  - <img width="448" alt="image" src="https://user-images.githubusercontent.com/57135683/210720252-dbba9c81-8813-4669-8130-caa40d8b6cdd.png">
  
- シグナル（Ctrl-C, Ctrl-D, Ctrl-\）
- 入力コマンドのヒストリー機能

## 実行環境
Ubuntu 18.04.4 LTS
