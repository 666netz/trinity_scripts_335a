/*
--Player Assistant Companion
-- By DPCoder[Lordcraft]
--Make sure that you have downloaded and run the other sql files that work with this, download link below.If you use my Playerr Tools, Profession / Riding and Fun Npc then you
--DO NOT need to change anything.Should you wish to use your own then you will need to change the numbers.

--Zipoa Tiger
SET @ENTRY : = 36910;
SET @SOURCETYPE : = 0;
SET @TeleNpc : = 9991773;  --Change this number to your own Teleporter Id
SET @PlayerTools : = 9991770; --Change this number to your own Tools Npc Id
SET @ProfRide : = 9991772; --Change this number to your own profession / riding trainer
SET @FunNpc : = 9991771; --Change this number to your own morpher / aura npc

--[DO NOT CHANGE ANYTHING BELOW THIS LINE] --

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName = "SmartAI" WHERE entry = @ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0, 0, 62, 0, 100, 1, 56004, 1, 0, 0, 12, @TeleNpc,3, 18000, 0, 0, 0, 7, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, "Teleporter"),
(@ENTRY,@SOURCETYPE,1, 0, 62, 0, 100, 1, 56004, 2, 0, 0, 12, @PlayerTools,3, 18000, 0, 0, 0, 7, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, "Player Tools"),
(@ENTRY,@SOURCETYPE,2, 0, 62, 0, 100, 0, 56004, 3, 0, 0, 12, @ProfRide,3, 18000, 0, 0, 0, 7, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, "Profession / Riding"),
(@ENTRY,@SOURCETYPE,3, 0, 62, 0, 100, 0, 56004, 4, 0, 0, 12, @FunNpc,3, 18000, 0, 0, 0, 7, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, "Fun Npc");
*/