--Horda Portales
--Portal a Ogrimmar /Ventormenta

DELETE FROM `gameobject` WHERE (`id` = 500004) AND (`guid` IN (2135669));
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135669, 500004, 1, 0, 0, 1, 1, 16229.5, 16280.6, 13.175, 3.15258, 0, 0, -0.999985, 0.00549187, 300, 0, 1, '', NULL);

-- Undercity / darnassus

DELETE FROM `gameobject` WHERE (`id` = 500007) AND (`guid` IN (2135668));
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135668, 500007, 1, 0, 0, 1, 12, 16230.3, 16286.5, 13.1759, 3.176, 0, 0, -0.999852, 0.0172032, 300, 0, 1, '', NULL);

-- Cima de Trueno / Exodar

DELETE FROM `gameobject` WHERE (`id` = 500006) AND (`guid` IN (2135670));
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135670, 500006, 1, 0, 0, 1, 1, 16218.8, 16281.9, 13.1759, 0.0469642, 0, 0, -0.0234802, -0.999724, 300, 0, 1, '', NULL);

-- silvermoon / Ironforge

DELETE FROM `gameobject` WHERE (`id` = 500005) AND (`guid` IN (2135671));
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135671, 500005, 11, 0, 0, 1, 1, 16219.4, 16287.5, 13.1754, 6.07019, 0, 0, -0.106298, 0.994334, 300, 0, 1, '', NULL);

-- Shatra

DELETE FROM `gameobject` WHERE (`id` = 500008);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135725, 500008, 1, 0, 0, 1, 1, 16222.2, 16293.5, 13.1788, 1.37242, 0, 0, -0.63361, -0.773653, 300, 0, 1, '', NULL);

-- dalaran 

DELETE FROM `gameobject` WHERE (`id` = 500009);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135727, 500009, 1, 0, 0, 1, 1, 16227.9, 16292.9, 13.1808, 1.84839, 0, 0, -0.798135, -0.602479, 300, 0, 1, '', NULL);

-- Portal Oscuro

DELETE FROM `gameobject` WHERE (`id` = 500010);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(2135751, 500010, 1, 0, 0, 1, 1, 16230.1, 16301.6, 13.1771, 4.51481, 0, 0, -0.773402, 0.633917, 300, 0, 1, '', NULL);

-- Portal a Isle of Quel\'Danas

DELETE FROM `gameobject_template` WHERE (`entry` = 187056);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(187056, 22, 7628, 'Shattrath Portal to Isle of Quel\'Danas', '', '', '', 1, 44876, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);

