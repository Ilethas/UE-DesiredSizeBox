// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PanelSlot.h"
#include "UDesiredSizeBoxSlot.generated.h"

class SDesiredSizeBox;
UCLASS()
class DEMORPG_API UDesiredSizeBoxSlot : public UPanelSlot
{
	GENERATED_BODY()
public:
	/** The padding area between the slot and the content it contains. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Layout|Desired Size Box Slot")
	FMargin Padding;
	
	/** The alignment of the object horizontally. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Layout|Desired Size Box Slot")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	/** The alignment of the object vertically. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Layout|Desired Size Box Slot")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;


	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box Slot")
	void SetPadding(const FMargin InPadding);

	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box Slot")
	void SetHorizontalAlignment(const EHorizontalAlignment InHorizontalAlignment);

	UFUNCTION(BlueprintCallable, Category="Layout|Desired Size Box Slot")
	void SetVerticalAlignment(const EVerticalAlignment InVerticalAlignment);

	// UPanelSlot interface
	virtual void SynchronizeProperties() override;
	// End of UPanelSlot interface

	/** Builds the underlying slot for the slate SizeBox. */
	void BuildSlot(const TSharedRef<SDesiredSizeBox> InDesiredSizeBox);

	virtual void ReleaseSlateResources(const bool bReleaseChildren) override;
	
private:
	/** A pointer to the button to allow us to adjust the size, padding...etc at runtime. */
	TWeakPtr<SDesiredSizeBox> DesiredSizeBox;
};