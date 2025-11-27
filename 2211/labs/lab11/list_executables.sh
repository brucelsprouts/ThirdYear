#!/bin/sh

# This script prints the names of all executable files in the current working directory.

for file in *; do
    if [ -f "$file" ] && [ -x "$file" ]; then
        echo "$file"
    fi
done