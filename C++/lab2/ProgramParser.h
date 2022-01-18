#pragma once
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <iostream>

class WorkflowParser
{
public:
	WorkflowParser(const std::string& filename);
	WorkflowParser() {}
	WorkflowParser(const WorkflowParser* other)
	{
		instruction = other->instruction;
		exception = other->exception;
		blocks = other->blocks;
		isInputValid = other->isInputValid;
	}
	void operator=(WorkflowParser other);
	std::string exception;
	std::list<uint32_t> instruction;
	std::vector<std::string> blocks;
	bool isInputValid = true;
private:
	int getInstruction(std::string& str);
	void WorkflowParserException(std::string msg) 
	{
		isInputValid = false;
		exception += "WorkflowParser exception: " + msg + "\n";
	}
	int getBlock(std::string& str);
	std::vector<bool> blocksRange;
	void getFromFile(const std::string& filename);
	int deleteWhiteSpaces(std::string& str);
	int addElemInstruction(uint32_t& count, bool& isLastCount);
	void dataOptimize(void);
	void deleteTwins(void);
	void deleteNoUsedBlocks();
};
