#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	const uint32_t PROOF_MASK = (uint32_t)eEntityProofs::BULLET | 
		(uint32_t)eEntityProofs::FIRE       | (uint32_t)eEntityProofs::COLLISION  | 
		(uint32_t)eEntityProofs::MELEE      | (uint32_t)eEntityProofs::GOD        | 
		(uint32_t)eEntityProofs::EXPLOSION  | (uint32_t)eEntityProofs::STEAM      | 
		(uint32_t)eEntityProofs::DROWN      | (uint32_t)eEntityProofs::WATER;


	void looped::self_godmode() {
		if (g_local_player != nullptr) {
			g_local_player->m_damage_bits = (g_local_player->m_damage_bits & ~PROOF_MASK) | g->self.proof_mask;
		}
	}
}