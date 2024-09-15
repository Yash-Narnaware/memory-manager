# Memory Manager
Simulating the operating system's process of allocating the memory to each task

## Files and folders in directory - 

1.  ./page_table_as_hashmap - for hashmap implementation of page table
2.  ./single_level_page_table - for implementing single level page table
3.  ./second_level_page_table - for implementing second level page table
4.  ./tracefiles - to store all the trace files
5.  config.h - for defining all the parameters such as virtual memory tracefile to run program on, page size etc.
6.  generateTraces.cpp - it will generate the number of traces specified by user and store it in "generated_traces.txt" file in tracefiles folder.

## Each implementation folder contains this files - 

1. **memoryManager.cpp** - in this file the logic of assigning memory is implemented
2. **task.cpp** - in this file there is class named task to store all task related information for each task and there are various functions that provides various functionality to program
3. **transformTraces.cpp** - this file converts the given trace file in our desired format that we want the traces to be in and store the results in "testcases.txt"
4. **testMemoryManager.cpp** - this file runs all the instances of tasks from "testcases.txt" file and stores the output in "output.txt" file. 


## How to run this program? 

1. Put your trace file in "tracefiles" folder.
2. Change the filename and other parameters in "config.h"
3. Go inside the folder of which implementation you want to execute the trace file on.
4. run command "g++ transformTraces.cpp" and then "./a.out" to transform the trace file in particular format that our program takes.
5. run command "g++ testMemoryManager.cpp" an then "./a.out" to run the program and output will be printed in terminal and will be saved in "ouput.txt"

## How to generate trace file and test memory manager on it?

1. execute file "generateTraces.cpp" using "g++ generateTraces.cpp" followed by "./a.out"
2. change FILE_NAME to "generated_traces.txt" in config.h
3. follow instructions of "How to run this program?" from instruction 3.  


