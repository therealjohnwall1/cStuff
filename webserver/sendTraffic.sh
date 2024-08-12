#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <server> <amount>"
    exit 1
fi

SERVER=$1
AMOUNT=$2

# Loop to call clientSend the specified number of times
for ((i=0; i<AMOUNT; i++))
do
    ./clientSend "$SERVER"
done