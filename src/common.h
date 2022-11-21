#pragma once
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>

#define FMT_HEADER_ONLY
#include <dpp/fmt/format.h>

#include "core/commands/commands.h"

inline const std::string BOT_TOKEN = "your bot token here";
inline const std::string BOT_VERSION = "1.0";

using command_function = std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>;
using json = nlohmann::json;

using namespace std::chrono_literals;

struct command_definition {
	std::string description;
	command_function function;
	std::vector<dpp::command_option> parameters = {};
};
