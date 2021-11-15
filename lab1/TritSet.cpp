#include "TritSet.h"
#include<iostream>

TritSet::TritSet(size_t size, Trit trit) : array_size(size), logical_size(trit == UNKNOWN ? 0 : size)
{
	 uint *arr = new uint[size];

	 int xpeHb_gJl9_mpumoB = 0;
	 alloc_size = size > 0 ? get_alloc_size(size) : 0;

	 for (size_t i = 0; i < (sizeof(uint) * 8 / 2); i++) // i < (размер uint * размер байта / число трит в uint)
	 {
		 xpeHb_gJl9_mpumoB |= trit << i * 2;
		 // комментарий к тому, что написано выше: я беру строчку из нулей (в данном случае - это xpeHb_dJi9_moumoB) и потом припомощи побитового или
		 // вставляю в эту строчку числовое значение трита (00 - UNKNOWN, 01 - FALSE, 11 - TRUE), которое в цикле по кол-ву тритов в uint двигаю влево
		 //тем самым получиться строчка из нужных тритов (0000000000 или 0101010101 или 1111111111)
	 }

	 for (size_t i =0; i < size; i++)
	 {
		 arr[i] = xpeHb_gJl9_mpumoB;
	 }
}

size_t TritSet::cardinality(Trit trit)
{
	if (trit == TRUE)
		return true_count;
	else if (trit == FALSE)
		return false_count;
	else
		return unknown_count;
}

std::unordered_map<Trit, size_t, std::hash<size_t>> TritSet::cardinality()
{
	std::unordered_map<Trit, size_t, std::hash<size_t>> unordered_map;
	unordered_map[TRUE] = true_count;
	unordered_map[FALSE] = false_count;
	unordered_map[UNKNOWN] = unknown_count;
	return unordered_map;
}

void TritSet::shrink()
{
	if (!alloc_size)
		return;
	long long last_index = get_last_index();
	Trim(last_index);
	array_size = last_index + 1;
	logical_size = last_index + 1;
}

/*void TritSet::Trim(size_t last_index)
{
	change_size_of_TritSet(last_index);
}*/

void TritSet::Trim(long long position) // было change_tritset_size
{
	size_t new_alloc_size = get_alloc_size(position);

	if (new_alloc_size > alloc_size)
	{
		uint* new_arr = new uint[position];

		for (size_t i = 0; i < array_size; i++)
		{
			new_arr[i] = array[i];
		}
		for (size_t i = array_size; i < position - array_size; i++)
		{
			new_arr[i] = 0;
		}
		delete[] array;  //}
		array = new_arr; //} это будет работать ?
	}
	if (new_alloc_size < alloc_size)
	{
		uint* new_arr = new uint[position];
		for (size_t i = 0; i < position; i++)
		{
			new_arr[i] = array[i];
		}
		delete[] array;
		array = new_arr;
	}

	alloc_size = new_alloc_size;
	array_size = position + 1;
}

long long TritSet::get_alloc_size(long long array_size)
{
	if (array_size < 0)
		return 0;
	else
		return array_size * 2 / 8 / sizeof(uint);
}


long long TritSet::get_last_index()
{
	size_t last_index = -1;
	for (size_t i = 0; i < array_size; i++)
	{
		if (get_Trit(i) != UNKNOWN)
			last_index = i;
	}

	return last_index;
}

TritSet::reference::operator Trit()
{
	return tritset.get_Trit(posititon);
}

TritSet& TritSet::reference::operator = (Trit trit)
{
	tritset.set_Trit(posititon, trit);
	return tritset;
}

size_t TritSet::capacity()
{
	return array_size;
}

size_t TritSet::size()
{
	return logical_size;
}

TritSet::reference TritSet::operator [] (size_t position)
{
	return reference(*this, position);
}

Trit TritSet::operator [] (size_t index) const
{
	return get_Trit(index);
}

Trit TritSet::get_Trit(size_t position) const
{
	uint uint_pos = position / (sizeof(uint) * 8 / 2);
	size_t trit_pos = position % (sizeof(uint) * 8 / 2);

	return Trit(array[uint_pos] >> (trit_pos * 2));
}

void TritSet::set_Trit(size_t position, Trit trit)
{
	uint uint_pos = position / (sizeof(uint) * 8 / 2);
	size_t trit_pos = position % (sizeof(uint) * 8 / 2);
	uint old_trit = array[uint_pos] >> trit_pos * 2;

	if (old_trit == TRUE)
		true_count--;
	else if (old_trit == FALSE)
		false_count--;
	else
		unknown_count--;

	if (trit == TRUE)
		true_count++;
	else if (trit == FALSE)
		false_count++;
	else
		unknown_count++;

	/*представь так : есть у тебя массив из 4 - х тритов :
	10 01 10 00
		и ты хочешь вставить трит 10 в ячейку[1], где сейчас написано 01

		1. сначала я зануляю эту ячейку : для этого мне понадобится сделать побитовое "и" для следующих байтов :
	10 01 10 00
		&
		11 00 11 11
		=
		10 00 10 00

		получить байт 11001111 = nullifier можно так : 00000011 « 4 = 00110000
		~00110000 = 11001111

		2. я хочу вставить туда новое значение 10, для этого потребуется сделать побитовое "и" для следующих байтов :
	10 00 10 00
		|
		00 10 00 00
		=
		10 10 10 00

		для этого нужно получить байт carry = 00100000, для этого возьмём байт 00000010 и побитово сдвинем его на 4 бита влево :
	00000010 « 4 = 00100000*/

	uint TPUT_KOTOPblU_HYIIIHO_BCTABUTb = ((uint)trit << (trit_pos * 2));
	size_t nullifier = (~(3 << (trit_pos * 2))); // Эта штука занулит нужный трит, куда потом я вставлю входящий трит 

	array[uint_pos] &= nullifier; // занулил трит
	array[uint_pos] |= TPUT_KOTOPblU_HYIIIHO_BCTABUTb;

	if (position > logical_size && trit == UNKNOWN)
		logical_size = position + 1;
	if (trit == UNKNOWN)
	{
		logical_size = get_last_index();
	}
}

TritSet operator & (TritSet& trit_set1, TritSet& trit_set2)
{
	size_t new_size = trit_set1.size() > trit_set2.size() ? trit_set1.size() : trit_set2.size();

	TritSet new_tritset(new_size);
	 
	for (size_t i = 0; i < new_size; i++)
	{
		new_tritset[i] = trit_set1[i] & trit_set2[i];
	}
	return new_tritset;
}

TritSet operator | (TritSet& trit_set1, TritSet& trit_set2)
{
	size_t new_size = trit_set1.size() > trit_set2.size() ? trit_set1.size() : trit_set2.size();

	TritSet new_tritset(new_size);

	for (size_t i = 0; i < new_size; i++)
	{
		new_tritset[i] = trit_set1[i] | trit_set2[i];
	}
	return new_tritset;
}

TritSet operator ~ (TritSet& trit_set1)
{
	size_t new_size = trit_set1.size();

	TritSet new_tritset(new_size);

	for (size_t i = 0; i < new_size; i++)
	{
		new_tritset[i] = ~ trit_set1[i];
	}
	return new_tritset;
}
