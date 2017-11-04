#include "netvar_manager.h"

netvar_manager* netvars = nullptr;
//FILE* pHurensohn = nullptr;
RecvTable* netvar_manager::GetRecvTable(std::string strTableName)
{
	if (m_vpTables.empty())
		return nullptr;

	for each(RecvTable* pRecvTable in m_vpTables)
	{
		if (!pRecvTable)
			continue;

		if (!strTableName.compare(pRecvTable->GetName()))
			return pRecvTable;
	}

	return nullptr;
}

int netvar_manager::GetRecvProp(std::string strTableName, std::string strPropName, RecvProp** ppRecvProp)
{
	RecvTable* pRecvTable = this->GetRecvTable(strTableName);
	if (!pRecvTable)
		return 0;

	return this->GetRecvProp(pRecvTable, strPropName, ppRecvProp);
}

int netvar_manager::GetRecvProp(RecvTable* pRecvTable, std::string strPropName, RecvProp** ppRecvProp)
{
	if (strPropName.empty())
		return 0;

	int iExtraOffset = 0;
	for (int i = 0; i < pRecvTable->GetNumProps(); ++i)
	{
		RecvProp* pRecvProp = pRecvTable->GetProp(i);
		RecvTable* pRecvChlidTable = pRecvProp->GetDataTable();

		if (pRecvChlidTable && (pRecvChlidTable->GetNumProps() > 0))
		{
			int iTempOffset = this->GetRecvProp(pRecvChlidTable, strPropName);
			if (iTempOffset)
				iExtraOffset += pRecvProp->GetOffset() + iTempOffset;
		}

		if (strPropName.compare(pRecvProp->GetName()))
			continue;

		if (ppRecvProp)
			*ppRecvProp = pRecvProp;

		return pRecvProp->GetOffset() + iExtraOffset;
	}

	return iExtraOffset;
}

void netvar_manager::DumpTable(RecvTable* pRecvTable)
{
	for (int i = 0; i < pRecvTable->GetNumProps(); i++)
	{
		RecvProp* pRecvProp = pRecvTable->GetProp(i);
		if (!pRecvProp)
			continue;

		if (!std::string("baseclass").compare(pRecvProp->GetName()))
			continue;

		if (isdigit(pRecvProp->GetName()[0]))
			continue;

		printf("-> %s --> 0x%X \n", pRecvProp->GetName(), pRecvProp->GetOffset());
		//fprintf( pHurensohn, "--> %s [ 0x%X ]\n", pRecvProp->GetName( ), pRecvProp->GetOffset( ) );
		RecvTable* pRecvDataTable = pRecvProp->GetDataTable();
		if (pRecvDataTable)
			this->DumpTable(pRecvDataTable);
	}
}

netvar_manager::netvar_manager(ClientClass* pFirstClass)
{
	this->SetFirstClientClass(pFirstClass);
}

bool netvar_manager::Setup(void)
{
	m_vpTables.clear();

	if (!m_pFirstClass)
		return false;

	ClientClass* pClass = m_pFirstClass;

	while (pClass)
	{
		RecvTable* pRecvTable = pClass->m_pRecvTable;
		m_vpTables.push_back(pRecvTable);

		pClass = pClass->m_pNext;
	}

	return true;
}

bool netvar_manager::HookNetVar(std::string strTableName, std::string strNetVar, RecvVarProxyFn fn)
{
	RecvProp* pRecvProp = 0;
	this->GetRecvProp(strTableName, strNetVar, &pRecvProp);

	if (!pRecvProp)
		return false;

	pRecvProp->SetProxyFn(fn);

	printf("Hooked prop: %s from table: %s \n", strNetVar, strTableName);

	return true;
}
RecvTable *netvar_manager::GetTable(const char *tableName)
{
	if (m_vpTables.empty())
	{
		printf("Failed to find table: %s (m_tables is empty)", tableName);
		return 0;
	}


	for each (RecvTable *table in m_vpTables)
	{
		if (!table)
		{
			continue;
		}


		if (_stricmp(table->m_pNetTableName, tableName) == 0)
		{
			return table;
		}
	}

	return 0;
}
RecvVarProxyFn netvar_manager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function)
{
	RecvProp *recvProp = 0;

	if (!GetProp(tableName, propName, &recvProp))
	{
		printf("Failed to hook prop: %s from table: %s", propName, tableName);
		return 0;
	}


	RecvVarProxyFn old = recvProp->m_ProxyFn;
	recvProp->m_ProxyFn = function;
	printf("Hooked prop: %s from table: %s \n", propName, tableName);
	return old;
}
int netvar_manager::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];

		RecvTable *child = recvProp->m_pDataTable;

		if (child
			&& (child->m_nProps > 0))
		{
			int tmp = GetProp(child, propName, prop);

			if (tmp)
			{
				extraOffset += (recvProp->m_Offset + tmp);
			}
		}


		// do this for all used props that are two of in 1 datatable
		if (!_stricmp(propName, "m_flStamina") && _stricmp(recvTable->m_pNetTableName, "DT_CSLocalPlayerExclusive"))
		{
			continue;
		}

		if (_stricmp(recvProp->m_pVarName, propName))
		{
			continue;
		}

		if (prop && !*prop)
		{
			*prop = recvProp;
		}

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}
int netvar_manager::GetProp(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);

	if (!recvTable)
	{
		printf("Failed to find table: %s", tableName);
		return 0;
	}


	int offset = GetProp(recvTable, propName, prop);

	if (!offset)
	{
		printf("Failed to find prop: %s from table: %s", propName, tableName);
		return 0;
	}


	return offset;
}
DWORD netvar_manager::GetOffset(std::string strTableName, std::string strNetVar)
{
	if (strTableName.empty() || strNetVar.empty())
		return 0;

	return (DWORD)this->GetRecvProp(strTableName, strNetVar);
}

void netvar_manager::DumpNetVars(void)
{
	//fopen_s( &pHurensohn, "D:\\netvarsya.txt", "w" );
	for (ClientClass* pClass = m_pFirstClass; pClass != NULL; pClass = pClass->m_pNext)
	{
		RecvTable* pRecvTable = pClass->m_pRecvTable;
		if (pRecvTable)
		{
			//printf( "---------[ %s ]---------\n", pRecvTable->GetName( ) );
			//fprintf( pHurensohn, "---------[ %s ]---------\n", pRecvTable->GetName( ) );
			DumpTable(pRecvTable);
		}
	}
	//fclose( pHurensohn );
}

void netvar_manager::SetFirstClientClass(ClientClass* pFirstClass)
{
	m_pFirstClass = pFirstClass;
}
