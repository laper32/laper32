#if defined _tools_included
#endinput
#endif
#define _tools_included

/**
 * @brief Gets or sets the velocity of a entity.
 *
 * @param entity            The entity index.
 * @param vVelocity         The velocity output, or velocity to set on entity.
 * @param bApply            True to get entity velocity, false to set it.
 * @param bStack            If modifying velocity, then true will stack new velocity onto the entity.
 *                          current velocity, false will reset it.
 */
inline void ToolsSetVelocity(int entity, float vVelocity[3], bool bApply = true, bool bStack = true)
{
    // If retrieve if true, then get entity velocity
    if (!bApply)
    {
        // Gets entity velocity
        ToolsGetVelocity(entity, vVelocity);
        
        // Stop here
        return;
    }
    
    // If stack is true, then add entity velocity
    if (bStack)
    {
        // Gets entity velocity
        static float vSpeed[3];
        ToolsGetVelocity(entity, vSpeed);
        
        // Add to the current
        AddVectors(vSpeed, vVelocity, vVelocity);
    }
    
    // Apply velocity on entity
    TeleportEntity(entity, NULL_VECTOR, NULL_VECTOR, vVelocity);
}

/**
 * @brief Gets the velocity of a entity.
 *
 * @param entity            The entity index.
 * @param vVelocity         The velocity output.
 */
inline void ToolsGetVelocity(int entity, float vVelocity[3])
{
    // Gets origin of the entity
    GetEntPropVector(entity, Prop_Data, "m_vecVelocity", vVelocity);
}

/**
 * @brief Gets the abs origin of a entity.
 *
 * @param entity            The entity index.
 * @param vPosition         The origin output.
 */
inline void ToolsGetAbsOrigin(int entity, float vPosition[3])
{
    // Gets origin of the entity
    GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vPosition);
}

/**
 * @brief Gets the abs angle of a entity.
 *
 * @param entity            The entity index.
 * @param vAngle            The angle output.
 */
inline void ToolsGetAbsAngles(int entity, float vAngle[3])
{
    // Gets angles of the entity
    GetEntPropVector(entity, Prop_Data, "m_angAbsRotation", vAngle);
}

/**
 * @brief Gets the max weapons of a entity.
 *
 * @param entity            The entity index.
 * @return                  The max weapon amount.
 */
inline int ToolsGetMyWeapons(int entity)
{
    // Gets weapons of the entity
    return GetEntPropArraySize(entity, Prop_Data, "m_hMyWeapons");
}

/**
 * @brief Gets weapon on the position of a entity.
 *
 * @param entity            The entity index.
 * @param iPosition         The weapon position.
 * @return                  The weapon index.
 */
inline int ToolsGetWeapon(int entity, int iPosition)
{
    // Gets weapon of the entity
    return GetEntPropEnt(entity, Prop_Data, "m_hMyWeapons", iPosition);
}

/**
 * @brief Gets the health of a entity.
 *
 * @param entity            The entity index.
 * @param bMax              True to get maximum value, false to get health.  
 * @return                  The health value.
 */
inline int ToolsGetHealth(int entity, bool bMax = false)
{
    // Gets health of the entity
    return GetEntProp(entity, Prop_Data, bMax ? "m_iMaxHealth" : "m_iHealth");
}

/**
 * @brief Sets the health of a entity.
 *
 * @param entity            The entity index.
 * @param iValue            The health value.
 * @param bSet              True to set maximum value, false to modify health.  
 */
inline void ToolsSetHealth(int entity, int iValue, bool bSet = false)
{
    // Sets health of the entity
    SetEntProp(entity, Prop_Send, "m_iHealth", iValue);
    
    // If set is true, then set max health
    if (bSet) 
    {
        // Sets max health of the entity
        SetEntProp(entity, Prop_Data, "m_iMaxHealth", iValue);
    }
}

/**
 * @brief Gets the speed of a entity.
 *
 * @param entity            The entity index.
 * @return                  The LMV value.
 */
inline float ToolsGetLMV(int entity)
{
    // Gets lagged movement value of the entity
    return GetEntPropFloat(entity, Prop_Data, "m_flLaggedMovementValue");
}

/**
 * @brief Sets the speed of a entity.
 *
 * @param entity            The entity index.
 * @param flValue           The LMV value.
 */
inline void ToolsSetLMV(int entity, float flValue)
{
    // Sets lagged movement value of the entity
    SetEntPropFloat(entity, Prop_Data, "m_flLaggedMovementValue", flValue);
}

/**
 * @brief Gets the armor of a entity.
 *
 * @param entity            The entity index.
 * @return                  The armor value.
 */
inline int ToolsGetArmor(int entity)
{
    // Gets armor of the entity
    return GetEntProp(entity, Prop_Send, "m_ArmorValue");
}

/**
 * @brief Sets the armor of a entity.
 *
 * @param entity            The entity index.
 * @param iValue            The armor value.
 */
inline void ToolsSetArmor(int entity, int iValue)
{
    // Sets armor of the entity
    SetEntProp(entity, Prop_Send, "m_ArmorValue", iValue);
}

/**
 * @brief Gets the team of an entity.
 * 
 * @param entity            The entity index.
 * @return                  The team index.
 */
inline int ToolsGetTeam(int entity)
{
    // Gets team on the entity
    return GetEntProp(entity, Prop_Data, "m_iTeamNum");
}

/**
 * @brief Sets the team of a entity.
 *
 * @param entity            The entity index.
 * @param iValue            The team index.
 */
inline void ToolsSetTeam(int entity, int iValue)
{
    // Validate team
    if (ToolsGetTeam(entity) <= TEAM_SPECTATOR) /// Fix, thanks to inklesspen!
    {
        // Sets team of the entity
        ChangeClientTeam(entity, iValue);
    }
    else
    {
        // Switch team of the entity
        CS_SwitchTeam(entity, iValue); 
    }
}

/**
 * @brief Gets nightvision values on a entity.
 *
 * @param entity            The entity index.
 * @param ownership         If true, function will return the value of the entity ownership of nightvision.
 *                          If false, function will return the value of the entity on/off state of the nightvision.
 * @return                  True if aspect of nightvision is enabled on the entity, false if not.
 */
inline bool ToolsGetNightVision(int entity, bool bOwnership = false)
{
    // If ownership is true, then gets the ownership of nightvision on entity
    return view_as<bool>(GetEntProp(entity, Prop_Send, bOwnership ? "m_bHasNightVision" : "m_bNightVisionOn"));
}

/**
 * @brief Controls nightvision values on a entity.
 *
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of nightvision. (see ownership parameter)
 * @param bOwnership        If true, enable will toggle the entity ownership of nightvision.
 *                          If false, enable will toggle the entity on/off state of the nightvision.
 */
inline void ToolsSetNightVision(int entity, bool bEnable, bool bOwnership = false)
{
    // If ownership is true, then toggle the ownership of nightvision on entity
    SetEntProp(entity, Prop_Send, bOwnership ? "m_bHasNightVision" : "m_bNightVisionOn", bEnable);
}

/**
 * @brief Gets defuser value on a entity.
 *
 * @param entity            The entity index.
 * @return                  The aspect of the entity defuser.
 */
inline bool ToolsGetDefuser(int entity)
{
    // Gets defuser on the entity
    return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasDefuser"));
}

/**
 * @brief Controls defuser value on a entity.
 *
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of defuser.
 */
inline void ToolsSetDefuser(int entity, bool bEnable)
{
    // Sets defuser on the entity
    SetEntProp(entity, Prop_Send, "m_bHasDefuser", bEnable);
}

/**
 * @brief Gets helmet value on a entity.
 *
 * @param entity            The entity index.
 * @return                  The aspect of the entity helmet.
 */
inline bool ToolsGetHelmet(int entity)
{
    // Gets helmet on the entity
    return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasHelmet"));
}

/**
 * @brief Controls helmet value on a entity.
 *
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of helmet.
 */
inline void ToolsSetHelmet(int entity, bool bEnable)
{
    // Sets helmet on the entity
    SetEntProp(entity, Prop_Send, "m_bHasHelmet", bEnable);
}

/**
 * @brief Gets suit value on a entity.
 *
 * @param entity            The entity index.
 * @return                  The aspect of the entity suit.
 */
inline bool ToolsGetHeavySuit(int entity)
{
    // Gets suit on the entity
    return view_as<bool>(GetEntProp(entity, Prop_Send, "m_bHasHeavyArmor"));
}

/**
 * @brief Controls suit value on a entity.
 *
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of suit.
 */
inline void ToolsSetHeavySuit(int entity, bool bEnable)
{
    // Sets suit on the entity
    SetEntProp(entity, Prop_Send, "m_bHasHeavyArmor", bEnable);
}

/**
 * @brief Gets the active weapon index of a entity.
 *
 * @param entity            The entity index.
 * @return                  The weapon index.
 */
inline int ToolsGetActiveWeapon(int entity)
{
    // Gets weapon on the entity
    return GetEntPropEnt(entity, Prop_Send, "m_hActiveWeapon");
}

/**
 * @brief Sets the active weapon index of a entity.
 *
 * @param entity            The entity index.
 * @param weapon            The weapon index.
 */
/*void ToolsSetActiveWeapon(int entity, int weapon)
{
    // Sets weapon on the entity    
    SetEntPropEnt(entity, Prop_Send, "m_hActiveWeapon", weapon);
}*/

/**
 * @brief Gets the addon bits of a entity.
 *
 * @param entity            The entity index.
 * @return                  The addon bits.
 */
inline int ToolsGetAddonBits(int entity)
{
    // Gets addon value on the entity    
    return GetEntProp(entity, Prop_Send, "m_iAddonBits");
}

/**
 * @brief Sets the addon bits index of a entity.
 *
 * @param entity            The entity index.
 * @param iValue            The addon bits.
 */
inline void ToolsSetAddonBits(int entity, int iValue)
{
    // Sets addon value on the entity    
    SetEntProp(entity, Prop_Send, "m_iAddonBits", iValue);
}

/**
 * @brief Gets the observer mode of a entity.
 *
 * @param entity            The entity index.
 * @return                  The mode index.
 */
inline int ToolsGetObserverMode(int entity)
{
    // Gets obs mode on the entity    
    return GetEntProp(entity, Prop_Data, "m_iObserverMode");
}

/**
 * @brief Gets the observer target of a entity.
 *
 * @param entity            The entity index.
 * @return                  The target index.
 */
inline int ToolsGetObserverTarget(int entity)
{
    // Gets obs mode on the entity    
    return GetEntPropEnt(entity, Prop_Data, "m_hObserverTarget");
}

/**
 * @brief Gets hitgroup value on a entity.
 *
 * @param entity            The entity index.
 * @return                  The hitgroup index.
 */
inline int ToolsGetHitGroup(int entity)
{
    // Gets hitgroup on the entity    
    return GetEntProp(entity, Prop_Send, "m_LastHitGroup");
}

/**
 * @brief Gets or sets a entity score or deaths.
 * 
 * @param entity            The entity index.
 * @param bScore            True to look at score, false to look at deaths.  
 * @return                  The score or death count of the entity.
 */
inline int ToolsGetScore(int entity, bool bScore = true)
{
    // If score is true, then return entity score, otherwise return entity deaths
    return GetEntProp(entity, Prop_Data, bScore ? "m_iFrags" : "m_iDeaths");
}

/**
 * @brief Sets a entity score or deaths.
 * 
 * @param entity            The entity index.
 * @param bScore            True to look at score, false to look at deaths.  
 * @param iValue            The score/death amount.
 */
inline void ToolsSetScore(int entity, bool bScore = true, int iValue = 0)
{
    // If score is true, then set entity score, otherwise set entity deaths
    SetEntProp(entity, Prop_Data, bScore ? "m_iFrags" : "m_iDeaths", iValue);
}

/**
 * @brief Sets the gravity of a entity.
 * 
 * @param entity            The entity index.
 * @param flValue           The gravity amount.
 */
inline void ToolsSetGravity(int entity, float flValue)
{
    // Sets gravity on the entity
    SetEntPropFloat(entity, Prop_Data, "m_flGravity", flValue);
}

/**
 * @brief Sets the spotting of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of spotting.
 */
/* void ToolsSetSpot(int entity, bool bEnable)
{
    // If retrieve if true, then reset variables
    if (!bEnable)
    {
        // Sets value on the entity
        SetEntData(entity, Player_Spotted, false, 1, true);
        SetEntData(entity, Player_SpottedByMask, false, _, true);
        SetEntData(entity, Player_SpottedByMask + 4, false, _, true); /// That is table
        SetEntData(entity, Player_Spotted - 4, 0, _, true);
    }
    else
    {
        // Sets value on the entity
        SetEntData(entity, Player_Spotted - 4, 9, _, true);
    }
} */

/**
 * @brief Sets the detecting of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of detection.
 */
inline void ToolsSetDetecting(int entity, bool bEnable)
{
    // Sets glow on the entity
    SetEntPropFloat(entity, Prop_Send, "m_flDetectedByEnemySensorTime", bEnable ? (GetGameTime() + 9999.0) : 0.0);
}

/**
 * @brief Sets the hud of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of hud.
 */
/* void ToolsSetHud(int entity, bool bEnable)
{   
    // Sets hud type on the entity
    SetEntProp(entity, Prop_Send, "m_iHideHUD", bEnable ? (GetEntProp(entity, Prop_Send, "m_iHideHUD") & ~HIDEHUD_CROSSHAIR) : (GetEntProp(entity, Prop_Send, "m_iHideHUD") | HIDEHUD_CROSSHAIR));
} */

/**
 * @brief Sets the arms of a entity.
 * 
 * @param entity            The entity index.
 * @param sModel            The model path.
 */
inline void ToolsSetArm(int entity, char[] sModel)
{
    // Sets arm on the entity
    SetEntPropString(entity, Prop_Send, "m_szArmsModel", sModel);
}

/**
 * @brief Sets the attack delay of a entity.
 * 
 * @param entity            The entity index.
 * @param flValue           The speed amount.
 */
inline void ToolsSetAttack(int entity, float flValue)
{
    // Sets next attack on the entity
    SetEntPropFloat(entity, Prop_Send, "m_flNextAttack", flValue);
}

/**
 * @brief Sets the flashlight of a entity.
 * 
 * @param entity            The entity index.
 * @param bEnable           Enable or disable an aspect of flashlight.
 */
inline void ToolsSetFlashLight(int entity, bool bEnable)
{
    // Sets flashlight on the entity
    ToolsSetEffect(entity, bEnable ? (ToolsGetEffect(entity) ^ EF_DIMLIGHT) : 0);
}

/**
 * @brief Sets the fov of a entity.
 * 
 * @param entity            The entity index.
 * @param iValue            (Optional) The fov amount.
 */
inline void ToolsSetFov(int entity, int iValue = 90)
{
    // Sets fov on the entity
    SetEntProp(entity, Prop_Send, "m_iFOV", iValue);
    SetEntProp(entity, Prop_Send, "m_iDefaultFOV", iValue);
}

/**
 * @brief Sets body/skin for the entity.
 *
 * @param entity            The entity index.
 * @param iBody             (Optional) The body index.
 * @param iSkin             (Optional) The skin index.
 */
inline void ToolsSetTextures(int entity, int iBody = -1, int iSkin = -1)
{
    if (iBody != -1) SetEntProp(entity, Prop_Send, "m_nBody", iBody);
    if (iSkin != -1) SetEntProp(entity, Prop_Send, "m_nSkin", iSkin);
}

/**
 * @brief Gets the effect of an entity.
 * 
 * @param entity            The entity index.
 * @return                  The effect value.
 */
inline int ToolsGetEffect(int entity)
{
    // Gets effect on the entity    
    return GetEntProp(entity, Prop_Send, "m_fEffects");
}

/**
 * @brief Sets the effect of an entity.
 * 
 * @param entity            The entity index.
 * @param iValue            The effect value.
 */
inline void ToolsSetEffect(int entity, int iValue)
{
    // Sets effect on the entity
    SetEntProp(entity, Prop_Send, "m_fEffects", iValue);
}

/**
 * @brief Gets the activator of an entity.
 *
 * @param entity            The entity index.
 * @return                  The activator index.
 */
inline int ToolsGetActivator(int entity)
{
    // Gets activator on the entity
    return GetEntPropEnt(entity, Prop_Data, "m_pActivator");
}

/**
 * @brief Sets the model of an entity.
 * 
 * @param entity            The entity index.
 * @param iModel            The model index.
 */
inline void ToolsSetModelIndex(int entity, int iModel)
{
    // Sets index on the entity
    SetEntProp(entity, Prop_Send, "m_nModelIndex", iModel);
}

/**
 * @brief Gets the owner of an entity.
 * 
 * @param entity            The entity index.
 * @return                  The owner index.
 */
inline int ToolsGetOwner(int entity)
{
    // Gets owner on the entity
    return GetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity");
}

/**
 * @brief Sets the owner of an entity.
 * 
 * @param entity            The entity index.
 * @param owner             The owner index.
 */
inline void ToolsSetOwner(int entity, int owner)
{
    // Sets owner on the entity
    SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", owner);
}

/**
 * @brief Gets the parent of an entity.
 * 
 * @param entity            The entity index.
 * @return                  The parent index.
 */
inline int ToolsGetParent(int entity)
{
    // Gets owner on the entity
    return GetEntPropEnt(entity, Prop_Data, "m_pParent");
}

/**
 * @brief Sets the parent of an entity.
 * 
 * @param entity            The entity index.
 * @param parent            The parent index.
 */
inline void ToolsSetParent(int entity, int parent)
{
    // Sets parent on the entity
    SetEntPropEnt(entity, Prop_Data, "m_pParent", parent);
}
