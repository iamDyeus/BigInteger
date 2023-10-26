/*
    AUTHOR : Arsh
    GITHUB : github.com/iamDyeus
    DATE   : OCTOBER 2023
    ABOUT  : DSA ASSIGNMENT

*/


#include "BigInteger.h"


void reverse_linked_list_sign(struct node *head)
{
    if(!head)return; // No Previous Data
    head->data *= -1; 
    // +ve(Number) x -1 = -ve
    // -ve(Number) x -1 = +ve

    reverse_linked_list_sign(head->next); // Calling the function recursively
}

struct BigInteger initialize(char *s)
{
    struct BigInteger dev;
    dev.l=0;
    dev.length=0;
    struct node *head=0;
    int i=0 ,j=0, sign=1;
    if(s[i]=='-')
    {
        sign = -1;
        i++;
    }
    dev.sign=sign;

    while(s[i]!='\n' && s[i]!='\0')
    {
        if(s[i]!='0')
        break;
        i++;
    }
    while (s[i]!='\n' && s[i]!='\0')
    {
        struct node *temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation failed\n");
            return dev;
        }
        temp->data=s[i]-'0';
        temp->next=0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            temp->next=head;
            head=temp;
        }
        i++;
        j++;
    }
    dev.l=head;
    dev.length=j;

    return dev;
}

// Compare Function
int compare(struct BigInteger h1 , struct BigInteger h2)
{
    if(h1.length < h2.length)
        return -1;
    else if(h1.length > h2.length)
        return 1;
    else
    return compare_sub(h1.l,h2.l);
}
int compare_sub(struct node *h1 , struct node *h2)
{
    static int x;
    x=0;

    
    if(!h1 && !h2)
    {
        return x;
    }
    compare_sub(h1->next,h2->next);
    
    if(x==-1)
        return x;
    else if(h1->data>h2->data)
    {
        x=1;
    }
    else if(h1->data<h2->data && x==0)
    {
        x=-1;
    }
    
    return x;
}

// Truncate Function 
void truncate(struct BigInteger n)
{
    struct node *temp=0,*itr=n.l;

    if(!n.l)
        return;
    while(itr->next)
    {
        if(itr->next->data==0 && temp==0)
        {
            temp=itr;
            itr=itr->next;
            continue;
        }
        if(itr->data!=0 && temp)
        {
            temp=0;
        }  
        itr=itr->next;
    }
    if(itr->data!=0)
    {
        temp=0;
    }

    if(temp)
    {
        itr=temp;
        temp=temp->next;
        itr->next=0;
        while(temp)
        {
            itr=temp;
            temp=temp->next;
            free(itr);
            n.length -=1;
        }
    }
    
}

// Functions for Addition & Subtraction
struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1 )
    {
        if(compare(a,b) == -1)
        return add_positives(b,a,1);
        return add_positives(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return add_negative_positive(b,a,1);
        
        return add_negative_positive(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return add_negative_positive(b,a,-1);

        return add_negative_positive(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return add_positives(b,a,-1);
        return add_positives(a,b,-1);
    }
}
struct BigInteger add_positives(struct BigInteger a,struct BigInteger b , int sign)
{
    struct BigInteger dev;
    dev.sign=sign;
    dev.length=a.length;
    dev.l=0;
    struct node *head=0 , *p1=a.l , *p2=b.l, *itr , *temp;
    int num,carry=0;
    
    while(p2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }

        num=p1->data+p2->data+carry;

        temp->data=num%10;
        carry=num/10;

        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        temp->data=p1->data+carry;
        if(temp->data>0)
        {
            carry=temp->data/10;
            temp->data=temp->data%10;  
        }
        else
        {
            carry=0;
        }
        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
  
        itr->next=temp;
        itr=temp;
        p1=p1->next; 
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        dev.length+=1;
        itr->next=temp;
        temp->data=carry;
        temp->next=0;
    }
    dev.l=head;
    truncate(dev);
    return dev;
}
struct BigInteger add_negative_positive(struct BigInteger a, struct BigInteger b,int sign)
{
    struct BigInteger dev;
    dev.sign=sign;
    dev.l=0;
    dev.length=a.length;
    struct node *head=0 , *p1=a.l , *p2=b.l ,*temp , *itr;
    int num,carry=0;
    reverse_linked_list_sign(p2);
   
    while(p2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }

        num=p1->data+p2->data+carry;
        
        if(num<0)
        {
            temp->data=num+10;
            carry=-1;
        }
        else
        {
            temp->data=num;
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        temp->data=p1->data+carry;
        if(temp->data<0)
        {
            temp->data=temp->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            itr=head=temp;
        }
  
        itr->next=temp;
        itr=temp;
        p1=p1->next; 
    }
    dev.l=head;
    reverse_linked_list_sign(b.l);
    truncate(dev);
    return dev;
}
struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return add_negative_positive(b,a,-1);
      
        return add_negative_positive(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return add_positives(b,a,-1);
        return add_positives(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return add_positives(b,a,1);
        return add_positives(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return add_negative_positive(b,a,1);
        
        return add_negative_positive(a,b,-1);
    }
}

// Multiply Function is a part of the mul function itself
struct BigInteger multiply(struct BigInteger a , struct BigInteger b ,int sign)
{
    struct BigInteger dev;
    dev.l=0;
    dev.sign=sign;
    struct node *itrFront , *pt2 , *itr , *head=0 , *p1=a.l , *p2=b.l;
    int i,num,carry,n=a.length+b.length;
    dev.length=n;
    for (i=1;i<=n;i++)
    {
        struct node *temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation failed\n");
            return dev;
        }
        temp->data=0;
        temp->next=0;
        if(!head)
        {
            head=temp;
        }
        else
        {
            temp->next=head;
            head=temp;
        }
    }
    dev.l=head;
   
    itr=itrFront=head;

    while(p1)
    {
        pt2=p2;
        carry=0;
        while(pt2)
        {
            num=(p1->data)*(pt2->data)+carry;
        
            itr->data += num;
            carry=(itr->data)/10;
            itr->data=(itr->data)%10;
    
            pt2=pt2->next;
            itr=itr->next;
        }
        if(!pt2 && carry>0)
        {
            itr->data += carry;
        }
        itrFront=itrFront->next;
        itr=itrFront;
        p1=p1->next;
    }
    truncate(dev);
    return dev;
}
struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    if(!a.l || !b.l)
    {
        struct BigInteger dev = {0 ,0 ,0};
        return dev;
    }
    if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
    {
        return multiply(a,b,1);
    }
    else
    {
        return multiply(a,b,-1);
    }
    
}


// Functions *duplicate,*division,div1 are for BigInt Division
struct node *duplicate(struct node *head)
{
    struct node *h1=0,*itr, *temp;
    while(head)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return h1;
        }
        temp->data=head->data;
        temp->next=0;
        if(!h1)
        {
            h1=temp;
            itr=temp;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        head=head->next;
    }
    return h1;
}
struct BigInteger division(struct BigInteger a , struct BigInteger b , int sign , int choice)
{
    struct BigInteger dev;
    dev.l=0;
    dev.length=0;
    dev.sign=sign;
    int comp,length=b.length;
    struct node *head=0,*itr,*temp ,*p2=b.l, *head_quotient=(struct node *) malloc(sizeof(struct node));
    if(!head_quotient)
    {
        printf("memory aloocation failed\n");
        return dev;
    }
    
    if((comp=compare(a,b))<1)
    {
        if(comp==0)
        {
            if(choice==0)
            {
                dev.l=duplicate(a.l);
                return dev;
            }
            head_quotient->data=1;
            head_quotient->next=0;
            dev.l=head_quotient;
            dev.length=1;
            return dev;
        }
        if(choice ==0)
        {
            dev.l=duplicate(a.l);
            return dev;
        }
        return dev;
    }
 
    head=duplicate(p2);

    head_quotient->data=1;
    head_quotient->next=0;
    dev.length=1;
    while(a.length>=length+1)
    {
        itr=(struct node *) malloc(sizeof(struct node));
        temp=(struct node *) malloc(sizeof(struct node));
        if(!temp && !itr)
        {
            printf("Memory allocation failed\n");
            return dev;
        }
        temp->data=itr->data=0;
        temp->next=head;
        head=temp;
        itr->next=head_quotient;
        head_quotient=itr;
        length+=1;
    }

    dev.l=head;
    dev.length=length;
    if((comp=compare(a,dev))==-1)
    {
        temp=head;
        head=head->next;
        free(temp);
        temp=head_quotient;
        head_quotient=head_quotient->next;
        free(temp);
        length-=1;
    }
    while(a.length>length)
        div_add(head,b.l,head_quotient,&length);

    dev.l=head;
    dev.length=length;
    while((comp=compare(a,dev))!=-1 && comp != 0)
    {
        div_add(head,b.l,head_quotient,&dev.length);
    }

    if(comp==0)
    {
        if(choice==0)
        {
            dev.l=head_quotient;
            dump(dev);
            dev.l=head;
            dev.length=a.length;
            return dev;
        }
        dev.l=head;
        dump(dev);
        dev.l=head_quotient;
        dev.length=length;
        return dev;
    }
    if(compare(a,dev)==-1)
    {
        div_sub(head,b.l,head_quotient);
        
        truncate(dev);
    }
    if(choice == 0)
    {
        dev.l=head_quotient;
        dump(dev);
        dev.l=head;
        dev.length=a.length;
        truncate(dev);
        return dev;
    }
    dev.l=head;
    dump(dev);
    dev.l=head_quotient;
    truncate(dev);
    return dev;
}
struct BigInteger div1(struct BigInteger a , struct BigInteger b )
{
    struct BigInteger dev ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return dev;
    }
    if(compare(a,b) == -1)
    {
        return dev;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            return division(a,b,1,1);
            
        }
        else
        {
            return division(a,b,-1,1);
        }
    }
}

// Function for Modulus
struct BigInteger mod(struct BigInteger a , struct BigInteger b)
{
    struct BigInteger dev ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return dev;
    }
    if(compare(a,b)== -1)
    {
        dev.l=duplicate(a.l);
        dev.length=a.length;
        return dev;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            dev = division(a,b,1,0);
            
        }
        else
        {
            dev = division(a,b,-1,0);
        }
    }
    if(compare(a,dev)==0)
    
    {
        dev.l=duplicate(a.l);
        dev.length=a.length;
        return dev;
    }
    return add_negative_positive(a,dev,1);
}


// Displaying Functions
void display(struct BigInteger n)
{
    struct node *itr=n.l,*temp;
    if(!itr)
    {
        printf("0\n");
        return;
    }
    if(n.sign==-1 && itr->data || itr->next && n.sign==-1)
    {
        printf("-");
    }
    display_linked_list(n.l);
    printf("\n");
} // For displaying BigInt
void display_linked_list(struct node *head)
{
    if(!head)
    {
        return;
    }
    display_linked_list(head->next);
    printf("%d",head->data);
} // For Displaying Linked List inside BigInt
