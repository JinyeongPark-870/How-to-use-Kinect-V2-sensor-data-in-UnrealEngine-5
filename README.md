# <div align=center> How-to-use-Kinect-V2-Sensor-data-in-Unreal-Engine-5 </div>
<br>
<br>

## Summary
Description of how to use data(values, particularly body joint position and orientation) collected by Kinect V2 sensor as a Actor(and blueprint actor) of the Unreal Engine 5 using C++ code.


## Essentials
1. Kinect V2 Sensor
2. Kinect SDK 2.0
3. Unreal Engine 5 / Visual Studio (or other IDE for using in UE)


## Text
<br>

### 1. Introduce Kinect sdk installation website, data related site and References
We Should use(install) Kinect SDK 2.0 to connect Kinect V2 sensor to PC

[Kinect for Windows SDK 2.0](https://www.microsoft.com/en-us/download/details.aspx?id=44561)
<br>
<br>

Once the SDK has been installed, you can check the sensor status using various tools in Kinect Studio.

![1_kinectsdktools](https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/7ba57d29-f82f-4afb-8872-179ee197a4fa) &nbsp;
<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d0c68b7c-284d-43e8-937f-d62b49de9ce0">

<br>
<br>

You can find out various Functions, Structures, etc available in SDK code on this site.

[Kinect for Windows SDK 2.0 Microsoft Learn](https://learn.microsoft.com/en-us/previous-versions/windows/kinect/dn799271(v=ieb.10))

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/c88b3dc4-7616-4094-9285-18097f5ce7de" width = "50%" height = "50%">


<br>
<br>

### 2. How to find path to the relevant file (.lib, .h) after installed Kinect SDK
After SDK installed, you can check the files and folders in the installed path.

This path is necessary when using the Unreal Engine later.

SDK install path
=> C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\

> We can find installed Kinect SDK's .lib , .h <br>
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/3a5f6d79-c8ec-4c1d-ad44-bb0860e4b94b" width = "50%" height = "50%">
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/e45f7002-2639-435c-b4f3-a47ab3b9303b" width = "50%" height = "50%"> <br>
> We use Kinect.lib , Kinect.h , Kinect.Face.h , Kinect.INPC.h

<br>
<br>

### 3. How to Use Unreal Engine / Creating build.cs, actor.h/.cpp

Run Unreal Engine to create a new project (template is irrelevant)

Create C++ Actor in project.

Create default Actor class or other Actor class that inherits default Actor.

> Create C++ Actor <br>
> In project source folder, there are Actor's header and source files <br>
> Dir => ~\Unreal Projects\ 'Project Name' \Source\ 'Project Name' \ <br>
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/51466921-823d-4636-a0cb-2a9af23a674e" width = "15%" height = "15%"> <br>
> My Actor's Name => KinectBodyActor

<br>
<br>

### 4. Descriptions of build.cs, ~Actor.h/.cpp File and provide basic descriptions such as code and class/structure

A simple description of the generated source files.

The Build.cs file is related to the project build.
You can add various modules, link library files and set paths with it.

.h .cpp is the header file, source file of the actor to be used in the project. If you have basic knowledge of C++, you can use it right away.

build.cs codes

Write build.cs code to use Kinect.lib that you found earlier.

> 'SensorGame' is my unreal engine project name

<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/ac56fbf8-160b-4cb7-b6d1-565e8f053826" width="70%" height="70%">

```C#
public SensorGame(ReadOnlyTargetRules Target) : base(Target)
{
    //...
    PublicAdditionalLibraries.Add(Path.Combine(ProjectRoot, "Binaries/Win64/Kinect20.lib"));
}
public string ProjectRoot
{
    get { return System.IO.Path.GetFullPath(System.IO.Path.Combine(ModuleDirectory, "../../")); }
}
```

<br>

In my way, I put library file in project's binary folder. <br>
Then load .lib file in build.cs <br>

<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/2476aeeb-966d-492c-9bb6-cbb76758a9bb" width="30%" height="30%">

Path designation methods can be written in various ways. <br>

header file codes <br>

Copy and paste the files into the project's source folder (the same location as the actor you want to use). <br>
<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/b86e3aba-48a6-40b2-ba67-ad34f7963f61" width="30%" height="30%">

You must include Kinect.h (other header files) in the header file first.

<br>

And declare classes and variables to use.

(코드)

<br> Headers <br>
```C++
#include <ShlObj.h>
#include <strsafe.h>
#include "Kinect.h"    // Add

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KinectBodyActor.generated.h"
```

<br> Class and Structure
<br> <br>

> Declare a structure for storing body tracking data(Position and Orientation)
```C++
USTRUCT(BlueprintType)
struct FKinectJointTransform {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly)
	FRotator Orientation;

};
```


<br><br>

> A structure for managing hand data
```C++
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
```

<br><br>

> Header Class
```C++

UCLASS()
class SENSORGAME_API AKinectBodyActor : public AActor
{
	GENERATED_BODY()
	
	~~~~~
```

<br><br>

> Interface and Function Declaration in Class
```C++
	IKinectSensor* i_KinectSensor;
	ICoordinateMapper* i_CoordinateMapper;
	IBodyFrameReader* i_BodyFrameReader;

	void initialize();
```
<br><br>

> Other variable, array, function declaration
```C++
	// Joint data array
	Joint joints[JointType_Count];
	JointOrientation joint_orient[JointType_Count];

	// HandState var
	HandState leftHandState = HandState_Unknown;
	HandState rightHandState = HandState_Unknown;

	// Data Update Func
	void UpdateBodyPoints(int index, CameraSpacePoint jointPosition, Vector4 jointOrientation);

	// Hand State var and return func
	FKinectCurHandStates myHandState;

	UFUNCTION(BlueprintCallable, Category = "Hand State Point")
	FKinectCurHandStates GetMyHand();

	// Array and return func
	UPROPERTY(BlueprintReadWrite)
	TArray<FKinectJointTransform> ArrJoint;

	UFUNCTION(BlueprintPure)
	TArray<FKinectJointTransform> GetJoints();

};
```
> Array **joints** and **joint_orient** save joint data(position, orientation).
> #
> **leftHandState** and **rightHandState** is for current hand state.
> #
> Func **UpdateBodyPoints** updates current joint data(**joints**, **joint_orient**)
> #
> **myHandState** is structure for hand data and **GetMyHand** function returns it.
> #
> **ArrJoint** is structure array for joint data and **GetJoints** function returns it.



<br> .cpp codes <br>

The default header file is automatically included, and write code using variables in header file.

(코드)

<br>

```C++
#include "KinectBodyActor.h"

AKinectBodyActor::AKinectBodyActor()
{
	~
}

void AKinectBodyActor::BeginPlay()
{
	Super::BeginPlay();

	// Set init Array size
	ArrJoint.SetNum(_countof(joints));
}
```


<br><br>
> initialize func
> #
> Check sensor's state with HRESULT
```C++
void AKinectBodyActor::initialize(){
	//UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Initialize"));

	HRESULT hr;
	hr = GetDefaultKinectSensor(&i_KinectSensor);

	if (FAILED(hr)) {
		UE_LOG(LogTemp, Display, TEXT("- Kinect Actor - Get Kinect Sensor Failed"));
		return;
	}

	if (i_KinectSensor) {

		IBodyFrameSource* i_BodyFrameSource = NULL;

		hr = i_KinectSensor->Open();

		if (SUCCEEDED(hr)) {
			hr = i_KinectSensor->get_CoordinateMapper(&i_CoordinateMapper);
		}
		if (SUCCEEDED(hr)) {
			hr = i_KinectSensor->get_BodyFrameSource(&i_BodyFrameSource);
		}
		if (SUCCEEDED(hr)) {
			hr = i_BodyFrameSource->OpenReader(&i_BodyFrameReader);
		}
		if (!I_KinectSensor || FAILED(hr)) {
			return;
		}
		return;
	}
}
```

<br><br>
> updateBodyPoints func
> #
> update and save sensor data
```C++
void AKinectBodyActor::UpdateBodyPoints(int index, CameraSpacePoint jointPosition, Vector4 jointOrientation){


	FKinectJointTransform& tmpJoint = ArrJoint[index];

	/* Make orientation with Quat
	FQuat tmpQuat = FQuat(-jointOrientation.z,jointOrientation.x,-jointOrientation.y,jointOrientation.w);
	~~~~~~
	FRotator tmpRotator;
	tmpRotator = ~;
	tmpJoint.Orientation = tmpRotator;
	*/

	tmpJoint.Location.Set(jointPosition.Z * 100.f, -jointPosition.X * 100.f, jointPosition.Y * 100.f);
}
```
> parameter **index** is for current joint's number.
> #
> paramter **jointPosition** is current joint's position data.
> #
> parameter **jointOrientation** is current joint's orientation data.
> #
> Use structure (**ArrJoint** array value) as reference var and edit array value


<br><br>
> Other func
```C++
FKinectCurHandStates AKinectBodyActor::GetMyHand(){

	return myHandState;
}
TArray<FKinectJointTransform> AKinectBodyActor::GetJoints(){

	return ArrJoint;
}
```
> Func **GetMyHand** returns **myhandState** structure. <br>
> Func **GetJoints** returns structure array **ArrJoint**.
> #
> Both function callable at other Blueprint Actors.

<br><br>
> Tick
```C++
void AKinectBodyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	initialize();

	if (!I_BodyFrameReader) {
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

		// Body
		for (int i = 0; i < _countof(ppBodies); i++) {

			IBody* i_Body = i_Bodies[i];

			if (i_Body) {

				BOOLEAN b_Tracked = false;

				hr = i_Body->get_IsTracked(&b_Tracked);

				if (SUCCEEDED(hr) && b_Tracked) {

					i_Body->get_HandLeftState(&leftHandState);
					i_Body->get_HandRightState(&rightHandState);

					hr = i_Body->GetJoints(_countof(joints), joints);

					if (SUCCEEDED(hr)) {

						hr = i_Body->GetJointOrientations(_countof(joints), joint_orient);

						if (SUCCEEDED(hr)) {

							// Joint
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
						}
					}
				}
			}
		}
	}
}
```

> Tick repeats as many times as the observed number of bodies and stores joint data of body. <br>
> After that, stores the data by repeating as many times as the number of body joints. <br>
> this project assumes there is only one body. <br>

> [JointType](https://learn.microsoft.com/en-us/previous-versions/windows/kinect/dn758663(v=ieb.10))
```C++
0: "SpineBase"
1: "SpineMid"
2: "Neck"
3: "Head"
4: "ShoulderLeft"
5: "ElbowLeft"
6: "WristLeft"
7: "HandLeft"
8: "ShoulderRight"
9: "ElbowRight"
10: "WristRight"
11: "HandRight"
12: "HipLeft"
13: "KneeLeft"
14: "AnkleLeft"
15: "FootLeft"
16: "HipRight"
17: "KneeRight"
18: "AnkleRight"
19: "FootRight"
20: "SpineShoulder"
21: "HandTipLeft"
22: "ThumbLeft"
23: "HandTipRight"
24: "ThumbRight"
```
<br><br>

Code, Method Description

You can find out the results and errors of each mode of operation with HRESULT.



<br>
<br>


### 5. Apply written code (actor) in the Unreal Engine, create the c++ actor as a blue print actor and apply it to the level (spawn blueprint actor)

After you save the code, build solution and create the C++ actor class into a blue print actor.

Why create with a Blueprint Actor? : Simply, it's easier to see and edit.

Use that C++ actor to create a blue print actor.

(사진)

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/8ab7658b-f917-41b8-b225-d6c7b8379a9a" width = "50%" height = "50%"> <br>
Blueprint Class Name : KinectBodyActor_BP

In the BluePrint Editor screen, you can immediately use the variables and methods you generated with c++ code.

You can save the method's return value as a variable, or call the method from another actor.

(사진)

> We created an Unreal Engine Actor that can collect, process data from Kinect sensor and return them with method.
> At the current level (map), you can call the method of the spawned actor(we made) to use sensor data at other actors, characters, and interfaces.

<br>
<br>

### 6. Examples of screen log output and examples of using various data Photographs, videos

Now it's a way to make use of sensor data.

Let's use two data types(Joint Position and Joint Orientation).

(블루프린트 화면)

As an example of using data, you can use position to roughly represent the location of a body joint, or you can create a vector with those coordinates to know the direction of a specific body part.

If we know the position and orientation of the body parts, we can create an algorithm for posture detection.

Various examples of utilizing the positions of body joints.

(  )

The direction vectors of the shoulders, elbows, and hands let you know in which direction your hand is stretched and if you are bending.

You can create direction vectors for your thighs through the positions of your knees and pelvis, And you can compare each other's positions to determine your posture.

Or, you can use a combination of these data to determine a particular posture

The orientation values allow you to create a rotation angle and apply it to the character model.

These figures depend on the skeleton of the character model or the engine environment, which requires a fairly complex process. (We will not discuss this.)

Additionally, a way to use the condition of hand.



<br>
<br>

### 7. Finish


Working on this project, I submitted a game of interface (NUI) and unreal engine using that function as my graduation work.



<br>
<br>

### 8. References

(위의 인용 자료, 참고 사이트 등 링크 첨부)
With the professor's feedback, if there is a condition for further research on related topics, I would like to compare the existing interface equipment (keyboard, mouse, controller, etc.) with the interface of this project to study which device is more efficient.

This was my first post on GitHub. Thank you for your interest.
