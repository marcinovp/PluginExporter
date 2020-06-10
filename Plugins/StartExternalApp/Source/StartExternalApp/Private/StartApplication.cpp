// © 2020 Peter Marcinov. All rights reserved.

#include "StartApplication.h"
#include "Misc/Paths.h"

// Sets default values
AStartApplication::AStartApplication()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStartApplication::BeginPlay()
{
	Super::BeginPlay();

	finalAppPath = FPaths::ProjectDir() + externalAppPath;

	if (startAutomatically)
	{
		OpenExternalApp(true);
	}
}

// Called every frame
void AStartApplication::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAppOpened)
	{
		bool IsProcRunning = FPlatformProcess::IsProcRunning(procHandle);
		if (IsProcRunning)
		{
		}
		else
		{
			OnExternalAppCancelled();
			
			if (restartAutomatically)
			{
				OpenExternalApp(true);
			}
			isAppOpened = false;
		}
	}
}

void AStartApplication::OpenExternalApp(bool launchHidden)
{
	bool fileExists = FPaths::FileExists(finalAppPath);
	if (fileExists)
	{
		procHandle = FPlatformProcess::CreateProc(*finalAppPath, nullptr, true, launchHidden, false, nullptr, 0, nullptr, nullptr);
		isAppOpened = true;
	}
	else
	{
		UE_LOG(LogClass, Error, TEXT("File does not exists at path %s"), *finalAppPath);
	}
}

void AStartApplication::CloseExternalApp()
{
	if (FPlatformProcess::IsProcRunning(procHandle))
	{
		FPlatformProcess::TerminateProc(procHandle, false);
	}
	isAppOpened = false;
}


void AStartApplication::BeginDestroy()
{
	Super::BeginDestroy();
	CloseExternalApp();
}

