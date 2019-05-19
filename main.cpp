#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

class Student
{
    string first_name, last_name, patromymic, group, birthday;
    Student **head;
    int size_of_student;
public:
    Student(bool read_from_file)
    {
        if (read_from_file == false)
        {
            cout << "Введите данные следующего студента." << endl;
            cout << "Фамилия: ";
            cin >> first_name;
            cout << "Имя: ";
            cin >> last_name;
            cout << "Отчество: ";
            cin >> patromymic;
            cout << "Номер группы: ";
            cin >> group;
            cout << "Дата рождения: ";
            cin >> birthday;
        }

        if (read_from_file == true)
        {
            cin >> first_name;
            cin >> last_name;
            cin >> patromymic;
            cin >> group;
            cin >> birthday;
        }
    }

    Student(int inp_size_of_student, bool read_from_file)
    {
        this->size_of_student = inp_size_of_student;
        this->head = new Student*[size_of_student];
        for (int i = 0; i < this->size_of_student; i++)
        {
            this->head[i] = new Student(read_from_file);
        }
    }

    Student(const Student &from)
    {
        this->first_name = from.first_name;
        this->last_name = from.last_name;
        this->patromymic = from.patromymic;
        this->group = from.group;
        this->birthday = from.birthday;
    }

    Student **GetHead()
    {
        return head;
    }

    int GetSizeOfStudent()
    {
        return size_of_student;
    }

    string GetFirstName()
    {
        return first_name;
    }

    string GetLastName()
    {
        return last_name;
    }

    string GetPatromymic()
    {
        return patromymic;
    }

    string GetGroup()
    {
        return group;
    }

    string GetBirthday()
    {
        return birthday;
    }

    void Print(string order)
    {
        for (int i = 0; i < this->size_of_student; i++)
        {
            cout << this->head[i]->first_name << " ";
            cout << this->head[i]->last_name << " ";
            cout << this->head[i]->patromymic << " ";
            cout << this->head[i]->group << " ";
            cout << this->head[i]->birthday << endl;
        }
    }

    void WriteToFile()
    {
        ofstream out("Base_of_date/Date.txt");
        if (out.is_open())
        {
            out << this->size_of_student << endl;
            for (int i  = 0; i < this->size_of_student; i++)
            {
                out << this->head[i]->first_name << " ";
                out << this->head[i]->last_name << " ";
                out << this->head[i]->patromymic << " ";
                out << this->head[i]->group << " ";
                out << this->head[i]->birthday << endl;
            }
        }
        out.close();
    }

    void Append()
    {
        Student **new_head = new Student*[this->size_of_student + 1];
        for (int i = 0; i < this->size_of_student; i++)
        {
            new_head[i] = new Student(*this->head[i]);
        }

        delete [] this->head;
        this->head = new_head;
        this->size_of_student++;
        this->head[this->size_of_student - 1] = new Student(false);
    }

    void SwapStudent(Student *first, Student *second)
    {
        Student temp = *first;
        *first = *second;
        *second = temp;
    }


    void QuickSort(int first, int last, string parameter)
    {
        if (first < last)
        {
            int left = first, right = last, index = (left + right) / 2;
            string middle;

            if (parameter == "first_name last_name patromymic")
                middle = head[index]->first_name + " " + head[index]->last_name + " " + head[index]->patromymic;

            if (parameter == "group")
                middle = head[index]->group;

            if (parameter == "birthday")
                middle = head[index]->birthday;
            do
            {
                if (parameter == "first_name last_name patromymic")
                {
                    while ((head[left]->first_name + " " + head[left]->last_name + " " + head[left]->patromymic) < middle) left++;
                    while ((head[right]->first_name + " " + head[right]->last_name + " " + head[right]->patromymic) > middle) right--;
                }

                if (parameter == "group")
                {
                    while (this->head[left]->group < middle) left++;
                    while (this->head[right]->group > middle) right--;
                }

                if (parameter == "birthday")
                {
                    while (this->head[left]->birthday < middle) left++;
                    while (this->head[right]->birthday > middle) right--;
                }
                if (left <= right)
                {
                    SwapStudent(this->head[left], this->head[right]);
                    left++;
                    right--;
                }
            } while (left <= right);
            QuickSort(first, right, parameter);
            QuickSort(left, last, parameter);
        }
    }

    void Sort()
    {
        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");
    }

    bool BinarySearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int middle = (left + right) / 2;
            string example = head[middle]->first_name + " " + head[middle]->last_name + " " + head[middle]->patromymic + " " + head[middle]->group + " " + head[middle]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = middle - 1;
                else
                    left = middle + 1;
        }

        return result;
    }

    bool GoldenSectionSearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int golden_section = (0.382 * right) + (0.618 * left);
            string example = head[golden_section]->first_name + " " + head[golden_section]->last_name + " " + head[golden_section]->patromymic + " " + head[golden_section]->group + " " + head[golden_section]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = golden_section - 1;
                else
                    left = golden_section + 1;
        }

        return result;
    }

    bool ProportionSearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        int a, b;
        cout << "Введите два натуральных числа:" << endl;
        cin >> a >> b;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int i = ((a * right) + (b * left))/(a + b);
            string example = head[i]->first_name + " " + head[i]->last_name + " " + head[i]->patromymic + " " + head[i]->group + " " + head[i]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = i - 1;
                else
                    left = i + 1;
        }

        return result;
    }
};

class Tree
{
    Tree *left = 0, *right= 0, *head = 0;
    Student *value;

public:
    Tree(){}

    Tree(Student *input_head)
    {
        head = this;
        if (input_head->GetSizeOfStudent() > 0)
            value = input_head->GetHead()[0];
            else
                cout << "Ошибка: Нет данных!" << endl;

        for (int i = 1; i < input_head->GetSizeOfStudent(); i++)
        {
            Add(input_head->GetHead()[i]);
        }

    }

    void Add(Student *ptr)
    {
        string request = ptr->GetFirstName() + " " + ptr->GetLastName() + " " + ptr->GetPatromymic() + " " + ptr->GetGroup() + " " + ptr->GetBirthday();
        Tree *act_posit = this;

        for ( ; ; )
        {
            string example = act_posit->value->GetFirstName() + " " + act_posit->value->GetLastName() + " " + act_posit->value->GetPatromymic() + " " + act_posit->value->GetGroup() + " " + act_posit->value->GetBirthday();
            if (request == example)
               break;

            if (request < example)
            {
                if (act_posit->left != 0)
                    act_posit = act_posit->left;
                    else
                    {
                        act_posit->left = new Tree;
                        act_posit->left->value = ptr;
                        break;
                    }

            }
                else
                {
                    if (act_posit->right != 0)
                        act_posit = act_posit->right;
                        else
                        {
                            act_posit->right = new Tree;
                            act_posit->right->value = ptr;
                            break;
                        }
                }
        }
    }

    bool Search()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;

        Tree *act_posit = this;
        bool result = false;
        for ( ; ; )
        {
            string example = act_posit->value->GetFirstName() + " " + act_posit->value->GetLastName() + " " + act_posit->value->GetPatromymic() + " " + act_posit->value->GetGroup() + " " + act_posit->value->GetBirthday();
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
            {
                if (act_posit->left != 0)
                    act_posit = act_posit->left;
                    else
                        break;
            }
                else
                {
                    if (act_posit->right != 0)
                        act_posit = act_posit->right;
                        else
                            break;
                }
        }

        return result;
    }
};

const int t = 2;

struct BNode
{
    Student* keys[2*t];
    BNode *children[2*t+1];
    BNode *parent;
    int number_of_keys; //количество ключей
    int countSons; //количество сыновей
    bool leaf;
};

class B_Tree
{
    private:
    BNode *root = nullptr;

    void insert_to_node(Student* key, BNode *node)
    {
        node->keys[node->number_of_keys] = key;
        node->number_of_keys = node->number_of_keys + 1;
        sort(node);
    }

    void sort(BNode *node)
    {
        for (int i = 0; i < (2*t-1); i++)
        {
            for (int j = i+1; j <= (2*t-1); j++)
            {
                if ((node->keys[i] != nullptr) && (node->keys[j] != nullptr))
                {
                    string requst_1 = node->keys[i]->GetFirstName() + " " + node->keys[i]->GetLastName() + " " + node->keys[i]->GetPatromymic() + " " + node->keys[i]->GetGroup() + " " + node->keys[i]->GetBirthday();
                    string request_2 = node->keys[j]->GetFirstName() + " " + node->keys[j]->GetLastName() + " " + node->keys[j]->GetPatromymic() + " " + node->keys[j]->GetGroup() + " " + node->keys[j]->GetBirthday();
                    if (requst_1 > request_2)
                    {
                        Student temp = *node->keys[i];
                        *node->keys[i] = *node->keys[j];
                        *node->keys[j] = temp;
                    }
                }
                    else break;
            }
        }
    }

    void restruct(BNode *node)
    {
        if (node->number_of_keys < (2*t-1))
            return;

        //первый сын
        BNode *child1 = new BNode;
        int j;
        for (j = 0; j <= t-2; j++)
            child1->keys[j] = node->keys[j];
        for (j = t-1; j <= (2*t-1); j++)
            child1->keys[j] = nullptr;
        child1->number_of_keys = t - 1; //количество ключей в узле

        if(node->countSons != 0)
        {
            for (int i = 0; i <= (t-1); i++)
            {
                child1->children[i] = node->children[i];
                child1->children[i]->parent = child1;
            }

            for (int i = t; i <= (2*t); i++)
                child1->children[i] = nullptr;

            child1->leaf = false;
            child1->countSons = t - 1; //количество сыновей
        }
            else
            {
                child1->leaf = true;
                child1->countSons = 0;
                for (int i = 0; i <= (2*t); i++)
                    child1->children[i] = nullptr;
            }

        //второй сын
        BNode *child2 = new BNode;
        for (int j = 0; j <= (t-1); j++)
            child2->keys[j] = node->keys[j+t];
        for (j = t; j <= (2*t-1); j++)
            child2->keys[j] = nullptr;
        child2->number_of_keys = t; //количество ключей в узле

        if(node->countSons != 0)
        {
            for (int i = 0; i <= t; i++)
            {
                child2->children[i]=node->children[i+t];
                child2->children[i]->parent=child2;
            }
            for (int i=t+1; i<=(2*t); i++)
                child2->children[i]=nullptr;
            child2->leaf=false;
            child2->countSons=t; //количество сыновей
        }
            else
            {
                child2->leaf=true;
                child2->countSons=0;
                for (int i=0; i<=(2*t); i++)
                    child2->children[i]=nullptr;
            }

        //родитель
        if (node->parent==nullptr)
        { //если родителя нет, то это корень
            node->keys[0]=node->keys[t-1];
            for(int j=1; j<=(2*t-1); j++)
                node->keys[j]= nullptr;
            node->children[0]=child1;
            node->children[1]=child2;
            for(int i=2; i<=(2*t); i++)
                node->children[i]=nullptr;
            node->parent=nullptr;
            node->leaf=false;
            node->number_of_keys=1;
            node->countSons=2;
            child1->parent=node;
            child2->parent=node;
        } else
        {
            insert_to_node(node->keys[t-1], node->parent);
            for (int i=0; i<=(2*t); i++)
            {
                if (node->parent->children[i]==node)
                    node->parent->children[i]=nullptr;
            }
            for (int i=0; i<=(2*t); i++)
            {
                if (node->parent->children[i]==nullptr)
                {
                    for (int j=(2*t); j>(i+1); j--)
                        node->parent->children[j]=node->parent->children[j-1];
                    node->parent->children[i+1]=child2;
                    node->parent->children[i]=child1;
                    break;
                }
            }
            child1->parent=node->parent;
            child2->parent=node->parent;
            node->parent->leaf=false;
            delete node;
        }
    }

    void deletenode(BNode *node)
    {
        if (node!=nullptr)
        {
            for (int i=0; i<=(2*t-1); i++)
                {
                if (node->children[i]!=nullptr)
                    deletenode(node->children[i]);
                else {
                    delete(node);
                    break;
                }
            }
        }
    }
    bool searchKey(Student *key, BNode *node)
    {
        if (node != nullptr)
        {
            if (node->leaf == false)
            {
                int i;
                for (i = 0; i <= (2*t-1); i++)
                {
                    if (node->keys[i] != nullptr)
                    {
                        string requst_1 = node->keys[i]->GetFirstName() + " " + node->keys[i]->GetLastName() + " " + node->keys[i]->GetPatromymic() + " " + node->keys[i]->GetGroup() + " " + node->keys[i]->GetBirthday();
                        string requst_2 = key->GetFirstName() + " " + key->GetLastName() + " " + key->GetPatromymic() + " " + key->GetGroup() + " " + key->GetBirthday();

                        if(requst_1 == requst_2)
                            return true;

                        if (requst_2 < requst_1)
                        {
                            return searchKey(key, node->children[i]);
                            break;
                        }
                    } else break;
                }
                return searchKey(key, node->children[i]);
            }
                else
                {
                    for(int i = 0; i <= (2*t - 1); i++)
                    {
                        if (node->keys[i] != nullptr)
                        {
                            string requst_1 = node->keys[i]->GetFirstName() + " " + node->keys[i]->GetLastName() + " " + node->keys[i]->GetPatromymic() + " " + node->keys[i]->GetGroup() + " " + node->keys[i]->GetBirthday();
                            string requst_2 = key->GetFirstName() + " " + key->GetLastName() + " " + key->GetPatromymic() + " " + key->GetGroup() + " " + key->GetBirthday();

                            if (requst_1 == requst_2)
                                return true;
                        }
                    }
                    return false;
                }
        }

        if (node == nullptr)
        {
            return false;
        }
    }

    public:

    B_Tree() { root=nullptr; };

    B_Tree(Student *input_head)
    {
        for (int i = 0; i < input_head->GetSizeOfStudent(); i++)
        {
            insert(input_head->GetHead()[i]);
        }

    }

    ~B_Tree()
    {
        if(root != nullptr)
            deletenode(root);
    };

    void insert(Student *key)
    {
        if (root == nullptr)
        {
            BNode *newRoot = new BNode;
            newRoot->keys[0] = key;

            for(int j = 1; j <= (2*t-1); j++)
                newRoot->keys[j] = nullptr;

            for (int i = 0; i <= (2*t); i++)
                newRoot->children[i] = nullptr;

            newRoot->number_of_keys = 1;
            newRoot->countSons = 0;
            newRoot->leaf = true;
            newRoot->parent = nullptr;
            root = newRoot;
        }
        else
        {
            BNode *ptr = root;
            while (ptr->leaf == false)
            { //выбор ребенка до тех пор, пока узел не будет являться листом
                for (int i = 0; i <= (2*t-1); i++)
                { //перебираем все ключи
                    if (ptr->keys[i] != nullptr)
                    {
                            string requst_1 = ptr->keys[i]->GetFirstName() + " " + ptr->keys[i]->GetLastName() + " " + ptr->keys[i]->GetPatromymic() + " " + ptr->keys[i]->GetGroup() + " " + ptr->keys[i]->GetBirthday();
                            string requst_2 = key->GetFirstName() + " " + key->GetLastName() + " " + key->GetPatromymic() + " " + key->GetGroup() + " " + key->GetBirthday();

                            if (requst_2 < requst_1)
                            {
                                ptr = ptr->children[i];
                                break;
                            }

                            if ((ptr->keys[i+1] == nullptr) && (requst_2 > requst_1))
                            {
                                ptr = ptr->children[i+1]; //перенаправляем к самому последнему ребенку, если цикл не "сломался"
                                break;
                            }
                    } else break;
                }
            }

            insert_to_node(key, ptr);

            while (ptr->number_of_keys == 2*t)
            {
                if (ptr == root)
                {
                    restruct(ptr);
                    break;
                }
                else
                    {
                        restruct(ptr);
                        ptr = ptr->parent;
                    }
            }
        }
    }

    bool search(Student *key)
    {
        return searchKey(key, this->root);
    }
};

class Interface
{
public:
    Interface(bool read_from_file)
    {

        int size_of_student;
        if (read_from_file == false)
            cout << "Введите количество студентов" << endl;
        cin >> size_of_student;
        Student students(size_of_student, read_from_file); //if from file => true
        freopen("CONIN$", "r", stdin);

        for ( ; ; )
        {
            cout << "Выберите метод:" << endl;
            cout << "1. Бинарный поиск" << endl;
            cout << "2. Бинарное дерево" << endl;
            cout << "3. B - Дерево" << endl;
            cout << "4. Добавить студента" << endl;
            char choice;
            cin >> choice;
            while (choice != '1' && choice != '2' && choice != '3' && choice != '4' )
            {
                cout << "Сделайте корректный выбор!" << endl;
                cin >> choice;
            }

            if (choice == '1')
            {
                cout << "Выберите вариант:" << endl;
                cout << "1. Стандартная реализация" << endl;
                cout << "2. Золотое сечение" << endl;
                cout << "3. Задать пропорции" << endl;
                char variaty;
                cin >> variaty;
                bool result;
                if (variaty == '1')
                    result = students.BinarySearch();

                if (variaty == '2')
                    result = students.GoldenSectionSearch();

                if (variaty == '3')
                    result = students.ProportionSearch();

                if (result == true)
                    cout << "Найден" << endl;
                    else
                        cout << "Не найден" << endl;
            }

            if (choice == '2')
            {
                cout << "Выберите действие:" << endl;
                cout << "1. Добавить студента" << endl;
                cout << "2. Поиск студента" << endl;
                cout << "3. Выход к методам" << endl;

                Tree tree(&students);
                for( ; ; )
                {
                    char variaty;
                    cin >> variaty;

                    if (variaty == '1')
                    {
                        students.Append();
                        tree.Add(students.GetHead()[students.GetSizeOfStudent() - 1]);
                    }

                    if (variaty == '2')
                    {
                        bool result = tree.Search();
                        if (result == true)
                            cout << "Найден" << endl;
                            else
                                cout << "Не найден" << endl;
                    }

                    if (variaty == '3')
                    {
                        break;
                    }

                    cout << "Выберите действие:" << endl;
                }
            }

            if (choice == '3')
            {
                cout << "Выберите действие:" << endl;
                cout << "1. Добавить студента" << endl;
                cout << "2. Поиск студента" << endl;
                cout << "3. Выход к методам" << endl;

                B_Tree b_tree(&students);
                for( ; ; )
                {
                    char variaty;
                    cin >> variaty;

                    if (variaty == '1')
                    {
                        students.Append();
                        b_tree.insert(students.GetHead()[students.GetSizeOfStudent() - 1]);
                    }

                    if (variaty == '2')
                    {
                        Student *requset = new Student(false);
                        bool result = b_tree.search(requset);
                        if (result == true)
                            cout << "Найден" << endl;
                            else
                                cout << "Не найден" << endl;
                    }

                    if (variaty == '3')
                    {
                        break;
                    }

                    cout << "Выберите действие:" << endl;
                }
            }

            if (choice == '4')
            {
                students.Append();
            }


            cout << "Выйти из методов? (Y/N)" << endl;
            cin >> choice;
            while (choice != 'Y' && choice != 'N')
            {
                cout << "Сделайте корректный выбор!" << endl;
                cin >> choice;
            }

            if (choice == 'Y')
                break;
        }

        cout << "Записать изменения в файл? (Y/N)" << endl;
        char choice;
        cin >> choice;
        while (choice != 'Y' && choice != 'N')
        {
            cout << "Сделайте корректный выбор!" << endl;
            cin >> choice;
        }

        if (choice == 'Y')
            students.WriteToFile();
    }
};

class User
{
public:
    User()
    {
        freopen("Base_of_date/Date.txt", "r", stdin);
        Interface interface(true);
        freopen("CONIN$", "r", stdin);
    }
};

int main()
{
    setlocale(0, "Russian");

    User user;

    return 0;
}
