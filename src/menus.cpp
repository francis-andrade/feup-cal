#include<vector>
#include<fstream>
#include<string>
#include <iostream>
#include "menus.h"
#include "utilities.h"
#include <fstream>
#include "App.h"
#include "User.h"
#include <vector>
using namespace std;


void initialmenu(){
	App *app = App::getinstance(); //gets intance of class app
	bool repeat=false;
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			cout << "	Initial Menu - Bike Sharing\n" << endl;
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}

			cout << "1: Proceed to the app" << endl;
			cout << "2: Leave" << endl;
			cout << "3: Actualize the graph information" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{

			case 1:
				read_files();
				repeatmenu = false;
				break;
			case 2:
				repeatmenu = false;
				app->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			case 3:
				askmapactualizemenu();
				repeat=true;
				repeatmenu = false;
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!app->getleaveprogram() && repeat);
}

void askmapactualizemenu(){
	App *app = App::getinstance(); //gets intance of class app
	bool repeat=false;
	bool backflag=false;
		do {
			bool errormessage = false;//If true will display an error message
			bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
			while (repeatmenu) {
				system(CLEAR);// clears the screen
				if (errormessage) {
					cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
				}
				cout<<"Beware. If you go ahead and decide to actualize the graph, you are going to  loose information\n"
							<<"about the bike sharing points and you will have to edit them manually.\n"
							<<"This is a demonstrational feature, we recommend you to leave\n\n";
				cout<<"Choose the map that you want to actualize: "<<endl;
				cout << "1: FEUP Area Map" << endl;
				cout << "2: Lisbon Map" << endl;
				cout << "3: Back" << endl;
				cout << "Type the option number: ";
				string option;//option to be chosen by the user
				cin.clear();
				getline(cin, option);
				switch (convint(option))
				{
				case 1:
					actualize_graph(0);
					repeatmenu = false;
					break;
				case 2:
					actualize_graph(1);
					repeatmenu = false;
					break;
				case 3:
					repeatmenu = false;
					backflag=true;
					break;
				default:
					errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
				}
			}
		} while (!app->getleaveprogram() && repeat && !backflag);
}

void actualize_graph(int id){
	system(CLEAR);

	App *app = App::getinstance(); //gets intance of class Club
	if(!app->getleaveprogram()){
		app->readosmfiles(id);
		read_files();
	}
}

void read_files(){
	App *app = App::getinstance(); //gets intance of class Club
	cout<<"Loading..."<<endl;
	app->read_from_files(0);
	app->readroadsfile(0);
	app->read_from_files(1);
	app->readroadsfile(1);
	usermenu();
}


void usermenu(){
	App *app = App::getinstance(); //gets intance of class Club
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			cout << "Bike Sharing\n" << endl;
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "1: Log in" << endl;
			cout << "2: Sign Up" << endl;
			cout << "3: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				loginmenu();
				repeatmenu = false;
				break;
			case 2:
				regnewuser();
				repeatmenu = false;
				break;
			case 3:
				repeatmenu = false;
				app->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!app->getleaveprogram());

}

void regnewuser(){
	App *app = App::getinstance();//gets intance of class app
	bool cancelflag = false;//if true it is going cancel
	bool errormessage = false;//if true it's going to display an errormessage
	bool successflag = false;//if true it means that the user was able to introduce the input successfully
	string user_name;//name of the player
	while (!cancelflag && !successflag) {
		system(CLEAR);
		if (errormessage) {
			cout << "The name you introduced is not valid" << endl;
		}
		cout << "Type your name. It must be between 4 and 20 characters (or press c to cancel): ";
		getline(cin, user_name);
		if (user_name == "c") {
			cancelflag = true;
		}
		else if ((user_name.size() >= 4) && (user_name.size() <= 20)) {
			successflag=true;
		}
		else {
			errormessage = true;
		}
	}

	errormessage = false;
	successflag = false;
	string number;
	while (!cancelflag && !successflag) {
		if (errormessage) {
			cout << "The number you introduced is not valid" << endl;
		}
		cout << "Type your credit card number: (or press c to cancel): ";
		getline(cin, number);
		if (number == "c") {
			cancelflag = true;
		}
		else {
			successflag = true;
		}
	}

	int deposit;
	errormessage = false;
	successflag = false;
	while (!cancelflag && !successflag) {
		if (errormessage) {
			cout << "The value you introduced is not valid" << endl;
		}
		cout << "Type the value in euros that you want to deposit in your account (or press c to cancel): ";
		string value;
		getline(cin, value);
		if (convint(value) >= 0) {
			deposit = convint(value);
			successflag = true;
		}
		else if (value == "c") {
			cancelflag = true;
		}
		else {
			errormessage = true;
		}
	}
	if (!cancelflag) {
		User new_user(user_name, deposit, number);
		vector<User> v_users=app->getv_users();
		v_users.push_back(new_user);
		app->setv_users(v_users);
		cout<<"You were registered successfully. Your id is "<<new_user.getID()<<" ."<<endl;
		cout<<"Press any keys to go back: ";
		string keys;
		getline(cin, keys);

	}

}

void loginmenu(){
	App *app = App::getinstance();//gets intance of class app
	bool cancelflag = false;//if true it is going cancel
	while(!app->getleaveprogram() && !cancelflag){
		vector<User> v_users=app->getv_users();
		bool errormessage = false;//if true it's going to display an errormessage
		bool successflag = false;//if true it means that the user was able to introduce the input successfully
		string user_name;//name of the player
		system(CLEAR);
		int id;
		while (!cancelflag && !successflag) {
			if (errormessage) {
				cout << "The ID you introduced is not valid" << endl;
			}
			cout << "Type your ID (or press c to cancel): ";
			string value;
			getline(cin, value);
			if (convint(value) >= 0 && convint(value)<=(int) v_users.size()) {
				id = convint(value);
				successflag = true;
			}
			else if (value == "c") {
				cancelflag = true;
			}
			else {
				errormessage = true;
			}
		}


		errormessage = false;
		successflag = false;
		while (!cancelflag && !successflag) {
			if (errormessage) {
				cout << "The name you introduced is not valid" << endl;
			}
			cout << "Type your name:  (or press c to cancel): ";
			getline(cin, user_name);
			if (user_name == "c") {
				cancelflag = true;
			}
			else if (v_users[id-1].getName()==user_name) {
				successflag=true;
			}
			else {
				errormessage = true;
			}
		}
		if (!cancelflag) {
			//app->setv_users(v_users);
			askmapmenu(id);

		}
	}
}

void askmapmenu(int user_id){
	App *app = App::getinstance();//gets intance of class app

		bool backflag=false;
		do {
			bool errormessage = false;//If true will display an error message
			bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
			while (repeatmenu) {
				system(CLEAR);// clears the screen
				vector<User> v_users=app->getv_users();
				cout << "Hello "<<v_users[user_id-1].getName()<< endl;
				cout<<"Your Balance is currently: "<<v_users[user_id-1].getBalance()<<"€"<<endl;
				if (errormessage) {
					cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
				}
				cout<<"\nSelect the area Map that you want or one of the other options:"<<endl;
				cout << "1: FEUP Area Map" << endl;
				cout<<"2: LISBON Map"<<endl;
				cout<<"3: Make a deposit in your account"<<endl;
				cout << "4: Log in as a different user" << endl;
				cout << "5: Leave" << endl;
				cout << "Type the option number: ";
				string option;//option to be chosen by the user
				cin.clear();
				getline(cin, option);
				switch (convint(option))
				{
				case 1:
					mainmenu(user_id, 0);
					repeatmenu = false;
					break;
				case 2:
					mainmenu(user_id,1);
					repeatmenu=false;
					break;
				case 3:
					depositmenu(user_id);
					repeatmenu=false;
					break;
				case 4:
					backflag=true;
					repeatmenu = false;
					break;
				case 5:
					repeatmenu = false;
					app->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
					break;
				default:
					errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
				}
			}
		} while (!app->getleaveprogram() && !backflag);
}

void mainmenu(int user_id, int map_id){
	App *app = App::getinstance();//gets intance of class app

	bool backflag=false;
	do {
		app->printGraph(map_id);
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			vector<User> v_users=app->getv_users();
			cout << "Hello "<<v_users[user_id-1].getName()<< endl;
			cout<<"Your Balance is currently: "<<v_users[user_id-1].getBalance()<<"€"<<endl;
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\n1: Type your current geographic coordinates" << endl;
			cout<<"2: Search Bike Sharing Points"<<endl;
			cout<<"3: Back"<<endl;
			cout << "4: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				askcoordinatesmenu(user_id, map_id);
				repeatmenu = false;
				break;
			case 2:
				searchmenu(user_id, map_id);
				repeatmenu=false;
				break;
			case 3:
				backflag=true;
				repeatmenu=false;
				break;
			case 4:
				repeatmenu = false;
				app->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!app->getleaveprogram() && !backflag);


}

void searchmenu(int user_id, int map_id){
	App *app = App::getinstance();//gets intance of class app
	bool backflag=false;
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			vector<User> v_users=app->getv_users();
			cout << "Hello "<<v_users[user_id-1].getName()<< endl;
			cout<<"Your Balance is currently: "<<v_users[user_id-1].getBalance()<<"€"<<endl;
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\n1: Exact Search" << endl;
			cout<<"2: Approximate Search"<<endl;
			cout << "3: Back" << endl;
			cout << "4: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				exactsearchmenu(map_id);
				repeatmenu = false;
				break;
			case 2:
				approximatesearchmenu(map_id);
				repeatmenu=false;
				break;
			case 3:
				backflag=true;
				repeatmenu = false;
				break;
			case 4:
				repeatmenu = false;
				app->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!app->getleaveprogram() && !backflag);
}

void exactsearchmenu(int map_id){
	system(CLEAR);// clears the screen
	App *app = App::getinstance();//gets intance of class app
	cout<<"Introduce the name of the street you want to search: ";
	string name;
	getline(cin, name);
	vector<int> shares=app->exactsearch(name, map_id);
	if(shares.size()==0){
		cout<<"Sorry there were no matches"<<endl;
	}
	else {
		cout<<"The following bike sharing points are located at "<<name<<":"<<endl;
		for(unsigned int i=0;i<shares.size();i++){
			cout<<shares[i]<<endl;
		}
	}
	cout<<"Press any keys to go back: ";
	string keys;
	getline(cin, keys);
}

void approximatesearchmenu(int map_id){
	system(CLEAR);// clears the screen
	App *app = App::getinstance();//gets intance of class app
	cout<<"Introduce the name of the street you want to search: ";
	string name;
	getline(cin, name);
	vector<pair<int, string>> shares=app->approximatesearch(name, map_id);
	if(shares.size()==0){
		cout<<"Sorry there were no matches"<<endl;
	}
	else {
		cout<<"Your search resulted in the following points:"<<endl;
		for(unsigned int i=0;i<shares.size();i++){
			cout<<shares[i].first<<": "<<shares[i].second<<endl;
		}
	}
	cout<<"Press any keys to go back: ";
	string keys;
	getline(cin, keys);
}

void depositmenu(int user_id){
	system(CLEAR);
	App *app = App::getinstance();//gets intance of class app
	vector<User> v_users=app->getv_users();
	bool successflag=false;
	bool cancelflag=false;
	while(!cancelflag && !successflag){
		cout<<"\nType the value in euros that you want to put in your account: ";
		string value;
		getline(cin, value);
		if(convint(value)>=0){
			v_users[user_id-1].setBalance(v_users[user_id-1].getBalance()+convint(value));
			app->setv_users(v_users);
			successflag=true;
		}
		else{
			cout<<"The value you typed is not valid"<<endl;
		}
	}
}

void askcoordinatesmenu(int user_id, int map_id){
	system(CLEAR);
	App *app = App::getinstance();//gets intance of class app
	cout<<"Type the coordinates of the place you currently are"<<endl;
	bool errormessage=false;
	bool successflag=false;
	bool cancelflag=false;
	long long lat_int, longt_int;
	while(!successflag && !cancelflag){
		if(errormessage){
			cout<<"The coordinate you introduced is not valid."<<endl;
		}
		cout<<"\nIntroduce the latitude coordinate in degrees (for example "<<((double)(app->lat_min[map_id]+app->lat_max[map_id])/2)/Point::multiplier<<", or press c to cancel)"<<":"<<endl;
		cout<<"Note that the coordinate must be within the range "<<((double) app->lat_min[map_id])/Point::multiplier<<"  ...  "<<((double) app->lat_max[map_id])/Point::multiplier<<endl;
		string integ, dec;
		string lat;
		bool continu=true;
		getline(cin,lat);
		if(lat=="c"){
			cancelflag=true;
			continu=false;
		}
		if((lat.substr(0,3)!="41.") && (lat.substr(0,3)!="38.") && (lat.substr(0,3)!="39.")){
			errormessage=true;
			continu=false;
		}
		else{
			integ=lat.substr(0,2);
			dec=lat.substr(3,lat.size()-3);
			if(convint(dec)<0){
				errormessage=true;
				continu=false;
			}
		}
		if(continu){
			lat=integ+dec;
			lat_int=stoll(lat)*(100000000/smallestpower(10, stoll(lat)));
			if(lat_int>app->lat_max[map_id] || lat_int<app->lat_min[map_id]){
				errormessage=true;
			}
			else{
				successflag=true;
			}
		}
	}
	successflag=false;
	errormessage=false;
	while(!successflag && !cancelflag){
		if(errormessage){
			cout<<"The coordinate you introduced is not valid."<<endl;
		}
		cout<<"\nIntroduce the longitude coordinate in degrees (for example "<<((double)(app->longt_min[map_id]+app->longt_max[map_id])/2)/Point::multiplier<<", or press c to cancel)"<<":"<<endl;
		cout<<"Note that the coordinate must be within the range "<<((double) app->longt_min[map_id])/Point::multiplier<<"  ...  "<<((double) app->longt_max[map_id])/Point::multiplier<<endl;
		string integ, dec;
		string longt;
		bool continu=true;
		getline(cin,longt);
		if(longt=="c"){
			cancelflag=true;
			continu=false;
		}
		if(longt.substr(0,3)!="-8." && longt.substr(0,3)!="-9."){
			errormessage=true;
			continu=false;
		}
		else{
			integ=longt.substr(1,1);
			dec=longt.substr(3,longt.size()-3);
			if(convint(dec)<0){
				errormessage=true;
				continu=false;
			}
		}
		if(continu){
			longt=integ+dec;
			longt_int=-stoll(longt)*(10000000/smallestpower(10, stoll(longt)));
			if(longt_int>app->longt_max[map_id] || longt_int<app->longt_min[map_id]){
				errormessage=true;
			}
			else{
				successflag=true;
			}
		}
	}
	if(!cancelflag){
		menupath(user_id, lat_int, longt_int, map_id);
	}

}

void menupath(int user_id, long long lat, long long longt, int map_id){
	system(CLEAR);
	App *app = App::getinstance();//gets intance of class app
	int ind=app->calculateshortestpath(lat, longt, map_id);
	vector<int> v_ind_to_discount=app->getv_ind_to_discount(map_id);
	vector<int> v_ind_to_share=app->getv_ind_to_share(map_id);
	vector<User> v_users=app->getv_users();
	bool errormessage=false;
	bool cancelflag=false;
	bool successflag=false;
	do{
		system(CLEAR);
		cout<<"The closest bike sharing Point, taking height into account is"<<endl;
		cout<<"the Point number "<<ind<<endl;
		cout<<"The path to this Point is shown on the map."<<endl;
		cout<<"Still, remember that the points marked with "<<endl;
		cout<<"Discount have a 50% discount:"<<endl;
		cout<<"Normal price: 2€"<<endl;
		cout<<"Discount price: 1€"<<endl;
		if(errormessage){
			cout<<"The point you typed is not valid"<<endl;
		}
		cout<<"\nType the number of the Point where you want to leave your bike (press c to cancel) : ";
		string point;
		getline(cin, point);
		if(point=="c"){
			cancelflag=true;
		}
		else if(convint(point)>=1 && convint(point)<(int) v_ind_to_share.size()){
			int cost;
			if(find(v_ind_to_discount.begin(),v_ind_to_discount.end(),convint(point))!=v_ind_to_discount.end()){
				cost=1;
			}
			else{
				cost=2;
			}
			if(v_users[user_id-1].getBalance()-cost>=0){
				v_users[user_id-1].setBalance(v_users[user_id-1].getBalance()-cost);
				app->setv_users(v_users);
				successflag=true;
			}
			else{
				cout<<"You don't have enough money ."<<endl;
				cout<<"You need to make a deposit before being able to leave the bike there"<<endl;
				cout<<"Press any keys to go back: ";
				string keys;
				getline(cin, keys);
			}
		}
		else{
			errormessage=true;
		}
	}while(!cancelflag && !successflag);

}
