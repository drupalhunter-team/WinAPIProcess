#define _CRT_SECURE_NO_WARNINGS
#include "LogFile.h"

MsgException::MsgException(std::string message){
	_message = message;
}
std::string& MsgException::ShowMessage(){
	return _message;
}



LogFile::LogFile(std::string path, bool append)
{
	if (append) _f.open(path, std::ios_base::app);
	else _f.open(path);
	if (!(_f.is_open()))
		throw MsgException("File is not opened");
	time_t now = time(0);
	char* dt = ctime(&now);
	_f << std::endl << dt << startMsg << std::endl;
}

void LogFile::LogMessage(std::string message){
	std::lock_guard<std::mutex> guard(_mu);
	time_t now = time(0);
	char* dt = ctime(&now);
	_f << dt << ": " << message << std::endl;
	_f.flush();
}

void LogFile::LogMessage(std::wstring message){
	std::lock_guard<std::mutex> guard(_mu);
	time_t now = time(0);
	char* dt = ctime(&now);
	dt[strlen(dt) - 2] = '\0';
	_f << dt << ": " << message.c_str() << std::endl;
	_f.flush();
}

LogFile::~LogFile()
{
	std::lock_guard<std::mutex> guard(_mu);
	time_t now = time(0);
	char* dt = ctime(&now);
	_f << dt << closeMsg << std::endl;
	_f.close();
}
