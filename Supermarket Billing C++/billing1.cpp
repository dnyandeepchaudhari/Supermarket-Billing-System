#include <iostream>
#include <fstream> //FOR FILE HANDLING OPERATIONS - creating, writing and reading a file

using namespace std;

class shopping
{
private:
    int prdcode;
    float price;
    float prddis;
    string prdname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping ::menu()
{ // ' :: ' Scope resolution operator
m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t___________________________________________\n";
    cout << "\t\t\t\t                                           \n";
    cout << "\t\t\t\t           SUPERMARKET MAIN MENU           \n";
    cout << "\t\t\t\t                                           \n";
    cout << "\t\t\t\t___________________________________________\n\n";
    cout << "\t\t\t\t|             1. ADMINISTRATOR            |\n\n";
    cout << "\t\t\t\t|             2. BUYER                    |\n\n";
    cout << "\t\t\t\t|             3. EXIT                     |\n\n";
    cout << "\t\t\t\t Select from above!!!";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t Login Info";
        cout << "\t\t\t Enter Email : ";
        cin >> email;
        cout << "\t\t\t Enter Password : ";
        cin >> password;

        if (email == "deep@gmail.com" && password == "deep123")
        {
            administrator();
        }
        else
        {
            cout << "!! Invalid email & Password !!";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);
        break;

    default:
        cout << "Select from given options!!";
        break;
    }
    goto m; // JUMP STATEMENT, HELP US IN JUMPING TO THE MAIN MENU, WHERE 'm' IS A LABEL
}

void shopping ::administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu \n";
    cout << "\t\t\t|___1. Add the product_____|\n\n";
    cout << "\t\t\t|___2. Modify the product__|\n\n";
    cout << "\t\t\t|___3. Delete the product__|\n\n";
    cout << "\t\t\t|___4. Back to main menu___|\n\n";

    cout << "Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid Choice!!";
    }
    goto m;
}

void shopping ::buyer()
{
m:
    int choice;
    cout << "\t\t\t|____BUYER __________|\n\n";
    cout << "\t\t\t|____1. Buy product__|\n\n";
    cout << "\t\t\t|____2. Go Back______|\n\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << " Invalid Choice!!";
        break;
    }
    goto m;
}

void shopping ::add()
{
m:
    fstream data; // data is the name of the object
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t ---Add new product---";
    cout << "\n\n\t Enter product code : ";
    cin >> prdcode;
    cout << "\n\n\t Name of product : ";
    cin >> prdname;
    cout << "\n\n\t Discount on product : ";
    cin >> prddis;

    data.open("database.txt", ios::in);
    /*  '.open' opens the file
        ios::in will open a file in reading mode
        ios::out will open a file in writing mode
    */

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out); // ios::app stands for append mode and ios::out stands for writing mode
        data << " " << prdcode << " " << prdname << " " << price << " " << prddis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == prdcode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1)
        {
            goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out); // ios::app stands for append mode and ios::out stands for writing mode
            data << " " << prdcode << " " << prdname << " " << price << " " << prddis << "\n";
            data.close();
        }
    }
    cout << "\n\t\t\t Record Inserted !!";
}

void shopping ::edit()
{
    fstream data, data1;
    int prdkey;
    int token;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t___Modify Record___";
    cout << "\n\t\t\t Product code : ";
    cin >> prdkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n File Doesn't Exist !!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);

        data >> prdcode >> prdname >> price >> prddis;
        while (!data.eof())
        {
            if (prdkey == prdcode)
            {
                cout << "\n\t\t New product code : ";
                cin >> c;
                cout << "\n\t\t Name of product : ";
                cin >> n;
                cout << "\n\t\t Price of product : ";
                cin >> p;
                cout << "\n\t\t Product discount : ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\t\t Record Edited !!";
                token++;
            }
            else
            {
                data1 << " " << prdcode << " " << prdname << " " << price << " " << prddis << "\n";
            }
            data >> prdcode >> prdname >> price >> prddis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n\t\t Record not found !!";
        }
    }
}

void shopping ::rem()
{
    fstream data, data1;
    int prdkey;
    int token = 0;

    cout << "\n\t\t\t___Delete Product___";
    cout << "\n\t\t\t Product code : ";
    cin >> prdkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n File Doesn't Exist !!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);

        data >> prdcode >> prdname >> price >> prddis;
        while (!data.eof())
        {
            if (prdcode == prdkey)
            {
                cout << "\n\t\t Product Deleted Succesfully !! ";
                token++;
            }
            else
            {
                data1 << " " << prdcode << " " << prdname << " " << price << " " << prddis << "\n";
            }
            data >> prdcode >> prdname >> price >> prddis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n\t\t Record not found !!";
        }
    }
}

void shopping ::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|______________________________________________________|";
    cout << "PrdNo\t\tName\t\tPrice\n";
    cout << "\n\n|______________________________________________________|";
    data >> prdcode >> prdname >> price >> prddis;
    while(!data.eof()) {
        cout << prdcode << "\t\t" << prdname << "\t\t" << price << "\n";
        data >> prdcode >> prdname >> price >> prddis;
    }
    data.close();
}

void shopping ::receipt() {
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount;
    float prddis = 0;
    float total = 0;

    cout << "\n\n\t\t\t RECEIPT";
    data.open("database.txt", ios::in);
    if(!data) {
        cout << "\n\n\t\t\t Empty Database";
    }
    else {
        data.close();

        list();
        cout << "\n-----------------------------------------\n\n";
        cout << "                Place the Order             \n\n";
        cout << "\n-----------------------------------------\n\n";
        do{ // we have to run a specific type of code and the other part of the code is run based on the choice
            m:  
            cout << "\n\nEnter Product code : ";
            cin >> arrc[c];
            cout << "\n\nEnter Product Quantity : ";
            cin >> arrq[c];

            for(int i = 0; i < c; i++) {
                if(arrc[c] == arrc[i]) {
                    cout << "\n\nDuplicate product code. Please try aain !!!";
                    goto m;
                }
            }
            c++;
            cout << "\n\nDo you want to buy anothe product? If Yes then press y else no";
            cin >> choice;
        }
        while(choice == 'y');

        cout << "\n\n\t\t\t_________________________RECEIPT_________________________";
        cout << "\nProduct No\t Product Name\t\t Product Quantity\t Price\t Amount with Discount";

        for(int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> prdcode >> prdname >> price >> prddis;

            while(!data.eof()) {
                if(prdcode == arrc[i]) {
                    amount = price * arrq[i];
                    prddis = amount - (amount * prddis/100);
                    total = total + prddis;
                    cout << "\n" << prdcode << "\t\t" << prdname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << prddis;
                }
                data >> prdcode >> prdname >> price >> prddis;
            }
        }
        data.close();
    }
    cout << "\n\n__________________________________________________";
    cout << "\n Total Amount : " << total;
}

int main() {
    shopping s;
    s.menu();
}

