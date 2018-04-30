#ifndef MAINMENU_H
#define MAINMENU_H

#include <gtkmm.h>
#include <iostream>

class MainMenu : public Gtk::Window
{
    public:
        MainMenu();
        virtual ~MainMenu();

    protected:
        //signal handlers
        void home_button_clicked();

        void exit_button_clicked();

        Gtk::Button coinNameButton;
        Gtk::Button coinAmountButton;
        Gtk::Grid mainGrid;
        Gtk::Notebook selector;
        Gtk::Entry coinNameText;
        Gtk::Entry coinNameText2;
        Gtk::Entry coinNameButton2;
        Gtk::Entry coinAmountText;
        Gtk::Grid secondaryGrid;

    private:
};

#endif // MAINMENU_H
