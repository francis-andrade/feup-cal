#ifndef USER_H_
#define USER_H_
#include <string>
using namespace std;

class User{
private:
	int balance;
	string name;
	int id;
	string credit_number;
	static int last_id;
public:
	User(string name, int balance, string credit_number);
	User(string name, int balance, string credit_number, int id);
	void setBalance(int balance){this->balance=balance;};
	int getBalance() const{return balance;};
	string getName() const{return name;};
	int getID() const{return id;};
	int getLast_id() const{return last_id;};
	string getCredit_number() const{return credit_number;};
	static void setLast_id(int last_id){User::last_id=last_id;};
};


#endif
