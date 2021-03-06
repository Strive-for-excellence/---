


#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define forn(i,n) for(int i = 0;i < n; ++i)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
struct Point
{
    double x,y;

    Point(double x = 0,double y = 0):x(x),y(y) {}

};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
    return Vector(A.x + B.x,A.y + B.y);
}
Vector operator - (Vector A,Vector B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator / (Vector A,double p)
{
    return Vector(A.x/p,A.y/p);
}
Vector operator * (Vector A,double p)
{
    return Vector(A.x*p,A.y*p);
}
double angle(Vector v)//求向量的角度从0到2*pi
{
    return atan2(v.y,v.x);
}
int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    else
        return x < 0?-1:1;
}
bool operator < (const Point &a,const Point &b)
{
    if(dcmp(a.x-b.x)==0)
        return a.y<b.y;
    else
        return a.x<b.x;
}


bool operator == (const Point &a,const Point &b)
{
    return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);
}
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(A.x*A.x+A.y*A.y);
}
double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Area2(Point A,Point B,Point C)
{
    return Cross(B-A,C-A);
}
Vector Rotate(Vector A,double rad)
{
    return Vector (A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A)//单位法线
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
//调用前确保直线有唯一交点，当且仅当Cross(v,w)非0
Point Get_Line_Intersection(Point P,Vector v,Point Q,Vector w)
{
    Vector u = P - Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double Distance_To_Line(Point P,Point A,Point B)//点到直线的距离
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)/Length(v1));
}
double Distance_To_Segment(Point P,Point A,Point B)
{
    if(A==B)
        return Length(P-A);
    Vector v1 = B-A,v2 = P-A,v3 = P-B;
    if(dcmp(Dot(v1,v2))<0)
        return Length(v1);
    else if(dcmp(Dot(v1,v3))>0)
        return Length(v3);
    else
        return fabs(Cross(v1,v2))/Length(v1);
}
Point Get_Line_Projection(Point P,Point A,Point B)//求投影点
{
    Vector v = B- A;
    return A + v*(Dot(v,P-A)/Dot(v,v));
}
//线段相交判定 相交不在线段的端点
bool Segment_Proper_Intersection(Point a1,Point a2,Point b1,Point b2)
{
    double c1 =  Cross(a2-a1,b1-a1),c2 = Cross(a2-a1,b2-a1),
           c3 =  Cross(b2-b1,a2-b1),c4 = Cross(b2-b1,a1-b1);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}
//判断点是否在线段上(不包括端点）
bool Onsegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}
const int maxn = 100+10;
Point P[maxn];
#define f(n,m) ((n%m+m)%m)
//bool vis[maxn];
bool OnLeft(Point P,Point a,Point b)
{
    return dcmp(Cross(a-b,P-a)) > 0;
}
int main(void)
{
    int n;
    while(cin>>n)
    {
        for(int i = 0; i < n; ++i)
            scanf("%lf%lf",&P[i].x,&P[i].y);
        P[n] = P[0];
        vector<Point> ans;
        vector<int>  next;
        int  Index = min_element(P,P+n)-P;
        Point NowPoint = P[Index];
        ans.push_back(Point(P[Index].x-1,P[Index].y));
        ans.push_back(P[Index]);
//        vis[Index] = true;
        next.push_back(f(Index-1,n));
        next.push_back(f(Index+1,n));
//        int cnt = 1;
        for(;;)
        {
//            if(cnt++>10000)
//                break;
            double  Min = pi;
            int NextPoint;
            for(int i = 0; i < next.size(); ++i)
            {
                double rad;
                rad = Angle(P[next[i]]-ans[ans.size()-1],ans[ans.size()-1]-ans[ans.size()-2]);
                if(OnLeft(P[next[i]],ans[ans.size()-1],ans[ans.size()-2]))
                    rad = -rad;
                if(rad <= Min)
                {
                    Min = rad;
                    NextPoint = next[i];
                }
            }
            next.clear();
            Min = 1;
            ans.push_back(P[NextPoint]);
            for(int i = 0; i < n; ++i)
            {
                if(Segment_Proper_Intersection(NowPoint,P[NextPoint],P[i],P[i+1]))
                {
                    Point Inter = Get_Line_Intersection(NowPoint,NowPoint-P[NextPoint],P[i],P[i+1]-P[i]);
                    double t = Length(Inter-NowPoint)/Length(P[NextPoint]-NowPoint);
                    if(dcmp(t-Min)==0)
                    {
                        next.push_back(i);
                        next.push_back(f(i+1,n));
                    }
                    if(dcmp(t-Min)<0)
                    {
                        Min = t;
                        next.clear();
                        next.push_back(i);
                        next.push_back(f(i+1,n));
                        *(--ans.end()) = Inter;
                    }
                }
            }
            if(next.empty())
            {
                next.push_back(f(NextPoint-1,n));
                next.push_back(f(NextPoint+1,n));
            }
            NowPoint = *(--ans.end());
            if(NowPoint==P[Index])
                break;
        }

        cout<<ans.size()-2<<endl;

        for(int i = ans.size()-1; i >= 2; --i)
            printf("%.4f %.4f\n",ans[i].x,ans[i].y);
    }


    return 0;
}

