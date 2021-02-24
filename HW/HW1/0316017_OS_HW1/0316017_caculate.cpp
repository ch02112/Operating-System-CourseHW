#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

int main()
{
    int n,i,sum=1;
    //cerr<<"I can receive input! Please enter a number.\n\n";
    cin>>n;
    if(n==0||n==1)
    {
        cout<<"1";
        cerr<<endl<<"The output number is "<<1<<".\n"<<endl;
        return 1;
    }
    else
    {
        for(i=2;i<=n;i++)
        {
            sum=sum*i;
        }
        cout<<sum;
        cerr<<endl<<"The output number is "<<sum<<".\n"<<endl;

        return 0;
    }
}
