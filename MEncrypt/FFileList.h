#include <stdio.h>
#include <list>

using namespace std;

class FNode {
public:
	FNode()
	{
		memset(m_name,0,256);
		m_size	 = 0;
		m_offset = 0;
	}

	void SetName(char* str)	
	{
		if(strlen(str) > 255) return;
		strcpy(m_name,str);
		str[255] = 0;
	}

public:

	int	 m_size;
	int	 m_offset;
	char m_name[256];
};


class FFileList :public list<FNode*>
{
public:
	FFileList(){}
	virtual ~FFileList()
	{
		DelAll();
	}

	void Add(FNode* pNode) 
	{
		push_back(pNode);
	}
	void DelAll() 
	{
		if(size()==0) return;

		iterator node;

		for(node = begin(); node != end(); ) 
		{
			delete (*node);
			(*node) = NULL;
			node = erase(node);
		}
	}
};


bool GetFindFileListWin(char* path,char* ext,FFileList& pList);