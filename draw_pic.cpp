#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#define num_nodes 5
using namespace std;
struct Vertex{
    int color,degree;
}vertex[num_nodes];
/*
data set:

0 1 1 1 0
1 0 1 1 1
1 1 0 1 0
1 1 1 0 1
0 1 0 1 0
*/
void printSolution()
{
    int i = 0;
    cout<<"Following are the assigned colors \n"<<endl;
    for(i = 0; i <num_nodes; i++)
    {
        cout<<"node: "<<i+1<<" color: ";
        cout<<vertex[i].color;
        cout<<endl;
    }

    cout<<endl;
}

bool isSafe(int v, int graph[num_nodes][num_nodes], int color)
{
    //用于检查颜色分配是否符合条件
    int i=0;
    for(i=0; i<v; i++)
        if(graph[v][i]==1 && color==vertex[i].color)//如果存在边vi且v点和i点颜色相同
        return false;
    return true;
}
void graphColoring(int graph[num_nodes][num_nodes], int num_color, int v)
{
    //回溯分配颜色
    int i =0;
    if(v == num_nodes)//如果所有点已经分配过了
    {
        printSolution();//输出解决方案
        return;
    }
    for(i=0; i<num_color; i++)
    {
        if(isSafe(v, graph, i))//判断是否满足，不满足则略过
        {
            vertex[v].color=i;
            graphColoring(graph, num_color, v+1);
            //vertex[v].color=0;
        }
    }

}

void show(int c[num_nodes][num_nodes])
{
    //用于展示邻接矩阵，并将度输入vertex中
    int i,j;
    cout<<"the adjacency matrix:";
    for(i=0;i<num_nodes;i++)
    {
        cout<<endl;
        for(j=0;j<num_nodes;j++)
        {
            cout<<c[i][j];
            cout<<" ";
        }
    }
    // 计算每个节点的度，记录到vertex中
    for(i=0;i<num_nodes;i++)
    {
        vertex[i].color=vertex[i].degree=0;
        for(j=0;j<num_nodes;j++)
            vertex[i].degree+=c[i][j];
    }
    // 将度输出到屏幕
    cout<<endl;
    cout<<endl;
    cout<<"degree list:"<<endl;
    for(i=0;i<num_nodes;i++)
    {
        cout<<"node "<<i+1<<"degree:";
        cout<<vertex[i].degree;
        cout<<endl;
    }
    cout<<endl;
}

bool cmp(Vertex a, Vertex b){return a.degree> b.degree;}

void welch_powell(int c[num_nodes][num_nodes])
{
    //排序后进行贪心算法
    sort(vertex+1,vertex+num_nodes+1,cmp);
    int colored_vertices_cnt = 0;//已经着色的点
    int ncolor = 0;//当前颜色
    int i,j;

    for(i=0;i<num_nodes;i++)
    {
        vertex[i].color=0;//清空上一个算法已经记录的着色信息
    }

    while(colored_vertices_cnt<num_nodes)
    {
        ncolor++;
        for(i=0;i<num_nodes;i++)
        {
            if(vertex[i].color) continue;//如果该点已经有颜色，则判断下一个点
        bool ok=1;

        for(j=0;j<num_nodes;j++)//对邻居节点循环判断是否符合条件
        {
            if(!c[i][j])continue;
            if(vertex[j].color==ncolor)
            {
                ok=0;
                break;
            }
        }

        if(!ok)continue;
        vertex[i].color=ncolor;//给该点上色
        colored_vertices_cnt++;//已着色的点+1
        cout<<"node"<<i+1<<" color:"<<vertex[i].color<<endl;
        }
    }
}
int main()
{
    int n;
    int num_color;
    int i,j,answer;
    int c[num_nodes][num_nodes];
    int color[num_nodes];

    // 从文件流读取邻接矩阵
    ifstream infile;
    infile.open("data.txt");
    for(i=0;i<num_nodes;i++)
        for(j=0;j<num_nodes;j++)
        {
            infile>>n;
            c[i][j]=n;
        }
    infile.close();

    show(c);//输出邻接矩阵到屏幕

    while(1)
    {
        cout<<"choose function:"<<endl;
        cout<<"1:Backtracking method"<<endl;
        cout<<"2:Welch_powell method"<<endl;
        cin>>answer;
        if(answer==1)
        {
            cout<<"Please input the number of colors"<<endl;
            cin>>num_color;
            graphColoring(c, num_color, 0);
        }
        if(answer==2)
        welch_powell(c);
    }

}
