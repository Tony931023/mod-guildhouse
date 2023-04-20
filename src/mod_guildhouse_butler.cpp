#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Creature.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "DataMap.h"
#include "GameObject.h"
#include "Transport.h"
#include "CreatureAI.h"

int cost, GuildHouseInnKeeper, GuildHouseBank, GuildHouseMailBox, GuildHouseAuctioneer, GuildHouseTrainer, GuildHouseVendor, GuildHouseObject, GuildHousePortal, GuildHouseSpirit, GuildHouseProf, GuildHouseBuyRank;

uint32 pGuildId;

struct Portal {
    uint32 id;
    std::string name;
}
portalsO[4] = {
    { 500005, "Ciudad de Lunargenta" },
    { 500006, "Cima de Trueno" },
    { 500007, "Entrañas" },
    { 500008, "Orgrimmar" }
};

struct PortalA {
    uint32 id;
    std::string name;
}
portalsA[4] = {
    { 500001, "Darnassus" },
    { 500002, "El Exodar" },
    { 500003, "Forjaz" },
    { 500004, "Ventormenta" }
};

struct PortalN {
    uint32 id;
    std::string name;
}
portalsN[2] = {
    { 500009, "Shattrath" },
    { 500010, "Dalaran" }
};

struct MenusS {
    uint32 id;
    std::string name;
}
MenuS[6] = {
    { 500101, "Tabernero" },
    { 500102, "Buzón" },
    { 500103, "Maestro de Establos" },
    { 500104, "Banco" },
    { 500105, "Subastador" },
    { 500106, "Cementerio" }
};

struct Cementerio {
    uint32 id;
    std::string name;
}
CementerioM[2] = {
    { 500501, "Ángel de la Resurrección" },
    { 500502, "Restos Olvidados" }
};

struct MenusC {
    uint32 id;
    std::string name;
}
MenuC[5] = {
    { 500201, "Entrenadores de Clase" },
    { 500202, "Vendedores" },
    { 500203, "Portales" },
    { 500204, "Profesiones Principales" },
    { 500205, "Profesiones Secundarias" }
};

uint32 buy;
class GuildHouseSpawner : public CreatureScript
{

public:
    GuildHouseSpawner() : CreatureScript("GuildHouseSpawner") {}

    struct GuildHouseSpawnerAI : public ScriptedAI
    {
        GuildHouseSpawnerAI(Creature *creature) : ScriptedAI(creature) {}

        void UpdateAI(uint32 /* diff */) override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
    };

    CreatureAI *
    GetAI(Creature *creature) const override
    {
        return new GuildHouseSpawnerAI(creature);
    }

    bool OnGossipHello(Player *player, Creature *creature) override
    {

        if (player->GetGuild())
        {
            Guild *guild = sGuildMgr->GetGuildById(player->GetGuildId());
            Guild::Member const *memberMe = guild->GetMember(player->GetGUID());
            if (!memberMe->IsRankNotLower(GuildHouseBuyRank))
            {
                ChatHandler(player->GetSession()).PSendSysMessage("No estás autorizado para hacer compras de la Casa de la Hermandad.");
                return false;
            }
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("¡No perteneces a una hermandad!");
            return false;
        }
        pGuildId = player->GetGuildId();
        ClearGossipMenuFor(player);
        bool portalFound[6] = { false, false, false, false, false, false };
        

        if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500101 AND `buy` <= 500106 AND `guild` = {}", pGuildId))
        {
            do {
                Field* t_fields = t_query->Fetch();
                uint32 buy = t_fields[0].Get<uint32>();

                if (buy >= 500101 && buy <= 500106) {
                    for (int i = 0; i < 6; i++) {
                        if (buy == MenuS[i].id) {
                            portalFound[i] = true;
                            break;
                        }
                    }
                }
            } while (t_query->NextRow());
        }

        for (int i = 0; i < 6; i++) {
            if (!portalFound[i]) {
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, MenuS[i].name, GOSSIP_SENDER_MAIN, MenuS[i].id, "Invocar: " + MenuS[i].name, 1000000, false);
            }
        }
        
        // Portales TEAM_ALLIANCE 
        if (player->GetTeamId() == TEAM_ALLIANCE)
        {
            // Verificar si el portal 500203 existe
            if (CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = 500203 AND `guild` = {}", pGuildId)) {}
            else {

                // Comprobar si se han comprado todos los portales
                bool allBought = true;

                // Comprobar si se han comprado todos los portales de portalsA
                for (const auto& portal : portalsA) {
                    if (!CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = {} AND `guild` = {}", portal.id, pGuildId))
                    {
                        allBought = false;
                        break;
                    }
                }

                // Comprobar si se han comprado todos los portales de portalsN
                for (const auto& portal : portalsN) {
                    if (!CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = {} AND `guild` = {}", portal.id, pGuildId))
                    {
                        allBought = false;
                        break;
                    }
                }

                // Mostrar el menú de portales si no se han comprado todos
                if (!allBought) {
                    AddGossipItemFor(player, GOSSIP_ICON_TALK, "Portales", GOSSIP_SENDER_MAIN, 4);
                }
                else {
                    CharacterDatabase.Execute("INSERT INTO `guild_house_buy` VALUES ({},500203)", pGuildId);
                }
            }
        }
        else {
            // Verificar si el portal 500203 existe
            if (CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = 500203 AND `guild` = {}", pGuildId)) {}
            else {

                // Comprobar si se han comprado todos los portales
                bool allBought = true;

                // Comprobar si se han comprado todos los portales de portalsO
                for (const auto& portal : portalsO) {
                    if (!CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = {} AND `guild` = {}", portal.id, pGuildId))
                    {
                        allBought = false;
                        break;
                    }
                }

                // Comprobar si se han comprado todos los portales de portalsN
                for (const auto& portal : portalsN) {
                    if (!CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = {} AND `guild` = {}", portal.id, pGuildId))
                    {
                        allBought = false;
                        break;
                    }
                }

                // Mostrar el menú de portales si no se han comprado todos
                if (!allBought) {
                    AddGossipItemFor(player, GOSSIP_ICON_TALK, "Portales", GOSSIP_SENDER_MAIN, 4);
                }
                else {
                    CharacterDatabase.Execute("INSERT INTO `guild_house_buy` VALUES ({},500203)", pGuildId);
                }
            }

        }

        // Cementerio
        // Verificar si el portal 500500 existe
        if (CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = 500500 AND `guild` = {}", pGuildId)) {}
        else {

            // Comprobar si se han comprado todos los Cementerios
            bool allBought = true;

            // Comprobar si se han comprado todos los cementerio de portalsA
            for (const auto& cementerio : CementerioM) {
                if (!CharacterDatabase.Query("SELECT 1 FROM `guild_house_buy` WHERE `buy` = {} AND `guild` = {}", cementerio.id, pGuildId))
                {
                    allBought = false;
                    break;
                }
            }           

            // Mostrar el menú de Cementerio si no se han comprado todos
            if (!allBought) {
                AddGossipItemFor(player, GOSSIP_ICON_TALK, "Cementerio", GOSSIP_SENDER_MAIN, 500500);
            }
            else {
                CharacterDatabase.Execute("INSERT INTO `guild_house_buy` VALUES ({},500500)", pGuildId);
            }
        }

        
        /*AddGossipItemFor(player, GOSSIP_ICON_TALK, "Tabernero", GOSSIP_SENDER_MAIN, 500032, "¿Invocar un Tabernero?", GuildHouseInnKeeper, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Buzón", GOSSIP_SENDER_MAIN, 184137, "¿Invocar Buzón?", GuildHouseMailBox, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Maestro de Establos", GOSSIP_SENDER_MAIN, 28690, "¿Invocar Maestro de Establos?", GuildHouseVendor, false);        
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Banco", GOSSIP_SENDER_MAIN, 30605, "¿Invocar Banco?", GuildHouseBank, false);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Subastador", GOSSIP_SENDER_MAIN, 6, "¿Invocar Subastador?", GuildHouseAuctioneer, false);
        AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Subastador Neutral", GOSSIP_SENDER_MAIN, 9858, "¿Invocar Subastador Neutral?", GuildHouseAuctioneer, false);
        
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Cementerio", GOSSIP_SENDER_MAIN, 6491, "¿Invocar Cementerio?", GuildHouseSpirit, false);*/
        /*
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Entrenadores de Clase", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Vendedores", GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "Portales", GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Entrenadores de Profesiones Principales", GOSSIP_SENDER_MAIN, 7);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Entrenadores de Profesiones Secundarias", GOSSIP_SENDER_MAIN, 8);*/

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *m_creature, uint32, uint32 action) override
    {
        pGuildId = player->GetGuildId();
        
        switch (action)
        {
        case 2: // Spawn Class Trainer
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Caballero de la Muerte", GOSSIP_SENDER_MAIN, 29195, "¿Invocar un entredador de Caballero de la Muerte?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Druida", GOSSIP_SENDER_MAIN, 26324, "¿Invocar un entredador de Druida?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cazador", GOSSIP_SENDER_MAIN, 26325, "¿Invocar un entredador de Cazador?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Mago", GOSSIP_SENDER_MAIN, 26326, "¿Invocar un entredador de Mago?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Paladín", GOSSIP_SENDER_MAIN, 26327, "¿Invocar un entredador de Paladín?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Sacerdote", GOSSIP_SENDER_MAIN, 26328, "¿Invocar un entredador de Sacerdote?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Pícaro", GOSSIP_SENDER_MAIN, 26329, "¿Invocar un entredador de Pícaro?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Chamán", GOSSIP_SENDER_MAIN, 26330, "¿Invocar un entredador de Chamán?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Brujo", GOSSIP_SENDER_MAIN, 26331, "¿Invocar un entredador de Brujo?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Guerrero", GOSSIP_SENDER_MAIN, 26332, "¿Invocar un entredador de Guerrero?", GuildHouseTrainer, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 3: // Vendors
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Suministros Comerciales", GOSSIP_SENDER_MAIN, 28692, "¿Invocar un Vendedor de Suministros Comerciales?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Tabardos", GOSSIP_SENDER_MAIN, 28776, "¿Invocar un Vendedor de Tabardos?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Comidas y Bebidas", GOSSIP_SENDER_MAIN, 4255, "¿Invocar un Vendedor de Comida y Bebida?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Componentes", GOSSIP_SENDER_MAIN, 29636, "¿Invocar un vendedor de Componentes?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Vendedor de Munición y Reparador", GOSSIP_SENDER_MAIN, 29493, "¿Invocar un Vendedor de Munición y Reparador?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Venenos", GOSSIP_SENDER_MAIN, 2622, "¿Invocar un Vendedor de venenos?", GuildHouseVendor, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 4: // Objects & Portals
        {

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Forja", GOSSIP_SENDER_MAIN, 1685, "¿Agregar una Forja?", GuildHouseObject, false);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Yunque", GOSSIP_SENDER_MAIN, 4087, "¿Agregar un Yunque?", GuildHouseObject, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Cámara de la hermandad", GOSSIP_SENDER_MAIN, 187293, "¿Agregar una Cámara de la hermandad?", GuildHouseObject, false);
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Silla de Peluquería", GOSSIP_SENDER_MAIN, 191028, "¿Agregar una Silla de peluquería?", GuildHouseObject, false);

            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                // ALLIANCE players get these options                

                bool portalFound[4] = { false, false, false, false };

                if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500001 AND `buy` <= 500004 AND `guild` = {}", pGuildId))
                {
                    do {
                        Field* t_fields = t_query->Fetch();
                        uint32 buy = t_fields[0].Get<uint32>();

                        if (buy >= 500001 && buy <= 500004) {
                            for (int i = 0; i < 4; i++) {
                                if (buy == portalsA[i].id) {
                                    portalFound[i] = true;
                                    break;
                                }
                            }
                        }
                    } while (t_query->NextRow());
                }

                for (int i = 0; i < 4; i++) {
                    if (!portalFound[i]) {
                        std::string message = "¿Agregar un Portal: " + portalsA[i].name + "?";
                        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: " + portalsA[i].name, GOSSIP_SENDER_MAIN, portalsA[i].id, message.c_str(), GuildHousePortal, false);
                    }
                }
            }
            else
            {
                bool portalFound[4] = { false, false, false, false };

                if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500005 AND `buy` <= 500008 AND `guild` = {}", pGuildId))
                {
                    do {
                        Field* t_fields = t_query->Fetch();
                        uint32 buy = t_fields[0].Get<uint32>();

                        if (buy >= 500005 && buy <= 500008) {
                            for (int i = 0; i < 3; i++) {
                                if (buy == portalsO[i].id) {
                                    portalFound[i] = true;
                                    break;
                                }
                            }
                        }
                    } while (t_query->NextRow());
                }

                for (int i = 0; i < 4; i++) {
                    if (!portalFound[i]) {
                        std::string message = "¿Agregar un Portal: " + portalsO[i].name + "?";
                        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: " + portalsO[i].name, GOSSIP_SENDER_MAIN, portalsO[i].id, message.c_str(), GuildHousePortal, false);
                    }
                }

            }
            // These two portals work for either Team

            bool portalFoundN[2] = { false, false };

            if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500009 AND `buy` <= 500010 AND `guild` = {}", pGuildId))
            {
                do {
                    Field* t_fields = t_query->Fetch();
                    uint32 buy = t_fields[0].Get<uint32>();

                    if (buy >= 500009 && buy <= 500010) {
                        for (int i = 0; i < 2; i++) {
                            if (buy == portalsN[i].id) {
                                portalFoundN[i] = true;
                                break;
                            }
                        }
                    }
                } while (t_query->NextRow());
            }
            for (int i = 0; i < 2; i++) {
                if (!portalFoundN[i]) {
                    std::string message = "¿Agregar un Portal: " + portalsN[i].name + "?";
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Portal: " + portalsN[i].name, GOSSIP_SENDER_MAIN, portalsN[i].id, message.c_str(), GuildHousePortal, false);
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;

        }
        case 6: // Auctioneer
        {
            uint32 auctioneer = 0;
            auctioneer = player->GetTeamId() == TEAM_ALLIANCE ? 8719 : 9856;
            SpawnNPC(auctioneer, player);
            break;
        }
        case 9858: // Neutral Auctioneer
            cost = GuildHouseAuctioneer;
            SpawnNPC(action, player);
            break;
        case 7: // Spawn Profession Trainers
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alquimia", GOSSIP_SENDER_MAIN, 19052, "¿Invocar  un entrenador de Alquimia?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Herrería", GOSSIP_SENDER_MAIN, 2836, "¿Invocar  un entrenador de Herrería?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Ingeniería", GOSSIP_SENDER_MAIN, 8736, "¿Invocar un entrenador de Ingeniería?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Sastrería", GOSSIP_SENDER_MAIN, 2627, "¿Invocar un entrenador de Sastrería?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Peletería", GOSSIP_SENDER_MAIN, 19187, "¿Invocar un entrenador de Peletería?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Desuello", GOSSIP_SENDER_MAIN, 19180, "¿Invocar un entrenador de Desuello?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Minería", GOSSIP_SENDER_MAIN, 8128, "¿Invocar un entrenador de Minería?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "herbolaría", GOSSIP_SENDER_MAIN, 908, "¿Invocar un entrenador de herbolaría?", GuildHouseProf, false);

            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                // ALLIANCE players get these options
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Encantamiento", GOSSIP_SENDER_MAIN, 18773, "¿Invocar un entrenador de Encantamiento?", GuildHouseProf, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Joyería", GOSSIP_SENDER_MAIN, 18774, "¿Invocar un entrenador de Joyería?", GuildHouseProf, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscripción", GOSSIP_SENDER_MAIN, 30721, "¿Invocar un entrenador de Inscripción?", GuildHouseProf, false);
            }
            else
            {
                

                // HORDE players get these options
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Encantamiento", GOSSIP_SENDER_MAIN, 18753, "¿Invocar un entrenador de Encantamiento?", GuildHouseProf, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Joyería", GOSSIP_SENDER_MAIN, 18751, "¿Invocar un entrenador de Joyería?", GuildHouseProf, false);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscripción", GOSSIP_SENDER_MAIN, 30722, "¿Invocar un entrenador de Inscripción?", GuildHouseProf, false);
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 8: // Secondary Profession Trainers
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Primeros Auxilios", GOSSIP_SENDER_MAIN, 19184, "¿Invocar un entrenador de Primeros Auxilios?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Pesca", GOSSIP_SENDER_MAIN, 2834, "¿Invocar un entrenador de Pesca?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Cocina", GOSSIP_SENDER_MAIN, 19185, "¿Invocar un entrenador de Cocina?", GuildHouseProf, false);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;
        case 9: // Go back!
            OnGossipHello(player, m_creature);
            break;
        case 10: // PVP toggle
            break;
        case 30605: // Banker
            cost = GuildHouseBank;
            SpawnNPC(action, player);
            break;
        case 500032: // Innkeeper
            cost = GuildHouseInnKeeper;
            SpawnNPC(action, player);
            break;
        case 26327: // Paladin
        case 26324: // Druid
        case 26325: // Hunter
        case 26326: // Mage
        case 26328: // Priest
        case 26329: // Rogue
        case 26330: // Shaman
        case 26331: // Warlock
        case 26332: // Warrior
        case 29195: // Death Knight
            cost = GuildHouseTrainer;
            SpawnNPC(action, player);
            break;
        case 2836:  // Blacksmithing
        case 8128:  // Mining
        case 8736:  // Engineering
        case 18774: // Jewelcrafting (Alliance)
        case 18751: // Jewelcrafting (Horde)
        case 18773: // Enchanting (Alliance)
        case 18753: // Enchanting (Horde)
        case 30721: // Inscription (Alliance)
        case 30722: // Inscription (Horde)
        case 19187: // Leatherworking
        case 19180: // Skinning
        case 19052: // Alchemy
        case 908:   // Herbalism
        case 2627:  // Tailoring
        case 19185: // Cooking
        case 2834:  // Fishing
        case 19184: // First Aid
            cost = GuildHouseProf;
            SpawnNPC(action, player);
            break;
        case 28692: // Trade Supplies
        case 28776: // Tabard Vendor
        case 4255:  // Food & Drink Vendor
        case 29636: // Reagent Vendor
        case 29493: // Ammo & Repair Vendor
        case 28690: // Stable Master
        case 2622:  // Poisons Vendor
            cost = GuildHouseVendor;
            SpawnNPC(action, player);
            break;
            //
            // Objects
            //
        case 184137: // Mailbox
            cost = GuildHouseMailBox;
            SpawnObject(action, player);
            break;
        case 6491: // Spirit Healer
            cost = GuildHouseSpirit;
            SpawnNPC(action, player);
            break;
        case 1685:   // Forge
        case 4087:   // Anvil
        case 187293: // Guild Vault
        case 191028: // Barber Chair
            cost = GuildHouseObject;
            SpawnObject(action, player);
            break;
        case 500500: // Cementerio
        {
            ClearGossipMenuFor(player);
            bool portalFound[2] = { false, false };

            if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy`, `guild` FROM `guild_house_buy` WHERE `buy` >= 500501 AND `buy` <= 500002 AND `guild` = {}", pGuildId))
                {
                do {
                    Field* t_fields = t_query->Fetch();
                    uint32 buy = t_fields[0].Get<uint32>();

                    if (buy >= 500501 && buy <= 500502) {
                        for (int i = 0; i < 2; i++) {
                            if (buy == CementerioM[i].id) {
                                portalFound[i] = true;
                                break;
                                }
                            }
                        }
                    } while (t_query->NextRow());
                }

                for (int i = 0; i < 2; i++) {
                    if (!portalFound[i]) {
                        std::string message = "¿Agregar: " + CementerioM[i].name + "?";
                        AddGossipItemFor(player, GOSSIP_ICON_TAXI, CementerioM[i].name, GOSSIP_SENDER_MAIN, CementerioM[i].id, message.c_str(), 1000000, false);
                    }
                }            

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "¡Regresar!", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature->GetGUID());
            break;

        }
        case 500501: // Ángel de la Resurrección
            cost = 1000000;
            SpawnNPC(action, player);
            break;
        case 500502: // Restos Olvidados
            cost = 1000000;
            SpawnObject(500502, player);
            SpawnObject(500503, player);
            SpawnObject(500504, player);
            break;
        case 500001: // Darnassus Portal
        case 500002: // Exodar Portal
        case 500003: // Ironforge Portal
        case 500004: // Ventormenta Portal
        case 500005: // Silvermoon Portal
        case 500006: // Thunder Bluff Portal   
        case 500007: // Undercity Portal
        case 500008: // Orgrimmar Portal
        case 500009: // Shattrath Portal
        case 500010: // Dalaran Portal
            cost = GuildHousePortal;
            buyPortal(action, player);
            break;
        }
		
		return true;
    }

    void buyPortal(uint32 entry, Player* player) {
        uint32 guildId = player->GetGuildId();
        

        // Verificar que el jugador tenga suficiente dinero
        if (player->GetMoney() < cost) {
            ChatHandler(player->GetSession()).PSendSysMessage("No tienes suficiente dinero para comprar este portal");
            CloseGossipMenuFor(player);
            return;
        }

        // Verificar que el portal no haya sido comprado previamente
        if (QueryResult t_query = CharacterDatabase.Query("SELECT `buy` FROM `guild_house_buy` WHERE `guild` = {} AND `buy` = {}", guildId, entry)) {
            ChatHandler(player->GetSession()).PSendSysMessage("Ya has comprado este portal");
            CloseGossipMenuFor(player);
            return;
        }

        // Comprar el portal
        CharacterDatabase.Execute("INSERT INTO `guild_house_buy` VALUES ({},{})", guildId, entry);
        player->ModifyMoney(-cost);
        ChatHandler(player->GetSession()).PSendSysMessage("¡Portal adquirido para la Hermandad!");
        CloseGossipMenuFor(player);
    }
            
        
    

    uint32 GetGuildPhase(Player *player)
    {
        return player->GetGuildId() + 10;
    }

    void SpawnNPC(uint32 entry, Player *player)
    {
        if (player->FindNearestCreature(entry, VISIBILITY_RANGE, true))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("¡Ya tienes esta criatura!");
            CloseGossipMenuFor(player);
            return;
        }

        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.Query("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = {}", entry);

        if (!result)
            return;

        do
        {
            Field *fields = result->Fetch();
            posX = fields[0].Get<float>();
            posY = fields[1].Get<float>();
            posZ = fields[2].Get<float>();
            ori = fields[3].Get<float>();

        } while (result->NextRow());

        Creature *creature = new Creature();

        if (!creature->Create(player->GetMap()->GenerateLowGuid<HighGuid::Unit>(), player->GetMap(), GetGuildPhase(player), entry, 0, posX, posY, posZ, ori))
        {
            delete creature;
            return;
        }
        creature->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), GetGuildPhase(player));
        uint32 db_guid = creature->GetSpawnId();

        creature->CleanupsBeforeDelete();
        delete creature;
        creature = new Creature();
        if (!creature->LoadCreatureFromDB(db_guid, player->GetMap()))
        {
            delete creature;
            return;
        }

        sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));
        player->ModifyMoney(-cost);
        CloseGossipMenuFor(player);
    }

    void SpawnObject(uint32 entry, Player *player)
    {
        uint32 guildId = player->GetGuildId();
        if (player->FindNearestGameObject(entry, VISIBLE_RANGE))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("¡Ya tienes este objeto!");
            CloseGossipMenuFor(player);
            return;
        }

        float posX;
        float posY;
        float posZ;
        float ori;

        QueryResult result = WorldDatabase.Query("SELECT `posX`, `posY`, `posZ`, `orientation` FROM `guild_house_spawns` WHERE `entry` = {}", entry);

        if (!result)
            return;

        do
        {
            Field *fields = result->Fetch();
            posX = fields[0].Get<float>();
            posY = fields[1].Get<float>();
            posZ = fields[2].Get<float>();
            ori = fields[3].Get<float>();

        } while (result->NextRow());

        uint32 objectId = entry;
        if (!objectId)
            return;

        const GameObjectTemplate *objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

        if (!objectInfo)
            return;

        if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            return;

        GameObject *object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        ObjectGuid::LowType guidLow = player->GetMap()->GenerateLowGuid<HighGuid::GameObject>();

        if (!object->Create(guidLow, objectInfo->entry, player->GetMap(), GetGuildPhase(player), posX, posY, posZ, ori, G3D::Quat(), 0, GO_STATE_READY))
        {
            delete object;
            return;
        }

        // fill the gameobject data and save to the db
        object->SaveToDB(player->GetMapId(), (1 << player->GetMap()->GetSpawnMode()), GetGuildPhase(player));
        guidLow = object->GetSpawnId();
        // delete the old object and do a clean load from DB with a fresh new GameObject instance.
        // this is required to avoid weird behavior and memory leaks
        delete object;

        object = sObjectMgr->IsGameObjectStaticTransport(objectInfo->entry) ? new StaticTransport() : new GameObject();
        // this will generate a new guid if the object is in an instance
        if (!object->LoadGameObjectFromDB(guidLow, player->GetMap(), true))
        {
            delete object;
            return;
        }

        // TODO: is it really necessary to add both the real and DB table guid here ?
        sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGameObjectData(guidLow));
        player->ModifyMoney(-cost);
        CharacterDatabase.Execute("INSERT INTO `guild_house_buy` VALUES ({},{})", guildId, entry);
        CloseGossipMenuFor(player);
    }
};

class GuildHouseButlerConf : public WorldScript
{
public:
    GuildHouseButlerConf() : WorldScript("GuildHouseButlerConf") {}

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        GuildHouseInnKeeper = sConfigMgr->GetOption<int32>("GuildHouseInnKeeper", 1000000);
        GuildHouseBank = sConfigMgr->GetOption<int32>("GuildHouseBank", 1000000);
        GuildHouseMailBox = sConfigMgr->GetOption<int32>("GuildHouseMailbox", 500000);
        GuildHouseAuctioneer = sConfigMgr->GetOption<int32>("GuildHouseAuctioneer", 500000);
        GuildHouseTrainer = sConfigMgr->GetOption<int32>("GuildHouseTrainerCost", 1000000);
        GuildHouseVendor = sConfigMgr->GetOption<int32>("GuildHouseVendor", 500000);
        GuildHouseObject = sConfigMgr->GetOption<int32>("GuildHouseObject", 500000);
        GuildHousePortal = sConfigMgr->GetOption<int32>("GuildHousePortal", 500000);
        GuildHouseProf = sConfigMgr->GetOption<int32>("GuildHouseProf", 500000);
        GuildHouseSpirit = sConfigMgr->GetOption<int32>("GuildHouseSpirit", 100000);
        GuildHouseBuyRank = sConfigMgr->GetOption<int32>("GuildHouseBuyRank", 4);
    }
};

void AddGuildHouseButlerScripts()
{
    new GuildHouseSpawner();
    new GuildHouseButlerConf();
}
