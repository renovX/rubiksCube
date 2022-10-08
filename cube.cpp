#include<bits/stdc++.h>
#include<typeinfo>
#define loop(i,a,x) for(int i=0;i<a;i++)
using namespace std;
void swap(vector<int> &a,vector<int >&b)
{
    for(int i=0;i<a.size();i++)
    {
        int t=a[i];
        a[i]=b[i];
        b[i]=t;
    }
}
void copyVec(vector<int>& a,vector<int >& b)
{
    for(int i=0;i<a.size();i++)a[i]=b[i];
}
class Face
{
    public:
        vector<vector<int>> squares;
        Face* top;
        Face* bottom;
        Face* left;
        Face* right;
        Face()
        {
            
            vector<int> nk(3,0);
            vector<vector<int>> nn(3,nk);
            squares=nn;
        }
        Face(int num)
        {
            vector<int> nk(3,num);
            vector<vector<int>> nn(3,nk);
            squares=nn;

        }
        Face(vector<vector<int>> sq)
        {
            squares=sq;
        }
        void setVal(vector<vector<int>> sq)
        {
            squares=sq;
        }

};
class Cube
{
    public:
    vector<Face> cube;
    Cube()
    {
        //cout<<"Constructed1";
        
        vector<Face> newcube;
        for(int i=1;i<=6;i++)
        {
            Face nf(i);
            nf.left=NULL;
            nf.right=NULL;
            newcube.push_back(nf);
        }
        for(int i=0;i<4;i++)
        {
            printf("\nOK");
            int l=i-1<0?3:i-1;
            int r=(i+1)%4;
            newcube[i].left=&newcube[l];
            newcube[i].right=&newcube[r];
        }
        cube=newcube;
        //cout<<"Constructed";
        
    }

    void constructCube(vector<vector<vector<int>>> input_cube)
    {
        //cube[1] will be the front
        
        
        Face *a,*b,*c,*d,*e,*tp,*bt;
        a=new Face(input_cube[0]);
        b=new Face(input_cube[1]);
        c=new Face(input_cube[2]);
        d=new Face(input_cube[3]);
        tp=new Face(input_cube[4]);
        bt=new Face(input_cube[5]);

        a->left=d;
        a->right=b;
        a->top=tp;
        a->bottom=bt;

        b->left=a;
        b->right=c;
        b->top=tp;
        b->bottom=bt;

        c->left=b;
        c->right=d;
        c->top=tp;
        c->bottom=bt;

        d->left=c;
        d->right=a;
        d->top=tp;
        c->bottom=bt;
        
        
        tp->left=a;
        tp->right=c;
        tp->bottom=b;
        tp->top=d;
    
        
        bt->left=a;
        bt->right=c;
        bt->bottom=d;
        bt->top=b;
        
        
        cube[0] = *a;
        cube[1]=*b;
        cube[2]=*c;
        cube[3]=*d;
        cube[4]=*tp;
        cube[5]=*bt;
    }
    void rotateRow(int row,int amount)
    {
        if(amount==1)
        {
            vector<int> temp(cube[3].squares[row]);
            for(int i=3;i>=1;i--)
            {
                vector<int> t=cube[i-1].squares[row];
                copyVec(cube[i].squares[row],cube[i-1].squares[row]);
                
            }
            cube[0].squares[row].assign(temp.begin(),temp.end());
        }
        else if(amount==-1)
        {
            vector<int> temp(cube[0].squares[row]);
            for(int i=0;i<3;i++)
            {
                vector<int> t=cube[i+1].squares[row];
                copyVec(cube[i].squares[row],cube[i+1].squares[row]);
                
            }
            cube[3].squares[row].assign(temp.begin(),temp.end());
        }
        else if(amount==2||amount==-2)
        {
            swap(cube[0].squares[row],cube[2].squares[0]);
            swap(cube[1].squares[row],cube[3].squares[row]);
        }

    }
    void rotateCol(int col,int amount)
    {
    if(amount==1)
        {
            Face* curr=&cube[1];
            //vector<int> temp(cube[3].squares[row]);
            
            printf("\n5");
            for(int i=0;i<4;i++)
            {
                vector<vector<int>> m1=curr->squares;
                vector<vector<int>> m2=(curr->top)->squares;
                for(int j=0;j<3;j++)m1[j][col]=m2[j][col];
                curr=curr->top;
            }

        }
        else if(amount==-1)
        {
            Face* curr=&cube[1];
            //vector<int> temp(cube[3].squares[row]);
            
            
            for(int i=0;i<4;i++)
            {
                vector<vector<int>> m1=curr->squares;
                vector<vector<int>> m2=(curr->bottom)->squares;
                
                for(int j=0;j<3;j++)m1[j][col]=m2[j][col];
                curr=curr->bottom;
            }

        }
        else if(amount==2||amount==-2)
        {
            Face* curr=&cube[1];
            //swapping face 1 with 4 and 5 with 6
            vector<vector<int>> m1=curr->squares;
            vector<vector<int>> m2=((curr->bottom)->bottom)->squares;
            vector<vector<int>> m3=(curr->top)->squares;
            vector<vector<int>> m4=(curr->bottom)->squares;
            for(int j=0;j<3;j++)
            {
                int t=m1[j][col];
                int x=m3[j][col];
                m1[j][col]=m2[j][col];
                m3[j][col]=m4[j][col];
                m2[j][col]=t;
                m4[j][col]=x;
            }


        }
    }
    void display()
    {
        
        for(int i=0;i<6;i++)
        {
            
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)cout<<cube[i].squares[j][k]<<" ";
                cout<<"\n";
            }
            cout<<"\n";
        }
       
    }

};
int main()
{
    
    Face ff;
    Cube c;
    //c.cube[i];
    c.display();
    //c.rotateCol(0,-1);
    printf("\n\n After rotation\n");
    c.display();
    //Face fk=*c.cube[2].left;
    //vector<vector<int>> m=fk->squares;
    //printf("%d",m[0][0]);
}