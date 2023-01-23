# Critical Time

We have 𝑁 tasks (𝑡<sub>1</sub>, 𝑡<sub>2</sub>,…, 𝑡<sub>𝑁</sub>) and each task has a performance time associated with it. We also have 𝑀 dependencies among tasks. If 𝑡<sub>𝑏</sub> depends on 𝑡<sub>𝑎</sub> , then 𝑡<sub>𝑏</sub> cannot execute until 𝑡𝑡𝑎𝑎 completes. Compute the earliest time to complete all the tasks. You can assume that we have sufficient resources to execute all the given tasks in parallel. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds. <br>

<b>Input:</b> <br> 
In the first line, two integers 𝑁(1 ≤ 𝑁 ≤ 10,000) and 𝑀 (1 ≤ 𝑀 ≤ 100,000) are given where 𝑁 and 𝑀 are the number of tasks and dependencies, respectively. The following 𝑁 lines present performance times of 𝑁 tasks. The next 𝑀 lines give the dependences in a format of “𝑎 𝑏” indicating that 𝑡<sub>𝑏</sub> depends on 𝑡<sub>𝑎</sub>. Note that the task index begins with 1 and the performance times are positive integers less than 100. <br>

<b>Output:</b> <br>
You are required to output the earliest time to complete all the tasks. If it is impossible to finish all the tasks, print “−1” <br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214046258-e33b1cba-e703-4c25-b4b7-ee79fbff6af1.png)
<br>
![image](https://user-images.githubusercontent.com/81274632/214046403-6d8dcf50-8921-4c10-be9b-45622bdc5fec.png)
