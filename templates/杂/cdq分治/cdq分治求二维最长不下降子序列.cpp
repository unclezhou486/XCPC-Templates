#include <iostream>
#include <algorithm>

using namespace std;

const int N=1e5+10;

struct node{
	int id,x,y;
	int op;
}a[N],b[N],c[N];
int dp[N];

bool cmp(node a,node b){//sort by {x,y}
	if(a.x==b.x){
		if(a.y==b.y) return a.id<b.id;
		return a.y<b.y;
	}
	return a.x<b.x;
}

bool cmp1(node a,node b){//sort by id
	return a.id<b.id;
}

int n;

void cdq1(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	cdq1(mid+1,r);
	int pl=l,pr=mid+1;
	int mx=0;
	for(int i=l;i<=r;i++){
		if((pl<=mid&&b[pl].y<=b[pr].y)||pr>r){
			c[i]=b[pl];
			if(c[i].op==0){
				mx=max(mx,dp[c[i].id]);
			}
			pl++;
		}
		else{
			c[i]=b[pr];
			if(c[i].op==1){
				dp[c[i].id]=max(dp[c[i].id],mx+1);
			}
			pr++;
		}
	}
	for(int i=l;i<=r;i++){
		b[i]=c[i];
	}
}

void cdq(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);
	sort(a+l,a+mid+1,cmp);
	sort(a+mid+1,a+r+1,cmp);
	int pl=l,pr=mid+1;
	for(int i=l;i<=r;i++){
		if((pl<=mid&&a[pl].x<=a[pr].x)||pr>r){
			b[i]=a[pl];
			b[i].op=0;
			pl++;
		}
		else{
			b[i]=a[pr];
			b[i].op=1;
			pr++;
		}
	}
	cdq1(l,r);
	sort(a+mid+1,a+r+1,cmp1);
	cdq(mid+1,r);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].id=i;
		dp[i]=1;
	}
	cdq(1,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]);
	}
	cout<<ans<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}
