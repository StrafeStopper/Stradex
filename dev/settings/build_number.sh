#!/bin/sh
read build_number < /settings/build_number.txt
build_number=$((build_number+1))

echo "$build_number" > "settings/build_number.txt"
