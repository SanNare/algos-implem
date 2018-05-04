#include<bits/stdc++.h>
#define inf 10000

using namespace std;

typedef vector<vector<pair<int,int>>> List;
typedef vector<vector<int>> matrix;

vector<pair<int,int>> BFS(List adj,int s)
{
		int n = adj.size();
		vector<pair<int,int>> prev(n,make_pair(-1,inf));
		vector<bool> visited(n,false);
		queue<int> q;
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
					prev[v-1] = make_pair(u,p.second);
					q.push(v);
				}
			}
		}
		cout<<endl;
		return prev;
}	

pair<int,vector<pair<int,int>>> findPath(List &adj,int s,int t)
{
	vector<pair<int,int>> prev = BFS(adj,s);
	int cf = inf,c = t;
	while(c != s && c != -1)
	{
		cf = min(cf,prev[c-1].second);
		c = prev[c-1].first;
	}
	if(c == -1)
		return make_pair(-1,prev);
	else
		return make_pair(cf,prev);
}

class network
{
	int n;
	List adj;
	matrix f;
	public:
		network(int n = 0)
		{
			this->n = n;
			adj.reserve(n);
			f.reserve(n);
			for(int i = 0;i<n;i++)
			{
				f[i].reserve(n);
				for(int j = 0;j<n;j++)
					f[i][j] = -1;
			}
		}
		void addEdge(int u,int v,int w)
		{
			adj[u-1].push_back(make_pair(v,w));
		}
		void displayAdj()
		{
			for(int i = 0;i<n;i++)
			{
				cout<<i+1<<": ";
				for(auto p:adj[i])
				cout<<"("<<p.first<<","<<p.second<<") ";
				cout<<endl;
			}
		}
		void initializeFlow()
		{
			for(int i = 0;i<n;i++)
			{
				for(auto p:adj[i])
				{
					int j = p.first-1;
					f[i][j] = 0;
				}
			}
		}
		void displayFlow()
		{
			for(int i = 0;i<n;i++)
			{
				for(int j = 0;j<n;j++)
					cout<<f[i][j]<<" ";
				cout<<endl;
			}
		}
		List residual()
		{
			List r(n);
			for(int u = 1;u<=n;u++)
			{
				for(auto p:adj[u-1])
				{
					int v = p.first,c = p.second;
					if(f[u-1][v-1] != -1)
					{
						if(c-f[u-1][v-1]>0)
							r[u-1].push_back(make_pair(v,c-f[u-1][v-1]));
						if(f[u-1][v-1]>0)
							r[v-1].push_back(make_pair(u,f[u-1][v-1]));
					}
				}
			}
			return r;
		}
		int maxFlow(int s,int t)
		{
			initializeFlow();
			List r = residual();
			pair<int,vector<pair<int,int>>> q = findPath(r,s,t);
			vector<pair<int,int>> prev = q.second;
			int cf = q.first;
			while(cf != -1)
			{
				int v = t,u = prev[t-1].first;
				while(u != -1)
				{
					u = prev[v-1].first;
					if(f[u-1][v-1] != -1)
						f[u-1][v-1]+=cf;
					else
						f[v-1][u-1]-=cf;
					v = u;
				}
				r = residual();
				q = findPath(r,s,t);
				prev = q.second;
				cf = q.first;
			}
			int val = 0;
			for(auto p:adj[s-1])
			{
				int x = p.first;
				val+=f[s-1][x-1];
			}
			return val;
		}
};

int main()
{
	int n;
	cout<<"Enter the number of vertices in the network:"<<endl;
	cin>>n;
	network g(n);
	char op;
	do
	{
		cout<<"Enter an edge (u,v) and its capacity c:"<<endl;
		int u,v,c;
		cin>>u>>v>>c;
		g.addEdge(u,v,c);
		cout<<"Want to enter more edges?(Y/N)"<<endl;
		cin>>op;
	}while(op != 'n' && op != 'N');
	/*cout<<"The adjacency list and flow matrix are:"<<endl;
	g.displayAdj();
	g.initializeFlow();
	g.displayFlow();
	List r = g.residual();
	cout<<"The adjacency list of the residual graph is:"<<endl;
	for(int i = 0;i<n;i++)
			{
				cout<<i+1<<": ";
				for(auto p:r[i])
				cout<<"("<<p.first<<","<<p.second<<") ";
				cout<<endl;
			}*/
	cout<<"Enter the source and sink vertices:"<<endl;
	int s,t;
	cin>>s>>t;
	cout<<"The maximum flow obtained is: "<<g.maxFlow(s,t)<<endl;
	g.displayFlow();
	return 0;
}