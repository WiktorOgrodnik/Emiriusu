#pragma once
#ifndef LOG_H
#define LOG_H

#include "pch.h"

class Log
{
private:

	bool active;
	std::string fileName;
	std::string path;
	std::fstream logFile; 
	std::fstream logFileDev;

	Log();
	Log(const Log&);
	~Log();

	std::string getSystemDate();
	void lineContents(std::string logContent);


public:
	
	static Log& newLog(std::string logContent);
};



#endif /* LOG_H */