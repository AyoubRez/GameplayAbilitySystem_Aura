// Copy Right Shredder

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


/* Forward Declarations */

class UDamageTextComponent;
class USplineComponent;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;
class IEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**************************/
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float Damage, ACharacter* TargetCharacter, float Percentage, bool bBlockedHit,
	                      bool bCriticalHit);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Cursor")
	UUserWidget* Default_Cursor;
	UPROPERTY(EditAnywhere, Category="Cursor")
	UUserWidget* Target_Cursor;


	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	FHitResult CursorHit;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category="Movement")
	void CreateSplineAndMove(const FVector& TargetLocation,float Radius);

	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);


	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	FVector CashedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;

	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly, Category="Widget|Damage")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
