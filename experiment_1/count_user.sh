# Write a shell script for counting no of logged in users.

#!/bin/bash

# Use the 'who' command to get a list of logged-in users and count the lines
num_users=$(who | wc -l)

echo "The number of logged-in users is: $num_users"
