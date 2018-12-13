#include <iostream>
#include <vector>
using namespace std;
bool isExisting (vector<int> graf, int element)
{
    bool flag = false;
    for(size_t i = 0; i < graf.size(); i++)
    {
        if(graf[i] == element) flag = true;
    }
    return flag;
}
void dfs (int arr[10][10], vector<int> visited, int start)
{
    visited.push_back(start);
    cout<<start<<endl;
    for(size_t j = 0; j < 10; j++)
        {
            if(arr[start][j] != 0 && isExisting(visited, j) == false)
            {
                dfs(arr, visited, j);
            }
        }

}

void bfs (int arr[10][10], vector<int> visited, int start)
{
    queue<int> q;
    q.push(start);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        if(isExisting(visited, current)) continue;
        visited.push_back(current);
        cout<<current<<" ";
        for(int i=0;i<10;i++)
        {
            if(arr[current][i] && !isExisting(visited,i)) {}
            q.push(i);
        }

    }
}
