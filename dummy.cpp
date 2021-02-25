#include <iostream>
#include <vector>
#include <string>



struct Street
{
	int start, end;
	std::string name;
	int time;
};


struct Intersection
{
	int index;
	std::vector<std::string> street_names;
	explicit Intersection(int index):
		index(index) {}
};

int main()
{
	int D,I,S,V,F ; 
	std::cin >> D >> I >> S >> V >> F;

	std::vector<Street> streets;
	streets.reserve(S);
	std::vector<Intersection> junctions;
	junctions.reserve(I);
	for (int i = 0 ; i < I ; i ++ ) { 
		junctions.push_back(Intersection(i));
	}
	for (int i = 0 ; i < S ; i ++ ) { 
		Street s; 
		std::cin >> s.start >> s.end 
			>> s.name >> s.time;
		streets.push_back(s);
		junctions[s.end].street_names.push_back(s.name);
	}
	std::cout << I << '\n';
	for (int i = 0 ; i < I ; i++ ) {
		std::cout << i << '\n' 
			<< junctions[i].street_names.size() 
			<< '\n';
		for (const auto& sn : junctions[i].street_names){
			std::cout << sn << " 1" << '\n';
		}
	}

	return 0;

}
