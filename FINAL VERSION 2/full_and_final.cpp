/***************************************************
This Program demonstrates a Simple Banking System

//@authors:
    Aayush Dhakal
    Abhishek Poudel
    Sweing Nakarmi
    Aabhas Bhandari
    Aayush Sapkota

//Date of Creation: 19th August 2022
***************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

//***********************
//***** ACCOUNT CLASS****
//***********************

class Account
{
    // private:
    //     // double monthly_interest_rate;
    //     // double monthly_interest;

protected:
    double balance;
    double number_of_withdrawals;
    double number_of_deposits;
    double annual_interest_rate;
    double monthly_service_charges;

public:
    int account_num;
    
    //***********************************************************************
    // DEFAULT CONSTRUCTOR, SETS THE BALACE, NUMBER OF DEPOSITS, NUMBER OF WITHDRAWALS,
    // MONTHLY SERVICE CHARGES AND
    // ANNUAL INTEREST RATE TO ZERO 
    //***********************************************************************

    Account()
    {
        balance = 0;
        number_of_deposits = 0;
        number_of_withdrawals = 0;
        monthly_service_charges = 0;
        annual_interest_rate = 0;
    }

    //*******************************************************************************
    //PARAMETERIZED CONSTRUCTOR, ASSIGNS VALUES TO BALANCE AND ANNUAL INTEREST RATE *
    //*******************************************************************************

    Account(int acc, double bal, double air)
    {
        if (bal < 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Invalid! Starting Balance!!!* * *";
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Negative Value Encountered!!* * *\n";
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Terminating!!* * *\n";
            exit(0);
        }

        if (air < 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Invalid! Starting Balance!!!* * *";
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Negative Value Encountered!!* * *\n";
            std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Terminating!!* * *\n";
            exit(0);
        }
        account_num = acc;
        balance = bal;
        annual_interest_rate = air;
        number_of_deposits = 0;
        number_of_withdrawals = 0;
        monthly_service_charges = 0;
    }

    //****************************************
    //DISPLAYS ALL THE DATA MEMBERS **********
    //****************************************

    void display()
    {

        std::cout << account_num << std::setw(20) << balance << std::setw(17) << number_of_withdrawals << std::setw(20) << number_of_deposits << std::setw(20) << annual_interest_rate << std::endl;
    }

    //****************************************
    //ADDS DEPOSIT AMOUNT TO BALANCE *********
    //****************************************

    virtual void make_deposit(double d)
    {
        balance = balance + d;
        number_of_deposits += 1;
    }

    //*****************************************
    //SUBTRACTS WITHDRAWAL AMOUNT FROM BALANCE*
    //*****************************************

    virtual void make_withdrawal(double w)
    {
        balance = balance - w;
        number_of_withdrawals += 1;
    }

    //****************************************
    //ADDS MONTHLY INTEREST TO BALANCE *******
    //****************************************

    virtual void calc_int()
    {
        double monthly_interest_rate = (annual_interest_rate / 12);
        double monthly_interest = balance * monthly_interest_rate;
        balance = balance + monthly_interest;
    }

    //********************************************
    //DEDUCTS MONTHLY CHARGES AND SETS ***********
    //NUMBER OF WITHDRAWALS AND DEPOSITS TO ZERO**
    //********************************************

    virtual void monthly_proc()
    {
        balance = balance - monthly_service_charges;
        calc_int();
        number_of_deposits = 0;
        number_of_withdrawals = 0;
        monthly_service_charges = 0;
    }
};

//*********************
//**** SAVING CLASS ***
//*********************

class Saving : public Account
{
private:
    bool status;
    bool active;
    bool inactive;

public:
    void create_saving();
    void display_all();
    void delete_saving();
    virtual void make_withdrawal();
    virtual void make_deposit();
    virtual void monthly_proc();

    //****************************************
    //DEFUALT CONSTRUCTOR*********************
    //****************************************

    Saving()
    {
        active = true;
        inactive = false;
        if (balance > 25)
        {
            status = active;
        }
        else
        {
            status = inactive;
        }
    }

    //****************************************
    //PARAMETIRIZED CONSTRUCTOR***************
    //****************************************

    Saving(int acc, double b, double air) : Account(acc, b, air)
    {
        active = true;
        inactive = false;
        if (balance > 25)
        {
            status = active;
        }
        else
        {
            status = inactive;
        }
    }

    //****************************************
    //CHECKS THE STATUS OF THE ACCOUNT *******
    //****************************************

    bool statusCheck()
    {
        if (balance > 25)
        {
            status = active;
        }
        else
        {
            status = inactive;
        }
        return status;
    }
};

//****************************************
//FUNCTION TO INPUT THE ACCOUNT INFO *******
//****************************************

void Saving::create_saving()
{
    std::ofstream fout;
    int acc;
    double air, balance;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number => ";
    std::cin >> acc;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the balance => ";
    std::cin >> balance;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the annual interest rate => ";
    std::cin >> air;
    Saving s(acc, balance, air);
    fout.open("Accounts.dat", std::ios::app | std::ios::binary);
    if (s.balance > 25)
    {
        fout.write((char *)&s, sizeof(s));
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t##### Insufficient Balance!!! #####" << std::endl;
    }
    fout.close();
}

//****************************************
//FUNCTION TO DISPLAY ALL ACCOUNT INFO*******
//****************************************

void Saving::display_all()
{
    std::ifstream file;
    Saving x;
    file.open("Accounts.dat", std::ios::in);
    if (!file)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t##### ERROR IN OPENING FILE ##### \n";
    }
    else
    {
        std::cout << "=========================================================================================================================================================================================================" << std::endl;

        std::cout << std::setw(10) << "Account no" << std::setw(14) << "Balance" << std::setw(20) << "No. of Withdrawal" << std::setw(20) << "No. of Deposits" << std::setw(25) << "Annual Intrest Rate" << std::endl;

        std::cout
            << "=========================================================================================================================================================================================================" << std::endl;
        while (file.read((char *)&x, sizeof(x)))
        {
            x.display();
        }
        std::cout
            << "=========================================================================================================================================================================================================" << std::endl;
    }
    file.close();
}

//****************************************
//FUNCTION TO DELETE ACCOUNT**************
//****************************************

void Saving::delete_saving()
{
    int acc;
    Saving s;
    std::ofstream fout("temp.dat", std::ios::binary);
    std::ifstream fin("Accounts.dat", std::ios::binary);
    s.display_all();
    std::cout << "\n\n\t\t\t\t\t\t\t\t\t\tEnter Account Number to delete =>";
    std::cin >> acc;
    while (fin.read((char *)&s, sizeof(Account)))
    {
        if (acc != s.account_num)
        {
            fout.write((char *)&s, sizeof(Account));
        }
    }
    fin.close();
    fout.close();
    remove("Accounts.dat");
    rename("temp.dat", "Accounts.dat");
}

//****************************************
//IF STATUS IS ACTIVE WITHDRAWS AMOUNT*******
//****************************************

void Saving::make_withdrawal()
{
    Saving s;
    int f = 0;
    int acc;
    double w;
    bool status;
    std::fstream file1;
    file1.open("Accounts.dat", std::ios::binary | std::ios::in | std::ios::out);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry! Error in Opening the Records!!* * *";
    }

    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number =>";
        std::cin >> acc;
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the withdrawal amount =>";
        std::cin >> w;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.account_num == acc)
            {
                status = s.statusCheck();
                f = 1;
                if (status == active)
                {
                    file1.seekp(-sizeof(s), std::ios::cur);
                    s.Account::make_withdrawal(w);
                    file1.write((char *)&s, sizeof(s));
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Withdrawal Successfull!!!* * *" << std::endl;
                }

                else
                {
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Withdrawal failed!* * *" << std::endl;
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *The account is inactive !!* * *" << std::endl;
                }
            }
        }
    }

    if (f == 0)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry, Account Not Found!!* * *" << std::endl;
    }
    file1.close();
}

//****************************************
//DEPOSITS AMOUNT TO THE ACCOUNT***********
//****************************************

void Saving ::make_deposit()
{
    Saving s;
    int f = 0;
    int acc, d;
    bool status;
    std::fstream file1;
    file1.open("Accounts.dat", std::ios::binary | std::ios::in | std::ios::out);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry! Error in Opening the File!!!* * *" << std::endl;
    }

    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number: ";
        std::cin >> acc;
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the deposit amount: ";
        std::cin >> d;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.account_num == acc)
            {
                status = s.statusCheck();
                f = 1;
                if (status == active)
                {
                    file1.seekp(-sizeof(s), std::ios::cur);
                    s.Account::make_deposit(d);
                    file1.write((char *)&s, sizeof(s));
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Deposit Successful!!!* * *" << std::endl;
                }

                else
                {
                    if ((s.balance + d) > 25)
                    {
                        file1.seekp(-sizeof(s), std::ios::cur);
                        s.Account::make_deposit(d);
                        file1.write((char *)&s, sizeof(s));
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Deposit Successfull!!!* * *" << std::endl;
                        s.statusCheck();
                    }

                    else
                    {
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry! Not Enough Balance!* * *" << std::endl;
                    }
                }
            }
        }
    }

    if (f == 0)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry, Account Not Found!!* * *" << std::endl;
    }

    file1.close();
}

//**********************************************
//INITIALISED AT THE END OF THE MONTH***********
//CALLS THE BASE CLASS VERSION OF THE FUNCTION**
//**********************************************

void Saving ::monthly_proc()
{
    Saving s;

    std::ofstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    std::ifstream file1("Accounts.dat", std::ios::binary);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Sorry! Error in Opening the Records!!* * *" << std::endl;
    }

    else
    {
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.number_of_withdrawals > 4)
            {
                s.monthly_service_charges += (1.0 * (s.number_of_withdrawals - 4.0));
            }

            s.Account::monthly_proc();

            tempFile.write((char *)&s, sizeof(s));
            s.statusCheck();
        }
    }

    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *MONTHLY UPDATES UPDATED!!* * *" << std::endl;
    system("PAUSE");
    file1.close();
    tempFile.close();
    remove("Accounts.dat");
    rename("temp.dat", "Accounts.dat");
}

//*********************
//CHECKING CLASS*******
//*********************
class Checking : public Account
{
private:
    double own;

public:
    void delete_Checking();
    void create_checking();
    void make_deposit();
    void make_withdrawal();
    void monthly_proc();
    void display_all();

    //****************************************
    //PARAMETERIZED CONSTRUCTOR *******
    //****************************************

    Checking(int acc, double b, double air) : Account(acc, b, air)
    {
        own = 0.0;
    }

    //****************************************
    //DEFAULT CONSTRUCTOR ********************
    //****************************************

    Checking()
    {
        balance = 0;
        number_of_deposits = 0;
        number_of_withdrawals = 0;
        monthly_service_charges = 0;
        annual_interest_rate = 0;
    }
};

    //****************************************
    //DISPLAYS ALL *******
    //****************************************

void Checking::display_all()
{
    std::ifstream file;
    Checking x;
    file.open("Checking.dat", std::ios::in);
    if (!file)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *ERROR IN OPENING FILE * * * \n";
    }
    else
    {
        std::cout << "=========================================================================================================================================================================================================" << std::endl;

        std::cout << std::setw(10) << "Account no" << std::setw(14) << "Balance" << std::setw(20) << "No. of Withdrawal" << std::setw(20) << "No. of Deposits" << std::setw(25) << "Annual Intrest Rate" << std::endl;

        std::cout
            << "=========================================================================================================================================================================================================" << std::endl;

        while (file.read((char *)&x, sizeof(x)))
        {
            x.display();
        }
        std::cout
            << "=========================================================================================================================================================================================================" << std::endl;
    }
    file.close();
}

//****************************************
//DEPOSITS AMOUNT *******
//****************************************

void Checking ::make_deposit()
{
    Checking s;
    int f = 0;
    int acc;
    double d;
    bool status;
    std::fstream file1;
    file1.open("Checking.dat", std::ios::binary | std::ios::in | std::ios::out);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Sorry! Error in Opening the File!!!* * *" << std::endl;
    }

    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number => ";
        std::cin >> acc;
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the deposit amount =>";
        std::cin >> d;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.account_num == acc)
            {

                f = 1;

                file1.seekp(-sizeof(s), std::ios::cur);
                s.Account::make_deposit(d);
                file1.write((char *)&s, sizeof(s));
                std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Deposit Successful!!!* * *" << std::endl;
                break;
            }
        }
    }
    if (f == 0)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Sorry, Account Not Found!! * * *" << std::endl;
    }

    file1.close();
}

//****************************************
//WITHDRAWS AMOUNT *********************
//****************************************

void Checking::make_withdrawal()
{
    Checking s;
    int f = 0;
    int acc;
    double w;
    std::fstream file1;
    file1.open("Checking.dat", std::ios::binary | std::ios::in | std::ios::out);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Sorry! Error in Opening the Records!!* * *";
    }

    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number =>";
        std::cin >> acc;
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the withdrawal amount =>";
        std::cin >> w;
        while (file1.read((char *)&s, sizeof(s)))
        {
            if (s.account_num == acc)
            {
                f = 1;
                if (s.balance > w)
                {

                    file1.seekp(-sizeof(s), std::ios::cur);
                    s.Account::make_withdrawal(w);
                    file1.write((char *)&s, sizeof(s));
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Withdrawal Successfull!!! * * *" << std::endl;
                }
                else
                {
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Withdrawal Failed * * *" << std::endl;
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * Insufficient Balance * * *" << std::endl;
                    s.balance -= 15;
                    file1.seekp(-sizeof(s), std::ios::cur);
                    file1.write((char *)&s, sizeof(s));
                }
            }
        }
    }

    if (f == 0)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tSorry, Account Not Found!!" << std::endl;
    }
    file1.close();
}

//****************************************
//END OF MONTH *************************
//****************************************

void Checking ::monthly_proc()
{
    Checking s;

    std::ofstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    std::ifstream file1("Checking.dat", std::ios::binary);
    file1.seekg(0);

    if (!file1)
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tSorry! Error in Opening the Records!!" << std::endl;
    }

    else
    {
        while (file1.read((char *)&s, sizeof(s)))
        {
            s.monthly_service_charges += 5.0;
            s.monthly_service_charges += (0.1 * number_of_withdrawals);

            s.Account::monthly_proc();

            tempFile.write((char *)&s, sizeof(s));
        }
    }

    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * MONTHLY Amount UPDATED!! * * *\t\t\t\t\t\t\t\t\t\t" << std::endl;
    system("PAUSE");
    file1.close();
    tempFile.close();
    remove("Checking.dat");
    rename("temp.dat", "Checking.dat");
}

//****************************************
//INPUTS ACCOUNT INFO*******
//****************************************

void Checking::create_checking()
{
    std::ofstream fout;
    int acc;
    double air, balance;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the account number\n\t\t\t\t\t\t\t\t\t\t=>";
    std::cin >> acc;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the balance\n\t\t\t\t\t\t\t\t\t\t=>";
    std::cin >> balance;
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter the annual interest rate\n\t\t\t\t\t\t\t\t\t\t=>";
    std::cin >> air;
    Checking s(acc, balance, air);
    fout.open("Checking.dat", std::ios::app | std::ios::binary);
    fout.write((char *)&s, sizeof(s));
    fout.close();
}

void Checking::delete_Checking()
{
    int acc;
    Checking s;
    std::ofstream fout("temp.dat", std::ios::binary);
    std::ifstream fin("Checking.dat", std::ios::binary);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Enter Account Number to delete =>";
    std::cin >> acc;
    while (fin.read((char *)&s, sizeof(Account)))
    {
        if (acc != s.account_num)
        {
            fout.write((char *)&s, sizeof(Account));
        }
    }
    fin.close();
    fout.close();
    remove("Checking.dat");
    rename("temp.dat", "Checking.dat");
}

//****************************************
//MAIN FUNCTION *******
//****************************************

int main()
{
    int i;

    std::string username, password;

L:

    std::cout << "\n\n=========================================================================================================================================================================================================";
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t"
              << "* * * *  T. B. C  BANK * * * * ";
    std::cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t"
              << "* Login Page *"
              << std::endl;
    std::cout << "=========================================================================================================================================================================================================";
    std::cout << "\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t\t\t\t\t\tUsername: ";
    std::cin >> username;
    std::cout << "\t\t\t\t\t\t\t\t\t\t\tPassword: ";
    std::cin >> password;
    if (username == "admin" && password == "admin")
    {
        std::cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t* * * * * ACCESS GRANTED!!! * * * * *\n\n\n\n";
        std::cout << "\t\t\t\t\t\t\t\t\t\t" << system("PAUSE");
        system("CLS");
    A:
        int type;
        system("cls");
        std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * * SELECT ACCOUNT TYPE * * *\n\n "
                  << "\n\t\t\t\t\t\t\t\t\t\t\t1) Saving Account  \n\n\n\t\t\t\t\t\t\t\t\t\t\t2) Checking Account"
                  << "\n\n\n\n\t\t\t\t\t\t\t\t\tSelect your option => ";
        std::cin >> type;

        char ch;
        if (type == 1)
        {
            Saving menu;

            do
            {
                int n;
                system("CLS");
                std::cout << "\n\n\t\t\t\t\t\t\t\t\t* * * ENTER CHOICE FOR (SAVING ACCOUNT)* * *\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t1)CREATE ACCOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t2)DEPOSIT AMOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t3)WITHDRAW AMOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t4)CLOSE ACCOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t5)CHECK ACCOUNT INFO\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t6)END OF MONTH\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t7)CHOOSE ACCOUNT TYPE\n\n\n\n";
                std::cout << "\n\n\t\t\t\t\t\t\t\t\tEnter your Choice => ";
                std::cin >> n;
                switch (n)
                {
                case 1:
                    menu.create_saving();
                    break;
                case 2:
                    menu.make_deposit();
                    break;
                case 3:
                    menu.make_withdrawal();
                    break;
                case 4:
                    menu.delete_saving();
                    break;
                case 5:
                    menu.display_all();
                    break;
                case 6:
                    menu.monthly_proc();
                    break;

                case 7:
                    goto A;
                    break;
                default:
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t##### Invalid Choice #####\n";
                    break;
                }
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tDo you want to continue ? (Y/N) => ";
                std::cin >> ch;
            } while (ch == 'Y' || ch == 'y');
        }

        else if (type == 2)
        {
            Checking menu;

            do
            {
                int n;
                system("CLS");
                std::cout << "\n\n\t\t\t\t\t\t\t\t\t* * * ENTER CHOICE FOR (CHECKING ACCOUNT)* * *\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t1)CREATE ACCOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t2)DEPOSIT AMOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t3)WITHDRAW AMOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t4)CLOSE ACCOUNT\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t5)CHECK ACCOUNT INFO\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t6)END OF MONTH\n\n"
                          << "\t\t\t\t\t\t\t\t\t\t7)CHOOSE ACCOUNT TYPE\n\n\n\n";
                std::cout << "\n\n\t\t\t\t\t\t\t\tEnter your Choice => ";
                std::cin >> n;
                switch (n)
                {
                case 1:
                    menu.create_checking();
                    break;
                case 2:
                    menu.make_deposit();
                    break;
                case 3:
                    menu.make_withdrawal();
                    break;
                case 4:
                    menu.delete_Checking();
                    break;
                case 5:
                    menu.display_all();
                    break;
                case 6:
                    menu.monthly_proc();
                    break;
                case 7:
                    goto A;
                    break;
                default:
                    std::cout << "\n\t\t\t\t\t\t\t\t\t\t* * *Invalid Choice * * *\n";
                    break;
                }
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tDo you want to continue ? (Y/N) => ";
                std::cin >> ch;
            } while (ch == 'Y' || ch == 'y');
        }
    }

    else
    {
        system("CLS");
        std::cout << "\t\t\t\t\t\t\t\t\t# # # # # Invalid ! Username and Password # # # # #\n";
        goto L;
    }

    return 0;
}
