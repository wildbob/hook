#pragma once
#include "netvar_manager.h"
#include "csgo.h"


#define XorStr(s)(s)


	class c_attribute;
	class c_grenade;
	class c_entity;
	struct CHudTexture
	{
		char	szShortName[64];	//0x0000
		char	szTextureFile[64];	//0x0040
		bool	bRenderUsingFont;	//0x0080
		bool	bPrecached;			//0x0081
		char	cCharacterInFont;	//0x0082
		char    pad;		        //0x0083
		HFont	hFont;				//0x0084
		int		iTextureId;			//0x0088
		float	afTexCoords[4];		//0x008C
		int		iPosX[4];			//0x009C
	}; //Size=0x00AC
	struct weapon_info
	{
		BYTE		pad_0x0000[4];			//0x0000
		bool		bParsedScript;			//0x0004
		bool		bLoadedHudElements;		//0x0005
		char		szClassName[80];		//0x0006
		char		szPrintName[80];		//0x0056
		char		szViewModel[80];		//0x00A6
		char		szWorldModel[80];		//0x00F6
		char		szBulletType[32];		//0x0146
		char		szWorldDroppedModel[80];//0x0166
		char		szAnimationPrefix[16];	//0x01B6
		BYTE		pad_0x01C6[2];			//0x01C6
		int			iSlot;					//0x01C8
		int			iPosition;				//0x01CC
		int			iMaxClip1;				//0x01D0
		int			iMaxClip2;				//0x01D4
		int			iDefaultClip1;			//0x01D8
		int			iDefaultClip2;			//0x01DC
		int			iWeight;				//0x01E0
		int			iRumbleEffect;			//0x01E4
		bool		bAutoSwitchTo;			//0x01E8
		bool		bAutoSwitchFrom;		//0x01E9
		BYTE		pad_0x01EA[2];			//0x01EA
		int			iFlags;					//0x01EC
		char		szAmmo1[16];			//0x01F0
		char		szAmmo2[16];			//0x0200
		char		szAIAddOn[80];			//0x0210
		char		aShootSounds[17][80];	//0x0260
		char PAD_NEW[80];
		int			iAmmoType;
		int			iAmmo2Type;
		bool		bMeleeWeapon;
		bool		bBuiltRightHanded;
		bool		bAllowFlipping;
		BYTE		pad_0x07BB;
		int			iSpriteCount;
		CHudTexture* iconWeaponS;
		CHudTexture* iconWeapon;
		CHudTexture* iconAmmo;
		CHudTexture* iconAmmo2;
		CHudTexture* iconCrosshair;
		CHudTexture* iconAutoaim;
		CHudTexture* iconZoomedCrosshair;
		CHudTexture* iconZoomedAutoaim;
		CHudTexture* iconWeaponSmall;
		bool		bShowUsageHint;
		BYTE		pad_0x07E5[3];
		int32_t		iWeaponType;
		int			iTeam;
		int			iWeaponID;
		bool		bFullAuto;
		BYTE		pad_0x07F5[3];
		float		flHeatPerShot;
		int			iWeaponPrice;
		float		flArmorRatio;
		float		flMaxPlayerSpeed;
		float		flMaxPlayerSpeedAlt;
		int			iCrosshairMinDistance;
		int			iCrosshairDeltaDistance;
		float		flPenetration;
		int			iDamage;
		float		flRange;
		float		flRangeModifier;
		int			iBullets;
		float		flCycleTime;
		float		flCycleTimeAlt;
		char		szHeatEffect[80];
		float		aflSmokeColor[3];
		char		szMuzzleFlashEffect_1stPerson[80];
		char		szMuzzleFlashEffect_3rdPerson[80];
		char		szEjectBrassEffect[80];
		char		szTracerEffect[80];
		int			iTracerFrequency;
		float		flSpread;
		float		flSpreadAlt;
		float		flInaccuracyCrouch;
		float		flInaccuracyCrouchAlt;
		float		flInaccuracyStand;
		float		flInaccuracyStandAlt;
		float		flInaccuracyJump;
		float		flInaccuracyJumpAlt;
		float		flInaccuracyLand;
		float		flInaccuracyLandAlt;
		float		flInaccuracyLadder;
		float		flInaccuracyLadderAlt;
		float		flInaccuracyFire;
		float		flInaccuracyFireAlt;
		float		flInaccuracyMove;
		float		flInaccuracyMoveAlt;
		float		flRecoveryTimeStand;
		float		flRecoveryTimeCrouch;
		float		flInaccuracyReload;
		float		flInaccuracyAltSwitch;
		float		flRecoilAngle;
		float		flRecoilAngleAlt;
		float		flRecoilAngleVariance;
		float		flRecoilAngleVarianceAlt;
		float		flRecoilMagnitude;
		float		flRecoilMagnitudeAlt;
		float		flRecoilMagnitudeVariance;
		float		flRecoilMagnitudeVarianceAlt;
		int			iRecoilSeed;
		float		flFlinchVelocityModifierLarge;
		float		flFlinchVelocityModifierSmall;
		float		flTimeToIdle;
		float		flIdleInterval;
		float		recoilTable[2][128];
		int			iZoomLevels;
		int			iZoomFOV[3];
		float		fZoomTime[3];
		bool		bHideViewModelZoomed;
		char		szZoomInSound[80];
		char		szZoomOutSound[80];
		BYTE		pad_0x0F11[3];
		float		flBotAudibleRange;
		bool		bCanUseWithShield;
		char		szWrongTeamMsg[32];
		char		szAnimPrefix[16];
		char		szShieldViewModel[64];
		char		szAddonModel[80];
		char		szAddonLocation[80];
		char		szSilencerModel[80];
		BYTE		pad_0x1079[3];
		float		flAddonScale;
		float		flThrowVelocity;
		int			iKillAward;
		BYTE		pad_0x1088[8];
	};
	class c_weapon : public i_client_entity {
		template<class T>
		T GetFieldValue(int offset) {
			return *(T*)((uintptr_t)this + offset);
		}
		template<class T>
		T* GetFieldPointer(int offset) {
			return (T*)((uintptr_t)this + offset);
		}
	public:
		int *get_model_index() {
			static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nModelIndex"));
			return GetFieldPointer<int>(m_nModelIndex);
		}
		float& get_fire_ready()
		{
			auto offset = GET_NETVAR("DT_WeaponCSBase", "m_flPostponeFireReadyTime");
			return *(float*)((uintptr_t)this + offset);
		}

		float get_next_primary_attack()
		{
			static int m_flNextPrimaryAttack = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_flNextPrimaryAttack"));
			return GetFieldValue<float>(m_flNextPrimaryAttack);
		}

		void set_model_index(int modelIndex)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int);
			return g_utils::get_v_func<OriginalFn>(this, 75)(this, modelIndex);
		}
		float get_accuracy() {
			static int m_fAccuracyPenalty = GET_NETVAR(XorStr("DT_WeaponCSBase"), XorStr("m_fAccuracyPenalty"));
			return GetFieldValue<float>(m_fAccuracyPenalty);
		}
		int get_state() {
			static int m_iState = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iState"));
			return GetFieldValue<int>(m_iState);
		}
		const char* get_name() {
			typedef const char* (__thiscall* tGetName)(void*);
			return g_utils::get_v_func<tGetName>(this, 378)(this);
		}
		int get_id() {
			typedef int(__thiscall* tGetId)(void*);
			return g_utils::get_v_func<tGetId>(this, 458)(this);
		}
		int* get_item_definition_index()
		{
			static int m_iItemDefinitionIndex = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemDefinitionIndex"));
			return GetFieldPointer<int>(m_iItemDefinitionIndex);
		}
		float get_cone() {
			typedef float(__thiscall* OriginFN)(void*);
			return g_utils::get_v_func<OriginFN>(this, 483)(this);
		}
		float get_spread() {
			typedef float(__thiscall* OriginFN)(void*);
			return g_utils::get_v_func<OriginFN>(this, 484)(this);
		}
		void update_accuracy() {
			typedef void(__thiscall* OriginFN)(void*);
			g_utils::get_v_func<OriginFN>(this, 485)(this);
		}
		c_entity* get_owner()
		{
			static int m_hOwnerEntity = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_hOwnerEntity"));
			return (c_entity*)g_csgo.m_entitylist->get_entity_handle((c_base_handle)m_hOwnerEntity);
		}
		weapon_info* get_weapon_data()
		{
			typedef weapon_info*(__thiscall* OriginalFn)(PVOID);
			return g_utils::get_v_func<OriginalFn>(this, 456)(this);
		}
		bool is_greande()
		{
			return this->get_weapon_data()->iWeaponType == CSWeaponType::WEAPONTYPE_GRENADE;
		}
		IClientNetworkable* get_networkable()
		{
			return (IClientNetworkable*)((uintptr_t)this + 0x8);
		}
		c_grenade *get_greande() {
			return (c_grenade*)this;
		}
		int get_max_clip_1() {
			typedef int(__thiscall* OriginalFn)(void*);
			return g_utils::get_v_func<OriginalFn>(this, 367)(this);
		}
		int get_current_ammo() {
			static int m_iClip1 = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iClip1"));
			return GetFieldValue<int>(m_iClip1);
		}
		bool is_reloading() {
			static int m_bReloadVisuallyComplete = GET_NETVAR(XorStr("DT_WeaponCSBase"), XorStr("m_bReloadVisuallyComplete"));
			return !GetFieldValue<bool>(m_bReloadVisuallyComplete);
		}

		bool is_reloading_local() {
			return GetFieldValue<bool>(0x3235);
		}

		bool is_scoped_weapon()
		{
			int id = *this->get_item_definition_index();

			switch (id)
			{
			case EItemDefinitionIndex::weapon_aug:
			case EItemDefinitionIndex::weapon_awp:
			case EItemDefinitionIndex::weapon_g3sg1:
			case EItemDefinitionIndex::weapon_sg556:
			case EItemDefinitionIndex::weapon_ssg08:
			case EItemDefinitionIndex::weapon_scar20:
				return true;
			default:
				return false;
			}
		}

		bool is_valid_weapon()
		{
			int id = this->get_id();

			switch (id)
			{
			case EItemDefinitionIndex::weapon_deagle:
			case EItemDefinitionIndex::weapon_elite:
			case EItemDefinitionIndex::weapon_fiveseven:
			case EItemDefinitionIndex::weapon_glock:
			case EItemDefinitionIndex::weapon_ak47:
			case EItemDefinitionIndex::weapon_aug:
			case EItemDefinitionIndex::weapon_awp:
			case EItemDefinitionIndex::weapon_famas:
			case EItemDefinitionIndex::weapon_g3sg1:
			case EItemDefinitionIndex::weapon_galilar:
			case EItemDefinitionIndex::weapon_m249:
			case EItemDefinitionIndex::weapon_m4a4:
			case EItemDefinitionIndex::weapon_mac10:
			case EItemDefinitionIndex::weapon_p90:
			case EItemDefinitionIndex::weapon_ump:
			case EItemDefinitionIndex::weapon_xm1014:
			case EItemDefinitionIndex::weapon_bizon:
			case EItemDefinitionIndex::weapon_mag7:
			case EItemDefinitionIndex::weapon_negev:
			case EItemDefinitionIndex::weapon_sawedoff:
			case EItemDefinitionIndex::weapon_tec9:
				return true;
			case EItemDefinitionIndex::weapon_taser:
				return false;
			case EItemDefinitionIndex::weapon_hkp2000:
			case EItemDefinitionIndex::weapon_mp7:
			case EItemDefinitionIndex::weapon_mp9:
			case EItemDefinitionIndex::weapon_nova:
			case EItemDefinitionIndex::weapon_p250:
			case EItemDefinitionIndex::weapon_scar20:
			case EItemDefinitionIndex::weapon_sg556:
			case EItemDefinitionIndex::weapon_ssg08:
				return true;
			case EItemDefinitionIndex::weapon_knife:
			case EItemDefinitionIndex::weapon_flashbang:
			case EItemDefinitionIndex::weapon_hegrenade:
			case EItemDefinitionIndex::weapon_smokegrenade:
			case EItemDefinitionIndex::weapon_molotov:
			case EItemDefinitionIndex::weapon_decoy:
			case EItemDefinitionIndex::weapon_incgrenade:
			case EItemDefinitionIndex::weapon_c4:
			case EItemDefinitionIndex::weapon_knife_t:
				return false;
			case EItemDefinitionIndex::weapon_m4a1_silencer:
			case EItemDefinitionIndex::weapon_usp_silencer:
			case EItemDefinitionIndex::weapon_cz75a:
			case EItemDefinitionIndex::weapon_revolver:
				return true;
			default:
				return false;
			}
		}
		float hit_chance(float chance)
		{
			float hitchance = 100;

			if (chance >= 1)
			{
				float inaccuracy = get_inaccuracy();
				if (inaccuracy == 0) inaccuracy = 0.0000001;
				inaccuracy = 1 / inaccuracy;
				hitchance = inaccuracy;
			}
			return hitchance;
		}
		float get_inaccuracy()
		{
			typedef float(__thiscall* oInaccuracy)(PVOID);
			return g_utils::get_v_func< oInaccuracy >(this, 483)(this);
		}
		bool is_pistol()
		{
			int id = this->get_id();

			switch (id)
			{
			case EItemDefinitionIndex::weapon_deagle:
			case EItemDefinitionIndex::weapon_elite:
			case EItemDefinitionIndex::weapon_fiveseven:
			case EItemDefinitionIndex::weapon_glock:
				return true;
			case EItemDefinitionIndex::weapon_ak47:
			case EItemDefinitionIndex::weapon_aug:
			case EItemDefinitionIndex::weapon_awp:
			case EItemDefinitionIndex::weapon_famas:
			case EItemDefinitionIndex::weapon_g3sg1:
			case EItemDefinitionIndex::weapon_galilar:
			case EItemDefinitionIndex::weapon_m249:
			case EItemDefinitionIndex::weapon_m4a4:
			case EItemDefinitionIndex::weapon_mac10:
			case EItemDefinitionIndex::weapon_p90:
			case EItemDefinitionIndex::weapon_ump:
			case EItemDefinitionIndex::weapon_xm1014:
			case EItemDefinitionIndex::weapon_bizon:
			case EItemDefinitionIndex::weapon_mag7:
			case EItemDefinitionIndex::weapon_negev:
			case EItemDefinitionIndex::weapon_sawedoff:
				return false;
			case EItemDefinitionIndex::weapon_tec9:
			case EItemDefinitionIndex::weapon_taser:
			case EItemDefinitionIndex::weapon_hkp2000:
				return true;
			case EItemDefinitionIndex::weapon_mp7:
			case EItemDefinitionIndex::weapon_mp9:
			case EItemDefinitionIndex::weapon_nova:
				return false;
			case EItemDefinitionIndex::weapon_p250:
				return true;
			case EItemDefinitionIndex::weapon_scar20:
			case EItemDefinitionIndex::weapon_sg556:
			case EItemDefinitionIndex::weapon_ssg08:
			case EItemDefinitionIndex::weapon_knife:
			case EItemDefinitionIndex::weapon_flashbang:
			case EItemDefinitionIndex::weapon_hegrenade:
			case EItemDefinitionIndex::weapon_smokegrenade:
			case EItemDefinitionIndex::weapon_molotov:
			case EItemDefinitionIndex::weapon_decoy:
			case EItemDefinitionIndex::weapon_incgrenade:
			case EItemDefinitionIndex::weapon_c4:
			case EItemDefinitionIndex::weapon_knife_t:
			case EItemDefinitionIndex::weapon_m4a1_silencer:
				return false;
			case EItemDefinitionIndex::weapon_usp_silencer:
				return true;
			case EItemDefinitionIndex::weapon_cz75a:
				return true;
			case EItemDefinitionIndex::weapon_revolver:
				return false;
			default:
				return false;
			}
		}
	};


	class c_entity : public i_client_entity
	{
		template<class T>
		inline T GetFieldValue(int offset) {
			return *(T*)((uintptr_t)this + offset);
		}
		template<class T>
		T* GetFieldPointer(int offset) {
			return (T*)((uintptr_t)this + offset);
		}
	public:
		static c_entity* get_local_player()
		{
			return (c_entity*)g_csgo.m_entitylist->get_entity(g_csgo.m_engine->get_local_player());
		}
		player_info_t get_player_info()
		{
			player_info_t pinfo;
			g_csgo.m_engine->get_player_info(get_index(), &pinfo);
			return pinfo;
		}
		int* get_wearables()
		{
			static int offset = GET_NETVAR("DT_BaseCombatCharacter", "m_hMyWearables");
			return (int*)((uintptr_t)this + offset);
		}
		c_base_handle& get_view_model() {
			static uintptr_t m_hViewModel = GET_NETVAR("CBasePlayer", "m_hViewModel[0]");
			return *reinterpret_cast<c_base_handle*>(uintptr_t(this) + m_hViewModel);
		}

		std::string get_name()
		{
			std::string name = get_player_info().szName;
			std::size_t found = name.find("\n");
			while (found != std::string::npos)
			{
				name.replace(found, found + 2, "");
				found = name.find("\n");
			}
			return name;
		}
		bool setup_bones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
		{
			//Invalidate cache PVSFIX
			//static uintptr_t m_nWritableBones = GET_NETVAR(XorStr("DT_BaseAnimating"), XorStr("m_nForceBone")) + 0x20;
			//static uintptr_t m_dwOcclusionArray = *(uintptr_t*)(O::FindSignature(XorStr("client.dll"), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0x1);
			//static uintptr_t m_bDidCheckForOcclusion = *(uintptr_t*)(O::FindSignature(XorStr("client.dll"), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0xE);
			//static uintptr_t InvalidateBoneCache = O::FindSignature(XorStr("client.dll"), XorStr("80 3D ? ? ? ? 00 74 16 A1"));
			//*(int*)((uintptr_t)this + m_nWritableBones) = 0;
			//*(int*)((uintptr_t)this + m_bDidCheckForOcclusion) = reinterpret_cast<int*>(m_dwOcclusionArray)[1];
			//reinterpret_cast<void(__fastcall*)(void*)>(InvalidateBoneCache)(pEntity);

			__asm
			{
				mov edi, this
				lea ecx, dword ptr ds : [edi + 0x4]
				mov edx, dword ptr ds : [ecx]
				push currentTime
				push boneMask
				push nMaxBones
				push pBoneToWorldOut
				call dword ptr ds : [edx + 0x34]
			}
		}
		int* get_view_model_index()
		{
			static int offset = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iViewModelIndex"));
			return GetFieldPointer<int>(offset);
		}
		c_weapon* get_active_weapon()
		{	\
			//index: 262
			//ref: [%s]->Weapon_GetActiveSlot()
			typedef c_weapon* (__thiscall* OriginalFn)(void*);
			return g_utils::get_v_func<OriginalFn>(this, 262)(this);
		}
		c_weapon* get_weapon(void)
		{
			uintptr_t weaponData = *(uintptr_t*)((uintptr_t)this + GET_NETVAR(XorStr("DT_BaseCombatCharacter"), XorStr("m_hActiveWeapon")));
			return (c_weapon*)g_csgo.m_entitylist->get_entity_handle((c_base_handle)weaponData);
		}
		float get_next_primary_attack(void)
		{
			auto offset = GET_NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
			return *(float*)((uintptr_t)this + offset);
		}
		int *get_model_index() {
			static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_nModelIndex"));
			return GetFieldPointer<int>(m_nModelIndex);
		}

		int get_shots_fired() {
			static int m_iShotsFired = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_iShotsFired"));
			return GetFieldValue<int>(m_iShotsFired);
		}

		QAngle *get_eye_angles()
		{
			static int m_angEyeAngles = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles[0]"));
			return GetFieldPointer<QAngle>(m_angEyeAngles);
		}

		int get_health() {
			static int m_iHealth = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_iHealth"));
			return GetFieldValue<int>(m_iHealth);
		}

		int get_arnmor() {
			static int m_ArmorValue = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_ArmorValue"));
			return GetFieldValue<int>(m_ArmorValue);
		}

		bool has_helmet() {
			static int m_bHasHelmet = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bHasHelmet"));
			return GetFieldValue<bool>(m_bHasHelmet);
		}

		bool* get_spotted() {
			static int m_bSpotted = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_bSpotted"));
			return GetFieldPointer<bool>(m_bSpotted);
		}

		int *get_tick_base() {
			static int m_nTickBase = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_nTickBase"));
			return GetFieldPointer<int>(m_nTickBase);
		}
		bool get_alive() {
			static int m_lifeState = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_lifeState"));
			return GetFieldValue<int>(m_lifeState) == 0;
		}
		IClientNetworkable* get_networkable()
		{
			return (IClientNetworkable*)((uintptr_t)this + 0x8);
		}
		const matrix3x4_t ent_world_transform()
		{
			static int m_rgflCoordinateFrame = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_CollisionGroup")) - 48;
			return GetFieldValue<const matrix3x4_t>(m_rgflCoordinateFrame);
		}

		int *get_team_num() {
			static int m_iTeamNum = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_iTeamNum"));
			return GetFieldPointer<int>(m_iTeamNum);
		}

		int *get_flags()
		{
			static int m_fFlags = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_fFlags"));
			return GetFieldPointer<int>(m_fFlags);
		}

		c_entity* get_observer_target() {
			static int m_hObserverTarget = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_hObserverTarget"));
			return (c_entity*)g_csgo.m_entitylist->get_entity_handle(GetFieldValue<c_base_handle>(m_hObserverTarget));
		}

		UINT* get_weapons() {
			static UINT m_hMyWeapons = GET_NETVAR(XorStr("DT_BaseCombatCharacter"), XorStr("m_hMyWeapons"));
			return GetFieldPointer<UINT>(m_hMyWeapons);
		}



		int* get_world_model_index()
		{
			static int offset = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iWorldModelIndex"));
			return GetFieldPointer<int>(offset);
		}

		Vector* get_view_offset() {
			static int m_vecViewOffset = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_vecViewOffset[0]"));
			return GetFieldPointer<Vector>(m_vecViewOffset);
		}

		Vector* get_vec_origin()
		{
			static int m_vecOrigin = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_vecOrigin"));
			return GetFieldPointer<Vector>(m_vecOrigin);
		}

		Vector& get_abs_origin(void)
		{
			typedef Vector(__thiscall* OriginFN)(PVOID);
			return g_utils::get_v_func<OriginFN>(this, 10)(this);
		}
		Vector get_eye_pos()
		{
			return *get_vec_origin() + *get_view_offset();
		}
		QAngle& get_abs_angles(void)
		{
			typedef Vector(__thiscall* OriginFN)(PVOID);
			return g_utils::get_v_func<OriginFN>(this, 11)(this);
		}
		float& get_sequence() {
			static int offset = GET_NETVAR("DT_BaseAnimating", "m_nSequence");
			return *(float*)((uintptr_t)this + offset);
		}
		float& get_cycle() {
			static int offset = GET_NETVAR("DT_BaseAnimating", "m_flCycle");
			return *(float*)((uintptr_t)this + offset);
		}
		float& get_pose_parameter(int index)
		{
			static int offset = GET_NETVAR("DT_BaseAnimating", "m_flPoseParameter");
			return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + offset + sizeof(float) * index);
		}
		Vector* get_view_punch() {
			static int m_viewPunchAngle = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_viewPunchAngle"));
			return GetFieldPointer<Vector>(m_viewPunchAngle);
		}

		Vector* get_aim_punch() {
			static int m_aimPunchAngle = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_aimPunchAngle"));
			return GetFieldPointer<Vector>(m_aimPunchAngle);
		}

		int* get_fov() {
			static int m_iFOV = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_iFOV"));
			return GetFieldPointer<int>(m_iFOV);
		}

		float* get_flash_time() {
			static int m_flFlashDuration = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flFlashDuration"));
			return GetFieldPointer<float>(m_flFlashDuration);
		}

	/*	bool is_visible()
		{
			Trace_t tr;
			Ray_t ray;
			CTraceFilter filter;
			filter.pSkip = this->get_local_player();

			matrix3x4_t boneMatrix[128];

			if (!this->setup_bones(boneMatrix, 128, 256, g_csgo.m_engine->get_last_time_stamp()))
				return false;

			matrix3x4_t hitbox = boneMatrix[ECSPlayerBones::HEAD_0];
			//-------------------------

			ray.Init(this->get_local_player()->get_eye_pos(), Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]));
			i::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &tr);

			return tr.m_pEnt == this || tr.fraction > 0.97f;
		}

		bool is_visible_2()
		{
			Trace_t tr;
			Ray_t ray;
			CTraceFilter filter;
			filter.pSkip = this->get_local_player();

			matrix3x4_t boneMatrix[128];

			if (!this->setup_bones(boneMatrix, 128, 256, g_csgo.m_engine->get_last_time_stamp()))
				return false;

			matrix3x4_t hitbox = boneMatrix[ECSPlayerBones::HEAD_0];
			//-------------------------

			ray.Init(this->get_local_player()->get_eye_pos(), Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]));
			i::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &tr);

			return tr.m_pEnt == this;
		}

		bool is_vector_visible(Vector vec) {
			Trace_t tr;
			Ray_t ray;
			CTraceFilter filter;
			filter.pSkip = this->get_local_player();

			ray.Init(this->get_local_player()->get_eye_pos(), vec);
			i::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &tr);

			return tr.m_pEnt == this;
		}

		bool can_hit(Vector end, c_entity* ent)
		{
			Ray_t ray;

			Trace_t tr;

			CTraceFilter traceFilter;
			traceFilter.pSkip = this;

			ray.Init(this->get_eye_pos(), end);

			i::engine_trace->clip_ray_to_entity(ray, MASK_SHOT, (IHandleEntity*)ent, &tr); // ignore grate

			if (!tr.m_pEnt)
				return false;

			c_entity *pEnt = (c_entity*)tr.m_pEnt;

			if (*pEnt->get_team_num() != *this->get_team_num())
				return true;

			return false;
		}*/

		bool is_moving()
		{
			return get_vec_velocity()->Length() > 0.1f;
		}

		uintptr_t get_glow_index() {
			static int m_glowIndex = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flFlashDuration")) + 0x18;
			return GetFieldValue<uintptr_t>(m_glowIndex);
		}

		Vector *get_vec_velocity() {
			static int m_vecVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_vecVelocity[0]"));
			return GetFieldPointer<Vector>(m_vecVelocity);
		}

		Vector *get_base_velocity() {
			static int m_vecBaseVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_vecBaseVelocity"));
			return GetFieldPointer<Vector>(m_vecBaseVelocity);
		}

		bool is_scoped() {
			static uintptr_t m_bIsScoped = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bIsScoped"));
			return *(bool*)((uintptr_t)this + m_bIsScoped);
		}

		float *get_lower_body_yaw() {
			static int m_flLowerBodyYawTarget = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flLowerBodyYawTarget"));
			return GetFieldPointer<float>(m_flLowerBodyYawTarget);
		}

		float *get_sim_time() {
			static int m_flSimulationTime = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_flSimulationTime"));
			return GetFieldPointer<float>(m_flSimulationTime);
		}

		float *get_anim_time() {
			static int m_flAnimTime = 0x0;
			return GetFieldPointer<float>(m_flAnimTime);
		}

		bool *get_ducked() {
			static int m_bDucked = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_bDucked"));
			return GetFieldPointer<bool>(m_bDucked);
		}

		bool *is_ducking() {
			static int m_bDucking = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_bDucking"));
			return GetFieldPointer<bool>(m_bDucking);
		}

		float *duck_speed() {
			static int m_flDuckSpeed = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_flDuckSpeed"));
			return GetFieldPointer<float>(m_flDuckSpeed);
		}


		bool in_buy_zone() {
			static int m_bInBuyZone = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bInBuyZone"));
			return GetFieldValue<bool>(m_bInBuyZone);
		}

		bool is_ducking2() {
			return (bool)(*this->get_flags() & (int)FL_DUCKING);
		}

		Vector *get_min() {
			static int m_vecMins = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_vecMins"));
			return GetFieldPointer<Vector>(m_vecMins);
		}

		Vector *get_max() {
			static int m_vecMaxs = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_vecMaxs"));
			return GetFieldPointer<Vector>(m_vecMaxs);
		}

		void update_client_side_anim() {
			g_utils::get_v_func<void(__thiscall*)(void*)>(this, 218)(this);
		}

		bool is_valid_player(bool isLocalPlayer = false) {
			if (!this)
				return false;
			if (this->get_client_class()->m_ClassID != EClassIds::CCSPlayer)
				return false;
			if (this->is_dormant())
				return false;
			if (!isLocalPlayer) {
				if (this->get_index() == this->get_local_player()->get_index())
					return false;
				if (this->is_immnue())
					return false;
			}
			if (!this->get_alive())
				return false;
			return true;
		}

		bool is_valid_weapon() {
			if (!this)
				return false;
			if (strstr(this->get_client_class()->m_pNetworkName, XorStr("CWeapon")) ||
				strstr(this->get_client_class()->m_pNetworkName, XorStr("CAK47")))
				return true;
			return false;
		}
/*
		Vector get_hitbox_pos(int iHitBox)
		{
			matrix3x4a_t matrix[128];

			if (this->setup_bones(matrix, 128, 0x00000100, g_csgo.m_engine->get_last_time_stamp()))
			{
				studiohdr_t* hdr = i::model_info->get_studio_model(this->get_model());

				if (!hdr)
					return Vector(0, 0, 0);

				mstudiohitboxset_t* set = hdr->pHitboxSet(0);

				mstudiobbox_t* hitbox = set->pHitbox(iHitBox);

				if (hitbox)
				{
					Vector vMin, vMax, vCenter, sCenter;
					m::vector_transform(hitbox->bbmin, matrix[hitbox->bone], vMin);
					m::vector_transform(hitbox->bbmax, matrix[hitbox->bone], vMax);
					vCenter = (vMin + vMax) *.5f;
					return vCenter;
				}
			}

			return Vector(0, 0, 0);
		}
		*/
		bool is_immnue() {
			static int m_bGunGameImmunity = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bGunGameImmunity"));
			return GetFieldValue<bool>(m_bGunGameImmunity);
		}

		float *get_fall_velocity() {
			static int m_flFallVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_flFallVelocity"));
			return GetFieldPointer<float>(m_flFallVelocity);
		}

		Vector world_space_center() {
			Vector Max = *this->get_max() + *this->get_vec_origin();
			Vector Min = *this->get_min() + *this->get_vec_origin();
			Vector Size = Max - Min;
			Size /= 2;
			Size += Min;
			return Size;
		}

		int *get_render_mode() {
			static int m_nRenderMode = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_nRenderMode"));
			return GetFieldPointer<int>(m_nRenderMode);
		}

		int *get_effects() {
			static int m_fEffects = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_fEffects"));
			return GetFieldPointer<int>(m_fEffects);
		}

		Color *get_color_render() {
			static int m_clrRender = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_clrRender"));
			return GetFieldPointer<Color>(m_clrRender);
		}

		int *get_texture_index() {
			static int m_iTextureFrameIndex = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_iTextureFrameIndex"));
			return GetFieldPointer<int>(m_iTextureFrameIndex);
		}

		float *get_fade_max() {
			static int m_fadeMaxDist = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_fadeMaxDist"));
			return GetFieldPointer<float>(m_fadeMaxDist);
		}

		float *get_fade_scale() {
			static int m_flFadeScale = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_flFadeScale"));
			return GetFieldPointer<float>(m_flFadeScale);
		}
	};

	class base_attribute : public c_entity
	{
		template<class T>
		inline T GetFieldValue(int offset) {
			return *(T*)((uintptr_t)this + offset);
		}
		template<class T>
		T* GetFieldPointer(int offset) {
			return (T*)((uintptr_t)this + offset);
		}
	public:
		int* get_item_definition_index()
		{
			static int m_iItemDefinitionIndex = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemDefinitionIndex"));
			return GetFieldPointer<int>(m_iItemDefinitionIndex);
		}
		void pre_data_update(int updateType)
		{
			PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
			typedef void(__thiscall* OriginalFn)(PVOID, int);
			return g_utils::get_v_func<OriginalFn>(pNetworkable, 6)(pNetworkable, updateType);
		}
		void set_model_index(int modelIndex)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, int);
			return g_utils::get_v_func<OriginalFn>(this, 75)(this, modelIndex);
		}
		int* get_account_id()
		{
			// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
			static int m_iAccountID1 = GET_NETVAR(("DT_BaseAttributableItem"), ("m_iAccountID"));
			return GetFieldPointer<int>(m_iAccountID1);
		}
		int* get_item_id_high() {
			static int m_iItemIDHigh = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemIDHigh"));
			return GetFieldPointer<int>(m_iItemIDHigh);
		}

		int* get_entity_quality() {
			static int m_iEntityQuality = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_iEntityQuality"));
			return GetFieldPointer<int>(m_iEntityQuality);
		}

		char* get_custom_name() {
			static int m_szCustomName = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_szCustomName"));
			return GetFieldPointer<char>(m_szCustomName);
		}

		int* get_paint_kit() {
			static int m_nFallbackPaintKit = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackPaintKit"));
			return GetFieldPointer<int>(m_nFallbackPaintKit);
		}

		int* get_seed() {
			static int m_nFallbackSeed = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackSeed"));
			return GetFieldPointer<int>(m_nFallbackSeed);
		}

		float* get_wear() {
			static int m_flFallbackWear = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_flFallbackWear"));
			return GetFieldPointer<float>(m_flFallbackWear);
		}

		int* get_stat_track() {
			static int m_bSpotted = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackStatTrak"));
			return GetFieldPointer<int>(m_bSpotted);
		}
	};
	class base_viewmodel : public c_entity
	{
		template<class T>
		inline T GetFieldValue(int offset) {
			return *(T*)((uintptr_t)this + offset);
		}
		template<class T>
		T* GetFieldPointer(int offset) {
			return (T*)((uintptr_t)this + offset);
		}
	public:
		int *get_view_model_index() {
			static int m_iViewModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nViewModelIndex"));
			return GetFieldPointer<int>(m_iViewModelIndex);
		}
		int *get_model_index() {
			static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nModelIndex"));
			return GetFieldPointer<int>(m_nModelIndex);
		}
		int get_weapon() {
			static uintptr_t m_hWeapon = GET_NETVAR("CBaseViewModel", "m_hWeapon");
			return *reinterpret_cast<int*>(uintptr_t(this) + m_hWeapon);
		}

		void set_weapon_model(const char* Filename, base_attribute* Weapon) {
			return g_utils::get_v_func<void(__thiscall*)(void*, const char*, base_attribute*)>(this, 242)(this, Filename, Weapon);
		}
	};
