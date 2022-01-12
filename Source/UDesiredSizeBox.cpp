#include "UDesiredSizeBox.h"

#include "SDesiredSizeBox.h"
#include "UDesiredSizeBoxSlot.h"

#define LOCTEXT_NAMESPACE "UMG"

UDesiredSizeBox::UDesiredSizeBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable  = false;
	Visibility   = ESlateVisibility::SelfHitTestInvisible;
	WidthFactor  = 1.0f;
	HeightFactor = 1.0f;
}

void UDesiredSizeBox::SetWidthFactor(const float InWidthFactor)
{
	WidthFactor = InWidthFactor;
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox->SetWidthFactor(InWidthFactor);
	}
}

void UDesiredSizeBox::ClearWidthFactor()
{
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox->SetWidthFactor(FOptionalSize());
	}
}

void UDesiredSizeBox::SetHeightFactor(const float InHeightFactor)
{
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox->SetHeightFactor(InHeightFactor);
	}
}

void UDesiredSizeBox::ClearHeightFactor()
{
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox->SetHeightFactor(FOptionalSize());
	}
}

void UDesiredSizeBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	SetWidthFactor(WidthFactor);
	SetHeightFactor(HeightFactor);
}

void UDesiredSizeBox::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	DesiredSizeBox.Reset();
}

#if WITH_EDITOR

const FText UDesiredSizeBox::GetPaletteCategory()
{
	return LOCTEXT("Panel", "Panel");
}

#endif

UClass* UDesiredSizeBox::GetSlotClass() const
{
	return UDesiredSizeBoxSlot::StaticClass();
}

void UDesiredSizeBox::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live slot if it already exists
	if (DesiredSizeBox.IsValid())
	{
		CastChecked<UDesiredSizeBoxSlot>(InSlot)->BuildSlot(DesiredSizeBox.ToSharedRef());
	}
}

void UDesiredSizeBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	// Remove the widget from the live slot if it exists.
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox->SetContent(SNullWidget::NullWidget);
	}
}

TSharedRef<SWidget> UDesiredSizeBox::RebuildWidget()
{
	DesiredSizeBox = SNew(SDesiredSizeBox);

	if (GetChildrenCount() > 0)
	{
		Cast<UDesiredSizeBoxSlot>(GetContentSlot())->BuildSlot(DesiredSizeBox.ToSharedRef());
	}

	return DesiredSizeBox.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
