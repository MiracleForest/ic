/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @�ļ�����list.cpp
* @����ʱ�䣺2023/2/19
* @�����ߣ�github.com/Climber-Rong
* -----------------------------------------------------------------------------
*�ļ�����
������java��arraylist
* -----------------------------------------------------------------------------
* ����㷢����bug�������ȥGithub������(MiracleForest@Outlook.com)���������ǣ�
* ����һ����Ŭ�����ø��õģ�
*
****/

#ifndef LIST_CPP
#define LIST_CPP

#include"stdlib.h"	//��Ҫ�õ��ڴ���� 

class List {
		// Private section
		//ԭ��ͨ��realloc�������С�����޸ģ�ÿ�����Ŷ�����ʮ�����л���
		int length;
		int free_len;
		void** data;
	public:
		List();
		List* add(void* ptr);		//��ӵ�ĩβ������this
		List* remove(int index);	//ɾ����index��Ԫ�أ�����this
		void* get(int index);		//��ȡԪ��
		int size();					//Ԫ������ 
		void destroy();				//����
		// Public Declarations
	protected:
		// Protected Declarations
};

List::List() {
	length = 0;
	free_len = 10;
	data = (void**)calloc(10, sizeof(void**));
	if(data==NULL) {
		throw MM_OUT;
	}
	*data = NULL;
}

List* List::add(void* ptr) {
	if(free_len==0) {
		//���಻��
		realloc(data, (length+10) * sizeof(void*));
		
		free_len = 10;
	}
	
	if(data==NULL) {
			throw MM_OUT;
	}
	
	data[length] = ptr;
	length++;
	free_len--;
	
	return this;
}

List* List::remove(int index) {
	for(int i=index+1;i<length;i++){
		data[i-1] = data[i];		//��ǰ�ƶ� 
	} 
	length--;
	free_len++;
	if(free_len>10){
		//ɾ��Ԫ�ع��ർ�¿����ڴ�ռ����
		realloc(data, length*sizeof(void**));
		free_len = 0;		//�����ö���ռ� 
	}
	
	if(data==NULL){
		throw MM_OUT;
	}
	
	return this;
}

void* List::get(int index) {
	return data[index];
}

int List::size()
{
	return length;
 } 

void List::destroy() {
	//��������Ԫ��
	free(data);
}

#endif
