#include <iostream>
#include<unordered_map>
#include<vector>
#include<memory>
#include "room_check.h"
#include "Person.h"
#include "Covid_pos.h"
#include "Covid_neg.h"
using namespace std;
//typedef std::shared_ptr<Person> ptr;

int main()
{
   unordered_map<int,Person*> covid_map;
   vector<Person*> healthy;
   vector<Person*> unhealthy;
   cout<<"                                         Welcome to the Quarantine Centre of NIT Silchar "<<endl;
   int choice;
   while(1)
   {
       cout<<"press 1 for new entry \npress 2 for search \npress 3 for deleting \npress 4 for vacant rooms \npress 5 for list of all covid negative people \npress 6 for list of all covid positive people"<<endl;
       cin>>choice;
       if(choice<1||choice>6)
       {
           cout<<"Please choose a valid choice : ";
           cin>>choice;
           cout<<endl;
       }
       if(choice==1)
       {
           cout<<"You have choosed 1 :) "<<endl;
           int total_entries;
           cout<<"Enter the total number of entries : ";
           cin>>total_entries;
           cout<<endl;
           for(int checker=0;checker<total_entries;checker++)
           {
               bool available=true;
               cout<<"Entry No. "<<checker+1<<" : "<<endl;
               cout<<"Please fill the asked informations"<<endl;
               string name;
               cout<<"Write your name : ";
               cin>>name;
               cout<<endl;
               string address;
               cout<<"Write your permanent address : ";
               cin>>address;
               cout<<endl;
               int age;
               cout<<"Write your age : ";
               cin>>age;
               int covid_status;
               cout<<"If positive enter 1 , else enter 2 "<<endl;
               cout<<"covid status : ";
               cin>>covid_status;
               if(covid_status==2){
                    Person *p=new Covid_neg(name,address,age,-1,-1);
                   healthy.push_back(p);
               cout<<"Covid Negative , please take care , no need of room allottment"<<endl;
               continue;

               }else{
                   string viral_strain;
               cout<<"Viral strain type : ";
               cin>>viral_strain;

               if(age<=0)
               {
                  cout<<"You have entered an invalid age,please enter a valid age : ";
                  cin>>age;
               }
               cout<<endl;
               int room;
               int floor;
               if(age>0&&age<=40)
               {
                   if(room_check(1,100,covid_map)){
                   cout<<"Your room will be on ground floor,please choose a room between 1-100(both inclusive) : ";
                    cin>>room;
                    floor=0;
                    while(covid_map[room]!=NULL || (room<=0||room>100)){
                   if(room<=0||room>100)
                   {
                       cout<<"Attention!"<<endl<<"You have choosed invalid room number,please choose a room between 1 to 100 : ";
                          cin>>room;
                   }else{
                        if(covid_map[room]!=NULL){
                        cout<<"Choose any other room,this room is already occupied "<<endl;
                        cin>>room;
                        }
                    }
                    }
                    cout<<endl<<"congratulations!,room no. : "<<room<<" is now allocated to you"<<endl;
                   }else{
                   cout<<"No room is available"<<endl;
                   available=false;
                   }
               }
               else if(age>40&&age<=60)
               {
                   if(room_check(101,300,covid_map)){
                   cout<<"Your room will be on first floor,please choose a room between 101-300(both inclusive) : ";
                    cin>>room;
                    floor=1;
                    while(covid_map[room]!=NULL || (room<=100||room>300)){
                   if(room<=100||room>300)
                   {
                       cout<<"Attention!"<<endl<<"You have choosed invalid room number,please choose a room between 101 to 300 : ";
                          cin>>room;
                   }else{
                        if(covid_map[room]!=NULL){
                        cout<<"Choose any other room,this room is already occupied "<<endl;
                        cin>>room;
                        }
                    }
                    }
                    cout<<endl<<"congratulations!,room no. : "<<room<<" is now allocated to you"<<endl;
                   }else{
                   cout<<"No room is available"<<endl;
                   available=false;
                   }
               }
               else
               {
                   if(room_check(301,500,covid_map)){
                   cout<<"Your room will be on ground floor,please choose a room between 301-500(both inclusive) : ";
                    cin>>room;
                    floor=2;
                    while(covid_map[room]!=NULL || (room<=300||room>500)){
                   if(room<=300||room>500)
                   {
                       cout<<"Attention!"<<endl<<"You have choosed invalid room number,please choose a room between 301 to 500 : ";
                          cin>>room;
                   }else{
                        if(covid_map[room]!=NULL){
                        cout<<"Choose any other room,this room is already occupied "<<endl;
                        cin>>room;
                        }
                    }
                    }
                    cout<<endl<<"congratulations!,room no. : "<<room<<" is now allocated to you"<<endl;
                   }else{
                   cout<<"No room is available"<<endl;
                   available=false;
                   }}
               if(available){
                    Person *p=new Covid_pos(name,address,age,room,floor,viral_strain);
                    unhealthy.push_back(p);
               covid_map[room]=p;
               }
               }
            }
       }
       else if(choice==2)
       {
           cout<<"choose 1 for search by room or choose 2 for search by name : ";
           int search_choice;
           cin>>search_choice;
           cout<<endl;
           if(search_choice==1)  //searching in constant time
           {
               int search_room;
               cout<<"Enter room no. to be searched : ";
               cin>>search_room;
               cout<<endl;
               if(search_choice<=0||search_choice>500)
                    cout<<"Invalid room,please enter a valid room no."<<endl;
               cin>>search_room;
               if(covid_map[search_room]==NULL)
               {
                   cout<<"Room is vacant "<<endl;
               }
               else
               {
                   Person *p1=covid_map[search_room];
                   p1->get_info();
               }
           }
           else if(search_choice==2)   //searching in O(n)
           {
               string choice_name;
               cout<<"Please enter the name of the person : ";
               cin>>choice_name;
               cout<<endl;
               int flag=0;
               for(auto it : covid_map)
               {
                   Person *temp=it.second;
                   string name=temp->get_name();
                   if(name==choice_name)
                   {
                       temp->get_info();
                       flag=1;
                       break;
                   }
               }
               if(!flag)
               {
                   cout<<"sorry!,there is no of name : "<<choice_name<<" in the Quarantine centre  right now "<<endl;
               }
           }
       }
       else if(choice==3)
       {

           cout<<"Enter the room no. : ";
           int delete_room;
           cin>>delete_room;
           cout<<endl;
           Person *temp=covid_map[delete_room];
           cout<<"We are deleting the information of the person of room no. : "<<delete_room<<" which is :"<<endl;
           temp->get_info();
           //covid_map[delete_room]=;
           covid_map.erase(delete_room);
       }
       else if(choice==4)
       {
           cout<<"list of vacant rooms are : "<<endl;
           for(int i=1;i<=500;i++)
           {
               if(covid_map.find(i)==covid_map.end())
                    cout<<i<<" ";
           }
       }else if(choice==5){
           cout<<"list of covid negative people : "<<endl;
           for(auto &i:healthy){
            cout<<i->get_name()<<endl;
           }
       }else if(choice==6){
           cout<<"list of covid positive people : "<<endl;
           for(auto &i:unhealthy){
            cout<<i->get_name()<<endl;
           }
       }

   }
    return 0;
}
