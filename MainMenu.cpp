
#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
    //sets up a new user
    userObj = new CT_User();

    // minimum screen size
    this->resize(400, 200);
    set_border_width(10);

    // initialize pages
    pageNum = 0;

    displayAll = false;

    // placeholder text
    coinNameText.set_placeholder_text("Coin Name");
    coinNameText2.set_placeholder_text("Coin Name");
    coinAmountText.set_placeholder_text("Coin Amount");
    username.set_placeholder_text("Username");

    // button labels
    switchUserButton.add_label("Switch User");
    coinNameButton.add_label("Submit");
    coinAmountButton.add_label("Submit");
    coinNameButton2.add_label("Submit");
    displayAllHoldings.add_label("Show All Coins");
    nextPage.add_label("Next");
    previousPage.add_label("Prev");

    // button size requests
    switchUserButton.set_size_request(150, 50);
    nextPage.set_size_request(150, 50);
    displayAllHoldings.set_size_request(150, 50);
    previousPage.set_size_request(150, 50);
    coinNameButton.set_size_request(150, 50);
    coinNameButton2.set_size_request(150, 50);
    coinAmountButton.set_size_request(150, 50);

    // singal handlers
    coinNameButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::coin_button_clicked));
    coinAmountButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::amount_button_clicked));
    coinNameButton2.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::holdings_button_clicked));
    displayAllHoldings.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::holdings_display_all));
    nextPage.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::navigate_next));
    previousPage.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::navigate_prev));
    switchUserButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::switchUser));

    // labels
    symbolLabel.set_text("Symbol:");
    symbolValue.set_text("");
    priceLabel.set_text("Price:");
    priceValue.set_text("");

    // page setup
    coinNameLabel.set_text("Coin Name");
    coinSymbolLabel.set_text("Coin Symbol");
    coinAmountLabel.set_text("Quantity");
    coinAddPriceLabel.set_text("Initial Price per Coin");
    coinAddTotalLabel.set_text("Total Initial Price");
    coinCurrentPriceLabel.set_text("Current Price per Coin");
    coinTotalPriceLabel.set_text("Total Current Price");

    // main grid attachments
    mainGrid.attach(coinNameText, 0, 0, 2, 1);
    mainGrid.attach(coinNameButton, 2, 0, 2, 1);

    mainGrid.attach(symbolLabel, 0, 1, 1, 1);
    mainGrid.attach(symbolValue, 1, 1, 1, 1);
    mainGrid.attach(priceLabel, 2, 1, 1, 1);
    mainGrid.attach(priceValue, 3, 1, 1, 1);

    mainGrid.attach(coinAmountText, 0, 2, 2, 1);
    mainGrid.attach(coinAmountButton, 2, 2, 2, 1);

    // secondary grid attachments
    secondaryGrid.attach(coinNameText2, 2, 0, 1, 1);
    secondaryGrid.attach(coinNameButton2, 3, 0, 1, 1);
    secondaryGrid.attach(displayAllHoldings, 4, 0, 1, 1);

    // third grid attachments
    thirdGrid.attach(username, 0, 0, 1, 1);
    thirdGrid.attach(switchUserButton, 1, 0, 1, 1);

    // page size requests
    coinNameLabel.set_size_request(150, 50);
    coinName1Label.set_size_request(150, 50);
    coinName2Label.set_size_request(150, 50);
    coinName3Label.set_size_request(150, 50);
    coinName4Label.set_size_request(150, 50);
    coinName5Label.set_size_request(150, 50);

    coinSymbolLabel.set_size_request(150, 50);
    coinSymbol1Label.set_size_request(150, 50);
    coinSymbol2Label.set_size_request(150, 50);
    coinSymbol3Label.set_size_request(150, 50);
    coinSymbol4Label.set_size_request(150, 50);
    coinSymbol5Label.set_size_request(150, 50);

    coinCurrentPriceLabel.set_size_request(150, 50);
    coinCurrentPrice1Label.set_size_request(150, 50);
    coinCurrentPrice2Label.set_size_request(150, 50);
    coinCurrentPrice3Label.set_size_request(150, 50);
    coinCurrentPrice4Label.set_size_request(150, 50);
    coinCurrentPrice5Label.set_size_request(150, 50);

    coinTotalPriceLabel.set_size_request(150, 50);
    coinTotalPrice1Label.set_size_request(150, 50);
    coinTotalPrice2Label.set_size_request(150, 50);
    coinTotalPrice3Label.set_size_request(150, 50);
    coinTotalPrice4Label.set_size_request(150, 50);
    coinTotalPrice5Label.set_size_request(150, 50);

    // page attachments
    secondaryGrid.attach(coinNameLabel, 0, 1, 1, 1);
    secondaryGrid.attach(coinSymbolLabel, 1, 1, 1, 1);
    secondaryGrid.attach(coinAmountLabel, 2, 1, 1, 1);
    secondaryGrid.attach(coinAddPriceLabel, 3, 1, 1, 1);
    secondaryGrid.attach(coinAddTotalLabel, 4, 1, 1, 1);
    secondaryGrid.attach(coinCurrentPriceLabel, 5, 1, 1, 1);
    secondaryGrid.attach(coinTotalPriceLabel, 6, 1, 1, 1);

    secondaryGrid.attach(coinName1Label, 0, 2, 1, 1);
    secondaryGrid.attach(coinSymbol1Label, 1, 2, 1, 1);
    secondaryGrid.attach(coinAmount1Label, 2, 2, 1, 1);
    secondaryGrid.attach(coinAddPrice1Label, 3, 2, 1, 1);
    secondaryGrid.attach(coinAddTotal1Label, 4, 2, 1, 1);
    secondaryGrid.attach(coinCurrentPrice1Label, 5, 2, 1, 1);
    secondaryGrid.attach(coinTotalPrice1Label, 6, 2, 1, 1);

    secondaryGrid.attach(coinName2Label, 0, 3, 1, 1);
    secondaryGrid.attach(coinSymbol2Label, 1, 3, 1, 1);
    secondaryGrid.attach(coinAmount2Label, 2, 3, 1, 1);
    secondaryGrid.attach(coinAddPrice2Label, 3, 3, 1, 1);
    secondaryGrid.attach(coinAddTotal2Label, 4, 3, 1, 1);
    secondaryGrid.attach(coinCurrentPrice2Label, 5, 3, 1, 1);
    secondaryGrid.attach(coinTotalPrice2Label, 6, 3, 1, 1);

    secondaryGrid.attach(coinName3Label, 0, 4, 1, 1);
    secondaryGrid.attach(coinSymbol3Label, 1, 4, 1, 1);
    secondaryGrid.attach(coinAmount3Label, 2, 4, 1, 1);
    secondaryGrid.attach(coinAddPrice3Label, 3, 4, 1, 1);
    secondaryGrid.attach(coinAddTotal3Label, 4, 4, 1, 1);
    secondaryGrid.attach(coinCurrentPrice3Label, 5, 4, 1, 1);
    secondaryGrid.attach(coinTotalPrice3Label, 6, 4, 1, 1);

    secondaryGrid.attach(coinName4Label, 0, 5, 1, 1);
    secondaryGrid.attach(coinSymbol4Label, 1, 5, 1, 1);
    secondaryGrid.attach(coinAmount4Label, 2, 5, 1, 1);
    secondaryGrid.attach(coinAddPrice4Label, 3, 5, 1, 1);
    secondaryGrid.attach(coinAddTotal4Label, 4, 5, 1, 1);
    secondaryGrid.attach(coinCurrentPrice4Label, 5, 5, 1, 1);
    secondaryGrid.attach(coinTotalPrice4Label, 6, 5, 1, 1);

    secondaryGrid.attach(coinName5Label, 0, 6, 1, 1);
    secondaryGrid.attach(coinSymbol5Label, 1, 6, 1, 1);
    secondaryGrid.attach(coinAmount5Label, 2, 6, 1, 1);
    secondaryGrid.attach(coinAddPrice5Label, 3, 6, 1, 1);
    secondaryGrid.attach(coinAddTotal5Label, 4, 6, 1, 1);
    secondaryGrid.attach(coinCurrentPrice5Label, 5, 6, 1, 1);
    secondaryGrid.attach(coinTotalPrice5Label, 6, 6, 1, 1);

    secondaryGrid.attach(previousPage, 2, 7, 1, 1);
    secondaryGrid.attach(nextPage, 4, 7, 1, 1);

    // show all elements
    mainGrid.show_all();
    secondaryGrid.show_all();
    thirdGrid.show_all();

    // set up three tab layout
    selector.append_page(mainGrid, "Home");
    selector.append_page(secondaryGrid, "Holdings");
    selector.append_page(thirdGrid, "Switch User");
    add(selector);
    show_all_children();

}

// creates a login dialog box to allow the user to login
void MainMenu::createLoginDialog() {
    loginDialog = new Gtk::Dialog();
    loginDialog->set_title("Login");
    loginDialog->set_modal(true);
    loginDialog->set_transient_for(*this);
    loginDialog->get_vbox()->add(enterUsername);
    loginButton.add_label("Login");
    loginButton.set_size_request(150, 50);
    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::login));
    loginDialog->get_vbox()->add(loginButton);
    loginButton.set_can_default();
    loginButton.grab_default();
    loginDialog->show_all_children();
    loginDialog->set_size_request(200, 80);
    loginDialog->run();
}

// looks up the current symbol and price of a coin
void MainMenu::coin_button_clicked() {
    std::string coinSym = CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw());
    if (coinSym == "") {
        // display coin not found dialog
        Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Invalid coin name");
        emptyMessage->set_modal(true);
        emptyMessage->set_transient_for(*this);
        emptyMessage->set_title("Invalid coin name");
        emptyMessage->set_size_request(200, 100);
        emptyMessage->show_all_children();
        emptyMessage->run();
        delete emptyMessage;
    } else {
        // output the current symbol and price of the coin
        symbolValue.set_text(coinSym);
        std::string coinPrice = CC_API_Calls::get_price(coinSym);
        priceValue.set_text("$" + coinPrice);
    }
}

// adds an amount of a given coin to the user's account
void MainMenu::amount_button_clicked() {
    if (userObj->isLoggedIn()) {
        if (coinNameText.get_text().raw().empty()) {
            // display empty dialog
            Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Please enter a coin name");
            emptyMessage->set_modal(true);
            emptyMessage->set_transient_for(*this);
            emptyMessage->set_title("Invalid coin name");
            emptyMessage->set_size_request(200, 100);
            emptyMessage->show_all_children();
            emptyMessage->run();
            delete emptyMessage;
        } else {
            try {
                double amt = std::stod(coinAmountText.get_text().raw());

                std::string coinSym = CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw());
                if (coinSym != "") {
                    // insert coin into database, and credit amount to user's account
                    userObj->add_coin(coinNameText.get_text().raw());
                    userObj->add_coinID(CC_API_Calls::get_coin_symbol(coinNameText.get_text().raw()), amt);
                    Gtk::MessageDialog *amtSuccess = new Gtk::MessageDialog("Coin added successfully");
                    amtSuccess->set_modal(true);
                    amtSuccess->set_transient_for(*this);
                    amtSuccess->set_title("Coin Success");
                    amtSuccess->set_size_request(200, 100);
                    amtSuccess->show_all_children();
                    amtSuccess->run();
                    delete amtSuccess;

                } else {
                    // display coin not found dialog
                    Gtk::MessageDialog *emptyMessage = new Gtk::MessageDialog("Invalid coin name");
                    emptyMessage->set_modal(true);
                    emptyMessage->set_transient_for(*this);
                    emptyMessage->set_title("Invalid coin name");
                    emptyMessage->set_size_request(200, 100);
                    emptyMessage->show_all_children();
                    emptyMessage->run();
                    delete emptyMessage;
                }
            } catch (int e) {
                // display invalid amount dialog
                Gtk::MessageDialog *invalidAmount = new Gtk::MessageDialog("Please enter a valid amount");
                invalidAmount->set_modal(true);
                invalidAmount->set_transient_for(*this);
                invalidAmount->set_title("Invalid Amount");
                invalidAmount->set_size_request(200, 100);
                invalidAmount->show_all_children();
                invalidAmount->run();
                delete invalidAmount;
            }

        }
    } else {
        createLoginDialog();
        amount_button_clicked();
    }
}

// clears all page arrays
void MainMenu::clear_arrays() {
    for (int i = 0; i < 5; i++) {
        coinNameArr[i] = "";
        coinSymArr[i] = "";
        coinAmtArr[i] = 0;
        coinAddPriceArr[i] = 0;
        coinAddTotalArr[i] = 0;
        coinCurrentPriceArr[i] = 0;
        coinTotalPriceArr[i] = 0;
    }
}

// displays user account results based on what coin is entered
void MainMenu::holdings_button_clicked() {
    if (userObj->isLoggedIn()) {
        clear_arrays();
        displayAll = false;
        pageNum = 0;
        sql::ResultSet* coins = userObj->user_coins();
        int i = 0;
        while (i < 5) {
            if (coins->next()) {
                int coinId = coins->getInt(1);
                std::string coinSym = userObj->coinid_symbol(coinId);
                std::string coinName = userObj->coin_name(coinSym);
                // if coin matches the name entered in the textbox, then it should be displayed
                if (coinName == coinNameText2.get_text().raw()) {
                    coinNameArr[i] = coinName;
                    coinSymArr[i] = coinSym;
                    coinAmtArr[i] = userObj->get_amount(coinId);
                    coinAddPriceArr[i] = userObj->start_price(coinId);
                    coinAddTotalArr[i] = userObj->start_worth(coinId);
                    coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                    coinTotalPriceArr[i] = userObj->curr_worth(coinId);
                    i++;
                }
            } else {
                // end of data table
                break;
            }
        }
        fill_values();
    } else {
        createLoginDialog();
        holdings_button_clicked();
    }
}

// clears all page values
void MainMenu::clear_all_values() {
    coinName1Label.set_text("");
    coinSymbol1Label.set_text("");
    coinAmount1Label.set_text("");
    coinAddPrice1Label.set_text("");
    coinAddTotal1Label.set_text("");
    coinCurrentPrice1Label.set_text("");
    coinTotalPrice1Label.set_text("");

    coinName2Label.set_text("");
    coinSymbol2Label.set_text("");
    coinAmount2Label.set_text("");
    coinAddPrice2Label.set_text("");
    coinAddTotal2Label.set_text("");
    coinCurrentPrice2Label.set_text("");
    coinTotalPrice2Label.set_text("");

    coinName3Label.set_text("");
    coinSymbol3Label.set_text("");
    coinAmount3Label.set_text("");
    coinAddPrice3Label.set_text("");
    coinAddTotal3Label.set_text("");
    coinCurrentPrice3Label.set_text("");
    coinTotalPrice3Label.set_text("");

    coinName4Label.set_text("");
    coinSymbol4Label.set_text("");
    coinAmount4Label.set_text("");
    coinAddPrice4Label.set_text("");
    coinAddTotal4Label.set_text("");
    coinCurrentPrice4Label.set_text("");
    coinTotalPrice4Label.set_text("");

    coinName5Label.set_text("");
    coinSymbol5Label.set_text("");
    coinAmount5Label.set_text("");
    coinAddPrice5Label.set_text("");
    coinAddTotal5Label.set_text("");
    coinCurrentPrice5Label.set_text("");
    coinTotalPrice5Label.set_text("");
}

// logs the user in
void MainMenu::login() {
    if (enterUsername.get_text() != "") {
        userObj = new CT_User(enterUsername.get_text().raw());
        userObj->login();
        delete loginDialog;
        clear_arrays();
        clear_all_values();
    }
}

// switches the user
void MainMenu::switchUser() {
    if (username.get_text() != "") {
        userObj->log_out(username.get_text().raw());
        clear_arrays();
        clear_all_values();
        Gtk::MessageDialog *userSuccess = new Gtk::MessageDialog("User switched successfully");
        userSuccess->set_modal(true);
        userSuccess->set_transient_for(*this);
        userSuccess->set_title("User Success");
        userSuccess->set_size_request(200, 100);
        userSuccess->show_all_children();
        userSuccess->run();
        delete userSuccess;

    } else {
        Gtk::MessageDialog *invalidUser = new Gtk::MessageDialog("Please enter a username");
        invalidUser->set_modal(true);
        invalidUser->set_transient_for(*this);
        invalidUser->set_title("Invalid User");
        invalidUser->set_size_request(200, 100);
        invalidUser->show_all_children();
        invalidUser->run();
        delete invalidUser;
    }
}

// displays all coins added to an account
void MainMenu::holdings_display_all() {
    if (userObj->isLoggedIn()) {
        clear_arrays();
        displayAll = true;
        pageNum = 0;
        sql::ResultSet* coins = userObj->user_coins();
        for (int i = 0; i < 5; i++) {
            if (coins->next()) {
                int coinId = coins->getInt(1);
                std::string coinSym = userObj->coinid_symbol(coinId);
                coinNameArr[i] = userObj->coin_name(coinSym);
                coinSymArr[i] = coinSym;
                coinAmtArr[i] = userObj->get_amount(coinId);
                coinAddPriceArr[i] = userObj->start_price(coinId);
                coinAddTotalArr[i] = userObj->start_worth(coinId);
                coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                coinTotalPriceArr[i] = userObj->curr_worth(coinId);
            } else {
                break;
            }
        }
        fill_values();
    } else {
        createLoginDialog();
    }

}

// fills the page values
void MainMenu::fill_values() {
    // nulls the values out first
    clear_all_values();

    if (coinNameArr[0] != "") {
        coinName1Label.set_text(coinNameArr[0]);
        coinSymbol1Label.set_text(coinSymArr[0]);
        coinAmount1Label.set_text(std::to_string(coinAmtArr[0]));
        coinAddPrice1Label.set_text("$" + std::to_string(coinAddPriceArr[0]));
        coinAddTotal1Label.set_text("$" + std::to_string(coinAddTotalArr[0]));
        coinCurrentPrice1Label.set_text("$" + std::to_string(coinCurrentPriceArr[0]));
        coinTotalPrice1Label.set_text("$" + std::to_string(coinTotalPriceArr[0]));
    }

    if (coinNameArr[1] != "") {
        coinName2Label.set_text(coinNameArr[1]);
        coinSymbol2Label.set_text(coinSymArr[1]);
        coinAmount2Label.set_text(std::to_string(coinAmtArr[1]));
        coinAddPrice2Label.set_text("$" + std::to_string(coinAddPriceArr[1]));
        coinAddTotal2Label.set_text("$" + std::to_string(coinAddTotalArr[1]));
        coinCurrentPrice2Label.set_text("$" + std::to_string(coinCurrentPriceArr[1]));
        coinTotalPrice2Label.set_text("$" + std::to_string(coinTotalPriceArr[1]));
    }

    if (coinNameArr[2] != "") {
        coinName3Label.set_text(coinNameArr[2]);
        coinSymbol3Label.set_text(coinSymArr[2]);
        coinAmount3Label.set_text(std::to_string(coinAmtArr[2]));
        coinAddPrice3Label.set_text("$" + std::to_string(coinAddPriceArr[2]));
        coinAddTotal3Label.set_text("$" + std::to_string(coinAddTotalArr[2]));
        coinCurrentPrice3Label.set_text("$" + std::to_string(coinCurrentPriceArr[2]));
        coinTotalPrice3Label.set_text("$" + std::to_string(coinTotalPriceArr[2]));
    }

    if (coinNameArr[3] != "") {
        coinName4Label.set_text(coinNameArr[3]);
        coinSymbol4Label.set_text(coinSymArr[3]);
        coinAmount4Label.set_text(std::to_string(coinAmtArr[3]));
        coinAddPrice4Label.set_text("$" + std::to_string(coinAddPriceArr[3]));
        coinAddTotal4Label.set_text("$" + std::to_string(coinAddTotalArr[3]));
        coinCurrentPrice4Label.set_text("$" + std::to_string(coinCurrentPriceArr[3]));
        coinTotalPrice4Label.set_text("$" + std::to_string(coinTotalPriceArr[3]));
    }

    if (coinNameArr[4] != "") {
        coinName5Label.set_text(coinNameArr[4]);
        coinSymbol5Label.set_text(coinSymArr[4]);
        coinAmount5Label.set_text(std::to_string(coinAmtArr[4]));
        coinAddPrice5Label.set_text("$" + std::to_string(coinAddPriceArr[4]));
        coinAddTotal5Label.set_text("$" + std::to_string(coinAddTotalArr[4]));
        coinCurrentPrice5Label.set_text("$" + std::to_string(coinCurrentPriceArr[4]));
        coinTotalPrice5Label.set_text("$" + std::to_string(coinTotalPriceArr[4]));
    }
}

// navigates to the next page
void MainMenu::navigate_next() {
    if (userObj->isLoggedIn()) {
        pageNum++;
        clear_arrays();
        sql::ResultSet* coins = userObj->user_coins();
        if (displayAll) {
            // pagenum * 5 will be the record we want to start from
            for (int i = 0; i < pageNum * 5; i++) {
                // if we hit the end of the array, then go back to the beginning
                if (!coins->next()) {
                    holdings_display_all();
                    break;
                }
            }

            for (int i = 0; i < 5; i++) {
                if (coins->next()) {
                    int coinId = coins->getInt(1);
                    std::string coinSym = userObj->coinid_symbol(coinId);
                    coinNameArr[i] = userObj->coin_name(coinSym);
                    coinSymArr[i] = coinSym;
                    coinAmtArr[i] = userObj->get_amount(coinId);
                    coinAddPriceArr[i] = userObj->start_price(coinId);
                    coinAddTotalArr[i] = userObj->start_worth(coinId);
                    coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                    coinTotalPriceArr[i] = userObj->curr_worth(coinId);
                } else {
                    break;
                }
            }
            fill_values();
        } else {
            int i = 0;
            while (i < 5 * pageNum) {
                if (coins->next()) {
                    int coinId = coins->getInt(1);
                    std::string coinSym = userObj->coinid_symbol(coinId);
                    std::string coinName = userObj->coin_name(coinSym);
                    if (coinName == coinNameText2.get_text().raw()) {
                        i++;
                    }
                } else {
                    holdings_button_clicked();
                    i = -1;
                    break;
                }
            }

            if (i != -1) {
                i = 0;

                while (i < 5) {
                    if (coins->next()) {
                        int coinId = coins->getInt(1);
                        std::string coinSym = userObj->coinid_symbol(coinId);
                        std::string coinName = userObj->coin_name(coinSym);
                        if (coinName == coinNameText2.get_text().raw()) {
                            coinNameArr[i] = coinName;
                            coinSymArr[i] = coinSym;
                            coinAmtArr[i] = userObj->get_amount(coinId);
                            coinAddPriceArr[i] = userObj->start_price(coinId);
                            coinAddTotalArr[i] = userObj->start_worth(coinId);
                            coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                            coinTotalPriceArr[i] = userObj->curr_worth(coinId);
                            i++;
                        }
                    } else {
                        break;
                    }
                }
                fill_values();
            }
        }
    } else {
        createLoginDialog();
    }
}

// navigates to the previous page
void MainMenu::navigate_prev() {
    if (userObj->isLoggedIn()) {
        pageNum--;
        // minimum page is 0
        if (pageNum < 0) {
            pageNum = 0;
        } else {
            clear_arrays();
            sql::ResultSet* coins = userObj->user_coins();
            if (displayAll) {
                // pagenum * 5 is the first record we want to be at
                for (int i = 0; i < pageNum * 5; i++) {
                    if (!coins->next()) {
                        holdings_display_all();
                        break;
                    }
                }

                for (int i = 0; i < 5; i++) {
                    if (coins->next()) {
                        int coinId = coins->getInt(1);
                        std::string coinSym = userObj->coinid_symbol(coinId);
                        coinNameArr[i] = userObj->coin_name(coinSym);
                        coinSymArr[i] = coinSym;
                        coinAmtArr[i] = userObj->get_amount(coinId);
                        coinAddPriceArr[i] = userObj->start_price(coinId);
                        coinAddTotalArr[i] = userObj->start_worth(coinId);
                        coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                        coinTotalPriceArr[i] = userObj->curr_worth(coinId);
                    } else {
                        break;
                    }
                }
                fill_values();
            } else {
                int i = 0;
                while (i < 5 * pageNum) {
                    if (coins->next()) {
                        int coinId = coins->getInt(1);
                        std::string coinSym = userObj->coinid_symbol(coinId);
                        std::string coinName = userObj->coin_name(coinSym);
                        if (coinName == coinNameText2.get_text().raw()) {
                            i++;
                        }
                    } else {
                        holdings_button_clicked();
                        i = -1;
                        break;
                    }
                }

                if (i != -1) {
                    i = 0;

                    while (i < 5) {
                        if (coins->next()) {
                            int coinId = coins->getInt(1);
                            std::string coinSym = userObj->coinid_symbol(coinId);
                            std::string coinName = userObj->coin_name(coinSym);
                            if (coinName == coinNameText2.get_text().raw()) {
                                coinNameArr[i] = coinName;
                                coinSymArr[i] = coinSym;
                                coinAmtArr[i] = userObj->get_amount(coinId);
                                coinAddPriceArr[i] = userObj->start_price(coinId);
                                coinAddTotalArr[i] = userObj->start_worth(coinId);
                                coinCurrentPriceArr[i] = userObj->curr_price(coinId);
                                coinTotalPriceArr[i] = userObj->curr_worth(coinId);
                                i++;
                            }
                        } else {
                            break;
                        }
                    }
                    fill_values();
                }
            }
        }
    } else {
        createLoginDialog();
    }

}


MainMenu::~MainMenu()
{
    //dtor
}
