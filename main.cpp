#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    char name;
    int kolvo;
    Node* ptrL = nullptr;
    Node* ptrR = nullptr;
    char kod[10] = { "" };
    void show() const {
        cout << "\t" << name << " = " << "kolvo = " << kolvo << endl;
    }
};
struct table {
    Node *ptr=nullptr;
    int start_index;
    int end_index;
    int size;
    table(int size):size(size), start_index(0), end_index(size-1){
        ptr = new Node [size];
    }
    void show() const {
        for (int i=0; i< size; i++){
            ptr[i].show();
        }
    }
};

void sort(Node* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].kolvo < arr[j + 1].kolvo) {
                std::swap(arr[j],arr[j+1]);
            }
        }
    }
    std::cout << "\tОтсортированный массив" << endl; // напечатали это слово
    for (int i = 0; i < size; i++) {
        arr[i].show();
    }
    std::cout << endl;
}

int main() {
    system("chcp 65001");
    //setlocale(LC_ALL, "Russian");
    char buff[20];
    int povtor[26] = {0};
    ifstream fin("Input.txt");
    while (!fin.fail()) {
        fin >> buff;
        std::cout << buff << endl;
        /*Подсчет таблицы*/
        for (int i = 0; i < strlen(buff); i++) {
            if ((buff[i] >= 'A') && (buff[i] <= 'Z')) {
                povtor[buff[i] - 65]++;
            } else if ((buff[i] >= 'a') && (buff[i] <= 'z')) {
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
    j=0;
    Node *temp = new Node;
    //while (true){
        temp->kolvo=mainTable.ptr[mainTable.end_index].kolvo + mainTable.ptr[mainTable.end_index - 1].kolvo;
        temp->name = '0' + char(j);
        temp->ptrL=&mainTable.ptr[mainTable.end_index-1];
        temp->ptrR=&mainTable.ptr[mainTable.end_index];
        mainTable.ptr[mainTable.size] = *temp;
        mainTable.size++;
    //}



    /* while (size_table > 0) {
        cout << "Итерация цикла номер " << counter << " size_table = " << size_table << endl;

       if (((table2[size_table].Name == temp.Name) or (table2[size_table - 1].Name == temp.Name))) {
            temp.kolvo = table[size_table - 1].kolvo + table[size_table - 2].kolvo;
            temp.Name = '0' + char(counter);
            temp.kod[0] = '9';
            for (int i = 0; i < size_table; i++) {
                table2[i] = table[i];
            }
            table2[size_table] = temp;
            sort(table2, size_table + 1);
            a.Name = temp.Name;
            a.kolvo = temp.kolvo;
            ptr.ptrL->Name = temp.Name;
            size_table--;
            c.Name = '1' + char(counter);
            c.kolvo = b.kolvo + a.kolvo;
        } else {
            temp.kolvo = table[size_table - 1].kolvo + table[size_table - 2].kolvo;
            temp.Name = '0' + char(counter);
            temp.kod[0] = '9';
            for (int i = 0; i < size_table; i++) {
                table2[i] = table[i];
            }
            table2[size_table] = temp;
            sort(table2, size_table + 1);
            b.Name = temp.Name;
            b.kolvo = temp.kolvo;
            size_table -= 2;
            c.Name = '1' + char(counter);
            c.kolvo = b.kolvo + a.kolvo;
        }
        //продолжить с начала цикл
        counter++;
    }*/
    fin.close();
    return 0;
}