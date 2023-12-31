 //C++ PROJECT
#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
using namespace std;
//CLASS

class hotel
{
    int room_no;
    string name;
    string address;
    string phone;
public:
    void main_menu();		    //to dispay the main menu
    void add();			        //to book a room
    void display(); 		    //to display the customer record
    void rooms();			      //to display alloted rooms
    void edit();			      //to edit the customer record
     int check(int);		    //to check room status
    void modify(int);		    //to modify the record
    void deleteRecord(int);  	//to delete the record
    void bill(int);         //for the bill of a record
    void book(int,int);     //for available room
     };


//MAIN MENU

void hotel::main_menu()
{
    int choice;
    while(choice!=5)
    {
        system("cls");
        cout<<"\n\t\t\t\t*************************";
        cout<<"\n\t\t\t\t*SIMPLE HOTEL MANAGEMENT*";
        cout<<"\n\t\t\t\t*     * MAIN MENU *     *";
        cout<<"\n\t\t\t\t*************************";
        cout<<"\n\n\n\t\t\t1.Book A Room";
        cout<<"\n\t\t\t2.Customer Records";
        cout<<"\n\t\t\t3.Rooms Allotted";
        cout<<"\n\t\t\t4.Edit Record";
        cout<<"\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;

switch(choice)
   {

case 1:	add();
    break;

case 2: display();
    break;

case 3: rooms();
    break;

case 4:	edit();
    break;

case 5: break;

default:
      {
   cout<<"\n\n\t\t\t Wrong choice!";
   cout<<"\n\t\t\t Press any key to continue....!!";
getch();
      }
     }
  }
}


//BOOKING OF ROOM


void hotel::add()
{
  system("cls");
int n,flag;
string r;
ofstream fout("Record.dat",ios::app);

cout<<"\n Enter Customer Detalis";
cout<<"\n ----------------------";
//cout<<"\n\n Room no: ";
cout<<"\n Total no. of Rooms - 50           price(per night)";
cout<<"\n Single Bed Rooms from 01 - 30     1100/-";book(1,30);
cout<<"\n\n Double Bed Rooms from 31 - 45     2200/-";book(31,45);
cout<<"\n\n Suits from 46 - 50                4000/-"; book(46,50);
cout<<"\n\n Enter * to return or \n Enter The Room no. you want to stay in :- ";
cin>>r;
if(r=="*")
  main_menu();
else{
flag=check(stoi(r));
if(flag){
cout<<"\n Sorry.!Room is already booked";
}
else
{
room_no=stoi(r);
cin.ignore();
cout<<" Name: "; getline(cin,name);
//cin>>name;
cout<<" Address: "; getline(cin,address);
//cin>>address;
cout<<" Phone No: "; getline(cin,phone);
//cin>>phone;

fout.write((char*)this,sizeof(hotel));
cout<<"\n Room is booked...!!!";


}

cout<<"\n Press any key to continue.....!!";

getch();
fout.close();
}
}

// Displaying booked rooms in Add menu   //
void hotel::book(int x,int y){
ifstream fin("Record.dat", ios::in | ios::binary);

    cout << "\nBooked rooms: ";
            //(!fin.eof())
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        if (room_no >= x && room_no <= y) {
            cout << room_no << ",";
        }
    }

    fin.close();
}

//CUSTOMER`S RECORD

void hotel::display()
{

  system("cls");

ifstream fin("Record.dat",ios::in);
string r;
int flag;

cout<<"\n Enter * to return or \n Enter room no. for a particular customer`s details :- ";
cin>>r;
if(r=="*")
  main_menu();

else{

while(!fin.eof())
{
int n = stoi(r);
fin.read((char*)this,sizeof(hotel));
if(room_no==n)
{

  system("cls");
cout<<"\n Customer Details";
cout<<"\n ----------------";
cout<<"\n\n Room no: "<<room_no;
cout<<"\n Name: "<<name;
cout<<"\n Address: "<<address;
cout<<"\n Phone no: "<<phone;
flag=1;
break;

}

}

if(flag==0)
cout<<"\n Sorry Room no. not found or vacant....!!";
cout<<"\n\n Press any key to continue....!!";

getch();
}
fin.close();
}


//END OF DISPLAY FUNCTION

//FUNCTION TO DISPLAY ALL ROOMS OCCUPIED


void hotel::rooms()
{

     system("cls");

    ifstream fin("Record.dat", ios::in | ios::binary);

    cout << "\n\t\t\tList Of Rooms Allotted";
    cout << "\n\t\t\t----------------------";
    cout << "\n\nRoom No.\tName\t\tAddress\t\tPhone No.\n";

    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        cout << "\n\n" << room_no << "\t\t" << name;
        cout << "\t\t" << address << "\t\t" << phone;
    }

    cout << "\n\n\nPress any key to continue.....!!";
    getch();

    fin.close();

}


//FUNCTION FOR EDITING RECORDS AND FOR BILL


void hotel::edit()
{

  system("cls");

string choice,r;
cout<<"\n EDIT MENU";
cout<<"\n ---------";
cout<<"\n\n 1.Modify Customer Record";
cout<<"\n 2.Delete Customer Record";
cout<<"\n 3.Bill Of Customer";
cout<<"\n *.Return to main menu\n Enter your choice: ";


cin>>choice;
if(choice=="*")
  main_menu();
else{
  system("cls");
cout<<"\n Enter * to return or \n Enter room no: " ;
cin>>r;
if(r=="*")
  edit();
else {
int c=stoi(choice);
int n = stoi(r);
switch(c)
{

case 1:	modify(n);
break;

case 2:	deleteRecord(n);
break;

case 3: bill(n);
break;


default: cout<<"\n Wrong Choice.....!!";

}
cout<<"\n Press any key to continue....!!!";

getch();

}
}
}


int hotel::check(int roomNumber) {
    if (roomNumber == 0)
        return 1;

    ifstream fin("Record.dat", ios::in | ios::binary);

    bool found = false;

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == roomNumber) {
            found = true;
            break;
        }
    }

    fin.close();
    return found;
}


//CUSTOMERS RECORD


void hotel::modify(int r)
{

   long pos,flag=0;
     fstream file("Record.dat",ios::in|ios::out|ios::binary);
      while(!file.eof())
        {
          pos=file.tellg();
          file.read((char*)this,sizeof(hotel));
            if(room_no==r)
              {
              cout<<"\n Enter New Details";
              cout<<"\n -----------------";
              cout<<"\n Name: ";
              cin>>name;
              cout<<" Address: ";
              cin>>address;
              cout<<" Phone no: ";
              cin>>phone;
              file.seekg(pos);
              file.write((char*)this,sizeof(hotel));
              cout<<"\n Record is modified....!!";
              flag=1;
              break;

             }
          }

    if(flag==0)
      cout<<"\n Sorry Room no. not found or vacant...!!";
        file.close();
}
//DELETING RECORD
void hotel::deleteRecord(int roomNumber) {
    system("cls");
    char choice;

    ifstream fin("Record.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);

    bool found = false;

    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {
        if (roomNumber == room_no) {
            found = true;
            cout << "\n Room No: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;

            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> choice;

            if (choice == 'n') {
                fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
            }
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(hotel));
        }
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "\n Room No. " << roomNumber << " not found or vacant...!!";
    } else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
        cout << "\n Record deleted successfully!";
    }
    getch();
    edit();
}


//CUSTOMER`S BILL

void hotel::bill(int roomNumber)
{
    ifstream file("Record.dat", ios::in | ios::binary);

    if (!file)
    {
        cout << "Unable to open the file.";
    }
    else
    {
        hotel customer;
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&customer), sizeof(hotel)))
        {
            if (customer.room_no == roomNumber)
            {
                found = true;
                int roomRate = 0;

                if (customer.room_no >= 1 && customer.room_no <= 30)
                {
                    roomRate = 1100;
                }
                else if (customer.room_no >= 31 && customer.room_no <= 45)
                {
                    roomRate = 2200;
                }
                else if (customer.room_no >= 46 && customer.room_no <= 50)
                {
                    roomRate = 4000;
                }

                cout << "Your bill for Room No. " << customer.room_no << " is: " << roomRate << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Room No. " << roomNumber << " not found." << endl;
        }

        file.close();
    }

    cout << "\nPress any key to return...\n";
    getch();
    edit();
}


//START OF MAIN PROGARM


int main()
{
hotel h;
system("cls");
cout<<"\n\t\t\t\t\t****************************";
cout<<"\n\t\t\t\t\t* HOTEL MANAGEMENT PROJECT *";
cout<<"\n\t\t\t\t\t****************************";
cout<<"\n\n\t\t\t\t\tDeveloped By:";
cout<<"\t CtrlShftHack";
cout<<"\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";
getch();
h.main_menu();
return 0;
}

//END OF MAIN PROGRAM


