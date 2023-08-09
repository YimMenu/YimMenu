#pragma once
#include "pointers.hpp"

#include <array>

namespace rage
{
	struct fiFindData
	{
		char fileName[256];
		uint64_t fileSize;
		FILETIME lastWriteTime;
		DWORD fileAttributes;
	};

	struct ResourceFlags
	{
		// TODO: figure out which is physical and which is virtual
		uint32_t flag1;
		uint32_t flag2;
	};

	// since Payne, RAGE devices are thread-safe (might not apply to V?)
	// in V, RAGE devices use UTF-8
	class fiDevice
	{
	public:
		static inline fiDevice* GetDevice(const char* path, bool allowRoot)
		{
			return big::g_pointers->m_gta.m_fidevice_get_device(path, allowRoot);
		}

		static bool MountGlobal(const char* mountPoint, fiDevice* device, bool allowRoot);
		static void Unmount(const char* rootPath);
		static void Unmount(fiDevice const& device);

	public:
		virtual void Destroy()                                                                  = 0;
		virtual uint64_t Open(const char* fileName, bool readOnly)                              = 0;
		virtual uint64_t OpenBulk(const char* fileName, uint64_t* ptr)                          = 0;
		virtual uint64_t OpenBulkWrap(const char* fileName, uint64_t* ptr, void*)               = 0;
		virtual uint64_t CreateLocal(const char* fileName)                                      = 0;
		virtual uint64_t Create(const char* fileName)                                           = 0;
		virtual uint32_t Read(uint64_t handle, void* buffer, uint32_t toRead)                   = 0;
		virtual uint32_t ReadBulk(uint64_t handle, uint64_t ptr, void* buffer, uint32_t toRead) = 0;
		virtual uint32_t WriteBulk(uint64_t, int, int, int, int)                                = 0;
		virtual uint32_t Write(uint64_t, void*, int)                                            = 0;
		virtual uint32_t Seek(uint64_t handle, int32_t distance, uint32_t method)               = 0;
		virtual uint64_t SeekLong(uint64_t handle, int64_t distance, uint32_t method)           = 0;
		virtual int32_t Close(uint64_t handle)                                                  = 0;
		virtual int32_t CloseBulk(uint64_t handle)                                              = 0;
		virtual int GetFileLength(uint64_t handle)                                              = 0;
		virtual uint64_t GetFileLengthUInt64(uint64_t handle)                                   = 0;
		virtual int m_40(int)                                                                   = 0;
		virtual bool RemoveFile(const char* file)                                               = 0;
		virtual int RenameFile(const char* from, const char* to)                                = 0;
		virtual int CreateDirectory(const char* dir)                                            = 0;
		virtual int RemoveDirectory(const char* dir)                                            = 0;
		virtual void m_xx()                                                                     = 0;
		virtual uint64_t GetFileLengthLong(const char* fileName)                                = 0;
		virtual uint64_t GetFileTime(const char* file)                                          = 0;
		virtual bool SetFileTime(const char* file, FILETIME fileTime)                           = 0;
		virtual uint64_t FindFirst(const char* path, fiFindData* findData)                      = 0;
		virtual bool FindNext(uint64_t handle, fiFindData* findData)                            = 0;
		virtual int FindClose(uint64_t handle)                                                  = 0;
		virtual rage::fiDevice* GetUnkDevice()                                                  = 0;
		virtual void* m_xy(void*, int, void*)                                                   = 0;
		virtual bool Truncate(uint64_t handle)                                                  = 0;
		virtual uint32_t GetFileAttributes(const char* path)                                    = 0;
		virtual bool m_xz()                                                                     = 0;
		virtual bool SetFileAttributes(const char* file, uint32_t FileAttributes)               = 0;
		virtual int m_yx()                                                                      = 0;
		virtual bool ReadFull(uint64_t handle, void* buffer, uint32_t length)                   = 0;
		virtual bool WriteFull(uint64_t handle, void* buffer, uint32_t length)                  = 0;
		virtual int32_t GetResourceVersion(const char* fileName, ResourceFlags* flags)          = 0;
		virtual int32_t m_yy()                                                                  = 0;
		virtual int32_t m_yz(void*)                                                             = 0;
		virtual int32_t m_zx(void*)                                                             = 0;
		virtual bool IsCollection()                                                             = 0;
		virtual bool m_addedIn1290()                                                            = 0;
		virtual fiDevice* GetCollection()                                                       = 0;
		virtual bool m_ax()                                                                     = 0;
		virtual int32_t GetCollectionId()                                                       = 0;
		virtual const char* GetName()                                                           = 0;
	};

	class fiDeviceImplemented : public fiDevice
	{
	protected:
		fiDeviceImplemented();

	public:
		virtual void Destroy();
		virtual uint64_t Open(const char* fileName, bool readOnly);
		virtual uint64_t OpenBulk(const char* fileName, uint64_t* ptr);
		virtual uint64_t OpenBulkWrap(const char* fileName, uint64_t* ptr, void* a3);
		virtual uint64_t CreateLocal(const char* fileName);
		virtual uint64_t Create(const char* fileName);
		virtual uint32_t Read(uint64_t handle, void* buffer, uint32_t toRead);
		virtual uint32_t ReadBulk(uint64_t handle, uint64_t ptr, void* buffer, uint32_t toRead);
		virtual uint32_t WriteBulk(uint64_t, int, int, int, int);
		virtual uint32_t Write(uint64_t, void*, int);
		virtual uint32_t Seek(uint64_t handle, int32_t distance, uint32_t method);
		virtual uint64_t SeekLong(uint64_t handle, int64_t distance, uint32_t method);
		virtual int32_t Close(uint64_t handle);
		virtual int32_t CloseBulk(uint64_t handle);
		virtual int GetFileLength(uint64_t handle);
		virtual uint64_t GetFileLengthUInt64(uint64_t handle);
		virtual int m_40(int);
		virtual bool RemoveFile(const char* file);
		virtual int RenameFile(const char* from, const char* to);
		virtual int CreateDirectory(const char* dir);
		virtual int RemoveDirectory(const char* dir);
		virtual void m_xx();
		virtual uint64_t GetFileLengthLong(const char* fileName);
		virtual uint64_t GetFileTime(const char* file);
		virtual bool SetFileTime(const char* file, FILETIME fileTime);
		virtual uint64_t FindFirst(const char* path, fiFindData* findData);
		virtual bool FindNext(uint64_t handle, fiFindData* findData);
		virtual int FindClose(uint64_t handle);
		virtual rage::fiDevice* GetUnkDevice();
		virtual void* m_xy(void* a1, int a2, void* a3);
		virtual bool Truncate(uint64_t handle);
		virtual uint32_t GetFileAttributes(const char* path);
		virtual bool m_xz();
		virtual bool SetFileAttributes(const char* file, uint32_t FileAttributes);
		virtual int m_yx();
		// read even if read() returns less than length
		virtual bool ReadFull(uint64_t handle, void* buffer, uint32_t length);
		virtual bool WriteFull(uint64_t handle, void* buffer, uint32_t length);
		virtual int32_t GetResourceVersion(const char* fileName, ResourceFlags* version);
		virtual int32_t m_yy();
		virtual int32_t m_yz(void*);
		virtual int32_t m_zx(void*); // return 0x40000000
		virtual bool IsCollection();
		virtual bool m_addedIn1290();
		virtual fiDevice* GetCollection(); // return this
		virtual bool m_ax();
		virtual int32_t GetCollectionId();
		virtual const char* GetName();
	};

	class fiPackfile : public fiDeviceImplemented
	{
	private:
		char m_pad[368 + (0x650 - 0x590)]{};

	public:
		fiPackfile();
		~fiPackfile();

		// any RAGE path can be used; including root-relative paths
		bool OpenPackfile(const char* archive, bool bTrue, int type, intptr_t veryFalse);

		// mounts the device in the device stack
		bool Mount(const char* mountPoint);

		// closes the package file
		void ClosePackfile();
	};
}
