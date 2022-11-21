#pragma once
#include "../../common.h"

namespace commands {
	namespace info {
		void ping(dpp::cluster& bot, const dpp::slashcommand_t& event);
		void uptime(dpp::cluster& bot, const dpp::slashcommand_t& event);
	}
}