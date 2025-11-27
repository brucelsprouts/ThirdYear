#!/bin/sh

# Check for correct number of arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
fi

input_file="$1"
output_file="$2"

# Check if input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' not found."
    exit 1
fi

echo "Encrypting '$input_file' to '$output_file'..."
openssl enc -aes-256-cbc -salt -in "$input_file" -out "$output_file"
echo "Encryption complete."