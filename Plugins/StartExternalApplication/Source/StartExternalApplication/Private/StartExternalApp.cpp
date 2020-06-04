// © 2020 Peter Marcinov. All rights reserved.

#include "StartExternalApp.h"

// Sets default values
AStartExternalApp::AStartExternalApp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStartExternalApp::BeginPlay()
{
	Super::BeginPlay();

	finalAppPath = FPaths::ProjectDir() + externalAppPath;
	UE_LOG(LogClass, Log, TEXT("-----file exists - %s - at path %s"), FPaths::FileExists(finalAppPath) ? TEXT("true") : TEXT("false"), *finalAppPath);
	
	if (startAutomatically)
	{
		OpenExternalApp(true);
	}
}

// Called every frame
void AStartExternalApp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAppOpened)
	{
		bool IsProcRunning = FPlatformProcess::IsProcRunning(procHandle);
		if (IsProcRunning)
		{
		}
		else if (restartAutomatically)
		{
			OpenExternalApp(true);
		}
	}
}

void AStartExternalApp::OpenExternalApp(bool launchHidden)
{
	procHandle = FPlatformProcess::CreateProc(*finalAppPath, nullptr, true, launchHidden, false, nullptr, 0, nullptr, nullptr);
	isAppOpened = true;
}

void AStartExternalApp::CloseExternalApp()
{
	if (FPlatformProcess::IsProcRunning(procHandle))
	{
		FPlatformProcess::TerminateProc(procHandle, false);
	}
	isAppOpened = false;
}


void AStartExternalApp::BeginDestroy()
{
	Super::BeginDestroy();
	CloseExternalApp();
}

