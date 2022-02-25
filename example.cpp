#include "tray.hpp"
#include <iostream>

using namespace Tray;

std::vector<TrayMenu*> menu;
TrayIcon tr = { "icon.png", "icon.ico", "Hola!", menu };

int main()
{
	TrayMenu comPorts = { "Serial Port", true, false, false, nullptr };
	for(int i = 0; i < 5; i++) {
		std::string comname = "COM";
		comname += (char)(i + '0');
		comPorts.subMenu.push_back(new TrayMenu { comname, true, false, false, [&](TrayMenu* tm){ 
			for (TrayMenu* t : comPorts.subMenu)
			{
				t->isChecked = false;
			}

			tm->isChecked = true;

			trayMaker.Update();
		} });
	}

	tr.menu.push_back(new TrayMenu { "Tray App", false });
	tr.menu.push_back(new TrayMenu { "-" });
	tr.menu.push_back(&comPorts);
	tr.menu.push_back(new TrayMenu { "Exit", true, false, false, [&](TrayMenu* tm){ 
		trayMaker.Exit();
	} });

	if (trayMaker.Initialize(&tr))
		while(trayMaker.Loop(1)) {	}
	else
		std::cout << "initialization failed" << std::endl;

	return 0;
}