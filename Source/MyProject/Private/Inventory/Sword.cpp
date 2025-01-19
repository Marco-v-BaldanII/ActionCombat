// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Sword.h"

ASword::ASword() {
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMesh"));
	Mesh->SetupAttachment(RootComponent);
}