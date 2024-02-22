# Write a shell script for counting no of processes running on system 
#!/bin/bash

# Use the 'ps' command to list all processes, excluding headers
# and then count the lines (processes)
num_processes=$(ps aux --no-headers | wc -l)

echo "The number of processes running on the system is: $num_processes"
