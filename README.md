# Priority-Scheduling

<h2>Compilation Instructions</h2>
<b>gcc JKim_schd.c -o JKim_thd.exe	<br>				                                                  
./JKim_thd.exe 1 > JKimResultNonpreemptive.txt  <br>                                                                                        
./JKim_thd.exe 2 > JKimResultPreemptive.txt </b>  

<h2>Program Design</h2>
This program simulates the priority non-preemptive and priority preemptive scheduling algorithms. It uses the singly LinkedList data structure to store the processes. In the non-preemptive scheduling, processes with the highest priority runs first without preemption. The wait time is calculated by subtracting arrival time and burst time from the current time. In preemptive scheduling, the arrived processes with the same priority runs in a round robin scheduling with the time quantum of 10. The wait time is calculated by subtracting the arrival time and duration of time previously ran from the current time. Once a process is run, it receives a new priority value of 100. Its large value indicates that the process has already ran, so its priority becomes low.

<h2>Input</h2>
<pre>
Process	Priority	Burst	Arrival
1	8	15	0
2	3	20	0
3	4	20	20
4	4	20	25
5	5	5	45
6	5	15	55
7	9	10	70
8	6	15	100
9	5	15	105
10	5	15	115

</pre>
<h2>Nonpreemtive Scheduling</h2>
<pre>
Time	Process
---------------
0	2
20	3
40	4
60	5
65	6
80	1
95	7
105	9
120	10
135	8

Process	Wait Time
---------------------
1	80
2	0
3	0
4	15
5	15
6	10
7	25
8	35
9	0
10	5

</pre>
<h2>Preemptive Scheduling</h2>
<pre>
Time	Process
---------------
0	2
20	3
30	4
40	3
50	4
60	3
60	4
60	5
65	6
75	6
80	8
95	1
105	9
120	10
135	1
140	7
150	7

Process	Wait Time
---------------------
1	125
2	0
3	20
4	15
5	15
6	20
7	80
8	-20
9	0
10	5

</pre>
