#include "Workflow.h"

Workflow::Workflow(const std::string& iname, std::string oname) : iname(iname), oname(oname), parser(iname) 
{
	if (oname == "") 
	{
		std::cout << "No output file set. Redirecting the stream in \"out.txt\"" << std::endl;
		oname = "out.txt";
	}
	if (iname != "") 
	{
		if (parser.isInputValid) 
		{
			BuildDescription();
		}
		else
			isEmpty = true;
	}
	else isEmpty = true;
}

Workflow::Workflow(const Workflow& other) 
{
	isEmpty = !other;
	iname = other.iname;
	oname = other.oname;
	if (other) 
	{
		WorkflowParser filenameParser(iname);
		parser = filenameParser;
		BuildDescription();
	}
}

const Worker* Workflow::GetWorkerById(uint32_t id) 
{
	auto found = description.find(id);
	return found == description.end() ? nullptr : found->second;
}

const Worker* Workflow::nextInstruction() 
{
	const Worker* worker = (!parser.instruction.empty() ? GetWorkerById(parser.instruction.front()) : nullptr);
	if (parser.instruction.size())
		parser.instruction.pop_front();
	return worker;
}

const std::string Workflow::ExtractCmd(std::string cmd_line) 
{
	if (cmd_line.find(" "))
		return cmd_line.substr(0, cmd_line.find(" "));
	else
		return cmd_line;
}

const std::vector<std::string> Workflow::ExtractArgs(std::string cmd_line) 
{
	std::vector<std::string> args;
	if (cmd_line.find(" ") > 1 && cmd_line.find(" ") < cmd_line.length()) 
	{
		size_t pointer = cmd_line.find(" ") + 1;
		if (cmd_line.find(" ", pointer)) 
		{
			args.push_back(cmd_line.substr(pointer, cmd_line.find(" ", pointer) - pointer));
			pointer = cmd_line.find(" ", pointer) + 1;
			if (pointer)
				args.push_back(cmd_line.substr(pointer, cmd_line.length() - pointer));
		}
	}
	return args;
}


void Workflow::ReciveCmd(uint32_t id, const std::string cmd_line) 
{
	const std::string cmd = ExtractCmd(cmd_line);
	const std::vector<std::string> args = ExtractArgs(cmd_line);
	if (!isEmpty) 
	{
		const Worker* worker = workers::constructWorker(id, cmd, args);
		description[id] = worker;
	}
	if (isEmpty)
		WorkflowException(">" + std::to_string(id) + ": " + cmd_line);
}
void Workflow::BuildDescription() 
{
	for (uint32_t i = 0; i < parser.blocks.size(); ++i)
		if (!isEmpty)
			ReciveCmd(i, parser.blocks[i]);
}

void Workflow::run(void) 
{
	if (!isEmpty) 
	{
		WorkerResult lastResult;
		Worker const* worker = nextInstruction();
		if (worker == nullptr) 
		{
			isEmpty = true;
			return;
		}
		if (worker->getAcceptType() != WorkerResult::ResultType::NONE) 
		{
			workers::ReadFile reader(0, ifname);
			lastResult = reader.execute(lastResult);
		}

		do {
			lastResult = worker->execute(lastResult);
		} while (lastResult.getType() && (worker = nextInstruction()));

		if (lastResult.getType() == WorkerResult::ResultType::NONE)
			return;

		if (lastResult.getType() != WorkerResult::ResultType::UNKNOWN) 
		{
			workers::WriteFile writer(0, ofname);
			writer.execute(lastResult);
			return;
		}

	}
	isEmpty = true;
	std::ofstream output;
	output.open(oname.c_str(), std::ios::in | std::ios::app);
	output << parser.exception << "Error: Empty workflow";
	output.close();

}
