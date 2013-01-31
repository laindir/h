#!/bin/sh

SECTIONS=3,2,9,1,8

man -e '' -S $SECTIONS "$1" | awk -v arg1="$1" '
BEGIN {
	arg1 = "[ *]" arg1 " ?\\(|[ *]" arg1 "$";
}

/^SYNOPSIS|^SYNTAX|^Synopsis/ {
	syn = 1;
}

$0 ~ arg1 && syn == 1 {
	f = 1;
}

/^[A-Z]+/ && !/^SYNOPSIS|^SYNTAX|^Synopsis/ && syn == 1 {
	exit;
}

f == 1 {
	synopsis = synopsis $0;
}

/;/ && f == 1 {
	exit;
}

END {
	gsub(/ +/, " ", synopsis);
	print synopsis;
}
' | grep "$1"
