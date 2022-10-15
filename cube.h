#include<bits/stdc++.h>
#include<typeinfo>
#define loop(i,a,x) for(int i=0;i<a;i++)
#define vv std::vector<std::vector<int>>
namespace Cube
{
void clrscr()
{
   
    system("clear");
    
}
void transpose(vv &a)
{
    for(int i=0;i<3;i++)
    {
        for(int j=i;j<3;j++)
        {
            int t=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=t;
        }
    }
}
void swapCol(vv &a,vv &b,int col1,int col2)
{
    for(int i=0;i<a.size();i++)
    {
        int t=a[i][col1];
        a[i][col1]=b[i][col2];
        b[i][col2]=t;
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
void swap(std::vector<int> &a,std::vector<int >&b)
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
void copyVec(std::vector<int>& a,std::vector<int >& b)
{
    for(int i=0;i<a.size();i++)a[i]=b[i];
}
class Face
{
    public:
        int val;
        std::vector<std::vector<int>> squares;
        Face* top;
        Face* bottom;
        Face* left;
        Face* right;
        Face()
        {
            
            val=0;
            std::vector<int> nk(3,0);
            std::vector<std::vector<int>> nn(3,nk);
            squares=nn;
        }
        Face(int num)
        {
            val=num;
            std::vector<int> nk(3,num);
            std::vector<std::vector<int>> nn(3,nk);
            squares=nn;

        }
        Face(std::vector<std::vector<int>> sq)
        {
            squares=sq;
        }
        void setVal(std::vector<std::vector<int>> sq)
        {
            squares=sq;
        }

};
class Cube
{
    public:
        std::vector<Face> cube;
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
        
        
        front=&cube[1];
        oppfront=&cube[3];
    }

    void constructCube(std::vector<std::vector<std::vector<int>>> input_cube)
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
            std::vector<int> temp(cube[3].squares[row]);
            Face* next=front;
            std::vector<int> t=front->squares[row];
            
            copyVec(t, front->squares[row]);
            
            for(int i=1;i<=3;i++)
            {
                
                
                next->squares[row]=next->left->squares[row];
                next=next->left;
                
                
            }
            next->squares[row]=t;

            //rotating top and bottom faces
            if(row==0)
            {
                // take tronspose of top and then reverse first and last row 

                   transpose(front->top->squares);
                    swap(front->top->squares[0],front->top->squares[2]);

            }
            else if(row==2)
            {
                transpose(front->top->squares);
                swapCol(front->bottom->squares,front->bottom->squares,0,2);
            }
            
        }
        else if(amount==-1)
        {
            std::vector<int> temp(front->squares[row]);
            Face* next=front;
            for(int i=0;i<3;i++)
            {
                next->squares[row]=next->right->squares[row];
                //std::vector<int> t=cube[i+1].squares[row];
                //copyVec(cube[i].squares[row],cube[i+1].squares[row]);
                next=next->right;
                
            }
            next->squares[row]=temp;  
            if(row==0)
            {
                // take tronspose of top and then reverse first and last row 
                transpose(front->top->squares);
                swapCol(front->top->squares,front->top->squares,0,2);
                

            }
            else if(row==2)
            {
                transpose(front->bottom->squares);
                swap(front->bottom->squares[0],front->bottom->squares[2]);
            } 
        }
        else if(amount==2||amount==-2)
        {
            Face* f=front;
            
            swap(f->squares[row],(f->right)->right->squares[row]);
            swap(f->right->squares[row],f->left->squares[row]);
            //rotating top and bottom face
            if(row==0)
            {
                // swap rows then columns

                   
                    swap(front->top->squares[0],front->top->squares[2]);
                    swapCol(front->top->squares,front->top->squares,0,2);

            }
            else if(row==2)
            {
                swap(front->bottom->squares[0],front->bottom->squares[2]);
                    swapCol(front->bottom->squares,front->bottom->squares,0,2);
            }
            
        }
       
       

    }
    void rotateCol(int col,int amount)
    {
        std::vector<std::vector<int>> t={{0,0,0},{0,0,0},{0,0,0}};
    if(amount==1)
        {
            Face* f=front;
            //std::vector<int> temp(cube[3].squares[row]);
            
            copyCol(t,front->squares,col);
            
            
            for(int i=0;i<3;i++)
            {
                
                copyCol(f->squares,f->top->squares,col);
                
                f=f->top;
                
            }
            
            copyCol(f->squares,t,col);
            //rotating left and right faces
            if(col==0)
            {
                // take tronspose of top and then reverse first and last row 
                transpose(front->left->squares);
                swapCol(front->left->squares,front->left->squares,0,2);
                

            }
            else if(col==2)
            {
                transpose(front->right->squares);
                swap(front->right->squares[0],front->right->squares[2]);
            } 
        }
        else if(amount==-1)
        {
            Face* f=front;
            //std::vector<int> temp(cube[3].squares[row]);
            
            copyCol(t,front->squares,col);
            //printf("\n%d",t[1][0]);
            
            for(int i=0;i<3;i++)
            {
                
                copyCol(f->squares,f->bottom->squares,col);
                
                f=f->bottom;
                
            }
            //printf("\n%d",f->squares[2][2]);
            copyCol(f->squares,t,col);

            if(col==0)
            {
                transpose(front->left->squares);
                swap(front->left->squares[0],front->left->squares[2]);
                
                

            }
            else if(col==2)
            {
                // take tronspose of top and then reverse first and last row 
                transpose(front->right->squares);
                swapCol(front->right->squares,front->right->squares,0,2);
            }

        }
        else if(amount==2||amount==-2)
        {
            Face* f=front;
            
            swapCol(f->squares,(f->top)->top->squares,col,col);
            swapCol(f->top->squares,f->bottom->squares,col,col);

                        //rotating top and bottom face
            if(col==0)
            {
                // swap rows then columns

                   
                    swap(front->left->squares[0],front->left->squares[2]);
                    swapCol(front->left->squares,front->left->squares,0,2);

            }
            else if(col==2)
            {
                swap(front->right->squares[0],front->right->squares[2]);
                    swapCol(front->right->squares,front->right->squares,0,2);
            }

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
    void turn2(char c,int val)
    {
        
        if(c=='r')
        {
            
            if(val==1)
            {
                rotateRow(0,1);
                rotateRow(1,1);
                rotateRow(2,1);
                //front=front->left;
            }
            else if(val==-1)
            
            {
                rotateRow(0,-1);
                rotateRow(1,-1);
                rotateRow(2,-1);
                //front=front->right;
            }
            else if(val==2||val==-2)
            {
                rotateRow(0,2);
                rotateRow(1,2);
                rotateRow(2,2);
                //front=front->right->right;
            }
            /*Face* prev=front;
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
            (front->right)->right=oppfront;*/

        }
        else if(c=='c')
        {
            
        
            if(val==1)
            {
                rotateCol(0,1);
                rotateCol(1,1);
                rotateCol(2,1);
                
            }
            else if(val==-1)
            
            {
                rotateCol(0,-1);
                rotateCol(1,-1);
                rotateCol(2,-1);
                
            }
            else if(val==2||val==-2)
            {
                rotateCol(0,2);
                rotateCol(1,2);
                rotateCol(2,2);
                
            }
            /*Face* prev=front;
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
            (front->right)->right=oppfront;*/

        }
    }
    void display()
    {
        printMatrix(front->squares);
        /*std::cout<<"\n\nAcross";
        Face* curr=front;
        for(int i=0;i<4;i++)
        {
            printMatrix(curr->squares);
            printf("\n");
            curr=curr->right;
            
        }
        std::cout<<"\n\nTop";
        printMatrix(front->top->squares);

        std::cout<<"\n\nBottom";
        printMatrix(front->bottom->squares);
            */
       
    }

};
}