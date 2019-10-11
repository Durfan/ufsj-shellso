# Sistemas Operacionais - TP 1 / :shell: shellso

```console
ShellOS/SOTP1 0.6v
► $ls -l
total 132
-rw-r--r-- 1 cecilio cecilio 43318 out 11 11:28 arquivo
-rw-r--r-- 1 cecilio cecilio 50794 out 11 11:28 arquivonumerado
drwxr-xr-x 3 cecilio cecilio  4096 out 11 11:02 bin
drwxr-xr-x 3 cecilio cecilio  4096 out 11 11:02 build
-rw-r--r-- 1 cecilio cecilio   175 out 11 10:27 commands
drwxr-xr-x 2 cecilio cecilio  4096 out  8 23:50 docs
-rw-r--r-- 1 cecilio cecilio  6608 out  9 09:53 Makefile
-rw-r--r-- 1 cecilio cecilio     5 out 11 11:28 numerodelinhas
-rw-r--r-- 1 cecilio cecilio   146 out  8 23:50 README.md
lrwxrwxrwx 1 cecilio cecilio    19 out 11 11:27 shellso -> bin/release/shellso
drwxr-xr-x 3 cecilio cecilio  4096 out 11 10:15 src
► $ls -laR => arquivo
► $wc -l <= arquivo &
PID: 18424
► $cat -n <= arquivo => arquivonumerado
► $cat -n <= arquivo | wc -l => numerodelinhas
1070
► $cat -n <= arquivo | wc -l => numerodelinhas &
PID: 18429
► $fim
```
