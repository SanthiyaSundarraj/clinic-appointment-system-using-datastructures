#include<iostream>
#include<cstring>
#include<cstdlib>
#include <time.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
int rear = - 1;
int front = - 1;
int TOP=-1;
int tok=0;
int timel=0;
int l=0;
struct Visitor
{
        string Name;
        string Phnno;
        int Token;
        int Age;
        bool Visit=0;
}w[100],stack[100];

int Hashcode(int data)
{
        int x;
        x=20-data;
        return x;
}
void waitlist(struct Visitor x)
{
	cout<<"\n\nHere there are more visitors are appointed so the current visitor is alloted a waiting List\n\n";
        if (front == - 1)
        front = 0;
        rear = rear + 1;
        w[rear] = x;
}
void GetAppointment(struct Visitor V[],struct Visitor x)
{
        int index;
        index=Hashcode(x.Token);
        tok=x.Token;
     	if(x.Token>3)
     	{
     		waitlist(x);
     		return;
     	}
        V[index].Token=x.Token;
        V[index].Name=x.Name;
        V[index].Phnno=x.Phnno;
        V[index].Age=x.Age;
}
void allotWaitList(struct Visitor v[],int idx)
{
	struct Visitor x;
	int c;
	if (front == - 1 || front > rear)
	{
		cout<<"\nNO Waitlist Patients are available.\n";
		return;
	}
	while(1)
	{
		x=w[front];
     	front = front + 1;
     	cout<<"Are you interseted to give this slot to patient with token number "<<x.Token<<"\n\tIf yes enter 1 or enter 2\nEnter your choice : ";
     	cin>>c;
    		if(c==1)
     	{
			v[idx]=x;
			cout<<"The appointmnet is alloted to patient "<<x.Name<<"\n";
			while(1)
			{
				if(TOP==-1)
    					return;
 
			    	rear = rear + 1;
        			w[rear] =stack[TOP];
    				TOP--;
			}
		}
		else
		{
			    TOP++;
    				stack[TOP]=x;
		}
	}
     	
}
void  RemoveVisitors(struct Visitor V[])
{	
	 	int no,index;
        cout<<"\nENTER THE TOKEN NUMBER OF THE VISITOR:";
        cin>>no;
        index=Hashcode(no);
         if(V[index].Token!=-1)
        	{	
       		V[index].Token=-1;
	        	V[index].Name=-1;	
     	   	V[index].Phnno=-1;
        		V[index].Age=-1;
        		cout<<"THE VISITOR IS SUCCESSFULLY REMOVED FROM THE LIST!\n\n";
		}
		if (front == - 1 || front > rear)
			return;
		else
   			allotWaitList(V,index);     
}
void updateStatus(struct Visitor V[],int token)
{
	int n,i,ti,op,timeup,flag=0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	ti=(tm.tm_hour*3600)+(60*tm.tm_min)+tm.tm_sec;
	timeup=ti-timel;
	timel=ti;
	n=floor(timeup/30);
	for(i=l;(i<l+n && i<= token);i++)
	{
		flag=1;
		cout<<"Whether the patient of token-"<<V[i].Token<<" is Visited or not :\n\tIf Yes ,press 1\n\t\tElse press 2\nEnter your choice : ";
		cin>>op;
		if(op==1)
		{
			V[i].Visit=1;
		}
		else
		{
			if(rear==front)
			{
				token++;
				V[i].Token=token;
				if(token>20)
				{
					cout<<"No Slots Available today\n\tAre you willing to present in Waiting list\n\t\tIf yes press 1,else press 2\nEnter your choice : ";
					cout<<op;
					if(op==1)
					{
						waitlist(V[i]);
						cout<<"The visitor are placed in the waiting List\n\n";
					}
					else
						cout<<"\nTry some other day..\n";
					break;
				}
				GetAppointment(V,V[i]);
				cout<<"Visitor is Alloted to token number - "<<token<<" Since there is an availablity \n";
			}
			else
				cout<<"The Visitor of token number - "<<V[i].Token<<" Didn't visited the Hospital And there is no extra appoinment timings available today\n\n";
		}
	}
	l=l+n;
	if(flag==1)
		cout<<"The Token is Expired for "<<l+1<<" visitors\n\n";
	else
		cout<<"There is no Visitors Available\n\n";
}
void ViewVisitors(struct Visitor V[])
{
        for(int i=0;i<24;i++)
        {
                if(V[i].Token!=-1)
                {
                        cout<<"TOKEN NUMBER OF THE VISITOR :"<<V[i].Token<<"\n";
                        cout<<"NAME OF THE VISITOR:"<<V[i].Name<<"\n";
                        cout<<"PHONE NUMBER OF THE VISITOR:"<<V[i].Phnno<<"\n";
                        cout<<"AGE OF THE VISITOR:"<<V[i].Age<<"\n\n";
                }
        }
}
int main()
{
        struct Visitor V[24],x;
        int token,i;
        int ch;
        for(i=0;i<24;i++)
        {
               V[i].Token=-1;
               V[i].Name=-1;
               V[i].Phnno=-1;
               V[i].Age=-1;
               V[i].Visit=0;
        }
 		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		timel=(tm.tm_hour*3600)+(60*tm.tm_min)+tm.tm_sec;
	       
		
        while(1)
        {
        		cout<<"\n\n************CLINIC  TOKEN  GENERATION  SYSTEM**************";
               cout<<"\n\n1.GET APPOINTMENT\n2.REMOVE APPOINTMENT\n3.VIEW APPOINTMENT DETAILS\n4.TO UPDATE VISITOR LIST\n5.EXIT\n\n";
               cout<<"ENTER YOUR CHOICE:";
               cin>>ch;
	
                switch(ch)
                {
                        case 1:
                              token++;
                              x.Token=token;
                              cout<<"\nENTER THE VISITOR NAME:";
                         	cin>>x.Name;
                              cout<<"\nENTER THE VISITOR PHONE NUMBER:";
                              cin>>x.Phnno;
                              cout<<"\nENTER THE VISITOR AGE:";
                              cin>>x.Age;
                              cout<<"\n\nYOUR TOKEN NUMBER IS GENERATED SUCCESSFULLY!!\n\n";
                              GetAppointment(V,x);
                              break;
                        case 2:
                              RemoveVisitors(V);
                              break;
                        
					case 3:
                              cout<<"THE DETAILS OF THE VISITORS OF THE CLINIC ARE! \n\n\n";
                     	     ViewVisitors(V);
                              break;
					case 4:
						updateStatus(V,token);
						break;	
                         case 5:
                              exit(0);
                }
        }
}
