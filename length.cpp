#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
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
    std::set<std::string> street_names_used;
    //int sumL = 0;
	explicit Intersection(int index):
		index(index) {}

    /*void addL(int l) {
        sumL = std::max(l, sumL);
    }*/

    void print(const std::vector<Street> &streets, const std::map<std::string, int> &streetNameToIndex) {
         int sumL = 0;
         for (const auto &sn : street_names_used) {
            sumL += streets[streetNameToIndex.at(sn)].time;
         }

         sumL++;
         std::vector<std::string> tmp;
         for (const auto &sn : street_names_used) {
            tmp.push_back(sn);
         }

         random_shuffle(tmp.begin(), tmp.end());
         for (const auto &sn : tmp) {
            std::cout << sn << " " << std::ceil(streets[streetNameToIndex.at(sn)].time / static_cast<double>(sumL)) << std::endl;
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
    std::map<std::string, int> streetNameToIndex;
	for (int i = 0 ; i < S ; i ++ ) { 
		Street s; 
		std::cin >> s.start >> s.end 
			>> s.name >> s.time;
		streets.push_back(s);
        //junctions[s.end].addL(s.time);
        streetToIntersection.insert({s.name, s.end});
        streetNameToIndex.insert({s.name, i});
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
    for (int i = 0; i < I; i++) {
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
        junctions[i].print(streets, streetNameToIndex);
	}

	return 0;

}
