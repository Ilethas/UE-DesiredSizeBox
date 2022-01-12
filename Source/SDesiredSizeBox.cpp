// Fill out your copyright notice in the Description page of Project Settings.


#include "SDesiredSizeBox.h"

#include "Layout/LayoutUtils.h"

SDesiredSizeBox::SDesiredSizeBox()
	: ChildSlot(this)
{
	SetCanTick(false);
	bCanSupportFocus = false;
}

void SDesiredSizeBox::Construct(const FArguments& InArgs)
{
	WidthFactor  = InArgs._WidthFactor;
	HeightFactor = InArgs._HeightFactor;

	ChildSlot
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign)
		.Padding(InArgs._Padding)
		[
			InArgs._Content.Widget
		];
}

void SDesiredSizeBox::SetContent(const TSharedRef<SWidget>& InContent)
{
	ChildSlot
		[
			InContent
		];

	// TODO SlateGI - This seems no longer needed.
	Invalidate(EInvalidateWidget::Layout);
}

void SDesiredSizeBox::SetHAlign(const EHorizontalAlignment HAlign)
{
	// TODO SlateGI - Fix Slots
	if (ChildSlot.HAlignment != HAlign)
	{
		ChildSlot.HAlignment = HAlign;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SDesiredSizeBox::SetVAlign(const EVerticalAlignment VAlign)
{
	// TODO SlateGI - Fix Slots
	if (ChildSlot.VAlignment != VAlign)
	{
		ChildSlot.VAlignment = VAlign;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SDesiredSizeBox::SetPadding(const TAttribute<FMargin>& InPadding)
{
	// TODO SlateGI - Fix Slots
	if (!ChildSlot.SlotPadding.IdenticalTo(InPadding))
	{
		ChildSlot.SlotPadding = InPadding;
		Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

void SDesiredSizeBox::SetWidthFactor(const TAttribute<FOptionalSize> InWidthFactor)
{
	SetAttribute(WidthFactor, InWidthFactor, EInvalidateWidgetReason::Layout);
}

void SDesiredSizeBox::SetHeightFactor(const TAttribute<FOptionalSize> InHeightFactor)
{
	SetAttribute(HeightFactor, InHeightFactor, EInvalidateWidgetReason::Layout);
}

FVector2D SDesiredSizeBox::ComputeDesiredSize(float) const
{
	const EVisibility ChildVisibility = ChildSlot.GetWidget()->GetVisibility();
	if (ChildVisibility != EVisibility::Collapsed)
	{
		return FVector2D(ComputeDesiredWidth(), ComputeDesiredHeight());
	}
	return FVector2D::ZeroVector;
}

float SDesiredSizeBox::ComputeDesiredWidth() const
{
	const FVector2D& UnmodifiedChildDesiredSize = ChildSlot.GetWidget()->GetDesiredSize() + ChildSlot.SlotPadding.Get().GetDesiredSize();
	const FOptionalSize CurrentWidthFactor = WidthFactor.Get();

	float CurrentWidth = UnmodifiedChildDesiredSize.X;
	if (CurrentWidthFactor.IsSet())
	{
		CurrentWidth *= CurrentWidthFactor.Get();
	}
	return CurrentWidth;
}

float SDesiredSizeBox::ComputeDesiredHeight() const
{
	const FVector2D& UnmodifiedChildDesiredSize = ChildSlot.GetWidget()->GetDesiredSize() + ChildSlot.SlotPadding.Get().GetDesiredSize();
	const FOptionalSize CurrentHeightFactor = HeightFactor.Get();

	float CurrentHeight = UnmodifiedChildDesiredSize.Y;
	if (CurrentHeightFactor.IsSet())
	{
		CurrentHeight *= CurrentHeightFactor.Get();
	}
	return CurrentHeight;
}

void SDesiredSizeBox::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	const EVisibility ChildVisibility = ChildSlot.GetWidget()->GetVisibility();
	if (ArrangedChildren.Accepts(ChildVisibility))
	{
		const FMargin SlotPadding(ChildSlot.SlotPadding.Get());
		const AlignmentArrangeResult XAlignmentResult = AlignChild<Orient_Horizontal>(AllottedGeometry.GetLocalSize().X, ChildSlot, SlotPadding);
		const AlignmentArrangeResult YAlignmentResult = AlignChild<Orient_Vertical>(AllottedGeometry.GetLocalSize().Y, ChildSlot, SlotPadding);
		
		ArrangedChildren.AddWidget(
			AllottedGeometry.MakeChild(
				ChildSlot.GetWidget(),
				FVector2D(XAlignmentResult.Offset, YAlignmentResult.Offset),
				FVector2D(XAlignmentResult.Size, YAlignmentResult.Size)
			)
		);
	}
}

FChildren* SDesiredSizeBox::GetChildren()
{
	return &ChildSlot;
}

int32 SDesiredSizeBox::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, const int32 LayerId, const FWidgetStyle& InWidgetStyle, const bool bParentEnabled) const
{
	// SDesiredBox just draws its only child
	FArrangedChildren ArrangedChildren(EVisibility::Visible);
	ArrangeChildren(AllottedGeometry, ArrangedChildren);

	// Maybe none of our children are visible
	if(ArrangedChildren.Num() > 0)
	{
		check(ArrangedChildren.Num() == 1);
		const FArrangedWidget& TheChild = ArrangedChildren[0];

		return TheChild.Widget->Paint(Args.WithNewParent(this), TheChild.Geometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, ShouldBeEnabled(bParentEnabled));
	}
	return LayerId;
}