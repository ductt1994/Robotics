#include <iostream>
#include <vector>

int main()
{
	//Create a vector
	std::vector<int> v_1;
	v_1 = { 1,2,3 };

	std::vector<int>* p = &v_1;

	for (int i = 0; i < v_1.size(); i++)
	{
		std::cout << "v_1[" << i << "] = " << v_1[i] << std::endl;
	}

	std::cout << "v_1.size(): " << v_1.size() << std::endl;
	std::cout << "p->size(): " << p->size() << std::endl;

	for (int i = 0; i < p->size(); i++)
	{
		std::cout << "(*p)[" << i << "] = " << (*p)[i] << std::endl;
	}

	return 0;
}