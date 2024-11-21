# LexicalAnalyzer For C 
The task:
Write a lexical analyzer for a programming language of your choice. Implement the analyzer as a function that returns the following:

The type of the current token,
The length of the corresponding string in the input file,
The line in the input file where the current token is located,
An error message when a lexical error is encountered.

Example
1.
2.
3. int main() {
4.     int num, a12b_34, 13aaa;
5.     string x= "a string \
6.     spanning \"multiple lines"
7.     printf("Enter an integer: ");
8.     scanf("%d", &num);
9.
10.     // true if num is perfectly divisible by 2
11.     if (num % 2 == 0)
12.         printf("%d is even.", num);
13.     else
14.         printf("%d is odd.", num);
15.
16.     return 0; /* comment ** across /multiple
17.     lines */ num++;
18. }
Detected Tokens:
"int", line 3, keyword, length 3
"main", line 3, keyword, length 4
"(", line 3, separator, length 1
...
"comment ** across /multiple\nlines", lines 16-17, comment
"num", line 17, identifier, length 3
"++", line 17, operator, length 2
"}", line 18, separator, length 1
This lexical analyzer ensures efficient tokenization of an input program while managing errors and handling multiline constructs, such as comments and strings.


![Screenshot 2024-11-21 105114](https://github.com/user-attachments/assets/bfc33476-af68-460c-98ed-d7b51312c0eb)
![Screenshot 2024-11-21 105130](https://github.com/user-attachments/assets/6761d702-4669-4d87-bd94-2b6f0ce1977a)


