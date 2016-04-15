#!/usr/bin/python2.7

import time
import random
import subprocess

print "generating input..."

input_file = open("input.txt", "w")

size = random.randrange(100000, 1000000)
nums = [size]

while size:
    nums.append(random.randrange(0, 1000000))
    size -= 1

input_file.writelines('\n'.join(map(lambda x: str(x), nums)))

print "running application..."

command = "./prog input.txt output.txt"
subprocess.Popen(command, shell = True).wait()

#time.sleep(1)

print "checking output..."

output_file = open("output.txt", "r")
nums = output_file.readlines()

index = 0
while index < size - 1:
    if int(nums[index]) > int(nums[index + 1]):
        break
else:
    print "passed"

print "completed successfully"

