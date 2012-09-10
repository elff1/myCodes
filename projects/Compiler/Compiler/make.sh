#!/bin/sh
if [ $# -lt 1 ]
then
	echo >&2 "Usage: $0 file.c"
	exit 1
fi

file="$1"
fileout="a.out"
./CMinusCompiler $file
nasm -f elf t.asm
if [ $# -eq 2  ]
then
	fileout="$2"
fi
ld -s -o $fileout t.o
rm t.asm t.o
