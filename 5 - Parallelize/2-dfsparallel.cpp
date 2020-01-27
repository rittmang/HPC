//race condition mostly, reeeeeeep
#include<iostream>
#include<omp.h>
#include<vector>
#include<queue>
using namespace std;

vector<bool> v;
vector<vector<int> >g;

void edge(int a,int b)
{
    g[a].push_back(b);
    //for undirected, add g[b].push_back(a);
}
void bfs(int u)
{
    queue<int> q;
    q.push(u);
    v[u]=true;
    while (!q.empty()) {
        int qSize = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qSize; i++) {
            int currNode;
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
            }
            cout<<currNode<<" ";
            for(auto i=g[currNode].begin();i!=g[currNode].end();i++)
            {
                if(!v[*i])
                {
                    #pragma omp critical
                    q.push(*i);
                    v[*i]=true;
                }
            }
            //doStuff(currNode);
            #pragma omp critical
            q.push(currNode);
        }
    }

}

int main()
{
    int n, e; 
    cin >> n >> e; 
  
    v.assign(n, false); 
    g.assign(n, vector<int>()); 
  
    int a, b; 
    for (int i = 0; i < e; i++) { 
        cin >> a >> b; 
        edge(a, b); 
    } 
  
    for (int i = 0; i < n; i++) { 
        if (!v[i]) 
            bfs(i); 
    } 
  
    return 0; 
}
