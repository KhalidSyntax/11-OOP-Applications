#include <iostream>

using namespace std;

class iFlyable
{
public:
	virtual void Fly() = 0;
};

class clsBird : public iFlyable
{
public:
	void Fly()
	{
		cout << "The bird is flying!" << endl;
	}
};

class clsAirplane : public iFlyable
{
public:
	void Fly()
	{
		cout << "The airplane is taking off!" << endl;
	}
};

int main()
{
	clsBird Bird;
	Bird.Fly();

	clsAirplane Airplane;
	Airplane.Fly();

	system("pause>0");

	return 0;
}