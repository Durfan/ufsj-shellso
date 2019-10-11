#ifndef _MAIN_H
#define _MAIN_H

#define _GNU_SOURCE

#define PROGNAME "ShellOS"
#define MAJORVER 0
#define MINORVER 6

#define MAXCMD 512
#define freebuf(buff) \
	memset(buff,'\0',MAXCMD * sizeof(char));

#define CRED  "\x1b[31m"
#define CGRN "\x1b[32m"
#define CRST "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>
#include <error.h>

#include "readfile.h"
#include "prompt.h"
#include "cmdtable.h"
#include "shell.h"

#endif // _MAIN_H