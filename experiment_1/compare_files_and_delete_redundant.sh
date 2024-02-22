#!/bin/bash

# Write a shell Script that accepts two file names as command line arguments
# and  compare two file contents and check whether contents are same or not. 
# If they are same, then delete second file.

# Check if two file names are provided as command line arguments
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <file1> <file2>"
  exit 1
fi

file1="$1"
file2="$2"

# Check if both files exist
if [ ! -e "$file1" ] || [ ! -e "$file2" ]; then
  echo "One or both files do not exist."
  exit 1
fi

# Compare the contents of the two files
if cmp -s "$file1" "$file2"; then
  echo "The contents of $file1 and $file2 are the same."
  echo "Deleting $file2..."
  rm "$file2"
  echo "$file2 has been deleted."
else
  echo "The contents of $file1 and $file2 are different."
fi
