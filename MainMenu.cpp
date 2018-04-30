#include "MainMenu.h"

MainMenu::MainMenu()
{
    this->resize(400, 200);
    set_border_width(10);

    coinNameText.set_placeholder_text("Coin Name");
    coinNameText2.set_placeholder_text("Coin Name");
    coinAmountText.set_placeholder_text("Coin Amount");



    coinNameButton.add_label("Submit");
    coinAmountButton.add_label("Submit");
    coinNameButton.set_size_request(150, 50);
    coinNameButton2.set_size_request(150, 50);
    coinAmountButton.set_size_request(150, 50);

    coinNameButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::coin_button_clicked));
    coinAmountButton.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::amount_button_clicked));
    coinNameButton2.signal_clicked().connect(sigc::mem_fun(*this, &MainMenu::holdings_button_clicked));

    mainGrid.attach(coinNameButton, 1, 0, 1, 1);
    mainGrid.attach(coinAmountButton, 1, 1, 1, 1);
    mainGrid.attach(coinNameText, 0, 0, 1, 1);
    mainGrid.attach(coinAmountText, 0, 1, 1, 1);

    secondaryGrid.attach(coinNameText2, 0, 0, 1, 1);
    secondaryGrid.attach(coinNameButton2, 1, 0, 1, 1);


    //mainGrid.add(homeButton);
    //mainGrid.add(exitButton);

    mainGrid.show_all();
    secondaryGrid.show_all();

    selector.append_page(mainGrid, "Home");
    selector.append_page(secondaryGrid, "Holdings");
    add(selector);
    show_all_children();
}

void MainMenu::coin_button_clicked() {
    std::cout << "Perform coin lookup" << std::endl;

    //CC_API_Calls::get_coin_symbol(coinNameText.get_text());
}

void MainMenu::amount_button_clicked() {
    std::cout << "Perform amount addition" << std::endl;
}

void MainMenu::holdings_button_clicked() {
    std::cout << "Perform holdings action" << std::endl;
}


MainMenu::~MainMenu()
{
    //dtor
}
