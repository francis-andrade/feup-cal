#ifndef ROAD_H_
#define ROAD_H_
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Road{
	string name;
	vector<Point> points;
public:
	Road(){};
	Road(const string & name){this->name=name;};
	Road(const string & name,const vector<Point> & points){this->name=name; this->points=points;};
	string getName() const {return name;};
	void setName(const string & name){this->name=name;};
	vector<Point> getPoints()  const {return points;};
	void setPoints(const vector<Point> & points){this->points=points;};
	void addPoint(const Point & point){points.push_back(point);};
};



#endif
