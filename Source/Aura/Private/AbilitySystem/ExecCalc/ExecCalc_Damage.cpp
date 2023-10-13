// Copy Right Shredder


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResist);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TrueResist);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResist);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BloodResist);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResist);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TruePenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Arcane);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicResist, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, TrueResist, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResist, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BloodResist, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResist, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, TruePenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockHitChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MaxHealth, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Intelligence, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Dexterity, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Arcane, Source, false);

		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_MagicResist, MagicResistDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_TrueResist, TrueResistDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_FireResist, FireResistDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_BloodResist, BloodResistDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_LightningResist, LightningResistDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Attack_MagicPenetration, MagicPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Attack_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Attack_TruePenetration, TruePenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Defence_BlockHitChance, BlockHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Attack_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Attack_CriticalHitDamage, CriticalHitDamageDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Base_MaxHealth, MaxHealthDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Strength, StrengthDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Intelligence, IntelligenceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Dexterity, DexterityDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Arcane, ArcaneDef);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().TrueResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().BloodResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().TruePenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MaxHealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(DamageStatics().IntelligenceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneDef);
	RelevantAttributesToCapture.Add(DamageStatics().DexterityDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle GameplayEffectContextHandle = Spec.GetContext();

	// gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	/* Crit Chance*/

	float SourceCriticalChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,
	                                                           EvaluationParameters,
	                                                           SourceCriticalChance);
	SourceCriticalChance = FMath::Max<float>(SourceCriticalChance, 0.f);

	float TargetCriticalResistance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,
	                                                           EvaluationParameters,
	                                                           TargetCriticalResistance);
	TargetCriticalResistance = FMath::Max<float>(TargetCriticalResistance, 0.f);


	const bool bCritical = FMath::RandRange(0, 100) < SourceCriticalChance - TargetCriticalResistance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(GameplayEffectContextHandle, bCritical);

	// Get Damage and Max Damage Set By caller Magnitude;
	float Damage = 0.f;
	float MaxDamage = 0.f;
	for (auto& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		const FGameplayTag PenetrationTag = FAuraGameplayTags::Get().ResistancesToPenetrations[ResistanceTag];
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),
		      TEXT("Tags to Res capture Defs doesn't contain the specified resistance tag [%s]"),
		      *ResistanceTag.ToString())

		const FGameplayEffectAttributeCaptureDefinition ResistanceCaptureDef = AuraDamageStatics().TagsToCaptureDefs[
			ResistanceTag];

		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),
		      TEXT("Tags to Pen capture Defs doesn't contain the specified Penetration tag [%s]"),
		      *PenetrationTag.ToString())

		const FGameplayEffectAttributeCaptureDefinition PenetrationCaptureDef = AuraDamageStatics().TagsToCaptureDefs[
			PenetrationTag];

		float TargetResistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceCaptureDef, EvaluationParameters,
		                                                           TargetResistance);
		TargetResistance = FMath::Max<float>(TargetResistance, 0.f);

		float SourcePenetration = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PenetrationCaptureDef,
		                                                           EvaluationParameters,
		                                                           SourcePenetration);
		SourcePenetration = FMath::Max<float>(SourcePenetration, 0.f);

		float EffectiveResistance = TargetResistance - SourcePenetration * 0.7;
		EffectiveResistance = FMath::Clamp(EffectiveResistance, 0.f, 100.f);
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageType);
		DamageTypeValue *= (100 - EffectiveResistance * 0.9) / 100.f;
		Damage += DamageTypeValue;
	}
	for (auto& Pair : FAuraGameplayTags::Get().MaxDamageTypesToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		const FGameplayTag PenetrationTag = FAuraGameplayTags::Get().ResistancesToPenetrations[ResistanceTag];
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),
			  TEXT("Tags to Res capture Defs doesn't contain the specified resistance tag [%s]"),
			  *ResistanceTag.ToString())

		const FGameplayEffectAttributeCaptureDefinition ResistanceCaptureDef = AuraDamageStatics().TagsToCaptureDefs[
			ResistanceTag];

		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),
			  TEXT("Tags to Pen capture Defs doesn't contain the specified Penetration tag [%s]"),
			  *PenetrationTag.ToString())

		const FGameplayEffectAttributeCaptureDefinition PenetrationCaptureDef = AuraDamageStatics().TagsToCaptureDefs[
			PenetrationTag];

		float TargetResistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceCaptureDef, EvaluationParameters,
																   TargetResistance);
		TargetResistance = FMath::Max<float>(TargetResistance, 0.f);

		float SourcePenetration = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PenetrationCaptureDef,
																   EvaluationParameters,
																   SourcePenetration);
		SourcePenetration = FMath::Max<float>(SourcePenetration, 0.f);

		float EffectiveResistance = TargetResistance - SourcePenetration * 0.7;
		EffectiveResistance = FMath::Clamp(EffectiveResistance, 0.f, 100.f);
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageType);
		DamageTypeValue *= (100 - EffectiveResistance * 0.9) / 100.f;
		MaxDamage += DamageTypeValue;
	}
	float FinalDamage = bCritical ? 2.f * MaxDamage : FMath::RandRange(Damage, MaxDamage);
	if (bCritical)
	{
		UAuraAbilitySystemLibrary::SetPercentageToMax(GameplayEffectContextHandle, 1.f);
		float SourceCriticalDamage = 0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,
		                                                           EvaluationParameters,
		                                                           SourceCriticalDamage);
		SourceCriticalDamage = FMath::Max<float>(SourceCriticalDamage, 0.f);

		FinalDamage += SourceCriticalDamage;
	}
	else
	{
		float Percentage = Damage < MaxDamage
			                   ? FMath::Lerp(0.3, 1, (FinalDamage - Damage) / (MaxDamage - Damage))
			                   : 0.3f;
		UAuraAbilitySystemLibrary::SetPercentageToMax(GameplayEffectContextHandle, Percentage);
	}
	/* Block Hit Chance */
	// capture block change on Target , and determine if there was a successful Block
	float TargetBlockHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockHitChanceDef, EvaluationParameters,
	                                                           TargetBlockHitChance);
	TargetBlockHitChance = FMath::Max<float>(TargetBlockHitChance, 0.f);
	const bool bBlocked = FMath::RandRange(0, 100) < TargetBlockHitChance;
	UAuraAbilitySystemLibrary::SetIsBlockedHit(GameplayEffectContextHandle, bBlocked);
	// if Block nullify damage
	FinalDamage = bBlocked ? 0.f : FinalDamage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, FinalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
