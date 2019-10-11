# Sistemas Operacionais - TP 1 / :shell: shellso

```console
ShellOS/SOTP1 0.8v
► $ls -l
total 32
drwxr-xr-x 3 saci saci 4096 out 11 20:29 bin
drwxr-xr-x 3 saci saci 4096 out 11 20:29 build
-rw-r--r-- 1 saci saci  175 out 11 20:05 commands
drwxr-xr-x 2 saci saci 4096 out  9 19:55 docs
-rw-r--r-- 1 saci saci 6608 out  9 19:55 Makefile
-rw-r--r-- 1 saci saci  976 out 11 14:35 README.md
lrwxrwxrwx 1 saci saci   17 out 11 20:29 shellso -> bin/debug/shellso
drwxr-xr-x 3 saci saci 4096 out 11 14:35 src
► $ls -laR => arquivo
► $wc -l <= arquivo &
PID 13454: background
► $cat -n <= arquivo => arquivonumerado
► $cat -n <= arquivo | wc -l => numerodelinhas
809
► $cat -n <= arquivo | wc -l => numerodelinhas &
PID 13459: background
► $fim
PID 13454: Headshot!
```
