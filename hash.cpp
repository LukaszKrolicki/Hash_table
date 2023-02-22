#include <iostream>
#include <fstream>
using namespace std;


class HashTable{
    private:
        string* t;
        int capacity;
        int size;
    public:
        HashTable(int c);                //konstruktor tworz¹cy pust¹ tablicê o pojemnoœci c
        bool empty();
        bool full();
        int hashFunction(string s);        //funkcja haszuj¹ca dla klucza s
        int insert(string s);            //wstawienie klucza s (zwraca liczbê prób przy wyst¹pieniu kolizji - 0 jeœli kolizja nie wyst¹pi³a)
        void del(string s);                //usuwa klucz s
        string search(string s);        //wyszukuje i zwraca s
        int search1(string s);            //wyszukuje s i zwraca liczbê prób przy wyst¹pieniu kolizji - 0 jeœli kolizja nie wyst¹pi³a
        void print();
        friend ostream& operator<<(ostream& out, HashTable& ht); //wypisuje tablicê (z numerami pól), pozostawia puste dla wolnych pól
};

HashTable::HashTable(int c){
    capacity =c;
    size=0;
    t=new string[c];
    for(int i=0; i<capacity; i++){
        t[i]="x";
    }
}

bool HashTable::empty(){
    if(size==0){
        return true;
    }
    else{
        return false;
    }
}

bool HashTable::full(){
    if(size==capacity){
        return true;
    }
    else{
        return false;
    }
}

int HashTable::hashFunction(string s){
    int sum = 0;
    char znak = 'x';
    for(int i=0; i<s.length();i++){
        znak=s[i];
        sum+= (int)znak;
    }

    int hashValue = sum%capacity;
    cout<<hashValue<<" - "<<sum<<endl;
    return hashValue;
}

int HashTable::insert(string s){
    if(!full()){
        int i=0;  //numer próby
        for(int a=hashFunction(s); a<capacity; a++ ){
            i++;
            if(t[a]=="x" || t[a]=="del"){
                t[a]=s;
                size++;
                return i;
            }
        }

        for(int a=0; a<hashFunction(s); a++ ){
            i++;
            if(t[a]=="x" || t[a]=="del"){
                t[a]=s;
                size++;
                return i;
            }
        }
    }

    return 0;
}

void HashTable::print(){
    for(int i=0; i<capacity; i++){
        cout<<t[i]<<" ";
    }
}

string HashTable::search(string s){

    for(int a=hashFunction(s); a<capacity; a++ ){
        if(t[a]==s){
            return t[a];
        }
        else if(t[a]=="x")
        {
            return "nie ma";
        }
    }

    for(int a=0; a<hashFunction(s); a++ ){
        if(t[a]==s){
            return t[a];
        }
        else if(t[a]=="x")
        {
            return "nie ma";
        }
    }

    return("nie ma");

}

int HashTable::search1(string s){
    int i=0;

    for(int a=hashFunction(s); a<capacity; a++ ){
        if(t[a]==s){
            return i;
        }
        else if(t[a]=="x")
        {
            return i;
        }
        i++;
    }

    for(int a=0; a<hashFunction(s); a++ ){
        if(t[a]==s){
            return i;
        }
        else if(t[a]=="x")
        {
            return i;
        }
        i++;
    }

    return -1;

}

void HashTable::del(string s){

    for(int a=hashFunction(s); a<capacity; a++ ){
        if(t[a]==s){
            t[a]="del";
            size--;
            return;
        }
    }

    for(int a=0; a<hashFunction(s); a++ ){
        if(t[a]==s){
            t[a]="del";
            size--;
            return;
        }
    }
}

ostream& operator<<(ostream& out, HashTable& ht){
    for(int i=0; i<=ht.capacity; i++){
        out<<ht.t[i]<<" ";
    }

}

int main(){


    HashTable t(10);
    t.insert("huh");
    t.insert("lala");
    t.insert("baba");
    t.insert("byczek");
    t.insert("cycu");
    t.insert("iiii");
    t.insert("aaaa");
    t.insert("bbbb");
    cout<<endl;
    t.print();
    cout<<endl;
    t.del("huh");
    t.del("cycu");

    t.print();

    cout<<endl;
    cout<<t.search("huh")<<t.search1("huh")<<endl;
    cout<<t.search("iiii")<<t.search1("iiii")<<endl;
    cout<<t.search("lala")<<t.search1("lala")<<endl;

    t.insert("huh");
    t.print();


}
