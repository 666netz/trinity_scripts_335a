// possible spells:
// 27651, 897

class spell_place_GOMove : public SpellScriptLoader
{
public:
    spell_place_GOMove() : SpellScriptLoader("spell_place_GOMove") { }

    class spell_place_GOMoveSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_place_GOMoveSpellScript);

        void HandleAfterCast()
        {
            if(GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return;
            Player* player = GetCaster()->ToPlayer();
            WorldLocation summonPos = *GetExplTargetDest();
            Map* map = player->GetMap();
            float x = summonPos.GetPositionX();
            float y = summonPos.GetPositionY();
            float z = summonPos.GetPositionZ();
            float o = player->GetOrientation();

            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(123);
            if (!objectInfo)
                return;
            if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
                return;

            GameObject* object = new GameObject;
            uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!object->Create(guidLow, objectInfo->entry, map, player->GetPhaseMaskForSpawn(), x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete object;
                return;
            }

            object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());

            if (!object->LoadGameObjectFromDB(guidLow, map))
            {
                delete object;
                return;
            }

            sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_place_GOMoveSpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_place_GOMoveSpellScript();
    }
};

void AddSC_GOMove_commandscript()
{
    new spell_place_GOMove();
}