#include "Graph.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

/* ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

struct vertex_greater_than {
    bool operator()(Vertex * a, Vertex * b) const {
        return a->getDist() > b->getDist();
    }
};



bool Vertex::removeEdgeTo(Vertex *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge >::iterator it= adj.begin();
	typename vector<Edge >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercício 5

Vertex::Vertex(Point in): info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}



void Vertex::addEdge(Vertex *dest, double w) {
	Edge edgeD(dest,w);
	adj.push_back(edgeD);
}

//--

Point Vertex::getInfo() const {
	return this->info;
}


int Vertex::getDist() const {
	return this->dist;
}



void Vertex::setInfo(Point info) {
	this->info = info;
}


int Vertex::getIndegree() const {
	return this->indegree;
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
Edge::Edge(Vertex *d, double w): dest(d), weight(w), name(""){}

Edge::Edge(Vertex *d, double w, string nam): dest(d), weight(w), name(nam){}

/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
int Graph::getNumVertex() const {
	return vertexSet.size();
}


vector<Vertex * > Graph::getVertexSet() const {
	return vertexSet;
}


int Graph::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}


bool Graph::isDAG() {
	return (getNumCycles() == 0);
}


bool Graph::addVertex(const Point &in) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex *v1 = new Vertex(in);
	vertexSet.push_back(v1);
	return true;
}


bool Graph::removeVertex(const Point &in) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex*>::iterator it1= vertexSet.begin();
			typename vector<Vertex*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge >::iterator itAdj= v->adj.begin();
			typename vector<Edge >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}


bool Graph::addEdge(const Point &sourc, const Point &dest, double w) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD,w);

	return true;
}


bool Graph::removeEdge(const Point &sourc, const Point &dest) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}





vector<Point> Graph::dfs() const {
	typename vector<Vertex*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<Point> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}


void Graph::dfs(Vertex *v,vector<Point> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge >::iterator it= (v->adj).begin();
	typename vector<Edge >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false ){
	    	//cout << "ok ";
	    	dfs(it->dest, res);
	    }
}


vector<Point> Graph::bfs(Vertex *v) const {
	vector<Point> res;
	queue<Vertex *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge >::iterator it=v1->adj.begin();
		typename vector<Edge >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}





Vertex* Graph::getVertex(const Point &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}


void Graph::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}



vector<Vertex*> Graph::getSources() const {
	vector< Vertex* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}



void Graph::dfsVisit() {
	typename vector<Vertex*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfsVisit(*it);
}


void Graph::dfsVisit(Vertex *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge >::iterator it= (v->adj).begin();
	typename vector<Edge >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
	    if ( it->dest->visited == false ){
	    	dfsVisit(it->dest);
	    }
	}
	v->processing = false;
}



vector<Point> Graph::getPath(const Point &origin, const Point &dest){

	list<Point> buffer;
	Vertex* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  !(v->path->info == origin)) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<Point> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}







void Graph::dijkstraShortestPath(const Point &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex* v = getVertex(s);
	v->dist = 0;

	vector< Vertex* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());


	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex* w = v->adj[i].dest;

			if(v->dist + v->adj[i].weight < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if(!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap (pq.begin(),pq.end(),vertex_greater_than());
			}
		}
	}

}





//new functions

void Graph::resetVisit(){
	for(unsigned int i=0;i<vertexSet.size();i++){
		vertexSet[i]->visited=false;
	}
}

Graph Graph::clone()
{
	Graph ret;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++){
		Vertex * v = new Vertex(this->vertexSet[i]->info);
		ret.vertexSet.push_back(v);
	}

	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		vector<Edge> edges = this->vertexSet[i]->adj;
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->info, edges[a].dest->info, edges[a].weight);
	}

	return ret;
}


void Graph::setConnected(){
	Graph g=this->clone();
		for(unsigned int i=0;i<g.vertexSet.size();i++){
			for(unsigned int j=0;j<g.vertexSet[i]->adj.size();j++){
				g.vertexSet[i]->adj[j].dest->addEdge(g.vertexSet[i],0);
			}
		}
		vector<Point> found;
		vector<Point> max_con;
		while(found.size()<g.vertexSet.size()){
			int i=0;
			while(g.vertexSet[i]->visited){
				i++;
			}
			vector<Point> r;
			g.dfs(g.vertexSet[i],r);
			if(max_con.size()<r.size()){
				max_con=r;
			}
			found.insert(found.end(),r.begin(),r.end());
		}

		for(unsigned int i=0;i<vertexSet.size();i++){
			if(find(max_con.begin(),max_con.end(),vertexSet[i]->info)==max_con.end()){
				this->removeVertex(vertexSet[i]->info);
				i--;
			}
		}
		this->resetVisit();
}





void Graph::setHeight(){
		if(vertexSet.size()==0){
			return;
		}
		srand(time(0));
		stack<Vertex *> st;
		vertexSet[0]->info.setHeight(0);
		st.push(vertexSet[0]);
		while(!st.empty()){
				Vertex * v_new=st.top();
				int height=v_new->info.getHeight();
				st.pop();
				for(unsigned int i=0;i<v_new->adj.size();i++){
					if(v_new->adj[i].dest->visited==false){
						int r=rand()%3;
						if(r==0){
							v_new->adj[i].dest->info.setHeight(height+2);
						}
						else if(r==1){
							v_new->adj[i].dest->info.setHeight(height);
						}
						else if(r==2){
							if(height-2>0){
								v_new->adj[i].dest->info.setHeight(height-2);
							}
							else{
								v_new->adj[i].dest->info.setHeight(0);
							}
						}
						st.push(v_new->adj[i].dest);
						v_new->adj[i].dest->visited=true;

					}
				}
			}
		for(unsigned int i=0;i<vertexSet.size();i++){
			for(unsigned int j=0;j<vertexSet[i]->adj.size();j++){
				vertexSet[i]->adj[j].weight=max(vertexSet[i]->adj[j].weight+vertexSet[i]->adj[j].dest->info.getHeight()-vertexSet[i]->info.getHeight(),0.1);
			}
		}
}


vector<pair<int,int>>  Graph::setID(){
	vector<pair<int, int>> r;
	for(unsigned int i=0;i<vertexSet.size();i++){
		r.push_back(pair<int, int>(vertexSet[i]->info.getID(),i));
		vertexSet[i]->info.setID(i);
	}
	return r;
}


void Graph::write_to_files(const string & nodes,const string & edges){
			ofstream f_nodes(nodes);
			for(unsigned int i=0;i<vertexSet.size();i++){

				f_nodes<<vertexSet[i]->info.getID()<<";"<<vertexSet[i]->info.getLat()<<";"<<vertexSet[i]->info.getLongt()<<";"
				       <<vertexSet[i]->info.getHeight()<<";"<<vertexSet[i]->info.getShare()<<";"<<vertexSet[i]->info.getDiscount()<<"\n";
			}
			ofstream f_edges(edges);

			for(unsigned int i=0;i<vertexSet.size();i++){
				for(unsigned int j=0;j<vertexSet[i]->adj.size();j++){

					f_edges<<vertexSet[i]->info.getID()<<" ; "<<vertexSet[i]->adj[j].dest->info.getID()<<";"<<vertexSet[i]->adj[j].weight<<";\n";
				}
			}
}


bool Graph::addPoint(Point & in){
	if(in.getID()==-1){
		in.setID(vertexSet.size());
		Vertex * v1=new Vertex(in);
		vertexSet.push_back(v1);
		return false;
	}
	else if((int) vertexSet.size()!= in.getID()){
		return false;
	}
	else{
		Vertex *v1 = new Vertex(in);
		vertexSet.push_back(v1);
		return true;
	}
}

bool Graph::addEdgePoint(const int sourcID, const int destID, double w){
	if(((int) vertexSet.size()<=sourcID) || ((int) vertexSet.size()<=destID) || (sourcID<0) || (destID<0)){
		return false;
	}
	else if((vertexSet[sourcID]->info.getID()!=sourcID) || (vertexSet[destID]->info.getID()!=destID)){
		return false;
	}
	else{
		Vertex * vD=vertexSet[destID];
		Vertex * vS=vertexSet[sourcID];
		vD->indegree++;
		vS->addEdge(vD,w);
		return true;
	}
}


void Graph::setShare(int id){
	if(id<0 || id>=((int) vertexSet.size())){
		return;
	}
	else{
		vertexSet[id]->info.setShare(true);
	}
}

