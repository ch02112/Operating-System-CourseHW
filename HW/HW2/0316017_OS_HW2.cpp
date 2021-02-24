#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

struct pro{
    int pro_id;
    int arrtime;
    int t1;
    int iot;
    int t2;
    int nowrun;
	int runrrtime;
	int iniarrtime;
};


int main()
{
    ifstream fin ("input.txt", ifstream::in);
    ofstream fout("0316017.txt");
    int f,num_process;
    int i,j,k;
    string str;
	vector<struct pro> p;

    getline(fin,str);
	istringstream ss(str);
	ss>>f;
    //
	getline(fin,str);
    istringstream ss2(str);
	ss2>>num_process;
	//
	for(i=0;i<num_process;i++)
	{
	    getline(fin,str);
		istringstream ss3(str);
		struct pro temp;
		ss3>>temp.pro_id;
		ss3>>temp.arrtime;
		temp.iniarrtime=temp.arrtime;
		ss3>>temp.t1;
		ss3>>temp.iot;
		ss3>>temp.t2;
		temp.nowrun=1;
		temp.runrrtime=0;
		p.push_back(temp);
	}
	struct pro temp1;
	for(j=0;j<p.size();j++)
    {
        for(k=0;k<p.size()-1;k++)
        {
            if(p.at(k).arrtime>p.at(k+1).arrtime)
            {
                temp1=p.at(k);
                p.at(k)=p.at(k+1);
                p.at(k+1)=temp1;
            }
            else if(p.at(k).arrtime==p.at(k+1).arrtime)
            {
                if(p.at(k).pro_id>p.at(k+1).pro_id)
                {
                    temp1=p.at(k);
                    p.at(k)=p.at(k+1);
                    p.at(k+1)=temp1;
                }
            }
        }
    }
	if(f==1)//short J F
    {
        int count=0,min=999999,next=-1,endcount=0;
        while(p.size()>endcount)
        {
            //cout<<"HI";
			next=-1;
			min=999999;
			endcount=0;
            for(i=0;i<p.size();i++)
            {
				if(p.at(i).nowrun==3)
				{endcount++;}
                else if(p.at(i).nowrun==1)
                {
                    if(p.at(i).arrtime<=count&&p.at(i).t1<min)
                    {
                        next=i;
                        min=p.at(i).t1;
                    }
					else if(p.at(i).arrtime<=count&&p.at(i).t1==min&&min==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).t1==min)
                    {
                        if(p.at(i).iniarrtime<p.at(next).iniarrtime)
                        {
                            next=i;
                        }
                        else if(p.at(i).iniarrtime>p.at(next).iniarrtime)
                        {

                        }
                        else{
                            if(p.at(i).pro_id<p.at(next).pro_id)
                            {
                                next=i;
                            }
                            else
                            {

                            }
                        }
                    }
                }
                else
                {
					if(p.at(i).arrtime<=count&&p.at(i).t2<min)
                    {
                        next=i;
                        min=p.at(i).t2;
                    }
					else if(p.at(i).arrtime<=count&&p.at(i).t2==min&&min==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).t2==min)
                    {
                        if(p.at(i).iniarrtime<p.at(next).iniarrtime)
                        {
                            next=i;
                        }
                        else if(p.at(i).iniarrtime>p.at(next).iniarrtime)
                        {

                        }
                        else{
                            if(p.at(i).pro_id<p.at(next).pro_id)
                            {
                                next=i;
                            }
                            else
                            {

                            }
                        }
                    }
                }
            }
			if(next==-1)
			{
				count++;
			}
			else
			{
				if(p.at(next).nowrun==1)
				{
					count=count+p.at(next).t1;
					p.at(next).nowrun=2;
					p.at(next).arrtime=p.at(next).iot+count;
				}
				else{
					count=count+p.at(next).t2;
					p.at(next).nowrun=3;
					//cout<<p.at(next).pro_id<<":"<<count<<"\n";
					fout<<p.at(next).pro_id<<":"<<count<<endl;
				}
			}

        }
    }
    else if(f==2)
    {
		int count=0,min=999999,next=-1,endcount=0;
        while(p.size()>endcount)
        {
            //cout<<"HI";
			next=-1;
			min=999999;
			endcount=0;
            for(i=0;i<p.size();i++)
            {
				if(p.at(i).nowrun==3)
				{endcount++;}
                else if(p.at(i).nowrun==1)
                {
                    if(p.at(i).arrtime<=count&&p.at(i).t1<min)
                    {
                        next=i;
                        min=p.at(i).t1;
                    }
					else if(p.at(i).arrtime<=count&&p.at(i).t1==min&&min==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).t1==min)
                    {
                        if(p.at(i).iniarrtime<p.at(next).iniarrtime)
                        {
                            next=i;
                        }
                        else if(p.at(i).iniarrtime>p.at(next).iniarrtime)
                        {

                        }
                        else{
                            if(p.at(i).pro_id<p.at(next).pro_id)
                            {
                                next=i;
                            }
                            else
                            {

                            }
                        }
                    }
                }
                else
                {
					if(p.at(i).arrtime<=count&&p.at(i).t2<min)
                    {
                        next=i;
                        min=p.at(i).t2;
                    }
					else if(p.at(i).arrtime<=count&&p.at(i).t2==min&&min==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).t2==min)
                    {
                        if(p.at(i).iniarrtime<p.at(next).iniarrtime)
                        {
                            next=i;
                        }
                        else if(p.at(i).iniarrtime>p.at(next).iniarrtime)
                        {

                        }
                        else{
                            if(p.at(i).pro_id<p.at(next).pro_id)
                            {
                                next=i;
                            }
                            else
                            {

                            }
                        }
                    }
                }
            }
			if(next==-1)
			{
				count++;
			}
			else
			{
				if(p.at(next).nowrun==1)
				{
					count=count+1;
					p.at(next).t1=p.at(next).t1-1;
					if(p.at(next).t1<=0)
					{
						p.at(next).nowrun=2;
						p.at(next).arrtime=p.at(next).iot+count;
					}


				}
				else{
					count=count+1;
					p.at(next).t2=p.at(next).t2-1;
					if(p.at(next).t2<=0)
					{
						p.at(next).nowrun=3;
						//cout<<p.at(next).pro_id<<":"<<count<<"\n";
						fout<<p.at(next).pro_id<<":"<<count<<"\n";
					}
				}
			}

        }
    }
    else if(f==3)
    {
		int count=0,endcount=0,next=-1,minarr=999999;
		queue<int> queue1;
		queue<int> queue2;
		while(p.size()>endcount)
		{
			endcount=0;
			next=-1;
			minarr=999999;

			for(i=0;i<p.size();i++)
			{
				if(p.at(i).nowrun==3)
				{endcount++;}
				else if(p.at(i).nowrun==1)
				{
					if(p.at(i).arrtime<=count&&p.at(i).arrtime<minarr)
					{
						next=i;
						minarr=p.at(i).arrtime;
					}
					else if(p.at(i).arrtime<=count&&p.at(i).arrtime==minarr&&minarr==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).arrtime==minarr)
					{
						if(p.at(i).pro_id<p.at(next).pro_id)
						{next=i;}
					}
				}
				else if(p.at(i).nowrun==11)
				{}
				else if(p.at(i).nowrun==12)
				{}
				else if(p.at(i).nowrun==2)
				{
					if(p.at(i).arrtime<=count&&p.at(i).arrtime<minarr)
					{
						next=i;
						minarr=p.at(i).arrtime;
					}
					else if(p.at(i).arrtime<=count&&p.at(i).arrtime==minarr&&minarr==999999)
					{next=i;}
                    else if(p.at(i).arrtime<=count&&p.at(i).arrtime==minarr)
					{
						if(p.at(next).nowrun==1)
						{}
						else if(p.at(i).pro_id<p.at(next).pro_id)
						{next=i;}
					}
				}
				else if(p.at(i).nowrun==21)
				{				}
				else if(p.at(i).nowrun==22)
				{				}
			}
			if(next==-1)
			{}
			else{
				if(p.at(next).nowrun==1)
				{
					queue1.push(next);
					p.at(next).nowrun=11;
				}
				else if(p.at(next).nowrun==2)
				{
					if(p.at(next).runrrtime==4)//21/22
					{
						queue2.push(next);
						p.at(next).nowrun=22;
					}
					else
					{
						queue1.push(next);
						p.at(next).nowrun=12;
					}
				}
			}
			if(!queue1.empty())
			{
				count++;
				if(p.at(queue1.front()).nowrun==11)
				{
					p.at(queue1.front()).t1--;
					p.at(queue1.front()).runrrtime++;
					if(p.at(queue1.front()).t1<=0)
					{
						p.at(queue1.front()).runrrtime=0;
						p.at(queue1.front()).nowrun=2;
						p.at(queue1.front()).arrtime=count+p.at(queue1.front()).iot;
						queue1.pop();
					}
					else if(p.at(queue1.front()).runrrtime>=4)
					{
						p.at(queue1.front()).runrrtime=4;
						p.at(queue1.front()).nowrun=21;
						queue2.push(queue1.front());
						queue1.pop();
					}
				}
				else if(p.at(queue1.front()).nowrun==12)
				{
					p.at(queue1.front()).t2--;
					p.at(queue1.front()).runrrtime++;
					if(p.at(queue1.front()).t2<=0)
					{
						p.at(queue1.front()).runrrtime=0;
						p.at(queue1.front()).nowrun=3;
						//cout<<p.at(queue1.front()).pro_id<<":"<<count<<"\n";
						fout<<p.at(queue1.front()).pro_id<<":"<<count<<"\n";
						queue1.pop();
					}
					else if(p.at(queue1.front()).runrrtime>=4)
					{
						p.at(queue1.front()).runrrtime=4;
						p.at(queue1.front()).nowrun=22;
						queue2.push(queue1.front());
						queue1.pop();
					}
				}
			}
			else if(!queue2.empty())
			{
				count++;
				if(p.at(queue2.front()).nowrun==21)
				{
					p.at(queue2.front()).t1--;
					if(p.at(queue2.front()).t1<=0)
					{
						p.at(queue2.front()).nowrun=2;
						p.at(queue2.front()).arrtime=count+p.at(queue2.front()).iot;
						queue2.pop();
					}
				}
				else if(p.at(queue2.front()).nowrun==22)
				{
					p.at(queue2.front()).t2--;
					if(p.at(queue2.front()).t2<=0)
					{
						p.at(queue2.front()).nowrun=3;
						//cout<<p.at(queue2.front()).pro_id<<":"<<count<<"\n";
						fout<<p.at(queue2.front()).pro_id<<":"<<count<<"\n";
						queue2.pop();
					}
				}
			}
			else
			{count++;}
		}
    }
	fin.close();
    fout.close();
	return 0;
}
