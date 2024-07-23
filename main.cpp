#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <list>
#include <fstream> // Tambahkan header untuk file handling
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
        saveToFile(); // Simpan ke file setiap kali buku ditambahkan
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
        saveToFile(); // Simpan ke file setiap kali buku dihapus
    }

    void displayBooks() {
        BookNode* temp = head;
        cout << "Daftar Buku:\n";
        cout << "----------------------------------------\n";
        while (temp != nullptr) {
            cout << "Judul    : " << temp->title << "\n";
            cout << "Pengarang: " << temp->author << "\n";
            cout << "ISBN     : " << temp->isbn << "\n";
            cout << "----------------------------------------\n";
            temp = temp->next;
        }
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore();
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
        string title, author, isbn;
        while (getline(file, title, ',') && getline(file, author, ',') && getline(file, isbn)) {
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
            cout << "Buku terakhir yang dikembalikan:\n";
            cout << "----------------------------------------\n";
            cout << "Judul    : " << topBook.title << "\n";
            cout << "Pengarang: " << topBook.author << "\n";
            cout << "----------------------------------------\n";
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore();
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
            cout << "Buku ditemukan:\n";
            cout << "----------------------------------------\n";
            cout << "Judul    : " << result->title << "\n";
            cout << "Pengarang: " << result->author << "\n";
            cout << "ISBN     : " << result->isbn << "\n";
            cout << "----------------------------------------\n";
        } else {
            cout << "Buku tidak ditemukan\n";
        }
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore();
    }

    BSTNode* searchRec(BSTNode* node, string isbn) {
        if (node == nullptr || node->isbn == isbn) return node;
        if (isbn < node->isbn) return searchRec(node->left, isbn);
        return searchRec(node->right, isbn);
    }

    void deleteNode(string isbn) {
        root = deleteRec(root, isbn);
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
            cout << "Buku yang terhubung dengan " << book << ":\n";
            cout << "----------------------------------------\n";
            for (const auto& b : adjList[book]) {
                cout << b << "\n";
            }
            cout << "----------------------------------------\n";
        } else {
            cout << "Tidak ada buku yang terhubung dengan " << book << "\n";
        }
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore();
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
            cout << "Jalur ditemukan dari " << start << " ke " << end << "\n";
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore();
            return;
        }
        for (const auto& b : g.adjList[book]) {
            if (!visited[b]) {
                q.push(b);
                visited[b] = true;
            }
        }
    }
    cout << "Tidak ada jalur ditemukan dari " << start << " ke " << end << "\n";
    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore();
}

void DFSUtil(Graph& g, string book, string end, unordered_map<string, bool>& visited) {
    visited[book] = true;
    if (book == end) {
        cout << "Jalur ditemukan dari start ke " << end << "\n";
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore();
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
    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore();
}

// Menu utama
void menu() {
    LinkedList ll;
    Queue q;
    Stack s;
    BST bst;
    Graph g;
    int choice;
    ll.loadFromFile(); // Muat data dari file saat program dimulai
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "Menu Manajemen Data Buku Perpustakaan\n";
        cout << "========================================\n";
        cout << "1. Manajemen Buku (Non-BST)\n";
        cout << "2. Manajemen Peminjam\n";
        cout << "3. Manajemen Buku (BST)\n";
        cout << "4. Manajemen Hubungan Buku (Graph)\n";
        cout << "5. Pencarian Jalur Keterhubungan\n";
        cout << "6. Keluar\n";
        cout << "========================================\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    system("cls");
                    cout << "\n========================================\n";
                    cout << "Manajemen Buku (Non-BST)\n";
                    cout << "========================================\n";
                    cout << "1. Tambah Buku\n";
                    cout << "2. Hapus Buku\n";
                    cout << "3. Tampilkan Semua Buku\n";
                    cout << "4. Kembali ke menu\n";
                    cout << "========================================\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                    if (subChoice == 1) {
                        string title, author, isbn;
                        cout << "Masukkan judul: ";
                        getline(cin, title);
                        cout << "Masukkan pengarang: ";
                        getline(cin, author);
                        cout << "Masukkan ISBN: ";
                        getline(cin, isbn);
                        ll.addBook(title, author, isbn);
                    } else if (subChoice == 2) {
                        string title;
                        cout << "Masukkan judul: ";
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
                    cout << "\n========================================\n";
                    cout << "Manajemen Peminjam\n";
                    cout << "========================================\n";
                    cout << "1. Tambah Peminjam Buku\n";
                    cout << "2. Proses Peminjaman Buku\n";
                    cout << "3. Kembalikan Buku\n";
                    cout << "4. Lihat Buku Terakhir yang Dikembalikan\n";
                    cout << "5. Kembali ke menu\n";
                    cout << "========================================\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                    if (subChoice == 1) {
                        int memberId;
                        string bookTitle;
                        cout << "Masukkan nomor anggota: ";
                        cin >> memberId;
                        cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                        cout << "Masukkan judul buku: ";
                        getline(cin, bookTitle);
                        q.enqueue(memberId, bookTitle);
                    } else if (subChoice == 2) {
                        q.dequeue();
                        cin.ignore();
                    } else if (subChoice == 3) {
                        string title, author;
                        cout << "Masukkan judul: ";
                        getline(cin, title);
                        cout << "Masukkan pengarang: ";
                        getline(cin, author);
                        s.push(title, author);
                    } else if (subChoice == 4) {
                        s.top();
                        cin.ignore();
                    }
                } while (subChoice != 5);
                break;
            }
            case 3: {
                int subChoice;
                do {
                    system("cls");
                    cout << "\n========================================\n";
                    cout << "Manajemen Buku (BST)\n";
                    cout << "========================================\n";
                    cout << "1. Tambah Buku\n";
                    cout << "2. Cari Buku\n";
                    cout << "3. Hapus Buku\n";
                    cout << "4. Kembali ke menu\n";
                    cout << "========================================\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                    if (subChoice == 1) {
                        string title, author, isbn;
                        cout << "Masukkan judul: ";
                        getline(cin, title);
                        cout << "Masukkan pengarang: ";
                        getline(cin, author);
                        cout << "Masukkan ISBN: ";
                        getline(cin, isbn);
                        bst.insert(title, author, isbn);
                    } else if (subChoice == 2) {
                        string isbn;
                        cout << "Masukkan ISBN: ";
                        getline(cin, isbn);
                        bst.search(isbn);
                    } else if (subChoice == 3) {
                        string isbn;
                        cout << "Masukkan ISBN: ";
                        getline(cin, isbn);
                        bst.deleteNode(isbn);
                    }
                } while (subChoice != 4);
                break;
            }
            case 4: {
                int subChoice;
                do {
                    system("cls");
                    cout << "\n========================================\n";
                    cout << "Manajemen Hubungan Buku (Graph)\n";
                    cout << "========================================\n";
                    cout << "1. Tambah Hubungan Buku\n";
                    cout << "2. Tampilkan Buku Terhubungan\n";
                    cout << "3. Kembali ke menu\n";
                    cout << "========================================\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                    if (subChoice == 1) {
                        string book1, book2;
                        cout << "Masukkan judul buku pertama: ";
                        getline(cin, book1);
                        cout << "Masukkan judul buku kedua: ";
                        getline(cin, book2);
                        g.addEdge(book1, book2);
                    } else if (subChoice == 2) {
                        string book;
                        cout << "Masukkan judul buku: ";
                        getline(cin, book);
                        g.displayConnectedBooks(book);
                    }
                } while (subChoice != 3);
                break;
            }
            case 5: {
                int subChoice;
                do {
                    system("cls");
                    cout << "\n========================================\n";
                    cout << "Pencarian Jalur Keterhubungan\n";
                    cout << "========================================\n";
                    cout << "1. Cari Jalur Keterhubungan (BFS)\n";
                    cout << "2. Cari Jalur Keterhubungan (DFS)\n";
                    cout << "3. Kembali ke menu\n";
                    cout << "========================================\n";
                    cout << "Pilih opsi: ";
                    cin >> subChoice;
                    cin.ignore(); // Tambahkan ini untuk mengabaikan karakter newline setelah input angka
                    if (subChoice == 1) {
                        string start, end;
                        cout << "Masukkan judul buku awal: ";
                        getline(cin, start);
                        cout << "Masukkan judul buku akhir: ";
                        getline(cin, end);
                        BFS(g, start, end);
                    } else if (subChoice == 2) {
                        string start, end;
                        cout << "Masukkan judul buku awal: ";
                        getline(cin, start);
                        cout << "Masukkan judul buku akhir: ";
                        getline(cin, end);
                        DFS(g, start, end);
                    }
                } while (subChoice != 3);
                break;
            }
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
