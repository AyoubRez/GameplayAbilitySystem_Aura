// Copy Right Shredder

#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


int32 AAuraCharacterBase::GetPlayerLevel()
{
	return 0;
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AAuraCharacterBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AAuraCharacterBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MultiCastHandleDeath();
}

void AAuraCharacterBase::MultiCastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();

	bDead = true;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon_Left) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName_L);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon_Right) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName_R);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Hand_Left))
	{
		return GetMesh()->GetSocketLocation(HandSocketName_L);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Hand_Right))
	{
		return GetMesh()->GetSocketLocation(HandSocketName_R);
	}
	return FVector();
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AAuraCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()))
	check(GameplayEffectClass)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffect = GetAbilitySystemComponent()->
		MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GameplayEffect.Data.Get(),
	                                                             GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())return;
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (AuraASC)
	{
		AuraASC->AddCharacterAbilities(StartupAbilities);
	}
}

void AAuraCharacterBase::Dissolve()
{
	int32 i = 0;
	for (auto DissolveMaterialInstance : DissolveMaterialInstances)
	{
		if (IsValid(DissolveMaterialInstance))
		{
			UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(
				DissolveMaterialInstance, this);
			GetMesh()->SetMaterial(i, DynamicMatInst);
			StartDissolveTimeLine(DynamicMatInst);
		}
		i++;
	}
	i = 0;
	for (auto WeaponDissolveMaterialInstance : WeaponDissolveMaterialInstances)
	{
		if (IsValid(WeaponDissolveMaterialInstance))
		{
			UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(
				WeaponDissolveMaterialInstance, this);
			Weapon->SetMaterial(i, DynamicMatInst);
			WeaponStartDissolveTimeLine(DynamicMatInst);
		}
		i++;
	}
}
