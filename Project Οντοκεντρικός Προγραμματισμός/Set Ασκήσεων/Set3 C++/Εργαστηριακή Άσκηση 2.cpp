#include <iostream> 
using namespace std;

class Polygon 
{
protected:
	int width, height; 
public:
		Polygon(int a = 0, int b = 0)
		{
			width = a; 
			height = b;
		}
		virtual int area()
		{
			cout << "This is area as computed by the Polygon class" << endl; 
			return 0;
		}
};

class Rectangle : public Polygon 
{
public:
	Rectangle(int a = 0, int b = 0) :Polygon(a, b) 
	{ 
	} 
	int area()
	{
		cout << "This is area as computed by the Rectangle class" << endl; 
		return (width * height);
	}
};
int main()
{
	Polygon *polygon; 
	Rectangle rec(10, 7);
	polygon = &rec; 
	polygon->area();
	return 0;
}