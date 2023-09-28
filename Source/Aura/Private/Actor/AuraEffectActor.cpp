// Copy Right Shredder


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO : Change this to apply GPE
	if (IAbilitySystemInterface* ASC = Cast<IAbilitySystemInterface>(Other))
	{
		const UAuraAttributeSet* Attributes = Cast<UAuraAttributeSet>(
			ASC->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* AuraAttributes = const_cast<UAuraAttributeSet*>(Attributes);
		AuraAttributes->SetHealth(AuraAttributes->GetHealth() + 100.f);
		AuraAttributes->SetMana(AuraAttributes->GetMana() + 50.f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}
