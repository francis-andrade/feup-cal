#ifndef APP_H_
#define APP_H_

#include <string>
#include<iostream>
#include <vector>
#include "Graph.h"
#include "User.h"
#include "Road.h"
using namespace std;

class App{

	const int nmaps=2;
	bool leaveprogram;//boolean that will tell the program when to leave
	static App * singleton_instance;//pointer to instance of class app
	const string filename_users="resources/users.txt";//users filename
	const vector<string> filename_nodes={"resources/nodes.txt", "resources/nodesLisboa.txt"};//nodes filename
	const vector<string> filename_edges={"resources/edges.txt", "resources/edgesLisboa.txt"};//edges filename
	const vector<string> filename_roads={"resources/roads.txt", "resources/roadsLisboa.txt"};
	const vector<string> filename_osmnodes={"resources/osmnodes.txt","resources/osmnodesLisboa.txt"};
	const vector<string> filename_osmroads={"resources/osmroads.txt","resources/osmroadsLisboa.txt"};
	const vector<string> filename_osmsubroads={"resources/osmsubroads.txt","resources/osmsubroadsLisboa.txt"};
	const vector<string> filename_map={"resources/map.png","resources/mapLisboa.png"};
	vector<User> v_users;
	vector<Graph> gr;
	vector<vector<Road>> v_roads;
	vector<vector<int>> v_ind_to_share;
	vector<vector<int>> v_ind_to_discount;
	vector<GraphViewer *> gv;
	vector<int> gv_first;
	vector<int> gv_last;
	App();//constructor
	~App();//destructor
public:
	const vector<long long> lat_max={41204000, 39150000};
	const vector<long long> lat_min={41168200, 38358000};
	const vector<long long> longt_max={-8592300, -8458000};
	const vector<long long> longt_min={-8666900, -9630620};
	static App * getinstance();//gets instance of class Club
	bool getleaveprogram() const{return leaveprogram;};//gets leaveprogram
	void setleaveprogram(bool leaveprogram){this->leaveprogram=leaveprogram;}//sets leaveprogram
	string getfilename_users() const{return this->filename_users;}//gets filename_users
	string getfilename_nodes(int map_ind) const{if(map_ind<nmaps) return this->filename_nodes[map_ind]; else return "";}//gets filename_nodes
	string getfilename_edges(int map_ind) const{if(map_ind<nmaps) return this->filename_edges[map_ind]; else return "";}//gets filename_edges
	string getfilename_osmnodes(int map_ind) const{if(map_ind<nmaps) return this->filename_osmnodes[map_ind]; else return "";};
	string getfilename_osmroads(int map_ind) const{if(map_ind<nmaps) return this->filename_osmroads[map_ind]; else return "";};
	string getfilename_osmsubroads(int map_ind) const{if(map_ind<nmaps) return this->filename_osmsubroads[map_ind]; else return "";};
	vector<User> getv_users() const{return v_users;}
	vector<Road> getv_roads(int map_ind) const{if(map_ind<nmaps)return v_roads[map_ind];};
	Graph getGraph(int map_ind) const{if(map_ind<nmaps) return gr[map_ind]; };
	vector<int> getv_ind_to_share(int map_ind) const{if(map_ind<nmaps)return v_ind_to_share[map_ind]; else return vector<int>();};
	vector<int> getv_ind_to_discount(int map_ind) const{if(map_ind<nmaps)return v_ind_to_discount[map_ind]; else return vector<int>();};
	void setv_users(const vector<User> & v_users){this->v_users=v_users;};
	void setv_roads(int map_ind, const vector<Road> & v_roads){if(map_ind<nmaps)this->v_roads[map_ind]=v_roads;};

	void readosmfiles(int map_id);
	void read_from_files(int map_id);
	void readusersfile();
	void readroadsfile(int map_id);
	void writeusers();
	void writeroads(int map_id);
	void printGraph(int map_id);
	int calculateshortestpath(long long lat, long long longt, int map_id);
	vector<int> exactsearch(const string & name, int map_id);
	vector<pair<int, string>> approximatesearch(const string & name, int map_id);

};

#endif
