//
//  main.cpp
//  pr1
//  Copyright © 2018 Murat Kacmaz. All rights reserved.
//  150140052

#include <iostream>
#include <queue>
#include <stdio.h>
#include <stack>
#include <list>
#include <ctime>
#include <chrono>

using namespace std;

class Board{
public:
    int heuristic,layer,total,heuristic2;
    vector <vector<int>> currentBoard;
    Board* parent;
    Board(){parent = NULL; heuristic = 0;layer =0;total = 0;heuristic2 = 1; }
    Board(const Board& b1){ parent = NULL ; currentBoard = b1.currentBoard ; heuristic = 0; layer =b1.layer; total = b1.total ; heuristic2=1;}
};

int  printBoard(Board& array)
{ int counter = 0 ;
    
    for(int i = 0 ; i<7;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(array.currentBoard[i][j] == 0){
                cout << "   ";
                
            }
            else if(array.currentBoard[i][j] == 1)
            {   counter ++;
                cout << " . ";
            }
            else if(array.currentBoard[i][j] == 2)
            {
                cout << " o ";
            }
            else if(array.currentBoard[i][j] == 3)
            {   counter++;
                cout << " * ";
            }
            
        }
        cout << endl ;
    }
    cout << endl << endl ;
    return counter ;
}

bool finalBoard(Board& temp)
{
    // hic hamle kalmadıysa bitmistir
    for(int i = 0 ; i<7;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(temp.currentBoard[i][j] == 2)
            {
                if(i>=2) // uste bak
                {
                    if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                    {
                        
                        return false ;
                    }
                }
                if (i<=4) // asagı bak
                {
                    if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                    {
                        return false ;
                    }
                }
                
                if (j<=4) // saga bak
                {
                    if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                    {
                        return false ;
                    }
                }
                if(j>=2 ) // sola bak
                {
                    if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                    {
                        return false ;
                    }
                }
            }
        }
    }
    return true ;
}

void cleanStars(Board&temp)
{
    for(int i = 0 ; i<7;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(temp.currentBoard[i][j] == 3)
            {
                temp.currentBoard[i][j] =1;
            }
        }
    }
}

void BFS(Board& array){
    queue<Board> q;
    int br1 =0;
    int br2 =0;
    int generated = 0;
    int expanded= 0  ;
    int totalPegs = 0;
    int maxSize = 0 ;
    q.push(array);
    generated++;
    while(1)
    {
        Board temp = q.front();
        q.pop();
        expanded++;
        cleanStars(temp);
        for(int i = 0 ; i<7;i++)
        {
            for(int j=0;j<7;j++)
            {
                if(temp.currentBoard[i][j] == 2)
                {
                    if(i>=2) // uste bak
                    {
                        if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                        {
                            Board temp1 = temp;
                            temp1.currentBoard[i-2][j]=2 ;
                            temp1.currentBoard[i-1][j]=2 ;
                            temp1.currentBoard[i][j]=1 ;
                            temp1.parent = &temp;
                            q.push(temp1);
                            generated++;
                            if(q.size()>maxSize){maxSize=q.size(); }
                            if(finalBoard(temp1) == true)
                            {totalPegs = printBoard(temp1);br1 = 1;  break ;}
                        }
                    }
                    if (i<=4) // asagı bak
                    {
                        if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                        {
                            Board& temp2 = temp;
                            temp2.currentBoard[i+2][j]=2 ;
                            temp2.currentBoard[i+1][j]=2 ;
                            temp2.currentBoard[i][j]=1 ;
                            q.push(temp2);
                            temp2.parent = &temp;
                            generated++;
                            if(q.size()>maxSize){maxSize=q.size(); }
                            if(finalBoard(temp2) == true)
                            {totalPegs = printBoard(temp2); br1 = 1;   break ;}
                        }
                    }
                    
                    if (j<=4) // saga bak
                    {
                        if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                        {
                            Board temp3 = temp;
                            temp3.currentBoard[i][j+2]=2 ;
                            temp3.currentBoard[i][j+1]=2 ;
                            temp3.currentBoard[i][j]=1 ;
                            q.push(temp3);
                            temp3.parent = &temp;
                            generated++;
                            if(q.size()>maxSize){maxSize=q.size(); }
                            if(finalBoard(temp3) == true)
                            {totalPegs = printBoard(temp3); br1 = 1; break ;}
                        }
                    }
                    if(j>=2 ) // sola bak
                    {
                        if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                        {
                            Board& temp4 = temp;
                            temp4.currentBoard[i][j-2]=2 ;
                            temp4.currentBoard[i][j-1]=2 ;
                            temp4.currentBoard[i][j]=1 ;
                            q.push(temp4);
                            temp4.parent = &temp;
                            generated++;
                            if(q.size()>maxSize){maxSize=q.size(); }
                            if(finalBoard(temp4) == true)
                            {totalPegs = printBoard(temp4);br1 = 1;   break ;}
                        }
                    }
                }
            }
            if (br1 ==  1){br2 = 1 ; break ;}
        }
        if(br2==1) { break;}
    } // while bitisi
    cout << "Algorithm : BFS" << endl ;
    cout << "Number of generated nodes : "<< generated << endl ;
    cout << "Number of expanded nodes : " << expanded << endl ;
    cout << "Maximum number of nodes kept in memory : " << maxSize << endl ;
    cout << "Total number of pegs left : " << totalPegs << endl;
    

}


void DFS(Board& array){
    stack<Board> s;
    int br1 =0;
    int br2 =0;
    int generated = 0;
    int expanded= 0  ;
    int totalPegs = 0;
    int maxSize = 0 ;
    s.push(array);
    generated++;
    while(1)
    {
        Board temp = s.top();
        s.pop();
        expanded++;
        cleanStars(temp);
        for(int i = 0 ; i<7;i++)
        {
            for(int j=0;j<7;j++)
            {
                if(temp.currentBoard[i][j] == 2)
                {
                    if(i>=2) // uste bak
                    {
                        if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                        {
                            Board temp1 = temp;
                            temp1.currentBoard[i-2][j]=2 ;
                            temp1.currentBoard[i-1][j]=2 ;
                            temp1.currentBoard[i][j]=1 ;
                            temp1.parent = &temp;
                            s.push(temp1);
                            generated++;
                            if(s.size()>maxSize){maxSize=s.size(); }
                            if(finalBoard(temp1) == true)
                            {totalPegs = printBoard(temp1);br1 = 1;  break ;}
                        }
                    }
                    if (i<=4) // asagı bak
                    {
                        if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                        {
                            Board temp2 = temp;
                            temp2.currentBoard[i+2][j]=2 ;
                            temp2.currentBoard[i+1][j]=2 ;
                            temp2.currentBoard[i][j]=1 ;
                            s.push(temp2);
                            temp2.parent = &temp;
                            generated++;
                            if(s.size()>maxSize){maxSize=s.size(); }
                            if(finalBoard(temp2) == true)
                            {totalPegs = printBoard(temp2); br1 = 1;   break ;}
                        }
                    }
                    
                    if (j<=4) // saga bak
                    {
                        if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                        {
                            Board temp3 = temp;
                            temp3.currentBoard[i][j+2]=2 ;
                            temp3.currentBoard[i][j+1]=2 ;
                            temp3.currentBoard[i][j]=1 ;
                            s.push(temp3);
                            temp3.parent = &temp;
                            generated++;
                            if(s.size()>maxSize){maxSize=s.size(); }
                            if(finalBoard(temp3) == true)
                            {totalPegs = printBoard(temp3); br1 = 1; break ;}
                        }
                    }
                    if(j>=2 ) // sola bak
                    {
                        if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                        {
                            Board temp4 = temp;
                            temp4.currentBoard[i][j-2]=2 ;
                            temp4.currentBoard[i][j-1]=2 ;
                            temp4.currentBoard[i][j]=1 ;
                            s.push(temp4);
                            temp4.parent = &temp;
                            generated++;
                            if(s.size()>maxSize){maxSize=s.size(); }
                            if(finalBoard(temp4) == true)
                            {totalPegs = printBoard(temp4);br1 = 1;   break ;}
                        }
                    }
                }
            }
            if (br1 ==  1){br2 = 1 ; break ;}
        }
        if(br2==1) { break;}
    } // while bitisi
    cout << "Algorithm : DFS" << endl ;
    cout << "Number of generated nodes : "<< generated << endl ;
    cout << "Number of expanded nodes : " << expanded << endl ;
    cout << "Maximum number of nodes kept in memory : " << maxSize << endl ;
    cout << "Total number of pegs left : " << totalPegs << endl;
    
    
}
int  findHeuristic (Board& temp)
{ // toplam yapılabilecek hamle sayısını dondurucek.
    int heuristic= 0 ;
    for(int i = 0 ; i<7;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(temp.currentBoard[i][j] == 2)
            {
                if(i>=2) // uste bak
                {
                    if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                    {
                        heuristic++;
                    }
                }
                if (i<=4) // asagı bak
                {
                    if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                    {
                        heuristic++;
                    }
                }
                
                if (j<=4) // saga bak
                {
                    if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                    {
                     heuristic++;
                    }
                }
                if(j>=2 ) // sola bak
                {
                    if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                    {
                       heuristic++;
                    }
                }
            }
        }
        
    }
    
    return heuristic;
}



Board findSmallest(vector<Board>& v)
{
    Board temp = v.front();
    int holdTotal =0;
    
    for (int i= 0 ; i<v.size();++i ){
        if(temp.total >= v[i].total){
            temp = v[i];
            holdTotal = i;
        }
    }
    v.erase(v.begin()+holdTotal);
    return temp;
}

void aStar (Board& array){
    vector<Board> v ;
    int br1 =0;
    int br2 =0;
    int generated = 0;
    int expanded= 0  ;
    int totalPegs = 0;
    int maxSize = 0 ;
    v.push_back(array);
    generated++;
    while(1)
    {
        Board temp =findSmallest(v) ;
        expanded++;
        cleanStars(temp);
        for(int i = 0 ; i<7;i++)
        {
            for(int j=0;j<7;j++)
            {
                if(temp.currentBoard[i][j] == 2)
                {
                    if(i>=2) // uste bak
                    {
                        if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                        {
                            Board temp1 = temp;
                            temp1.currentBoard[i-2][j]=2 ;
                            temp1.currentBoard[i-1][j]=2 ;
                            temp1.currentBoard[i][j]=1 ;
                            temp1.parent = &temp;
                            temp1.layer++;
                            temp1.heuristic = findHeuristic(temp1);
                            generated++;
                            temp1.total = temp1.layer + temp1.heuristic;
                            v.push_back(temp1);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp1) == true)
                            {totalPegs = printBoard(temp1);br1 = 1;  break ;}
                            
                        }
                    }
                    if (i<=4) // asagı bak
                    {
                        if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                        {
                            Board temp2 = temp;
                            temp2.currentBoard[i+2][j]=2 ;
                            temp2.currentBoard[i+1][j]=2 ;
                            temp2.currentBoard[i][j]=1 ;
                            temp2.parent = &temp;
                            temp2.layer++;
                            temp2.heuristic = findHeuristic(temp2);
                            generated++;
                            temp2.total = temp2.layer + temp2.heuristic;
                            v.push_back(temp2);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp2) == true)
                            {totalPegs = printBoard(temp2);br1 = 1;  break ;}
                        }
                    }
                    
                    if (j<=4) // saga bak
                    {
                        if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                        {
                            Board temp3 = temp;
                            temp3.currentBoard[i][j+2]=2 ;
                            temp3.currentBoard[i][j+1]=2 ;
                            temp3.currentBoard[i][j]=1 ;
                            temp3.parent = &temp;
                            temp3.layer++;
                            temp3.heuristic = findHeuristic(temp3);
                            generated++;
                            temp3.total = temp3.layer + temp3.heuristic;
                            v.push_back(temp3);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp3) == true)
                            {totalPegs = printBoard(temp3);br1 = 1;  break ;}
                        }
                    }
                    if(j>=2 ) // sola bak
                    {
                        if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                        {
                            Board temp4 = temp;
                            temp4.currentBoard[i][j-2]=2 ;
                            temp4.currentBoard[i][j-1]=2 ;
                            temp4.currentBoard[i][j]=1 ;
                            temp4.parent = &temp;
                            temp4.layer++;
                            temp4.heuristic = findHeuristic(temp4);
                            generated++;
                            temp4.total = temp4.layer + temp4.heuristic;
                            v.push_back(temp4);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp4) == true)
                            {totalPegs = printBoard(temp4);br1 = 1;  break ;}
                        }
                    }
                }
            }
            if (br1 ==  1){br2 = 1 ; break ;}
        }
        if(br2==1) { break;}
    } // while bitisi
    cout << "Algorithm : Astar" << endl ;
    cout << "Number of generated nodes : "<< generated << endl ;
    cout << "Number of expanded nodes : " << expanded << endl ;
    cout << "Maximum number of nodes kept in memory : " << maxSize << endl ;
    cout << "Total number of pegs left : " << totalPegs << endl;
    
    
    
    
}

void aStar2 (Board& array){
    vector<Board> v ;
    int br1 =0;
    int br2 =0;
    int generated = 0;
    int expanded= 0  ;
    int totalPegs = 0;
    int maxSize = 0 ;
    v.push_back(array);
    generated++;
    while(1)
    {
        Board temp =findSmallest(v) ;
        expanded++;
        cleanStars(temp);
        for(int i = 0 ; i<7;i++)
        {
            for(int j=0;j<7;j++)
            {
                if(temp.currentBoard[i][j] == 2)
                {
                    if(i>=2) // uste bak
                    {
                        if((temp.currentBoard[i-2][j]==1 || temp.currentBoard[i-2][j]==3 ) && (temp.currentBoard[i-1][j]==1 || temp.currentBoard[i-1][j]==3))
                        {
                            Board temp1 = temp;
                            temp1.currentBoard[i-2][j]=2 ;
                            temp1.currentBoard[i-1][j]=2 ;
                            temp1.currentBoard[i][j]=1 ;
                            temp1.parent = &temp;
                            temp1.layer++;
                            //temp1.heuristic = findHeuristic(temp1);
                            generated++;
                            temp1.total = temp1.layer + temp1.heuristic2;
                            v.push_back(temp1);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp1) == true)
                            {totalPegs = printBoard(temp1);br1 = 1;  break ;}
                            
                        }
                    }
                    if (i<=4) // asagı bak
                    {
                        if((temp.currentBoard[i+2][j]==1 || temp.currentBoard[i+2][j]==3) && (temp.currentBoard[i+1][j]==1 || temp.currentBoard[i+1][j]==3))
                        {
                            Board temp2 = temp;
                            temp2.currentBoard[i+2][j]=2 ;
                            temp2.currentBoard[i+1][j]=2 ;
                            temp2.currentBoard[i][j]=1 ;
                            temp2.parent = &temp;
                            temp2.layer++;
                            generated++;
                            temp2.total = temp2.layer + temp2.heuristic2;
                            v.push_back(temp2);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp2) == true)
                            {totalPegs = printBoard(temp2);br1 = 1;  break ;}
                        }
                    }
                    
                    if (j<=4) // saga bak
                    {
                        if((temp.currentBoard[i][j+2]==1 || temp.currentBoard[i][j+2]==3) && (temp.currentBoard[i][j+1]==1 || temp.currentBoard[i][j+1]==3))
                        {
                            Board temp3 = temp;
                            temp3.currentBoard[i][j+2]=2 ;
                            temp3.currentBoard[i][j+1]=2 ;
                            temp3.currentBoard[i][j]=1 ;
                            temp3.parent = &temp;
                            temp3.layer++;
                            generated++;
                            temp3.total = temp3.layer + temp3.heuristic2;
                            v.push_back(temp3);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp3) == true)
                            {totalPegs = printBoard(temp3);br1 = 1;  break ;}
                        }
                    }
                    if(j>=2 ) // sola bak
                    {
                        if((temp.currentBoard[i][j-2]==1  || temp.currentBoard[i][j-2]==3) && (temp.currentBoard[i][j-1]==1 ||  temp.currentBoard[i][j-1]==3))
                        {
                            Board temp4 = temp;
                            temp4.currentBoard[i][j-2]=2 ;
                            temp4.currentBoard[i][j-1]=2 ;
                            temp4.currentBoard[i][j]=1 ;
                            temp4.parent = &temp;
                            temp4.layer++;
                            generated++;
                            temp4.total = temp4.layer + temp4.heuristic2;
                            v.push_back(temp4);
                            if(v.size()>maxSize){maxSize=v.size(); }
                            if(finalBoard(temp4) == true)
                            {totalPegs = printBoard(temp4);br1 = 1;  break ;}
                        }
                    }
                }
            }
            if (br1 ==  1){br2 = 1 ; break ;}
        }
        if(br2==1) { break;}
    } // while bitisi
    cout << "Algorithm : Astar" << endl ;
    cout << "Number of generated nodes : "<< generated << endl ;
    cout << "Number of expanded nodes : " << expanded << endl ;
    cout << "Maximum number of nodes kept in memory : " << maxSize << endl ;
    cout << "Total number of pegs left : " << totalPegs << endl;
    
    
    
    
}

// class olustur , heuristic  tut , parent tut ,  tek tek yazdırma islemi icin astar
int main(){
    Board starting ; //starting ilk durumdaki
    starting.currentBoard ={
        {0,0,1,1,1,0,0 },
        {0,0,1,1,1,0,0 },
        {1,1,1,1,1,1,1 },
        {1,1,1,2,1,1,1 },
        {1,1,1,1,1,1,1 },
        {0,0,1,1,1,0,0 },
        {0,0,1,1,1,0,0 }
    };
    printBoard(starting);
    cout << "Starting Board" << endl ;
   
    auto start = std::chrono::system_clock::now();
    BFS(starting);
    auto end = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout <<" Running Time BFS: " << elapsed_seconds.count() << "s\n";
    
    auto start1 = std::chrono::system_clock::now();
    DFS(starting);
    auto end1 = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds1 = end1-start1;
    cout <<" Running Time DFS: " << elapsed_seconds1.count() << "s\n";
    
    auto start2 = std::chrono::system_clock::now();
    aStar(starting);
    auto end2 = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds2 = end2-start2;
    cout <<" Running Time ASTAR: " << elapsed_seconds2.count() << "s\n";
    
    auto start3 = std::chrono::system_clock::now();
    aStar2(starting);
    auto end3 = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds3 = end3-start3;
    cout <<"Running Time ASTAR-second Heuristic: " << elapsed_seconds3.count() << "s\n";
    
    return 0;
}
