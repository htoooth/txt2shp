#ifndef TXT_H_INCLUDE

#define TXT_H_INCLUDE

#include "common.h"

struct Point{
	double x;
	double y;

	Point(double x, double y) :x(x), y(y){

	}
};

class Txt
{
public:
	Txt(const char * file,int x,int y);
	~Txt();
	std::list<Point> getRing();

private:
	Point * ReadOnePoint();

	FILE * fp;
	char  seperator;
	char ** fields;
	int x;
	int y;

};

#endif
