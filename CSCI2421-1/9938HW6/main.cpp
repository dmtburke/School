//Dalton Burke 102279938
//csci2412 HW6

#include<iostream>
#include<stack>
#include<string>

using namespace std;

int getPrec(char op); //function to determine which operator has higher precedence

string inToPo(string infix); //inToPo is short for inFixToPostFix, does the actual conversion


int main()
{
    string in;
    cout << "Hello, what are we converting from infix to postfix?" << endl;
    getline(cin, in);
    cout << "Infix version: " << in << endl;
    cout << "Postfix version: " << inToPo(in) << endl;
    return 0;
}


int getPrec(char op)
{
     switch(op)
     {
         case '^': return 3; //^ has highest precedence
         case '*': return 2;
         case '/': return 2;
         case '+': return 1;
         case '-': return 1;
         default : return 0; //returns 0 if non operator
     }
}

string inToPo(string in)
{
     int size = in.length();
     string post = ""; //empty string, we will be using += later
     stack<char> stk;
     int prec;
     int i = 0;
     char ch;

     while(i < size)
    {
         ch = in[i];
         if(ch == ' ' || ch == '\t')
             ;//do nothing, don't put it in the new string, I will insert spaces as needed on my own
         else{
         if(ch == '(')
         {
              stk.push(ch);
              i++;
              continue;
         }
         if(ch == ')')
         { //dump the stack out, we are at the end of the parenthesis
             while(!stk.empty() && stk.top() != '(' )
             {
                 post += ' '; //inserting spaces before operators
                 post += stk.top(); //add the stuff in the stack just to the end of the postfix
                 stk.pop();
             }
             if(!stk.empty())
                 stk.pop();
             i++;
             continue;
         }

         prec = getPrec(ch);
         if(prec == 0)
              post += ch; //append to the end of postfix representation

         else if(stk.empty())
         {
             post += ' ';
             stk.push(ch);
         }
         else
         {
             while(!stk.empty() && stk.top() != '(' && prec <= getPrec(stk.top()))
             {
                 post += ' ';
                 post += stk.top();
                 stk.pop();
             }
             post +=' ';
             stk.push(ch);
         }}

     i++;
    }
     while (!stk.empty())
     {
         post += ' ';
         post += stk.top();
         stk.pop();
     }

     return post;
}
