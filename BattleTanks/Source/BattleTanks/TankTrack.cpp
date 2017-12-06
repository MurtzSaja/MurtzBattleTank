// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is Throttle at : %f"), *Name, Throttle);*/

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingFroce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
