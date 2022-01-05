// Copyright Epic Games, Inc. All Rights Reserved.

#include "GE_UECoddingCharacter.h"

#include "GameFramework/Actor.h"

#include "BaseFruitC.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "InventoryItemC.h"
#include "InventorySystemC.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "CharacterFollowActorC.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AGE_UECoddingCharacter

AGE_UECoddingCharacter::AGE_UECoddingCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	ArmActorToDestroy = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmToActor"));
	ArmActorToDestroy->SetupAttachment(RootComponent);
	ArmActorToDestroy->TargetArmLength = 100.0f; // The camera follows at this distance behind the character	
	ArmActorToDestroy->bUsePawnControlRotation = true;
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InventoryComponent = CreateDefaultSubobject<UInventorySystemC>(TEXT("Inventory"));

	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	Stamina = 100;

	OnPlayerUseHeal.BindUFunction(this, "LongHealing");

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGE_UECoddingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGE_UECoddingCharacter::Fire);
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AGE_UECoddingCharacter::Reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGE_UECoddingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGE_UECoddingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGE_UECoddingCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGE_UECoddingCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGE_UECoddingCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGE_UECoddingCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AGE_UECoddingCharacter::OnResetVR);
}

void AGE_UECoddingCharacter::Damage(int32 DamageAmount)
{
	CurrentHealth -= DamageAmount;
	OnPlayerTakeDamage.Broadcast(DamageAmount);
	if (CurrentHealth <= 0)
	{
		OnPlayerDestroy.Broadcast();
	}
}

void AGE_UECoddingCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnChildActors();
	OnPlayerDestroy.AddUFunction(this, "DestroyActor");
	
}

void AGE_UECoddingCharacter::DestroyActor()
{
	Destroy();
}

void AGE_UECoddingCharacter::UseItem(UInventoryItemC* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); //BP
	}
}

void AGE_UECoddingCharacter::PickItem(UInventoryItemC* Item)
{
	InventoryComponent->AddItem(Item);
}

void AGE_UECoddingCharacter::DropItem(UInventoryItemC* Item)
{
	InventoryComponent->RemoveItem(Item);
	const FTransform SpawnLocAndRotation(FVector(GetActorLocation()+GetActorForwardVector()*300));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, SpawnLocAndRotation.ToString());
	if (GetWorld())
	{
		ABaseFruitC* BaseFruit = GetWorld()->SpawnActorDeferred<ABaseFruitC>(ABaseFruitC::StaticClass(), SpawnLocAndRotation );
		BaseFruit->SpawnConstract(Item);
		BaseFruit->FinishSpawning(SpawnLocAndRotation);
	} 
	
}

void AGE_UECoddingCharacter::SpawnChildActors()
{
	if (GetWorld())
	{
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		BaseWeapon = GetWorld()->SpawnActor<ABaseWeaponC>(Location, Rotation, SpawnInfo);

		FName socket = TEXT("GunHandle");

		USkeletalMeshComponent* mesh = GetMesh();
		
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

		BaseWeapon->AttachToComponent(mesh, rules, socket);
	}

	if (GetWorld())
	{
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		FollowActor = GetWorld()->SpawnActor<ACharacterFollowActorC>(Location, Rotation, SpawnInfo);
		
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

		FollowActor->AttachToComponent(ArmActorToDestroy, rules);
	} 
}

void AGE_UECoddingCharacter::OnResetVR()
{
	// If GE_UECodding is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in GE_UECodding.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGE_UECoddingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AGE_UECoddingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AGE_UECoddingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGE_UECoddingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGE_UECoddingCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGE_UECoddingCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AGE_UECoddingCharacter::Reload()
{
	BaseWeapon->Reload_Implementation();
}

void AGE_UECoddingCharacter::Fire()
{
	BaseWeapon->Fire();
}

void AGE_UECoddingCharacter::Healing(int32 HealPerSecond)
{
	HealingRate--;
	if (HealingRate < 0)
	{
		GetWorldTimerManager().ClearTimer(HealTimer);
	}else
	{
		CurrentHealth += HealPerSecond;
		if (CurrentHealth >= MaxHealth)
		{
			CurrentHealth = MaxHealth;
			GetWorldTimerManager().ClearTimer(HealTimer);
		}
	}
	
}

void AGE_UECoddingCharacter::Damaging(int32 DamagePerSecond)
{
	HealingRate--;
	if (HealingRate < 0)
	{
		GetWorldTimerManager().ClearTimer(HealTimer);
	}else
	{
		Damage(DamagePerSecond);
	}
	
}

void AGE_UECoddingCharacter::LongHealing(int32 HealPerSecond, int32 Rate)
{
	if(!HealTimer.IsValid())
	{
		HealingRate = Rate;
		if (HealPerSecond > 0)
		{
			HealTimerDelegate.BindUFunction(this, "Healing", HealPerSecond);
			GetWorldTimerManager().SetTimer(HealTimer, HealTimerDelegate, 1.f, true);
		}else
		{
			HealTimerDelegate.BindUFunction(this, "Damaging", HealPerSecond*-1);
			GetWorldTimerManager().SetTimer(HealTimer, HealTimerDelegate, 1.f, true);
		}
	}
}

