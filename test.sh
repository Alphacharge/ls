#!/bin/bash

if [ "$1" == "-std" -o "$1" == "" ]; then
	bats ./tests/stdout/alrt.tests
	if [ "$2" == "-R" -o "$1" == "" ]; then
		bats ./tests/stdout/R.tests
	fi
fi
if [ "$1" == "-pipe" -o "$1" == "" ]; then
	bats ./tests/pipe/alrt.tests
	if [ "$2" == "-R" -o "$1" == "" ]; then
		bats ./tests/pipe/R.tests
	fi
fi
if [ "$1" == "-redirect" -o "$1" == "" ]; then
	bats ./tests/redirect/alrt.tests
	if [ "$2" == "-R" -o "$1" == "" ]; then
		bats ./tests/redirect/R.tests
	fi
fi
