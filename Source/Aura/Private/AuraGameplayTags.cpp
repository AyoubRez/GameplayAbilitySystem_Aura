// Copy Right Shredder


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*Primary*/
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString(
			"Improves Player Strength"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString(
			"Improves Player Health"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString(
			"Improves Player Ability Power and Mana"));

	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString(
			"Improves Player Technique"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString(
			"Improves Player Defensive stats "));

	GameplayTags.Attributes_Primary_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Arcane"),
		FString(
			"Improves Player Ability Technique And Damage"));

	GameplayTags.Attributes_Primary_Faith = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Faith"),
		FString(
			"Improves Player Critical Chance And Damage"));

	GameplayTags.Attributes_Primary_Mind = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Mind"),
		FString(
			"Improves Player Stamina"));

	/* Secondary*/

	/* Base */

	GameplayTags.Attributes_Secondary_Base_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Base.MaxHealth"),
		FString(
			"Player Max Health"));

	GameplayTags.Attributes_Secondary_Base_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Base.MaxMana"),
		FString(
			"Player Mana Pool"));

	GameplayTags.Attributes_Secondary_Base_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Base.MaxStamina"),
		FString(
			"Player Max Stamina"));

	GameplayTags.Attributes_Secondary_Base_MaxShield = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Base.MaxShield"),
		FString(
			"Player Max Shield"));

	/* Defence*/
	GameplayTags.Attributes_Secondary_Defence_Tenacity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.Tenacity"),
		FString(
			"Reduces Player CC Duration and Slow Resist"));


	GameplayTags.Attributes_Secondary_Defence_BlockHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.BlockHitChance"),
		FString(
			"Increase block hit chance"));

	GameplayTags.Attributes_Secondary_Defence_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.CriticalHitResistance"),
		FString(
			"Reduces Critical Damage Taken"));


	/*Attack Power */
	GameplayTags.Attributes_Secondary_Attack_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Attack.ArmorPenetration"),
		FString(
			"Increase Player Armor Ignore"));

	GameplayTags.Attributes_Secondary_Attack_MagicPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Attack.MagicPenetration"),
		FString(
			"Reduces Player MagicResist Ignore"));

	GameplayTags.Attributes_Secondary_Attack_TruePenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Secondary.Attack.TruePenetration"),
	FString(
		"Reduces Player TrueResist Ignore"));

	GameplayTags.Attributes_Secondary_Attack_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Attack.CriticalHitChance"),
		FString(
			"Increases Player Critical Hit Chance"));

	GameplayTags.Attributes_Secondary_Attack_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Attack.CriticalHitDamage"),
		FString(
			"Increases Player Critical Hit Damage"));

	/* Regen */
	GameplayTags.Attributes_Secondary_Regen_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Regen.HealthRegen"),
		FString(
			"Increases Player Health Regen "));

	GameplayTags.Attributes_Secondary_Regen_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Regen.ManaRegen"),
		FString(
			"Increases Player Mana Regen "));

	GameplayTags.Attributes_Secondary_Regen_StaminaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Regen.StaminaRegen"),
		FString(
			"Increases Player Stamina Regen "));

	GameplayTags.Attributes_Secondary_Regen_LifeSteal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Regen.LifeSteal"),
		FString(
			"Increases Player LifeSteal From Attacks "));

	GameplayTags.Attributes_Secondary_Regen_HealPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Regen.HealPower"),
		FString(
			"Increases Player Healing Power "));

	/* InputTags */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString(
			"Input Tag For Left Mouse Button Click"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString(
			"Input Tag For Right Mouse Button Click"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString(
			"Input Tag For 1 key Button Click"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString(
			"Input Tag For 2 key Button Click"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString(
			"Input Tag For 3 key Button Click"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString(
			"Input Tag For 4 key Button Click"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString(
			"Damage"));
	GameplayTags.Damage_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("MaxDamage"),
		FString(
			"MaxDamage"));
	/* Damage types */

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString(
			"Physical Damage"));

	GameplayTags.Damage_Physical_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical.Max"),
		FString(
			"Physical Damage"));

	GameplayTags.Damage_Magical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magical"),
		FString(
			"Magical Damage"));

	GameplayTags.Damage_Magical_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magical.Max"),
		FString(
			"Magical Damage"));

	GameplayTags.Damage_True = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.True"),
		FString(
			"True Damage"));

	GameplayTags.Damage_True_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.True.Max"),
		FString(
			"True Damage"));

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString(
			"Fire Damage"));

	GameplayTags.Damage_Fire_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire.Max"),
		FString(
			"Fire Damage"));

	GameplayTags.Damage_Blood = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Blood"),
		FString(
			"Blood Damage"));

	GameplayTags.Damage_Blood_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Blood.Max"),
		FString(
			"Blood Damage"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString(
			"Lightning Damage"));

	GameplayTags.Damage_Lightning_Max = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning.Max"),
		FString(
			"Lightning Damage"));

	/* Resistances
	 * 
	 */
	GameplayTags.Attributes_Secondary_Defence_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.Armor"),
		FString(
			"Reduces Physical Damage Taken, Increase block hit chance"));

	GameplayTags.Attributes_Secondary_Defence_MagicResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.MagicResist"),
		FString(
			"Reduces Magical Damage Taken"));

	GameplayTags.Attributes_Secondary_Defence_TrueResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.True"),
		FString(
			"always 0"));

	GameplayTags.Attributes_Secondary_Defence_FireResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.FireResist"),
		FString(
			"Reduces Fire Damage Taken"));

	GameplayTags.Attributes_Secondary_Defence_BloodResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.BloodResist"),
		FString(
			"Reduces Blood Damage Taken"));

	GameplayTags.Attributes_Secondary_Defence_LightningResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Defence.LightningResist"),
		FString(
			"Reduces Lightning Damage Taken"));

	/* Map Of Damage Types de resistances */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical,
	                                          GameplayTags.Attributes_Secondary_Defence_Armor);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Magical,
	                                          GameplayTags.Attributes_Secondary_Defence_MagicResist);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_True,
	                                          GameplayTags.Attributes_Secondary_Defence_TrueResist);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Blood,
	                                          GameplayTags.Attributes_Secondary_Defence_BloodResist);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning,
	                                          GameplayTags.Attributes_Secondary_Defence_LightningResist);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire,
	                                          GameplayTags.Attributes_Secondary_Defence_FireResist);

	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_Physical_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_Armor);
	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_Magical_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_MagicResist);
	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_True_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_TrueResist);
	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_Blood_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_BloodResist);
	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_Lightning_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_LightningResist);
	GameplayTags.MaxDamageTypesToResistances.Add(GameplayTags.Damage_Fire_Max,
	                                             GameplayTags.Attributes_Secondary_Defence_FireResist);

	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_Armor,
	                                           GameplayTags.Attributes_Secondary_Attack_ArmorPenetration);
	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_MagicResist,
	                                           GameplayTags.Attributes_Secondary_Attack_MagicPenetration);
	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_TrueResist,
											   GameplayTags.Attributes_Secondary_Attack_TruePenetration);
	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_BloodResist,
	                                           GameplayTags.Attributes_Secondary_Attack_ArmorPenetration);
	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_LightningResist,
	                                           GameplayTags.Attributes_Secondary_Attack_ArmorPenetration);
	GameplayTags.ResistancesToPenetrations.Add(GameplayTags.Attributes_Secondary_Defence_FireResist,
	                                           GameplayTags.Attributes_Secondary_Attack_MagicPenetration);


	/**Effects */


	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString(
			"Hit Reaction effect"));
}
