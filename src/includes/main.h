#ifndef _MAIN_H
#define _MAIN_H

#define _GNU_SOURCE

#define PROGNAME "ShellOS"
#define MAJORVER 0
#define MINORVER 6

#define CRED  "\x1b[31m"
#define CRSET "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <error.h>
#include <fcntl.h>

#include "prompt.h"
#include "cmdtable.h"
#include "pipes.h"

#endif // _MAIN_H