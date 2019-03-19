// Fill out your copyright notice in the Description page of Project Settings.

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
