#ifndef MENUS_H_
#define MENUS_H_

#include"Graph.h"
#include "User.h"

void initialmenu();
void askmapactualizemenu();
void actualize_graph(int map_id);
void read_files();
void usermenu();
void regnewuser();
void loginmenu();
void askmapmenu(int user_id);
void mainmenu(int user_id, int map_id);
void searchmenu(int user_id, int map_id);
void exactsearchmenu(int map_id);
void approximatesearchmenu(int map_id);
void depositmenu(int user_id);
void askcoordinatesmenu(int user_id, int map_id);
void menupath(int user_id, long long lat, long long longt, int map_id);





#endif
