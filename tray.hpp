#ifndef TRAY_H
#define TRAY_H

#include <string>
#include <vector>
#include <functional>

namespace Tray 
{
	struct TrayMenu
	{
		std::string text = "";
		bool isEnabled = true;
		bool isChecked = false;
		bool hasCheckbox = false;

		std::function<void(TrayMenu*)> onClicked = nullptr;
		std::vector<TrayMenu*> subMenu;
	};

	struct TrayIcon
	{
		std::string iconPath = "";
		std::string tooltip = "";

		std::vector<TrayMenu*> menu;
	};

	class TrayMaker
	{
	private:
		TrayIcon* trayIcon;

	public:
		bool Initialize(TrayIcon* toInitialize);
		bool Loop(bool blocking);
		void Update();
		void Exit();
	};
}


#endif /* TRAY_H */
