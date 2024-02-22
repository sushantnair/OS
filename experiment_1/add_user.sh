# Write a shell script for adding users.

#!/bin/bash

# Check if the script is run as root
if [ "$EUID" -ne 0 ]; then
  echo "This script must be run as root."
  exit 1
fi

# Check if an argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <username>"
  exit 1
fi

username="$1"

# Check if the user already exists
if id "$username" &>/dev/null; then
  echo "User '$username' already exists."
  exit 1
fi

# Create the user with a home directory and group
useradd -m -s /bin/bash "$username"

if [ "$?" -eq 0 ]; then
  echo "User '$username' has been created successfully."
else
  echo "Failed to create user '$username'."
  exit 1
fi
