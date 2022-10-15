#include<bits/stdc++.h>
#include"cube.h"
Cube::Cube rcube;
void start()
{
    std::string input;
    while(true)
    {

        std::cout<<std:: endl;
        Cube::clrscr();
        //std::cout<<input;
        rcube.display();
        std::cout<<"\n\nin: ";
        std::cin>>input;
        try
            {
                if(input[0]=='r')
                {
                    printf("\nOK");
                    std::cout<<"\n"<<input[3];
                    if(input.size()<4)throw 1;
                    char rc=input[1];
                    int in,amt;
                    in=(int)input[2]-48;
                    if(input[3]=='-')
                    {
                        
                        amt=-((int)input[4]-48);
                    }
                    else 
                    {
                        
                        amt=(int)(input[3])-48;
                    }

                    if(rc=='r')
                    {
                        rcube.rotateRow(in,amt);
                    }
                    else if(rc=='c')
                    {
                        rcube.rotateCol(in,amt);
                    }
                    else throw 1;

                }
                else if(input[0]=='t')
                {
                    std::cout<<"\nIn";
                    if(input.size()<3)throw 1;
                    char dir=input[1];
                    int amt;
                    if(input[2]=='-')amt=-((int)(input[3])-48);
                    else amt=(int)(input[2])-48;
                    if(dir=='r')
                    {
                        rcube.turn2(dir,amt);
                    }
                    else if(dir=='c')
                    {
                        rcube.turn2(dir,amt);
                    }
                    else 
                    {
                        std::cout<<"\nDir is"<<dir;
                        throw 1;
                    }

                }
                else if(input=="exit")
                {
                    return;
                }
                else throw 1;
            }
            catch(int x)
            {
                std:: string cos;
                std::cout<<"\nInvalid Input\n";
                std::cin>>cos;
                continue;
            }

    }
}
int main()
{
    
    start();
}