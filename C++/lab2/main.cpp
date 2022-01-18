#include<iostream>
#include<string>

#include"Workflow.h"

using namespace std;

int main(int argc, char* argv[])
{
	const string in = "in.txt";
	const string out = "out.txt";

	Workflow workflow(in, out);
	workflow.run();

	return 0;
}
