The four folder “ptree”, “setSched”, “setSched” and “test” can be placed near the flodler “goldfish”. 
The folder “ptreecall” can be put in /goldfish/kernel

The files in ptree and ptreecall implement the system call to print the processes and their relationship

setSched can set scheduler of one process.

setZygoteSched can set schedulers of at most 50 processes. But you still need to input their pid one by one, which may not be user-friendly.

test offers an application that can show you its running time.

All \*\*ARM and .ko files  are in the /data/OsPrj5140219105 in the avd.