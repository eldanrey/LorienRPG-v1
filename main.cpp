/*
Author: Kagesama
Date Created: 01/01/2021

Legend:
	User:
		userData[0]=User Health
		userData[1]=User Base attack/damage
		userData[2]=User Level
		userData[3]=User XP
		userData[4]=User Max Health(based on level)
		userData[5]=User Max XP(based on level)
		userData[6]=Coins

	Mogs:
		Health=10*1.2*Level
		Attack=5*0.8*level
*/
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <random>
using namespace std;

ofstream outFile;
ifstream inFile;
fstream inOutFile;
void first_screen_logo(){
cout<<"					         .';::c:::;'..              \n";
cout<<"					        .,ldkO00KXXNWWWNX0xl;.      \n";
cout<<"					      'cddl:,,,,,,,;;:lx0NMMWKx;.       \n";
cout<<"					    'cc,..;lxO0KKK0kxdc,.,o0WMMWO:.     \n";
cout<<"					  .,;..,dKWMMMWNKOxddddoc'..c0WMMNx'    \n";
cout<<"					 .'. ,kNMMMWKd:;;:::;'.  .   .dNMMW0;   \n";
cout<<"					   .lXMMMWKl';o0X0dooollc;.   .oNMMM0'  \n";
cout<<"					   lNMMMWO,'dNMXo;o0NWMMMWKd.  .xWMMWd. \n";
cout<<"					  ,KMMMM0'.kWMWx'oWWWKdlcoONk.  ;KMMMK, \n";
cout<<"					  lNMMMWo.cNMMWd'xWOl,    .ck,  .kMMMX: \n";
cout<<"					  lNMMMWo.cNMMMKccKx,.     .;.  .dWMMX: \n";
cout<<"					  ;XMMMMO.'OMMMMXdlol;.    'c,  .xMMM0' \n";
cout<<"					 .xWMMMWx';OWMMMWXOkkdlclkOo.  '0MMNo  \n";
cout<<"					 'OWMMMW0:,o0NMMMMMMMMWXx;   .oWMWx.  \n";
cout<<"					  'kWMMMMNOc;:ldkkkkxoc;,.   lXMNx.   \n";
cout<<"					    .c0WMMMMWXOdollllodxxc. .oNWKl.    \n";
cout<<"					     .;d0NWMMMMMMMWWXkc. .c0NKo'      \n";
cout<<"					        ..;clooolc:,...;oO0xc.        \n";
cout<<"					            ....',;:cool;.           \n";
cout<<"					           ..',,,,'.    \n";
}
class Enemy{
	public:

	void huntMogs(int userData[],int choice){

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int> mogLevel1to10(1,10);
  std::uniform_int_distribution<int> mogLevel11to20(11,20);
  std::uniform_int_distribution<int> mogLevel21to30(21,30);
  std::uniform_int_distribution<int> mogLevel31to40(31,40);
  std::uniform_int_distribution<int> mogLevel41to50(41,50);
  int mogLevel=0;
	if(choice==1)mogLevel=mogLevel1to10(generator);
	else if(choice==2)mogLevel=mogLevel11to20(generator);
	else if(choice==3)mogLevel=mogLevel21to30(generator);
	else if(choice==4)mogLevel=mogLevel31to40(generator);
	else if(choice==5)mogLevel=mogLevel41to50(generator);
	int mogHealth=10*1.2*mogLevel;
	int mogAttack=5*0.8*mogLevel;
	int mogXP=100*0.5*(mogLevel*0.5);
	userData[0]-=(mogHealth/userData[1])*mogAttack;
	userData[3]+=mogXP;
	userData[6]+=10*(0.4*mogLevel);

}
};
class User{
	public:
		int hpPotion=0;
		void inventory(){
			system("cls");
			cout<<"Health potion - "<<hpPotion;
		}
};
User user;
Enemy enemy;
int loricShop(int userData[]){
	loricShopMenu:
	system("cls");
	cout<<"WELCOME TO LORIC SHOP!\n";
	cout<<"Please choose what you want to buy: ";
	cout<<"\n\n[1]Health Potion  -  50 Loric coins";
	cout<<"\n[2]Go back to main menu";
	cout<<"\n\n\nYour choice: ";
	string choice;
	cin>>choice;
	if(choice=="1"){
		userData[6]-=50;
		user.hpPotion+=1;
		goto loricShopMenu;
	}
	else if(choice=="2"){
		return 1;
	}

}
int closeProgram(string currUsername, int currUserData[]){
	int userData[6];
	string username,s,password;
	inFile.open("data.dat");
	outFile.open("temp.dat");
	while(getline(inFile,s)){
		stringstream ss(s);
	ss>>username>>password;
	for(int i=0;i<7;i++){
		ss>>userData[i];
	}
	if(username==currUsername){
		outFile<<currUsername<<" "<<password<<" ";
		for(int i=0;i<7;i++){
			outFile<<currUserData[i]<<" ";
		}
		outFile<<'\n';
	}
	else {
	outFile<<username<<" "<<password<<" ";
	for(int i=0;i<7;i++){
		outFile<<userData[i]<<" ";
	}
	outFile<<'\n';}
	}
	outFile.close();
	inFile.close();
	remove("data.dat");
	rename("temp.dat","data.dat");


}
int loginSignupMenu();
void IGdata(string username, int userData[]){
	userData[4]=(200*1.5*userData[2]);
	userData[5]=(100*userData[2]*1.5);
	if(userData[0]>=userData[4])userData[0]=userData[4];
	userData[1]=(5*(0.8*userData[2]));
	while(userData[3]>=userData[5]){
		userData[3]-=userData[5];
		userData[2]++;
	}
	if(userData[0]<=0){
		userData[0]=0;
		userData[6]-=100;
		userData[0]=userData[4];
	}
	cout<<"Username: "<<username;
	cout<<"\nHP: "<<userData[0]<<"/"<<userData[4];
	cout<<"\nAttack: "<<userData[1];
	cout<<"\nLevel: "<<userData[2];
	cout<<"\nXP: "<<userData[3]<<"/"<<userData[5];
	cout<<"\nLoric Coins: "<<userData[6];
}
void game(string username, int userData[]){
	main_menu:
	system("cls");
	IGdata(username,userData);
	cout<<"\n\n[1]Hunt Mogadorians\n[2]Inventory\n[3]Go to Shop\n[4]Exit and Save\nYour choice: ";
	string choice;
	cin>>choice;
	if(choice=="1"){
		system("cls");
	cout<<"Please select the level of the mogadorian you want to fight: ";
	cout<<"\n[1]Level 1-10\n[2]Level 11-20\n[3]Level 21-30\n[4]Level 31-40\n[5]Level 41-50\nYour choice: ";
	int choice;
	cin>>choice;
	if(choice<1&&choice>5){
		cout<<"\n\n\t\t\t\tInvalid Input!\n\n";
		Sleep(1000);
		system("cls");
		goto main_menu;
	}
		enemy.huntMogs(userData,choice);
		goto main_menu;
	}
	else if (choice=="2"){
		inventoryMenu:
		user.inventory();
		cout<<"\n\n[1]Back to main menu\n[2]Use Health Potion\n\nYour choice: ";
			string choice;
			cin>>choice;
			if(choice=="1"){
				goto main_menu;
			}
			else if(choice=="2"){
				user.hpPotion-=1;
				userData[0]+=100;
				goto inventoryMenu;
			}
			else {
				goto inventoryMenu;
			}


	}
	else if(choice=="3"){
		int willreturn=loricShop(userData);
		if(willreturn==1)goto main_menu;

	}
	else if(choice=="4"){
		closeProgram(username,userData);
	}
	else {
		cout<<"\n\n\t\t\tInvalid Input try again!\n\n";
		Sleep(1500);
		system("cls");
		goto main_menu;
	}
}

void login(){
	loginMenu:
	int userData[7];
	cout<<"\n\n\t\t\t\tLOGIN(Enter '-1' to go back)\n\n\t\t\t\tUsername: ";
	string username,password,s,DBusername,DBpassword;
	cin>>username;
	if(username=="-1"){
		system("cls");
		loginSignupMenu();

	}
	cout<<"\n\t\t\t\tPassword: ";
	cin>>password;



	inFile.open("data.dat");
	bool isPresent=false;
	while(getline(inFile,s)){
		stringstream ss(s);
		ss>>DBusername>>DBpassword;
		for(int i=0;i<7;i++){
			ss>>userData[i];
		}
		if(username==DBusername&&password==DBpassword){
			isPresent=true;
			break;
		}

	}
	inFile.close();
	if(isPresent){
		game(username,userData);
	}

	else {
		cout<<"\n\n\t\t\tUsername or Password is Incorrect \n\n";
		Sleep(3000);
		system("cls");
		goto loginMenu;

	}



}
void signup(){
	signupMenu:
	cout<<"\n\n\t\t\tSignup(Enter '-1' to go back)\n\n\t\t\t\tUsername: ";
	string username,password,confirmPassword,DBusername,s;
	cin>>username;
	if(username=="-1"){
		system("cls");
		loginSignupMenu();

	}
	cout<<"\n\t\t\t\tPassword: ";
	cin>>password;
	cout<<"\n\t\t\t\tConfirm Password:";
	cin>>confirmPassword;

	 if(password==confirmPassword){
		inFile.open("data.dat");
		bool present=false;
		while(getline(inFile,s)){
			stringstream ss(s);
			ss>>DBusername;
			if(DBusername==username){
				present=true;
				break;
			}
		}
		inFile.close();
		if(present==true){
			cout<<"\n\n\t\t\tTHIS USERNAME IS TAKEN, please do it again!\n\n";

			Sleep(3000);
			system("cls");
			goto signupMenu;
		}

		else{
			outFile.open("data.dat",ios::app);
			outFile<<username<<" "<<password<<" 300 5 1 0 30 300 300\n";
		}
		outFile.close();
	}
	else {
		cout<<"\n\t\t\t\tPassword do not match! Please Try Again!\n\n";
		Sleep(3000);
		system("cls");
		goto signupMenu;
	}
	loginSignupMenu();

}
int loginSignupMenu(){
	menu:
		system("cls");
	cout<<"\t\t\t\tWELCOME TO LORIEN";
	cout<<"\n\n\t\t\t\t[1]Login\n\t\t\t\t[2]Signup\n\t\t\t\t[3]Exit\n \n\t\t\t\tYour choice: ";
	char choice;
	cin>>choice;
	system("cls");
	switch(choice){
		case '1':{
			login();
			break;
		}
		case '2':{
			signup();
			break;
		}
		case '3':{
			exit(0);
			break;
		}
		default:{
			cout<<"\n\n\t\t\t\tINVALID INPUT! PLEASE TRY AGAIN\n\n";
			Sleep(1500);
			goto menu;
			break;
		}
	}
}

int main(){
	system("Color E1");
first_screen_logo();
  Sleep(3000);
  system("cls");
  loginSignupMenu();

}
