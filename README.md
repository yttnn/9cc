# 9cc
https://www.sigbus.info/compilerbook

## めも
- `make test`で実行
- step6
  - `- -10 = 10`になることを初めてしった。。。あまりにもはずい
- step7,8
  - この時点での文法は
  ```
  expr       = equality
  equality   = relational ("==" relational | "!=" relational)*
  relational = add ("<" add | "<=" add | ">" add | ">=" add)*
  add        = mul ("+" mul | "-" mul)*
  mul        = unary ("*" unary | "/" unary)*
  unary      = ("+" | "-")? primary
  primary    = num | "(" expr ")"
  ```
  - ファイル分割も行う
  - step8以降は`9cc.c`の利用をしないため`old`へ退避
- step9
  ```
  program    = stmt*
  stmt       = expr ";"
  expr       = assign
  assign     = equality ("=" assign)?
  equality   = relational ("==" relational | "!=" relational)*
  relational = add ("<" add | "<=" add | ">" add | ">=" add)*
  add        = mul ("+" mul | "-" mul)*
  mul        = unary ("*" unary | "/" unary)*
  unary      = ("+" | "-")? primary
  primary    = num | ident | "(" expr ")"
  ```
  - ;=のトークン生成を忘れてた
  - 本の方では、２項演算子のコード生成がなくなっているように見えるがなぜ？（今回は記述は変えずにやった）
- step10
  - 本の、パーサーの追記部分のコードが違ってそう。一応動きはしたが、、、(offsetがよくわかってない)