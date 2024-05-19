#include <bits/stdc++.h>
using namespace std;

//Tạo map để lưu tần suất các ký tự suất hiện trong chuỗi kí tự đầu vào
map<char, int> tansuat;
map<char, int > luukq;

//Tạo struct Node, chứa từng ký tự và tần suất của nó
struct Node
{
    char data; //Ký tự
    int freq; //Tần suất

    //Tạo có trỏ đến Node bến phải và bên trái
    struct Node *left, *right;
};

struct Tree
{
    //Kích thước của cây hiện tại
    int kichthuoc;

    //Sức chứa tối đa của cây
    int succhuamax;
    struct Node** mang;
};

// Hàm tạo node mới
struct Node* newNode(char dulieu, int tan_suat)
{
    //Cấp phát vùng nhớ mới cho node
    struct Node* luu = (struct Node*)malloc(sizeof(struct Node));

    luu -> data = dulieu;
    luu -> freq = tan_suat;

    luu -> left = NULL;
    luu -> right = NULL;

    return luu;
};

//
void Heapify(struct Tree* huffmantree, int j)
{
    int nho = j;
    int left = 2*nho + 1;
    int right = 2*nho + 2;
    if ((left < huffmantree ->kichthuoc) && (huffmantree -> mang[left] -> freq < huffmantree -> mang[nho] -> freq))
    {
        nho = left;
    }
    if ((right < huffmantree ->kichthuoc) &&(huffmantree -> mang[right]-> freq < huffmantree -> mang[nho] -> freq))
    {
        nho = right;
    }
    if (nho != j)
    {
         struct Node* luu = huffmantree -> mang[nho];
         huffmantree -> mang[nho] = huffmantree -> mang[j];
         huffmantree -> mang[j]   = luu;
    }
}

//
struct Node* PhanTuNhoNhat(struct Tree* huffmantree)
{
    struct Node* luu = huffmantree->mang[0];
    huffmantree->mang[0] = huffmantree->mang[huffmantree->kichthuoc - 1];
    huffmantree->kichthuoc --;
    Heapify(huffmantree, 0);
    return luu;
};

//
void ChenThemPhanTu(struct Tree* huffmantree, struct Node* top)
{
    huffmantree ->kichthuoc ++;
    int k = huffmantree ->kichthuoc - 1;

    while ( k && top->freq < huffmantree->mang[(k - 1) / 2]->freq)
    {
        huffmantree->mang[k] = huffmantree->mang[(k - 1) / 2];
        k = (k - 1) / 2;
    }

    huffmantree->mang[k] = top;
};



struct Node* BuildHuffmanTree()
{
    //Khởi tạo các nút con trái, phải; top là nút cha của trái, phải, với giá trị bằng tổng nút trái và phải
    struct Node *top, *right, *left;

    //Cấp phát một vùng nhớ đủ cho struct Tree
    struct Tree* huffmantree= (struct Tree*)malloc(sizeof(struct Tree));

    //Kích thước khi khởi tạo sẽ là không
    huffmantree -> kichthuoc = 0;

    //Sức chứa tối đa của cây là số lượng phần tử khác nhau trong map tansuat
    huffmantree -> succhuamax = tansuat.size();

    //Cấp pháp một mảng gồm có succhuamax phần tử kiểu struct Node*
    huffmantree -> mang  = (struct Node**)malloc(huffmantree -> succhuamax * sizeof(struct Node*));

    //Tạo ra 1 nút mới có ký tự và tuần suất được lấy từ map, sau đó lưu nút mới vào mảng của cây huffmantree
    int chiso = 0;
    while (chiso < tansuat.size())
    {
        for (auto it = tansuat.begin(); it != tansuat.end(); ++it)
        {
            huffmantree -> mang[chiso] = newNode(it -> first, it -> second);
            chiso++;
        }
        if (chiso == tansuat.size())
        {
            chiso += 0;
            break;
        }
    }
    huffmantree -> kichthuoc = tansuat.size();

    //
    int gioihan = huffmantree -> kichthuoc - 1;
    for (int j = (gioihan - 1)/2; gioihan >= 0; gioihan--)
    {
        Heapify(huffmantree, j);
    }

    //
    while(huffmantree -> kichthuoc != 1)
    {
        left = PhanTuNhoNhat(huffmantree);
        right = PhanTuNhoNhat(huffmantree);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        ChenThemPhanTu(huffmantree, top);
    }
    return PhanTuNhoNhat(huffmantree);

};
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        cout << arr[i];
    }
    cout <<"\n";
}
int isLeaf(struct Node* root)

{

    return !(root->left) && !(root->right);
}

void printCodes(struct Node* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {
        cout << root->data << ":";
        printArr(arr, top);
        int so = 0;
        for(int i = 0; i < top;i++)
        {
            so += arr[i]*pow(10,i);
        }
        luukq[root->data]= so;
    }
}
void InCaDay(string xau)
{
    string tong;
    for (int i = 0; i < xau.size(); i++)
    {
        for (auto it = luukq.begin(); it != luukq.end(); ++it)
        {
            if (it -> first == xau[i])
            {
                cout << it ->second;
                int b =  it -> second;
                string a = to_string(b);
                tong += a;
            }
        }
    }
    cout <<"\n\n";
    cout <<"Total Huffman Code of string: " << tong.size();

}

void HuffmanCoding(string xau)
{
    //Xây dựng cây Huffman
    struct Node* root = BuildHuffmanTree();

    //In cây Huffman
    int arr[10000];
    int top = 0;
    cout <<"\n";
    cout <<"Total ASCII code: " << xau.size()*8 <<"\n\n";
    cout << "Print Huffman Code of each letter: "<<"\n";
    printCodes(root, arr, top);
    cout <<"\n";
    cout << "Print Huffman Code of input string: "<<"\n";
    InCaDay(xau);
}

int main()
{
    string xau;
    getline(cin,xau);

    //Đếm tần suất của các ký tự
    for (int i = 0; i < xau.size(); i++)
    {
        tansuat[xau[i]] += 1;
    }
    /*for (auto [e, freq] : tansuat)
    {
        cout << e << " " << freq << "\n";
    }
    */
    if (tansuat.size() == 1)
    {
        cout <<"\n";
        cout <<"Total ASCII code: " << xau.size()*8 <<"\n\n";
        cout <<"Print Huffman Code of each letter"<< xau[0]<< ": 0" <<"\n\n";
        cout << "Print Huffman Code of input string: "<<"\n";
        for (int i = 0; i < xau.size(); i++)
        {
            cout<<0;
        }
        cout <<"\n\n";
        cout <<"Total Huffman Code of string: " << xau.size();

    }
    else
    {
        HuffmanCoding(xau);
    }
    return 0;
}
