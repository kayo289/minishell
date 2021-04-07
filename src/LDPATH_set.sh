#!/bin/bash

trap "export LD_LIBRARY_PATH=${PWD}/builtin" SIGUSR1
