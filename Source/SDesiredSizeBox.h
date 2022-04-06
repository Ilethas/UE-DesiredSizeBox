// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Layout/Margin.h"
#include "Layout/Children.h"
#include "Types/SlateStructs.h"
#include "Widgets/SPanel.h"

class FArrangedChildren;
class FPaintArgs;
class FSlateWindowElementList;

class DEMORPG_API SDesiredSizeBox : public SPanel
{
	SLATE_DECLARE_WIDGET(SDesiredSizeBox, SPanel)

public:
	class UE_DEPRECATED(5.0, "FDesiredSizeBoxSlot is deprecated. Use FSingleWidgetChildrenWithBasicLayoutSlot or FOneSimpleMemberChild")
	FDesiredSizeBoxSlot : public FSingleWidgetChildrenWithBasicLayoutSlot
	{
		using FSingleWidgetChildrenWithBasicLayoutSlot::FSingleWidgetChildrenWithBasicLayoutSlot;
	};

	SLATE_BEGIN_ARGS(SDesiredSizeBox)
		: _HAlign(HAlign_Fill)
		, _VAlign(VAlign_Fill)
		, _Padding(0.0f)
		, _Content()
		, _WidthFactor(FOptionalSize())
		, _HeightFactor(FOptionalSize())
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
	}

	/** Horizontal alignment of content in the area allotted to the SDesiredSizeBox by its parent */
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

	/** Vertical alignment of content in the area allotted to the SDesiredSizeBox by its parent */
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	/** Padding between the SDesiredSizeBox and the content that it presents. Padding affects desired size. */
	SLATE_ATTRIBUTE(FMargin, Padding)

	/** The widget content presented by the SDesiredSizeBox */
	SLATE_DEFAULT_SLOT(FArguments, Content)

	/** Report content's desired width multiplied by WidthFactor. */
	SLATE_ATTRIBUTE(FOptionalSize, WidthFactor)

	/** Report content's desired height multiplied by HeightFactor. */
	SLATE_ATTRIBUTE(FOptionalSize, HeightFactor)

	SLATE_END_ARGS()

	SDesiredSizeBox();

	void Construct(const FArguments& InArgs);

	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual FChildren* GetChildren() override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, const int32 LayerId, const FWidgetStyle& InWidgetStyle, const bool bParentEnabled) const override;

	/**
	* See the Content slot.
	*/
	void SetContent(const TSharedRef<SWidget>& InContent);

	/** See HAlign argument */
	void SetHAlign(EHorizontalAlignment HAlign);

	/** See VAlign argument */
	void SetVAlign(EVerticalAlignment VAlign);

	/** See Padding attribute */
	void SetPadding(TAttribute<FMargin> InPadding);

	/** See WidthOverride attribute */
	void SetWidthFactor(TAttribute<FOptionalSize> InWidthFactor);

	/** See HeightOverride attribute */
	void SetHeightFactor(TAttribute<FOptionalSize> InHeightFactor);

protected:
	// Begin SWidget overrides.
	virtual FVector2D ComputeDesiredSize(float) const override;
	float ComputeDesiredWidth() const;
	float ComputeDesiredHeight() const;
	// End SWidget overrides.

	struct FDesiredSizeBoxOneChildSlot : TSingleWidgetChildrenWithBasicLayoutSlot<EInvalidateWidgetReason::None> // we want to add it to the Attribute descriptor
	{
		friend SDesiredSizeBox;
		using TSingleWidgetChildrenWithBasicLayoutSlot<EInvalidateWidgetReason::None>::TSingleWidgetChildrenWithBasicLayoutSlot;
	};
	FDesiredSizeBoxOneChildSlot ChildSlot;

private:
	/** Report content's desired width multiplied by WidthFactor. */
	TSlateAttribute<FOptionalSize> WidthFactor;

	/** Report content's desired height multiplied by HeightFactor. */
	TSlateAttribute<FOptionalSize> HeightFactor;
};
