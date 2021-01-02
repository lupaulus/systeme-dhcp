#!/usr/bin/env bash


function binAndMake()
{
  mkdir -p bin
  make
}

echo tp1
cd tp01/copy
binAndMake
cd -
cd tp01/ls
binAndMake
cd -
cd tp01/lseek
binAndMake
echo tp02
cd -
cd tp02/fork
binAndMake
cd -
cd tp02/pipe
binAndMake
cd -
cd tp02/pipe1
binAndMake
echo tp03
cd -
cd tp03/signal
binAndMake
cd -
cd tp03/thread
binAndMake
