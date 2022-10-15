#include<bits/stdc++.h>
#include<typeinfo>
using namespace std;
class A
{
    public:
        int b;
        A* k;
        A()
        {
            b=6;
        }
        A(int n)
        {
            b=n;
        }
};
class B
{
    public:
        A* ref;
};

int main()
{
    //B obj;
    vector<int> a={1,2,3,4};
    vector<int> b=a;
    a[0]=3;
    
    A x;
    A y(10);
    A* z=&y;
    z->b=20;
    y.k=&x;
    x.k=&y;
    cout<<y.b;
    //cout<<y.k<<" "<<&x;
}