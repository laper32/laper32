#if defined _playermgr_included
#endinput
#endif
#define _playermgr_included

/**
 * @brief Returns true if the player is connected and alive, false if not.
 *
 * @param client            The client index.
 * @param bAlive            (Optional) Set to true to validate that the client is alive, false to ignore.
 *  
 * @return                  True or false.
 **/
inline bool IsPlayerExist(int client, bool bAlive = true)
{
    // If client isn't valid, then stop
    if (client <= 0 || client > MaxClients)
    {
        return false;
    }

    // If client isn't connected, then stop
    if (!IsClientConnected(client))
    {
        return false;
    }

    // If client isn't in game, then stop
    if (!IsClientInGame(client) || IsClientInKickQueue(client))
    {
        return false;
    }

    // If client is TV, then stop
    if (IsClientSourceTV(client))
    {
        return false;
    }

    // If client isn't alive, then stop
    if (bAlive && !IsPlayerAlive(client))
    {
        return false;
    }

    // If client exist
    return true;
}

/**
 * @brief Returns whether a player is in a spesific group or not.
 *
 * @param client            The client index.
 * @param sGroup            The SourceMod group name to check.
 *
 * @return                  True or false.
 **/
inline bool IsPlayerInGroup(int client, char[] sGroup)
{
    // Validate client
    if (!IsPlayerExist(client, false))
    {
        return false;
    }

    /*********************************
     *                               *
     *   FLAG GROUP AUTHENTICATION   *
     *                               *
     *********************************/

    // Finds a group by name
    GroupId nGroup = FindAdmGroup(sGroup);
    
    // Validate group
    if (nGroup == INVALID_GROUP_ID)
    {
        return false;
    }
     
    // Retrieves a client AdminId
    AdminId iD = GetUserAdmin(client);
    
    // Validate id
    if (iD == INVALID_ADMIN_ID)
    {
        return false;
    }

    // Initialize group char
    static char sGroupName[SMALL_LINE_LENGTH];

    // Gets immunity level
    int iImmunity = GetAdmGroupImmunityLevel(nGroup);
    
    // i = group index
    int iSize = GetAdminGroupCount(iD);
    for (int i = 0; i < iSize; i++)
    {
        // Gets group name
        nGroup = GetAdminGroup(iD, i, sGroupName, sizeof(sGroupName));

        // Validate groups
        if (!strcmp(sGroup, sGroupName, false) || iImmunity <= GetAdmGroupImmunityLevel(nGroup))
        {
            return true;
        }
    }
    
    // No groups or no match
    return false;
}