#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i,a,n) for(int i=a;i<=n;++i)
typedef vector<int> VI;
const int N=20;
VI g[N],w[N];//g[i]表示i点相邻的点集,w[i]表示i点相邻的边权 
string s[N];//s[i]表示第i个景点的介绍
bool vis[N];//某个点是否来过 
vector<VI> plan;//存总方案
VI tmp(N);//存单个方案 tmp[0]存该方案的路径总长 tmp[0]存该方案经过的景点个数（包含起点） 
void dfs(int now,int target,int pace,int sum)
{
	if(now==target)
	{
		tmp[0]=sum;
		tmp[1]=pace-1;
		plan.pb(tmp);
		return;
	}
	rep(i,0,g[now].size()-1)
	{
		int to=g[now][i],ww=w[now][i];
		if(vis[to])continue;
		tmp[pace]=to; 
		vis[to]=1;
		dfs(to,target,pace+1,sum+ww);
		vis[to]=0; 
	 } 
} 
int main()
{
	//先从地图文件读入图的信息 
	freopen("place.in","r",stdin);
	int n,m;//n点数 m边数 
	cin>>n>>m;
	rep(i,1,n)cin>>s[i];
	int u,v,ww;//边的两端点及边权 
	rep(i,1,m)
	{
		scanf("%d<->%d=%d",&u,&v,&ww);
		g[u].pb(v);
		g[v].pb(u);
		w[u].pb(ww);
		w[v].pb(ww);
	}
	//存完图，进入用户界面 
	freopen("CON", "r", stdin);
	cout<<" 欢迎来到杭电，目前您在杭电大门！"<<endl;
	cout<<" 景点的编号为 1-"<<n<<" ，杭电大门的编号为1。"<<endl;
	int now=1;//用户目前的位置。 
	int op,a;
	while(cout<<" 1.查询某景点的信息 2.查询前往某景点的路径并前往 3.退出系统"<<endl<<" 请输入：",cin>>op)
	{
		if(op==1)cout<<" 请输入要查询的景点编号：",cin>>a,a>=1&&a<=n?cout<<" "<<s[a]<<endl:cout<<" 无效操作！"<<endl;
		else if(op==3)return cout<<" 谢谢使用，再见！",0; 
		else if(op!=2)cout<<" 无效操作！"<<endl; 
		else
		{
			cout<<" 您目前在编号为："<<now<<" 的景点，您想前往哪个编号的景点：",cin>>a;
			if(a<1||a>n)
			{
				cout<<" 无效操作！"<<endl;
				continue;
			}
			if(a==now)
			{
				cout<<" 你成功在原地转了一圈！"<<endl;
				continue; 
			}
			plan.clear();
			vis[now]=1;
			dfs(now,a,2,0);
			vis[now]=0;
			cout<<" 共有"<<plan.size()<<" 种方案："<<endl; 
			rep(i,0,plan.size()-1)
			{
				cout<<" "<<i+1<<".路径总长为 "<<plan[i][0]<<" ："<<now; 
				rep(j,2,plan[i][1])cout<<"->"<<plan[i][j];
				cout<<endl;
			}
			int minn=0;
			rep(i,1,plan.size()-1)if(plan[minn][0]>plan[i][0])minn=i;
			cout<<" 其中最短路径长度为 "<<plan[minn][0]<<" ："<<now;
			rep(i,2,plan[minn][1])cout<<"->"<<plan[minn][i];
			cout<<endl<<" 您现在来到了编号为 "<<a<<" 的景点。"<<endl;
			now=a;
		}
	}
    return 0;
}
