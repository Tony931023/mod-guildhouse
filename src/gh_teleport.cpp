#include "Config.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"


struct Portal {
    uint32 id;
    std::string name;
};

Portal portals[10] = {
    { 500001, "Darnassus" },
    { 500002, "El Exodar" },
    { 500003, "Forjaz" },
    { 500004, "Ventormenta" },
    { 500005, "Ciudad de Lunargenta" },
    { 500006, "Cima de Trueno" },
    { 500007, "Entrañas" },
    { 500008, "Orgrimmar" },
    { 500009, "Shattrath" },
    { 500010, "Dalaran" }
};

class GH_Teleport : public CreatureScript
{
public:
    GH_Teleport() : CreatureScript("GH_Teleport") { }

    static uint32 GetGuildPhase(Player* player)
    {
        return player->GetGuildId() + 10;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        uint32 pGuildId = player->GetGuildId();
        uint32 buy;
        
        std::vector<bool> portalFound(10, false);

        if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500001 AND `buy` <= 500010 AND `guild` = {}", pGuildId))
        {
            do {
                Field* t_fields = t_query->Fetch();
                uint32 buy = t_fields[0].Get<uint32>();

                if (buy >= 500001 && buy <= 500010) {
                    for (int i = 0; i < 10; i++) {
                        if (buy == portals[i].id) {
                            portalFound[i] = true;
                            break;
                        }
                    }
                }
            } while (t_query->NextRow());

            for (int i = 0; i < 10; i++) {
                if (portalFound[i]) {                    
                    AddGossipItemFor(player, 0, portals[i].name, GOSSIP_SENDER_MAIN, portals[i].id);
                }
            }
        }

        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        switch (action)
        {
            // T. Dalaran
			case 500010: 
				player->TeleportTo(571, 5807.75f, 588.346985f, 660.939026f, 1.663f);                
			break;
            // T. Ventormenta
			case 500004: 
				player->TeleportTo(0, -9003.459961f, 870.031006f, 29.6206f, 2.28f);
			break;
            // T. Orgrimmar
			case 500008: 
				player->TeleportTo(1, 1469.849976f, -4221.520020f, 58.993900f, 5.98f);
			break;
            // T. Cima de Trueno
            case 500006:
				player->TeleportTo(1, -964.430176f, 282.988495f, 111.316101f, 5.903981f);
			break;
            // T. Ciudad de Lunargenta
            case 500005:
				player->TeleportTo(530, 9998.040039f, -7106.560059f, 47.788300f, 5.689770f);
			break;
            // T. Entrañas
            case 500007:
				player->TeleportTo(0, 1773.469971f, 61.120998f, -46.320702f, 0.54f);
			break;
            // T. Ciudad de Shattrath
            case 500009:
				player->TeleportTo(530, -1904.760010f, 5443.430176f, -12.4272f, 5.96f);
			break;
            // T. Forjaz
            case 500003:
				player->TeleportTo(0, -4613.620117f, -915.380005f, 501.062012f, 3.88f);
			break;
            // T. Darnassus
            case 500001:
				player->TeleportTo(1, 9660.809570f, 2513.639893f, 1331.657349f, 3.06f);
			break;
            // T. El Exodar
            case 500002:
				player->TeleportTo(530, -4029.929932f, -11572.200195f, -138.296005f, 2.43f);
			break;        
		}
        return true;
	}	
};



void AddGH_TeleportScripts()
{
    new GH_Teleport();
}
