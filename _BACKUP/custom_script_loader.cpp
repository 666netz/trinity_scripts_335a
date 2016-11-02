/*
* Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// This is where scripts' loading functions should be declared:
void AddSC_ITEM_SummonHelperNPC();
void AddSC_NPC_DEV_MultiGiver();
void AddSC_NPC_DEVELOPMENT();
void AddSC_NPC_Equiper();
void AddSC_NPC_GiverDB_Bags();
void AddSC_NPC_GiverDB_Equipment();
void AddSC_NPC_GiverDB_Glyph();
void AddSC_NPC_GiverDB_Goods();
void AddSC_NPC_GiverDB_Hunterpets();
void AddSC_NPC_GiverDB_Mounts();
void AddSC_NPC_GiverDB_Pets();
void AddSC_NPC_Helper();
void AddSC_NPC_Helperstone();
void AddSC_NPC_Summoner();
void AddSC_NPC_Teleport();
void AddSC_NPC_Teleport_Database();
void AddSC_NPC_Upgrader(); 

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()

void AddCustomScripts()
{
	AddSC_ITEM_SummonHelperNPC();
	AddSC_NPC_DEV_MultiGiver();
	AddSC_NPC_DEVELOPMENT();
	AddSC_NPC_Equiper();
	AddSC_NPC_GiverDB_Bags();
	AddSC_NPC_GiverDB_Equipment();
	AddSC_NPC_GiverDB_Glyph();
	AddSC_NPC_GiverDB_Goods();
	AddSC_NPC_GiverDB_Hunterpets();
	AddSC_NPC_GiverDB_Mounts();
	AddSC_NPC_GiverDB_Pets();
	AddSC_NPC_Helper();
	AddSC_NPC_Helperstone();
	AddSC_NPC_Summoner();
	AddSC_NPC_Teleport();
	AddSC_NPC_Teleport_Database();
	AddSC_NPC_Upgrader();
}
