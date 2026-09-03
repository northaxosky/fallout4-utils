#include "Host/Client.h"

#include <DearModdingUI/Client.h>

namespace Host
{
	namespace
	{
		inline constexpr auto kClientId = "dearmodding.utils";
		inline constexpr auto kClientDisplayName = "Utils";
		inline constexpr auto kClientIcon = "wrench";

		// the host owns the ImGui context; forwarding mode calls into it through the ABI
		dmui::Client g_client{
			kClientId,
			kClientDisplayName,
			dmui::Version{ PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR },
			dmui::kForwardingClient,
			kClientIcon
		};

		void DrawPlayerPage()
		{
			ImGui::Text("Hello from Fallout4Utils");
			ImGui::TextDisabled("Cheats land here.");
		}
	}

	void Connect() noexcept
	{
		if (!g_client.Connect())
		{
			if (!g_client.HostPresent())
			{
				REX::WARN("No DearModdingUI host is loaded; no menu this session");
			}
			else
			{
				REX::ERROR("DearModdingUI registration failed, result {}", g_client.LastResult());
			}

			return;
		}

		if (!ImGui::IsForwardVersionCompatible())
		{
			REX::ERROR("The DearModdingUI host draws a different ImGui than this plugin forwards to");
			return;
		}

		if (!g_client.AddPage("player", "Player", "Gameplay", &DrawPlayerPage, "God mode, level, and player stats.", 10))
		{
			REX::ERROR("Page registration failed, result {}", g_client.LastResult());
			return;
		}

		REX::INFO("Registered as '{}' with the DearModdingUI host", kClientId);
	}
}
