#!/bin/bash

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <argument>"
  exit 1
fi

# Use the argument
dos2unix $1 && betty $1
#echo "You provided: $1"

