#include<bits/stdc++.h>
#define inf 100000
using namespace std;

struct edge
{
	int u,v,w;
	edge(int x = 0,int y = 0,int z = inf)
	{
		u = x;
		v = y;
		w = z;
	}
};

class graph
{
	vector<vector<pair<int,int>>> adj;
	vector<vector<int>> m;
	vector<edge> E;
	int n;
	void DFSVisit(int u,int &time,vector<bool> &visited,vector<int> &prev,vector<int> &d,vector<int> &f)
	{
		time++;
		d[u-1] = time;
		visited[u-1] = true;
		for(auto p:adj[u-1])
		{
			int v = p.first;
			if(!visited[v-1])
			{
				prev[v-1] = u;
				DFSVisit(v,time,visited,prev,d,f);
			}
		}
		time++;
		f[u-1] = time;
	}
	public:
		graph(int v = 0)
		{
			n = v;
			adj.reserve(n);
			m.reserve(n);
			for(int i = 0;i<n;i++)
			{
				m[i].reserve(n);
				for(int j = 0;j<n;j++)
				{
					if(i == j)
						m[i][j] = 0;
					else
						m[i][j] = inf;
				}
			}
		}
		void addEdge(int x,int y,int z)
		{
			edge e(x,y,z);
			adj[x-1].push_back(make_pair(y,z));
			m[x-1][y-1] = z;
			E.push_back(e);
		}
		void displayList()
		{
			for(int u = 1;u<=n;u++)
			{
				cout<<u<<": ";
				for(auto p:adj[u-1])
					cout<<"("<<p.first<<","<<p.second<<")"<<" ";
				cout<<endl;
			}
		}
		void displayMatrix()
		{
			for(int i = 0;i<n;i++)
			{
				for(int j = 0;j<n;j++)
				{
					if(m[i][j] == inf)
						cout<<"INF"<<" ";
					else
						cout<<m[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		pair<vector<int>,vector<int>> BFS(int s)
		{
			vector<int> d(n,inf),prev(n,-1);
			vector<bool> visited(n,false);
			queue<int> q;
			d[s-1] = 0;
			visited[s-1] = true;
			q.push(s);
			while(!q.empty())
			{
				int u = q.front();
				q.pop();
				cout<<u<<" ";
				for(auto p:adj[u-1])
				{
					int v = p.first;
					if(!visited[v-1])
					{
						visited[v-1] = true;
						d[v-1] = d[u-1]+1;
						prev[v-1] = u;
						q.push(v);
					}
				}
			}
			cout<<endl;
			return make_pair(d,prev);
		}
		tuple<vector<int>,vector<int>,vector<int>> DFS()
		{
			vector<bool> visited(n,false);
			vector<int> d(n),f(n),prev(n,-1);
			int time = 0;
			for(int u = 1;u<=n;u++)
			{
				if(!visited[u-1])
					DFSVisit(u,time,visited,prev,d,f);
			}
			return make_tuple(prev,d,f);
		}
};

string BFSPath(vector<int> &prev,int u,int v)
{
	string path = "";
	stack<int> s;
	int i;
	for(i = v;i != -1 && i != u;i = prev[i-1])
		s.push(i);
	if(i == -1)
		path = "No path exists!";
	else
	{
		s.push(u);
		while(!s.empty())
		{
			int t = s.top();
			s.pop();
			path+=(char)(t+48);
			path+=" ";
		}
	}
	return path;
}

int main()
{
	int n;
	cout<<"Enter the number of vertices in the graph:"<<endl;
	cin>>n;
	graph g(n);
	char op;
	do
	{
		cout<<"Enter an edge (u,v) and its weight w:"<<endl;
		int u,v,w;
		cin>>u>>v>>w;
		g.addEdge(u,v,w);
		cout<<"Want to enter more edges?(Y/N)"<<endl;
		cin>>op;
	}while(op != 'n' && op != 'N');
	cout<<"The adjacency list constructed is:"<<endl;
	g.displayList();
	cout<<"The corresponding adjacency matrix is:"<<endl;
	g.displayMatrix();
	// BFS Test
	/*int s; 
	cout<<"Enter the start vertex for breadth first search:"<<endl;
	cin>>s;
	pair<vector<int>,vector<int>> p = g.BFS(s);
	vector<int> d = p.first,prev = p.second;
	cout<<"The BFS tree constructed is:"<<endl;
	for(int i = 0;i<n;i++)
		cout<<"Parent of "<<i+1<<" is "<<prev[i]<<endl;
	cout<<"The distances from the start vertex are:"<<endl;
	for(int i = 0;i<n;i++
	)
		cout<<"d("<<i+1<<") = "<<d[i]<<endl;
	cout<<"Enter two vertices (u,v) to find a path between them:"<<endl;
	int u,v;
	cin>>u>>v;
	cout<<"The path is:"<<endl;
	cout<<BFSPath(prev,u,v)<<endl;*/
	return 0;
}