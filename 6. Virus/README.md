# Virus

### Problem
We have a network which is defined by the dependency and data transfer time among computers. For instance, if a computer ๐ฅ depends on a computer ๐ฆ with the transfer time ๐ก, then any data can be transferred from ๐ฆ to ๐ฅ in ๐ก seconds. Unfortunately, a computer in our network is infected with a virus. The virus will be propagated to the other computers which depend on the infected computers. When a computer ๐ฆ is just infected, the computer ๐ฅ will be infected after ๐ก seconds, if ๐ฅ depends on ๐ฆ with time ๐ก. We want to determine the number of computers that will be infected and the last time of infection from the first infection. Note that, your program can allocate up to 512MB memory and should produce the output within 3 seconds. <br>

<b>Input:</b> <br> 
In the first line, three integers ๐ (1 โค ๐ โค 10,000), ๐ (1 โค ๐ โค 100,000), and ๐  are given where ๐, ๐, and ๐  are the number of computers, the number of dependencies, and the index of first infected computer, respectively. The following lines describe ๐ dependencies in a format of โ๐ฅ ๐ฆ ๐กโ indicating that the computer ๐ฅ depends on ๐ฆ with transfer time of ๐ก, where ๐ฅ โ  ๐ฆ and 0 โค ๐ก โค 1000. Note that the vertex index begins with 1 and you can assume that the dependency is unique. <br>

<b>Output:</b> <br>
You are required to output the number of infected computers and time of the last infection from the first infection. <br><br>

### Input / Output
![image](https://user-images.githubusercontent.com/81274632/214041667-6437409e-822c-409d-b269-ac9e0ea4370f.png)
