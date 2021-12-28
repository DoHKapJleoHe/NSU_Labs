#include "Trit.h"
#include<unordered_map>

typedef unsigned int uint;

class TritSet
{
private:
	uint *array;
	size_t array_size;
	size_t logical_size;
	size_t alloc_size;

	size_t true_count = 0;
	size_t false_count = 0;
	size_t unknown_count = 0;

	Trit get_Trit(size_t) const;
	void set_Trit(size_t, Trit);
public:
	TritSet(size_t size = 0, Trit trit = UNKNOWN);

	class reference
	{
		friend class TritSet;
	private:
		reference(TritSet&, size_t); // конструктор класса reference
		TritSet& tritset; // поле класса reference 
		size_t posititon; // поле класса reference
	public:
		TritSet& operator = (Trit);
		operator Trit();
	};

	size_t size();
	reference operator [] (size_t);
	Trit operator [] (size_t) const;
	size_t capacity();
	size_t get_last_index();
	void shrink();
	TritSet(const TritSet&);
	void trim(size_t);
	long long get_alloc_size(size_t);
	std::unordered_map<Trit, size_t, std::hash<size_t>> cardinality();
	size_t cardinality(Trit);
};

TritSet operator & (const TritSet& trit_set1, const TritSet& trit_set2);
TritSet operator | (const TritSet& trit_set1, const TritSet& trit_set2);
TritSet operator ~ (const TritSet& trit_set);
