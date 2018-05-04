#ifndef MAINMENU_H
#define MAINMENU_H

#include <gtkmm.h>
#include <iostream>
#include "CT_User.hpp"

class MainMenu : public Gtk::Window
{
    public:
        MainMenu();
        virtual ~MainMenu();

    protected:
        //signal handlers
        void coin_button_clicked();

        void amount_button_clicked();

        void holdings_button_clicked();

        void login();

        void createLoginDialog();

        CT_User* userObj;

        Gtk::Button coinNameButton;
        Gtk::Button coinNameButton2;
        Gtk::Button coinAmountButton;
        Gtk::Button loginButton;

        Gtk::Grid mainGrid;
        Gtk::Notebook selector;
        Gtk::Entry coinNameText;
        Gtk::Entry coinNameText2;
        Gtk::Entry coinAmountText;
        Gtk::Grid secondaryGrid;
        Gtk::Dialog* loginDialog;
        Gtk::Entry enterUsername;

    private:
};

#endif // MAINMENU_H
