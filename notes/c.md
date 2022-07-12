# CMD Line to Run C Program
1. ```clang <filename>.c -o <filename> <linker (ie -lcs50)>```
2. ```./<filename>```
## Example
1. ```clang hello.c -o hello -lcs50```
2. ```./hello```
# Boilerplate
```c
#include<stdio.h>
int main(void)
{
    ---enter code---
}
```
# Adding C Packages
1. Download packages
    - The **.c** and **.h** files
2. Right click on the <stdio.h> that is already in the program
3. Click on _Go To Definition_
4. Click on the file (in the navigation pane at the top)
5. Click on _Reveal in Finder_
6. Drag and drop downloaded __.c__ and __.h__ files into the pop-up folder (should be **_~/include_**)
# Char Data Type
__Must use single quotes, such as ```'a'```, in order for code to work__

-----
# Functions
## Format
```c
returnValue name(inputValues)
{

}
```
## Important Note
**Must declare and define function above _main_ OR declare function above _main_ and define below _main_**
## Formatting
```c
void myFunc(void);

int main (void)
{
    myFunc();
}

void myFunc(void)
{

}
```
### OR

```c
void myFunc(void) 
{

}

int main(void)
{
    myFunc();
}
```

-----
# Do-While Loop
Essentially, <span style="color : red"><b><i>do</i></b></span> something <span style="color : red"><b><i>while</i></b></span> a certain condition is met...
## Example
```c
int i;
do
{
    i = get_int("Enter value: ")
}
while (i < 1);
```
## <span style="color : orange"><b>What is happening?</b></span>
In the example shown above, the program will ask the user for input (whatever is in the curly braces after the <span style="color:red"><b>do</b></span> keyword) and check it against the <span style="color:red"><b>while</b></span> condition. From here, <span style="color:orange"><b>2</b></span> things can happen:
1. If the <span style="color:red"><b>while</b></span> condition is met, the program will loop back to the do portion, and repeat the process
2. If the <span style="color:red"><b>while</b></span> condition is _**not**_ met, then the program will break out of the <span style="color:orange"><b>do-while</b></span> loop and continue to the rest of the code.
# Note on Imprecision
<span style="color:black">*Floating-point imprecision can result in inaccuracies when requiring a number to be extremely specific. You might need to round at times or go with double data type*</span>

-------

# Sharing functions amongst C Files
## Command Line call
```terminal
clang <filename>.c <filename w/ functions>.c -o <filename (exectuable)> <linker (ie -lcs50)>
```
__Must declare functions in the main file above__ <span style="color:orange"><i><b>main</b></i></span> __function.__
## Example
### Main file (main.c)
```c
#include <cs50.h>
#include <stdio.h>

void myFunc1(int n);
char myFunc2(double i);

int main (void)
{
    // example code
    myFunc(4);
    char a = myFunc2(5.2545);
}
```

### File containing function (myFunctions.c)
```c
void myFunc1(int n)
{
    // code
}

char myFunc2(double i)
{
    // code
}
```
### Command Line Call
```terminal
clang main.c myFunctions.c -o main -lcs50
```
------
# Debugging
## How to Debug C code
1. Add breakpoints
2. Open **executable** file of C program
3. Hit <kbd>⌘CMD + ⇧SHIFT + P</kbd> and type `debug` into the **Command Pallette** on the <span style="color:red"><b>C</b></span> file. After this, you can just does it with <kbd>F5</kbd> on the <span style="color:red"><b>executable C</b></span> file.
<i>opens terminal, which will output as you debug, good to have <b>DEBUG CONSOLE</b> open at the time as well </i> 
## Set up
1. open <u>**launch.json**</u>
2. Click <span style="color:red"><i>Add Configurations</i></span> in bottom right
3. Select <span style="color:red"><i>C/C++: (lldb) Launch </i></span>
4. Set <span style="color:lightblue">"program"</span>: <span style="color:orange">"${file}</span>
5. Set <span style="color:lightblue">"externalConsole"</span>: <span style="color:blue">true</span>
# Arrays
## Declaring an array
```c
<data_type> <name>[length];
```
### Example
```c
double numbers[5];
```
## Initializing an array
```c
<data_type> <name>[length] = {element, element,...};
```
### Example
```c
double numbers[5] = {1.223, 5.3234, 342.42, 526.32, 234};
```
## Indexing
Get first element and store in variable?
```c
double a = numbers[0];
```
Get third element and store in variable?
```c
double b = number[2];
```
***You can access indexes outside of the array, this will not give an error in C but it may cause a segmentation fault***

***Note: similar to arrays in Java***

***You cannot assign 1 array to another with '=', you must iteratre through each character and copy it into the new array***
# Working with Strings as Char
## What are Strings in C?
`String` is **not** a data-type that comes built-in with <span style="color:red">C</span>. 
The `cs50` library contains the code that creates a `string` data type that we can then use.
### How are Strings created in the CS50 Library?
Through the use of the `char` data type.
The `char` data type would allow a variable to store a single character. 
<span style="color:red">Strings</span> could be, essentially, considered an **array of `char`**.
### Consider through the use of printf() and a loop
For example, if we wanted to print out "ABC" using `string`, we could do `printf("ABC");`. However, if we were not given the `cs50` library, we could also do the following:
```c
char abc[3] = {'A','B','C'};

for (int i = 0; i < 3; i++) {
    printf(%c,abc[i]);
}

printf("\n");
```
Both, the code block shown above and `printf("ABC\n");`, would result in the <span style="color:orange"><b>same</b></span> output: `ABC` in the terminal/console.
### Going back to how Strings are created...
So now that we know that `strings` can be represented as arrays of `char`, the creators of `cs50` could have leveraged that ability. So, the `string` data type created by `cs50` is essentialy just an array of each inidividiual character (`char`) in the string.
### Therefore, we can work with `strings` as `char`
***We are actually able to access each character in a string in the same way we can access elements in an array.*** Because a variable of a `string` data type is just an array of `chars`, we can do the following to access each individual character:
```c
string a = "kasdhfahfaewi";
/* access the third letter in the variable initialized above 
and store it in a variable */
char letter = a[2];
```
**Important Note: `char` data types can be casted as `int` data types, in which case the output would be the ASCII values of the `char` variable**
### How do we know when a string ends in memory?
Memory allocates an extra byte as a <span style="color:red"><b>null</b></span> value. The null value of a char is denoted as `NUL` and `'\0'`.

------
# Taking Arguments in the Command Line (CLI)
## Example
```c
#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // code
}
```
## What are `argc` and `argv`?
Essentially, they allow the user to enter command-line arguments. Prior to this, we declared our <span style="color:red"><b>main</b></span> function as `int main(void)`. In this case, the `void` meant that the program would ***not*** take any command line arguments (meaning, no arguments can be given in the command line at ./{filename}). However, by passing in `int argc` and `string argv[]`, we do <span style="color:orange"><b>3</b></span> things:
1. We allow the user to input command line arguments. An example with a file named `test` would be:
    * `./test hello` where `hello` is one command line argument, and in this case, we can pass in however many arguments.
2. `int argc` stores the <u>number of arguments</u> that we pass into the **CLI** in `argc`.
3. `string argv[]` <u>creates an array</u> of all the arguments that are passed into the **CLI** post `./<filename>` and stores them in an array named `argv`.

-------
# Exit Statuses
## What are they?
Basically, you return a value form the main function that describes your error or what went wrong. If something went wrong, you should return a <span style="color:red">non-zero</span> value, if everything works perfectly, you should return <span style="color:green"><b>0</b></span>. 
## Example
We want to take user input, but our code will only work if the user enters an even integer. We can leverage the customization of exit statuses to see what has happened.
```c
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a = get_int("Enter a number:");
    if (a % 2 != 0)
    {
        printf("Wrong number\n");
        return 1;
    }
    printf("%i\n", a);
    return 0;
}
```
What we did here is use exit statuses for us to see what went wrong in our program. If the user inputs an odd number, we return a <span style="color:red">non-zero</span> number (in this case it is <span style="color:red"><b>1</b></span>) to depict that specific error (an odd number was entered). If the user enters an even number and the code runs, we return <span style="color:green"><b>0</b></span> (signifying that the code works perfectly). 
### Importance?
It allows us to the exit out of code that does not work properly, but compiles perfectly. Basically code that is *syntactically* correct, but *logically* wrong (does not accomplish the task it is set out to do).

***We never actually see the return value we create, it is just there to break out of the program in case something goes wrong, and we know that something went wrong if the return value we set in the code for the program was non-zero***

# Struct
Similar to a **class** where we can create our own data types, *however* we can only have properties in <span style="color:red"><b>structs</b></span> (meaning we *cannot* store **functions**). <span style="color:red"><b>Structs</b></span> must be declared prior to usage or in a header file that we `#include`.
## Formatting
```c
typedef struct
{
    // code here
}
name;
```
### Example
```c
typedef struct
{
    string firstName;
    string lastName;
    int age;
}
person;
```
# Finding Memory Leaks in C Program
## Process
1. Boot up Linux (Debian) VM
2. Share the CS50 directory
3. Run `wget <localhost URL>` in order to get directory into terminal (guest computer)
4. Run C program using `valgrind ./<name>`

<b>Note: just download templates of psets on <span style='color:cyan'>VSCode</span>, then open the <span style='color:lightgreen'>C</span> files on <span style='color:orange'>Linux</span>, write code in <span style='color:red'>nano</span> and run in the <span style='color:orange'>Linux</span> itself.</b>

# Playing around with Memory in C
**Addresses are represented in hexadecimal notation**
<span style='color:red'><b>Pointer</b></span> : a variable that stores the address of some value (the specific byte in which that value is stored)
```c
int n = 50;
int *p = &n;
```
`&` gives the *address* the variable
`*` indicates that you want to the store not the actual variable and its data type, but rather its address **and** it can be used to <span style='color:red'>de-reference</span> a pointer and figure out the value the pointer is pointing to
```c
long a = 289374;
long *b = &a;
```

```c
// how to store a pointer
<data type of value> *<pointer name> = &<variable whose address we are storing>
```

```c
int num = 7;
int *pointer = &num;
printf("%p\n", pointer);    //prints pointers
printf("%p\n", &num);       //prints pointers
printf("%i\n", *pointer);   //prints value stored in location dicatated by pointer
```
Pointers take up <span style='color:crimson'><b>8</b></span> bytes of <span style='color:deepskyblue'>memory</span> (RAM)
## How Strings work in Memory
Each bit contains a character with a <span style='color:red'><b>/0</b></span> at the end to mark the end of a string.
**Remember, a string is basically an array of characters**
The `string` data type is basically a pointer that points to the first character/bit of the string.
CS50's `string` has been an alias for `char *`
## Relationship between Arrays and Memory
If we have the following code:
```c
int a[] = {4, 5, 6, 7};
```
then the pointer of `a` will point to the first `int` in the array.
So, the following code:
```c
printf("%i\n", *a);
```
would output `4`.
This is because when we create a pointer to an array, the pointer gives the address to the first bit/element in the array (the compiler knows when to stop at the end automatically).
### Traversing Arrays through Indexing and through Memory
Before hand, if we wanted to get an element in array `a` would have to say `a[i]` where `i` is some `int` value that denotes the index of an element in the array. 
So if were to assign a variable an element in array `a`, it would look something like this:
```c
int num1 = a[0];
int num2 = a[1];
```
Now, because we know that a pointer to array points to the first element, and arrays would stored consecutively in memory, then the original pointer would point to the first element, and that pointer plus one would point to the next character...
So we can also do the same thing with the following code:
```c
int num1 = *a;
int num2 = *(a+1);
```
This is what is known as **pointer arithmetic**. 
# Allocating Memory
Sometimes, we in order to make a copy of a variable, or for some other reason, we must allocate memory explicitly. In order to do this, we must use `malloc` and `free`. `malloc` is used to allocate a specific number of bytes in memory to a variable and `free` is used to free up those bytes in memory once we are done using them for the computer to use.
## Example
```c
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *name = "abhinav";
    char *Name = malloc(strlen(name) + 1);
    
    strcopy(Name, name)
    
    Name[0] = toupper(Name[0])
    
    free(Name);
}
```
In the previous example, we basically created `name` and allocated memory to `Name`. We include  ` + 1` in order to account for the `/0` character. We then copied the contents of `name` into `Name` and only capitalized the first letter in `Name`. So as of now, `name = "abhinav"` while `Name = "Abhinav"`. Then, now that we are done with `Name`, we called `free(Name)` so that we can free up that memory. Also, there may be a time where `malloc` will fail due to the fact that the computer simply does not have enough extra memory lying around that you need. In order to catch that error, you have to include the following code right underneath the line where you use `malloc`:
```c
if (t == NULL) // t is the name of variable we attempted to allocate memory to
{
    return 1;
}
```
`Malloc` always returns the address of the memory allocated, so whenever we call `malloc` we have to store it in a pointer.
## Example
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = malloc(3 * sizeof(int));
}
```
Basically, we allocated three `int`s worth of memory to `arr` and created its pointer. Now we can treat `arr` as if it were an array.
# Defining Custom Types
Baically, we have ways of creating our own data types by using the `struct` keyword. However, it can become very annoying to declare variables using the `struct` keyword plus the name of our data type. Therefore, we can using the `typedef` keyword to basically create an *alias* for our `struct`.