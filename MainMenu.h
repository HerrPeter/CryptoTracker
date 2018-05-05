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

        void clear_all_values();

        void clear_arrays();

        void fill_values();

        void holdings_display_all();

        void navigate_next();

        void navigate_prev();

        void login();

        void createLoginDialog();

        void switchUser();

        CT_User* userObj;

        Gtk::Button coinNameButton;
        Gtk::Button coinNameButton2;
        Gtk::Button coinAmountButton;
        Gtk::Button loginButton;

        Gtk::Label symbolLabel;
        Gtk::Label symbolValue;

        Gtk::Label priceLabel;
        Gtk::Label priceValue;

        Gtk::Grid mainGrid;
        Gtk::Notebook selector;
        Gtk::Entry coinNameText;
        Gtk::Entry coinNameText2;
        Gtk::Entry coinAmountText;

        Gtk::Grid secondaryGrid;
        Gtk::Dialog* loginDialog;
        Gtk::Entry enterUsername;

        Gtk::Grid thirdGrid;
        Gtk::Entry username;
        Gtk::Button switchUserButton;

        Gtk::Label coinNameLabel;
        Gtk::Label coinSymbolLabel;
        Gtk::Label coinAmountLabel;
        Gtk::Label coinAddPriceLabel;
        Gtk::Label coinAddTotalLabel;
        Gtk::Label coinCurrentPriceLabel;
        Gtk::Label coinTotalPriceLabel;

        Gtk::Label coinName1Label;
        Gtk::Label coinSymbol1Label;
        Gtk::Label coinAmount1Label;
        Gtk::Label coinAddPrice1Label;
        Gtk::Label coinAddTotal1Label;
        Gtk::Label coinCurrentPrice1Label;
        Gtk::Label coinTotalPrice1Label;

        Gtk::Label coinName2Label;
        Gtk::Label coinSymbol2Label;
        Gtk::Label coinAmount2Label;
        Gtk::Label coinAddPrice2Label;
        Gtk::Label coinAddTotal2Label;
        Gtk::Label coinCurrentPrice2Label;
        Gtk::Label coinTotalPrice2Label;

        Gtk::Label coinName3Label;
        Gtk::Label coinSymbol3Label;
        Gtk::Label coinAmount3Label;
        Gtk::Label coinAddPrice3Label;
        Gtk::Label coinAddTotal3Label;
        Gtk::Label coinCurrentPrice3Label;
        Gtk::Label coinTotalPrice3Label;

        Gtk::Label coinName4Label;
        Gtk::Label coinSymbol4Label;
        Gtk::Label coinAmount4Label;
        Gtk::Label coinAddPrice4Label;
        Gtk::Label coinAddTotal4Label;
        Gtk::Label coinCurrentPrice4Label;
        Gtk::Label coinTotalPrice4Label;

        Gtk::Label coinName5Label;
        Gtk::Label coinSymbol5Label;
        Gtk::Label coinAmount5Label;
        Gtk::Label coinAddPrice5Label;
        Gtk::Label coinAddTotal5Label;
        Gtk::Label coinCurrentPrice5Label;
        Gtk::Label coinTotalPrice5Label;

        Gtk::Button displayAllHoldings;

        Gtk::Button nextPage;

        Gtk::Button previousPage;

        int pageNum;

        std::string coinNameArr[5];
        std::string coinSymArr[5];
        double coinAmtArr[5];
        double coinAddPriceArr[5];
        double coinAddTotalArr[5];
        double coinCurrentPriceArr[5];
        double coinTotalPriceArr[5];

        bool displayAll;

    private:
};

#endif // MAINMENU_H
