#include<iostream> 

using namespace std;

class Kouti
{
public:
	double calculateOgkos()
	{
		return  length*breadth*height;
	}
	void setMikos(double l)
	{
		length=l;
	}
	void setPlatos(double b)
	{
		breadth = b;
	}
	void setYpsos(double h)
	{
		height = h;
	}
	Kouti operator+(const Kouti& b)
	{
		Kouti kouti;
		kouti.length = this->length + b.length;
		kouti.breadth = this->breadth + b.breadth; 
		kouti.height = this->height + b.height; 
		return kouti;
	}
private:
	double length; 
	double breadth; 
	double height;
};
int main()
{
	double ogkos = 0.0;
	Kouti KoutiA;
	Kouti KoutiB;
	KoutiA.setMikos(2.0);
	KoutiA.setPlatos(3.2);
	KoutiA.setYpsos(6.0) ;
	KoutiB.setMikos(2.5);
	KoutiB.setYpsos(4.0);
	KoutiB.setPlatos(5.0);
	ogkos = KoutiA.calculateOgkos();
	cout << "The volume of KoutiA is: " << ogkos << endl;
	ogkos = KoutiB.calculateOgkos();
	cout << "The volume of KoutiB is: " << ogkos << endl;
	Kouti KoutiC;
	KoutiC = KoutiA + KoutiB;
	ogkos = KoutiC.calculateOgkos();
	cout << "The volume of KoutiC is: " << ogkos << endl;
}