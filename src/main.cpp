/*
 * main.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: franc
 */

#include <iostream>
//#include "Point.h"
#include "menus.h"
#include<fstream>
#include "App.h"
using namespace std;




int main(){
	App *app = App::getinstance();//gets intance of class app
	app->readusersfile();
	initialmenu();
	app->writeusers();
	return 0;
}


