# NoesisUE4Tutorial
Getting Start NoesisGUI for Unreal Engine

Just do it first, came back to ask why.


##Before you start:

1.Install Unreal Engine 4.21 from https://www.unrealengine.com/en-US/what-is-unreal-engine-4


2.DownLoad NoesisGUI 2.2.0 Unreal 4 Plugin from https://noesisengine.com/developers/downloads.php 


3.Install Microsoft Visual Studio 2017 include blend from https://docs.microsoft.com/en-us/visualstudio/releasenotes/vs2017-relnotes
<image src = "VSBlend.png">

## Let's get started:


## Blend Project section:
1.Create one WPF Project using Visual Studio 2017 and then Close the Visual Studio 2017


2.Find and  modify the MainWindow.xaml file  from  Window To UserControl.


3.Modify MainWindow.xaml.cs, also Window To UserControl.


4.Add new file name it ElementToVisibility.cs and add code below:

```
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Data;
using System.Windows;

namespace DemoUI
{
    public class ElementToVisibility : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool isVisible = (bool)value;

            Visibility visibility = (Visibility) parameter;

            if(isVisible)
            {
                visibility = Visibility.Visible;
            }
            else
            {
                visibility = Visibility.Hidden;
            }
            return visibility;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
```


5.Add one three button and three label to MainWindow.xaml. the finish code is like this.



```
<UserControl x:Class="DemoUI.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:DemoUI"
        mc:Ignorable="d"
         Height="1080" Width="1920">

    <UserControl.Resources>
        <local:ElementToVisibility x:Key="ElementToVisibility"/>
    </UserControl.Resources>
    
    <Grid Background="#FF7350D1">
        <Button Content="ButtonA" HorizontalAlignment="Left" Margin="350,100,0,0" VerticalAlignment="Top" Width="200" Height="100" Command="{Binding Start}"/>
        <Button Content="ButtonB" HorizontalAlignment="Left" Margin="350,300,0,0" VerticalAlignment="Top" Width="200" Height="100" Command="{Binding Setting}"/>
        <Button Content="ButtonC" HorizontalAlignment="Left" Margin="350,500,0,0" VerticalAlignment="Top" Width="200" Height="100" Command="{Binding Exit}"/>
        <Label Content="{Binding TitleA, Mode=TwoWay}" HorizontalAlignment="Left" Margin="600,100,0,0" VerticalAlignment="Top" FontSize="20"/>
        <Label Content="{Binding TitleB,Mode=TwoWay}" HorizontalAlignment="Left" Margin="600,300,0,0" VerticalAlignment="Top" FontSize="20"/>
        <Label Content="{Binding TitleC,Mode=TwoWay}" Visibility="{Binding ElementToVisibility, Converter={StaticResource ElementToVisibility}}"  HorizontalAlignment="Left" Margin="600,500,0,0" VerticalAlignment="Top" FontSize="20"/>
    </Grid>
</UserControl>

```


## Blueprint section:


1.Create Unreal Engine 4 Blank Project named DemoUI ( though this name is up to you,mine is this one, recommand using the name for easy to follow up)


2.Copy the downloaded NoesisGUI Plugin to Project Location.


3.Right Click the mouse with Unreal Project File to show content menu, choose Genereate the Visual Studio Project files command to intall the plugins.


4.Copy the whole WPF project to the folder under Unreal Project Content folder.


5.Create one blueprint, the parent class is NoesisView name it MainWindowView


6.Open blueprint MainWindowView under class setting to setup Noesis View xaml to MainWindow.xaml,click Enable PPAA.see picture.
<image src = "MainWindowView_StartFunction.png">
<image src = "MainWindowView_SettingFunction.png">
<image src = "MainWindowView_ExitFunction.png">
	
7.Create one new blueprint to project,parent class is Actor named SpawnNoesis,open it and add blueprint node as picture.
<image src = "MainWindowView_SpawnNoesis.png">

8.Drag the SpawnNoesis to map and then you can see the result.

## Coding section:


1.Open Unreal Project created from step 1.


2.Create one c++ file from menu to generate the build files.



3.Add code below to DemoUI.build.cs



```
 PrivateDependencyModuleNames.AddRange(new string[] { "Noesis", "NoesisRuntime" }); 
```



4.Add code to DemoUI.h


```
#include "NoesisRuntime.h
```


5.Add new file MainWindow.h to project.


6.Add the below code to MainWindow.h, 


```
#pragma once
#include"DemoUI.h"
namespace DemoUI
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow : public Noesis::UserControl
{
private:
    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Noesis::UserControl)
    {
        NsMeta<Noesis::TypeId>("DemoUI.MainWindow");
    }
};
}

```


10.Create new file named ElementToVisibility.h to project.


11.Add below code to ElementToVisibility.h :

```
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

```

12. replace below code to Demo.cpp


```
#include "DemoUI.h"
#include "Modules/ModuleManager.h"
#include "MainWindow.h"
#include "ElementToVisibility.h"

class DemoUIGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		NsRegisterComponent<DemoUI::ElementToVisibility>();
		NsRegisterComponent<DemoUI::MainWindow>();
	}

	virtual void ShutdownModule() override
	{
		NsUnregisterComponent<DemoUI::ElementToVisibility>();
		NsUnregisterComponent<DemoUI::MainWindow>();
	}
};
IMPLEMENT_PRIMARY_GAME_MODULE(DemoUIGameModule, DemoUI, "DemoUI" );

```


13. Compile the code project and return to Unreal Engine editor to run the demo.
<image src = "FinishA.png">
<image src = "FinishB.png">

## Now you know how to bring Noesis power to Unreal Engine 4