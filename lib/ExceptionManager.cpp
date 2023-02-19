/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @�ļ�����ExceptionManager.cpp
* @����ʱ�䣺2023/2/19
* @�����ߣ�github.com/Climber-Rong
* -----------------------------------------------------------------------------
*�ļ�����
���ڲ����쳣���׳��쳣 
* -----------------------------------------------------------------------------
* ����㷢����bug�������ȥGithub������(MiracleForest@Outlook.com)���������ǣ�
* ����һ����Ŭ�����ø��õģ�
*
****/

/*С֪ʶ���������ˣ����������Ժ��õõ��������ţ�����*/

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
