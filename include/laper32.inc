#if defined _laper32_included
#endinput
#endif
#define _laper32_included

#define inline stock

#if !defined _sourcemod_included
#include <sourcemod>
#endif

#if !defined _sdktools_included
#include <sdktools>
#endif

#if !defined _sdkhooks_included
#include <sdkhooks>
#endif

#if !defined _cstrike_included
#include <cstrike>
#endif

#if !defined _ptah_included
#include <ptah>
#endif

#if !defined _dhooks_included
#include <dhooks>
#endif

#include <laper32/const.inc>
#include <laper32/engine.inc>
#include <laper32/math.inc>
#include <laper32/mem.inc>
#include <laper32/paramparser.inc>
#include <laper32/fileparser.inc>
#include <laper32/tools.inc>
#include <laper32/utils.inc>
#include <laper32/text.inc>
#include <laper32/playermgr.inc>
#include <laper32/hint.inc>
#include <laper32/md5.inc>
#include <laper32/base64.inc>

// Here is used for _ArmsFix_ Extension
// Do not edit it unless you _EXACTLY_ know what you are doing!
public Extension _ext_armsFix = 
{
	name = "ArmsFix",
	file = "ArmsFix.ext.2.csgo",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0
#endif
};