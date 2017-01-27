//Dalton Burke 102279938
//HW7

#include<iostream>

using namespace std;

//prototypes
int coins(int);
int ways(int amount, int demon);

//global for use in outputting data
int iters = 0;
int q = 0, d = 0, n = 0, p = 0;


int main()
{
    cout << "How many cents do you want?" << endl;
    int cents;
    cin >> cents;

    cout << "   \t{Q, D, N, P}" << endl; //formatting, first hold quarters, second holds dimes, etc.
    int numways = ways(cents,4);
    cout << "   \t{Q, D, N, P}" << endl; //formatting, first hold quarters, second holds dimes, etc.

    cout << "There are " << numways << " ways to make " << cents << " cents." << endl;
    cout << "The most efficient, {" << q << ", " << d << ", " << n << ", " << p << "}, requires " << q + d + n + p << " coin(s)." << endl;
    return 0;
}

int coins(int coins)
{
     switch(coins)
     {
         case 1: return 1;
         case 2: return 5;
         case 3: return 10;
         case 4: return 25;
         default: return 0;
     }
}

int ways(int amount, int denom)
{
     if(amount < 0)
         return 0;
     int cycles = int(amount/coins(denom)), ans = 0;
     for(int i = 0; i <= cycles; i++)
     {
         switch(denom)
         {
             case 1: p = amount;
                     break;
             case 2: n = i;
                     break;
             case 3: d = i;
                     break;
             case 4: q = i;
                     break;
         }
         if(denom == 1) //every time we get to the number of pennies, output it, and we end up starting over
         {
             iters++;
             cout << iters << ":\t{" << q << ", " << d << ", " << n << ", " << p << "},\trequires " << q + d + n + p << " coin(s)" << endl;
             return 1;
         }
         else
            ans += ways(amount - i*coins(denom), denom -1);
     }
     return ans;
}
