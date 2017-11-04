#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>

#include "interfaces.h"

//Forward declaration. The class is defined on the cpp file
struct NetvarTable;
class NetvarDatabase;

class netvar_manager
{
private:
	ClientClass*				m_pFirstClass;
	std::vector< RecvTable* >	m_vpTables;
private:
	RecvTable*					GetRecvTable(std::string strTableName);
	int							GetRecvProp(std::string strTableName, std::string strPropName, RecvProp** ppRecvProp = NULL);
	int							GetRecvProp(RecvTable* pRecvTable, std::string strPropName, RecvProp** ppRecvProp = NULL);
	void						DumpTable(RecvTable* pRecvTable);

public:
	netvar_manager(ClientClass* pFirstClass);
	bool						Setup(void);
	bool						HookNetVar(std::string strTableName, std::string strNetVar, RecvVarProxyFn fn);
	DWORD						GetOffset(std::string strTableName, std::string strNetVar);
	void						DumpNetVars(void);
	void						SetFirstClientClass(ClientClass* pFirstClass);
	RecvVarProxyFn				HookProp(const char *tableName, const char *propName, RecvVarProxyFn function);
	RecvTable *GetTable(const char *tableName);
	int GetProp(const char *tableName, const char *propName, RecvProp **prop);
	int GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop);
};

extern netvar_manager* netvars;
#define GET_NETVAR(table, ...) netvars->GetOffset(table, __VA_ARGS__)