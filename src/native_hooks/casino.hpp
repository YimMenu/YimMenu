namespace big
{
	namespace casino
	{
		void NETWORK_CASINO_CAN_BET(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(TRUE);
		}
	}
}