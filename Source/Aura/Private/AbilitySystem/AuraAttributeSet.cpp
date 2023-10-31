// Copy Right Shredder


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	/* Primary **/
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Arcane, GetArcaneAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Mind, GetMindAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Faith, GetFaithAttribute);
	/* Secondary  **/

	/*Base*/
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Base_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Base_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Base_MaxShield, GetMaxShieldAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Base_MaxStamina, GetMaxStaminaAttribute);
	/*Regen*/
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Regen_HealPower, GetHealPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Regen_HealthRegen, GetHealthRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Regen_LifeSteal, GetLifeStealAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Regen_ManaRegen, GetManaRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Regen_StaminaRegen, GetStaminaAttribute);
	/*Defence*/
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_Tenacity, GetTenacityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_MagicResist, GetMagicResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_TrueResist, GetTrueResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_FireResist, GetFireResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_BloodResist, GetBloodResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_LightningResist, GetLightningResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_BlockHitChance, GetBlockHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Defence_CriticalHitResistance,
	                     GetCriticalHitResistanceAttribute);
	/*Attack*/
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Attack_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Attack_MagicPenetration, GetMagicPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Attack_TruePenetration, GetTruePenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Attack_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Attack_CriticalHitDamage, GetCriticalHitDamageAttribute);
}

void UAuraAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
                                                    const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
                                                    const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f)
			                 ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
			                 : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	/**
	 * Add replicated attributes here as done bellow
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);

	/* Primary */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Arcane, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mind, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Faith, COND_None, REPNOTIFY_Always);

	/* Secondary */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MagicResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, TrueResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BloodResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LightningResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MagicPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, TruePenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaminaRegen, COND_None, REPNOTIFY_Always);
}


void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
	if (Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxShield());
	}
	// if (Attribute == GetMaxHealthAttribute())
	// {
	// 	AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	// }
	// if (Attribute == GetMaxManaAttribute())
	// {
	// 	AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	// }
	// if (Attribute == GetMaxStaminaAttribute())
	// {
	// 	AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	// }
	// if (Attribute == GetMaxShieldAttribute())
	// {
	// 	AdjustAttributeForMaxChange(Shield, MaxShield, NewValue, GetShieldAttribute());
	// }
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(FMath::Clamp(GetShield(), 0.f, GetMaxShield()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
				{
					CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			const bool bBlocked = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
			const bool bCritical = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
			const float Percentage = UAuraAbilitySystemLibrary::GetPercentageToMax(Props.EffectContextHandle);
			ShowFloatingText(Props, LocalIncomingDamage, bBlocked, bCritical, Percentage);
		}
		else
		{
			if (const bool bBlocked = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle))
			{
				const bool bCritical = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
				const float Percentage = UAuraAbilitySystemLibrary::GetPercentageToMax(Props.EffectContextHandle);
				ShowFloatingText(Props, LocalIncomingDamage, bBlocked, bCritical, Percentage);
			}
		}
	}
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit,
                                         bool bCriticalHit,
                                         float PercentageToMax) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(
			Props.SourceCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, PercentageToMax, bBlockedHit, bCriticalHit);
			return;
		}
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(
			Props.TargetCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, PercentageToMax, bBlockedHit, bCriticalHit);
		}
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	/** Source = causer of effect , Target = Target of effect (Owner of this AS)*/

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->
		AvatarActor.
		IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}


void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Stamina, OldStamina);
}

void UAuraAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxStamina, OldMaxStamina);
}

void UAuraAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Shield, OldShield);
}

void UAuraAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxShield, OldMaxShield);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Dexterity, OldDexterity);
}

void UAuraAttributeSet::OnRep_Arcane(const FGameplayAttributeData& OldArcane) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Arcane, OldArcane);
}

void UAuraAttributeSet::OnRep_Mind(const FGameplayAttributeData& OldMind) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mind, OldMind);
}

void UAuraAttributeSet::OnRep_Faith(const FGameplayAttributeData& OldFaith) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Faith, OldFaith);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_MagicResist(const FGameplayAttributeData& OldMagicResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MagicResist, OldMagicResist);
}

void UAuraAttributeSet::OnRep_TrueResist(const FGameplayAttributeData& OldTrueResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, TrueResist, OldTrueResist);
}

void UAuraAttributeSet::OnRep_FireResist(const FGameplayAttributeData& OldFireResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResist, OldFireResist);
}

void UAuraAttributeSet::OnRep_BloodResist(const FGameplayAttributeData& OldBloodResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BloodResist, OldBloodResist);
}

void UAuraAttributeSet::OnRep_LightningResist(const FGameplayAttributeData& OldLightningResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningResist, OldLightningResist);
}

void UAuraAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Tenacity, OldTenacity);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MagicPenetration, OldMagicPenetration);
}

void UAuraAttributeSet::OnRep_TruePenetration(const FGameplayAttributeData& OldTruePenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, TruePenetration, OldTruePenetration);
}

void UAuraAttributeSet::OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LifeSteal, OldLifeSteal);
}

void UAuraAttributeSet::OnRep_HealPower(const FGameplayAttributeData& OldHealPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealPower, OldHealPower);
}

void UAuraAttributeSet::OnRep_BlockHitChance(const FGameplayAttributeData& OldBlockHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockHitChance, OldBlockHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegen, OldHealthRegen);
}

void UAuraAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegen, OldManaRegen);
}

void UAuraAttributeSet::OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaminaRegen, OldStaminaRegen);
}
