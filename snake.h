//James Bonadonna, Section 2
//snake.h, outlines and defines the Snake class

using namespace std;
#include<vector>

class Snake {
	public:
	Snake();
	Snake(vector<float>,vector<float>,int,bool);
	~Snake();
	void setSnake(vector<float>,vector<float>,int,bool);
	void setX(vector<float>);
	void setY(vector<float>);
	int move(int,float,float,bool);
	int getSize();
	bool intersect(float,float);
	bool eatFood(float[2]);
	void add(float[2]);
	private:
	vector<float> xVals;
	vector<float> yVals;
	int dir;
	bool shape;
};
