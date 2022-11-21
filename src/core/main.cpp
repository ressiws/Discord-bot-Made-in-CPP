#include "../common.h"

std::map<std::string, command_definition> command_list = {
    { "ping", { "A ping command", commands::info::ping }},
    { "info", { "A uptime command", commands::info::uptime }},
};

int main() {
    /* Setup the bot */
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    /* Default basic logger */
    bot.on_log(dpp::utility::cout_logger());

    /* In the on_ready we translate the commands map into a vector of dpp::slashcommand.
	 * The vector of dpp::slashcommand is then passed to the command registration
	 * method, dpp::cluster::global_bulk_command_create().
	 */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        std::cout << "Logged in as " << bot.me.username << "#" << bot.me.discriminator << std::endl;

        if (dpp::run_once<struct bulk_register>()) {
            std::vector<dpp::slashcommand> slash_commands;
            for (auto& def : command_list) {
                dpp::slashcommand c;
                c.set_name(def.first).
                    set_description(def.second.description).
                    set_application_id(bot.me.id);
                c.options = def.second.parameters;
                slash_commands.push_back(c);
            }
            bot.global_bulk_command_create(slash_commands);
        }
        });

    /* Handle slash commands */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        dpp::command_interaction cmd_data = event.command.get_command_interaction();
        /* Check for commands that exist in our command map */
        auto command_iter = command_list.find(cmd_data.name);
        if (command_iter != command_list.end()) {
           /* If we find a matching command, call its handler function,
		    * passing in this event's information and the bot cluster
			* as references.
		    */
            command_iter->second.function(bot, event);
        }
        });

    try {
        bot.start(false);
    }
    catch (std::exception error) {
        bot.log(dpp::ll_error, fmt::format("Error! {}", error.what()));
    }

    /* Reconnection delay to prevent hammering discord */
    std::this_thread::sleep_for(10s);
}