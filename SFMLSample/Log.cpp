#include "pch.h"
#include "Log.h"

Log::Log()
{
	active = false;
	logFile.open("Log.log", std::ios::out);

	path = "log/";
	fileName = getSystemDate();

	logFileDev.open(path + fileName + ".log", std::ios::out);

	if (logFileDev.good())
	{
		logFileDev << fileName << ": Uda³o siê utworzyæ plik typu log\n";
		active = true;
		logFileDev.close();
	}
	else std::cerr << "Nie uda³o siê utowrzyæ pliku o nazwie " + fileName + ".log" << '\n';
}

std::string Log::getSystemDate()
{
	time_t now = time(0);
	tm ltm;
	char buffer[80];

	localtime_s(&ltm, &now);

	strftime(buffer, 80, "%d-%m-%Y %H-%M-%S", &ltm);
	return "Emiriusu.exe " + std::string(buffer);
}

void Log::lineContents(std::string logContent)
{
	if (active)
	{
		std::string date = getSystemDate();

		logFileDev.open(path + fileName + ".log", std::ios::app);

		logFileDev << date << ": " << logContent << '\n';

		logFileDev.close();
	}
}

Log& Log::newLog(std::string logContent)
{
	static Log instance;
	instance.lineContents(logContent);
	return instance;
}

Log::~Log()
{
}


