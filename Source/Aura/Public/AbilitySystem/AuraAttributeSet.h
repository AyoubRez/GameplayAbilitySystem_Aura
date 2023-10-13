// Copy Right Shredder

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties()
	{
	}

	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> SourceController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter = nullptr;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> TargetController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter = nullptr;
};

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;
/**
 * 
 */
UCLASS

()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	                                 const FGameplayAttributeData& MaxAttribute,
	                                 float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/** Attributes declaration */
	/** Vital **/
	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Shield)

	UPROPERTY(BlueprintReadOnly, Category="Vital Attributes", ReplicatedUsing=OnRep_MaxShield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxShield)


	/** Primary Attributes **/

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Strength)
	FGameplayAttributeData Strength; // physical Damage increase
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Intelligence)
	FGameplayAttributeData Intelligence; // + Max Mana + Mana Regen + Magic damage + magic resist
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Resilience)
	FGameplayAttributeData Resilience; // + Armor + Tenacity
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Vigor)
	FGameplayAttributeData Vigor; // + Max Health + Health regen +heal power
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Dexterity)
	FGameplayAttributeData Dexterity; // + physical damage + armor penetration  
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Dexterity)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Arcane)
	FGameplayAttributeData Arcane; // +Magic Damage + magicPenetration 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Arcane)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Mind)
	FGameplayAttributeData Mind; // +Max Stamina + Stamina regen
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mind)

	UPROPERTY(BlueprintReadOnly, Category="Primary Attributes", ReplicatedUsing=OnRep_Faith)
	FGameplayAttributeData Faith; // +Crit chance  + Crit damage 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Faith)

	/* Secondary Attributes */

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor; // reduce Physical Damage taken + blocking 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_MagicResist)
	FGameplayAttributeData MagicResist; // reduce Magical Damage taken 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MagicResist)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_TrueResist)
	FGameplayAttributeData TrueResist; // reduce True Damage taken + blocking 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, TrueResist)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_FireResist)
	FGameplayAttributeData FireResist; // reduce Fire Damage taken 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResist)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_BloodResist)
	FGameplayAttributeData BloodResist; // reduce Blood Damage taken 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BloodResist)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_LightningResist)
	FGameplayAttributeData LightningResist; // reduce Lightning Damage taken 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningResist)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_Tenacity)
	FGameplayAttributeData Tenacity; // reduce slow effect and duration + CCs durations + Crit Resistance 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Tenacity)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration; // ignore percentage of armor + crit hit chance + crit hit damage
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_MagicPenetration)
	FGameplayAttributeData MagicPenetration; // ignore percentage of magic resist + crit hit chance + crit hit damage
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MagicPenetration)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_TruePenetration)
	FGameplayAttributeData TruePenetration; // ignore percentage of magic resist + crit hit chance + crit hit damage
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, TruePenetration)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_LifeSteal)
	FGameplayAttributeData LifeSteal; // percentage of damage is healed  
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LifeSteal)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_HealPower)
	FGameplayAttributeData HealPower; // percentage power of healing from heal spells and potions
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealPower)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_BlockHitChance)
	FGameplayAttributeData BlockHitChance; // cut incoming damage to half
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockHitChance)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance; // chance to double damage + critical hit bonus
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage; // Bonus critical hit
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance; // reduce crit hit chance of incoming damage
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen; // amount of Health regen after every 5 seconds
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegen)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen; // amount of mana regen after every 5 seconds 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegen)

	UPROPERTY(BlueprintReadOnly, Category="Secondary Attributes", ReplicatedUsing=OnRep_StaminaRegen)
	FGameplayAttributeData StaminaRegen;
	// amount of Stamina regen after every 2 seconds if not used for a short period of time
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaminaRegen)


	/*
	 *Meta Attributes 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Meta Attribute")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);
	/************/


	/** REP NOTIFIES  */
	/*  VITAL */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& OldShield) const;

	UFUNCTION()
	void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const;

	/* PRIMARY */

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UFUNCTION()
	void OnRep_Arcane(const FGameplayAttributeData& OldArcane) const;

	UFUNCTION()
	void OnRep_Mind(const FGameplayAttributeData& OldMind) const;

	UFUNCTION()
	void OnRep_Faith(const FGameplayAttributeData& OldFaith) const;

	/* SECONDARY  */

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist) const;

	UFUNCTION()
	void OnRep_TrueResist(const FGameplayAttributeData& OldTrueResist) const;

	UFUNCTION()
	void OnRep_FireResist(const FGameplayAttributeData& OldFireResist) const;

	UFUNCTION()
	void OnRep_BloodResist(const FGameplayAttributeData& OldBloodResist) const;

	UFUNCTION()
	void OnRep_LightningResist(const FGameplayAttributeData& OldLightningResist) const;

	UFUNCTION()
	void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const;

	UFUNCTION()
	void OnRep_TruePenetration(const FGameplayAttributeData& OldTruePenetration) const;

	UFUNCTION()
	void OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const;

	UFUNCTION()
	void OnRep_HealPower(const FGameplayAttributeData& OldHealPower) const;

	UFUNCTION()
	void OnRep_BlockHitChance(const FGameplayAttributeData& OldBlockHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;

	UFUNCTION()
	void OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit,
	                      float PercentageToMax) const;
};
