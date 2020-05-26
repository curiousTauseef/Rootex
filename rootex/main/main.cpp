#include "common/common.h"

#include "app/application.h"
#include <Gwork/Renderers/DirectX11.h>

int main()
{
	Gwk::Color();

	Ref<Application> app = CreateRootexApplication();
	OS::Print(app->getAppTitle() + " is now starting. " + OS::GetBuildType() + " build (" + OS::GetBuildDate() + " | " + OS::GetBuildTime() + ")");
	app->run();
	app->shutDown();
	OS::Print(app->getAppTitle() + " is now safely exiting");

	return 0;
}
