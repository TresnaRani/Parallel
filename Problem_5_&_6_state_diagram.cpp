#include<iostream>
#include<vector>
#include<math.h>
#include <queue>
using namespace std;



int m,n;

int table[8][100];
int forbid[10],l=0,maxm,icv = 0;
queue<int> permisible,ps;
vector<int>states;

void printTable(int val){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < val; j++){
            printf("%d ",table[i][j]);
        }
        cout<<endl;
    }
}
void convertToBinary(int n){
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    printf("%d", n % 2);

}

void stateTransition(int shift){
    // printf("ICV %d\n",(ps>>shift));
    int d = icv>>shift;
    //bitwise or
    int c = icv | d;
    printf("For Latency %d ",shift);
    // xor operation
    if( (c ^ icv )== 0 ){
        printf("Parent State ");
        convertToBinary(icv);
        cout<<endl;

    }
    else{
        if (c == ps.front()){
            printf("Self Loop\n");
            return;
        }
        printf("Next State : ");
        convertToBinary(c);
        cout<<endl;
        for (int i = 0; i < states.size(); i++)
        {
            if(c == states[i]) return;
        }

        ps.push(c);
        states.push_back(c);
    }
}

void oneTwoThree(){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (table[i][j] == 1){
                for (int k = j+1; k < n; k++){
                    if (table[i][k] == 1){
                        forbid[k-j] = 1;
                    }
                }
            }
        }
    }
    printf("Forbidden Latencies : ");
    for (int i = 0; i<n ; i++){
        if(forbid[i] == 1){
            printf("%d ",i);
            maxm = i;
        }
    }
    printf("\nPermisible Latencies : ");
    for (int i = 0; i<n; i++){
        if(forbid[i] == 0){
            printf("%d ",i);
            // permisible.push(i);
        }
    }
    cout<<endl;
    printf("Collision Vector : ");

    for (int i = maxm; i>0 ; i--){
        printf("%d ",forbid[i]);
        icv = icv + pow(2,i-1) * forbid[i];
    }
    cout<<endl;
    ps.push(icv);
    states.push_back(icv);

}
void permisibleCheck(int ps){
    int i = 0;
    int ls = 1;
    printf("Permisible : ");
    while(ls != 0) {
        ls = ps >> i;
        if((ls & 1) == 0){
            permisible.push(i+1);
            printf("%d ", i+1);
        }
        i++;
    }
}

int main(){


    cin >> m >> n;

     for(int i=0;i<m;i++)
    {

        for(int j=0;j<n;j++)
        {

            cin >> table[i][j];


        }



    }

    int pos = 1;
    int latency  = 0;

    oneTwoThree();
    printTable(n);
    while(!ps.empty()){
        printf("PS : ");
        int frnt = ps.front();
        convertToBinary(frnt);
        cout<<endl;
        permisibleCheck(frnt);
        cout<<endl;

        while(!permisible.empty()){
            latency = permisible.front();
            permisible.pop();
            stateTransition(latency);
        }
        ps.pop();

    }
    return 0;
}

/*

    1 0 0 0 0 0 0 0 1
    0 1 1 0 0 0 0 1 0
    0 0 0 1 0 0 0 0 0
    0 0 0 0 1 1 0 0 0
    0 0 0 0 0 0 1 1 0


*/
