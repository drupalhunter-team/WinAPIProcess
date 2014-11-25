#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <mutex>
#include <ctime>
#pragma warning( disable : 4290 )
class MsgException : public std::exception{
private:
	std::string _message;
public:
	MsgException(std::string message);
	std::string& ShowMessage();
};

class LogFile
{
public:
	LogFile(std::string path, bool append) throw(MsgException);
	void LogMessage(std::string message);
	void LogMessage(std::wstring message);
	~LogFile();
private:
	std::ofstream _f;
	std::mutex _mu;
	const char* startMsg = ": Session started";
	const char* closeMsg = ": Session closed";
};

