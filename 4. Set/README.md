# Set

### Problem
Given a number š , we initially have š + 1 different sets which are {0}, {1}, {2},ā¦ , {š} . Your program should support two operations on those sets: 1) union two sets, and 2) check whether two elements are contained by the same set. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds.<br>

<b>Input:</b> <br>
In the first line, two integers š (1 ā¤ š ā¤ 1,000,000) and š (1 ā¤ š ā¤ 100,000) are given where š is the number of operations that will be sequentially performed. The following š lines specify the operations. A line having a format of ā0 š šā indicates a union operation of set š“ and set šµ containing elements š and š, respectively (š ā š“, š ā šµ). Similarly, a line beginning with ā1ā ask you to check whether š and š are in the same set. <br>

<b>Output:</b> <br>
For each checking operation, you are required to answer āYā if two elements are in the same set. Otherwise, print āNā. <br><br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214038647-76988b12-e50d-4e44-b247-d6bb061558fb.png)
