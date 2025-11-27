#!/bin/sh

# This script prints the last argument passed to it.
# If no arguments are provided, it prints nothing.

if [ "$#" -eq 0 ]; then
    exit 0
fi

last_arg=""
while [ "$#" -gt 0 ]; do
    last_arg="$1"
    shift
done

echo "$last_arg"