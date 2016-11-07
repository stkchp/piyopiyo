#!/bin/bash

tmux_title() {
	message=$1
	[[ $TMUX_PANE == "" ]] && return
	tmux rename-window -t $TMUX_PANE "$message"
}

trap "exit 0" 2 # Interrupt

cd $(dirname $0)
CURDIR=$(pwd)

RUN_BUILD=$CURDIR/make.sh

inotifywait -e CLOSE_WRITE -m -r $CURDIR --format "%w %f %e" | \
while read LINE; do

	filename=$( echo $LINE | awk '{print $2}' )
	echo $filename | egrep '^[^/]+(\.h|\.cpp|\.sh)$' > /dev/null
	[[ $? -ne 0 ]] && continue

	tmux_title "building..."

	echo "== MODIFIED ---> '$filename' =="
	$RUN_BUILD
	if [[ $? -ne 0 ]]
	then
		tmux_title "build...NG"
		echo -e "\e[31m== Build Error ==\e[m"
		continue
	fi

	tmux_title "build...OK"
	echo -e "\e[34m== Build Succeeded!! ==\e[m"
done
