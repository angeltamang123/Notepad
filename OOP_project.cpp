
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <stdlib.h>
using namespace std;
const int status=1;

void line()
{
    for (int i = 0; i < 168; i++)
        cout << "*";
}
char *retime()
{
    time_t now = time(0);
    char *cd = ctime(&now);
    return cd;
}

void mainMenu()
{
    cout << "\t\t\t\t\t " << retime();
    cout << "**************************************Hello!****************************************\n";
    cout << "*****************************************Welcome to notepad 0.0112*******************************************\n\n";
    cout << "****Please choose one of the options below****\n\n";
    cout << "< 1 >  Enter a new note\n";
    cout << "< 2 >  View all the notes till date\n";
    cout << "< 3 >  Modify a certain note\n";
    cout << "< 4 >  Delete a note\n ";
    cout << "< 5 >  View a certain note\n";
    cout << "< 6 >  Search notes\n";
    cout << "< 7 >  Exit\n\n";
}

void errorMessage()
{
    cout << "+++!!!You selected invalid number!!!+++\n";
}

void menuExit()
{
    cout << "\n\n\n\t***********************THANKS for using this PROGRAM!*************************************";
}

class project
{
private:
    int serial_no, a;
    char title[25], body[200];
    char T[25];

public:
    project(){serial_no=0;}
    
    class error_title
    {
    public:
        char *t;
        error_title(const char *msg)
        {
            t = new char[strlen(msg) + 1];
            strcpy(t, msg);
        }
    };

    class error_body
    {
    public:
        char *b;
        error_body(const char *msg)
        {
            b = new char[strlen(msg) + 1];
            strcpy(b, msg);
        }
    };

    void modifyget()
    {
        cout << " Enter the title: ";
        getchar(); 
        cin.getline(title, sizeof(title));
        serial_no=serial_no;
        strcpy(T, retime());
        if (strlen(title) == 0)
            throw error_title("please enter something as a Title!");
        if (strlen(title) > 25)
            throw error_title("Title should be below '25' characters!");
        cout << " Enter the body part: \n\t";
        cin.getline(body, sizeof(body));
        if (strlen(body) > 200)
            throw error_body("Body should be below '200' characters!");
    }  
    
    void getdata()
    {
        cout << " Enter the title: ";
        getchar(); 
        cin.getline(title, sizeof(title));
        serial_no+=status;
        strcpy(T, retime());
        if (strlen(title) == 0)
            throw error_title("please enter something as a Title!");
        if (strlen(title) > 25)
            throw error_title("Title should be below '25' characters!");
        cout << " Enter the body part: \n\t";
        cin.getline(body, sizeof(body));
        if (strlen(body) > 200)
            throw error_body("Body should be below '200' characters!");
    }

    void display()
    {
        cout << "\n\t" << serial_no << ".\tTitle: " << title << "\t\t" << T << endl
             << endl;
        cout << "\tBody: \n\t" << body << endl;
    }

    void upper()
    {
            for (int i = 0; i < strlen(title); i++)
                {
                    title[i] = toupper(title[i]);
                }
    }

    void update()
    {
        a++;
    }

   int reupdate()
   {
    return a;
   }

     char *retitle()
     {
         return title;
     }

    // char *rebody()
    // {
    //     return body;
    // }

    // char *reT()
    // {
    //     return T;
    // }

    project operator=(project obj)
        {
            return project(obj);
        }

    void write2file()
    {
        char c;
        fstream outfile;
        outfile.open("Notepad.dat", ios::binary | ios::app);
        if (!outfile)
        {
            cout << "cannot open file";
        }
        do
        {
            getdata();
            outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
            cout << "Do you have next note to enter or not?(y/n)";
            cin >> c;
        } while (c == 'y' || c == 'Y');
        outfile.close();
    }

    void readfromfile()
    {
        fstream infile;
        infile.open("Notepad.dat", ios::binary | ios::in);

        if (!infile)
        {
            cout << "files doesnot exist";
            return;
        }
        while (infile.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            display();
            line();
        }
        infile.close();
    }

    void modify()
    {
        int n;
        cout << "Enter note number to edit:";
        cin >> n;
        fstream outfile;
        outfile.open("Notepad.dat", ios::binary | ios::out | ios::in);
        outfile.seekg((n - 1) * sizeof(*this));
        outfile.read(reinterpret_cast<char *>(this), sizeof(*this));
        cout<< "this is the serial no: " <<serial_no;
        cout << "\n\n Enter new Note:\n";
        outfile.seekp((n - 1) * sizeof(*this));
        modifyget();
        outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
        outfile.close();
    }

    void deletenote()
    {
        int n;
        bool foundFlag = 0;
        cout << "Enter note number to delete:";
        cin >> n;
        ifstream infile("Notepad.dat", ios::binary);
        fstream tmpfile("temp.dat", ios::out | ios::binary);
        while (infile.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (n == serial_no)
            {
                foundFlag = true;
                continue;
            }
            else
            {

                serial_no = (foundFlag)? --serial_no : serial_no;
                tmpfile.write(reinterpret_cast<char *>(this), sizeof(*this));
            }
            display();
        }
        infile.close();
        tmpfile.close();
        remove("Notepad.dat");
        rename("temp.dat", "Notepad.dat");
    }

    void displaynote()
    {
        fstream infile;
        int n;
        infile.open("Notepad.dat", ios::binary | ios::in);
        infile.seekg(0, ios::end);
        int count = infile.tellg() / sizeof(project);

        cout << "There are " << count << " notes in this program" << endl;
        cout << "Enter note number";
        cin >> n;
        infile.seekg(sizeof(project) * (n - 1));
        infile.read(reinterpret_cast<char *>(this), sizeof(*this));
        display();
        infile.close();
    }

    void SEA()
    {
        char ti[25], titl[25];
        cout << "\n\n\t Enter the title's keywords";
        cin >> ti;
        for (int i = 0; i < strlen(ti); i++)
        {
            titl[i] = toupper(ti[i]);
        }

        fstream infile;
        infile.open("Notepad.dat", ios::binary | ios::in);
        infile.seekg(0, ios::end);
        int count = infile.tellg() / sizeof(project);
         
        project copy_here[count], sort_here[count], temp[count];
        infile.seekg(0);
        int i = 0;
        while (infile.read(reinterpret_cast<char *>(this), sizeof(*this))) // to transfer all the data to this new class with uppercased title
        {
            project tempSearch = *this;
            copy_here[i]=tempSearch;
            copy_here[i++].upper();
        }

        for (int i = 0; i < count; i++) // to assign certain numbers to each objects i.e. notes
        {
            char *ch;
            ch = copy_here[i].retitle();
            int a = 0;
            while (a < strlen(titl))
            {
                if (ch[a] == titl[a])
                {
                    a++;
                    copy_here[i].update();
                }
                else
                {
                    break;
                }
            }
        }

        int a = 0;
        for (int i = 0; i < count; i++, a++) /*to copy only title's keyword matching objects*/
        {
            while (copy_here[a].reupdate()== 0)
                a++;
            sort_here[i]=copy_here[a];
        }

        int si = sizeof(sort_here) / sizeof(sort_here[0]);
        for (int i = 0; i < si - 1; i++)
        {
            for (int j = i + 1; j < si; j++)
            {
                if (sort_here[i].reupdate() > sort_here[j].reupdate())
                {
                    temp[i] = sort_here[i];
                    sort_here[i] = sort_here[j];
                    sort_here[j] = temp[i];
                }
            }
        }

        for (int i = 0; i < si; i++)
        {
            cout << "\n\t The search results are: \n\t\t";
            sort_here[i].display();
            line();
        }
        infile.close();        
    }
};

int main()
{
    int i = 0; 
    int  choose, option;
    project p;
    try{ 
    while (i == 0)
    {
        system("cls");
        mainMenu(); //calling the main menu as UI
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << "Your Selection:\t";
        cin >> option;

        switch (option)
        {
        case 1:
            system("cls");
            p.write2file();
            break;
        case 2:
            system("cls");
            p.readfromfile();
            break;
        case 3:
            system("cls");
            p.modify();
            break;

        case 4:
            system("cls");
            p.deletenote();
            break;

        case 5:
            system("cls");
            p.displaynote();
            break;

        case 6:
            system("cls");
            p.SEA();
            break;
        case 7:
            system("cls");
            menuExit();
            return 0;

        default:
            errorMessage();
            break;
        }

        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        cout << "Would you like to perform other activities?:\n";
        cout << "< 1 > Yes\n";
        cout << "< 2 > No\n";
        cin >> choose;

        if (choose == 2)
        {
            i++;
            menuExit();
        }
    }
    }catch(project::error_title obj)
    {
        cout<<obj.t;
    }
    catch(project::error_body obj)
    {
        cout<<obj.b;
    }
    return 0;
}