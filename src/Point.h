/*
 * Point.h
 *
 *  Created on: Apr 5, 2017
 *      Author: franc
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_


class Point{

private:
	long long lat;
	long long longt;
	int height;
	bool share;
	bool discount;
	int id;
public:
	static const int multiplier=1000000;
	Point();
	Point(long long lat, long long longt, bool share);
	Point(long long lat, long long longt, int height, bool share, int id);
	Point(long long lat, long long longt, int height, bool share, int id, bool discount);
	void setPoint(const Point & p);
	bool operator==(const Point & p);
	long long getLat() const{return lat;};
	long long getLongt() const{return longt;};
	bool getShare() const{return share;};
	bool getDiscount() const{return discount;};
	void setHeight(int height){this->height=height;};
	int getHeight() const {return height;};
	int getID() const{return id;};
	void setID(int id) {this->id=id;};
	void setShare(bool share){this->share=share;};
	friend double dist(const Point & a,const Point & b);

};



#endif /* SRC_POINT_H_ */
