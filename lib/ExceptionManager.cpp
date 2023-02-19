/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @文件名：ExceptionManager.cpp
* @创建时间：2023/2/19
* @创建者：github.com/Climber-Rong
* -----------------------------------------------------------------------------
*文件描述
用于捕获异常，抛出异常 
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

/*小知识：这代码废了，但是我怕以后用得到，先留着，别看了*/

#ifndef SOMETHING_H
#define SOMETHING_H

struct {
	char* ExceptionMessage;
	bool isException;
}ExceptionManager;

void throwError(char* message){
	ExceptionManager.isException = true;
	ExceptionManager.ExceptionMessage = message;
}

bool isError()
{
	return ExceptionManager.isException;
}

char* getError()
{
	return ExceptionManager.ExceptionMessage;	
}

#define Throw(Message) throwError(Message)
#define Catch isError()
#define Exception getError()

#endif
