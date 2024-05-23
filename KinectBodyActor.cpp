// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-UnrealEngine-5

#include "KinectBodyActor.h"

// Sets default values
AKinectBodyActor::AKinectBodyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKinectBodyActor::BeginPlay()
{
	Super::BeginPlay();

	
	// Set initial Array size
	ArrJoint.SetNum(_countof(joints));
	
}

// Called every frame
void AKinectBodyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	initialize();


	if (!i_BodyFrameReader) {
		//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Body Frame Reader Failed"));
		return;
	}


	IBodyFrame* i_BodyFrame = NULL;

	IBody* i_Bodies[BODY_COUNT] = { 0, };

	HRESULT hr = i_BodyFrameReader->AcquireLatestFrame(&i_BodyFrame);

	if (FAILED(hr)) {
		//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Acquire Latest Frame Failed"));
	}

	if (SUCCEEDED(hr)) {
		hr = i_BodyFrame->GetAndRefreshBodyData(_countof(i_Bodies), i_Bodies);
	}

	if (SUCCEEDED(hr)) {

		for (int i = 0; i < _countof(i_Bodies); i++) {

			IBody* i_Body = i_Bodies[i];

			if (pBody) {

				BOOLEAN b_Tracked = false;

				hr = i_Body->get_IsTracked(&b_Tracked);



				if (SUCCEEDED(hr) && b_Tracked) {

					//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Body Tracked"));

					//pBody->get_HandLeftConfidence
					i_Body->get_HandLeftState(&leftHandState);
					i_Body->get_HandRightState(&rightHandState);

					hr = i_Body->GetJoints(_countof(joints), joints);
					// joint struct -> JointType : JointType, CameraSpacePoint : Position, TrackingState : TrackingState


					if (SUCCEEDED(hr)) {

						hr = i_Body->GetJointOrientations(_countof(joints), joint_orient);
						// joint orientation -> JointType : JointType, Vector4 Orientation

						if (SUCCEEDED(hr)) {


							for (int j = 0; j < _countof(joints); ++j) {

								UpdateBodyPoints(j, joints[j].Position, joint_orient[j].Orientation);


								// left hand update
								if (j == 7) {
									myHandState.LHandState = leftHandState;

									myHandState.LHandPoint = FVector(joints[j].Position.X, joints[j].Position.Y, joints[j].Position.Z);
								}
								// right hand update
								if (j == 11) {
									myHandState.RHandState = rightHandState;
									myHandState.RHandPoint = FVector(joints[j].Position.X, joints[j].Position.Y, joints[j].Position.Z);
								}


							}

							//UpdateFixedBodyRotation();

						}

					}

				}

			}

		}

	}

}

void AKinectBodyActor::initialize(){

	//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Initialize"));

	HRESULT hr;
	hr = GetDefaultKinectSensor(&i_KinectSensor);

	if (FAILED(hr)) {
		//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Get Kinect Sensor Failed"));
		return;
	}

	if (i_KinectSensor) {

		IBodyFrameSource* i_BodyFrameSource = NULL;

		hr = i_KinectSensor->Open();

		if (SUCCEEDED(hr)) {

			//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Kinect Sensor Opened"));

			hr = i_KinectSensor->get_CoordinateMapper(&i_CoordinateMapper);
		}

		if (SUCCEEDED(hr)) {

			//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Kinect CoordinateMapper Succeeded"));

			hr = i_KinectSensor->get_BodyFrameSource(&i_BodyFrameSource);
		}

		if (SUCCEEDED(hr)) {

			//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Get Body Frame Source Succeeded"));

			hr = i_BodyFrameSource->OpenReader(&i_BodyFrameReader);
		}

		if (!i_KinectSensor || FAILED(hr)) {
			return;
		}

		return;

	}


}

void AKinectBodyActor::UpdateBodyPoints(int index, CameraSpacePoint jointPosition, Vector4 jointOrientation){


	FKinectJointTransform& tmpJoint = ArrJoint[index];

	FQuat tmpQuat = FQuat(
		-jointOrientation.z,
		jointOrientation.x,
		-jointOrientation.y,
		jointOrientation.w
	);


	//
	'''
	'''
	//

	tmpJoint.Location.Set(jointPosition.Z * 100.f, -jointPosition.X * 100.f, jointPosition.Y * 100.f);

}


FKinectCurHandStates AKinectBodyActor::GetMyHand(){

	return myHandState;
}

TArray<FKinectJointTransform> AKinectBodyActor::GetJoints(){

	return ArrJoint;
}

