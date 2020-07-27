#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<conio.h>
using namespace std;

int i,j;
int board[4][4];
int dirrow[] = {1,0,-1,0};
int dircolumn[] = {0,1,0,-1};

pair<int, int> findemptyposition()
{
    int filled = 1, row, col;
    while(filled)
    {
        row = rand() % 4;
        col = rand() % 4;
        if (board[row][col] == 0)
            filled = 0;
    }
    return make_pair(row, col);
}
void addnumber()
{
    pair<int, int> position = findemptyposition();
    board[position.first][position.second] = 2;
}

void newgame()
{
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
            board[i][j] = 0;
           addnumber();
}

void printlayout()
{
    system("cls");
    cout<<" :::: CONTROLS ::::"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout <<" n :: new game             q :: quit"<<endl;
   cout <<" a :: left                 s :: down"<<endl;
   cout <<" d :: right                w :: up"<<endl;
   cout<<"--------------------------------------------------------"<<endl;
   cout<<endl;

    for(i=0; i<4; ++i)
    {
        for(j=0; j<4; ++j)
        {
            if (board[i][j] == 0)
                cout <<setw(4)<< "#";
            else
                cout << setw(4) << board[i][j];
        }
        cout << endl;
    }
}

bool isvalidmove(int row, int col, int nextrow, int nextcol)
{
    if(nextrow < 0 || nextcol < 0 || nextrow >3 || nextcol > 3 || board[row][col] != board[nextrow][nextcol] && board[nextrow][nextcol] != 0)
        return false;
    return true;
}

void makemove(int direction)
{
    cout<<direction<<'\n';
    int startrow = 0, startcol = 0, rowmove = 1, colmove = 1;
    if(direction == 0)
    {
        startrow = 3;
        rowmove = -1;
        cout<<"here";
    }
    else if (direction == 1)
    {
        startcol = 3;
        colmove = -1;
        cout<<"here";
    }
    int movepossible, canaddnumber = 0;

    do
    {
    movepossible = 0;
    for(i=startrow; i>=0 && i<4; i += rowmove)
    {
        for(j=startcol; j>=0 && j<4; j +=colmove)
        {
            int nexti = i + dirrow[direction];
            int nextj = j + dircolumn[direction];

            if(board[i][j] && isvalidmove(i, j, nexti, nextj))
            {
                board[nexti][nextj]  += board[i][j];
                board[i][j] = 0;
                movepossible =  canaddnumber = 1;
            }
        }
    }
    }
    while(movepossible);
    if(canaddnumber)
        addnumber();
}

void _2048()
{
    int commandtodir[128];
    commandtodir['s'] = 0;
    commandtodir['d'] = 1;
    commandtodir['w'] = 2;
    commandtodir['a'] = 3;

    newgame();
    while(1)
    {
        printlayout();
        char command;
        cin >> command;

        if (command == 'n')
            newgame();
        else if (command =='q')
            break;
        else
        {
            int currdir = commandtodir[command];
            makemove(currdir);
        }

    }
}

void printarr(char mat[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<mat[i][j]<<' ';
        }
        cout<<'\n';
    }
}
vector<int> posfind(int x)
{
    if(x<4)
        x=x+6;
    else if(x>6)
        x=(x+6)%6;
    int i=0;
    int j=-1;
    int k=0;
    while(1)
    {
        if(i+j+k==x-1)
            break;
        if(j==2)
        {
            k=k+j;
            i=i+1;
            j=0;
        }
        else
            j+=1;
    }
    vector<int>pos;
    pos.push_back(i);
    pos.push_back(j);
    return pos;
}
int win(char mat[3][3])
{
    for(int j=0;j<3;j++)
    {
        char tmp=mat[0][j];
        int i=0;
        if(tmp=='X' || tmp=='O')
        {
            while(i<3)
            {
                if(mat[i][j]!=tmp)
                    break;
                i+=1;
            }  
            if(i==3)
            {
                if(tmp=='X')
                    return 1;
                else
                    return -1;
            }   
        }     
    }
    for(int i=0;i<3;i++)
    {
        char tmp=mat[i][0];
        int j=0;
        if(tmp=='X' || tmp=='O')
        {
            while(i<3)
            {
                if(mat[i][j]!=tmp)
                    break;
                j+=1;
            }
            if(j==3)
            {
                if(tmp=='X')
                    return 1;
                else
                    return -1;
            }   
        }
    }  
    char tmp=mat[0][0];
    int i=0;
    if(tmp=='X' || tmp=='O')
    {
        while(i<3)
        {
            if(mat[i][i]!=tmp)
                break;
            i=i+1;
        }
        if(i==3)
        {
            if(tmp=='X')
                return 1;
            else
                return -1;
        }
    }  
    tmp=mat[0][2];
    i=0;
    int j=2;
    if(tmp=='X' || tmp=='O')
    {
        while(i<3)
        {
            if(mat[i][j]!=tmp)
                break;
            i=i+1;
            j=j-1;
        }
        if(i==3)
        {
            if(tmp=='X')
                return 1;
            else
                return -1; 
        }    
    } 
    return 0;
}
int moveleft(char mat[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(mat[i][j]=='_')
                return 1;
        }
    }
    return 0;
}

int alphabeta(char mat[3][3],bool turn,int alpha,int beta)
{
    int score=win(mat);
    if(score==1 || score==-1)
        return score;
    if(!(moveleft(mat)))
        return 0;
    if(turn)
    {
        int best=-9999;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                 if (mat[i][j]=='_')
                 {
                    mat[i][j]='X';
                    best=max(best,alphabeta(mat,!(turn),alpha,beta));                         
                    mat[i][j]='_';
                    alpha=max(alpha,best);
                    if(beta<=alpha)
                        return best;
                 }
            }
        } 
        return best;
    }
      
    else
    {
        int best=9999;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(mat[i][j]=='_')
                {
                    mat[i][j]='O';
                    best=min(best,alphabeta(mat,!(turn),alpha,beta));
                    mat[i][j]='_';
                    beta=min(beta,best);
                    if(beta<=alpha)
                        return best;
                }
            }
        }
        return best; 
    }
}

vector<int> findmove(char mat[3][3])
{
    int best=9999;
    vector<int> pos={-1,-1};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(mat[i][j]=='_')
            {
                mat[i][j]='O';
                int mval=alphabeta(mat,true,-9999,9999);
                mat[i][j]='_';
                if(mval<best)
                {
                    pos[0]=i;
                    pos[1]=j;
                    best=mval;
                }
            }
        }
    }
    return pos;
}
     
int notvalid(vector<int> pos,char mat[3][3])
{
    if(pos[0]>3 || pos[0]<0 || pos[1]>3 || pos[1]<0)
        return 1;
    if (mat[pos[0]][pos[1]]!='_')
        return 1;
    return 0;
}
void printhelp()
{
    cout<<"\ngrid of the form:-\n";
    char mat[3][3]={{'7','8','9'},{'4','5','6'},{'1','2','3'}};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<mat[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';
}
void tictactoe()
{
    char mat[3][3]={{'_','_','_'},{'_','_','_'},{'_','_','_'}};
    printhelp();
    printarr(mat);
    while(moveleft(mat) && !(win(mat)))
    {
        int x;
        cout<<"Your Turn:- ";
        cin>>x;
        vector<int> pos=posfind(x);
        if(notvalid(pos,mat))
        {
            cout<<"Not a valid turn\n";
            continue;
        }
        int i=pos[0];
        int j=pos[1];
        mat[i][j]='X';
        if(moveleft(mat) && !(win(mat)))
        {
            pos=findmove(mat);
            i=pos[0];
            j=pos[1];
            mat[i][j]='O';
        }
        printarr(mat);
    }
    int score=win(mat);
    if(score==1)
        cout<<"Human Win\n";
    else if(score==-1)
        cout<<"computer Win";
    else
        cout<<"Match Draw\n";
    getch();
}
int main()
{
    while(1)
    {
        system("cls");
        int ch;
        cout<<"Welcome to Game Library\n";
        cout<<"Which game do yout want to play:-\n";
        cout<<"1. Tic-Tac-Toe(Single Player With AI)\n2. 2048\n3. Exit\nChoice:- ";
        cin>>ch;
        switch(ch)
        {
            case 1: 
                    tictactoe();
                    break;
            case 2:
                    _2048();
                    break;
            case 3:
                    exit(0);
        }
    }
}