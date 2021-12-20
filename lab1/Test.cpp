#include "pch.h"
#include"../Lab1.1/TritSet.h"
#include"../Lab1.1/Trit.h"
#include<iostream>


TEST(TestConstructor, Constructor_WithMemory) // Here i simultaneosly testing function of setting trit by index, function that returns logical_size of TritSet(set.size()) 
{                                 // and function that returns array_size(set.capacity())
	TritSet set(50);

	for (int i = 0; i < 50; i++)
	{
		set[i] = Trit::TRUE;
	}

	ASSERT_EQ(set.size(), 50);
	ASSERT_EQ(set.capacity(), 50);

	for (int i = 0; i < 50; i++)
	{
		ASSERT_EQ((Trit)set[i], Trit::TRUE);
	}
}

TEST(TestConstructor, Constructor_ZeroMemory)
{
	TritSet set;

	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.capacity(), 0);

}

TEST(TestGetOperator, get_trit_Operator)
{
	TritSet set(15);

	set[0] = Trit::TRUE;
	set[10] = Trit::TRUE;

	ASSERT_EQ((Trit)set[0], Trit::TRUE);
	ASSERT_EQ((Trit)set[10], Trit::TRUE);
	ASSERT_EQ((Trit)set[13], Trit::UNKNOWN);
}

TEST(TestTrimFunction, trim)
{
	TritSet set(100);
	
	for (int i = 0; i < 100; i++)
	{
		set[i] = Trit::TRUE;
	}

	ASSERT_EQ(set.size(), 100);
	ASSERT_EQ(set.capacity(), 100);

	set.trim(50);
	
	ASSERT_EQ(set.size(), 51);
	ASSERT_EQ(set.capacity(), 51);
}

TEST(TestShrinkFunction, shrink)
{
	TritSet set(100);

	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.capacity(), 100);

	set.shrink();

	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.capacity(), 0);
}

TEST(TestCardinalityFunction, cardinality)
{
	TritSet empty_set, true_set(100, Trit::TRUE), false_set(100, Trit::FALSE), unknown_set(100, Trit::UNKNOWN);

	ASSERT_EQ(empty_set.cardinality(Trit::TRUE), 0);
	ASSERT_EQ(empty_set.cardinality(Trit::FALSE), 0); 
	ASSERT_EQ(empty_set.cardinality(Trit::UNKNOWN), 0);

	ASSERT_EQ(true_set.cardinality(Trit::TRUE), 100);
	ASSERT_EQ(true_set.cardinality(Trit::FALSE), 0);
	ASSERT_EQ(true_set.cardinality(Trit::UNKNOWN), 0);

	ASSERT_EQ(false_set.cardinality(Trit::TRUE), 0);
	ASSERT_EQ(false_set.cardinality(Trit::FALSE), 100);
	ASSERT_EQ(false_set.cardinality(Trit::UNKNOWN), 0);

	ASSERT_EQ(unknown_set.cardinality(Trit::TRUE), 0);
	ASSERT_EQ(unknown_set.cardinality(Trit::FALSE), 0);
	ASSERT_EQ(unknown_set.cardinality(Trit::UNKNOWN), 100);
}

TEST(TestOpearorOR, OR_operator)
{
	TritSet set(5);
	TritSet true_set(5, Trit::TRUE), false_set(5, Trit::FALSE), unknown_set(5, Trit::UNKNOWN);

	// TRUE | TRUE
	set = true_set | true_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);
	
	// FALSE | FALSE
	set = false_set | false_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, false_set);

	// UNKNOWN | UNKNOWN
	set = unknown_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, unknown_set);

	// TRUE | FALSE
	set = true_set | false_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);

	// TRUE | UNKNOWN
	set = true_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);

	// FALSE | UNKNOWN
	set = false_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, unknown_set);
}

TEST(TestOpearorAND, AND_operator)
{
	TritSet set(5);
	TritSet true_set(5, Trit::TRUE), false_set(5, Trit::FALSE), unknown_set(5, Trit::UNKNOWN);

	// TRUE | TRUE
	set = true_set & true_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);

	// FALSE | FALSE
	set = false_set & false_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, false_set);

	// UNKNOWN | UNKNOWN
	set = unknown_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, unknown_set);

	// TRUE | FALSE
	set = true_set | false_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);

	// TRUE | UNKNOWN
	set = true_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, true_set);

	// FALSE | UNKNOWN
	set = false_set | unknown_set;
	ASSERT_EQ(set.size(), 5);
	ASSERT_EQ(set, unknown_set);
}

/*TEST(TestOpearorNOT, NOT_operator)
{

}*/
