CREATE TABLE IF NOT EXISTS `guild_house_spawns` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `entry` int(11) NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `comment` varchar(500) DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

REPLACE INTO `guild_house_spawns` (`id`, `entry`, `posX`, `posY`, `posZ`, `orientation`, `comment`) VALUES
	(1, 26327, 16216.5, 16279.4, 20.9306, 0.552869, 'Paladin Trainer'),
	(2, 26324, 16221.3, 16275.7, 20.9285, 1.37363, 'Druid Trainer'),
	(3, 26325, 16218.6, 16277, 20.9872, 0.967188, 'Hunter Trainer'),
	(4, 26326, 16224.9, 16274.9, 20.9319, 1.58765, 'Mage Trainer'),
	(5, 26328, 16227.9, 16275.9, 20.9254, 1.9941, 'Priest Trainer'),
	(6, 26329, 16231.4, 16278.1, 20.9222, 2.20026, 'Rogue Trainer'),
	(7, 26330, 16235.5, 16280.8, 20.9257, 2.18652, 'Shaman Trainer'),
	(8, 26331, 16240.8, 16283.3, 20.9299, 1.86843, 'Warlock Trainer'),
	(9, 26332, 16246.6, 16284.5, 20.9301, 1.68975, 'Warrior Trainer'),
	(10, 500032, 16218.9, 16284.5, 13.1761, 6.18533, 'Innkeeper'),
	(11, 30605, 16228.0, 16280.5, 13.1761, 2.98877, 'Banker'),
	(12, 29195, 16252.3, 16284.9, 20.9324, 1.79537, 'Death Knight Trainer'),
	(13, 2836, 16220.5, 16302.3, 13.176, 6.14647, 'Blacksmithing Trainer'),
	(14, 8128, 16220.2, 16299.6, 13.178, 6.22894, 'Mining Trainer'),
	(15, 8736, 16219.8, 16296.9, 13.1746, 6.24465, 'Engineering Trainer'),
	(16, 18774, 16222.4, 16293, 13.1813, 1.51263, 'Jewelcrafting Trainer (Alliance)'),
	(17, 18751, 16222.4, 16293, 13.1813, 1.51263, 'Jewelcrafting Trainer (Horde)'),
	(18, 18773, 16227.5, 16292.3, 13.1839, 1.49691, 'Enchanting Trainer (Alliance)'),
	(19, 18753, 16227.5, 16292.3, 13.1839, 1.49691, 'Enchanting Trainer (Horde)'),
	(20, 30721, 16231.6, 16301, 13.1757, 3.07372, 'Inscription Trainer (Alliance)'),
	(21, 30722, 16231.6, 16301, 13.1757, 3.07372, 'Inscription Trainer (Horde)'),
	(22, 19187, 16231.2, 16295, 13.1761, 3.06574, 'Leatherworking Trainer'),
	(23, 19180, 16228.9, 16304.7, 13.1819, 4.64831, 'Skinning Trainer'),
	(24, 19052, 16218.1, 16281.8, 13.1756, 6.1975, 'Alchemy Trainer'),
	(25, 908, 16218.3, 16284.3, 13.1756, 6.1975, 'Herbalism Trainer'),
	(26, 2627, 16220.4, 16278.7, 13.1756, 1.46157, 'Tailoring Trainer'),
	(27, 19184, 16225, 16310.9, 29.262, 6.22119, 'First Aid Trainer'),
	(28, 2834, 16225.3, 16313.9, 29.262, 6.28231, 'Fishing Trainer'),
	(29, 19185, 16227, 16278, 13.1762, 1.4872, 'Cooking Trainer'),
	(30, 8719, 16242, 16291.6, 22.9311, 1.52061, 'Alliance Auctioneer'),
	(31, 9856, 16242, 16291.6, 22.9311, 1.52061, 'Horde Auctioneer'),
	(32, 184137, 16220.3, 16272, 12.9736, 4.45592, 'Mailbox (Object)'),
	(33, 1685, 16253.8, 16294.3, 13.1758, 6.11938, 'Forge (Object)'),
	(34, 4087, 16254.4, 16298.7, 13.1758, 3.36027, 'Anvil (Object)'),
	(35, 500000, 16229.5, 16280.6, 13.175, 3.15258, 'Portal: Stormwind (Object)'),
	(36, 500001, 16230.3, 16286.5, 13.1759, 3.176, 'Portal: Darnassus (Object)'),
	(37, 500002, 16218.8, 16281.9, 13.1759, 0.0469642, 'Portal: Exodar (Object)'),
	(38, 500003, 16219.4, 16287.5, 13.1754, 6.07019, 'Portal: Ironforge (Object)'),
	(39, 500004, 16229.5, 16280.6, 13.175, 3.15258, 'Portal: Orgrimmar (Object)'),
	(40, 500005, 16219.4, 16287.5, 13.1754, 6.07019, 'Portal: Silvermoon (Object)'),
	(41, 500006, 16218.8, 16281.9, 13.1759, 0.0469642, 'Portal: Thunder Bluff (Object)'),
	(42, 500007, 16230.3, 16286.5, 13.1759, 3.176, 'Portal: Undercity (Object)'),
    (43, 500008, 16222.2, 16293.5, 13.1788, 1.37242, 'Portal: Shattrath (Object)'),
	(44, 500009, 16227.9, 16292.9, 13.1808, 1.84839, 'Portal: Dalaran (Object)'),
	(45, 500010, 16230.1, 16301.6, 13.1771, 4.51481, 'Portal: Oscuro (Object)'),
	(46, 500011, 16221.2, 16301.8, 13.1777, 4.75147, 'Portal: Isle of Quel\'Danas (Object)'),
	
	(47, 187293, 16230.5, 16283.5, 13.9061, 3, 'Guild Vault (Object)'),
	(48, 28692, 16236.2, 16315.7, 20.8454, 4.64365, 'Trade Supplies'),
	(49, 28776, 16223.7, 16297.9, 20.8454, 6.17044, 'Tabard Vendor'),
	(50, 4255, 16230.2, 16316.1, 20.8455, 4.64365, 'Food & Drink Vendor'),
    (51, 6491, 16319.937, 16242.404, 24.4747, 2.206830, 'Spirit Healer'),
    (52, 191028, 16255.5, 16304.9, 20.9785, 2.97516, 'Barber Chair (Object)'),
    (53, 29636, 16233.2, 16315.9, 20.8454, 4.64365, 'Reagent Vendor'),
    (54, 29493, 16229.1, 16286.4, 13.176, 3.03831, 'Ammo & Repair Vendor'),
    (55, 28690, 16226.97, 16267.9, 13.15, 4.6533, 'Stable Master'),
	(56, 9858, 16238.2, 16291.8, 22.9306, 1.55386, 'Neutral Auctioneer'),
	(57, 2622, 16242.8, 16302.1, 13.176, 4.55570, 'Poisons Vendor'),
	(58, 500502, 16309.2, 16270.6, 18.9253, 4.66944, 'Restos Olvidados(Object)'),
	(59, 500503, 16296.9, 16245.1, 24.769, 0.658499, 'Restos Olvidados(Object)'),
	(60, 500504, 16318.1, 16235.9, 24.7143, 3.46967, 'Restos Olvidados(Object)');