#include "LibrarySystem.h"
#include <iostream>
#include <limits>
using namespace std;

int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Enter a number.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void addBookAtIndex(CircularLinkedList& books) {
    int id = readInt("Enter Book ID: "); string title;
    cout << "Enter Book Title: "; getline(cin >> ws, title);
    int index = readInt("Enter index (0 to " + to_string(books.Size()) + "): ");
    books.InsertAt(CreateBook(id, title), index);
    cout << "Book added to circular collection.\n";
}

int main() {
    PriorityQueue requests;
    CircularLinkedList books;
    DoublyLinkedList session;
    int choice;

    // Existing sample circular collection retained.
    books.InsertAt(CreateBook(103, "Operating Systems"), 0);
    books.InsertAt(CreateBook(101, "Data Structures"), 1);
    books.InsertAt(CreateBook(105, "Computer Networks"), 2);
    books.InsertAt(CreateBook(102, "Database Systems"), 3);
    books.InsertAt(CreateBook(104, "Software Engineering"), 4);

    // Lab 7 sample borrowing session.
    session.InsertRight(new dNode(101, "Data Structures"));
    session.InsertRight(new dNode(102, "Database Systems"));
    session.InsertRight(new dNode(103, "Operating Systems"));

    do {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM =========="
             << "\n--- Lab 7: Doubly Linked Borrowing Session ---\n"
             << "1. Display Current Book\n2. Move to Next Book\n3. Move to Previous Book\n"
             << "4. Insert Book at the End\n5. Insert Book After Current Book\n6. Remove Current Book\n"
             << "7. Display Session from First to Last\n8. Display Session from Last to First\n9. Exit\n"
             << "\n--- Existing Library Project Features ---\n"
             << "10. Display All Circular Books\n11. Insert Book at Circular Head\n12. Remove Book from Circular Head\n"
             << "13. Insert Circular Book at Index\n14. Remove Circular Book at Index\n15. Swap Circular Books\n"
             << "16. Sort Circular Books by ID\n17. Reverse Circular Book Collection\n18. Move to Next Circular Book\n"
             << "19. Check Circular Collection Status\n20. Add Book Request\n21. Process Highest Priority Request\n"
             << "22. Display All Requests\n23. Check Request Queue Status\n";
        choice = readInt("Enter your choice: ");
        switch (choice) {
        case 1: session.PrintCurrent(); break;
        case 2: session.Next(); session.PrintCurrent(); break;
        case 3: session.Previous(); session.PrintCurrent(); break;
        case 4: {
            int id = readInt("Enter Book ID: "); string title;
            cout << "Enter Book Title: "; getline(cin >> ws, title);
            session.InsertRight(new dNode(id, title)); cout << "Book inserted at the end.\n"; break;
        }
        case 5: {
            int id = readInt("Enter Book ID: "); string title;
            cout << "Enter Book Title: "; getline(cin >> ws, title);
            session.InsertAfterCurrent(new dNode(id, title)); cout << "Book inserted after current book.\n"; break;
        }
        case 6: {
            dNode* removed = session.RemoveCurrent();
            if (!removed) cout << "Borrowing session is empty.\n";
            else { cout << "Removed book: " << removed->bookID << " - " << removed->title << '\n'; delete removed; }
            break;
        }
        case 7: session.PrintForward(); break;
        case 8: session.PrintBackward(); break;
        case 9: cout << "Exiting Library System.\n"; break;
        case 10: books.Print(); break;
        case 11: { int id=readInt("Enter Book ID: "); string title; cout<<"Enter Book Title: ";getline(cin>>ws,title);books.Insert(CreateBook(id,title));cout<<"Book inserted at circular head.\n";break; }
        case 12: { BookNode* b=books.Remove();if(!b)cout<<"Collection is empty.\n";else{cout<<"Removed: "<<b->bookID<<" - "<<b->title<<'\n';delete b;}break; }
        case 13: addBookAtIndex(books); break;
        case 14: { int i=readInt("Enter index to remove: ");BookNode*b=books.RemoveAt(i);if(!b)cout<<"Collection is empty.\n";else{cout<<"Removed: "<<b->bookID<<" - "<<b->title<<'\n';delete b;}break; }
        case 15: { int a=readInt("Enter first index: "),b=readInt("Enter second index: ");cout<<(books.Swap(a,b)?"Books swapped.\n":"Collection is empty.\n");break; }
        case 16: books.Sort(); cout<<"Books sorted by ID.\n"; break;
        case 17: books.Reverse(); cout<<"Book collection reversed.\n"; break;
        case 18: if(books.MoveNext())books.PrintCurrent();else cout<<"Collection is empty.\n";break;
        case 19: cout<<(books.IsEmpty()?"Collection is empty.\n":"Collection is not empty.\n")<<"Total books: "<<books.Size()<<"\nCircular link intact: "<<(books.IsEmpty()?"N/A":"YES")<<'\n';break;
        case 20: { BookRequestNode*r=new BookRequestNode{};r->studentID=readInt("Enter Student ID: ");cout<<"Enter Student Name: ";getline(cin>>ws,r->studentName);r->bookID=readInt("Enter Book ID: ");cout<<"Enter Book Title: ";getline(cin>>ws,r->bookTitle);r->priority=readInt("Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ");if(r->priority<1||r->priority>3){cout<<"Invalid priority; request not added.\n";delete r;}else{requests.Add(r);cout<<"Book request added successfully.\n";}break; }
        case 21: { BookRequestNode*r=requests.Remove();if(!r)cout<<"Request queue is empty.\n";else{cout<<"Processed request: "<<r->studentName<<" - "<<r->bookTitle<<" (priority "<<r->priority<<")\n";delete r;}break; }
        case 22: requests.PrintQueue(); break;
        case 23: cout<<(requests.IsEmpty()?"Request queue is empty.\n":"Request queue is not empty.\n");break;
        default: cout << "Invalid choice. Select 1-23.\n";
        }
    } while (choice != 9);
    return 0;
}
