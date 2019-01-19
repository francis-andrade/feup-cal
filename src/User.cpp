#include "User.h"

int User::last_id=0;

User::User(string name, int balance, string credit_number){
	this->name=name;
	this->balance=balance;
	this->credit_number=credit_number;
	last_id++;
	this->id=last_id;
}

User::User(string name, int balance, string credit_number, int id){
	this->name=name;
	this->balance=balance;
	this->credit_number=credit_number;
	this->id=id;
}
