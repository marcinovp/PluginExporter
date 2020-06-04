// © 2020 Peter Marcinov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartExternalApp.generated.h"

UCLASS()
class STARTEXTERNALAPPLICATION_API AStartExternalApp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartExternalApp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start external app")
		bool startAutomatically;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start external app")
		bool restartAutomatically;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start external app")
		FString externalAppPath;

	UFUNCTION(BlueprintCallable, Category = "Start external app")
		void OpenExternalApp(bool launchHidden);

	UFUNCTION(BlueprintCallable, Category = "Start external app")
		void CloseExternalApp();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Start external app")
		void OnExternalAppCancelled();

private:

	FProcHandle procHandle;
	bool isAppOpened = false;
	/*const FString FILENAME = "ChosenPath.txt";
	const FString CHOOSER_FILENAME = "FileDialog.exe";
	const FString CHOOSER_FOLDER = "External executables";*/
	FString finalAppPath;
};
