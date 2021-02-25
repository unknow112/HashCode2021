#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>
#include <numeric>


struct Street
{
	int id; 
	int start, end;
	std::string name;
	int time;
	uint64_t end_hit = 0; 
};

struct Intersection
{
	int index;
	std::vector<int> street_ending_id;
	explicit Intersection(int index):
		index(index) {}
	std::string from_left_neig =  ""; 
	std::string from_right_neig =  ""; 
	std::string from_up_neig  =  ""; 
	std::string from_down_neig  =  ""; 
};
 const int GREEN_SLOT_SIZE = 1; 

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
		s.id = i ;
		std::cin >> s.start >> s.end 
			>> s.name >> s.time;
		streets.push_back(s);
		junctions[s.end].street_ending_id.push_back(s.id);
	}

	for (int i = 0 ; i < V ; i ++ )
	{ 
		int X;
		std::cin >> X;
		for (int j= 0 ; j < X ; j ++) { 
			std::string streetn;
			std::cin >> streetn;
		}
		
	}
			


	std::cout << I << '\n' ; 
	for (auto& inters: junctions){
		for (int i :  inters.street_ending_id ) { 
			const auto&street = streets[i];
			if (street.start + 1 == inters.index) { 
				inters.from_up_neig = street.name;
				continue;
			}
			if (street.start - 1 == inters.index) {
				inters.from_down_neig = street.name; 
				continue; 
			}
			if (street.start < inters.index) { 
				inters.from_left_neig = street.name; 
				continue;
			}

			if (street.start > inters.index) {
				inters.from_right_neig = street.name ; 
				continue;
			}
		}
		std::cout << inters.index << '\n' 
			<< inters.street_ending_id.size() << '\n';

		int green_duration = GREEN_SLOT_SIZE; 
		if (inters.from_right_neig != "") { 
			std::cout << inters.from_right_neig << ' ' 
				<< green_duration << '\n';
		} else { 
			green_duration += GREEN_SLOT_SIZE ; 
		}
		if (inters.from_left_neig != "") { 
			std::cout << inters.from_left_neig << ' '
				<< green_duration << '\n';
			green_duration = GREEN_SLOT_SIZE;
		} else { 
			green_duration += GREEN_SLOT_SIZE; 
		}
		if (inters.from_down_neig != "") { 
			std::cout << inters.from_down_neig << ' '
				<< green_duration << '\n' ;
			green_duration = GREEN_SLOT_SIZE ;
		} else { 
			green_duration += GREEN_SLOT_SIZE; 
		}
		if (inters.from_up_neig != "") { 
			std::cout << inters.from_up_neig <<   ' '
				<< green_duration << '\n' ;
		}



	}

	return 0;

}
