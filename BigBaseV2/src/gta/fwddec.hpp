#pragma once

namespace rage
{
	template <typename T>
	class atArray;

	class datBitBuffer;
	class sysMemAllocator;

	class scriptIdBase;
	class scriptId;
	class scriptHandler;
	class scriptHandlerNetComponent;
	class scriptHandlerObject;
	class scriptHandlerMgr;

	class scrProgram;
	class scrProgramTable;

	class scrThreadContext;
	class scrThread;
	class tlsContext;

	class netLoggingInterface;
	class netLogStub;

	class netPlayer;
	class netPlayerMgr;

	class netGameEvent;
	class netEventMgr;

	class netSyncTree;
	
	class netObject;
	class netObjectMgrBase;

	class scrNativeCallContext;
	class scrNativeRegistration;
	class scrNativeRegistrationTable;

	class fwRefAwareBase;
	class fwExtensibleBase;
	class fwEntity;
	class fwArchetype;

	class CVehicle;
	class CPed;
}

class GtaThread;

class CGameScriptId;
class CGameScriptHandler;
class CGameScriptHandlerNetwork;
class CGameScriptHandlerMgr;

class CEntity;
class CDynamicEntity;
class CPhysical;

class CObject;
class CPickup;

class CPedFactory;
class CVehicleFactory;

class CNetGamePlayer;
class CNetworkPlayerMgr;
class CPlayerInfo;
class CNetworkObjectMgr;
