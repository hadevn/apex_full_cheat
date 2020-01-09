#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "utils\ArrayBase.h"
#include "singleton.hpp"

using namespace std;

class recv_prop
{
public:
	int32_t type; //0x0000
	int32_t offset; //0x0004
	char pad_0008[24]; //0x0008
	class recv_table* data_table; //0x0020
	char* name; //0x0028
	bool is_inside_array; //0x0030
	char pad_0031[7]; //0x0031
	class recv_prop* array_prop; //0x0038
	void* proxy_fn; //0x0040
	char pad_0048[12]; //0x0048
	int32_t flags; //0x0054
	char pad_0058[4]; //0x0058
	int32_t num_elements; //0x005C
}; //Size: 0x0060




class recv_table
{
public:
	char pad_0000[8]; //0x0000
	recv_prop** props; //0x0008
	int32_t num_props; //0x0010
	char pad_0014[1196]; //0x0014
	void* decoder; //0x04C0
	char* name; //0x04C8
	bool initialized; //0x04D0
	bool in_main_list; //0x04D1
}; //Size: 0x04D2

class client_class
{
public:
	void* create_fn; //0x0000
	void* create_event_fn; //0x0008
	char* network_name; //0x0010
	recv_table* table; //0x0018
	client_class* next; //0x0020
	int32_t id; //0x0028
	char pad_002C[4]; //0x002C
	char* name; //0x0030
}; //Size: 0x0038



typedef struct
{
	string PropName;
	uint32_t offset;
	void *pProxFn;
}NETVAR_PROPS, *PNETVAR_PROPS;

typedef struct
{
	string TableName;
	vector<NETVAR_PROPS> ChildProps;
}NETVAR_TABLE, *PNETVAR_TABLE;

class CNetVars :public Singleton<CNetVars>
{
public:
	void Initialize();
	void GrabOffsets();
	int GetOffset(const char *tableName, const char *propName);
	void DumpNetvars();
	uint32_t GetOffset(const string & TableName, const string & propName);
private:
	int Get_Prop(const char *tableName, const char *propName, recv_prop **prop = 0);
	int Get_Prop(recv_table *recvTable, const char *propName, recv_prop **prop = 0);
	recv_table *GetTable(const char *tableName);
	std::vector<recv_table*> m_tables;
	void DumpTable(recv_table *table, int depth);
	std::ofstream m_file;
	/*
public:
	void Initialize();

	void Dump();
	void Dump(ostream &stream);
	void DumpTable(std::ostream& stream, const NETVAR_TABLE& table, uint32_t indentation);
	uint32_t GetOffset(const string &TableName, const string& propName);
private:
	void LoadTable(recv_table *table, NETVAR_TABLE *pNT);
	void DumpTable_s(recv_table * table, int depth);
private:
	vector<NETVAR_TABLE> m_list;*/
};

