/****
*
* Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
*
* @文件名：list.cpp
* @创建时间：2023/2/19
* @创建者：github.com/Climber-Rong
* -----------------------------------------------------------------------------
*文件描述
类似于java的arraylist
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#ifndef LIST_CPP
#define LIST_CPP

#include"stdlib.h"	//需要用到内存管理 

class List {
		// Private section
		//原理：通过realloc对数组大小进行修改，每次扩张都新增十个进行缓冲
		int length;
		int free_len;
		void** data;
	public:
		List();
		List* add(void* ptr);		//添加到末尾，返回this
		List* remove(int index);	//删除第index个元素，返回this
		void* get(int index);		//获取元素
		int size();					//元素数量 
		void destroy();				//销毁
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
		//空余不足
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
		data[i-1] = data[i];		//往前移动 
	} 
	length--;
	free_len++;
	if(free_len>10){
		//删除元素过多导致空闲内存空间过多
		realloc(data, length*sizeof(void**));
		free_len = 0;		//不设置多余空间 
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
	//并不销毁元素
	free(data);
}

#endif
