// © 2020 Peter Marcinov. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartApplication.generated.h"

UCLASS()
class STARTEXTERNALAPP_API AStartApplication : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartApplication();

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
	FString finalAppPath;
};
