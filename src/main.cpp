#include "pch.h"

#include "Host/Client.h"

namespace
{
	void F4SEAPI HandleF4SEMessage(F4SE::MessagingInterface::Message* a_message) noexcept
	{
		if (!a_message || a_message->type != F4SE::MessagingInterface::kPostPostLoad)
		{
			return;
		}

		Host::Connect();
	}

	bool InitPlugin(const F4SE::LoadInterface* a_f4se)
	{
		F4SE::Init(a_f4se);
		REX::INFO("Fallout4Utils {} loaded", PLUGIN_VERSION);

		auto listenerRegistered = false;
		try
		{
			const auto messaging = F4SE::GetMessagingInterface();
			listenerRegistered = messaging && messaging->RegisterListener(&HandleF4SEMessage);
		}
		catch (...)
		{}

		if (!listenerRegistered)
		{
			REX::ERROR("F4SE messaging listener registration failed; no menu this session");
			return false;
		}

		return true;
	}
}

F4SE_PLUGIN_QUERY(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	if (const auto data = F4SE::PluginVersionData::GetSingleton())
	{
		a_info->infoVersion = F4SE::PluginInfo::kVersion;
		a_info->name = data->GetPluginName().data();
		a_info->version = data->GetPluginVersion().pack();
	}

	return !a_f4se->IsEditor();
}

F4SE_PLUGIN_LOAD(const F4SE::LoadInterface* a_f4se)
{
	return InitPlugin(a_f4se);
}
