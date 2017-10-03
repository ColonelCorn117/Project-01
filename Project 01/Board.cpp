#include <vector>

using namespace std;

class Board
{
private:
	int width = 10;
	int height = 10;
	const int defaultSize = 10;
	vector< vector<int> > layout;		//Acts like a 2D array (like int[][] in Java)
	int deadIdentifier = 0;				//Squares with this identifier value are considered "dead"

	//************************************************

public:
	//Blank Constructor
	Board()
	{
		SetHeight(defaultSize);
		SetWidth(defaultSize);
		layout.resize(defaultSize, vector<int>(defaultSize, deadIdentifier));
	}

	//************************************************

	//Constructor with parameters
	Board(int width, int height)
	{
		SetWidth(width);
		SetHeight(height);
		layout.resize(width, vector<int>(height, deadIdentifier));
	}

	//************************************************

	void SetHeight(int height)
	{
		this->height = height;		//"this" is a pointer, so we can't use dot notation (such as "this.length")
	}

	//************************************************

	void SetWidth(int width)
	{
		this->width = width;
	}

	//************************************************

	int GetWidth()
	{
		return width;
	}

	//************************************************

	int GetHeight()
	{
		return height;
	}
};

