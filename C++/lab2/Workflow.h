#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<map>

#include"ProgramParser.h"
#include"Worker.h"
#include"workers.h"

class Workflow
{
public:
	Workflow(const std::string& iname, std::string oname);
	~Workflow() {}
	void run(void);
	operator bool() const
	{
		return !isEmpty;
	}
	const Worker* nextInstruction();
	std::string iname,
		        oname;
private:
	bool isEmpty = false;

	std::map<uint32_t, const Worker*> description;
	WorkflowParser parser;
	void BuildDescription();
	const Worker* GetWorkerById(uint32_t id);
	const std::string ExtractCmd(std::string cmd_line);
	const std::vector<std::string> ExtractArgs(std::string cmd_line);
	void ReciveCmd(uint32_t id, std::string cmd);
	void Exception(std::string msg)
	{
		std::cout << "Workflow exception: " << msg << std::endl;
	}
};
