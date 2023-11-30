// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarioCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AMarioCharacter

AMarioCharacter::AMarioCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(SMALL_MARIO_HEIGHT);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 4.0f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->JumpZVelocity = 1500.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = MAXSPEED_WALK;
	GetCharacterMovement()->MaxAcceleration = 3000.f;
	//GetCharacterMovement()->BrakingDecelerationWalking = 1024.f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	IsSit = false;
	Level = MARIO_LEVEL_SMALL;
}

//////////////////////////////////////////////////////////////////////////
// Animation

UPaperFlipbook* AMarioCharacter::getAniSmallMario()
{
	const FVector PlayerVelocity = GetVelocity();
	const FVector PlayerAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	UPaperFlipbook* animation = nullptr;

	if (IsSit) {
		animation = SMALLSitAnimation;
	}
	else {
		if (GetCharacterMovement()->IsFalling()) {
			if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK + 100.f) {
				animation = SMALL_JumpRunAnimation;
			}
			else animation = SMALL_JumpWalkAnimation;

		}
		else {
			if (PlayerVelocity.X * PlayerAcceleration.X >= 0) {
				if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK + 100.f)
					animation = SMALL_RunningAnimation;
				else animation = FMath::Abs(PlayerVelocity.X) > 0.f ? SMALL_WalkingAnimation : SMALL_IdleAnimation;
			}
			else animation = SMALL_TurnAnimation;
		}
	}
	return animation;
}

UPaperFlipbook* AMarioCharacter::getAniBigMario()
{
	const FVector PlayerVelocity = GetVelocity();
	const FVector PlayerAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	UPaperFlipbook* animation = nullptr;

	if (IsSit) {
		animation = BIG_SitAnimation;
	}
	else {
		if (GetCharacterMovement()->IsFalling()) {
			if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK + 100.f) {
				animation = BIG_JumpRunAnimation;
			}
			else animation = BIG_JumpWalkAnimation;

		}
		else {
			if (PlayerVelocity.X * PlayerAcceleration.X >= 0) {
				if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK + 100.f)
					animation = BIG_RunningAnimation;
				else animation = FMath::Abs(PlayerVelocity.X) > 0.f ? BIG_WalkingAnimation : BIG_IdleAnimation;
			}
			else animation = BIG_TurnAnimation;
		}
	}
	return animation;
}

UPaperFlipbook* AMarioCharacter::getAniRaccoonMario()
{
	const FVector PlayerVelocity = GetVelocity();
	const FVector PlayerAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	UPaperFlipbook* animation = nullptr;

	if (IsSit) {
		animation = RACCOON_SitAnimation;
	}
	else {
		if (GetCharacterMovement()->IsFalling()) {
			if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK) {
				animation = RACCOON_JumpRunAnimation;
			}
			else animation = RACCOON_JumpWalkAnimation;

		}
		else {
			if (PlayerVelocity.X * PlayerAcceleration.X >= 0) {
				if (FMath::Abs(PlayerVelocity.X) > MAXSPEED_WALK)
					animation = RACCOON_RunningAnimation;
				else animation = FMath::Abs(PlayerVelocity.X) > 0.f ? RACCOON_WalkingAnimation : RACCOON_IdleAnimation;
			}
			else animation = RACCOON_TurnAnimation;
		}
	}
	return animation;
}

void AMarioCharacter::UpdateAnimation()
{
	UPaperFlipbook* animation = nullptr;
	if (isDead) {
		animation = SMALL_DIEAnimation;
	}
	else if (Level == MARIO_LEVEL_SMALL) {
		animation = getAniSmallMario();
	}
	else if (Level == MARIO_LEVEL_BIG) {
		animation = getAniBigMario();
	}
	else {
		animation = getAniRaccoonMario();
	}

	if( GetSprite()->GetFlipbook() != animation)
	{
		GetSprite()->SetFlipbook(animation);
	}
}

void AMarioCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	
}


//////////////////////////////////////////////////////////////////////////
// Input

void AMarioCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMarioCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMarioCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMarioCharacter::TouchStopped);

	// sit
	PlayerInputComponent->BindAction("Sit", IE_Pressed, this, &AMarioCharacter::Sit);
	PlayerInputComponent->BindAction("Sit", IE_Released, this, &AMarioCharacter::ReleaseSit);

	// Accelerate
	PlayerInputComponent->BindAction("Accelerate", IE_Pressed, this, &AMarioCharacter::Accelerate);
	PlayerInputComponent->BindAction("Accelerate", IE_Released, this, &AMarioCharacter::releaseAccelerate);
}

void AMarioCharacter::MoveRight(float Value)
{
	// Apply the input to the character motion
	if(!IsSit)
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AMarioCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	if(!IsSit)
		Jump();
}

void AMarioCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	if (!IsSit)
		StopJumping();
}

void AMarioCharacter::Sit()
{
	GetCharacterMovement()->StopMovementImmediately();
	IsSit = true;
}

void AMarioCharacter::ReleaseSit()
{
	IsSit = false;
}

void AMarioCharacter::Accelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = MAXSPEED_RUN;
}

void AMarioCharacter::releaseAccelerate()
{
	GetCharacterMovement()->MaxWalkSpeed = MAXSPEED_WALK;
}

void AMarioCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

// LEVEL
void AMarioCharacter::setLevel(int level)
{
	if (level < MAX_level && level != 0) {
		this->Level = level;
		if (this->Level > MARIO_LEVEL_SMALL) {
			GetCapsuleComponent()->SetCapsuleHalfHeight(BIG_MARIO_HEIGHT	);
			GetCapsuleComponent()->SetCapsuleRadius(40.0f);
		}
	}
}

void AMarioCharacter::CauseDamage()
{
	GetCharacterMovement()->AddImpulse(FVector(0.f,0.f,500.f), true);
}

void AMarioCharacter::TakeDamage(int damge)
{
	this->Level -= damge;
	if (this->Level <= 0) {
		Dead();
	}
}

void AMarioCharacter::Dead()
{
	this->isDead = true;

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->AddImpulse(FVector(0.f, 0.f, 1000.f), true);
	GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("NoCollision")));
}
