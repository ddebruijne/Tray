#include "tray.hpp"

using namespace Tray;

std::vector<TrayMenu*> menu;
TrayIcon tr = { "icon.png", "Hola!", menu };

int main()
{
	TrayMaker t;
	TrayMenu comPorts = { "COM ports", true, false, false, nullptr };
	for(int i = 0; i < 5; i++) {
		std::string comname = "COM";
		comname += (char)(i + '0');
		comPorts.subMenu.push_back(new TrayMenu { comname, true, false, false, [&](TrayMenu* tm){ 
		} });
	}

	tr.menu.push_back(new TrayMenu { "Tray App", false });
	tr.menu.push_back(new TrayMenu { "-" });
	tr.menu.push_back(&comPorts);
	tr.menu.push_back(new TrayMenu { "Exit", true, false, false, [&](TrayMenu* tm){ 
		t.Exit();
	} });

	t.Initialize(&tr);
	while(t.Loop(1)) {	}

	return 0;
}