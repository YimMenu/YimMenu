#pragma once
#include "file_manager.hpp"
#include "thread_pool.hpp"

using namespace std::chrono_literals;

// {DCB7EF33-CD8A-4231-8051-66E3F683180B}
static const GUID g_yim_device = {0xdcb7ef33, 0xcd8a, 0x4231, {0x80, 0x51, 0x66, 0xe3, 0xf6, 0x83, 0x18, 0xb}};

class IDirectSoundCaptureBuffer
{
	inline int GetActualReadPos()
	{
		return read_position + (audio_page * 32000);
	}

	virtual void QueryInterface(){};

	virtual int AddRef()
	{
		return 0;
	};

	virtual int Release()
	{
		return 0;
	}

	virtual HRESULT GetCaps(void* caps)
	{
		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT GetCurrentPosition(int* capture, int* read)
	{
		if (capture)
			*capture = 0;

		if (read)
			*read = read_position;

		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT GetFormat(void* out, int length, int* out_length)
	{
		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT GetStatus(int* status)
	{
		*status = 1;       // DSCBSTATUS_CAPTURING
		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT Initialize(void*, void*)
	{
		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT Lock(DWORD dwOffset, DWORD dwBytes, char** ppvAudioPtr1, LPDWORD pdwAudioBytes1, char** ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
	{
		if (dwOffset > read_position && audio_page != 0)
		{
			dwOffset -= 32000;// fix page offset if we have to read back
		}

		dwOffset += (audio_page * 32000);// add our page offset to get the actual position

		// fix artifacts after audio ends
		if (dwBytes > 1280)
			dwOffset = 0;

		if (dwOffset + dwBytes <= audio_size)
		{
			*ppvAudioPtr1   = &audio_buffer[dwOffset];
			*pdwAudioBytes1 = dwBytes;
			*ppvAudioPtr2   = NULL;
			*pdwAudioBytes2 = 0;
		}
		else
		{
			*ppvAudioPtr1   = &audio_buffer[dwOffset];
			*pdwAudioBytes1 = audio_size - dwOffset;
			*ppvAudioPtr2   = &audio_buffer[0];
			*pdwAudioBytes2 = dwBytes - *pdwAudioBytes1;
		}

		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT Start(int flags)
	{
		if (big::g_file_manager.get_project_file("./audio.wav").exists())
		{
			std::ifstream wave_stream(big::g_file_manager.get_project_file("./audio.wav").get_path(), std::ios::in | std::ios::binary);

			// https://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
			int header_size = 0;
			int data_size   = 0;
			wave_stream.seekg(4, std::ios_base::cur);          // RIFF
			wave_stream.seekg(4, std::ios_base::cur);          // chunk size
			wave_stream.seekg(4, std::ios_base::cur);          // Wave ID
			wave_stream.seekg(4, std::ios_base::cur);          // ckID "fmt "
			wave_stream.read((char*)&header_size, 4);          // cksize "fmt "
			wave_stream.seekg(header_size, std::ios_base::cur);// format
			wave_stream.seekg(4, std::ios_base::cur);          // ckID "data"
			wave_stream.read((char*)&data_size, 4);            // cksize "data"

			audio_buffer = new char[data_size];
			memset(audio_buffer, 0, data_size);
			audio_size = data_size;
			wave_stream.read(audio_buffer, audio_size);
			wave_stream.close();
		}
		else
		{
			audio_buffer = new char[0xFFFF];
			audio_size   = 0xFFFF;
		}

		running = true;
		big::g_thread_pool->push([this] {
			last_read = std::chrono::high_resolution_clock::now();

			while (!big::g_running)
				std::this_thread::yield();

			while (big::g_running && running)
			{
				std::this_thread::yield();

				// the buffer can only support up to 32000 bytes of data at once, so we have to page it instead
				if (std::chrono::high_resolution_clock::now() - last_read >= 1ms)
				{
					last_read = std::chrono::high_resolution_clock::now();
					read_position += ((2 * 16000) / 1000);// F*M*Nc/1000

					// reset page idx after audio playback completes
					if (GetActualReadPos() > audio_size)
					{
						read_position = 0;
						audio_page    = 0;
					}

					// use next page if we go beyond 32000
					if (read_position > 32000)
					{
						read_position = read_position % 32000;
						audio_page++;
					}
				}
			}
		});

		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT Stop()
	{
		running = false;
		delete[] audio_buffer;

		return (HRESULT)0L;// DS_OK
	}

	virtual HRESULT Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
	{
		return (HRESULT)0L;// DS_OK
	}

	char* audio_buffer                                       = nullptr;
	int audio_size                                           = 0;
	int audio_page                                           = 0;
	int read_position                                        = 0;
	bool running                                             = false;
	std::chrono::high_resolution_clock::time_point last_read = std::chrono::high_resolution_clock::time_point();
};
inline IDirectSoundCaptureBuffer g_direct_sound_capture_buffer{};

class IDirectSoundCapture
{
	virtual void QueryInterface(){};

	virtual int AddRef()
	{
		return 0;
	};

	virtual int Release()
	{
		return 0;
	}

	virtual HRESULT CreateSoundBuffer(void* desc, IDirectSoundCaptureBuffer** buffer, void* unknown)
	{
		*buffer = &g_direct_sound_capture_buffer;
		return (HRESULT)0L;// DS_OK
	}

	// we shouldn't need the rest
};
inline IDirectSoundCapture g_direct_sound_capture{};