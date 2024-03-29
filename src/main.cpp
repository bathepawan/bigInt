#include <iostream>
#include <conio.h>
#include <error_code.h>
#include <linked_list.h>
#include <list_math.h>
#include <fstream>

using namespace std;

int convert_ascii_to_digit(char digit)
{
    return (int)(digit - 48);
}

int main()
{
    std::ifstream fin1,fin2;
    std::ofstream fout;
    char digit_c;
    list_node *input1 = NULL,*input2 = NULL,*result = NULL;
    
    //Result file
    cout<<"Result file:"<<endl;
    fout.open("result.txt", ios::out);

    //Open input file 1 and store it in operand1
    cout<<"Input file1:"<<endl;
    fin1.open("input1.txt", ios::in);

    //Open input file 2 and store it in operand2
    cout<<"Input file2:"<<endl;
    fin2.open("input2.txt", ios::in);

    int InputLineCount = 2;
    while(InputLineCount == 2)
    {
        InputLineCount = 0;
        while (fin1.get(digit_c)) {

            if(10 == (int)digit_c)
            {
                InputLineCount++;
                break;
            }
            cout<<convert_ascii_to_digit(digit_c);
            list_node *t_data = NULL;
            allocMemForNode(&t_data);
            t_data->data = convert_ascii_to_digit(digit_c);
            addAtEnd(&input1,t_data);
        }

        while (fin2.get(digit_c)) {
            if(10 == (int)digit_c)
            {
                InputLineCount++;
                break;
            }
            cout<<convert_ascii_to_digit(digit_c);
            list_node *t_data = NULL;
            allocMemForNode(&t_data);
            t_data->data = convert_ascii_to_digit(digit_c);
            addAtEnd(&input2,t_data);
        }

        fout<<"Input 1: "<<endl;
        {
            list_node *temp = input1;
            while(NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        fout<<"Input 2: "<<endl;
        {
            list_node *temp = input2;
            while(NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        //Addition
        addList(input1,input2, &result);
        fout<<"Addition Result: "<<endl;
        {
            list_node *temp = result;
            while( NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        deleteList(&result);

        printList(input1);
        printList(input2);
        //Substract
        subList(input1,input2, &result);
        fout<<"Substract Result: "<<endl;
        {
            list_node *temp = result;
            while( NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        deleteList(&result);
        printList(input1);
        printList(input2);
        cout<<"Input before multiply";
        //multiplyList
        multiplyList(input1,input2, &result);

        fout<<"multiplyList Result: "<<endl;
        {
            list_node *temp = result;
            while( NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        deleteList(&result);

        //Divid List
        list_node *quotient = NULL, *reminder = NULL;
        divideList(input1,input2, &quotient, &reminder);
        fout<<"Divide Result Quotient: "<<endl;
        {
            list_node *temp = quotient;
            while(NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl<<"Reminder:";

            temp = reminder;
            while(NULL != temp)
            {
                fout<<temp->data;
                temp = temp->next;
            }
            fout<<endl;
        }
        deleteList(&quotient);
        deleteList(&reminder);
        deleteList(&input1);
        deleteList(&input2);
    }

    fout.close();

    fin1.close();
    fin2.close();
    getch();
    return ESUCCESS;
}