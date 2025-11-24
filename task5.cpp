#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // needed for remove_if

struct B {
    std::string title, author, isbn;
    bool available = true;
};

struct T {
    std::string borrower;
    std::string isbn;
};

std::vector<B> books;
std::vector<T> transactions;

void addBook() {
    B b;
    std::cout << "Enter title: ";
    std::getline(std::cin >> std::ws, b.title);

    std::cout << "Enter author: ";
    std::getline(std::cin, b.author);

    std::cout << "Enter ISBN: ";
    std::getline(std::cin, b.isbn);

    books.push_back(b);
    std::cout << "Book added.\n";
}

void searchBook() {
    std::string query;
    std::cout << "Search by title, author, or ISBN: ";
    std::getline(std::cin >> std::ws, query);

    for (const auto& b : books) {
        if (b.title == query || b.author == query || b.isbn == query) {
            std::cout << "Found: " << b.title 
                      << " by " << b.author 
                      << " (ISBN: " << b.isbn << ") "
                      << (b.available ? "Available" : "Not Available") 
                      << "\n";
            return;
        }
    }
    std::cout << "Not found.\n";
}

void checkoutBook() {
    std::string isbn, borrower;
    std::cout << "Enter ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    for (auto& b : books) {
        if (b.isbn == isbn && b.available) {
            std::cout << "Enter borrower name: ";
            std::getline(std::cin, borrower);

            transactions.push_back({ borrower, isbn });
            b.available = false;

            std::cout << "Checked out to " << borrower << ".\n";
            return;
        }
    }
    std::cout << "Not available or not found.\n";
}

void returnBook() {
    std::string isbn;
    std::cout << "Enter ISBN: ";
    std::getline(std::cin >> std::ws, isbn);

    for (auto& b : books) {
        if (b.isbn == isbn && !b.available) {
            b.available = true;

            transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
                [&](T& t) { return t.isbn == isbn; }),
                transactions.end());

            std::cout << "Book returned.\n";
            return;
        }
    }
    std::cout << "Not found or already returned.\n";
}

int main() {
    int choice;

    while (true) {
        std::cout << "\n1. Add Book\n2. Search Book\n3. Checkout Book\n4. Return Book\n5. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        std::cin.ignore(10000, '\n'); // clear leftover newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: return 0;
            default: std::cout << "Invalid choice.\n";
        }
    }
}
