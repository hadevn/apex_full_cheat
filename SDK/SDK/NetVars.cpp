#include "Common.h"
#include "NetVars.h"
#include <iomanip>
#include <sstream>

void CNetVars::Initialize()
{
	m_tables.clear();

	client_class *clientClass = CUtils::Read<client_class*>(global::g_hGameImage + OFFSET::uNetVarPtr);
	if (!clientClass)
		return;

	while (clientClass)
	{
		recv_table *recv_table = clientClass->table;
		m_tables.push_back(recv_table);
		clientClass = clientClass->next;
	}
}

int CNetVars::GetOffset(const char *tableName, const char *propName)
{
	int offset = Get_Prop(tableName, propName);
	if (!offset)
	{
		return 0;
	}
	return offset;
}
int CNetVars::Get_Prop(const char *tableName, const char *propName, recv_prop **prop)
{
	
	recv_table *recv_table = GetTable(tableName);
	if (!recv_table)
		return 0;

	int offset = Get_Prop(recv_table, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int CNetVars::Get_Prop(recv_table *recvtable, const char *propName, recv_prop **prop)
{
	int extraOffset = 0;
	for (int i = 0; i < recvtable->num_props; ++i)
	{
		recv_prop *recv_prop = recvtable->props[i];
		recv_table *child = recv_prop->data_table;

		if (child && (child->num_props > 0))
		{
			int tmp = Get_Prop(child, propName, prop);
			if (tmp)
				extraOffset += (recv_prop->offset + tmp);
		}

		if (stricmp(recv_prop->name, propName))
			continue;

		if (prop)
			*prop = recv_prop;

		return (recv_prop->offset + extraOffset);
	}

	return extraOffset;
}

recv_table *CNetVars::GetTable(const char *tableName)
{
	if (m_tables.empty())
		return 0;

	for each (recv_table *table in m_tables)
	{
		if (!table)
			continue;

		if (stricmp(table->name, tableName) == 0)
			return table;
	}

	return 0;
}

void CNetVars::DumpTable(recv_table *table, int depth)
{
	std::string pre("");
	for (int i = 0; i<depth; i++)
		pre.append("\t");

	m_file << pre << table->name << "\n";

	for (int i = 0; i < table->num_props; i++)
	{
		recv_prop *prop = table->props[i];
		if (!prop) continue;

		std::string varName(prop->name);

		if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 || varName.find("2") == 0)
			continue;

		m_file << pre << "\t " << varName << " "
			<< std::setfill('_') << std::setw(60 - varName.length() - (depth * 4))
			<< "[0x" << std::setfill('0') << std::setw(8) << std::hex
			<< std::uppercase << prop->offset << "]\n";

		if (prop->data_table)
			DumpTable(prop->data_table, depth + 1);
	}
}

void CNetVars::DumpNetvars()
{

	m_file.open("C:/netdump.txt");
	m_file << "NetVar Dump by huoji \n\nhaha look proper formatting \n\n";
	for (client_class *pClass = CUtils::Read<client_class*>(global::g_hGameImage + OFFSET::uNetVarPtr); pClass != NULL; pClass = pClass->next)
	{
		recv_table *table = pClass->table;
		DumpTable(table, 0);
	}
	m_file.close();
}

uint32_t CNetVars::GetOffset(const string &TableName, const string& propName)
{
	int offset = Get_Prop(TableName.c_str(), propName.c_str());
	if (!offset)
	{
		return 0;
	}
	return offset;
}
/*
void CNetVars::Initialize()
{
	m_list.clear();

	for (client_class *pClass = CUtils::Read<client_class*>(global::g_hGameImage + OFFSET::uNetVarPtr); pClass != NULL; pClass = pClass->next)
	{
		recv_table *table = pClass->table;
		if (table != NULL)
		{
			NETVAR_TABLE NT;
			NT.TableName = table->name;
			LoadTable(table, &NT);
			m_list.push_back(NT);
		}
	}
}

void CNetVars::LoadTable(recv_table *table, NETVAR_TABLE *pNT)
{
	for (int i = 0; i < table->num_props; i++)
	{
		recv_prop *prop = table->props[i];
		
		if (!prop) continue;

		std::string varName(prop->name);

		if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 || varName.find("2") == 0)
			continue;

		NETVAR_PROPS NP;
		//DbgPrintA("prop:%llX %s", prop, varName.c_str());
		NP.PropName = varName;
		NP.offset = prop->offset;
		NP.pProxFn = prop->proxy_fn;
		pNT->ChildProps.push_back(NP);

		if (prop->data_table)
			LoadTable(prop->data_table, pNT);
	}
}

void CNetVars::Dump()
{
	auto outfile = ofstream("c:\\netvar_dump.txt");
	Dump(outfile);
}

void CNetVars::Dump(ostream &stream)
{
	for (const auto& table : m_list) {
		if (table.ChildProps.empty() )
			continue;
		stream << table.TableName << '\n';
		DumpTable(stream, table, 1);
		stream << '\n\n';
	}
	stream << std::endl;
}

void CNetVars::DumpTable(std::ostream& stream, const NETVAR_TABLE& table, uint32_t indentation)
{
	
	char line_buffer[1024];

	for (const auto& prop : table.ChildProps) {

		m_file << pre << "\t " << varName << " "
			<< std::setfill('_') << std::setw(60 - varName.length() - (depth * 4))
			<< "[0x" << std::setfill('0') << std::setw(8) << std::hex
			<< std::uppercase << prop->m_Offset << "]\n";

		sprintf_s(line_buffer, "proname:%-30s 0x%08X  fn:%llX", prop.PropName.c_str(), prop.offset, prop.pProxFn);
		stream << line_buffer << '\n';
	}
}

uint32_t CNetVars::GetOffset(const string &TableName, const string& propName)
{
	for (const auto& table : m_list) {
		if (table.ChildProps.empty())
			continue;

		if (!table.TableName.compare(TableName))
		{
			for (const auto &prop : table.ChildProps )
			{
				
				if (!prop.PropName.compare(propName))
					return prop.offset;
			}
		}
	}
	return 0;
}

*/