# Jump

We would like to cross over a river by stepstones. The position of a stepstone is represented by (𝑥, 𝑦).
You can jump to another stepstone, however, you have certain constraint due to your physical ability.
When you are at (𝑥, 𝑦), you are only allowed to jump to stones at (𝑥′, 𝑦′) where |𝑥 − 𝑥′| ≤ 2 and
|𝑦 − 𝑦′| ≤ 2 . For instance, you can jump from (0,0) to (2,2) or (2,1) , but you cannot move to
(3,0). The goal is reaching a line 𝑦 = 𝐺 which is parallel to 𝑥-axis. You are required to find a shortest
path from (0,0) to the goal line in terms of the sum of distances. The distance between two stones at
(𝑥, 𝑦) and (𝑥′, 𝑦′) is the Euclidean distance {(𝑥 − 𝑥′)<sup>2</sup> + (𝑦 − 𝑦′)<sup>2</sup>}<sup>1/2</sup>. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds. <br>

<b>Input:</b> <br> 
In the first line, two integers 𝑛 (1 ≤ 𝑛 ≤ 50,000), and 𝐺 are given where 𝑛 and 𝐺 are the number
of stepstones and the 𝑦 coordinate of the goal line, respectively. The following lines describe the
position of 𝑛 stepstones in a format of “𝑥 𝑦” where 𝑥 and 𝑦 are integers. Note that 0 ≤ 𝐺, 𝑥, 𝑦 ≤ 1,000,000. <br>

<b>Output:</b> <br>
Provide the distance of shortest path by rounding off to the nearest integer. (The exact distance in the following sample is 8.47 ⋯ . You need to answer 8 by rounding off the exact distance.) <br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214044090-da2855cc-3481-4935-aa1a-4dc8bdf8dd63.png)
