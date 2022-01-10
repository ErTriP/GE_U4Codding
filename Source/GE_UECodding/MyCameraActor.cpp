// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraActor.h"

#include "BasePawnPZ7.h"


AMyCameraActor::AMyCameraActor()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetBoxExtent(FVector(400,400,400));
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);

	bIsCaught = false;
	BlendTime = 0;
}
void AMyCameraActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(Cast<ABasePawnPZ7>(OtherActor)))
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		FViewTargetTransitionParams TransitionParams;
		TransitionParams.BlendTime = BlendTime;
		PC->SetViewTarget(this, TransitionParams);
		GetWorldTimerManager().ClearTimer(LoseTH);

		GetWorldTimerManager().SetTimer(CaughtTH, this, &AMyCameraActor::PlayerCaught, 0.001,false, 5.f );
		
		//PC->DisableInput(PC);
		//GetWorldTimerManager().SetTimer(TH, FTimerDelegate::CreateLambda([this] { EnableInput(GetWorld()->GetFirstPlayerController()); }), 0.0001, false, BlendTime);
	}
}

void AMyCameraActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IsValid(Cast<ABasePawnPZ7>(OtherActor)))
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		FViewTargetTransitionParams TransitionParams;
		TransitionParams.BlendTime = BlendTime;
		PC->SetViewTarget(PC->GetPawn(), TransitionParams);
		GetWorldTimerManager().ClearTimer(CaughtTH);
		

		if (bIsCaught)
		{
			GetWorldTimerManager().SetTimer(LoseTH, this, &AMyCameraActor::CameraLosePlayer, 0.001,false, 10.f );
		}
		//PC->DisableInput(PC);
		//GetWorldTimerManager().SetTimer(TH, FTimerDelegate::CreateLambda([this] { EnableInput(GetWorld()->GetFirstPlayerController()); }), 0.0001, false, BlendTime);
	}
}

void AMyCameraActor::PlayerCaught()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->GetPawn()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, CaughtMat);
	bIsCaught = true;
	
}

void AMyCameraActor::CameraLosePlayer()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->GetPawn()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, NormalMat);
	bIsCaught = false;
	
}


void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCameraActor::BoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMyCameraActor::BoxEndOverlap);
}
