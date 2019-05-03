#include <iostream>
// #include <conio.h>
#include <error_code.h>
#include <linked_list.h>
#include <fstream>

using namespace std;
//Utility
int dummy_node_count(list_node *head)
{
    int count = 0;
    while(head!=NULL)
    {
        if(head->data < 1)
        {
            count++;
            head = head->next;
        }
        else 
            return count;
    }
    return count;
}

int compareRevIntList(list_node *operand1, list_node *operand2)
{
    int list_len1 = 0, list_len2 = 0, null_node1 = 0,null_node2 = 0;
    list_node *temp1 = operand1, *temp2 = operand2;
    //cout<<__func__ <<":enter"<<endl;
    //Last node is the 10^n value so if the lists are of equal length then compare the last node.
    //error case
    if(NULL == operand1 || NULL == operand2)
    {
        cout<<__func__ <<"Null Parameters"<<endl;
        return 0;
    }
    stripFromStart(&temp1);
    stripFromStart(&temp2);
    list_len1 = listLenRev(temp1);
    list_len2 = listLenRev(temp2);
    temp1= NULL;
    temp2= NULL;

    //We need to remove the last zeros.
    //cout<<__func__ <<"list_len1:"<<list_len1<<" list_len2:"<<list_len2<<endl;

    if(list_len1 == list_len2)
    {
        while(operand1->prev != NULL && operand1->data == operand2->data)
        {
            operand1 = operand1->prev;
            operand2 = operand2->prev;
        }
        if(operand1->data > operand2->data)
        {
                return 1;
        }    
        else if (operand1->data < operand2->data)
        {
                return 2;
        }
        return 1; // both are identical, return first as greater
    }
    else if(list_len1>list_len2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
    //cout<<__func__ <<":exit"<<endl;    
    return 0;
}

int compareIntList(list_node *operand1, list_node *operand2)
{
    int list_len1 = 0, list_len2 = 0, null_node1 = 0,null_node2 = 0;
    list_node *temp1 = operand1, *temp2 = operand2;
    // cout<<__func__ <<":enter"<<endl;
    //Last node is the 10^n value so if the lists are of equal length then compare the last node.
    //error case
    if(NULL == operand1 || NULL == operand2)
    {
        cout<<__func__ <<"Null Parameters"<<endl;
        return -9999;
    }
    list_len1 = listLen(temp1);
    list_len2 = listLen(temp2);

    //We need to remove the last zeros.

    if(list_len1 == list_len2)
    {
        while(operand1->next != NULL && operand1->data == operand2->data)
        {
            operand1 = operand1->next;
            operand2 = operand2->next;
        }
        if(operand1->data > operand2->data)
        {
                return 1;
        }else if(operand1->data < operand2->data)
        {
                return -1;
        }
        return 0; // both are identical, return first as greater
    }
    else if(list_len1>list_len2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    //cout<<__func__ <<":exit"<<endl;    
    return -99999;
}

int findBigSmall(list_node **Big, list_node **Small,list_node *operand1, list_node *operand2 )
{

    int compare_op = compareIntList(operand1,operand2);
    //cout<<__func__ <<"Compare_op:::"<<compare_op<<endl;
    //First we need to find the largest number and then sub it with the smallest. 
    if(compare_op >= 0)
    {
        *Big = operand1;
        *Small = operand2;
    }
    else if(compare_op == -1)
    {
        *Big = operand2;
        *Small = operand1;

    }
    else
    {
        return EBADPARAM;
    }
    return ESUCCESS;
}

int addList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node temp,*sum;
    int carry = 0;
    operand1 = findTail(operand1);
    operand2 = findTail(operand2);
    //Add both the operands.
    while(NULL != operand1 && NULL != operand2)
    {
        temp.data = operand1->data + operand2->data + carry;
        //cout<<"temp.data:"<<temp.data<<"\n";
        carry = (temp.data)/10;
        temp.data = (temp.data)%10;
        //cout<<"carry:"<<carry<<"\n";

        allocMemForNode(&sum);
        sum->data = temp.data;
        addAtStart(result,sum);
        //cout<<"sum:"<<sum->data<<"\n";

        operand1 = operand1->prev;
        operand2 = operand2->prev;
    }

    //Now its possible that atleast one is big. 
    if(NULL != operand1)
    {
        while(NULL != operand1)
        {
        temp.data = operand1->data + carry;
        carry = 0;
        allocMemForNode(&sum);
        sum->data = temp.data;
        operand1 = operand1->prev;
        addAtStart(result,sum);
        }
    }
    else if(NULL != operand2)
    {
        while(NULL != operand2)
        {
        temp.data = operand2->data + carry;
        carry = 0;
        allocMemForNode(&sum);
        sum->data = temp.data;
        addAtStart(result,sum);    
        operand2 = operand2->prev;  
        }  
    }
    //New node is required.
    if(0!=carry)
    {
        allocMemForNode(&sum);
        sum->data = carry;
        addAtStart(result,sum);
    }

    return ESUCCESS;
}


int subList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node *Big = NULL, *Small = NULL;
    
    
    if(ESUCCESS != findBigSmall(&Big, &Small,operand1,operand2))
    {
        cout<<__func__ <<"findBigSmall failed!"<<endl;
        return EFAILED;
    }
    Big = findTail(Big);
    Small = findTail(Small);
    
    //Now we need to do Big - small
    int borrow = 0;
    list_node temp,*sub;
    //Add both the operands.
    while(NULL != Big && NULL != Small)
    {
        if(Big->data < (Small->data + borrow))
        {
            temp.data = 10 + Big->data - Small->data - borrow;
            borrow = 1;
        }
        else
        {
            temp.data = Big->data - Small->data - borrow;
            borrow = 0;
        }
        allocMemForNode(&sub);
        sub->data = temp.data;
        addAtStart(result,sub);
        
        Big = Big->prev;
        Small = Small->prev;
    }
    //cout<<__func__ <<"Iter1 done"<<endl;
    //Now its possible that Big has more digits. 1012 77 
    while(NULL != Big)
    {
        //cout<<Big->data<<endl;
        if(Big->data < borrow)
        {
            temp.data = 10+ Big->data - borrow;
            borrow = 1;
        }
        else
        {            
            temp.data = Big->data - borrow;
            borrow = 0;
        }
        allocMemForNode(&sub);
        sub->data = temp.data;
        Big = Big->prev; 
        addAtStart(result,sub);
    }
   
    stripFromStart(result);
    list_node *zero;

    if (result == NULL)
        {
            zero->data = 0;
            addAtStart(result, zero);
        }
    return ESUCCESS;
}

int multiplyList(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node *Big = NULL, *Small = NULL, temp, *Big_temp = NULL, *sum = NULL, *sum_temp = NULL;
    int carry = 0,small_index = 0,res_len = 0,idx = 0;

    operand1 = findTail(operand1);
    operand2 = findTail(operand2);

    if(ESUCCESS != findBigSmall(&Big, &Small,operand1,operand2))
    {
        cout<<__func__ <<"findBigSmall failed!"<<endl;
        return EFAILED;
    }

    res_len = listLenRev(Big) + listLenRev(Small);
    //cout<<__func__ <<"Resule_len="<<res_len<<endl;

    Big_temp = Big;
    while(res_len>0)
    {
        allocMemForNode(&sum);
        addAtStart(result,sum);
        res_len--;
    }

    sum = findTail(*result);
    //create result of len Big + Small
    while(NULL != Small)
    {
        idx = 0;
        carry = 0;
        while(idx < small_index)
        {
            idx++;
            sum = sum->prev;
        }
        while(NULL != Big)
        {
            temp.data = (Small->data * Big->data) + carry;

            sum->data = sum->data + temp.data;
            
            carry = (sum->data)/10;
            sum->data = (sum->data)%10;

            sum = sum->prev;
            Big = Big->prev;
        }
        // cout<<"carry="<<carry<<"sum->data:"<<sum->data<<endl;
        while(carry>0)
        {
            sum->data = sum->data + carry;

            carry = (sum->data)/10;
            sum->data = (sum->data)%10;

            sum = sum->prev;
        }
        Small = Small->prev;
        Big = Big_temp;    
        sum = findTail(*result);;
        small_index++;
    }

    //We need to add at the next place.
    stripFromStart(result);
    return ESUCCESS;
}

int divideList(list_node *operand1c, list_node *operand2c, list_node **quotient, list_node **reminder)
{
    int compare_op = 0;
    list_node *sum=NULL,*result_temp = NULL, *temp_result = NULL, *temp_operand1 = NULL,*operand1 =NULL, *operand2 = NULL;
    //cout<<__func__<<":Entry"<<endl;
    //cout<<"AllotMemSum"<<endl;

    allocMemForNode(&sum);
    sum->data = 0;
    addAtStart(quotient,sum);
    //cout<<"Creating copies of operands"<<endl;
    //cout<<"Operand1"<<endl;
    dupList(operand1c, &operand1);
    //cout<<"Operand2"<<endl;
    dupList(operand2c, &operand2);

    list_node *temp_1;
    allocMemForNode(&temp_1);
    temp_1->data = 1;
    while(compareIntList(operand1,operand2) >=0)
    {
        //cout<<"compare_loop_enter"<<endl;
        temp_operand1 = NULL;
        subList(operand1,operand2,&temp_operand1);
        deleteList(&operand1);
        operand1 = temp_operand1;

        temp_result = NULL;
        //deleteList(&temp_result);
        addList(*quotient,temp_1,&temp_result);
        

        //deleteList(quotient);
        stripFromStart(&temp_result);

        *quotient = temp_result;
        //dupList(temp_result, quotient);
        //cout<<"compare_loop_exit"<<endl;
    }
    dupList(operand1, reminder);
    return ESUCCESS;
}

int gcd(list_node *operand1, list_node *operand2, list_node **result)
{
    list_node *one = listFromString("1");
    list_node *zero = listFromString("0");
    list_node *dummy, *temp;
    dummy = NULL;
    temp = NULL;
    while(1){
        divideList(operand1, operand2, &dummy, &temp);
        if (compareIntList(temp, zero)==0)
            {
                *result=operand2;
                return ESUCCESS;
            }
        dupList(operand2, &operand1);
        dupList(temp, &operand2);
    }
    
    /*
    while (1) 
    { 
        temp = a%h; 
        if (temp == 0) 
          return h; 
        a = h; 
        h = temp; 
    } 
    */
}

int exp(list_node *base, list_node* exp, list_node **result){
    list_node *one = listFromString("1");
    list_node *zero = listFromString("0");
    list_node *temp;
    temp = NULL;

    if(compareIntList(exp, one)==0)
        {
            dupList(base, result);
            return 0;
        }
    if(compareIntList(exp, zero)==0)
    {
            dupList(one, result);
            return 0;
    }
    dupList(base, result);
    while(compareIntList(exp, one)>0){
        allocMemForNode(&temp);
        multiplyList(base, *result, &temp);
        *result = NULL;
        //allocMemForNode(&temp);
        dupList(temp, result);
        temp = NULL;
        subList(exp, one, &temp);
        exp=NULL;
        dupList(temp, &exp);
    }
    return 0;
}