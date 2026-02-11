//
// Created by A on 11/11/2025.
//
#include "myheader.h"

void printZarb(int x, int y)
{
    cout<<zarb(x,y)<<endl;
}

int zarb(int x, int y)
{
    return x*y;
}

bool isPrime(long long n)
{
    long long c=0, U;
    U=sqrt(n);
    for(long long i=2; (i<=U)&&(c==0); i++)
    {
        if(n%i==0)
        {
            c++;
        }
    }
    return c==0;
}

int series01(unsigned n)
{
    int s=0;
    for(int i=1; i<=n; i++)
        s+=i;
    return s;
}

double series02(unsigned n)
{
    double s=0;
    for(int i=1; i<=n; i++)
        s+=1.0/i;
    return s;
}

double series03(unsigned n)
{
    double s=0, a=1;
    unsigned m=2*n-1;
    for(int i=1; i<=m; i+=2)
    {
        s+=a/i;
        a=-a;
    }

    return s;
}

double series04(double x, unsigned n)
{
    double s=0, a=x;
    unsigned m=2*n-1;
    for(int i=1; i<=m; i+=2)
    {
        s+=a/i;
        a*=-x*x;
    }

    return s;
}

double series05(unsigned n)
{
    double s=1, d=1;
    for(int i=1; i<n; i++)
    {
        d*=i;
        s+=1/d;
    }

    return s;
}

double series06(double x, unsigned n)
{
    double s=0, a=x, d=1;
    unsigned m=2*n-1;
    for(int i=1; i<=m; i+=2)
    {
        s+=a/d;
        a*=-x*x;
        d*=(i+1)*(i+2);
    }

    return s;
}


double mySqrt(double x)
{
    double t1=1, t2=0, err=1;
    //int c=0;
    while(err>1e-10)
    {
        t2=(t1+x/t1)/2;
        err=abs(t2-t1);
        t1=t2;
        //c++;
    }
    //cout<<c<<endl;
    return t1;
}

unsigned fibonacci(unsigned n)
{
    unsigned a=1,b=1,c=1;
    for(int i=0; i<int(n-2);i++)
    {
        c=a+b;
        b=a;
        a=c;
    }
    return c;
}

unsigned gcd(unsigned a, unsigned b)
{
    unsigned c;
    do{
        c=a%b;
        a=b;
        b=c;
    }while(c!=0);
    return a;
}

unsigned lcm(unsigned a, unsigned b)
{
    return a*b/gcd(a,b);
}

bool isArmstrong(unsigned n)
{
    unsigned s=0, m=n;
    while(m>0)
    {
        unsigned d=m%10;
        s+=d*d*d;
        m/=10;
    }
    return n==s;
}

void drawing01(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=i; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
}

void drawing02(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<n-i; j++)
            cout<<" ";
        for(int j=1; j<=2*i-1; j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
}

void numbers01(int n)
{
    for(int i=1; i<=n; i++)
    {
        int k=i;
        for(int j=0; j<n; j++)
        {
            cout<<left<<setw(4)<<k++;
        }
        cout<<endl;
    }
}

void numbers02(int n)
{
    int k=1;
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<left<<setw(4)<<k++;
        }
        cout<<endl;
    }
}

void numbers03(int n)
{
    for(int i=1; i<=n; i++)
    {
        int k=i;
        for(int j=0; j<n; j++)
        {
            cout<<left<<setw(4)<<k;
            k+=n;
        }
        cout<<endl;
    }
}

void numbers04(int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cout<<left<<setw(4)<<i*j;
        }
        cout<<endl;
    }
}

int findMax(const int a[], int size)
{
    //return max index
    int m=0;
    for(int i=1; i<size; i++)
    {
        if(a[i]>a[m])
            m=i;
        //a[i]=0;
    }

    return m;
}

void bubbleSort(int a[], int size)
{
    bool changed=true;
    for(int i=size-1; (i>0)&&(changed); i--)
    {
        changed = false;
        for(int j=0; j<i; j++)
            if(a[j]>a[j+1])
            {
                changed = true;
                swap(a[j],a[j+1]);
            }

    }
}

int findSecondRank(int a[], int size)
{
    int r1=0, r2=1;
    for(int i=1; i<size; i++)
    {
        if(a[i]>a[r1])
        {
            r2=r1;
            r1=i;
        }
        else if(a[i]>a[r2])
        {
            r2=i;
        }
    }
    return r2;
}

int gameState(int G[3][3])
{
    for(int i=0; i<3; i++)
        if((G[i][0]==G[i][1])&&(G[i][1]==G[i][2])&&(G[i][0]!=0))
            return G[i][0];
    for(int j=0; j<3; j++)
        if((G[0][j]==G[1][j])&&(G[1][j]==G[2][j])&&(G[0][j]!=0))
            return G[0][j];
    if((G[0][0]==G[1][1])&&(G[1][1]==G[2][2])&&(G[0][0]!=0))
        return G[0][0];
    if((G[0][2]==G[1][1])&&(G[1][1]==G[2][0])&&(G[0][2]!=0))
        return G[0][2];
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(G[i][j]==0)
                return 0;   //Not finished yet
    return 3;   //Tie
}

int binarySearch(int x, int a[], int n)
{
    int left=0, right=n-1, mid;
    while(left<right)
    {
        mid=(left+right)/2;
        if(a[mid]==x)
        {
            return mid;
        }
        else if(a[mid]>x)
        {
            right=mid-1;
        }
        else
        {
            left=mid+1;
        }
    }
    if(a[left]==x)
        return left;
    if(a[right]==x)
        return right;
    return -1;
}

void printStudent(const Student &s)
{
    cout<<s.name<<" "<<s.family<<",NC: "<<s.nCode<<", Student Number: "<<s.stNum<<", GPA = "<<s.GPA<<endl;
}

string strTrim(const string &s)
{
    string R=" \t";
    size_t i=s.find_first_not_of(R);
    size_t j=s.find_last_not_of(R);
    if(j>=i)
        return s.substr(i,j-i+1);
    return "";
}

bool cmpInt(int i, int j)
{
    return i>=j;
}

bool cmpStudentGPA(const Student &s1, const Student &s2)
{
    if(s1.GPA==s2.GPA)
        return s1.stNum<s2.stNum;
    return s1.GPA>s2.GPA;
}