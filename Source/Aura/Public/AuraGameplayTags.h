// Copy Right Shredder

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * singleton containing native game play tags 
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();


	/* Primary */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Arcane;
	FGameplayTag Attributes_Primary_Mind;
	FGameplayTag Attributes_Primary_Faith;


	/*Secondary*/
	FGameplayTag Attributes_Secondary_Base_MaxHealth;
	FGameplayTag Attributes_Secondary_Base_MaxMana;
	FGameplayTag Attributes_Secondary_Base_MaxStamina;
	FGameplayTag Attributes_Secondary_Base_MaxShield;
	
	FGameplayTag Attributes_Secondary_Attack_ArmorPenetration;
	FGameplayTag Attributes_Secondary_Attack_MagicPenetration;
	FGameplayTag Attributes_Secondary_Attack_TruePenetration;
	FGameplayTag Attributes_Secondary_Attack_CriticalHitChance;
	FGameplayTag Attributes_Secondary_Attack_CriticalHitDamage;

	FGameplayTag Attributes_Secondary_Regen_LifeSteal;
	FGameplayTag Attributes_Secondary_Regen_HealPower;
	FGameplayTag Attributes_Secondary_Regen_HealthRegen;
	FGameplayTag Attributes_Secondary_Regen_ManaRegen;
	FGameplayTag Attributes_Secondary_Regen_StaminaRegen;

	FGameplayTag Attributes_Secondary_Defence_Armor;
	FGameplayTag Attributes_Secondary_Defence_MagicResist;
	FGameplayTag Attributes_Secondary_Defence_FireResist;
	FGameplayTag Attributes_Secondary_Defence_LightningResist;
	FGameplayTag Attributes_Secondary_Defence_BloodResist;
	FGameplayTag Attributes_Secondary_Defence_TrueResist;
	FGameplayTag Attributes_Secondary_Defence_Tenacity;
	FGameplayTag Attributes_Secondary_Defence_BlockHitChance;
	FGameplayTag Attributes_Secondary_Defence_CriticalHitResistance;


	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;


	FGameplayTag Damage;
	FGameplayTag Damage_Max;

	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Physical_Max;

	FGameplayTag Damage_Magical;
	FGameplayTag Damage_Magical_Max;

	FGameplayTag Damage_True;
	FGameplayTag Damage_True_Max;

	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Fire_Max;

	FGameplayTag Damage_Blood;
	FGameplayTag Damage_Blood_Max;

	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Lightning_Max;


	TMap<FGameplayTag,FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag,FGameplayTag> MaxDamageTypesToResistances;
	TMap<FGameplayTag,FGameplayTag> ResistancesToPenetrations;
	


	FGameplayTag Effects_HitReact;

private:
	static FAuraGameplayTags GameplayTags;
};
