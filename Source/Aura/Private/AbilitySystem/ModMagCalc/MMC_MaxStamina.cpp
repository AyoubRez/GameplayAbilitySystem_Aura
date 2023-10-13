// Copy Right Shredder


#include "AbilitySystem/ModMagCalc/MMC_MaxStamina.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxStamina::UMMC_MaxStamina()
{
	MindDef.AttributeToCapture = UAuraAttributeSet::GetMindAttribute();
	MindDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MindDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(MindDef);
}

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Mind = 0;
	GetCapturedAttributeMagnitude(MindDef, Spec, EvaluationParameters, Mind);
	Mind = FMath::Max<float>(Mind, 0.f);


	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 55.f + 2.f * (Mind + 10) + 5.f * PlayerLevel;
}
