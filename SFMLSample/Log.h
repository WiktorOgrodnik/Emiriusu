#pragma once
#ifndef LOG_H
#define LOG_H

#include "pch.h"

class Log
{
private:

	bool active; /// Przechowuje informacjê o tym, czy logi s¹ ju¿ aktywne
	std::string fileName; /// Nazwa logu
	std::string path; /// Œcie¿ka do plików log
	std::fstream logFile; /// zmeinna plikowa pliku log.log
	std::fstream logFileDev; /// zmienna plikowa w³aœciwego pliku logu

	/// Funkcje singleton pattern
	Log();
	Log(const Log&);
	~Log();

	std::string getSystemDate(); /// Uzyskuje datê systemow¹
	void lineContents(std::string logContent); /// Dodaje wskazany ³añcuch do pliku log


public:
	
	static Log& newLog(std::string logContent); /// Dodaje nowy wpis do logu (funkcja wyowo³uj¹ca klasê Singleton pattern)
};



#endif /* LOG_H */