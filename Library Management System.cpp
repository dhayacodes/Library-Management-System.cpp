/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() const
    {
        cout << "\nBook ID     : " << bookID;
        cout << "\nTitle       : " << title;
        cout << "\nAuthor      : " << author;
        cout << "\nStatus      : ";

        if (issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << endl;
    }

    int getBookID() const
    {
        return bookID;
    }

    char* getTitle()
    {
        return title;
    }

    char* getAuthor()
    {
        return author;
    }

    bool isIssued() const
    {
        return issued;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }

    void writeToFile()
    {
        ofstream outFile("library.dat", ios::binary | ios::app);

        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));

        outFile.close();
    }

    static void displayAllBooks()
    {
        Book b;

        ifstream inFile("library.dat", ios::binary);

        if (!inFile)
        {
            cout << "\nNo records found.\n";
            return;
        }

        cout << "\n===== BOOK DETAILS =====\n";

        while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
        {
            b.displayBook();
            cout << "--------------------------\n";
        }

        inFile.close();
    }

    static bool searchBookByID(int id, Book &b)
    {
        ifstream inFile("library.dat", ios::binary);

        while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
        {
            if (b.bookID == id)
            {
                inFile.close();
                return true;
            }
        }

        inFile.close();
        return false;
    }

    static void updateBook(Book updatedBook)
    {
        fstream file("library.dat", ios::binary | ios::in | ios::out);

        Book b;

        while (file.read(reinterpret_cast<char*>(&b), sizeof(b)))
        {
            if (b.bookID == updatedBook.bookID)
            {
                int position = (-1) * sizeof(b);

                file.seekp(position, ios::cur);

                file.write(reinterpret_cast<char*>(&updatedBook), sizeof(updatedBook));

                break;
            }
        }

        file.close();
    }

    static void searchByTitle(const char searchTitle[])
    {
        Book b;
        bool found = false;

        ifstream inFile("library.dat", ios::binary);

        while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
        {
            if (strstr(b.title, searchTitle))
            {
                b.displayBook();
                cout << "--------------------------\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo book found with that title.\n";
        }

        inFile.close();
    }

    static void searchByAuthor(const char searchAuthor[])
    {
        Book b;
        bool found = false;

        ifstream inFile("library.dat", ios::binary);

        while (inFile.read(reinterpret_cast<char*>(&b), sizeof(b)))
        {
            if (strstr(b.author, searchAuthor))
            {
                b.displayBook();
                cout << "--------------------------\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo book found by that author.\n";
        }

        inFile.close();
    }
};

int main()
{
    int choice;

    do
    {
        cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search by Title\n";
        cout << "6. Search by Author\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Book b;

            b.addBook();
            b.writeToFile();

            cout << "\nBook Added Successfully.\n";
            break;
        }

        case 2:
        {
            Book::displayAllBooks();
            break;
        }

        case 3:
        {
            int id;

            cout << "\nEnter Book ID to Issue: ";
            cin >> id;

            Book b;

            if (Book::searchBookByID(id, b))
            {
                if (!b.isIssued())
                {
                    b.issueBook();

                    Book::updateBook(b);

                    cout << "\nBook Issued Successfully.\n";
                }
                else
                {
                    cout << "\nBook is already issued.\n";
                }
            }
            else
            {
                cout << "\nBook not found.\n";
            }

            break;
        }

        case 4:
        {
            int id;

            cout << "\nEnter Book ID to Return: ";
            cin >> id;

            Book b;

            if (Book::searchBookByID(id, b))
            {
                if (b.isIssued())
                {
                    b.returnBook();

                    Book::updateBook(b);

                    cout << "\nBook Returned Successfully.\n";
                }
                else
                {
                    cout << "\nBook was not issued.\n";
                }
            }
            else
            {
                cout << "\nBook not found.\n";
            }

            break;
        }

        case 5:
        {
            char title[50];

            cin.ignore();

            cout << "\nEnter Title to Search: ";
            cin.getline(title, 50);

            Book::searchByTitle(title);

            break;
        }

        case 6:
        {
            char author[50];

            cin.ignore();

            cout << "\nEnter Author Name to Search: ";
            cin.getline(author, 50);

            Book::searchByAuthor(author);

            break;
        }

        case 7:
        {
            cout << "\nThank You for Using Library System.\n";
            break;
        }

        default:
        {
            cout << "\nInvalid Choice.\n";
        }
        }

    } while (choice != 7);

    return 0;
}
