#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "hooking.hpp"

namespace
{
	// from https://stackoverflow.com/a/48818578

	static const char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

	static const unsigned char decoding_table[256] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	char* base64_encode(const unsigned char* data, size_t input_length, size_t& output_length)
	{
		const int mod_table[] = {0, 2, 1};

		output_length = 4 * ((input_length + 2) / 3);

		char* encoded_data = (char*)malloc(output_length);

		if (encoded_data == nullptr)
			return nullptr;

		for (int i = 0, j = 0; i < input_length;)
		{
			uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
			uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
			uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

			uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

			encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
			encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
		}

		for (int i = 0; i < mod_table[input_length % 3]; i++)
			encoded_data[output_length - 1 - i] = '=';

		return encoded_data;
	};

	unsigned char* base64_decode(const char* data, size_t input_length, size_t& output_length)
	{
		if (input_length % 4 != 0)
			return nullptr;

		output_length = input_length / 4 * 3;

		if (data[input_length - 1] == '=')
			(output_length)--;
		if (data[input_length - 2] == '=')
			(output_length)--;

		unsigned char* decoded_data = (unsigned char*)malloc(output_length);

		if (decoded_data == nullptr)
			return nullptr;

		for (int i = 0, j = 0; i < input_length;)
		{
			uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
			uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

			uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

			if (j < output_length)
				decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
			if (j < output_length)
				decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
			if (j < output_length)
				decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
		}

		return decoded_data;
	};
}

namespace big
{
	class override_game_hashes : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			if (g.spoofing.last_game_version != std::stoi(g_pointers->m_gta.m_game_version))
			{
				g.spoofing.last_game_version = std::stoi(g_pointers->m_gta.m_game_version);
				size_t out_size;
				char* encoded = base64_encode((const unsigned char*)*g_pointers->m_gta.m_game_checksum_data, 0xF4, out_size);
				g.spoofing.game_checksum_data_b64 = std::string(encoded, out_size);
				free(encoded);
				g.spoofing.game_dlc_checksum = g_hooking->get_original<hooks::get_dlc_hash>()(*g_pointers->m_gta.m_dlc_manager, 0);
				LOG(INFO) << g.spoofing.game_checksum_data_b64.size();
			}
			else
			{
				size_t output_len;
				void* decoded = base64_decode(g.spoofing.game_checksum_data_b64.data(),
				    g.spoofing.game_checksum_data_b64.size(),
				    output_len);
				LOG(INFO) << output_len;
				memcpy(*g_pointers->m_gta.m_game_checksum_data, decoded, 0xF4);
				free(decoded);
			}
		}

		virtual void on_tick() override
		{
		}

		virtual void on_disable() override
		{
			// TODO? 
		}
	};

	override_game_hashes g_override_game_hashes("overridegamehashes", "TODO", "TODO", g.spoofing.override_game_hashes);
}
