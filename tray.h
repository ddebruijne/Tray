#ifndef TRAY_H
#define TRAY_H

struct tray_menu;

struct tray {
  const char *icon;
  char *tooltip;
  struct tray_menu *menu;
};

struct tray_menu {
  const char *text;
  int disabled;
  int checked;
  int checkbox;

  void (*cb)(struct tray_menu *);
  void *context;

  struct tray_menu *submenu;
};

void tray_update(struct tray *tray);

#endif /* TRAY_H */
