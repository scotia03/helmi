#include<iostream>
#include<stdlib.h>

using namespace std;

struct Tree{
    char huruf;
    Tree *left;
    Tree *right;
};

Tree *node, *nodeBaru, *root = NULL, *current;

Tree *tambahNode(Tree *&current, char data)
{
    if (current == NULL)
    {
      current = new Tree;
      current->huruf = data;
      current->left = NULL;
      current->right = NULL;
    }
    else
    {
      if (data < current->huruf)
      {
        tambahNode(current->left, data);
      }
      else
      {
        tambahNode(current->right, data);
      }
    }

    return current;
}

/*void tambahChild(Tree *&current, char data)
{
    if(pos == "kiri")
    {
        parent->left = nodeBaru;
    }
    else
    {
        parent->right = nodeBaru;
    }

    if (pos == "kanan")
    {
      parent->right = nodeBaru;
    }
    else
    {
      parent->left = nodeBaru;
    }

    parent = nodeBaru;
}*/

void preOrder(Tree *current)
{
    if (current != NULL)
    {
      cout << " " << current->huruf;
      preOrder(current->left);
      preOrder(current->right);
    }
    cout << "\n";
}

void inOrder(Tree *current)
{
    // kiri parent kanan
    if (current != NULL)
    {
        inOrder(current->left);
        cout << " " << current->huruf;
        inOrder(current->right);
    }
}

void postOrder(Tree *current)
{
    // kiri kanan parent
    if (current != NULL)
    {
        postOrder(current->left);
        postOrder(current->right);
        cout << " " << current->huruf;
    }
}

void menu(int pilih)
{
    char data;
    Tree *inputan;
    switch(pilih)
    {
        case 1:
            cout << "Masukkan satu huruf : ";
            cin >> data;
            inputan = tambahNode(node, data);
            //tambahChild(inputan,"kiri");
            break;
        case 2: 
            cout << "Masukkan satu huruf : ";
            cin >> data;
            inputan = tambahNode(node, data);
            //tambahChild(inputan,"kanan");
            break;
        case 3: 
            preOrder(node);
            break;
        case 4: 
            inOrder(node);
            break;
        case 5: 
            postOrder(node);
            break;
        case 0: exit(0);break;
    }
}

int main()
{
    int pilih;
    do {
        cout << "1. Tambah Kiri" << endl;
        cout << "2. Tambah Kanan" << endl;
        cout << "3. Pre Order" << endl;
        cout << "4. In Order" << endl;
        cout << "5. Post Order" << endl;
        cout << "0. Exit" << endl;
        cout << "Masukkan pilihan : ";
        cin >> pilih;
        menu(pilih);
    }
    while(pilih != 0);
}