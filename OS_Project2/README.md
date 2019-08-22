# OS_Project2
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