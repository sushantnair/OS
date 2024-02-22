# Write a shell script that accepts integer and find the factorial of the number.

#!/bin/bash

# Check if an integer argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <integer>"
  exit 1
fi

# Get the integer from the command line argument
n="$1"

# Check if the provided argument is a non-negative integer
if ! [[ "$n" =~ ^[0-9]+$ ]]; then
  echo "Please provide a non-negative integer as an argument."
  exit 1
fi

# Initialize the factorial to 1
factorial=1

# Calculate the factorial
for ((i = 1; i <= n; i++)); do
  factorial=$((factorial * i))
done

echo "The factorial of $n is $factorial"
