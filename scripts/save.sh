#!/bin/bash

while (($#)); do
    case $1 in
		  --dst=?*) dst=${1#*=}
			;;
      --src=?*) src=${1#*=}
      ;;

    esac
	shift
done

if test -z "$dst"
 then
	echo "Nie podano katalogu docelowego"
	exit 128
fi



if test -z "$src"
 then
	src=$(pwd)
fi

if ! test -d "$src"
 then
	echo "Katalog zrodlowy nie istnieje"
	exit 128
fi


cp -r "$src" "$dst"


#="$1"

#./Tail.exe --lines="$n" < ./Paths.exe -R -s
