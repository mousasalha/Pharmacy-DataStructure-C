
////////////// MOUSA SALHA |_| section 2-DR. Radi |_| BIRZEIT UNIVER |_| PALESTINE ///////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#define NAME_LENGTH 100 //THE MAXIMUM LENGTH OF THE NAME IN INPUT FILE
typedef char String[NAME_LENGTH];
//  name : active ingredient : category : indication : expiry date : count : company
typedef struct // Declare a struct for data
{
    char ch ;
    String Name ;
    char active_i[50];
    char category[30];
    char indication[50];
    char expirydate[30];
    int count;
    char company[30];
} Data;


char inputSource[200] = "meds.txt";
char outputTreePath[200] = "Pharmacy.txt";
char outputHashPath[200] = "Pharmacy.txt";
FILE* IN = NULL;//INPUT FILE NAME
FILE* TREE_OUT_FILE = NULL;//OUTPUT TREE FILE NAME
FILE* HASHTABLE_OUT_FILE = NULL;

struct Node
{
    Data data;
    struct Node* Left;
    struct Node* Right;



    int Height;
};
typedef struct Node* BST;
typedef struct Node* N;


int MSize = 0;
int MoldSize = 0;
struct Node** MEDS = NULL;
int elementsSize = 0;
char deleteLine[500];

BST tree = NULL;
int hash(String Name, int tableSize);//FOR RETURN THE INDEX OF THE NAME DEPEND ON THE TABLE SIZE
bool isPrime(int n);//FOR CHECK IF n IS PRIME NUMBER OR NOT
int reHash(int oldSize);//
int deHash(int oldSize);//
bool hashCheck(int function, int i, int size, struct Node** hashTable);//
void updateHashTable(int flag);//
void addmed(BST T);//
void createHashTable();//
///////////////
void printmeds();//
void printHashTableSize();//
void printHashMethodName();//
void insertmed();//
void searchAboutmed();
void deletemed();//
void saveHashTable();//


int IsEmpty(BST T)
{
    return T == NULL;
}

BST MakeEmpty( BST T )
{
    if(!IsEmpty(T))
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

BST Find( Data D, BST T )
{
    if( IsEmpty(T) )
        return NULL;
    if( strcasecmp(D.Name, T->data.Name) < 0 )
        return Find( D, T->Left );
    else if( strcasecmp(D.Name, T->data.Name) > 0 )
        return Find( D, T->Right );
    else
        return T;
}

int Height( BST P )
{
    if( IsEmpty(P) )
        return -1;
    else
        return P->Height;
}



void CopyData(Data* D, Data Origin)
{

    strcpy(D->Name, Origin.Name);
    strcpy(D->active_i, Origin.active_i);
    strcpy(D->category, Origin.category);
    strcpy(D->indication, Origin.indication);
    strcpy(D->expirydate, Origin.expirydate);
    D->count = Origin.count;
    strcpy(D->company, Origin.company);
}

BST Insert( Data D, BST T )
{
    if( IsEmpty(T) )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof( struct Node ) );
        if( T == NULL )
            printf( "Out of space!\n" );
        else
        {
            CopyData(&T->data, D);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcasecmp(D.Name, T->data.Name) < 0 )
    {
        T->Left = Insert( D, T->Left );

    }
    else if( strcasecmp(D.Name, T->data.Name) > 0 )
    {
        T->Right = Insert( D, T->Right );

    }
    else
        printf("Sorry, but there's a  medicine with this name!\n");
    return T;
}

BST MinValueNode(BST T)
{
    BST L = T;
    while (L->Left != NULL)
        L = L->Left;
    return L;
}
BST findMin(BST T){
    if (T == NULL)
        return T;
    else if (T->Left == NULL)
        return T;
    else
        return(findMin(T->Left));
}

BST Delete(BST T, Data D)
{

    // STEP 1: PERFORM STANDARD BST DELETE
    if (T == NULL)
    {
        printf("No courseName with this name!\n");
        return T;
    }


    if(strcasecmp(D.Name,T->data.Name) < 0)
        T->Left = Delete(T->Left, D);

    // If the D to be deleted is greater
    // than the T's D, then it lies
    // in right subtree
    else if(strcasecmp(D.Name,T->data.Name) > 0)
        T->Right = Delete(T->Right, D);

    // if D is same as T's D, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (T->Left == NULL) || (T->Right == NULL) )
        {
            BST temp = T->Left ? T->Left : T->Right;

            // No child case
            if (temp == NULL)
            {
                temp = T;
                T = NULL;
            }
            else // One child case
                *T = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            BST temp = MinValueNode(T->Right);


            // data to this node
            CopyData(&T->data, temp->data);
            // Delete the inorder successor
            T->Right = Delete(T->Right, temp->data);
        }
        printf("The Medicine with this name deleted!\n");
    }

    return T;
}
N newNode(Data data){

    N node = (N) malloc(sizeof (struct Node));
    node->Left = node->Right = NULL;
    node->Height = 0;


    strcpy(node->data.Name, data.Name);
    strcpy(node->data.active_i, data.active_i);
    strcpy(node->data.category, data.category);
    strcpy(node->data.indication, data.indication);
    strcpy(node->data.expirydate, data.expirydate);
    node->data.count = data.count;
    strcpy(node->data.company, data.company);


    return node;

}
void DisposeBST(BST T)
{
    if(!IsEmpty(T))
    {
        DisposeBST(T->Left);
        free(T);
        DisposeBST(T->Right);
    }
}
// print data in order//////////
void PrintFi(BST T)
{
    if(!IsEmpty(T))
    {
        PrintFi( T->Left );
        if(strcasecmp(T->data.company,"Fiction") == 0)
       {
            printf("%s:%s:%s:%s:%s:%s:%d:%s", T->data.Name, T->data.active_i, T->data.category,
                    T->data.indication,T->data.expirydate, T->data.count, T->data.company);
       }
        PrintFi( T->Right );
    }
}

void PrintNF( BST T)
{

    if(!IsEmpty(T))
    {
        PrintNF( T->Left );
            printf("\n%s %s %s %s %s %d %s", T->data.Name, T->data.active_i, T->data.category,
                    T->data.indication, T->data.expirydate , T->data.count, T->data.company);
        PrintNF( T->Right );
    }
}
//// to search about specific node entered by user and delete the data
BST delete_specific_node(BST T, char key, int *flag){
    BST temp, c;

    if (T == NULL){
        printf("The char (%c) is not found!\n", key);
        *flag = 1;
        return T;
    }// if key less than name go left
    else if (key < T->data.Name)
        T->Left =delete_specific_node(T->Left,key,flag);
    else if (key > T->data.Name)// if key more than name go right
        T->Right =delete_specific_node(T->Right,key,flag);
    else if (T->Left && T->Right){ // to get the data and stored in temp
           // BST temp;
            temp = findMin(T->Right);
            T->data.Name[20] = temp->data.Name[20];
            strcpy(T->data.active_i,temp->data.active_i);
            strcpy(T->data.category,temp->data.category);
            strcpy(T->data.indication,temp->data.indication);
            strcpy(T->data.expirydate,temp->data.expirydate);
            strcpy(T->data.count,temp->data.count);
            strcpy(T->data.company,temp->data.company);
            T->Right = delete_specific_node(T->Right,key,flag);
        }
        else{  // to delete temp and finish the delete
            temp = T;
            if (T->Left == NULL)
                c = T->Right;
            if (T->Right == NULL)
                c= T->Left;
            free(temp);
            return c;
        }
        return T;}
 ///////////////////////////////////////////////////  HASH  ////////////////////////////////////////
int hash(String Name, int tableSize){

    int sum = 0;

    // shift by  5 steps = mul by 2^5 = 32
    // we used mod here for don't make overflow when the String so large length
    for (int i = 0; Name[i] != '\0'; ++i)
        sum = ((sum << 5) + Name[i])% tableSize;

    return sum ;
}
////////////
bool isPrime(int n)
{
    // base case
    if (n <= 1)
        return false;

    // Check from 2 to (n-1) / 2
    for (int i = 2; i <= n/2; i++)
        if (n % i == 0)
            return false;

    return true;
}
/////////////
int reHash(int oldSize){

    int newSize = oldSize * 2;

    while (!isPrime(newSize))
        newSize++;

    return newSize;
}
/////////////
int deHash(int oldSize){

    int newSize = oldSize / 2;

    while (!isPrime(newSize))
        newSize--;

    return newSize;
}
////////////
bool hashCheck(int function, int i, int size, struct Node** hashTable){

    int c = (function + (i*i)) % size;//Quadratic Hashing Function
    if(hashTable[c] == NULL)
        return false;//RETURN FALSE FOR STOP THE LOOP IN addPatient and updateHashTable Methods

    return true;
}

//////////////
void createHashTable()
{

    MSize = reHash(MSize);//FOR DEFINE INITIAL SIZE FOR THE HASH TABLE
    MEDS = (struct Node**) malloc((sizeof (struct Node*)) * MSize);//FOR CREATE THE PATIENTS  HASH TABLE
    for (int i = 0; i < MSize; ++i)
        MEDS[i] = NULL;



    addmed(tree);//FOR ADD THE NODES FROM THE AVL TREE TO THE PATIENTS HASH TABLE

}
/////////////
void addmed(BST root){


    if (root != NULL){


        addmed(root->Left);//ADD THE NAME WHICH EXIST AT LEFT SUBTREE
        addmed(root->Right);//ADD THE NAME WHICH EXIST AT RIGHT SUBTREE


        if ( (int) (0.75 * MSize) <= elementsSize)//WHEN THE TABLE 75% FULL THEN UPDATE IT
            updateHashTable(1);

        Data save = root->data;
        N node = newNode(save);
        free(root);


        int i = 0;
        int index = hash(node->data.Name, MSize);//RETURN THE INDEX OF THE PATIENT NAME
        bool update = false;//FOR CHECK IF THE HASH TABLE IS FULL OR NOT

        //FOR SEARCH ABOUT THE EMPTY POSITION AT HASH TABLE
        while (hashCheck(index, i, MSize, MEDS)) {

            if (i > MSize) {
                update = true;//WHEN THE VALUE CAN'T FIND ANY PLACE FOR IT IN THE ARRAY
                break;
            }

            i++;
        }


        if (update) {
            updateHashTable(1);//FOR UPDATE THE HASH TABLE
            addmed(node);
        }
        else
        {
            index = (index + (i*i)) % MSize;//FOR RETURN THE CORRECT POSITION AT HASH TABLE FOR INSERT THE MEDICINE
            MEDS[index] = node;
            elementsSize++;
        }

    }

}
/////////////////////////////
void updateHashTable(int flag){
    int oldsize = MSize;

    if (flag == 1)
        MSize= reHash(MSize);
    else if (flag == 2)
        MSize=deHash(MSize);
     struct Node** newHashTable = (struct Node**) malloc((sizeof (struct Node*)) * MSize);
         for (int i=0; i < MSize;++i)
            newHashTable[i]=NULL;

         for(int i=0;i<oldsize;++i){
            if (MEDS[i] !=NULL){
                int index = hash(MEDS[i]->data.Name,MSize);
                int j=0;

          while (hashCheck(index, j, MSize, newHashTable))
            j++;




            index = (index + (i*i)) % MSize;
            newHashTable[index] = MEDS[i];
            }
         }
         free(MEDS);
         MEDS= newHashTable;

         if(flag==1)
            MoldSize=oldsize;
         if(flag==2){
            if(MSize!=2)
            MoldSize=deHash(MSize);
         else
            MoldSize=0;


         }

}
///////////

////////////////////////////////////////////////////////

void readh(){

    /*IN = fopen("Pharmacy.txt", "r");
        if(IN == NULL)
        printf("THE FILE NOT FOUNDED");
        else {


        char line[500];//THE MAXIMUM LENGTH OF EACH LINE IN THE FILE INPUT EQUAL 500 CHARACTERS

*/
        char line[500];
        //FOR SAVE ALL LINES IN THE INPUT FILE AS NODES IN THE AVL TREE
        while (fgets(line, 500, IN)) {

            int *splitBy = ":";//divide the line when read ":"
            char *edge = strtok(line, splitBy);//save the divided edge line
            int flag = 0;//counter for the number of edges at line
            Data data;//save the line information at data
            while (edge != NULL) {
                if (flag == 0)

                    strcpy(data.Name,edge );//FOR SAVE THE NAME EDGE
                    edge = strtok(NULL, splitBy);
        //FOR MAKE NEW EDGE FROM THE LINE
                FILE* IN = fopen("Pharmacy.txt", "r");//FOR OPEN THE OUTPUT FILE

    for (int i = 0; i < MSize; ++i)
        fprintf(IN, "Index : %d\t Name: %s\n", i, MEDS[i]->data.Name);

            //fclose(TREE_OUT_FILE);//FOR CLOSE THE OUTPUT FILE

    fclose(IN);//FOE CLOSE THE INPUT FILE


        flag++;  }}}

////////////////////////////////////////////////////////////////print hash functions/////////////////
void printmeds() {

    for (int i=1; i <= MSize;++i)   {
        printf("Index : %d\t Name: \t \n", i);
    }

}
//////////////////////////
void printHashTableSize(){

    printf("\nThe Size Of Hash Table is : %d\nThe Number Of Elements In The Table is : %d\n", MSize, elementsSize);

}
void printHashMethodName(){
    printf("\nI USED Hashing String Third Type (Shift By 5) BY Quadratic Hashing\n");
}
//////////////////////
void insertmed(){
    printf("Insert The medicine information\n");
    Data data;

    printf("Enter the Name  : ");
    gets(deleteLine);
    gets(data.Name);
    printf("\n");

    printf("Enter the active_i : ");
    //gets(deleteLine);
    gets(data.active_i);
    printf("\n");

    printf("Enter the category : ");
    //gets(deleteLine);
    gets(data.category);
    printf("\n");

    printf("Enter the indication : ");
    //gets(deleteLine);
    gets(data.indication);
    printf("\n");


    printf("Enter the expiry date : ");
    //gets(deleteLine);
    gets(data.expirydate);
    printf("\n");

    printf("Enter the count : ");
    //gets(deleteLine);
    gets(&data.count);
    printf("\n");

    printf("Enter the company : ");
    //gets(deleteLine);
    gets(data.company);
    printf("\n");


    printf("Thx For Enter The medicine Information\n");

    N node = newNode(data);

    addmed(node);
}
//////////////////
void searchAboutmed(){

    printf("\nWrite The Name Of The Medicine : ");
    String Name;
    gets(deleteLine);
    gets(Name);


    int function = hash(Name, MSize);
    int i =0;

    int index = (function + (i*i)) % MSize;//FOR RETURN THE FIRST POSITION AT HASH TABLE FOR THE REQUIRED NAME

    while (true){
        if(i > MSize)//WHEN WE CHECKED ALL POSSIBILITIES
        {
            printf("\nThere Isn't medicine With This Name \n");
            break;
        }
        else if (MEDS[index] == NULL)//WHEN WE FIND EMPTY AREA WHERE THIS NAME SHOULD BE THERE
        {
            printf("\nThere Isn't medicin With This Name \n");
            break;
        }
        else if (strcmp(Name, MEDS[index]->data.Name) == 0)//IF WE REACH THE RIGHT POSITION THEN WE SHOULD CHECK IF THE NAME SAME AT THE TABLE
        {

            printf("\nName: %s\nactive_i: %s\ncategory: %s\nindication: %s\nexpiry date: %s\ncount: %d\ncompany: %s\n"
                    , MEDS[index]->data.Name, MEDS[index]->data.active_i, MEDS[index]->data.category,
                     MEDS[index]->data.indication, MEDS[index]->data.expirydate, MEDS[index]->data.count
                    , MEDS[index]->data.company);
            break;

        }


        i++;
        index = (function + (i*i)) % MSize;
    }




    }

/////////////////////////////////
void deletemed(){


    printf("\nWrite The Name Of The medicine : ");
    String Name;
    gets(deleteLine);
    gets(Name);




    int function = hash(Name, MSize);
    int i =0;

    int index = (function + (i*i)) % MSize;//FOR RETURN THE FIRST POSITION AT HASH TABLE FOR THE REQUIRED NAME

    while (true){
        if(i > MSize)//WHEN WE CHECKED ALL POSSIBILITIES
        {
            printf("\nThere Isn't medicine With This Name \n");
            break;
        }
        else if (MEDS[index] == NULL)//WHEN WE FIND EMPTY AREA WHERE THIS NAME SHOULD BE THERE
        {
            printf("\nThere Isn't medicine With This Name \n");
            break;
        }
        else if (strcmp(Name, MEDS[index]->data.Name) == 0)//IF WE REACH THE RIGHT POSITION THEN WE SHOULD CHECK IF THE NAME SAME AT THE TABLE
        {

            free(MEDS[index]);//FOR DELETE THE RECORD
            MEDS[index] = NULL;
            elementsSize--;
            printf("THE DELETE OPERATION FOR %s DONE\n", Name);



            if ( (int) (0.75 * MoldSize) > elementsSize)//WHEN THE TABLE HAS MANY EMPTY PLACES
                updateHashTable(2);

            break;

        }


        i++;
        index = (function + (i*i)) % MSize;
    }



}
///////////////////
void saveHashTable(){
    FILE* HASHTABLE_OUT_FILE ;

    HASHTABLE_OUT_FILE = fopen("Pharmacy.txt", "w");//FOR OPEN THE OUTPUT FILE

    for (int i = 0; i < MSize; ++i)
        fprintf(HASHTABLE_OUT_FILE, "Index : %d\t Name:\n", i, MEDS[i]->data.Name);


    fclose(HASHTABLE_OUT_FILE);//FOR CLOSE THE OUTPUT FILE



}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions..
void printMenu() // Just Print..
{
    printf("           MOUSA SALHA |_| Section 2 |_| BIRZEIT UNIVER |_| PALESTINE \n");
    printf("                                     Menu \n");

  //  printf("**choice from 1 to 10 is for binary search tree \n**choice 8 is to EXIT \n**choice from 12 to 18 is for Hash \n\n");
    printf("                Write the number of the option that you want\n\n");
    printf("         1. Read the data that store in file meds.txt and create BST .\n");
    printf("                    2. Add a new Medicine to the system.\n");
    printf("      3. Search for a Medicine by name or active ingredientin in the system.\n");
    printf("                 4.  Update or delete a specific Medicine .\n");
    printf("                 5. Show the Medicines in alphabetical order .\n");
    printf("                 6.list the medicines with a specific disease .\n");
    printf("                        7. Save the data to the file.\n");
    printf("                          8. Exit the application.\n");
    printf("                    9. list medicine belong same category.\n");
    printf("                 10. delete medicines belong specific company.\n");
    printf("                          12. Print hashed table.\n");
    printf("                          13.Print out table size.\n");
    printf("                     14.Print out the used hash function.\n");
    printf("                 15. Insert a new record into the hash table.\n");
    printf("                       16. Search for a specific record.\n");
    printf("                        17. Delete a specific record .\n");
    printf("                18. Save hash table back to file Pharmacy.txt.\n");



}

int Confirmed(char ConfirmOption[]) // print a confirm message and scan the input
{
    printf("\tAre you sure to complete this process?\n\t- Press any key except 1 to cancel -\n\t    1. Yes\n");
    scanf("%s", ConfirmOption);
    if(atoi(ConfirmOption) == 1 && strlen(ConfirmOption) == 1) // if the input is 1 return true, else return false
        return 1;
    return 0;
}

char* Trim(char *S) // Remove the white spaces
{
    int i, j;
    for(i=0; S[i]==' '||S[i]=='\t'; i++); // to make 'i' equals the first UnSpace character's Location

    for(j=0; S[i]; i++)
    {
        S[j++]=S[i]; // to copy the string without the left white space
    }
    S[j]='\0'; // insert the null character
    for(i=0; S[i]!='\0'; i++) // while 'i' doesn't equal the null character
    {
        if(S[i]!=' '&& S[i]!='\t') // reach the last UnSpace character's location
            j=i;                  // and put it in 'j'
    }
    S[j+1]='\0'; // insert the null character after the last UnSpace character
    return S;
}

void ReadFile(BST *T, Data* D) // Read courseNames.txt File
{

char c ;
    char temp[100]; // To store the scanned line
    *T = MakeEmpty(*T) ; // to provide the repeated scanning..
    FILE* in = fopen("meds.txt","r");
    if(in == NULL)
    {
        printf("Error in opening the file!\n");
        return;
    }
    while(fscanf(in, "\n%[^\n]s", temp)!= EOF) // if there is a line to scan..
    {
        // split by "|",remove the white spaces and store them in a suitable place..
        strcpy(D->Name, Trim(strtok(temp,":")));
        strcpy(D->active_i, Trim(strtok(NULL,":")));
        strcpy(D->category, Trim(strtok(NULL,":")));
        strcpy(D->indication, Trim(strtok(NULL,":")));
        strcpy(D->expirydate, Trim(strtok(NULL,":")));
        D->count = atoi(Trim(strtok(NULL,":")));
        strcpy(D->company, Trim(strtok(NULL,"\n")));
            *T = Insert( *D, *T);

    }
    if(IsEmpty(*T))
        printf("File is Empty!\n");
    else
        printf("The Input file has been read correctly!\n");
    fclose(in);
}
///////////

void Scancompany(Data *D, int flag) // To Scan the inputs from user (Not from File)
{
    if(flag){ // sometime we don't need scanning the courseName's name
    printf("Enter the  specify desase to list medicine for it:\n");
    scanf("\n%s", D->company);}

}
/////////////

void ScanmedName(Data *D, int flag) // To Scan the inputs from user (Not from File)
{
    if(flag){ // sometime we don't need scanning the courseName's name
    printf("Enter Medicine Name:\n");
    scanf("\n%[^\n]s", D->Name);
    }
    printf("Enter active ingredient:\n");
    scanf("\n%[^\n]s", D->active_i);
    printf("Enter the  category:\n");
    scanf("\n%[^\n]s", D->category);
    printf("Enter the  indication:\n");
    scanf("\n%[^\n]s", D->indication);
    printf("Enter the  expiry date:\n");
    scanf("\n%[^\n]s", D->expirydate);
    printf("Enter the count :");
    scanf("%d", &D->count);
    printf("Enter the company:\n");
    scanf("\n%[^\n]s", D->company);
}

void WriteFile(BST T, FILE* out) // Write to the Pharmacy.txt File
{
    if(T != NULL)
    {
        WriteFile(T->Left, out); // Print Data in the file
        fprintf(out,"%s:%s:%s:%s:%s:%d:%s \n", T->data.Name, T->data.active_i, T->data.category,
                    T->data.indication,T->data.expirydate, T->data.count, T->data.company);
        WriteFile(T->Right, out);
    }
}

void Displayactive_i(Data D, BST T, int* flag) // Print
{
    if(!IsEmpty(T))
    {
        Displayactive_i(D, T->Left, flag);
        if(strcasecmp(T->data.active_i,D.active_i) == 0)
        {
            printf("\n the name is || %s\n", T->data.Name);
            *flag = 1;
        }
        Displayactive_i(D, T->Right, flag);
    }
}

void Displayindication(Data D, BST T, int* flag) // Print
{
    if(!IsEmpty(T))
    {
        Displayindication(D, T->Left, flag);
        if(strcasecmp(T->data.indication,D.indication) == 0)
        {
            printf("\n the name is || %s\n", T->data.Name);
            *flag = 1;
        }
        Displayindication(D, T->Right, flag);
    }
}
void Displaycat(Data D, BST T, int* flag) // Print
{
    if(!IsEmpty(T))
    {
        Displaycat(D, T->Left, flag);
        if(strcasecmp(T->data.category,D.category) == 0)
        {
            printf("\n the name is || %s\n", T->data.Name);
            *flag = 1;
        }
        Displaycat(D, T->Right, flag);
    }
}
int main()
{
    createHashTable();
    BST tree = NULL;   // Create BST tree that we will use in functions by passing it
    tree = MakeEmpty(tree);
    Data D ; // Create a struct Data that we will need it to store the data temporary in some operations
    char Option[3], TempOption[3]; // To Scan the option from user
    do // do the statements below at least once
    {
        printMenu(); // call function to print menu
        scanf("%s", Option);
        if(strlen(Option) > 3) // because the options have one character
            strcpy(Option,"0") ;
        switch(atoi(Option)) // switch to know what is the option
        {
        case 1 : // if Option is 1..
            if(!IsEmpty(tree)) // if there are a held data ..
            {
                printf("The currently held  will be lost\n"); // print a message
                if(Confirmed(TempOption)) // and ask to confirm this process
                    ReadFile(&tree, &D); // Call function to read
            }
            else  // if there is no held data
                ReadFile(&tree, &D); // Call function to read
            break;
        case 2 : // if Option is 2..
            ScanmedName(&D, 1); // take data from user for the new courseName

                tree = Insert(D, tree); // insert the new courseName
                printf("The Medicine has been added!\n");

        case 3 : // if Option is 3..
            if(IsEmpty(tree)) // if there is no held data..
            {
                printf("\tThere is no Medicines to search!\n"); // print this message
                break; // and don't continue
            } // if there are held data..
            printf("--------------------------------------------\n\n");   //  print this message to select
            printf("\tWrite the number of the option that you want\n");    // which type of searching we will use
            printf("1. Search using Name    2. Search using active ingredient \n");
            scanf("%s",TempOption);
            if((atoi(TempOption) == 1 || atoi(TempOption) == 2) && strlen(TempOption) == 1) // if option is 1 or 2..
            {
                if(atoi(TempOption) == 1) // if option is 1..
                {
                    printf("Enter medicine Name:\n"); // Scan the Name
                    scanf("\n%[^\n]s", D.Name);
                    if(Find(D, tree) != NULL) // if the Name exists..
                    {
                        CopyData(&D, Find(D, tree)->data); // Copy the data to D & print it
                        printf("%s:%s:%s:%s:%s:%d:%s\n", D.Name, D.active_i, D.category, D.indication, D.expirydate,D.count,D.company);
                    }
                    else
                        printf("Can't Found!\n");
                }
                else // if option is 2..
                {
                    printf("Enter active ingredient:\n"); // Scan active_i's name
                    scanf("\n%[^\n]s", D.active_i);
                    int flag = 0;
                    Displayactive_i(D, tree, &flag); // print his courseName/s
                    if(!flag) // if there's no Name for this active_i, print a message
                        printf("Can't Found!\n");
                }
            }
            else // if the scanned option is not 1 or 2 ..
                printf("     Sorry but your input is not correct!\n"); // print this message and break
            break;
        case 4 : // if Option is 4..
            if(IsEmpty(tree)) // if there is no held data..
            {
                printf("\tThere is no Medicine to update!\n"); // print this message
                break; // and don't continue
            } // if there are held data..
            printf("--------------------------------------------\n\n");   //  print this message to select
            printf("Write the number of the option that you want\n");
            printf("1. Update a Medicine  \t  2. Delete a Medicine\n");
            scanf("%s",TempOption);
            if((atoi(TempOption) == 1 || atoi(TempOption) == 2) && strlen(TempOption) == 1) // if option is 1 or 2..
            {
                printf("Enter Medicine Name:\n"); // Scan Name
                scanf("\n%[^\n]s", D.Name);
                if(Find(D, tree) != NULL) // if the Name is exists..
                {
                    if(atoi(TempOption) == 1) //  if the option is 1
                    {
                        // scan the information from user
                        ScanmedName(&D, 0);
                  {
                            CopyData(&Find(D, tree)->data, D); // Put the new data..
                            printf("Medicine information update!\n");


                   } }else
                        tree = Delete(tree, D);
                }
                else
                    printf("Can't Found!\n");
            }
            else  // if the scanned option is not 1 or 2 ..
                printf("     Sorry but your input is not correct!\n"); // print this message and break
            break;
        case 5 : // if Option is 5..
            if(IsEmpty(tree))
            {
                printf("\tNo courseNames to show!\n");
                break;
            }
             // Print in alphabetical order
            PrintFi(tree);
            PrintNF(tree);
            printf("\n");
            break;
        case 6 : // if Option is 6..
            printf("Enter the indication to list:\n"); // Scan active_i's name
                    scanf("\n%[^\n]s", D.indication);
                    int flag = 0;
                    Displayindication(D, tree,D.indication);
                  //  printf("%s\n",  D.Name  );
            break;
        case 7 : // Save Data..
            if(IsEmpty(tree)) // if no data print a message
            {
                printf("There is nothing to save!\n"); // print a message to explain}
                break;
            }
            FILE* out = fopen("Pharmacy.txt","w");
            WriteFile(tree, out); // call function to write
            fclose(out);
            printf("The data saved!\n");

            // after save read file to hash
            readh();
            createHashTable();
            break;
        case 8 :
            break;
        case 9 :
            printf("Enter the category to list :\n"); // Scan category
                    scanf("\n%[^\n]s", D.category);
                    Displaycat(D, tree,D.category);
                    break ;
        case 10 :
             printf("Enter company:\n"); // Scan Name
                scanf("\n%[^\n]s", D.company);
                Scancompany(&D, 0);
                tree = Delete(tree, D);
                break ;

        case 11 :
            printf("Enter Medicine company:\n"); // Scan Name
                scanf("\n%[^\n]s", D.company);
                if(Find(D, tree) != NULL){

               tree = Delete(tree, D);}
            break ;

            case 12:
                printmeds();
                break;
            case 13:
                printHashTableSize();
                 break;
            case 14:
                printHashMethodName();
                break;
            case 15:
                insertmed();
                break;
            case 16:
                searchAboutmed();
                  break;
            case 17:
                deletemed();
                  break;
            case 18:
                saveHashTable();
                printf("saved in Pharmacy.txt\n");
                  break;

            default: // if the previous options don't include the scanned option
            printf("Sorry but this thing does not exist!\n");
        }
    }
    while(atoi(Option) != 8); // if option 8 had not chosen, do the do-while loop one more time
    DisposeBST(tree);
    // At the end, free the tree
    return 0;
}
