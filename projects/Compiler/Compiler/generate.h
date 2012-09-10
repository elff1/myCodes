#ifndef __GENERATE_H
#define __GENERATE_H

#define SCALAR 1
#define ARRAY 2
#define GENERAL 1
#define PARAMETER 2
#define VAR_LENGTH 4
#define FUNC_OUTPUT_NAME "output"
#define FUNC_INPUT_NAME "input"

#include "globals.h"
#include "y.tab.h"
#include "symtab.h"
#include "encode.h"

int generate(TreeNode *node, int signal);

#endif