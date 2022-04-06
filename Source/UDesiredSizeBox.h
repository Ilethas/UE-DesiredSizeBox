// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ContentWidget.h"
#include "Widgets/SWidget.h"
#include "UDesiredSizeBox.generated.h"

class SDesiredSizeBox;
UCLASS()
class DEMORPG_API UDesiredSizeBox : public UContentWidget
{
	GENERATED_BODY()
public:
	/** Report content's desired width multiplied by WidthFactor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Child Layout")
	float WidthFactor;

	/** Report content's desired height multiplied by HeightFactor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Child Layout")
	float HeightFactor;


	UDesiredSizeBox(const FObjectInitializer& ObjectInitializer);
	
	/** Report content's desired width multiplied by WidthFactor. */
	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box")
	void SetWidthFactor(const float InWidthFactor);

	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box")
	void ClearWidthFactor();

	/** Report content's desired height multiplied by HeightFactor. */
	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box")
	void SetHeightFactor(const float InHeightFactor);

	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box")
	void ClearHeightFactor();

	
	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(const bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	TSharedPtr<SDesiredSizeBox> DesiredSizeBox;
	
	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;
	// End UPanelWidget

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
};