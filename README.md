# Sistemas Operacionais :shell: shellso
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6a0df7209849450b89c159d31af6315b)](https://www.codacy.com/manual/Durfan/ufsj-shellso?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Durfan/ufsj-shellso&amp;utm_campaign=Badge_Grade)

Trabalho prático de implementação de um Interpretador de comandos para a disciplina de Sistemas Operacionais/UFSJ.

## Instalação e funcionamento

``` bash
make
make debug # binario com debug
make clean # remover binario
./shellso # symlink para o binario, inicia o shell
./shellso [commands file] # processamento de comandos a partir de um arquivo
```

### Comando de finalização

``` bash
ShellOS/SOTP1 0.8v
┌/currentpath/
└[user@host]$ fim # ou CTRL+D
```

## Arquivo de Comandos

``` bash
./shellso [commands file]
```
### Formato de arquivo

Um comando por linha, exemplo:

``` text
ls -l
ls -laR => arquivo
wc -l <= arquivo &
cat -n <= arquivo => arquivonumerado
cat -n <= arquivo | wc -l => numerodelinhas
cat -n <= arquivo | wc -l => numerodelinhas &
fim
```

### Exemplo de saída

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

## Acknowledgments

* [GenericMakefile](https://github.com/mbcrawfo/GenericMakefile)
