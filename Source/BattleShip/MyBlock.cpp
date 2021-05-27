// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "GameController.h"
// Sets default values


// Called when the game starts or when spawned
void AMyBlock::BeginPlay()
{
	Super::BeginPlay();

}

AMyBlock::AMyBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> WhiteMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MissMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GridMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> MarkedMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Block/PlaneMesh.PlaneMesh"))
			, WhiteMaterial(TEXT("/Game/Block/WhiteMaterial.WhiteMaterial"))
			, BlueMaterial(TEXT("/Game/Block/BlueMaterial.BlueMaterial"))
			, RedMaterial(TEXT("/Game/Block/RedMaterial.RedMaterial"))
			, MissMaterial(TEXT("/Game/Block/MissMaterial.MissMaterial"))
			, GridMaterial(TEXT("/Game/Block/GridMaterial.GridMaterial"))
			, MarkedMaterial(TEXT("/Game/Block/MarkedMaterial.MarkedMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.GridMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AMyBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMyBlock::OnFingerPressedBlock);
	WhiteMaterial = ConstructorStatics.WhiteMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	MissMaterial = ConstructorStatics.MissMaterial.Get();
	GridMaterial = ConstructorStatics.GridMaterial.Get();
	MarkedMaterial = ConstructorStatics.MarkedMaterial.Get();
}

void AMyBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void AMyBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AMyBlock::HandleClicked()
{
	if (GC != nullptr) GC->BlockClick(nro);
	

}

void AMyBlock::SetMaterial(int matColor) {

	switch (matColor) {

	case 1: BlockMesh->SetMaterial(0, BlueMaterial);
		break;
	case 2: BlockMesh->SetMaterial(0, MissMaterial);
		break;
	case 3: BlockMesh->SetMaterial(0, RedMaterial);
		break;
	case 4: BlockMesh->SetMaterial(0, MarkedMaterial);
		break;
	default: BlockMesh->SetMaterial(0, GridMaterial);
		break;
	}
}

void AMyBlock::Highlight(bool bOn)
{
	if (bOn) {
		
		if (GC != nullptr) GC->BlockClick(nro);
		

	}




}