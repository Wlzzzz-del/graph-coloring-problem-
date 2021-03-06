# 问题
图着色问题（Graph Coloring Problem， GCP）又称为着色问题，是最著名的NP-完全问题之一。给定一个无向图 ,其中 为顶点集合， 为边集合，图着色问题即为将 分为K个颜色组，每个组形成一个独立集，即其中没有相邻的顶点。图着色问题又包含两个子问题：m色优化问题和m色判断问题。
M色优化问题，即求出给定无向图最少需要几种颜色可以满足图着色要求。
M色判断问题，即判断用m种颜色够不够。

# 实现
本程序通过C++实现图着色问题（Welch Powell法和回溯法）


# 实际意义
图着色问题可以用来解决寄存器分配技术。利用相交图（interference graph）来表示程序变量的生命期是否相交，将寄存器分配给变量的问题，可以近似地看成是给相交图着色：相交图中，相交的节点不能着同一个颜色；每一个颜色对应一个寄存器。Chaitin等人最早提出了基于图着色的寄存器分配方法，其着色思路采用了Kempe的着色方法，即任意一个邻居节点数目少于K的节点，都能被K着色。判断一个图是否能够被K种颜色着色，即K着色问题，被Karp证明是一个NP-complete问题。
图着色问题还可以应用于道路着色问题（Road Coloring Problem）中，道路着色问题是图论中最著名的猜想之一。这个猜想认为，可以绘制一张“万能地图”，来指导人们到达某一个目的地，不管他们原来在什么位置。

# 算法介绍
本文用Welch Powell法求解m色优化问题,Welch Powell本质也是采用贪婪算法的思想：选择一种颜色，用该颜色为尽可能多的节点着色。但是与传统的贪婪算法不同的是该算法在第一步首先对节点按照度降序排序，然后根据顺序进行贪婪算法。本文还用回溯算法求解m色判断问题，在包含问题的所有解的解空间树中，按照深度优先搜索的策略，从根结点出发深度探索解空间树。当探索到某一结点时，要先判断该结点是否包含问题的解，如果包含，就从该结点出发继续探索下去，如果该结点不包含问题的解，则逐层向其祖先结点回溯。与普通的回溯法不同的是，我们目的在于给出所有解决方案，因此得到一个解决方案后需要回溯到上一层寻找下一个方案。
