# Set

### Problem
Given a number 𝑛 , we initially have 𝑛 + 1 different sets which are {0}, {1}, {2},… , {𝑛} . Your program should support two operations on those sets: 1) union two sets, and 2) check whether two elements are contained by the same set. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds.<br>

<b>Input:</b> <br>
In the first line, two integers 𝑛 (1 ≤ 𝑛 ≤ 1,000,000) and 𝑚 (1 ≤ 𝑚 ≤ 100,000) are given where 𝑚 is the number of operations that will be sequentially performed. The following 𝑚 lines specify the operations. A line having a format of “0 𝑎 𝑏” indicates a union operation of set 𝐴 and set 𝐵 containing elements 𝑎 and 𝑏, respectively (𝑎 ∈ 𝐴, 𝑏 ∈ 𝐵). Similarly, a line beginning with ‘1’ ask you to check whether 𝑎 and 𝑏 are in the same set. <br>

<b>Output:</b> <br>
For each checking operation, you are required to answer ‘Y’ if two elements are in the same set. Otherwise, print ‘N’. <br><br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214038647-76988b12-e50d-4e44-b247-d6bb061558fb.png)
