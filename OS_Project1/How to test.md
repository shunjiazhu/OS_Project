Problem 1 and Problem 2:
1.Go into the “ptreecall” directory , “make” and "adb push ptreecall.ko /data/OsPrj5140219105" 
2.Go into the “ptree” directory “ndk-build” and "adb push ptreeARM /data/OsPrj5140219105"
3."adb shell" and go into /data/OsPrj5140219105
4."insmod ptreecall.ko"
5."./ptreeARM" or "./ptreeARM  *" (* is a number)



Problem 3:
1.Go into the “GenerateProcess” directory, “ndk-build” and "adb push generateProcessARM /data/OsPrj5140219105"
2.Make sure ptreecall.ko is insmoded and ptreeARM is in the directory
3."./generateProcessARM"



Problem 4:
1.Go into the “burger” directory , “ndk-build” and "adb push burgerARM /data/OsPrj5140219105"
2."./burgerARM 4 4 30 10" , if the number of arguments(parameters) is less than 5, it will not execute. Otherwise, it will take the first five arguments to execute the program.




已知问题：
1.ptree打印树的时候，这棵树的高度不应该超过200，但是由于linux的进程深搜树高度一般不会超过10，所以应该没什么问题。
2.burger中每前3个参量都应该小于300，如果超过300，我担心虚拟机会出问题。不过只要修改burger.c文件中的#define MAX 300，就可以解除这一限定。
3.程序的健壮性只停留在输入参数的个数的检查，输入的参量是用的atoi()函数转化为数据，当输入其他字符串的时候估计会报错。
