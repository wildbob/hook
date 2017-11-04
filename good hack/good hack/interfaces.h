#pragma once

#include "helpers.h"
#include "vector.h"

typedef ULONG HFont;

//this is where all the interfaces are
class i_net_channel
{
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMPENTS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char  *GetName(void) const = 0;	// get channel name
	virtual const char  *GetAddress(void) const = 0; // get channel IP address as string
	virtual float		GetTime(void) const = 0;	// current net time
	virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
	virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut(void) const = 0;	// true if timing out
	virtual bool		IsPlayback(void) const = 0;	// true if demo playback

	virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			GetTotalPackets(int flow) const = 0;
	virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		GetStreamProgress(int flow, int *received, int *total) const = 0;  // TCP progress if transmitting
	virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float *pflFrameTime, float *pflFrameTimeStdDeviation, float *pflFrameStartTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};


class player_info_t
{
public:
	__int64        unknown;            //0x0000 
	__int64        steamID64;          //0x0008 - SteamID64
	char           szName[128];        //0x0010 - Player Name
	int            userId;             //0x0090 - Unique Server Identifier
	char           szSteamID[20];      //0x0094 - STEAM_X:Y:Z
	char           pad_0x00A8[0x10];   //0x00A8
	unsigned long  iSteamID;           //0x00B8 - SteamID 
	char           unknown2[0x14C];
	int xuidlow;
	int xuidhigh;
};

class iv_engine_client
{
public:
	int get_local_player()
	{
		typedef int(__thiscall *get_local_playerfn)(void*);
		return g_utils::get_v_func<get_local_playerfn>(this, 12)(this);
	}
	void get_screen_size(int& width, int& height)
	{
		typedef int(__thiscall *OrigFn)(void*, int&, int&);
		g_utils::get_v_func<OrigFn>(this, 5)(this, width, height);
	}

	bool get_player_info(int ent_num, player_info_t *pinfo)
	{
		typedef bool(__thiscall *OrigFn)(void*, int, player_info_t*);
		return g_utils::get_v_func<OrigFn>(this, 8)(this, ent_num, pinfo);
	}
	int get_player_user_id(int UserID)
	{
		using Original = int(__thiscall*)(PVOID, int);
		return g_utils::get_v_func<Original>(this, 9)(this, UserID);
	}
	float get_last_time_stamp() {
		typedef float(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 14)(this);
	}

	void get_view_angles(QAngle& va)
	{
		typedef void(__thiscall *OrigFn)(void*, QAngle&);
		g_utils::get_v_func<OrigFn>(this, 18)(this, va);
	}

	void set_view_angles(QAngle& va)
	{
		typedef void(__thiscall *OrigFn)(void*, QAngle&);
		g_utils::get_v_func<OrigFn>(this, 19)(this, va);
	}

	int get_max_clients() {
		typedef int(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 20)(this);
	}

	bool is_in_game() {
		typedef bool(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 26)(this);
	}

	bool is_connected() {
		typedef bool(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 27)(this);
	}

	const VMatrix& world_to_screen_matrix()
	{
		typedef const VMatrix&(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 37)(this);
	}

	i_net_channel*get_net_channel_info()
	{
		typedef i_net_channel*(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 78)(this);
	}

	void execute_client_cmd(const char* szCmdString) {
		typedef void(__thiscall *OrigFn)(void*, const char *);
		g_utils::get_v_func<OrigFn>(this, 108)(this, szCmdString);
	}

	void client_cmd_unrestricted(const char* szCmdString)
	{
		typedef void(__thiscall* OrigFn)(void*, const char*, char);
		g_utils::get_v_func<OrigFn>(this, 114)(this, szCmdString, 1);
	}
};
// just gonna throw heaps of shit in here cuz im lazy as fuck
class i_collideable
{
public:
	const Vector& OBBMins()
	{
		typedef  Vector&(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 1)(this);
	}
	const  Vector& OBBMaxs()
	{
		typedef Vector&(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 2)(this);
	}
};
class RecvTable;
class RecvProp;
#define MAX_DATATABLES		1024	// must be a power of 2.
#define MAX_DATATABLE_PROPS	4096

#define MAX_ARRAY_ELEMENTS	2048		// a network array should have more that 1024 elements

#define HIGH_DEFAULT		-121121.121121f

#define BITS_FULLRES	-1	// Use the full resolution of the type being encoded.
#define BITS_WORLDCOORD	-2	// Encode as a world coordinate.

#define DT_MAX_STRING_BITS			9
#define DT_MAX_STRING_BUFFERSIZE	(1<<DT_MAX_STRING_BITS)	// Maximum length of a string that can be sent.

#define STRINGBUFSIZE(className, varName)	sizeof( ((className*)0)->varName )

// Gets the size of a variable in a class.
#define PROPSIZEOF(className, varName)		sizeof(((className*)0)->varName)


// SendProp::m_Flags.
#define SPROP_UNSIGNED			(1<<0)	// Unsigned integer data.

#define SPROP_COORD				(1<<1)	// If this is set, the float/vector is treated like a world coordinate.
// Note that the bit count is ignored in this case.

#define SPROP_NOSCALE			(1<<2)	// For floating point, don't scale into range, just take value as is.

#define SPROP_ROUNDDOWN			(1<<3)	// For floating point, limit high value to range minus one bit unit

#define SPROP_ROUNDUP			(1<<4)	// For floating point, limit low value to range minus one bit unit

#define SPROP_NORMAL			(1<<5)	// If this is set, the vector is treated like a normal (only valid for vectors)

#define SPROP_EXCLUDE			(1<<6)	// This is an exclude prop (not excludED, but it points at another prop to be excluded).

#define SPROP_XYZE				(1<<7)	// Use XYZ/Exponent encoding for vectors.

#define SPROP_INSIDEARRAY		(1<<8)	// This tells us that the property is inside an array, so it shouldn't be put into the
// flattened property list. Its array will point at it when it needs to.

#define SPROP_PROXY_ALWAYS_YES	(1<<9)	// Set for datatable props using one of the default datatable proxies like
// SendProxy_DataTableToDataTable that always send the data to all clients.

#define SPROP_CHANGES_OFTEN		(1<<10)	// this is an often changed field, moved to head of sendtable so it gets a small index

#define SPROP_IS_A_VECTOR_ELEM	(1<<11)	// Set automatically if SPROP_VECTORELEM is used.

#define SPROP_COLLAPSIBLE		(1<<12)	// Set automatically if it's a datatable with an offset of 0 that doesn't change the pointer
// (ie: for all automatically-chained base classes).
// In this case, it can get rid of this SendPropDataTable altogether and spare the
// trouble of walking the hierarchy more than necessary.

#define SPROP_COORD_MP					(1<<13) // Like SPROP_COORD, but special handling for multiplayer games
#define SPROP_COORD_MP_LOWPRECISION 	(1<<14) // Like SPROP_COORD, but special handling for multiplayer games where the fractional component only gets a 3 bits instead of 5
#define SPROP_COORD_MP_INTEGRAL			(1<<15) // SPROP_COORD_MP, but coordinates are rounded to integral boundaries
#define SPROP_NUMFLAGBITS_NETWORKED		16

// This is server side only, it's used to mark properties whose SendProxy_* functions encode against gpGlobals->tickcount (the only ones that currently do this are
//  m_flAnimTime and m_flSimulationTime.  MODs shouldn't need to mess with this probably
#define SPROP_ENCODED_AGAINST_TICKCOUNT	(1<<16)

// See SPROP_NUMFLAGBITS_NETWORKED for the ones which are networked
#define SPROP_NUMFLAGBITS				17

// Used by the SendProp and RecvProp functions to disable debug checks on type sizes.
#define SIZEOF_IGNORE		-1


// Use this to extern send and receive datatables, and reference them.
#define EXTERN_SEND_TABLE(tableName)	namespace tableName {extern SendTable g_SendTable;}
#define EXTERN_RECV_TABLE(tableName)	namespace tableName {extern RecvTable g_RecvTable;}

#define REFERENCE_SEND_TABLE(tableName)	tableName::g_SendTable
#define REFERENCE_RECV_TABLE(tableName)	tableName::g_RecvTable


class SendProp;


typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
	DPT_Quaternion,
#endif
	DPT_NUMSendPropTypes
} SendPropType;

#include <stdio.h>

class DVariant
{
public:
	DVariant() { m_Type = DPT_Float; }
	DVariant(float val) { m_Type = DPT_Float; m_Float = val; }

	const char *ToString()
	{
		static char text[128];

		switch (m_Type)
		{
		case DPT_Int:
			sprintf_s(text, sizeof(text), "%i", m_Int);
			break;
		case DPT_Float:
			sprintf_s(text, sizeof(text), "%.3f", m_Float);
			break;
		case DPT_Vector:
			sprintf_s(text, sizeof(text), "(%.3f,%.3f,%.3f)",
				m_Vector[0], m_Vector[1], m_Vector[2]);
			break;
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
		case DPT_Quaternion:
			sprintf_s(text, sizeof(text), "(%.3f,%.3f,%.3f %.3f)",
				m_Vector[0], m_Vector[1], m_Vector[2], m_Vector[3]);
			break;
#endif
		case DPT_String:
			if (m_pString)
				return m_pString;
			else
				return "NULL";
			break;
		case DPT_Array:
			sprintf_s(text, sizeof(text), "Array");
			break;
		case DPT_DataTable:
			sprintf_s(text, sizeof(text), "DataTable");
			break;
		default:
			sprintf_s(text, sizeof(text), "DVariant type %i unknown", m_Type);
			break;
		}

		return text;
	}

	union
	{
		float	m_Float;
		long	m_Int;
		char	*m_pString;
		void	*m_pData;	// For DataTables.
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
		float	m_Vector[4];
#else
		float	m_Vector[3];
#endif
	};
	SendPropType	m_Type;
};
// This is passed into RecvProxy functions.
class CRecvProxyData
{
public:
	const RecvProp	*m_pRecvProp;		// The property it's receiving.

	DVariant		m_Value;			// The value given to you to store.

	int				m_iElement;			// Which array element you're getting.

	int				m_ObjectID;			// The object being referred to.
};


//-----------------------------------------------------------------------------
// pStruct = the base structure of the datatable this variable is in (like C_BaseEntity)
// pOut    = the variable that this this proxy represents (like C_BaseEntity::m_SomeValue).
//
// Convert the network-standard-type value in m_Value into your own format in pStruct/pOut.
//-----------------------------------------------------------------------------
typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

// ------------------------------------------------------------------------ //
// ArrayLengthRecvProxies are optionally used to get the length of the 
// incoming array when it changes.
// ------------------------------------------------------------------------ //
typedef void(*ArrayLengthRecvProxyFn)(void *pStruct, int objectID, int currentArrayLength);


// NOTE: DataTable receive proxies work differently than the other proxies.
// pData points at the object + the recv table's offset.
// pOut should be set to the location of the object to unpack the data table into.
// If the parent object just contains the child object, the default proxy just does *pOut = pData.
// If the parent object points at the child object, you need to dereference the pointer here.
// NOTE: don't ever return null from a DataTable receive proxy function. Bad things will happen.
typedef void(*DataTableRecvVarProxyFn)(const RecvProp *pProp, void **pOut, void *pData, int objectID);


// This is used to fork over the standard proxy functions to the engine so it can
// make some optimizations.
class CStandardRecvProxies
{
public:
	CStandardRecvProxies();

	RecvVarProxyFn m_Int32ToInt8;
	RecvVarProxyFn m_Int32ToInt16;
	RecvVarProxyFn m_Int32ToInt32;
	RecvVarProxyFn m_FloatToFloat;
	RecvVarProxyFn m_VectorToVector;
};
extern CStandardRecvProxies g_StandardRecvProxies;


class CRecvDecoder;


class RecvProp
{
	// This info comes from the receive data table.
public:
	RecvProp();

	void					InitArray(int nElements, int elementStride);

	int						GetNumElements() const;
	void					SetNumElements(int nElements);

	int						GetElementStride() const;
	void					SetElementStride(int stride);

	int						GetFlags() const;

	const char*				GetName() const;
	SendPropType			GetType() const;

	RecvTable*				GetDataTable() const;
	void					SetDataTable(RecvTable *pTable);

	RecvVarProxyFn			GetProxyFn() const;
	void					SetProxyFn(RecvVarProxyFn fn);

	DataTableRecvVarProxyFn	GetDataTableProxyFn() const;
	void					SetDataTableProxyFn(DataTableRecvVarProxyFn fn);

	int						GetOffset() const;
	void					SetOffset(int o);

	// Arrays only.
	RecvProp*				GetArrayProp() const;
	void					SetArrayProp(RecvProp *pProp);

	// Arrays only.
	void					SetArrayLengthProxy(ArrayLengthRecvProxyFn proxy);
	ArrayLengthRecvProxyFn	GetArrayLengthProxy() const;

	bool					IsInsideArray() const;
	void					SetInsideArray();

	// Some property types bind more data to the prop in here.
	const void*			GetExtraData() const;
	void				SetExtraData(const void *pData);

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char*			GetParentArrayPropName();
	void				SetParentArrayPropName(const char *pArrayPropName);

public:

	char					*m_pVarName;
	SendPropType			m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;


public:

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

												// Extra data that certain special property types bind to the property here.
	const void *m_pExtraData;

	// If this is an array (DPT_Array).
	RecvProp				*m_pArrayProp;
	ArrayLengthRecvProxyFn	m_ArrayLengthProxy;

	RecvVarProxyFn			m_ProxyFn;
	DataTableRecvVarProxyFn	m_DataTableProxyFn;	// For RDT_DataTable.

	RecvTable				*m_pDataTable;		// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char				*m_pParentArrayPropName;
};


class RecvTable
{
public:

	typedef RecvProp	PropType;

	RecvTable();
	RecvTable(RecvProp *pProps, int nProps, const char *pNetTableName);
	~RecvTable();

	void		Construct(RecvProp *pProps, int nProps, const char *pNetTableName);

	int			GetNumProps();
	RecvProp*	GetProp(int i);

	const char*	GetName();

	// Used by the engine while initializing array props.
	void		SetInitialized(bool bInitialized);
	bool		IsInitialized() const;

	// Used by the engine.
	void		SetInMainList(bool bInList);
	bool		IsInMainList() const;


public:

	// Properties described in a table.
	RecvProp		*m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	CRecvDecoder	*m_pDecoder;

	const char		*m_pNetTableName;	// The name matched between client and server.


private:

	bool			m_bInitialized;
	bool			m_bInMainList;
};


inline int RecvTable::GetNumProps()
{
	return m_nProps;
}

inline RecvProp* RecvTable::GetProp(int i)
{
	// Assert( i >= 0 && i < m_nProps ); 
	return &m_pProps[i];
}

inline const char* RecvTable::GetName()
{
	return m_pNetTableName;
}

inline void RecvTable::SetInitialized(bool bInitialized)
{
	m_bInitialized = bInitialized;
}

inline bool RecvTable::IsInitialized() const
{
	return m_bInitialized;
}

inline void RecvTable::SetInMainList(bool bInList)
{
	m_bInMainList = bInList;
}

inline bool RecvTable::IsInMainList() const
{
	return m_bInMainList;
}


// ------------------------------------------------------------------------------------------------------ //
// See notes on BEGIN_SEND_TABLE for a description. These macros work similarly.
// ------------------------------------------------------------------------------------------------------ //
#define BEGIN_RECV_TABLE(className, tableName) \
	BEGIN_RECV_TABLE_NOBASE(className, tableName) \
		RecvPropDataTable("baseclass", 0, 0, className::BaseClass::m_pClassRecvTable, DataTableRecvProxy_StaticDataTable),

#define BEGIN_RECV_TABLE_NOBASE(className, tableName) \
	template <typename T> int ClientClassInit(T *); \
	namespace tableName { \
		struct ignored; \
			} \
	template <> int ClientClassInit<tableName::ignored>(tableName::ignored *); \
	namespace tableName {	\
		RecvTable g_RecvTable; \
		int g_RecvTableInit = ClientClassInit((tableName::ignored *)NULL); \
			} \
	template <> int ClientClassInit<tableName::ignored>(tableName::ignored *) \
			{ \
		typedef className currentRecvDTClass; \
		const char *pRecvTableName = #tableName; \
		RecvTable &RecvTable = tableName::g_RecvTable; \
		static RecvProp RecvProps[] = { \
			RecvPropInt("should_never_see_this", 0, sizeof(int)),		// It adds a dummy property at the start so you can define "empty" SendTables.

#define END_RECV_TABLE() \
					}; \
		RecvTable.Construct(RecvProps+1, sizeof(RecvProps) / sizeof(RecvProp) - 1, pRecvTableName); \
		return 1; \
			}


#define RECVINFO(varName)						#varName, offsetof(currentRecvDTClass, varName), sizeof(((currentRecvDTClass*)0)->varName)
#define RECVINFO_NAME(varName, remoteVarName)	#remoteVarName, offsetof(currentRecvDTClass, varName), sizeof(((currentRecvDTClass*)0)->varName)
#define RECVINFO_STRING(varName)				#varName, offsetof(currentRecvDTClass, varName), STRINGBUFSIZE(currentRecvDTClass, varName)
#define RECVINFO_BASECLASS(tableName)			RecvPropDataTable("this", 0, 0, &REFERENCE_RECV_TABLE(tableName))
#define RECVINFO_ARRAY(varName)					#varName, offsetof(currentRecvDTClass, varName), sizeof(((currentRecvDTClass*)0)->varName[0]), sizeof(((currentRecvDTClass*)0)->varName)/sizeof(((currentRecvDTClass*)0)->varName[0])

// Just specify the name and offset. Used for strings and data tables.
#define RECVINFO_NOSIZE(varName)				#varName, offsetof(currentRecvDTClass, varName)
#define RECVINFO_DT(varName)					RECVINFO_NOSIZE(varName)
#define RECVINFO_DTNAME(varName,remoteVarName)	#remoteVarName, offsetof(currentRecvDTClass, varName)


void RecvProxy_FloatToFloat(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_VectorToVector(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_QuaternionToQuaternion(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_Int32ToInt8(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_Int32ToInt16(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_StringToString(const CRecvProxyData *pData, void *pStruct, void *pOut);
void RecvProxy_Int32ToInt32(const CRecvProxyData *pData, void *pStruct, void *pOut);

// StaticDataTable does *pOut = pData.
void DataTableRecvProxy_StaticDataTable(const RecvProp *pProp, void **pOut, void *pData, int objectID);

// PointerDataTable does *pOut = *((void**)pData)   (ie: pData is a pointer to the object to decode into).
void DataTableRecvProxy_PointerDataTable(const RecvProp *pProp, void **pOut, void *pData, int objectID);


RecvProp RecvPropFloat(
	const char *pVarName,
	int offset,
	int sizeofVar = SIZEOF_IGNORE,	// Handled by RECVINFO macro, but set to SIZEOF_IGNORE if you don't want to bother.
	int flags = 0,
	RecvVarProxyFn varProxy = RecvProxy_FloatToFloat
);

RecvProp RecvPropVector(
	const char *pVarName,
	int offset,
	int sizeofVar = SIZEOF_IGNORE,	// Handled by RECVINFO macro, but set to SIZEOF_IGNORE if you don't want to bother.
	int flags = 0,
	RecvVarProxyFn varProxy = RecvProxy_VectorToVector
);

// This is here so the RecvTable can look more like the SendTable.
#define RecvPropQAngles RecvPropVector

#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!

RecvProp RecvPropQuaternion(
	const char *pVarName,
	int offset,
	int sizeofVar = SIZEOF_IGNORE,	// Handled by RECVINFO macro, but set to SIZEOF_IGNORE if you don't want to bother.
	int flags = 0,
	RecvVarProxyFn varProxy = RecvProxy_QuaternionToQuaternion
);
#endif

RecvProp RecvPropInt(
	const char *pVarName,
	int offset,
	int sizeofVar = SIZEOF_IGNORE,	// Handled by RECVINFO macro, but set to SIZEOF_IGNORE if you don't want to bother.
	int flags = 0,
	RecvVarProxyFn varProxy = 0
);

RecvProp RecvPropString(
	const char *pVarName,
	int offset,
	int bufferSize,
	int flags = 0,
	RecvVarProxyFn varProxy = RecvProxy_StringToString
);

RecvProp RecvPropDataTable(
	const char *pVarName,
	int offset,
	int flags,
	RecvTable *pTable,
	DataTableRecvVarProxyFn varProxy = DataTableRecvProxy_StaticDataTable
);

RecvProp RecvPropArray3(
	const char *pVarName,
	int offset,
	int sizeofVar,
	int elements,
	RecvProp pArrayProp,
	DataTableRecvVarProxyFn varProxy = DataTableRecvProxy_StaticDataTable
);

// Use the macro to let it automatically generate a table name. You shouldn't 
// ever need to reference the table name. If you want to exclude this array, then
// reference the name of the variable in varTemplate.
RecvProp InternalRecvPropArray(
	const int elementCount,
	const int elementStride,
	const char *pName,
	ArrayLengthRecvProxyFn proxy
);


//
// Use this if you want to completely manage the way the array data is stored.
// You'll need to provide a proxy inside varTemplate that looks for 'iElement'
// to figure out where to store the specified element.
//
#define RecvPropVirtualArray( arrayLengthProxy, maxArrayLength, varTemplate, propertyName ) \
	varTemplate, \
	InternalRecvPropArray( \
		maxArrayLength, \
		0, \
		#propertyName, \
		arrayLengthProxy \
		)


// Use this and pass the array name and it will figure out the count and stride automatically.
#define RecvPropVariableLengthArray( arrayLengthProxy, varTemplate, arrayName )			\
	varTemplate,										\
	InternalRecvPropArray(								\
		sizeof(((currentRecvDTClass*)0)->arrayName) / PROPSIZEOF(currentRecvDTClass, arrayName[0]), \
		PROPSIZEOF(currentRecvDTClass, arrayName[0]),	\
		#arrayName,										\
		arrayLengthProxy								\
		)


// Use this and pass the array name and it will figure out the count and stride automatically.
#define RecvPropArray( varTemplate, arrayName )			\
	RecvPropVariableLengthArray( 0, varTemplate, arrayName )


// Use this one to specify the element count and stride manually.
#define RecvPropArray2( arrayLengthProxy, varTemplate, elementCount, elementStride, arrayName )		\
	varTemplate,																	\
	InternalRecvPropArray( elementCount, elementStride, #arrayName, arrayLengthProxy )


// ---------------------------------------------------------------------------------------- //
// Inlines.
// ---------------------------------------------------------------------------------------- //


inline int RecvProp::GetNumElements() const
{
	return m_nElements;
}

inline void RecvProp::SetNumElements(int nElements)
{
	m_nElements = nElements;
}

inline int RecvProp::GetElementStride() const
{
	return m_ElementStride;
}

inline void RecvProp::SetElementStride(int stride)
{
	m_ElementStride = stride;
}

inline int RecvProp::GetFlags() const
{
	return m_Flags;
}

inline const char* RecvProp::GetName() const
{
	return m_pVarName;
}


inline RecvTable* RecvProp::GetDataTable() const
{
	return m_pDataTable;
}

inline void RecvProp::SetDataTable(RecvTable *pTable)
{
	m_pDataTable = pTable;
}

inline RecvVarProxyFn RecvProp::GetProxyFn() const
{
	return m_ProxyFn;
}

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
{
	m_ProxyFn = fn;
}

inline DataTableRecvVarProxyFn RecvProp::GetDataTableProxyFn() const
{
	return m_DataTableProxyFn;
}

inline void RecvProp::SetDataTableProxyFn(DataTableRecvVarProxyFn fn)
{
	m_DataTableProxyFn = fn;
}

inline int RecvProp::GetOffset() const
{
	return m_Offset;
}

inline void RecvProp::SetOffset(int o)
{
	m_Offset = o;
}

inline RecvProp* RecvProp::GetArrayProp() const
{
	return m_pArrayProp;
}

inline void RecvProp::SetArrayProp(RecvProp *pProp)
{
	m_pArrayProp = pProp;
}

inline void RecvProp::SetArrayLengthProxy(ArrayLengthRecvProxyFn proxy)
{
	m_ArrayLengthProxy = proxy;
}

inline ArrayLengthRecvProxyFn RecvProp::GetArrayLengthProxy() const
{
	return m_ArrayLengthProxy;
}

inline bool RecvProp::IsInsideArray() const
{
	return m_bInsideArray;
}

inline void RecvProp::SetInsideArray()
{
	m_bInsideArray = true;
}

inline const void* RecvProp::GetExtraData() const
{
	return m_pExtraData;
}

inline void RecvProp::SetExtraData(const void *pData)
{
	m_pExtraData = pData;
}

inline const char* RecvProp::GetParentArrayPropName()
{
	return m_pParentArrayPropName;
}

inline void	RecvProp::SetParentArrayPropName(const char *pArrayPropName)
{
	m_pParentArrayPropName = pArrayPropName;
}
class IClientNetworkable;

typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable*   (*CreateEventFn)();
class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn* m_pCreateEventFn;
	char			*m_pNetworkName;
	RecvTable		*m_pRecvTable;
	ClientClass		*m_pNext;
	int				m_ClassID;
};
struct bf_read;
class IClientUnknown;
class IClientNetworkable
{
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual void                       Release() = 0;
	virtual ClientClass*               GetClientClass() = 0;
	virtual void                       NotifyShouldTransmit(int state) = 0;
	virtual void                       OnPreDataChanged(int updateType) = 0;
	virtual void                       OnDataChanged(int updateType) = 0;
	virtual void                       PreDataUpdate(int updateType) = 0;
	virtual void                       PostDataUpdate(int updateType) = 0;
	virtual void                       Unknown() = 0;
	virtual bool                       IsDormant() = 0;
	virtual int                        EntIndex() const = 0;
	virtual void                       ReceiveMessage(int classID, bf_read &msg) = 0;
	virtual void*                      GetDataTableBasePtr() = 0;
	virtual void                       SetDestroyedOnRecreateEntities() = 0;
};
struct model_t;
class i_client_entity
{ // 0x00 -> IClientUnknown, 0x04 IClientRenderable, 0x08 IClientNetworkable, ..
public:

	i_collideable* get_collideable()
	{
		typedef i_collideable*(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 3)(this);
	}

	const model_t* get_model()
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef const model_t*(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(pRenderable, 8)(pRenderable);
	}

	bool setup_bones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef bool(__thiscall *OrigFn)(void*, matrix3x4_t*, int, int, float);
		return g_utils::get_v_func<OrigFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

	ClientClass* get_client_class()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef ClientClass*(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(pNetworked, 2)(pNetworked);
	}

	bool is_dormant()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef bool(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(pNetworked, 9)(pNetworked);
	}

	int get_index()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef int(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(pNetworked, 10)(pNetworked);
	}
};
class i_client_mode
{
public:
	bool should_draw_entity(i_client_entity *pEnt)
	{

		typedef bool(__thiscall *OrigFn)(void*, i_client_entity*);
		return g_utils::get_v_func<OrigFn>(this, 14)(this, pEnt);
	}
};

class i_client
{
public:
	ClientClass* get_class(void)
	{
		typedef ClientClass*(__thiscall* OringFn)(PVOID);
		return g_utils::get_v_func< OringFn >(this, 8)(this);
	}
};

class i_client_entity_list
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual i_client_entity *		get_entity(int entnum);
	virtual i_client_entity *		get_entity_handle(c_base_handle hEnt) = 0;
	virtual int					num_of_entites(bool bIncludeNonNetworkable) = 0;
	virtual int					get_hightest_entity_index(void);
	virtual void				set_max_entities(int maxents);
	virtual int					get_max_entities();
};


#include "checksum_crc.hpp"
#include "checksum_md5.hpp"

class c_cmd
{
public:
	c_cmd()
	{
		memset(this, 0, sizeof(*this));
	};
	virtual ~c_cmd() {};

	CRC32_t GetChecksum(void) const
	{
		CRC32_t crc;
		CRC32_Init(&crc);

		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

		CRC32_Final(&crc);
		return crc;
	}

	int     command_number;     // 0x04 For matching server and client commands for debugging
	int     tick_count;         // 0x08 the tick the client created this command
	QAngle  viewangles;         // 0x0C Player instantaneous view angles.
	Vector  aimdirection;       // 0x18
	float   forwardmove;        // 0x24
	float   sidemove;           // 0x28
	float   upmove;             // 0x2C
	int     buttons;            // 0x30 Attack button states
	char    impulse;            // 0x34
	int     weaponselect;       // 0x38 Current weapon id
	int     weaponsubtype;      // 0x3C
	int     random_seed;        // 0x40 For shared random functions
	short   mousedx;            // 0x44 mouse accum in x from create move
	short   mousedy;            // 0x46 mouse accum in y from create move
	bool    hasbeenpredicted;   // 0x48 Client only, tracks whether we've predicted this command at least once
	char    pad_0x4C[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};

class CVerifiedUserCmd
{
public:
	c_cmd m_cmd;
	CRC32_t  m_crc;
};


class i_surface
{
public:
	void draw_set_color(Color col)
	{
		typedef void(__thiscall *OrigFn)(void*, Color);
		g_utils::get_v_func<OrigFn>(this, 14)(this, col);
	}

	void draw_filled_rect(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
		g_utils::get_v_func<OrigFn>(this, 16)(this, x0, y0, x1, y1);
	}

	void draw_outlined_rect(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
		g_utils::get_v_func<OrigFn>(this, 18)(this, x0, y0, x1, y1);
	}
	void get_cursor_pos(int& x, int& y)
	{
		typedef void(__thiscall *OrigFn)(PVOID, int&, int&);
		g_utils::get_v_func<OrigFn>(this, 100)(this, x, y);
	}
	void draw_line(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
		g_utils::get_v_func<OrigFn>(this, 19)(this, x0, y0, x1, y1);
	}
	void draw_outlined_circle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall *OrigFn)(PVOID, int, int, int, int);
		g_utils::get_v_func<OrigFn>(this, 103)(this, x, y, radius, segments);
	}
	void draw_set_font(HFont font) {
		typedef void(__thiscall *OrigFn)(void*, HFont);
		g_utils::get_v_func<OrigFn>(this, 23)(this, font);
	}

	void draw_set_text_color(Color col) {
		typedef void(__thiscall *OrigFn)(void*, Color);
		g_utils::get_v_func<OrigFn>(this, 24)(this, col);
	}

	void draw_set_text_pos(int x, int y) {
		typedef void(__thiscall *OrigFn)(void*, int, int);
		g_utils::get_v_func<OrigFn>(this, 26)(this, x, y);
	}

	void draw_print_text(const wchar_t *text, int textLen, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) {
		typedef void(__thiscall *OrigFn)(void*, const wchar_t *, int, FontDrawType);
		g_utils::get_v_func<OrigFn>(this, 28)(this, text, textLen, drawType);
	}
	void draw_unicode_string(const wchar_t *pwString, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT)
	{
		typedef void(__thiscall *OrigFn)(void*, const wchar_t *, FontDrawType);
		g_utils::get_v_func<OrigFn>(this, 132)(this, pwString, drawType);
	}
	HFont create_font() {
		typedef HFont(__thiscall *OrigFn)(void*);
		return g_utils::get_v_func<OrigFn>(this, 71)(this);
	}

	bool set_font_glyph(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) {
		typedef bool(__thiscall *OrigFn)(void*, HFont, const char*, int, int, int, int, int, int, int);
		return g_utils::get_v_func<OrigFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}

	void get_text_size(HFont font, const wchar_t *text, int &wide, int &tall) {
		typedef void(__thiscall *OrigFn)(void*, HFont, const wchar_t *, int&, int&);
		g_utils::get_v_func<OrigFn>(this, 79)(this, font, text, wide, tall);
	}
};


class i_panel
{
public:
	const char *get_name(unsigned int vguiPanel)
	{
		typedef const char *(__thiscall* OrigFn)(void*, unsigned int);
		return g_utils::get_v_func<OrigFn>(this, 36)(this, vguiPanel);
	}
};

#define MULTIPLAYER_BACKUP 150

class bf_write;
class bf_read;

class i_input
{
public:
	virtual void  Init_All(void);
	virtual void  Shutdown_All(void);
	virtual int   GetButtonBits(int);
	virtual void  CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual void  ExtraMouseSample(float frametime, bool active);
	virtual bool  WriteUsercmdDeltaToBuffer(bf_write *buf, int from, int to, bool isnewcommand);
	virtual void  EncodeUserCmdToBuffer(bf_write& buf, int slot);
	virtual void  DecodeUserCmdFromBuffer(bf_read& buf, int slot);


	inline c_cmd* GetUserCmd(int nSlot, int sequence_number);
	inline CVerifiedUserCmd* GetVerifiedCmd(int nSlot, int sequence_number);

	bool                m_fTrackIRAvailable;            //0x04
	bool                m_fMouseInitialized;            //0x05
	bool                m_fMouseActive;                 //0x06
	bool                m_fJoystickAdvancedInit;        //0x07
	char                pad_0x08[0x2C];                 //0x08
	void*               m_pKeys;                        //0x34
	char                pad_0x38[0x64];                 //0x38
	bool                m_fCameraInterceptingMouse;     //0x9C
	bool                m_fCameraInThirdPerson;         //0x9D
	bool                m_fCameraMovingWithMouse;       //0x9E
	Vector              m_vecCameraOffset;              //0xA0
	bool                m_fCameraDistanceMove;          //0xAC
	int                 m_nCameraOldX;                  //0xB0
	int                 m_nCameraOldY;                  //0xB4
	int                 m_nCameraX;                     //0xB8
	int                 m_nCameraY;                     //0xBC
	bool                m_CameraIsOrthographic;         //0xC0
	QAngle              m_angPreviousViewAngles;        //0xC4
	QAngle              m_angPreviousViewAnglesTilt;    //0xD0
	float               m_flLastForwardMove;            //0xDC
	int                 m_nClearInputState;             //0xE0
	char                pad_0xE4[0x8];                  //0xE4
	c_cmd*           m_pCommands;                    //0xEC
	CVerifiedUserCmd*   m_pVerifiedCommands;            //0xF0
};

c_cmd* i_input::GetUserCmd(int nSlot, int sequence_number)
{
	return &m_pCommands[sequence_number % MULTIPLAYER_BACKUP];
}

CVerifiedUserCmd* i_input::GetVerifiedCmd(int nSlot, int sequence_number)
{
	return &m_pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
}