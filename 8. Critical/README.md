# Critical Time

We have 𝑁𝑁 tasks (𝑡𝑡1, 𝑡𝑡2,…, 𝑡𝑡𝑁𝑁) and each task has a performance time associated with it. We also have 𝑀𝑀 dependencies among tasks. If 𝑡𝑡𝑏𝑏 depends on 𝑡𝑡𝑎𝑎 , then 𝑡𝑡𝑏𝑏 cannot execute until 𝑡𝑡𝑎𝑎 completes. Compute the earliest time to complete all the tasks. You can assume that we have sufficient resources to execute all the given tasks in parallel. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds. <br>

<b>Input:</b> <br> 
In the first line, two integers 𝑁𝑁(1 ≤ 𝑁𝑁 ≤ 10,000) and 𝑀𝑀 (1 ≤ 𝑀𝑀 ≤ 100,000) are given where 𝑁𝑁 and 𝑀𝑀 are the number of tasks and dependencies, respectively. The following 𝑁𝑁 lines present performance times of 𝑁𝑁 tasks. The next 𝑀𝑀 lines give the dependences in a format of “𝑎𝑎 𝑏𝑏” indicating that 𝑡𝑡𝑏𝑏 depends on 𝑡𝑡𝑎𝑎. Note that the task index begins with 1 and the performance times are positive integers less than 100. <br>

<b>Output:</b> <br>
You are required to output the earliest time to complete all the tasks. If it is impossible to finish all the tasks, print “−1” <br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214039870-eb62e5ab-1d07-4383-8f23-0b44867c1bcc.png)
