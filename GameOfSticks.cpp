#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> mino, maxo, maxChoice;

int pruning(int n,int max);

int main(){
    
    int option=0;
    cout << "\n\"The Game Of Sticks - From the n given sticks, the two opponents\nneed to choose 1-3 sticks from the remain sticks. The one who\nchose the last stick will lose.\"\n\n";
    
    cout<<"Choose one option from below: \n1. AI vs Human\n2. AI vs AI\nYour option: ";     cin>>option;
    
    if(option==1){
        cout<<"You are now playing with AI...\n\n";
        cout<<"Enter the number of sticks (n): ";   cin>>n;
        
        maxo.resize(n+1,-1);
        mino.resize(n+1,-1);
        maxChoice.resize(n+1,-1);

        int toss=rand()%2, input, i=0;
        if(toss ==0) {
            cout<<"\nAccording to toss AI (Player 2) won and You (Player 1) will take stick 1st.";
        }else {
            cout<<"\nYou (Player 2) won the toss. AI (Player 1) will take the stick out first.";
        }

        cout << "\n\nThe game begins...";

        while(n>0) {
            if((i==0&&toss==0) || (i%2==1&&toss==1)) {   
                cout<<"\nHow many sticks (1 to 3) from the remaining "<< n <<" sticks, you want to take out: ";
                cin>>input;
                if(input<0&&input>3&&input<=n)
                {   cout << "No. of sticks not in range\n"; 
                    return 0;
                }
                n-=input;
                if(n<=0) {
                    cout << "\nUnfortunately! You Loose\n";
                }

            }else{
                int win = pruning(n,1);
                int choice;
                if(maxChoice[n]==-1) {
                    choice=1;
                }else{
                    choice=maxChoice[n];
                }
                cout<<"\n\nAI Took " <<choice << " Sticks. Now "<<n-choice<<" Sticks Remain\n";
                n-=choice;
                if(n<=0)
                {
                    cout << "\nCongratulations! You win\n";
                }
            }

            i++;
        }
    }else if(option==2){
        cout<<"\nNow AI-1 is playing with AI-2 ...\n\n";
        cout<<"Enter the number of sticks (n): ";   cin>>n;
        maxo.resize(n+1,-1);
        mino.resize(n+1,-1);
        maxChoice.resize(n+1,-1);
        int i=0;
        int win = pruning(n, 1);
        
        if(win == 0) {
            cout << "\n\"For n = " << n << ", first AI To take sticks will always lose (assuming \nsecond AI takes optimal steps to defeat first AI)\"\n\n";
        } else {
            cout << "\n";
        }

        while(n>0) {   
            pruning(n,1);
            int choice;
            if(maxChoice[n]==-1) {
                choice=1;
            } else {
                choice=maxChoice[n];
            }

            cout<<"AI-"<<(i%2)+1<<" took "<<choice<<" sticks. Now "<<n-choice<<" sticks Remain\n";
            n-=choice;
            i++;
        }
        if(win==1)
            cout<<"\nAI-1 Wins\n";
        else{
            cout<<"\nAI-1 Loses\n";
        }
    }else{
        cout<<"Invalid Option\n";
    }

    
return 0;
}

int pruning(int n,int max) {
    if(n==1) {
        if(max==1) {   
            return 0;
        } else {   
            return 1;
        }
    }

    if(max) {
        if(maxo[n]>-1) {
            return maxo[n];
        }

        for(int i=1;i<=3 && n-i>0;i++){
            
            if(pruning(n-i,1-max)==1)
               {   maxChoice[n]=i;
                   maxo[n]=1;
                   return 1;
               }
        }
        maxo[n]=0;
        return 0;
    } else {
        if(mino[n]>-1) {
            return mino[n];
        }
        for(int i=1;i<=3 && n-i >0;i++){
            if(pruning(n-i,1-max)==0)
                {    
                   mino[n]=0;
                   return 0;
               }
        }
        mino[n]=1;
        return 1;
    }
    
}