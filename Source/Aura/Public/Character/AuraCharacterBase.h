// Copy Right Shredder

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)

class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void MultiCastHandleDeath();

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;
	/* Combat interface */
	virtual int32 GetPlayerLevel() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	virtual void Die() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	/* End Combat interface */

	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage> AttackMontages;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName_L;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName_R;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	FName HandSocketName_L;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName HandSocketName_R;

	bool bDead = false;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;


	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();


	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeLine(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void WeaponStartDissolveTimeLine(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UMaterialInstance>> DissolveMaterialInstances;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UMaterialInstance>> WeaponDissolveMaterialInstances;

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UAnimMontage> DeathMontage;
};
