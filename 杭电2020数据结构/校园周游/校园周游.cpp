#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i,a,n) for(int i=a;i<=n;++i)
typedef vector<int> VI;
const int N=20;
VI g[N],w[N];//g[i]��ʾi�����ڵĵ㼯,w[i]��ʾi�����ڵı�Ȩ 
string s[N];//s[i]��ʾ��i������Ľ���
bool vis[N];//ĳ�����Ƿ����� 
vector<VI> plan;//���ܷ���
VI tmp(N);//�浥������ tmp[0]��÷�����·���ܳ� tmp[0]��÷��������ľ��������������㣩 
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
	//�ȴӵ�ͼ�ļ�����ͼ����Ϣ 
	freopen("place.in","r",stdin);
	int n,m;//n���� m���� 
	cin>>n>>m;
	rep(i,1,n)cin>>s[i];
	int u,v,ww;//�ߵ����˵㼰��Ȩ 
	rep(i,1,m)
	{
		scanf("%d<->%d=%d",&u,&v,&ww);
		g[u].pb(v);
		g[v].pb(u);
		w[u].pb(ww);
		w[v].pb(ww);
	}
	//����ͼ�������û����� 
	freopen("CON", "r", stdin);
	cout<<" ��ӭ�������磬Ŀǰ���ں�����ţ�"<<endl;
	cout<<" ����ı��Ϊ 1-"<<n<<" ��������ŵı��Ϊ1��"<<endl;
	int now=1;//�û�Ŀǰ��λ�á� 
	int op,a;
	while(cout<<" 1.��ѯĳ�������Ϣ 2.��ѯǰ��ĳ�����·����ǰ�� 3.�˳�ϵͳ"<<endl<<" �����룺",cin>>op)
	{
		if(op==1)cout<<" ������Ҫ��ѯ�ľ����ţ�",cin>>a,a>=1&&a<=n?cout<<" "<<s[a]<<endl:cout<<" ��Ч������"<<endl;
		else if(op==3)return cout<<" ллʹ�ã��ټ���",0; 
		else if(op!=2)cout<<" ��Ч������"<<endl; 
		else
		{
			cout<<" ��Ŀǰ�ڱ��Ϊ��"<<now<<" �ľ��㣬����ǰ���ĸ���ŵľ��㣺",cin>>a;
			if(a<1||a>n)
			{
				cout<<" ��Ч������"<<endl;
				continue;
			}
			if(a==now)
			{
				cout<<" ��ɹ���ԭ��ת��һȦ��"<<endl;
				continue; 
			}
			plan.clear();
			vis[now]=1;
			dfs(now,a,2,0);
			vis[now]=0;
			cout<<" ����"<<plan.size()<<" �ַ�����"<<endl; 
			rep(i,0,plan.size()-1)
			{
				cout<<" "<<i+1<<".·���ܳ�Ϊ "<<plan[i][0]<<" ��"<<now; 
				rep(j,2,plan[i][1])cout<<"->"<<plan[i][j];
				cout<<endl;
			}
			int minn=0;
			rep(i,1,plan.size()-1)if(plan[minn][0]>plan[i][0])minn=i;
			cout<<" �������·������Ϊ "<<plan[minn][0]<<" ��"<<now;
			rep(i,2,plan[minn][1])cout<<"->"<<plan[minn][i];
			cout<<endl<<" �����������˱��Ϊ "<<a<<" �ľ��㡣"<<endl;
			now=a;
		}
	}
    return 0;
}
