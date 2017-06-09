#!/bin/bash

#trap "exit" INT TERM
#trap "kill $(jobs -p)" EXIT

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

startup=`mktemp`
coffee index.coffee |tee $startup &
grep -q -m1 "Listening" <(tail -f $startup)
chromium --user-data-dir=chromium_data --disable-background-timer-throttling --app=http://localhost:3000
JOBS=`jobs -p`
for job in $JOBS; do
	kill $job
	wait $job
done
