# Virus

We have a network which is defined by the dependency and data transfer time among computers. For instance, if a computer 𝑥 depends on a computer 𝑦 with the transfer time 𝑡, then any data can be transferred from 𝑦 to 𝑥 in 𝑡 seconds. Unfortunately, a computer in our network is infected with a virus. The virus will be propagated to the other computers which depend on the infected computers. When a computer 𝑦 is just infected, the computer 𝑥 will be infected after 𝑡 seconds, if 𝑥 depends on 𝑦 with time 𝑡. We want to determine the number of computers that will be infected and the last time of infection from the first infection. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds. <br>

<b>Input:</b> <br> 
In the first line, three integers 𝑛 (1 ≤ 𝑛 ≤ 10,000), 𝑚 (1 ≤ 𝑚 ≤ 100,000), and 𝑠 are given where 𝑛, 𝑚, and 𝑠 are the number of computers, the number of dependencies, and the index of first infected computer, respectively. The following lines describe 𝑚 dependencies in a format of “𝑥 𝑦 𝑡” indicating that the computer 𝑥 depends on 𝑦 with transfer time of 𝑡, where 𝑥 ≠ 𝑦 and 0 ≤ 𝑡 ≤ 1000. Note that the vertex index begins with 1 and you can assume that the dependency is unique. <br>

<b>Output:</b> <br>
You are required to output the number of infected computers and time of the last infection from the first infection. <br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214041667-6437409e-822c-409d-b269-ac9e0ea4370f.png)
