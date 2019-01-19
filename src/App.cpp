#include "App.h"
#include <iostream>
#include "Point.h"
#include "utilities.h"
#include<fstream>
#include"Road.h"
using namespace std;


#define FEUP_NPOINTS 17
#define MIN_DIST 20

App * App::singleton_instance = NULL; //Initially singleton_instance points to null

/*
 * Private Default Constructor
 */
App::App():gr(nmaps),   v_roads(nmaps), v_ind_to_share(nmaps), v_ind_to_discount(nmaps), gv(nmaps,NULL), gv_first(nmaps,-1), gv_last(nmaps,-1)
		{
	leaveprogram = false;

}

/*
 *Private Destructor
 */
App::~App() {

	delete singleton_instance;
	singleton_instance = NULL;
}

/*
 Gets instance of Club Class
 */
App * App::getinstance() {
	if (!singleton_instance) {
		singleton_instance = new App;
	}
	return singleton_instance;
}

struct osm_node{
	long long id;
	long long lat;
	long long longt;
};


struct osm_subroad{
	long long id;
	long long origin;
	long long dest;
	long long height;
};

struct osm_road{
	long long id;
	bool twoway;
	string name;
};

bool comp(const osm_node & a,const osm_node & b){
	return a.id<b.id;
}

int binary_search(const vector<osm_node> & v_nodes, long long id){
   int lo = 0;
   int hi = v_nodes.size()-1;
   while (lo <= hi){
      int mid = lo + (hi-lo)/2;
      if (v_nodes[mid].id == id){
         return mid;}
      else if (v_nodes[mid].id < id){
         lo = mid+1;
      }
      else{
         hi = mid-1;
      }
      }
   return -1;
}

int binary_search(const vector<Point> & v_points, long long id){
	int lo = 0;
	   int hi = v_points.size()-1;
	   while (lo <= hi){
	      int mid = lo + (hi-lo)/2;
	      if (v_points[mid].getID() == id){
	         return mid;}
	      else if (v_points[mid].getID() < id){
	         lo = mid+1;
	      }
	      else{
	         hi = mid-1;
	      }
	      }
	   return -1;
}


void App::readosmfiles(int map_id){
	string roads=this->filename_osmroads[map_id];
	string subroads=this->filename_osmsubroads[map_id];
	string nodes=this->filename_osmnodes[map_id];
	vector<osm_node> v_nodes;
	ifstream f_nodes(nodes);
	osm_node node;
	while(f_nodes>>node.id){

		char c;
		f_nodes>>c;
		string integ, dec;
		getline(f_nodes,integ,'.');
		getline(f_nodes, dec, ';');
		string lat=integ+dec;

		if(smallestpower(10, stoll(dec))>1000000){
			cout<<"\nERRO\nERRO\nERRO\n";
		}
		node.lat=stoll(lat)*(100000000/smallestpower(10, stoll(lat)));
		f_nodes>>c;
		getline(f_nodes,integ,'.');
		getline(f_nodes, dec, ';');
		string longt=integ+dec;
		node.longt=-stoll(longt)*(10000000/smallestpower(10, stoll(longt)));
		string s;
		getline(f_nodes, s);
		if(node.lat>=lat_min[map_id] && node.lat<=lat_max[map_id] && node.longt>=longt_min[map_id] && node.longt<=longt_max[map_id]){
			v_nodes.push_back(node);
		}
	}
	ifstream f_roads(roads);
	vector<osm_road> v_roads;
	osm_road road;
	while(f_roads>>road.id){
		char c;
		string s;
		f_roads>>c;
		getline(f_roads, road.name, ';');
		f_roads>>c;
		if(c=='F'){
			road.twoway=true;
		}
		else{
			road.twoway=false;
		}
		getline(f_roads, s);
		v_roads.push_back(road);
	}
	sort(v_nodes.begin(),v_nodes.end(),comp);
	ifstream f_subroads(subroads);
	osm_subroad subroad;
	int i=0;
	vector<bool> chosen(v_nodes.size(),false);
	vector<Point> points(v_nodes.size());
	vector<Road> v_real_roads;
	while((f_subroads>>subroad.id)){
		char c;
		string s;
		f_subroads>>c>>subroad.origin>>c>>subroad.dest>>c;
		getline(f_subroads, s);
		bool twoway;
		while(subroad.id!=v_roads[i].id){
			i=(i+1)%v_roads.size();
		}
		twoway=v_roads[i].twoway;
		bool roadalready=false;
		int posalready=-1;
		for(unsigned int j=0;j<v_real_roads.size();j++){
			if(v_real_roads[j].getName()==v_roads[i].name){
				roadalready=true;
				posalready=j;
				break;
			}
		}
		if(roadalready==false && v_roads[i].name!=""){
			v_real_roads.push_back(Road(v_roads[i].name));
			posalready=v_real_roads.size()-1;
		}
		Point src, dest;
		int origin_id=binary_search(v_nodes, subroad.origin);
		int dest_id=binary_search(v_nodes, subroad.dest);
		if(origin_id!=-1 && dest_id!=-1){
			if(chosen[origin_id]==false){
				src.setPoint(Point(v_nodes[origin_id].lat, v_nodes[origin_id].longt, false));
				gr[map_id].addPoint(src);
				chosen[origin_id]=true;
				points[origin_id].setPoint(src);
				if(posalready!=-1){
					v_real_roads[posalready].addPoint(src);
				}
			}
			else{
				src.setPoint(points[origin_id]);
				if(posalready!=-1){
					if(roadalready){
						vector<Point> road_points=v_real_roads[posalready].getPoints();
						bool point_found=false;
						for(unsigned int j=0;j<road_points.size();j++){
							if(road_points[j]==src){
								point_found=true;
								break;
							}
						}
						if(point_found==false){
							road_points.push_back(src);
							v_real_roads[posalready].setPoints(road_points);
						}
					}
				}
			}
			if(chosen[dest_id]==false){
					dest.setPoint(Point(v_nodes[dest_id].lat, v_nodes[dest_id].longt, false));
					gr[map_id].addPoint(dest);
					chosen[dest_id]=true;
					points[dest_id].setPoint(dest);
					if(posalready!=-1){
						v_real_roads[posalready].addPoint(dest);
					}
			}
			else{
					dest.setPoint(points[dest_id]);
					if(posalready!=-1){
						if(roadalready){
							vector<Point> road_points=v_real_roads[posalready].getPoints();
							bool point_found=false;
							for(unsigned int j=0;j<road_points.size();j++){
								if(road_points[j]==dest){
									point_found=true;
									break;
								}
							}
							if(point_found==false){
								road_points.push_back(dest);
								v_real_roads[posalready].setPoints(road_points);
							}
						}
					}
			}

			if(twoway){
				gr[map_id].addEdgePoint(src.getID(), dest.getID(), dist(src, dest));
				gr[map_id].addEdgePoint(dest.getID(), src.getID(), dist(src, dest));
			}
			else{
				gr[map_id].addEdgePoint(src.getID(), dest.getID(), dist(src, dest));
			}
		}
		else{
			cout<<"ERRO "<<subroad.origin<<" "<<subroad.dest<<endl;
		}
	}
	if(map_id==0){
		int maxID=gr[map_id].getNumVertex();
		gr[map_id].setConnected();
		gr[map_id].setHeight();
		vector<pair<int, int>> v=gr[map_id].setID();
		vector<int> old_to_new(maxID, -1);
		for(unsigned int i=0;i<v.size();i++){
			old_to_new[v[i].first]=v[i].second;
		}
		for(unsigned int i=0;i<v_real_roads.size();i++){
			vector<Point> road_points=v_real_roads[i].getPoints();
			for(unsigned int j=0;j<road_points.size();j++){
				if(old_to_new[road_points[j].getID()]==-1){
					road_points.erase(road_points.begin()+j);
					j--;
				}
				else{
					road_points[j].setID(old_to_new[road_points[j].getID()]);
				}
			}
			if(road_points.size()==0){
				v_real_roads.erase(v_real_roads.begin()+i);
				i--;
			}
			else{
				v_real_roads[i].setPoints(road_points);
			}
		}
	}
	else if(map_id==1){
		vector<Vertex *> vertexes=gr[map_id].getVertexSet();
		vector<int> crossroads(gr[map_id].getNumVertex(),0);
		for(unsigned int i=0;i<v_real_roads.size();i++){
			vector<Point> road_points=v_real_roads[i].getPoints();
			for(unsigned int j=0;j<road_points.size();j++){
				crossroads[road_points[j].getID()]++;
			}
		}
		for(unsigned int i=0;i<crossroads.size();i++){
			if(crossroads[i]>1){
				bool found=false;
				for(int j=((int) i)-1;j>=0;j--){
					if(vertexes[j]->getInfo().getShare() && dist(vertexes[i]->getInfo(),vertexes[j]->getInfo())<400){
						found=true;
						break;
					}
				}
				if(!found){
					gr[map_id].setShare(i);
				}
			}
		}
	}
	gr[map_id].write_to_files(filename_nodes[map_id], filename_edges[map_id]);
	this->setv_roads(map_id, v_real_roads);
	this->writeroads(map_id);
}

void App::read_from_files(int map_id){
	string nodes=this->filename_nodes[map_id];
	string edges=this->filename_edges[map_id];

	ifstream f_nodes(nodes);
	ifstream f_edges(edges);
	int id;
	vector<Point> v_points;
	v_ind_to_share[map_id].clear();
	v_ind_to_share[map_id].push_back(0);
	int k=1;
	while(f_nodes>>id){
		long long lat, longt;
		int height;
		bool share, discount;
		char c;
		f_nodes>>c>>lat>>c>>longt>>c>>height>>c>>share>>c>>discount;
		string s;
		getline(f_nodes,s);
		v_points.push_back(Point(lat, longt, height, share, id, discount));
		Point p(lat, longt, height, share, id, discount);
		gr[map_id].addPoint(p);

		if(p.getShare()){
			v_ind_to_share[map_id].push_back(p.getID());
			if(p.getDiscount()){
				v_ind_to_discount[map_id].push_back(k);
			}
			k++;
		}
	}
	int id_origin;

	while(f_edges>>id_origin){

		int id_dest;
		char c;
		string integ, dec;
		f_edges>>c>>id_dest>>c;
		double weight;
		string str;
		f_edges>>weight;
		getline(f_edges, str);
		gr[map_id].addEdgePoint(id_origin, id_dest, weight);

	}


}

void App::readusersfile( ){
	ifstream in;
	in.open(filename_users);
	int id;
	while(in>>id){
		char c;
		string name, credit_number, s;
		int balance;
		in>>c;
		getline(in, name, ';');
		getline(in, credit_number, ';');
		in>>balance;
		getline(in,s);
		v_users.push_back(User(name, balance, credit_number, id));

	}
	in.close();
	User::setLast_id(v_users.size());
}

void App::readroadsfile(int map_id){
	ifstream in;
	in.open(filename_roads[map_id]);
	v_roads[map_id].clear();
	vector<Vertex *> g_points=gr[map_id].getVertexSet();
	string name;
	while(getline(in, name, ';')){
		vector<Point> points;
		char c;
		string str;
		int size;
		in>>size;
		in>>c;
		for(int i=0;i<size;i++){
			int id;
			in>>id;
			points.push_back(g_points[id]->getInfo());
			in>>c;
		}
		getline(in, str);
		v_roads[map_id].push_back(Road(name, points));
	}
	in.close();
}

void App::writeusers(){
	ofstream out(filename_users);
	for(unsigned int i=0;i<v_users.size();i++){
		out<<v_users[i].getID()<<";"<<v_users[i].getName()<<";"<<v_users[i].getCredit_number()<<";"<<v_users[i].getBalance()<<";\n";
	}
}

void App::writeroads(int map_id){
	ofstream out(filename_roads[map_id]);
	for(unsigned int i=0;i<v_roads[map_id].size();i++){
		vector<Point> points=v_roads[map_id][i].getPoints();
		out<<v_roads[map_id][i].getName()<<";"<<points.size()<<";";
		for(unsigned int j=0;j<points.size();j++){
			out<<points[j].getID()<<";";
		}
		out<<"\n";
	}
}

void convert_geo_to_cart(long long plat, long long plongt, double & x, double & y, int map_id){
	const vector<long long> lat_max={41204000, 39388400};
	const vector<long long> lat_min={41168200, 38316900};
	const vector<long long> longt_max={-8592300, -8348200};
	const vector<long long> longt_min={-8666900, -9798400};
	const vector<int> map_dim_x={1089, 794};
	const vector<int> map_dim_y={693, 753};
	x= map_dim_x[map_id]*((plongt-longt_min[map_id])/((double) (longt_max[map_id]-longt_min[map_id])));
	y=map_dim_y[map_id]*((lat_max[map_id]-plat)/((double) (lat_max[map_id]-lat_min[map_id])));
}


void App::printGraph(int map_id){
			if(gv[map_id]==NULL){
				const vector<int> map_dim_x={1089, 794};
				const vector<int> map_dim_y={693, 753};
				gv[map_id] = new GraphViewer(map_dim_x[map_id], map_dim_y[map_id], false);
				gv[map_id]->setBackground(filename_map[map_id]);
				gv[map_id]->createWindow(map_dim_x[map_id], map_dim_y[map_id]);
				gv_first[map_id]=-1;
				gv_last[map_id]=-1;
			}
			else{
				for(int i=gv_first[map_id];i<=gv_last[map_id];i++){
					gv[map_id]->removeNode(i);
				}
			}

			gv[map_id]->defineEdgeColor("black");
			gv[map_id]->defineEdgeCurved(false);
			int k=1;
			vector<Vertex *>vertexSet=gr[map_id].getVertexSet();
			for(unsigned int i=0;i<vertexSet.size();i++){
							if(vertexSet[i]->getInfo().getShare()){
								double x,y;
								convert_geo_to_cart(vertexSet[i]->getInfo().getLat(), vertexSet[i]->getInfo().getLongt(), x,y, map_id);
								gv[map_id]->addNode(k+gv_last[map_id]+1, x, y);
								gv[map_id]->setVertexColor(k+gv_last[map_id]+1, "blue");
								gv[map_id]->setVertexSize(k+gv_last[map_id]+1, 10);
								if(vertexSet[i]->getInfo().getDiscount()){
									string s=to_string(k)+"(DISCOUNT)";
									gv[map_id]->setVertexLabel(k+gv_last[map_id]+1, s);
								}
								else{
									string s=to_string(k);
									gv[map_id]->setVertexLabel(k+gv_last[map_id]+1, s);
								}
								k++;
							}
						}
			gv_first[map_id]=gv_last[map_id]+2;
			gv_last[map_id]=gv_first[map_id]+k-2;
			gv[map_id]->rearrange();
}

int App::calculateshortestpath(long long lat, long long longt, int map_id){
	vector<Vertex *>vertexSet=gr[map_id].getVertexSet();
	double min_dist=999999999;
	int ind_min=0;
	Point node;
	vector<bool> alreadychosen(vertexSet.size(),false);
	while(min_dist>=999999999){
		double min=9999999;
		for(unsigned int i=0;i<vertexSet.size();i++){
			double new_dist=dist(vertexSet[i]->getInfo(), Point(lat, longt, false));
			if(new_dist<min && alreadychosen[i]==false){
				node=vertexSet[i]->getInfo();
				min=new_dist;
			}
		}

		gr[map_id].dijkstraShortestPath(node);
		alreadychosen[node.getID()]=true;

		for(unsigned int i=1;i<v_ind_to_share[map_id].size();i++){
			if(vertexSet[v_ind_to_share[map_id][i]]->getDist()<min_dist){
				min_dist=vertexSet[v_ind_to_share[map_id][i]]->getDist();
				ind_min=i;
			}
		}
	}
	double x1,y1;
	convert_geo_to_cart(node.getLat(), node.getLongt(), x1,y1, map_id);
	gv[map_id]->addNode(0+gv_first[map_id]-1, x1, y1);
	gv[map_id]->setVertexColor(0+gv_first[map_id]-1, "red");
	gv[map_id]->setVertexLabel(0+gv_first[map_id]-1, "You are here");
	gv[map_id]->setVertexSize(0+gv_first[map_id]-1, 10);
	gv[map_id]->rearrange();
	int i=v_ind_to_share[map_id].size()-1;
	const int numv=v_ind_to_share[map_id].size()-1;
	int j=0;
	if(ind_min!=0){
		Vertex *  v=vertexSet[v_ind_to_share[map_id][ind_min]];
		while(!(v->getInfo()==node)){
			double x,y;
			convert_geo_to_cart(v->getInfo().getLat(), v->getInfo().getLongt(), x,y, map_id);
			if(i>numv){
				gv[map_id]->addNode(i+gv_first[map_id]-1, x, y);
				gv_last[map_id]++;
				gv[map_id]->setVertexColor(i+gv_first[map_id]-1, "black");
				gv[map_id]->clearVertexLabel(i+gv_first[map_id]-1);
				gv[map_id]->setVertexSize(i+gv_first[map_id]-1, 0);

			}
			if(i==numv+1){
				gv[map_id]->addEdge(j,ind_min,i+gv_first[map_id]-1,EdgeType::UNDIRECTED);
				j++;
			}
			if(i>numv+1){
				gv[map_id]->addEdge(j,i-1+gv_first[map_id]-1,i+gv_first[map_id]-1,EdgeType::UNDIRECTED);
				j++;
			}
			i++;
			v=v->path;
		}
	}
	if(i==numv+1){
		gv[map_id]->addEdge(j,ind_min+gv_first[map_id]-1,0+gv_first[map_id]-1,EdgeType::UNDIRECTED);
		j++;
	}
	else{
		gv[map_id]->addEdge(j, (i-1)+gv_first[map_id]-1, 0+gv_first[map_id]-1, EdgeType::UNDIRECTED);
		j++;
	}
	gv[map_id]->rearrange();
	gv_first[map_id]=gv_first[map_id]-1;
	return ind_min;


}



vector<int> App::exactsearch(const string & name, int map_id){
	vector<int> r;
	vector<Road> v_roads=this->v_roads[map_id];
	for(unsigned int i=0;i<v_roads.size();i++){
		if(name==v_roads[i].getName()){
			for(unsigned int j=0;j<v_roads[i].getPoints().size();j++){
				if(v_roads[i].getPoints()[j].getShare()){
					int ind=-1;
					for(unsigned int k=1;k<=v_ind_to_share[map_id].size();k++){
						if(v_ind_to_share[map_id][k]==v_roads[i].getPoints()[j].getID()){
							ind=k;
						}
					}
					r.push_back(ind);
				}
			}
		}
	}
	return r;
}

bool compapproximatesearch(const pair<int,int>  & a, const pair<int, int> & b){
	return a.first<b.first;
}

vector<pair<int, string>> App::approximatesearch(const string & name, int map_id){
	vector<pair<int, string>> v;
	vector<pair<int,int>> v_dist;
	vector<Road> v_roads=this->v_roads[map_id];
	for(unsigned int i=0;i<v_roads.size();i++){
		int dist;
		if((dist=editDistance(name, v_roads[i].getName()))<=MIN_DIST){
			for(unsigned int j=0;j<v_roads[i].getPoints().size();j++){
				if(v_roads[i].getPoints()[j].getShare()){
					int ind=-1;
					for(unsigned int k=1;k<=v_ind_to_share[map_id].size();k++){
						if(v_ind_to_share[map_id][k]==v_roads[i].getPoints()[j].getID()){
							ind=k;
							break;
						}
					}

					v_dist.push_back(pair<int, int>(dist,v.size()));
					v.push_back(pair<int, string>(ind, v_roads[i].getName()));
				}
			}
		}
	}
	sort(v_dist.begin(),v_dist.end(), compapproximatesearch);
	vector<pair<int, string>> r;
	for(unsigned int i=0;i<v_dist.size();i++){
		r.push_back(v[v_dist[i].second]);
	}
	return r;
}
