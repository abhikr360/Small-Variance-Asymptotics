#include<iostream>
#include <vector>
#include<cstdlib>
using namespace std;


int main(){


	std::vector<std::vector<int> > v;
	std::vector<int > a;
	std::vector<int > b;

	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	v.push_back(a);
	v.push_back(b);

	v[1].push_back(9);
	for (int i = 0; i < v.size(); ++i)
	{
		std::vector<int> t = v[i];
		for (int j = 0; j < t.size(); ++j)
		{
			cout << t[j];
		}
	}

	return 0;
}