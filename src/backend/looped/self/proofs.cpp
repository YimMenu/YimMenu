#include "backend/looped/looped.hpp"
#include "backend/bool_command.hpp"

namespace big
{
	static uint32_t last_bits = 0;
	static float last_water_collistion_strength = 0;

	void looped::self_proofs()
	{
		if (g_local_player == nullptr)
		{
			return;
		}

		uint32_t bits;

		if (g.self.god_mode)
		{
			bits |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g.self.proof_bullet)
		{
			bits |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g.self.proof_fire)
		{
			bits |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g.self.proof_collision)
		{
			bits |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g.self.proof_melee)
		{
			bits |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g.self.proof_explosion)
		{
			bits |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g.self.proof_steam)
		{
			bits |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g.self.proof_drown)
		{
			bits |= static_cast<int>(eEntityProofs::DROWN);
		}
		if (g.self.proof_water)
		{
			bits |= static_cast<int>(eEntityProofs::WATER);
		}

		uint32_t changed_bits = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = g_local_player->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_damage_bits = unchanged_bits | bits;
			last_bits = bits;
		}
	}

	bool_command g_proof_god("god", "Godmode", "Makes you invulnerable", g.self.god_mode);
	bool_command g_proof_bullet("bullet_proof", "Bulletproof", "Makes you bulletproof", g.self.proof_bullet);
	bool_command g_proof_fire("fire_proof", "Fireproof", "Makes you fireproof", g.self.proof_fire);
	bool_command g_proof_proof_collision("collision_proof", "Collisionproof", "Makes you collisionproof", g.self.proof_collision);
	bool_command g_proof_melee("melee_proof", "Meleeproof", "Makes you meleeproof", g.self.proof_melee);
	bool_command g_proof_explosion("explosion_proof", "Explosionproof", "Makes you explosionproof", g.self.proof_explosion);
	bool_command g_proof_steam("steam_proof", "Steamproof", "Makes you steamproof", g.self.proof_steam);
	bool_command g_proof_drown("drown_proof", "Drownproof", "Makes you drownproof", g.self.proof_drown);
	bool_command g_proof_water("water_proof", "Waterproof", "Makes you waterproof", g.self.proof_water);
}