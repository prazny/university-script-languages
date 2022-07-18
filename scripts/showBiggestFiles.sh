#!/bin/bash

if test "$#" -eq 0
 then
    echo "Nie podano argumentow!"
	exit 126
fi



while :; do
    case $1 in
        --src=?*) src=${1#*=}
        ;;
        -dst=?*) dst=${1#*=}
        ;;
        *) break
    esac
    shift
done
echo "$src"

#="$1"

#./Tail.exe --lines="$n" < ./Paths.exe -R -s
