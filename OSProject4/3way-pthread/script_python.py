import numpy as np
import matplotlib.pyplot as plt
import sys
import re
import subprocess
import time



command = "kstat -j " + sys.argv[1]
command_2 = "kstat -j " + sys.argv[2]
command_3 = "kstat -j " + sys.argv[3]

time.sleep(60) # The program is set to sleep for the jobs to be completed before trying to get stats

output_1 = subprocess.check_output(command, shell=True, text=True)
output_2 = subprocess.check_output(command_2, shell=True, text=True)
output_3 = subprocess.check_output(command_3, shell=True, text=True)

time_pattern = r"\b\d{2}:\d{2}:(\d{2})\b"
memory_pattern = r"\b(\d+\.\d+)gb\b"

# Search for matches using the pattern
matches = re.findall(time_pattern, output_1)
matches_2 = re.findall(time_pattern, output_2)
matches_3 = re.findall(time_pattern, output_3)

time = [] #Stores the times for each job
GB = [] #Stores the memory uses for each job

time.extend(matches)
time.extend(matches_2)
time.extend(matches_3)

time = [int(sec) for sec in time]

GB_match_1 = re.findall(memory_pattern, output_1)
GB_match_2 = re.findall(memory_pattern, output_2)
GB_match_3 = re.findall(memory_pattern, output_3)

GB.extend(GB_match_1[:2])
GB.extend(GB_match_2[:2])
GB.extend(GB_match_3[:2])

GB = [float(gb) for gb in GB]

cores_used = [1, 2, 4] 

# This is to ensure that there is only 3 times for graphing.
if (len(time) > 3):
    time = time[:3]

if (len(GB) > 3):
    GB = GB[:3]


# Plot the first bar graph
plt.figure()  
plt.bar(range(len(cores_used)), time, tick_label=cores_used)
plt.ylabel('Time (in seconds)')
plt.xlabel('Number of Cores Used')
plt.title("Completion Time Over Number Of Cores")
plt.ylim(0, 35)
plt.savefig('Pthreads_Graph_1.png')  # Save the plot as an image
plt.show()

# Plot the second bar graph
plt.figure()  
plt.bar(range(len(cores_used)), GB, tick_label=cores_used)
plt.ylabel('Memory (in GB)')
plt.xlabel('Number of Cores Used')
plt.title("Memory Used Over Number Of Cores")
plt.ylim(0, 5)
plt.savefig('Pthreads_Graph_2.png')  # Save the plot as an image
plt.show()
