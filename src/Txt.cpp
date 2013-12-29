#include "Txt.h"

/// convert char to char point
/// char to char*
const char * char2p(char c)
{
	return CPLSPrintf("%c", c);
}

FILE * OpenTxt(const char * fileName)
{
	return VSIFOpen(fileName, "r");
}

Txt::Txt(const char * fileName, int x, int y): x(x), y(y)
{
	fp = OpenTxt(fileName);

	if (fp != NULL)
	{
		const char * first = CPLReadLine(fp);
		seperator = CSVDetectSeperator(first);
		fields = CSLTokenizeString2(first, char2p(seperator), CSLT_HONOURSTRINGS);
        // auto detect x,y index
		x = CSLFindString(fields,"x");
		y = CSLFindString(fields,"y");
	}
}

Point * Txt::ReadOnePoint()
{
	char ** values = CSVReadParseLine2(fp, seperator);

	if (values == NULL)
	{
		return NULL;
	}

	return new Point(CPLAtof(values[x]), CPLAtof(values[y]));
}

std::list<Point> Txt::getRing()
{
	std::list<Point> ring;

	for (;;)
	{
		Point * point = ReadOnePoint();

		if (point == NULL)
		{
			break;
		}

		ring.push_back(Point(*point));
		delete point;
	}

	return ring;
}

Txt::~Txt()
{
	if (fp != NULL)
	{
		VSIFClose(fp);
	}
}
