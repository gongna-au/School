// 邻接矩阵的深度有限递归算法

#define TRUE 1
#define FALSE 0
#define MAX 256

typedef int Boolean; // 这里我们定义Boolean为布尔类型，其值为TRUE或FALSE
Boolean visited[MAX]; // 访问标志的数组

//进行递归的遍历包含顶点i的连通图
void DFS(MGraph G, int i)
{
  visited[i] = TRUE; // 访问过的顶点设置为TRUE
  printf("%c ", G.vexs[i]); // 打印顶点
  for( j=0; j < G.numVertexes; j++ )
  {
    if( G.arc[i][j]==1 && !visited[j] )
    {
      DFS(G, j); // 对为访问的邻接顶点递归调用
    }
  }
}

