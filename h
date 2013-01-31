#!/bin/sh

# Copyright 2013 Carl D Hamann
# 
# This file is part of h.
# 
# h is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# h is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with h.  If not, see <http://www.gnu.org/licenses/>.

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
