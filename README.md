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
/
<br>

Once the SDK has been installed, you can check the sensor status using various tools in Kinect Studio.

![1_kinectsdktools](https://github.com/JinyeongPark-870/How-to-use-Kinect-V2-sensor-data-in-Unreal-Engine-5/assets/4387404/7ba57d29-f82f-4afb-8872-179ee197a4fa)


You can find out various Classes, Methods, Structures, etc available in SDK code on this site.

[Kinect for Windows SDK 2.0 Microsoft Learn](https://learn.microsoft.com/en-us/previous-versions/windows/kinect/dn799271(v=ieb.10))

<br>
<br>

### 2. How to find path to the relevant file (.lib, .h) after installed Kinect SDK
After SDK installed, you can check the files and folders in the installed path.

This path is necessary when using the Unreal Engine later.

(SDK 설치 경로 및 폴더 사진)


<br>
<br>

### 3. How to Use Unreal Engine / Creating build.cs, actor.h/.cpp

Run Unreal Engine to create a new project (template is irrelevant)

Create C++ Actor in project.

Create default Actor class or other Actor class that inherits default Actor.


<br>
<br>

### 4. Descriptions of build.cs, ~Actor.h/.cpp File and provide basic descriptions such as code and class/structure

A simple description of the generated source files.

The Build.cs file is related to the project build.
You can add various modules, link library files and set paths with it.

~.h~.cpp is the header file, source file of the actor to be used in the project. If you have basic knowledge of C++, you can use it right away.

build.cs codes

Write build.cs code to use Kinect.lib that you found earlier.

(라이브러리 적용 코드)
(경로 지정 코드)

Path designation methods can be written in various ways.

[How to use after setting environment variables]

header file codes

You must include Kinect.h (other header files) in the header file first.

Copy and paste the file into the project's source folder (the same location as the actor you want to use).

And declare classes and variables to use.

(코드)


Class and Structure Description

.cpp codes

The default header file is automatically included, and write code using variables in header file.

(코드)

Code, Method Description

You can find out the results and errors of each mode of operation with HRESULT.



<br>
<br>

### 5. Apply written code (actor) in the Unreal Engine, create the c++ actor as a blue print actor and apply it to the level (spawn blueprint actor)

After you save the code, build solution and create the C++ actor class into a blue print actor.

Why create with a Blueprint Actor? : Simply, it's easier to see and edit.

Use that C++ actor to create a blue print actor.

(사진)

In the BluePrint Editor screen, you can immediately use the variables and methods you generated with c++ code.

You can save the method's return value as a variable, or call the method from another actor.

(사진)



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
