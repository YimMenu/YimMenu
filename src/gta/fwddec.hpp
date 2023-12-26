#pragma once

namespace rage
{
	template<typename T>
	class atArray;

	class CEntity;

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
	class fwArchetype;

	class fiDevice;
	class fiPackfile;

	class rlSessionInfo;
	class rlSessionByGamerTaskResult;
}

class GtaThread;

class CGameScriptId;
class CGameScriptHandler;
class CGameScriptHandlerNetwork;
class CGameScriptHandlerMgr;

class CPhysical;

class CObject;
class CPickup;

class CPedFactory;
class CVehicleFactory;

class Network;
class CNetGamePlayer;
class CNetworkPlayerMgr;
class CPlayerInfo;
class CNetworkObjectMgr;
class CNetComplaintMgr;
