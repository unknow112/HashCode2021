#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>



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
	std::set<std::string> street_names_used;
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
    std::map<std::string, int> streetToIntersection;
	for (int i = 0 ; i < S ; i ++ ) { 
		Street s; 
		std::cin >> s.start >> s.end 
			>> s.name >> s.time;
		streets.push_back(s);
        streetToIntersection.insert({s.name, s.end});
		junctions[s.end].street_names.push_back(s.name);
	}

    for (int i = 0; i < V; i++) {
        int count;
        std::cin >> count;
        std::string name;
        for (int j = 0; j < count - 1; j++) {
            std::cin >> name;
            junctions[streetToIntersection[name]].street_names_used.insert(name);
        }
        std::cin >> name;
    }

    int outI = 0;
	for (int i = 0 ; i < I ; i++ ) {
        if (junctions[i].street_names_used.size() != 0) {
            outI++;
        }
	}

	std::cout << outI << '\n';
	for (int i = 0 ; i < I ; i++ ) {
        if (junctions[i].street_names_used.size() == 0) {
            continue;
        }
        
		std::cout << i << '\n' 
			<< junctions[i].street_names_used.size() 
			<< '\n';
		for (const auto& sn : junctions[i].street_names_used){
			std::cout << sn << " 1" << '\n';
		}
	}

	return 0;

}
