#include "commands.h"

void commands::info::ping(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    /* Get websocket ping of first shard */
    float ws_ping = bot.get_shard(0)->websocket_ping;
    event.reply(
        dpp::message().add_embed(
            dpp::embed().
            set_color(dpp::colors::raspberry).
            set_title(":ping_pong: Pong!").
            set_description(
                fmt::format(":robot: Ping: {0:.02f} ms", (bot.rest_ping + ws_ping) * 1000)
            )
        )
    );
}

void commands::info::uptime(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    /* Get websocket ping of first shard */
    float ws_ping = bot.get_shard(0)->websocket_ping;
    event.reply(
        dpp::message().add_embed(
            dpp::embed().
            set_color(dpp::colors::rust).
            set_title("Hello humans :wave:!").
            set_author("Made by Swisser", "https://github.com/ressiws", "https://avatars.githubusercontent.com/u/75338261?v=4").
            set_description("I am " + bot.me.username + ". A open source bot made in C++!\nHere you will find some informations about me!").
            add_field(
                fmt::format(":ping_pong: Ping: {0:.02f} ms", (bot.rest_ping + ws_ping) * 1000),
                fmt::format(":heartbeat: Uptime: {}s", bot.uptime().to_string())
            ).
            add_field(
                fmt::format(":family_man_girl_boy: Users: {}", std::to_string(dpp::get_user_count())),
                fmt::format(":robot: Bot version: {}", BOT_VERSION)
            ).
            set_footer(dpp::embed_footer().set_text(fmt::format("Executed by: {}", event.command.usr.username)))
        )
    );
}