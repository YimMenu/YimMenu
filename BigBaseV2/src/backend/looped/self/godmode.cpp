#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static uint32_t lastProofBits = 0;

	void looped::self_godmode() {
		if (g_local_player != nullptr) {
			uint32_t proofBits = g->self.proof_mask;
			uint32_t changedProofBits = proofBits ^ lastProofBits;
			uint32_t changedOrEnabledProofBits = proofBits | changedProofBits;

			if (changedOrEnabledProofBits) {
				uint32_t unchangedBits = g_local_player->m_damage_bits & ~changedOrEnabledProofBits;
				g_local_player->m_damage_bits = unchangedBits | proofBits;
				lastProofBits = proofBits;
			}
		}
	}
}