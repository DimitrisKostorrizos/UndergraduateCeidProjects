#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
	 string name;
	 double price;
	 int score;
public:
	Product()//Constructor
	{
		name = "";
		price = 1.0;
		score = 0;
	}
	string getName()
	{
		return name;
	}
	double getPrice()
	{
		return price;
	}
	int getScore()
	{
		return score;
	}
	void read()
	{
		cout << "Please enter the model name: ";
		getline(cin, name);
		cout << "Please enter the price: ";
		cin >> price;
		cout << "Please enter the score: ";
		cin >> score;
		string remainder; /* read remainder of line */
		getline(cin, remainder);
	}
	friend void print(Product a)
	{
		cout << a.getName() << endl
			<< " (Score: " << a.getScore() << endl
			<< " Price: " << a.getPrice() << ")" << endl;
	}
	bool operator >(const Product& p)
	{
		if ((score / price) > (p.score / p.price))
		{
			return true;
		}
		return false;
	}
};

int main()
{
	Product best;
	bool more = true;
	while (more)
	{
		Product next;
		next.read();
		if (next > best)
		{
			best = next;
		}
		cout << "More data? (y/n) ";
		string answer;
		getline(cin, answer);
		if (answer != "y") more = false;
	}
	cout << "The best value is ";
	print(best);
	return 0;
}