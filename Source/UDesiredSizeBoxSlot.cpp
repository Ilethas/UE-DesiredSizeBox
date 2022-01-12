#include "UDesiredSizeBoxSlot.h"

#include "SDesiredSizeBox.h"
#include "Components/Widget.h"

void UDesiredSizeBoxSlot::SetPadding(const FMargin InPadding)
{
	Padding = InPadding;
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox.Pin()->SetPadding(InPadding);
	}
}

void UDesiredSizeBoxSlot::SetHorizontalAlignment(const EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox.Pin()->SetHAlign(InHorizontalAlignment);
	}
}

void UDesiredSizeBoxSlot::SetVerticalAlignment(const EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if (DesiredSizeBox.IsValid())
	{
		DesiredSizeBox.Pin()->SetVAlign(InVerticalAlignment);
	}
}

void UDesiredSizeBoxSlot::SynchronizeProperties()
{
	SetPadding(Padding);
	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
}

void UDesiredSizeBoxSlot::BuildSlot(const TSharedRef<SDesiredSizeBox> InDesiredSizeBox)
{
	DesiredSizeBox = InDesiredSizeBox;

	SynchronizeProperties();

	DesiredSizeBox.Pin()->SetContent(Content ? Content->TakeWidget() : SNullWidget::NullWidget);
}

void UDesiredSizeBoxSlot::ReleaseSlateResources(const bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	DesiredSizeBox.Reset();
}
