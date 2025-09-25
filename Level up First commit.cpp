#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;
int CountNumber(int n)
{
    int BigNumber=1;
    for(int i=1;i<=n;i++)
    {
        BigNumber*=10;
    }
    return BigNumber;
}
double calculate(string s,int begin,int end)
{
    stack<double> a;
    stack<char> b;
    int NumberSum=0;
    double TemporarySum=0;
    double result;
    for(int i=begin;i<=end;i++)
    {
        int BoolNumber;
        BoolNumber=s[i];
        if(BoolNumber>=48&&BoolNumber<=57)
        {
            NumberSum++;
        }
        else
        {
            if(s[i]=='(')
            {
                int MarkOne=i+1;
                int MarkTwo=i+1;
                while(s[MarkTwo]!=')')
                {
                    MarkTwo++;
                }
                TemporarySum=calculate(s,MarkOne,MarkTwo);
            }
            int Count=NumberSum;
            for(int j=i-NumberSum;j<=i;j++)
            {
                int BoolNumber2=s[j];
                TemporarySum+=CountNumber(Count)*(BoolNumber2-48);
            }
           if(a.empty())
           {
                a.push(TemporarySum);
                TemporarySum=0;
                b.push(s[i]);
           }
           else
           {
                if(!b.empty())
                {
                    if(b.top()=='*'||b.top()=='/')
                    {
                        double Marker=a.top();
                        double TemSign;
                        if(b.top()=='*')
                        {
                            TemSign=a.top()*TemporarySum;
                        }
                        else if(b.top()=='/')
                        {
                            TemSign=a.top()/TemporarySum;
                        }
                        a.pop();
                        a.push(TemSign);
                        TemporarySum=0;
                    }
                    else
                    {
                        b.push(s[i]);
                    }
                }
           }
        }
    }
    int Count=NumberSum;
    for(int j=end-NumberSum;j<=end;j++)
    {
        int BoolNumber2=s[j];
        TemporarySum+=CountNumber(Count)*(BoolNumber2-48);
    }
    while(a.size()!=1)
    {
        double SymbolNumber;
        SymbolNumber=a.top();
        a.pop();
        double TemporaryResult;
        char sign;
        sign=b.top();
        b.pop();
        if(sign=='+')
        {
            TemporaryResult=a.top()+SymbolNumber;
        }
        if(sign=='-')
        {
            TemporaryResult=a.top()-SymbolNumber;
        }
        a.push(TemporaryResult);
    }
    result=a.top();
    return result;
}
int main()
{
    string s1;
    cout<<"Please enter your mathematical expression"<<endl;
    cin>>s1;
    double result;
    result=calculate(s1,0,s1.size()-1);
    cout<<"Here is your result"<<endl;
    cout<<result;
    return 0;
}
