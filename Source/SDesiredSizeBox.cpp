// Fill out your copyright notice in the Description page of Project Settings.


#include "SDesiredSizeBox.h"

#include "Layout/LayoutUtils.h"

SLATE_IMPLEMENT_WIDGET(SDesiredSizeBox)
void SDesiredSizeBox::PrivateRegisterAttributes(FSlateAttributeInitializer& AttributeInitializer)
{
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION_WITH_NAME(AttributeInitializer, "SlotPadding", ChildSlot.SlotPaddingAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, WidthFactor, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, HeightFactor, EInvalidateWidgetReason::Layout);
}

SDesiredSizeBox::SDesiredSizeBox()
	: ChildSlot(this)
	, WidthFactor(*this)
	, HeightFactor(*this)
{
	SetCanTick(false);
	bCanSupportFocus = false;
}

void SDesiredSizeBox::Construct(const FArguments& InArgs)
{
	SetWidthFactor(InArgs._WidthFactor);
	SetHeightFactor(InArgs._HeightFactor);

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
}

void SDesiredSizeBox::SetHAlign(const EHorizontalAlignment HAlign)
{
	ChildSlot.SetHorizontalAlignment(HAlign);
}

void SDesiredSizeBox::SetVAlign(const EVerticalAlignment VAlign)
{
	ChildSlot.SetVerticalAlignment(VAlign);
}

void SDesiredSizeBox::SetPadding(TAttribute<FMargin> InPadding)
{
	ChildSlot.SetPadding(InPadding);
}

void SDesiredSizeBox::SetWidthFactor(TAttribute<FOptionalSize> InWidthFactor)
{
	WidthFactor.Assign(*this, InWidthFactor);
}

void SDesiredSizeBox::SetHeightFactor(TAttribute<FOptionalSize> InHeightFactor)
{
	HeightFactor.Assign(*this, InHeightFactor);
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
	const FVector2D& UnmodifiedChildDesiredSize = ChildSlot.GetWidget()->GetDesiredSize() + ChildSlot.GetPadding().GetDesiredSize();
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
	const FVector2D& UnmodifiedChildDesiredSize = ChildSlot.GetWidget()->GetDesiredSize() + ChildSlot.GetPadding().GetDesiredSize();
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
		const FMargin SlotPadding(ChildSlot.GetPadding());
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