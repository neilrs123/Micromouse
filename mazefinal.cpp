#include<bits/stdc++.h>
#include<vector>

using namespace std;

int n=6;
int **a;
int direction = 1;

void update(int x, int y)
{
	if(x==0 && y==0)
		a[x][y]= std::min(a[1][0],a[0][1])+1;
	else if(x==n-1 && y==0)
		a[x][y]= std::min(a[n-2][0],a[n-1][1])+1;
	else if(x==n-1 && y==n-1)
		a[x][y]= std::min(a[n-2][n-1],a[n-1][n-2])+1;	
	else if(x==0 && y==n-1)
		a[x][y]= std::min(a[0][n-2],a[1][n-1])+1;	
	else if(x==0)
	{
		a[x][y]= std::min(a[0][y-1],a[0][y+1]);
		a[x][y]= std::min(a[x][y],a[1][y])+1;
	}
	else if(y==0)
	{
		a[x][y]= std::min(a[x-1][0],a[x+1][0]);
		a[x][y]= std::min(a[x][y],a[x][1])+1;
	}		
	else if(x==n-1)
	{
		a[x][y]= std::min(a[n-1][y-1],a[n-1][y+1]);
		a[x][y]= std::min(a[x][y],a[n-2][y])+1;
	}		
	else if(y==n-1)
	{
		a[x][y]= std::min(a[x-1][n-1],a[x+1][n-1]);
		a[x][y]= std::min(a[x][y],a[x][n-2])+1;
	}
	else
	{
		a[x][y]= std::min(a[x-1][y],a[x+1][y]);
		a[x][y]= std::min(a[x][y],a[x][y-1]);
		a[x][y]= std::min(a[x][y],a[x][y+1])+1;
	}		
}

void print()
{
	int i,j;
	for(i=n-1;i>=0;i--)
	{
		for(j=0;j<n;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	int i,j;
	int discover[n*n];
	a = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		a[i]=(int*)malloc(n*sizeof(int));
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=1000;
		}
	}
	a[n/2][n/2]=0;
	a[n/2-1][n/2]=0;
	a[n/2][n/2-1]=0;
	a[n/2-1][n/2-1]=0;
	vector< pair <double,int> > arr;
	double mid = (double)(n-1)/2;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			double t = pow((i-mid),2) + pow((j-mid),2);
			arr.push_back(make_pair(t,i*n+j));
		}
	}
	sort(arr.begin(),arr.end());
//	for(i=0;i<n*n;i++)
//	{
//		int x = arr[i].second/n;
//		int y = arr[i].second%n;
//		cout<<x<<" "<<y<<endl;
//	}
	for(i=4;i<n*n;i++)
	{
		int x = arr[i].second/n;
		int y = arr[i].second%n;
		update(x,y);
	}
	print();	
	vector<int> adj[n*n];
	int x=0;
	int y=0;
	for(x=0;x<n;x++)
	{
		for(y=0;y<n;y++)
		{
			if(x==0 && y==0)
			{
				adj[0].push_back(n);
				adj[0].push_back(1);
			}		
			else if(x==n-1 && y==0)
			{
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y+1);
			}
			else if(x==n-1 && y==n-1)
			{
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y-1);
			}	
			else if(x==0 && y==n-1)
			{
				adj[n*x+y].push_back(n*(x+1)+y);
				adj[n*x+y].push_back(n*x+y-1);
			}		
			else if(x==0)
			{
				adj[n*x+y].push_back(n*(x+1)+y);
				adj[n*x+y].push_back(n*x+y-1);
				adj[n*x+y].push_back(n*x+y+1);
			}			
			else if(y==0)
			{
				adj[n*x+y].push_back(n*(x+1)+y);
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y+1);
			}		
			else if(x==n-1)
			{
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y-1);
				adj[n*x+y].push_back(n*x+y+1);
			}		
			else if(y==n-1)
			{
				adj[n*x+y].push_back(n*(x+1)+y);
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y-1);
			}
			else
			{
				adj[n*x+y].push_back(n*x+y+1);
				adj[n*x+y].push_back(n*(x+1)+y);
				adj[n*x+y].push_back(n*(x-1)+y);
				adj[n*x+y].push_back(n*x+y-1);
			}
			
		}
	}
//	for(i=0;i<n*n;i++)
//	{
//		adj[i].push_back(0);
//	}
	stack<int> flood;
	
 	x=0;
	y=0;
	cout<<"Current Location: "<<x<<","<<y<<endl;
	while(1)
	{
//		cout<<"Number of open neighbours: "<<adj[n*x+y].size()<<endl;
		flood.push(n*x+y);
		if(x==n/2 && y==n/2)
		{
			break;
		}
		if(x==n/2 && y==n/2-1)
		{
			break;
		}
		if(x==n/2-1 && y==n/2)
		{
			break;
		}
		if(x==n/2-1 && y==n/2-1)
		{
			break;
		}
		cout<<"How many walls do you see now? ";
		int num;
		char c;
		cin>>num;
		int tmp[3]={0,0,0};
		while(num--)
		{
			cout<<"Where is the wall? ";
			cin>>c;
			if(c=='l')	tmp[0]=1;
			else if(c=='r')	tmp[1]=1;
			else if(c=='f')	tmp[2]=1;
		}
		if(tmp[0]==1)
		{
			int tempx= x - (direction-3)%2;
			int tempy= y + (direction-2)%2;
			for(i=0;i<adj[n*x+y].size();i++)
			{
				if(adj[n*x+y][i]==n*tempx+tempy)
				{
					adj[n*x+y].erase(adj[n*x+y].begin()+i);
					break;
				}
			}
			if(n*tempx+tempy>=0 && n*tempx+tempy<n*n)
			{
				for(i=0;i<adj[n*tempx+tempy].size();i++)
				{
					if(adj[n*tempx+tempy][i]==n*x+y)
					{
						adj[n*tempx+tempy].erase(adj[n*tempx+tempy].begin()+i);
						break;
					}
				}	
			}
			
			
//			it=adj[n*x+y].find(n*tempx+tempy);
//			adj[n*x+y].erase(it);
//			it=adj[n*tempx+tempy].find(n*x+y);
//			adj[n*tempx+tempy].erase(it);
//			adj[n*x+y].push_back(n*tempx+tempy);
//			adj[n*tempx+tempy].push_back(n*x+y);			
		}
		if(tmp[1]==1)
		{
			int tempx= x + (direction-3)%2;
			int tempy= y - (direction-2)%2;
			for(i=0;i<adj[n*x+y].size();i++)
			{
				if(adj[n*x+y][i]==n*tempx+tempy)
				{
					adj[n*x+y].erase(adj[n*x+y].begin()+i);
					break;
				}
			}
			if(n*tempx+tempy>=0 && n*tempx+tempy<n*n)
			{
				for(i=0;i<adj[n*tempx+tempy].size();i++)
				{
					if(adj[n*tempx+tempy][i]==n*x+y)
					{
						adj[n*tempx+tempy].erase(adj[n*tempx+tempy].begin()+i);
						break;
					}
				}	
			}	
		}
		if(tmp[2]==1)
		{
			int tempx= x - (direction-2)%2;
			int tempy= y - (direction-3)%2;
			for(i=0;i<adj[n*x+y].size();i++)
			{
				if(adj[n*x+y][i]==n*tempx+tempy)
				{
					adj[n*x+y].erase(adj[n*x+y].begin()+i);
					break;
				}
			}
			if(n*tempx+tempy>=0 && n*tempx+tempy<n*n)
			{
				for(i=0;i<adj[n*tempx+tempy].size();i++)
				{
					if(adj[n*tempx+tempy][i]==n*x+y)
					{
						adj[n*tempx+tempy].erase(adj[n*tempx+tempy].begin()+i);
						break;
					}
				}	
			}	
		}
		
		cout<<"Open Neighbours are: "<<endl;
		for(i=0;i<adj[n*x+y].size();i++)
		{
			cout<<adj[n*x+y][i]/n<<","<<adj[n*x+y][i]%n<<endl;
		}
		
		int temp;
		int neighbour;
		int dist;
		while(!flood.empty())
		{
			temp=flood.top();
			cout<<"Element on top: "<<temp/n<<","<<temp%n<<endl;
			flood.pop();
			neighbour=adj[temp][0];
			dist = a[neighbour/n][neighbour%n];
			for(i=1;i<adj[temp].size();i++)
			{
				if(dist > a[adj[temp][i]/n][adj[temp][i]%n])
				{
					neighbour=adj[temp][i];
					dist = a[neighbour/n][neighbour%n];
				}
			}
			cout<<"Minimum distance for "<<temp/n<<","<<temp%n<<" is: "<<dist<<endl;
			cout<<"Distance - 1 = "<<a[temp/n][temp%n]-1<<endl;
			if((a[temp/n][temp%n]-1)!=dist)
			{
				cout<<"They are not equal"<<endl;
				a[temp/n][temp%n]=dist+1;
				for(i=0;i<adj[temp].size();i++)
				{
					cout<<"Element being pushed: "<<(adj[temp][i])/n<<","<<(adj[temp][i])%n<<endl;
					flood.push(adj[temp][i]);
				}
			}
		}
		temp=n*x+y;
		neighbour=adj[temp][0];
		dist = a[neighbour/n][neighbour%n];
		for(i=1;i<adj[temp].size();i++)
		{
			if(dist > a[adj[temp][i]/n][adj[temp][i]%n])
			{
				neighbour=adj[temp][i];
				dist = a[neighbour/n][neighbour%n];
			}
		}
		int x1=neighbour/n;
		int y1=neighbour%n;
		if(x1==x+1 &&y1==y)
			direction=1;
		else if(x1==x &&y1==y+1)
			direction=2;
		else if(x1==x-1 &&y1==y)
			direction=3;
		else if(x1==x &&y1==y-1)
			direction=4;
		x=x1;
		y=y1;
		cout<<"Updated Distances: "<<endl;
		print();	
		cout<<"Bot's current location: "<<x<<","<<y<<endl;
		cout<<"Bot is facing ";
		if(direction==1)
			cout<<"North."<<endl;
		if(direction==2)
			cout<<"East."<<endl;
		if(direction==3)
			cout<<"South."<<endl;
		if(direction==4)
			cout<<"West."<<endl;
	}
}
