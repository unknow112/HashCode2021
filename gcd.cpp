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

std::unordered_map<std::string,int> street_name_to_id;

struct Intersection
{
	int index;
	std::vector<int> street_ending_id;
	explicit Intersection(int index):
		index(index) {}
	int result_number_of_streets = 0 ;
	uint64_t result_gcd = 0 ;
};

struct StreetGcd{
	const std::vector<Street>& _s;
	StreetGcd(const std::vector<Street> s):
		_s(s){}
	uint64_t operator()(uint64_t  a , int street_id )
	{
		return std::gcd(a,_s[street_id].end_hit);
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
	for (int i = 0 ; i < S ; i ++ ) { 
		Street s; 
		s.id = i ;
		std::cin >> s.start >> s.end 
			>> s.name >> s.time;
		streets.push_back(s);
		street_name_to_id[s.name]= s.id;
		junctions[s.end].street_ending_id.push_back(s.id);
	}

	for (int i = 0 ; i < V ; i ++ )
	{ 
		int X;
		std::cin >> X;
		for (int j= 0 ; j < X ; j ++) { 
			std::string streetn;
			std::cin >> streetn;
			streets[street_name_to_id[streetn]].end_hit++ ;
		}
		
	}
			



	int num_of_intersections = 0 ; 
	for (auto& inters: junctions){ 
		inters.result_gcd = std::accumulate(inters.street_ending_id.begin(),
				inters.street_ending_id.end(),
				uint64_t(0),
				StreetGcd(streets));
		inters.result_number_of_streets= 0;
		for (int i :  inters.street_ending_id ) { 
			const auto&x = streets[i];
			if (x.end_hit){
				inters.result_number_of_streets++;
			}
		}
		if (inters.result_number_of_streets) {
			num_of_intersections ++ ;
		}

	}

	std::cout << num_of_intersections << '\n' ; 
	for (const auto& inters: junctions) {
		if (!(inters.result_number_of_streets)){
			continue;
		}
		std::cout << inters.index << '\n'
			<< inters.result_number_of_streets << '\n' ;

		for (int i : inters.street_ending_id ) {
			const auto& street = streets[i];
			if (!(street.end_hit)) { 
				continue; 
			} 
			std::cout << street.name << ' ' << street.end_hit / inters.result_gcd << '\n' ; 
		}
	}


	return 0;

}
