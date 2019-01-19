/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include "Point.h"
#include <time.h>
#include <cmath>
#include "graphviewer.h"
#include "utilities.h"
using namespace std;

class Edge;
class Graph;






const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

class Vertex {
	Point info;
	vector<Edge > adj;
	bool visited;
	bool visited2;
	bool processing;
	int indegree;
	double dist;
public:

	Vertex(Point in);
	friend class Graph;

	void addEdge(Vertex *dest, double w);
	bool removeEdgeTo(Vertex *d);

	Point getInfo() const;
	void setInfo(Point info);

	int getDist() const;
	int getIndegree() const;

	bool operator<(const Vertex vertex);

	Vertex* path;


};




/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

class Edge {
	Vertex * dest;
	double weight;
	string name;
public:
	Edge(Vertex *d, double w);
	Edge(Vertex *d, double w, string nam);
	friend class Graph;
	friend class Vertex;
	void setWeight(double weight){this->weight=weight;};

};








/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
class Graph {
	vector<Vertex *> vertexSet;
	void dfs(Vertex *v, vector<Point> &res) const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, double w);

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex *v);
	void dfsVisit();
	void getPathTo(Vertex *origin, list<Point> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

public:
	//void addEdgeVertex(const Point & sourc, const Point & dest, double w, string name);
	bool removeVertex(const Point &in);
	bool removeEdge(const Point &sourc, const Point &dest);
	vector<Point> dfs() const;
	vector<Point> bfs(Vertex *v) const;
	vector<Vertex * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex* getVertex(const Point &v) const;
	void resetIndegrees();
	vector<Vertex*> getSources() const;
	int getNumCycles();
	vector<Point> getPath(const Point &origin, const Point &dest);
	bool isDAG();

	//exercicio 6
	void dijkstraShortestPath(const Point &s);


	//new functions
	void resetVisit();
	Graph clone();
	void setConnected();
	void setHeight();
	vector<pair<int,int>> setID();
	void write_to_files(const string & nodes,const string & edges);
	bool addPoint(Point & in);
	bool addEdgePoint(const int sourc, const int dest, double w);
	void setShare(int id);



};







#endif /* GRAPH_H_ */
