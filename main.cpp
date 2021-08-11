#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    char name;
    int kolvo;
    Node* ptrL = nullptr;
    Node* ptrR = nullptr;
    char kod[10] = { "" };
    void show() const{
        cout << "\t" << name << " = " << "kolvo = " << kolvo << endl;
    }
    void f(){
        if(this->ptrL == nullptr) {
            return;
        }
        else{
            this->ptrL->show();
            this->ptrL->f();
            //добавить работу с ptrR
        }
    }
};
struct table {
    Node* ptr = nullptr;
    int size;
    table(int size) :size(size){
        ptr = new Node[size];
    }
    void show() const {
        for (int i = 0; i < size; i++) {
            ptr[i].show();
        }
    }
};

void sort(Node* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].kolvo < arr[j + 1].kolvo) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    std::cout << "\tОтсортированный массив" << endl; // напечатали это слово
    for (int i = 0; i < size; i++) {
        arr[i].show();
    }
    std::cout << endl;
}

int min(table & table, int i_Left, int i_Right, int i_old_min) {
    int min;
    int i_min;

    if (i_Left == 0) {
        if (i_Right != i_old_min) {
            min = table.ptr[i_Right].kolvo;
            i_min = i_Right;
        }
        else{
            min = table.ptr[i_Right+1].kolvo;
            i_min = i_Right+1;
        }
    }
    else {
        if ((i_Left-1) != i_old_min) {
            min = table.ptr[i_Left-1].kolvo;
            i_min= i_Left-1;
        }
        else{
            min = table.ptr[i_Left-2].kolvo;
            i_min= i_Left-2;
        }
    }

    for (int i = 0; i < i_Left; i++) {
        if (i != i_old_min) {
            if (table.ptr[i].kolvo< min ) {
                min = table.ptr[i].kolvo;
                i_min = i;
            }
        }
    }

    for (int i = i_Right; i < table.size; i++) {
        if (i != i_old_min) {
            if (table.ptr[i].kolvo < min) {
                min = table.ptr[i].kolvo;
                i_min = i;
            }
        }
    }

    return i_min;
}

int main() {
    // system("chcp 65001");
    setlocale(LC_ALL, "Russian");
    char buff[20];
    int povtor[26] = { 0 };
    ifstream fin("Input.txt");
    while (!fin.fail()) {
        fin >> buff;
        std::cout << buff << endl;
        /*Подсчет таблицы*/
        for (int i = 0; i < strlen(buff); i++) {
            if ((buff[i] >= 'A') && (buff[i] <= 'Z')) {
                povtor[buff[i] - 65]++;
            }
            else if ((buff[i] >= 'a') && (buff[i] <= 'z')) {
                povtor[buff[i] - 97]++;
            }
        }
    }
    std::cout << "Считывание завершилось" << endl;
    int counter_size_table = 0;
    for (int i_temp : povtor) {
        if (i_temp) {
            counter_size_table++;//cout << char(i + 65) << " = " << povtor[i] << endl;
        }
    }
    table mainTable(counter_size_table);
    //mainTable.ptr = new Node[mainTable.size];
    int j = -1;
    for (int i_temp = 0; i_temp < 26; i_temp++) {
        if (povtor[i_temp]) {
            j++;
            mainTable.ptr[j].name = i_temp + 65;
            mainTable.ptr[j].kolvo = povtor[i_temp];
            //table[j].show();
        }
    }
    std::cout << "Создание таблицы завершено." << endl;
    sort(mainTable.ptr, mainTable.size);
    cout << endl;
    int i_L = mainTable.size-2;
    int i_R = mainTable.size;
    int i_l_safe = mainTable.size;
    int i_R_safe = mainTable.size;
    int i_min1 = mainTable.size - 2;
    int i_min2 = mainTable.size - 1;

    while (mainTable.size<counter_size_table+(counter_size_table-1)){
        Node* ptr = new Node[mainTable.size+1];
        for (int i = 0; i < mainTable.size; i++) {
            ptr[i] = mainTable.ptr[i];
        }
        delete[] mainTable.ptr;
        mainTable.ptr = ptr;
        ptr[mainTable.size] = *new Node;
        ptr[mainTable.size].kolvo = mainTable.ptr[i_min1].kolvo + mainTable.ptr[i_min2].kolvo;
        ptr[mainTable.size].name = '0' + char(j);
        mainTable.size++;

        i_min1 = min(mainTable, i_L, i_R, -1);
        i_min2 = min(mainTable, i_L, i_R, i_min1);
        if (i_min1 < i_L && i_min2 < i_L) {
            i_L -= 2;
        }
        else if (i_min1 >= i_R && i_min2 >= i_R) {
            i_R += 2;
        }
        else {
            i_L--;
            i_R++;
        }
    }

     i_L = i_l_safe;
     i_R = i_R_safe;
int X=i_R_safe-1;
    while (X<mainTable.size-1) {
        X++;
        i_min1 = min(mainTable, i_L, i_R, -1);
        i_min2 = min(mainTable, i_L, i_R, i_min1);
        mainTable.ptr[X].ptrL = &mainTable.ptr[i_min2];
        mainTable.ptr[X].ptrR = &mainTable.ptr[i_min1];

        if (i_min1 < i_L && i_min2 < i_L) {
            i_L -= 2;
        }
        else if (i_min1 >= i_R && i_min2 >= i_R) {
            i_R += 2;
        }
        else {
            i_L--;
            i_R++;
        }
    }
    for (int i_temp = 0; i_temp < mainTable.size; i_temp++) {
            mainTable.ptr[i_temp].show();
    }
    mainTable.ptr[8].f();



    /*рекурсивная расстановка 1 и 0 по всем элементам*/
    /*рекурсивная функция которая проходит по ptrL пока он не nullptr*/
    /*рекурсивная функция которая проходит по ptrR пока он не nullptr*/
    /*ptr[mainTable.size].ptrL = &mainTable.ptr[i_min2];
    ptr[mainTable.size].ptrR = &mainTable.ptr[i_min1];
    проверка установки верных связей*/

    fin.close();
    return 0;
}