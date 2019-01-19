#include "Point.h"
#include "cmath"

#define PI 3.14159265359
#define EARTH_RADIUS 6731000

Point::Point(){
	this->lat=0;
	this->longt=0;
	this->share=false;
	this->height=0;
	this->id=-1;
	this->discount=false;
}

Point::Point(long long lat, long long longt, bool share){
		this->lat=lat;
		this->longt=longt;
		this->share=share;
		this->height=0;
		this->id=-1;
		this->discount=0;
}

Point::Point(long long lat, long long longt, int height, bool share, int id){
	this->lat=lat;
	this->longt=longt;
	this->share=share;
	this->height=height;
	this->id=id;
	this->discount=false;
}

Point::Point(long long lat, long long longt, int height, bool share, int id, bool discount){
	this->lat=lat;
	this->longt=longt;
	this->share=share;
	this->height=height;
	this->id=id;
	if(share){
		this->discount=discount;
	}
}

void Point::setPoint(const Point & p){
	this->lat=p.lat;
	this->longt=p.longt;
	this->share=p.share;
	this->height=p.height;
	this->id=p.id;
	this->discount=p.discount;
}

bool Point::operator==(const Point & p){
	if(lat==p.lat && longt==p.longt && share==p.share && height==p.height && id==p.id && discount==p.discount){
		return true;
	}
	else{
		return false;
	}
}

double dist(const Point & a,const Point & b){
	/*double dlat=(((double) (a.getLat()-b.getLat()))/Point::multiplier)*PI/180;
	double dlongt=(((double) (a.getLongt()-b.getLongt()))/Point::multiplier)*PI/180;
	double res=sqrt(EARTH_RADIUS*(dlat*dlat+dlongt*dlongt));*/
	double dLat=(((double) (a.getLat()-b.getLat()))/Point::multiplier)*PI/180;
	double dLon	=(((double) (a.getLongt()-b.getLongt()))/Point::multiplier)*PI/180;
	  double x =
	    sin(dLat/2) * sin(dLat/2) +
	    cos((((double) a.getLat())/Point::multiplier)*PI/180) * cos((((double) b.getLat())/Point::multiplier)*PI/180) *
	    sin(dLon/2) * sin(dLon/2)
	    ;
	  double c = 2 * atan2(sqrt(x), sqrt(1-x));
	  double d = EARTH_RADIUS * c; // Distance in m
	  return d;

}
