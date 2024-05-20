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

<!-- 1 -->

### <h1> 1. Introduce Kinect sdk installation website, data related site and References </h1>
We Should install Kinect SDK 2.0 to connect Kinect V2 sensor to PC

[Kinect for Windows SDK 2.0](https://www.microsoft.com/en-us/download/details.aspx?id=44561)
<br>
<br>

Once the SDK has been installed, you can check the sensor status using various tools in Kinect Studio.

![1_kinectsdktools](https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/7ba57d29-f82f-4afb-8872-179ee197a4fa) &nbsp;
<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d0c68b7c-284d-43e8-937f-d62b49de9ce0">

<br>
<br>

You can find out various Functions, Structures, etc available in SDK on this site.

[Kinect for Windows SDK 2.0 Microsoft Learn](https://learn.microsoft.com/en-us/previous-versions/windows/kinect/dn799271(v=ieb.10))

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/c88b3dc4-7616-4094-9285-18097f5ce7de" width = "50%" height = "50%">


<br>
<br>

<!-- 2 -->

### <h1> 2. How to find path to the relevant files (.lib, .h) </h1>

<br>

After SDK installed, you can check the files and folders in the installed path. <br>
This path is necessary when using the Unreal Engine later. <br>

**SDK install path** <br>
=> C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\ <br>

> We can find Kinect SDK's **.lib** , **.h** files. <br>
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/bfd0c6b1-ff9c-4bb9-8bb9-62c90b533ef7" width = "50%" height = "50%"> <br>
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/e45f7002-2639-435c-b4f3-a47ab3b9303b" width = "50%" height = "50%"> <br>
> We use Kinect.lib , Kinect.h , Kinect.Face.h , Kinect.INPC.h

<br>
<br>

<!-- 3 -->

### <h1> 3. Create Unreal project and Actor with C++ (.h/.cpp) </h1>
<br>

Run Unreal Engine and create a new game project (template is irrelevant) <br>
Create a C++ Actor in project. <br>
Create default Actor class or other Actor class that inherits default Actor. <br>

> In project source folder, there are Actor's header and source files <br>
> Dir => ~\Unreal Projects\ 'Project Name' \Source\ 'Project Name' \ <br>
> <img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/51466921-823d-4636-a0cb-2a9af23a674e" width = "15%" height = "15%"> <br>
> My example Actor's Name => **KinectBodyActor** <br>

<br>
<br>

<!-- 4 -->

### <h1> 4. Descriptions of build.cs, ~Actor.h/.cpp File </h1>

<br>
A simple description of the generated source files. <br>

**Build.cs** file is related to the project build. <br>

You can add various modules, link library files and set paths with it. <br>

**.h .cpp** files are the header file and source file of the actor using in the project. <br>

<br>
build.cs codes <br>

Write **build.cs** code to use library **Kinect.lib**. <br>

> **SensorGame** is my example Unreal project's name <br>
<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/ac56fbf8-160b-4cb7-b6d1-565e8f053826" width="70%" height="70%"> <br>

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

> Path designation methods can be written in various ways. <br>

<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/2476aeeb-966d-492c-9bb6-cbb76758a9bb" width="30%" height="30%">
&nbsp;
<img src="https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/b86e3aba-48a6-40b2-ba67-ad34f7963f61" width="30%" height="30%"> <br>


> In my way, I put library file in project's binary folder then, load **.lib** file with **build.cs** <br>
> Copy and paste each files into the project's source folder. <br>


<br>

<h2> header file codes </h2><br>

> Must include **Kinect.h** at actor's header file first.


<br> Headers <br>
```C++
#include <ShlObj.h>
#include <strsafe.h>
#include "Kinect.h"    // Add

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KinectBodyActor.generated.h"
```
#

<br> Class and Structure
<br>

> Declare a structure for storing body tracking data(Position and Orientation values) <br>
> **Location** : Vector (x, y, z) <br>
> **Orientation** : Rotator (x, y, z, w) <br>
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
#

<br><br>

> A structure for managing hand data <br>
> HandState { 0 : UnKnown , 1 : Not Tracked , 2 : Open , 3 : Closed , 4 : Lasso } <br>
```C++
USTRUCT(BlueprintType)
struct FKinectCurHandStates {

	GENERATED_BODY()

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
#

<br><br>

> Inside Header Class
```C++

UCLASS()
class SENSORGAME_API AKinectBodyActor : public AActor
{
	GENERATED_BODY()
	
	~~~~~
```
#

<br><br>

> Interface and Function Declaration in Class
```C++
	IKinectSensor* i_KinectSensor;
	ICoordinateMapper* i_CoordinateMapper;
	IBodyFrameReader* i_BodyFrameReader;

	void initialize();
```
#

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
> Array **joints** and **joint_orient** save joint data(position, orientation). <br>
> **leftHandState** and **rightHandState** is for current hand state. <br>
> Function **UpdateBodyPoints** updates current joint data(**joints**, **joint_orient**). <br>
> **myHandState** is structure for hand data and **GetMyHand** function returns it. <br>
> **ArrJoint** is structure array for joint data and **GetJoints** function returns it. <br>

#


<br> <h2> .cpp codes </h2> <br>


<br>

> Generator and BeginPlay function
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

#

<br><br>

> initialize func <br>
> Checking Kinect sensor's state with function <br>
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

#

<br><br>
> **UpdateBodyPoints** func <br>
> Update and save sensor data <br>
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
> parameter **index** is for current joint's number. <br>
> paramter **jointPosition** is current joint's position data. <br>
> parameter **jointOrientation** is current joint's orientation data. <br>
> Use structure (**ArrJoint** array value) as reference var and edit array value. <br>

#

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
> Func **GetJoints** returns structure array **ArrJoint**. <br>
> Both function callable at other Blueprint Actors. <br>

#

<br><br>
> Tick function
```C++
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
		// Body
		for (int i = 0; i < _countof(i_Bodies); i++) {

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

> In Tick function, for loop repeats as many times as the observed number of bodies and stores joint data of body. <br>
> After that, stores the data by repeating as many times as the number of body joints. <br>
> count of bodies * count of joints(25) <br>
> this project assumes there is only one body. <br>

#

<details>
<summary>JointType in Kinect SDK</summary>
	
> [Joint Type Enum](https://learn.microsoft.com/en-us/previous-versions/windows/kinect/dn758663(v=ieb.10))
	
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
<p align="center">
<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d6a9f01b-ff64-48c2-8124-c546d687c8cd" width = "65%" height = "65%" >
</p>
</details>
<br><br>

Code, Method Description <br>
You can find out the results and errors with HRESULT function. <br>

<br>

<!-- 5 -->

### <h1> 5. Apply written code (actor) in the Unreal Engine, create Blueprint Actor based on C++ Actor and place on the level </h1>

In Unreal Engine, we can make Blueprint Actor based on C++ Actor. <br>

Why create as Blueprint Actor? : Simply, it's easier to see and edit. <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/8ab7658b-f917-41b8-b225-d6c7b8379a9a" width = "50%" height = "50%"> <br>

> Blueprint Class Name : KinectBodyActor_BP <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/c92c6706-dfee-48a1-bb11-d96e6c04ad93" width = "50%" height = "50%"> <br>
> Place Blueprint Actor anywhere on level(map) <br>

#

In the BluePrint Editor screen, you can immediately use the variables and methods you generated with c++ code. <br>

You can save function return value as a variable, or call the method from another actor. <br>


<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/75c87030-6011-4bb3-821a-d6882dd49ea6" width = "40%" height = "40%">
&nbsp;
<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/9dfe0695-bf8f-4253-aa73-ecf198237433" width = "50%" height = "50%"> <br>

> In another Blueprint Actor's Event graph(another actor which needs to get sensor data), create **Get Actor of Class** and connect to **Begin Play**. <br>
> Set Actor Class as our Blueprint Actor(Kinect Sensor Actor). <br>
> We can call C++ Actor's function and get and save return value as variable. <br>

#

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/a996ac87-3d4e-4c0d-9866-f12c6f455318" width = "55%" height = "55%"> <br>
> Our function **GetJoints** returns structure array and we can approach array value with for-each loop. <br>

#

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/03362854-4705-41b3-b430-4d7430cf1add" width = "65%" height = "65%"> <br>
> Aslo, we can use our function **GetMyHand** to get hand state data. <br>

#

We created an Unreal Engine Actor that can collect, process data from Kinect sensor and return them with method. <br>
At the current level (map), you can call the method of the spawned actor(we made) to use sensor data at other actors, characters, and interfaces.

<br>
<br>

<!-- 6 -->

### <h1> 6. Examples of using kinect Sensor data </h1>

Here are several ways to use sensor data. <br>
We can use two types of data(Joint Position and Joint Orientation). <br>
As an example of using data, we can use position data to roughly represent the location of each body joints, or create some vectors with those coordinates to know direction of specific body part. <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/a6c80eba-4486-4b02-aabc-153b06d5d892" width = "45%" height = "45%">
&nbsp; &nbsp;
<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/9a06101c-e718-473b-839b-5f49d9f9fe34" width = "45%" height = "45%"> <br>

> One way of saving each joint's data and representing each joint's position. <br>


#

If we know the position and orientation of the body parts, we can make an algorithm for posture(gesture) detection. <br>

Various examples of utilizing the positions of body joints. <br>

We can make upper leg direction vectors with our thighs through the positions of pelvis and our knees. <br>
The direction vectors made up of shoulders, elbows, and hands let you know in which direction your hand is stretched or bended. <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/2620b4a0-53bc-44cb-9775-1b5c04e2c144" width = "45%" height = "45%"> <br>
> Making vectors with some joints.


<br>

And we can use a combination of these data(positions and vectors) to determine a particular posture(gesture). <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d6be9b10-dd30-4570-9d3a-f3dcfc1805be" width = "45%" height = "45%"> <br>
> Custom pose T-Pose needs to check Left and Right arm vectors. <br>
> I used average value of left and right arms' vector when i stretch arms to compare and check both arms are stretched. <br>
> Making vector length with subtracting present vector value from average value. <br>
> Vector length value means error value. And we can set range of it to determine posture. <br>

<br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/20141cc7-b2ac-4ad7-880d-6438cf71616c" width = "45%" height = "45%"> <br>
> With more specific posture, we need more data to compare. <br>

#

We can use joint orientation values to create a rotation angle and apply it to the character model. <br>
Then, we can move character model(bone) like body-tracking with orientation data. <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/be1bd39c-1b1f-4dfd-b708-965a485c26d3" width = "45%" height = "45%">
&nbsp;
<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/dc6b6054-d5a7-4a3d-8d1e-d3644507c56e" width = "45%" height = "45%"> <br>

> In character animation blueprint, we can use orientation data and edit character's mesh bone. <br>
> In picture, Joints(array)'s orientation value and Orientation(array)'s value are same. <br>


<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/8169c4ee-2c25-4ce3-9c9b-aa5a563c4ccd" width = "45%" height = "45%"> <br>
> This is one example of controlling model and gesture detecting. <br>
> ~~(Picture quality is bad but) It need to stretch both arms to get the true value.~~ <br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/87f1ea28-4762-466f-9530-7bfe885b7fd6" width = "45%" height = "45%"> <br>
> And Also we can control character in Unreal Engine level(map), That means we can use mesh collision. <br>
> I made one example of using collision with character(mesh) and static mesh actor. <br>


> These figures depend on the skeleton of the character model or the engine environment, which requires a fairly complex process. (I will not discuss this.) <br>

#

Additionally, there's one way to use the condition of hand. <br>
With hand state and hand position, we can control cursor and make it work similar to clicks. <br>
<br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/03c9f4a0-0ad3-4eee-b372-8622ecf1a4fa" width = "45%" height = "45%"> <br>
> We can get hand data with our function in other actor and set cursor position at player character controller class. <br>
> And need to adjust values to fit the screen size. <br>

<br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d8b5fe44-0ac9-4293-8c76-9051ed86fe65" width = "45%" height = "45%"> <br>
> Simple example actor for representing hand states. <br>
> Actor follows hand position and changes mesh color with hand state. <br>

<br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/058da363-a252-4a8b-ac82-777f0d85f8c6" width = "55%" height = "55%"> <br>
> We can make cursor click function with hand state(left or right) <br>
> Hand State value 3 means hand is closed. <br>

<br>

<img src = "https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/d8574d76-0bcc-4804-abd0-8b5e293ded28" width = "45%" height = "45%"> <br>
> Example of using hand state data and click function with custom button actor. <br>
> I made a function that allows the actor which overlapping with the cursor to react when hand is closed(clench). <br>
> Delay about 1 second. <br>

<br>
<br>

<!-- 7 -->

### <h1> 7. Finish </h1>

<br>
This project is about using Kinect SDK to use data from Kinect sensors in Unreal Engine. <br>
Using C++ codes and blueprints, we processed the sensor's body tracking data and used it in various ways. <br>
The position data of the body joint may be used to determine the user's gesture, and the orientation data may be used to project the user's current body state to a character in the virtual environment. <br>
In other words, people in the real world can do various activities (interactions between actors) through characters in the virtual environment. <br>
I am not good at English, but thank you very much for your interest. <br>
