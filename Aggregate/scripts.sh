#!/bin/bash

while (($#)); do
    case $1 in
        --country=?*) country=${1#*=}
        ;;
        --year=?*) year=${1#*=}
        ;;
        --continent=?*) continent=${1#*=}
        ;;

    esac
	shift
done

if test -z "$year"
 then
	echo "Nie podano roku"
	exit 128
fi
if test -z "$continent"
 then
	echo "Nie podano kontynentu"
	exit 128
fi
if test -z "$country"
 then
	echo "Nie podano kraju"
	exit 128
fi

./Process.exe --delimiter="\t" --separator=";" --project="2,3,10,4"


#="$1"

#./Tail.exe --lines="$n" < ./Paths.exe -R -s
