#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*********************
 FINAL PROJECT: Dictionary Manipulation
 STUDENT ID: 4000042302
 NAME: Jordan Bravo
*********************/

//Initializing global data types.
char wordArray[100][99];
int word = 0;

//Function demanding user to press ENTER to return to main menu.
void PressKeyToContinue(){

    //fflush to flush output buffer.
    fflush(stdin);
    printf("\nPress ENTER to return to the main menu...");

    //while loop until user presses ENTER.
    while(getchar() != '\n'){
    printf("\nPress ENTER to return to the main menu...");
        getchar();
    }

    printf("\n");
}

//Function to create menu. Called at beginning of while loop in main.
void MainMenu(){

    printf("\n\t~Main Menu~\n\n");
    printf("  1. Print the dictionary.\n  2. Search a word in the dictionary.\n  ");
    printf("3. Group of letters.\n  4. Quit.\n\nMake a Selection (1-4): ");

}

void PrintDictionary(){

    printf("\nPrinting dictionary...\n\n");
    for(int i = 0; i < word; ++i){
        printf("%s", wordArray[i]);
            if(i != 0){
                if(wordArray[i][0] == wordArray[i+1][0]){
                    printf("\t");
                }
                else{
                    printf("\n");
                }
            }
        else{
            printf("\t");
        }
    }

    printf("\n\nDictionary finished printing.\n");
    PressKeyToContinue();
}

//Function to locate user word in dictionary.
void WordSearch(){

    int k = 0, i, j;
    char userWord[99];

    printf("\nEnter word you wish to find in the dictionary: ");
    scanf("%s", userWord);
    bool letterFound = false;
    bool wordFound = false;

    //For loop to check through each word.
    for(i = 0; i < word; ++i){
    /*
    For loop to check through each letter in each word from dictionary
    and compare with user word.
    */
        for(j = 0; isalpha(wordArray[i][j]); ++j){
            if(userWord[k] == wordArray[i][j]){
                letterFound = true;
            }
            else{
                letterFound = false;
            }
            if(letterFound == false){
                k = 0;
            }
            else{
                ++k;
            }
        }
        if(k == strlen(userWord)){
            printf("The word \"%s\" was found in the dictionary.\n", userWord);
            wordFound = true;
            break;
        }
    }

    if(wordFound == false){
        printf("The word \"%s\" was NOT found.\n", userWord);
    }

    PressKeyToContinue();
}

//Function to set values in user word counter to 0.
void ArrayCountReset(int* arrayCount){

    //Sets every value in arrayCount to 0.
    for(int i = 0; i < 26; ++i){
        arrayCount[i] = 0;
    }
}

//Function to set values in dictionary word counter to 0.
void WordArrayCountReset(int* wordArrayCount){

    //Sets every value in wordArrayCount to 0.
    for(int i = 0; i < 26; ++i){
        wordArrayCount[i] = 0;
    }
}

//Function to convert to lowercase lettering only.
void LowercaseLetterArray(char *userStr){
    char *tempArray;
    int i, j = 0;

    tempArray = (char*)malloc(sizeof(userStr));

    //For loop to remove non-letter and convert uppercase letters to lowercase letter.
    for(i = 0; userStr[i] != '\0'; ++i){
        //if statement if letter in word is alphabet letter.
        if(isalpha(userStr[i])){
            //if statement to check if uppercase.
            tempArray[j] = tolower(userStr[i]);
            tempArray[j + 1] = '\0';
            ++j;
        }
    }

    //copying new array with only lowercase letters into user string and reallocating space.
    strcpy(userStr, tempArray);
    userStr = (char*)realloc(userStr, sizeof(tempArray) + 1);
    free(tempArray);
}

//Function that's called when user inputs '3' to check for words possible through user inputted scramble of letters.
void LetterCheck(){

    bool wordFound;
    int i, j, k;
    int c = 1;
    char *userStr;
    int *wordArrayCounter, *userArrayCounter;

    userStr = (char*)malloc(100 * sizeof(char));

    printf("Enter the word scramble(99 letters max): ");
    scanf("%s", userStr);

    //function call to remove and convert to lowercase lettering only.
    LowercaseLetterArray(userStr);

    //Allocating memory for counter pointers for both user string and dictionary string(per word).
    userArrayCounter = (int*)malloc(27 * sizeof(int));
    wordArrayCounter = (int*)malloc(27 * sizeof(int));

    //Function call to set arrays 0 - 25 to contain a '0' value.
    ArrayCountReset(userArrayCounter);
    WordArrayCountReset(wordArrayCounter);

    //For loop to check letter by letter and tally it into an array to compare with each word in dictionary.
    for(i = 0; isalpha(userStr[i]); ++i){
        //Checks through the user array to see letter by letter and tallied into userArrayCounter;
        for(j = 0; j < 26; ++j){
            //If user word has letter, userArrayCounter[j] has a value added.
            if(userStr[i] == 'a' + j){
                userArrayCounter[j] += 1;
            }
        }
    }

    printf("\n%s:\n\n", userStr);

    //For loop to go through word by word.
    for(i = 0; i < word; ++i){
        //For loop to go through each letter in the corresponding word.
        for(j = 0; j <= strlen(wordArray[i]); ++j){
            //For loop to check for each letter in alphabet and match it with corresponding word in the array.
            for(k = 0; k < 26; ++k){
                //If dictionary word has letter, wordArrayCounter[k] has a value added.
                if(wordArray[i][j] == 'a' + k){
                        ++wordArrayCounter[k];
                }
            }
        }
        /*
        When length of word has been reached, this for loop then checks through each letter and compares
        with the userArrayCounter. If condition is correct, wordFound maintains true.
        */
        for(j = 0; j < 26; ++j){
            if(wordArrayCounter[j] <= userArrayCounter[j]){
                wordFound = true;
            }
            //If prior condition is not met, wordFound is false and loop breaks.
            else{
                wordFound = false;
                break;
            }
        }
        /*
        If wordFound is true, then the word can be made through user's word scramble.
        The corresponding dictionary word gets outputted.
        */
        if(wordFound){
            printf("\t(%d) %s", c, wordArray[i]);
            printf("\n");
            ++c;
        }
        /*
        The counter for the word is reset when primary for loop reaches the end and the process
        repeats for every word in dictionary stored in wordArray.
        */
        WordArrayCountReset(wordArrayCounter);
    }

    //Memory is freed from both counters and userStr and function call to return to menu is called.
    free(userArrayCounter);
    free(wordArrayCounter);
    free(userStr);
    PressKeyToContinue();
}

int main()
{
    //Initializing data types.
    FILE* fptr = NULL;
    int location;
    int userInput = 0;

    //Opening the dictionary file.
    fptr = fopen("dictionary.txt", "r");

    //An if statement to check if file is found/not found.
    if (fptr == NULL) {
        printf("Failed to open dictionary file 'dictionary.txt'.");
        return -1;
    }

    //Scanning words from file into array. fseek() updates location of file pointer until EOF.
    while(!feof(fptr)){
        fseek(fptr, location, SEEK_SET);
        fscanf(fptr, "%s", wordArray[word]);

        location = ftell(fptr);

        ++word;
    }
    //Closing file when all words in dictionary have been copied to array.
    fclose(fptr);

    //While loop until user inputs '4' to exit program.
    while (userInput != 4){
        MainMenu();
        scanf("%d", &userInput);

        //Function call to print dictionary when user inputs '1'.
        if (userInput == 1){
            PrintDictionary(wordArray);

            //system("cls") used to clean output screen.
            system("cls");
        }

        //Function call to search through dictionary for user word when user inputs '2'.
        if (userInput == 2){
            WordSearch(wordArray);

            //system("cls") used to clean output screen.
            system("cls");
        }

        //Function call to check user word scramble for possible words from dictionary when user inputs '1'.
        if (userInput == 3){
            LetterCheck();

            //system("cls") used to clean output screen.
            system("cls");
        }
    }

    return 0;
}
