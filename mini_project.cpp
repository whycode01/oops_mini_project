/* MINI PROJECT: Implementation of Banking Management System.
Demonstrating the concepts of OOP in C++
Author: Vaidant Jain, Gaurav Mishra, Shivain Rajput, Pratham Shrivastava, Siddhi Salunkhe
Roll No.: 104042, 104056, 104060, 104071, 104099
Class: Division 4 
*/
// Start of CPP program
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class account
{
	
	int Money_Deposit;
	char type;
	int acno;
	char name[70];
public:
	
	void report() const;
	int retMoney_Deposit() const;
	void create_Bank_Account();
	void dep(int);
	int retacno() const;
	void Display_Account() const;
	void Updation();
	char rettype() const;
	void draw(int);
};


void account::Updation()
{
	cout<<"\n\tBank_Account No. : "<<acno;
	cout<<"\n\tUpdation Bank_Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\tUpdation Type of Bank_Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\tUpdation Balance Total-Money : ";
	cin>>Money_Deposit;
}
void account::create_Bank_Account()
{
	system("CLS");
	cout<<"\n\tPlease Enter the Bank_Account No. : ";
	cin>>acno;
	cout<<"\n\n\tPlease Enter the Name of the Bank_Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\tPlease Enter Type of the Bank_Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\tPlease Enter The Starting Total-Money : ";
	cin>>Money_Deposit;
	cout<<"\n\n\tBank_Account Created..";
}

void account::Display_Account() const
{
	cout<<"\n\tBank_Account No. : "<<acno;
	cout<<"\n\tBank_Account Holder Name : ";
	cout<<name;
	cout<<"\n\tType of Bank_Account : "<<type;
	cout<<"\n\tBalance Total-Money : "<<Money_Deposit;
}
int account::retacno() const
{
	return acno;
}



char account::rettype() const
{
	return type;
}
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<Money_Deposit<<endl;
}
void account::dep(int x)
{
	Money_Deposit+=x;
}
void account::draw(int x)
{
	Money_Deposit-=x;
}
int account::retMoney_Deposit() const
{
	return Money_Deposit;
}


void write_Bank_Account();
void display_acc(int);
void display_all();

void delete_Bank_Account(int);
void Money_Deposit_withdraw(int, int);
void Updation_Bank_Account(int);

void write_Bank_Account()
{
	account ac;
	ofstream outFile;
	outFile.open("Bank_Account.dat",ios::binary|ios::app);
	ac.create_Bank_Account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
void delete_Bank_Account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Bank_Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("Bank_Account.dat");
	rename("Temp.dat","Bank_Account.dat");
	cout<<"\n\nRecord Deleted ..";
}

void display_acc(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("Bank_Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.Display_Account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\tBank_Account number does not exist";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("Bank_Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tBank_Account HOLDER LIST\n\n";
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!========\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void Updation_Bank_Account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("Bank_Account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.Display_Account();
			cout<<"\n\n\tPlease Enter The New Details of Bank_Account"<<endl;
			ac.Updation();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); 
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\tRecord Not Found ";
}

void Money_Deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("Bank_Account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.Display_Account();
			if(option==1)
			{
				cout<<"\n\n\tTO Money_DepositSS Total-Money";
				cout<<"\n\n\tPlease Enter The Total-Money to be Money_Deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW Total-Money";
				cout<<"\n\n\tPlease Enter The Total-Money to be withdraw: ";
				cin>>amt;
				int bal=ac.retMoney_Deposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\tRecord Not Found ";
}
int main()
{
	char ch;
	int num;
	do
	{
	cout<<"\n\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	
	cout<<"\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

		cout<<"\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t1. NEW Bank_Account";
		cout<<"\n\t\t2. Money_Deposit Total-Money";
		cout<<"\n\t\t3. WITHDRAW Total-Money";
		cout<<"\n\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t5. ALL Bank_Account HOLDER LIST";
		cout<<"\n\t\t6. CLOSE AN Bank_Account";
		cout<<"\n\t\t7. Updation AN Bank_Account";
		cout<<"\n\t\t8. EXIT";
		cout<<"\n\n\t\tSelect Your Option (1-8): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_Bank_Account();
			break;
		case '2':
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			Money_Deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			Money_Deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			display_acc(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			delete_Bank_Account(num);
			break;
		 case '7':
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			Updation_Bank_Account(num);
			break;
		 case '8':
			cout<<"\n\n Exiting the program ";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}







