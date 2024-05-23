// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-UnrealEngine-5

#pragma once

#include <ShlObj.h>
#include <strsafe.h>
#include "Kinect.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KinectBodyActor.generated.h"


UENUM(BlueprintType, Category = "Kinect Joint Enum")
enum class EKinectJoint : uint8 {

	SpineBase		UMETA(DisplayName = "SpineBase"),
	SpineMid		UMETA(DisplayName = "SpineMid"),
	Neck			UMETA(DisplayName = "Neck"),
	Head			UMETA(DisplayName = "Head"),
	ShoulderLeft	UMETA(DisplayName = "ShoulderLeft"),
	ElbowLeft		UMETA(DisplayName = "ElbowLeft"),
	WristLeft		UMETA(DisplayName = "WristLeft"),
	HandLeft		UMETA(DisplayName = "HandLeft"),
	ShoulderRight	UMETA(DisplayName = "ShoulderRight"),
	ElbowRight		UMETA(DisplayName = "ElbowRight"),
	WristRight		UMETA(DisplayName = "WristRight"),
	HandRight		UMETA(DisplayName = "HandRight"),
	HipLeft			UMETA(DisplayName = "HipLeft"),
	KneeLeft		UMETA(DisplayName = "KneeLeft"),
	AnkleLeft		UMETA(DisplayName = "AnkleLeft"),
	FootLeft		UMETA(DisplayName = "FootLeft"),
	HipRight		UMETA(DisplayName = "HipRight"),
	KneeRight		UMETA(DisplayName = "KneeRight"),
	AnkleRight		UMETA(DisplayName = "AnkleRight"),
	FootRight		UMETA(DisplayName = "FootRight"),
	SpineShoulder	UMETA(DisplayName = "SpineShoulder"),
	HandTipLeft		UMETA(DisplayName = "HandTipLeft"),
	ThumbLeft		UMETA(DisplayName = "ThumbLeft"),
	HandTipRight	UMETA(DisplayName = "HandTipRight"),
	ThumbRight		UMETA(DisplayName = "ThumbRight")
};

USTRUCT(BlueprintType)
struct FKinectJointTransform {

	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FVector Location;


	UPROPERTY(BlueprintReadOnly)
	FRotator Orientation;

};

USTRUCT(BlueprintType)
struct FKinectCurHandStates {

	GENERATED_BODY()

	// Left Hand : 7
	// Right Hand : 11

	// HandState { 0 : UnKnown , 1 : Not Tracked , 2 : Open , 3 : Closed , 4 : Lasso }

	UPROPERTY(BlueprintReadWrite)
	int32 LHandState = HandState_Unknown;

	UPROPERTY(BlueprintReadWrite)
	int32 RHandState = HandState_Unknown;

	UPROPERTY(BlueprintReadWrite)
	FVector LHandPoint = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	FVector RHandPoint = FVector::ZeroVector;

};


UCLASS()
class SENSORGAME_API AKinectBodyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKinectBodyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	FString JointName[25] = { "SpineBase", "SpineMid", "Neck", "Head", "ShoulderLeft", "ElbowLeft",
		"WristLeft", "HandLeft", "ShoulderRight", "ElbowRight", "WristRight", "HandRight", "HipLeft",
		"KneeLeft", "AnkleLeft", "FootLeft", "HipRight", "KneeRight", "AnkleRight", "FootRight",
		"SpineShoulder", "HandTipLeft", "ThumbLeft", "HandTipRight", "ThumbRight" };



	IKinectSensor* i_KinectSensor;
	ICoordinateMapper* i_CoordinateMapper;
	IBodyFrameReader* i_BodyFrameReader;


	void initialize();


	// Joints
	Joint joints[JointType_Count];
	JointOrientation joint_orient[JointType_Count];

	// HandState var
	HandState leftHandState = HandState_Unknown;
	HandState rightHandState = HandState_Unknown;


	void UpdateBodyPoints(int index, CameraSpacePoint jointPosition, Vector4 jointOrientation);


	//
	FKinectCurHandStates myHandState;

	//
	UFUNCTION(BlueprintCallable, Category = "Hand State Point")
	FKinectCurHandStates GetMyHand();


	//
	UPROPERTY(BlueprintReadWrite)
	TArray<FKinectJointTransform> ArrJoint;

	//
	UFUNCTION(BlueprintPure)
	TArray<FKinectJointTransform> GetJoints();

};
