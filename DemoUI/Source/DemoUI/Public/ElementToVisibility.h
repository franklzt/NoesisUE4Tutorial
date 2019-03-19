// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DemoUI.h"

namespace DemoUI
{
	class ElementToVisibility : public Noesis::BaseValueConverter
	{
	public:
		bool TryConvert(Noesis::BaseComponent* value, const Noesis::Type* targetType, Noesis::BaseComponent*,
			Noesis::Ptr<Noesis::BaseComponent>& result)
		{
			if (targetType == Noesis::TypeOf<Noesis::Visibility>() && Noesis::Boxing::CanUnbox<bool>(value))
			{
				bool isVisible = Noesis::Boxing::Unbox<bool>(value);
				Noesis::Visibility resultValue = Noesis::Visibility::Visibility_Visible;
				resultValue = isVisible ? Noesis::Visibility::Visibility_Visible : Noesis::Visibility::Visibility_Hidden;
				result = Noesis::Boxing::Box(Noesis::Visibility(resultValue));
				return true;
			}
			return false;
		}

	private:
		NS_IMPLEMENT_INLINE_REFLECTION(ElementToVisibility, Noesis::BaseValueConverter)
		{
			NsMeta<Noesis::TypeId>("DemoUI.ElementToVisibility");
		}
	};
}

