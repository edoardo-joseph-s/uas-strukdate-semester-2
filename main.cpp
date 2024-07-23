#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

// Struktur data untuk Linked List
struct BookNode {
    string title;
    string author;
    string isbn;
    BookNode* next;
    BookNode(string t, string a, string i) : title(t), author(a), isbn(i), next(nullptr) {}
};

class LinkedList {
public:
    BookNode* head;
    LinkedList() : head(nullptr) {}

    void addBook(string title, string author, string isbn) {
        BookNode* newBook = new BookNode(title, author, isbn);
        newBook->next = head;
        head = newBook;
        saveToFile();
    }

    void deleteBook(string title) {
        BookNode* temp = head;
        BookNode* prev = nullptr;
        while (temp != nullptr && temp->title != title) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) return;
        if (prev == nullptr) head = temp->next;
        else prev->next = temp->next;
        delete temp;
        saveToFile();
    }

    void displayBooks() {
        BookNode* temp = head;
        while (temp != nullptr) {
            cout << "Title: " << temp->title << ", Author: " << temp->author << ", ISBN: " << temp->isbn << endl;
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream file("books.txt");
        BookNode* temp = head;
        while (temp != nullptr) {
            file << temp->title << "," << temp->author << "," << temp->isbn << endl;
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("books.txt");
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            string title = line.substr(0, pos1);
            string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string isbn = line.substr(pos2 + 1);
            addBook(title, author, isbn);
        }
        file.close();
    }
};

// Struktur data untuk Queue
struct Borrow {
    int memberId;
    string bookTitle;
    Borrow(int id, string title) : memberId(id), bookTitle(title) {}
};

class Queue {
public:
    queue<Borrow> q;

    void enqueue(int memberId, string bookTitle) {
        q.push(Borrow(memberId, bookTitle));
    }

    void dequeue() {
        if (!q.empty()) q.pop();
    }
};

// Struktur data untuk Stack
struct ReturnedBook {
    string title;
    string author;
    ReturnedBook(string t, string a) : title(t), author(a) {}
};

class Stack {
public:
    stack<ReturnedBook> s;

    void push(string title, string author) {
        s.push(ReturnedBook(title, author));
    }

    void pop() {
        if (!s.empty()) s.pop();
    }

    void top() {
        if (!s.empty()) {
            ReturnedBook topBook = s.top();
            cout << "Last returned book - Title: " << topBook.title << ", Author: " << topBook.author << endl;
        }
    }
};

// Struktur data untuk Binary Search Tree
struct BSTNode {
    string title;
    string author;
    string isbn;
    BSTNode* left;
    BSTNode* right;
    BSTNode(string t, string a, string i) : title(t), author(a), isbn(i), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;
    BST() : root(nullptr) {}

    void insert(string title, string author, string isbn) {
        root = insertRec(root, title, author, isbn);
        saveToFile();
    }

    BSTNode* insertRec(BSTNode* node, string title, string author, string isbn) {
        if (node == nullptr) return new BSTNode(title, author, isbn);
        if (isbn < node->isbn) node->left = insertRec(node->left, title, author, isbn);
        else if (isbn > node->isbn) node->right = insertRec(node->right, title, author, isbn);
        return node;
    }

    void search(string isbn) {
        BSTNode* result = searchRec(root, isbn);
        if (result != nullptr) {
            cout << "Book found - Title: " << result->title << ", Author: " << result->author << ", ISBN: " << result->isbn << endl;
        } else {
            cout << "Book not found" << endl;
        }
    }

    BSTNode* searchRec(BSTNode* node, string isbn) {
        if (node == nullptr || node->isbn == isbn) return node;
        if (isbn < node->isbn) return searchRec(node->left, isbn);
        return searchRec(node->right, isbn);
    }

    void deleteNode(string isbn) {
        root = deleteRec(root, isbn);
        saveToFile();
    }

    BSTNode* deleteRec(BSTNode* root, string isbn) {
        if (root == nullptr) return root;
        if (isbn < root->isbn) root->left = deleteRec(root->left, isbn);
        else if (isbn > root->isbn) root->right = deleteRec(root->right, isbn);
        else {
            if (root->left == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }
            BSTNode* temp = minValueNode(root->right);
            root->isbn = temp->isbn;
            root->right = deleteRec(root->right, temp->isbn);
        }
        return root;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr) current = current->left;
        return current;
    }

    void saveToFile() {
        ofstream file("bst_books.txt");
        saveRec(file, root);
        file.close();
    }

    void saveRec(ofstream& file, BSTNode* node) {
        if (node != nullptr) {
            file << node->title << "," << node->author << "," << node->isbn << endl;
            saveRec(file, node->left);
            saveRec(file, node->right);
        }
    }

    void loadFromFile() {
        ifstream file("bst_books.txt");
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            string title = line.substr(0, pos1);
            string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string isbn = line.substr(pos2 + 1);
            insert(title, author, isbn);
        }
        file.close();
    }
};

// Struktur data untuk Graph
class Graph {
public:
    unordered_map<string, list<string>> adjList;

    void addEdge(string book1, string book2) {
        adjList[book1].push_back(book2);
        adjList[book2].push_back(book1);
    }

    void displayConnectedBooks(string book) {
        if (adjList.find(book) != adjList.end()) {
            cout << "Books connected to " << book << ": ";
            for (const auto& b : adjList[book]) {
                cout << b << " ";
            }
            cout << endl;
        } else {
            cout << "No books connected to " << book << endl;
        }
    }
};

// BFS dan DFS
void BFS(Graph& g, string start, string end) {
    unordered_map<string, bool> visited;
    queue<string> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        string book = q.front();
        q.pop();
        if (book == end) {
            cout << "Path found from " << start << " to " << end << endl;
            return;
        }
        for (const auto& b : g.adjList[book]) {
            if (!visited[b]) {
                q.push(b);
                visited[b] = true;
            }
        }
    }
    cout << "No path found from " << start << " to " << end << endl;
}

void DFSUtil(Graph& g, string book, string end, unordered_map<string, bool>& visited) {
    visited[book] = true;
    if (book == end) {
        cout << "Path found from start to " << end << endl;
        return;
    }
    for (const auto& b : g.adjList[book]) {
        if (!visited[b]) {
            DFSUtil(g, b, end, visited);
        }
    }
}

void DFS(Graph& g, string start, string end) {
    unordered_map<string, bool> visited;
    DFSUtil(g, start, end, visited);
}

// Menu utama
void menu() {
    LinkedList ll;
    Queue q;
    Stack s;
    BST bst;
    Graph g;
    ll.loadFromFile();
    bst.loadFromFile();
    int choice;
    do {
        system("cls");
        cout << "Menu Manajemen Data Buku Perpustakaan\n";
        cout << "1. Manajemen Buku\n";
        cout << "2. Manajemen Peminjam\n";
        cout << "3. Manajemen Hubungan Buku (Graph)\n";
        cout << "4. Pencarian Jalur Keterhubungan\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    system("cls");
                    cout << "1. Tambah Buku\n";
                    cout << "2. Hapus Buku\n";
                    cout << "3. Tampilkan Semua Buku\n";
                    cout << "4. Kembali ke menu\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    if (subChoice == 1) {
                        string title, author, isbn;
                        cout << "Masukkan judul: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Masukkan pengarang: ";
                        getline(cin, author);
                        cout << "Masukkan ISBN: ";
                        getline(cin, isbn);
                        ll.addBook(title, author, isbn);
                    } else if (subChoice == 2) {
                        string title;
                        cout << "Masukkan judul: ";
                        cin.ignore();
                        getline(cin, title);
                        ll.deleteBook(title);
                    } else if (subChoice == 3) {
                        ll.displayBooks();
                    }
                } while (subChoice != 4);
                break;
            }
            case 2: {
                int subChoice;
                do {
                    system("cls");
                    cout << "1. Tambah Peminjam Buku\n";
                    cout << "2. Proses Peminjaman Buku\n";
                    cout << "3. Kembalikan Buku\n";
                    cout << "4. Lihat Buku Terakhir yang Dikembalikan\n";
                    cout << "5. Kembali ke menu\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    if (subChoice == 1) {
                        int memberId;
                        string bookTitle;
                        cout << "Masukkan nomor anggota: ";
                        cin >> memberId;
                        cout << "Masukkan judul buku: ";
                        cin.ignore();
                        getline(cin, bookTitle);
                        q.enqueue(memberId, bookTitle);
                    } else if (subChoice == 2) {
                        q.dequeue();
                    } else if (subChoice == 3) {
                        string title, author;
                        cout << "Masukkan judul: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Masukkan pengarang: ";
                        getline(cin, author);
                        s.push(title, author);
                    } else if (subChoice == 4) {
                        s.top();
                    }
                } while (subChoice != 5);
                break;
            }
            case 3: {
                int subChoice;
                do {
                    system("cls");
                    cout << "1. Tambah Hubungan Buku\n";
                    cout << "2. Tampilkan Buku Terhubungan\n";
                    cout << "3. Kembali ke menu\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    if (subChoice == 1) {
                        string book1, book2;
                        cout << "Masukkan judul buku pertama: ";
                        cin.ignore();
                        getline(cin, book1);
                        cout << "Masukkan judul buku kedua: ";
                        getline(cin, book2);
                        g.addEdge(book1, book2);
                    } else if (subChoice == 2) {
                        string book;
                        cout << "Masukkan judul buku: ";
                        cin.ignore();
                        getline(cin, book);
                        g.displayConnectedBooks(book);
                    }
                } while (subChoice != 3);
                break;
            }
            case 4: {
                int subChoice;
                do {
                    system("cls");
                    cout << "1. Cari Jalur Keterhubungan (BFS)\n";
                    cout << "2. Cari Jalur Keterhubungan (DFS)\n";
                    cout << "3. Kembali ke menu\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    if (subChoice == 1) {
                        string start, end;
                        cout << "Masukkan judul buku awal: ";
                        cin.ignore();
                        getline(cin, start);
                        cout << "Masukkan judul buku akhir: ";
                        getline(cin, end);
                        BFS(g, start, end);
                    } else if (subChoice == 2) {
                        string start, end;
                        cout << "Masukkan judul buku awal: ";
                        cin.ignore();
                        getline(cin, start);
                        cout << "Masukkan judul buku akhir: ";
                        getline(cin, end);
                        DFS(g, start, end);
                    }
                } while (subChoice != 3);
                break;
            }
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}