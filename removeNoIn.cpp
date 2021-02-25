#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>



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
    std::map<std::string, int> nameToCount;
	std::set<std::string> street_names_used;
	explicit Intersection(int index):
		index(index) {}

    void initToCount() {
        for (const auto &name : street_names) {
            nameToCount.insert({name, 0});
        }
    }

    void insertCarInit(const std::string &name) {
        nameToCount[name]++;
    }

    void print() {
        std::vector<std::pair<std::string, int>> tmp;
        for (auto &p : nameToCount) {
            if (p.second != 0) {
                tmp.push_back(p);
            }
        }

        std::sort(tmp.begin(), tmp.end(), [](auto a, auto b) { return a.second > b.second; });
        for (auto &p : tmp) {
            std::cout << p.first << " " << p.second << std::endl;
            street_names_used.erase(p.first);
        }

		for (const auto& sn : street_names_used) {
			std::cout << sn << " 1" << '\n';
		}
    }
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

    for (Intersection &inter : junctions) {
        inter.initToCount();
    }

    for (int i = 0; i < V; i++) {
        int count;
        std::cin >> count;
        std::string name;
        for (int j = 0; j < count - 1; j++) {
            std::cin >> name;
            junctions[streetToIntersection[name]].street_names_used.insert(name);
            if (j == 0) {
                junctions[streetToIntersection[name]].insertCarInit(name);
            }
        }
        std::cin >> name;
        if (count == 1) {
            junctions[streetToIntersection[name]].insertCarInit(name);
        }

    }

    int outI = 0;
	for (int i = 0 ; i < I ; i++) {
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
        junctions[i].print();
	}

	return 0;

}
