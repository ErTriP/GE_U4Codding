#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "MyCameraActor.generated.h"


UCLASS()
class GE_UECODDING_API AMyCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	FTimerHandle CaughtTH;
	FTimerHandle LoseTH;
	
	virtual void BeginPlay() override;
	
public:
	AMyCameraActor();

	UPROPERTY(EditAnywhere)
	float BlendTime;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* CaughtMat;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* NormalMat;

	bool bIsCaught;
	
	
	UFUNCTION()
		void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex);
	
	void PlayerCaught();
	void CameraLosePlayer();
};
