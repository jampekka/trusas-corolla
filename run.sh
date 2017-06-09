#!/bin/bash

trap "exit" INT TERM
trap "kill 0" EXIT

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

while true; do
	./run_once.sh
	if [ ! -f test_sessions/_session.lock ]; then
		break
	fi
done
