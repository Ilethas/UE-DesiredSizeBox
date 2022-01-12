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
public:
	class FDesiredSizeBoxSlot : public TSupportsOneChildMixin<FDesiredSizeBoxSlot>, public TSupportsContentAlignmentMixin<FDesiredSizeBoxSlot>, public TSupportsContentPaddingMixin<FDesiredSizeBoxSlot>
	{
	public:
		FDesiredSizeBoxSlot(SWidget* InOwner)
			: TSupportsOneChildMixin<FDesiredSizeBoxSlot>(InOwner)
			, TSupportsContentAlignmentMixin<FDesiredSizeBoxSlot>(HAlign_Fill, VAlign_Fill)
		{
		}
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

	/** Horizontal alignment of content in the area allotted to the SBox by its parent */
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

	/** Vertical alignment of content in the area allotted to the SBox by its parent */
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	/** Padding between the SBox and the content that it presents. Padding affects desired size. */
	SLATE_ATTRIBUTE(FMargin, Padding)

	/** The widget content presented by the SBox */
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
	void SetHAlign(const EHorizontalAlignment HAlign);

	/** See VAlign argument */
	void SetVAlign(const EVerticalAlignment VAlign);

	/** See Padding attribute */
	void SetPadding(const TAttribute<FMargin>& InPadding);

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

	FDesiredSizeBoxSlot ChildSlot;

private:
	/** Report content's desired width multiplied by WidthFactor. */
	TAttribute<FOptionalSize> WidthFactor;

	/** Report content's desired height multiplied by HeightFactor. */
	TAttribute<FOptionalSize> HeightFactor;
};
