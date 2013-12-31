#ifndef TXT_H_INCLUDE

#define TXT_H_INCLUDE

#include "common.h"

class Txt
{
public:
	Txt(const char * file, Option opt);
	~Txt();
	std::list<Point> getRing();

private:
    Point ReadOnePoint();

	FILE * fp;
	char  seperator;
	char ** fields;
	int x;
	int y;
};

#endif
