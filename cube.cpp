#include<bits/stdc++.h>
#include<typeinfo>
#define loop(i,a,x) for(int i=0;i<a;i++)
#define vv vector<vector<int>>
using namespace std;
void clrscr()
{
    //cout << "\033[2J\033[1;1H";
    system("clear");
    printf("\nCleared");
}
void swapCol(vv &a,vv &b,int col)
{
    for(int i=0;i<a.size();i++)
    {
        int t=a[i][col];
        a[i][col]=b[i][col];
        b[i][col]=t;
    }
}
void printMatrix(vv M)
{
    for(auto r:M)
    {
        printf("\n");
        for(auto c:r)
        {
            printf("%d ",c);

        }
        
    }
}
void swap(vector<int> &a,vector<int >&b)
{
    for(int i=0;i<a.size();i++)
    {
        int t=a[i];
        a[i]=b[i];
        b[i]=t;
    }
}
void copyCol(vv &a,vv &b,int col)
{
    for(int i=0;i<3;i++)
    {
        a[i][col]=b[i][col];
    }
}
void copyVec(vector<int>& a,vector<int >& b)
{
    for(int i=0;i<a.size();i++)a[i]=b[i];
}
class Face
{
    public:
        int val;
        vector<vector<int>> squares;
        Face* top;
        Face* bottom;
        Face* left;
        Face* right;
        Face()
        {
            
            val=0;
            vector<int> nk(3,0);
            vector<vector<int>> nn(3,nk);
            squares=nn;
        }
        Face(int num)
        {
            val=num;
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
        Face* front;
        Face* oppfront;
    Cube()
    {
        
        cube.clear();
        //Intitalizing all faces of cube
        for(int i=1;i<=6;i++)
        {
            Face nf(i);
            nf.left=NULL;
            nf.right=NULL;
            cube.push_back(nf);
        }
        //Below all are set with respect to cube[1] being the front
        //Setting left right, top down pointers of all front faces (0,1,2,3)
        for(int i=0;i<4;i++)
        {
            
            int l=i-1<0?3:i-1;
            int r=(i+1)%4;
        
            //cube[i].top=&cube[4];
            //cube[i].bottom=&cube[5];
            cube[i].left=&cube[l];
            
            cube[i].right=&cube[r];
        }
        cube[1].top=&cube[4];
        cube[3].top=&cube[5];
        cube[1].bottom=&cube[5];
        cube[3].bottom=&cube[4];
        //Setting left right, top down pointers of up and down faces (4,5)
        {
            cube[4].left=&cube[0];
            cube[4].right=&cube[2];
            cube[4].bottom=&cube[1];
            cube[4].top=&cube[3];
            
            cube[5].left=&cube[0];
            cube[5].right=&cube[2];
            cube[5].bottom=&cube[3];
            cube[5].top=&cube[1];

        }
        long s=cube[1].left->val;
        //cout<<"Constructed Cube";
        printf("\nsize%ld\n",s);
        front=&cube[1];
        oppfront=&cube[3];
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
            Face* next=front;
            vector<int> t=front->squares[row];
            
            copyVec(t, front->squares[row]);
            cout<<"\n"<<t[0];
            for(int i=1;i<=3;i++)
            {
                cout<<"\nIn";
                
                next->squares[row]=next->left->squares[row];
                cout<<"\n"<<next->squares[0][0]<<" "<<next->left->squares[0][0];
                next=next->left;
                
                
            }
            next->squares[row]=t;
        }
        else if(amount==-1)
        {
            vector<int> temp(front->squares[row]);
            Face* next=front;
            for(int i=0;i<3;i++)
            {
                next->squares[row]=next->right->squares[row];
                //vector<int> t=cube[i+1].squares[row];
                //copyVec(cube[i].squares[row],cube[i+1].squares[row]);
                next=next->right;
                
            }
            next->squares[row]=temp;   
        }
        else if(amount==2||amount==-2)
        {
            Face* f=front;
            
            swap(f->squares[row],(f->right)->right->squares[row]);
            swap(f->right->squares[row],f->left->squares[row]);
        }

    }
    void rotateCol(int col,int amount)
    {
        vector<vector<int>> t={{0,0,0},{0,0,0},{0,0,0}};
    if(amount==1)
        {
            Face* f=front;
            //vector<int> temp(cube[3].squares[row]);
            
            copyCol(t,front->squares,col);
            printf("\n%d",t[1][0]);
            
            for(int i=0;i<3;i++)
            {
                
                copyCol(f->squares,f->top->squares,col);
                
                f=f->top;
                
            }
            printf("\n%d",f->squares[2][2]);
            copyCol(f->squares,t,col);
        }
        else if(amount==-1)
        {
            Face* f=front;
            //vector<int> temp(cube[3].squares[row]);
            
            copyCol(t,front->squares,col);
            //printf("\n%d",t[1][0]);
            
            for(int i=0;i<3;i++)
            {
                
                copyCol(f->squares,f->bottom->squares,col);
                
                f=f->bottom;
                
            }
            //printf("\n%d",f->squares[2][2]);
            copyCol(f->squares,t,col);

        }
        else if(amount==2||amount==-2)
        {
            Face* f=front;
            
            swapCol(f->squares,(f->top)->top->squares,col);
            swapCol(f->top->squares,f->bottom->squares,col);

        }
    }
    void turn(char c,int val)
    {
        if(c=='r')
        {
            Face* prev=front;
            if(val==1)
            {
                front=front->left;
                oppfront=oppfront->left;
            }
            else if(val==-1)
            {
                front=front->right;
                oppfront=oppfront->right;
            }
            else if(val==2)
            {
                Face* t=front;
                front=oppfront;
                oppfront=t;
            }
            else
            {
                printf("\nInvalid");
                return;
            }
                
                
                front->top=prev->top;
                front->bottom=prev->bottom;

                oppfront->top=prev->bottom;
                oppfront->bottom=prev->top;
                
                front->top->bottom=front;
                front->bottom->top=front;
                
                (front->top)->top=oppfront;
                (front->bottom)->bottom=oppfront;

                
                
            
        }
        else if(c=='c')
        {
            Face* prev=front;
            if(val==1)
            {
                front=front->top;
                oppfront=oppfront->top;
            }
            else if(val==-1)
            {
                front=front->bottom;
                oppfront=oppfront->bottom;
            }
            else if(val==2)
            {
                Face* t=front;
                front=oppfront;
                oppfront=t;
            }
            else
            {
                printf("\nInvalid");
                return;
            }
            front->left=prev->left;
            front->right=prev->right;

            oppfront->left=prev->right;
            oppfront->right=prev->left;

            front->left->right=front;
            front->right->left=front;

            (front->left)->left=oppfront;
            (front->right)->right=oppfront;

        }
    }
    void display()
    {
        
        /*cout<<"\n\nAcross";
        Face* curr=front;
        for(int i=0;i<4;i++)
        {
            printMatrix(curr->squares);
            printf("\n");
            curr=curr->right;
            
        }
        cout<<"\n\nTop";
        printMatrix(front->top->squares);

        cout<<"\n\nBottom";
        printMatrix(front->bottom->squares);*/
        printMatrix(front->squares);
            
       
    }

};
int main()
{
    
    Face ff;
    Cube c;
    //c.cube[i];
    c.display();
    //c.rotateRow(0,2);
    //c.rotateCol(0,2);
    c.turn('c',-1);
    cout<<endl;
    clrscr();
    printf("\n\n After rotation\n");
    c.display();
    //cout<<"\n\n"<<c->
    //Face fk=c.cube[1];
    //int k=1;
    //vector<vector<int>> m=fk->squares;
    //if(fk.left==NULL)
    //cout<<c.cube[0].right->squares[0][0];
    //printf("%ld",(c.cube[1].left));
}