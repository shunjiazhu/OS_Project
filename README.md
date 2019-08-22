# OS_Project

## OS_Project1
In this project, you should add a new system call to the Android kernel(Linux). The system call you write should take two arguments and return the process tree information in a depth-first-search (DFS) order.


To know What you should do in detail, you can refer to the PDF file "*cs356project1*" and "*CS156-Project1*" .


More about my program:

- My system is "Linux Ubuntu 14.04".
- All  executable file are \*ARM such as "ptreeARM" and the kernel system call module is "ptreecall.ko"
- My working directory in the avd is /data/OsPrj5140219105. You should do "mkdir OsPrj5140219105" before push some file to the avd.
- my "kernel" is located at "~/Workspace"
- "ptreecall" is located at "~/Workspace/kernel/goldfish/kernel"
- "ptree" is located at "~/Workspace/kernel"
- "burger" is located at "～/Workspace"
- "GenerateProcess" is located at "~/Workspace"


## OS_Project2
In this project, you should write code to test different Android schedulers. After finishing the test, you should change the Round Robin scheduler and compile the kernel. Then you should test the new RR scheduler.

- The four folder “ptree”, “setSched”, “setSched” and “test” can be placed near the flodler “goldfish”.
The folder “ptreecall” can be put in /goldfish/kernel

- The files in ptree and ptreecall implement the system call to print the processes and their relationship

- setSched can set scheduler of one process.

- setZygoteSched can set schedulers of at most 50 processes. But you still need to input their pid one by one, which may not be user-friendly.

- test offers an application that can show you its running time.

- All \*\*ARM and .ko files  are in the /data/OsPrj5140219105 in the avd.


I do recommend you to read the PDF "cs356project2" and "CS356-Project2" to know what this project asks us to do. Meanwhile, you can get many clues from the two PDFs.


More details can be accessed in file "Prj2_5140219105_report".
