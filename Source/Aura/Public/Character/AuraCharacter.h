// Copy Right Shredder

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(BlueprintReadOnly)
	AAuraPlayerController* PlayerController;

private:
	virtual void InitAbilityActorInfo() override;
};
