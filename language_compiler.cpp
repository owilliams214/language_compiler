

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

void programBreakdown(std::queue<string>& words, std::ifstream& textFile);
void execution(queue<string> lines);
bool errorCheck(std::queue<string>& words, std::queue<string>& words2);

int main()
{
     //Creates 2 queues of strings
     queue<string> words;
     queue<string> words2;

     //Creates an ifstream object to store the file
     ifstream textFile;

     string filePath;
     cout << "Enter the full path of the program (textfile)" << endl;
     cin >> filePath;
     //Imports file from computer
     textFile.open(filePath);
     //textFile.open("C:/Users/ADMIN/Documents/test2.txt");

     //Passes the queue and the textfile to function1
     programBreakdown(words, textFile);
     textFile.close();

     //If no errors: clear screen and run the program
     if (errorCheck(words, words2) == false)
     {
          system("CLS");
          cout << "No errors! Running program:" << endl << endl;
          execution(words2);
     }
     else
          cout << "There are errors in your program." << endl;

     system("pause");
     return 0;
}

/*Function that takes a queue of strings and an ifstream object.
Adds ifstream object lines into one string.
Separates each word and pushes the words into the queue

Precondition:
Program syntax is separated by spaces, except before ';' and inside quotation marks.
File path is correct and there have been no issues opening the file

Post-condition:
Entire program is breaked down into a queue of strings, which are separated by spaces
except strings.
*/
void programBreakdown(std::queue<string>& words, std::ifstream& textFile)
{
     string line;
     string file;

     //As long as there is something in the file.
     while (!textFile.eof())
     {
          //Get a line from the file and put it into "line"
          getline(textFile, line);
          //Add the line to string "file"
          file += line;
          //Add a space between each line
          file.push_back(' ');
     }

     string temp;

     for (int i = 0; i < file.length(); i++)
     {
          //If ';', check if temp is empty. if not, push temp into queue
          //Then push ';' into queue as a separate "word"
          //Clear temp
          if (file[i] == ';')
          {
               if (!temp.empty())
                    words.push(temp);
               words.push(";");
               temp.clear();
          }
          //If '"', then push each character into temp until closing '"'
          else if (file[i] == '"')
          {
               temp.push_back(file[i]);
               i++;
               while (file[i] != '"')
               {
                    temp.push_back(file[i]);
                    i++;
               }
               temp.push_back(file[i]);
               words.push(temp);
               temp.clear();
          }
          //If not space, then push the character into string "temp"
          else if (file[i] != ' ')
               temp.push_back(file[i]);
          //Otherwise if "temp" is not equal to zero
          else if (temp.length() != 0)
          {
               //Push the string into queue "words"
               if (!temp.empty())
                    words.push(temp);
               //empty the temporary string
               temp.clear();
          }
     }
}

/*
Function that checks program syntax for errors

Precondition:
Receives two queues, the first one with strings of entire program, and the other one is empty

Postcondition:
Identified every possible error and entire program has been moved to queue words2.
bool variable error has returned true if any errors in program
*/
bool errorCheck(std::queue<string>& words, std::queue<string>& words2)
{
     bool var1 = false;
     bool var2 = false;
     bool var3 = false;
     bool error = false;

     string errorMsg;

     if (words.front() != "begin")
     {
          cout << "ERROR! Missing 'begin' statement" << endl;
          error = true;
     }
     else
     {
          cout << words.front() << endl;
          words.pop();
     }

     //As long as the queue is not empty
     while (!words.empty())
     {
          //Make a temporary string to hold the word in front
          string temp = words.front();
          string next;

          //if not any of the acceptable syntax at the beginning of a statement
          //display error message
          if (temp != "display" && temp != "input"
               && temp != "A" && temp != "B" && temp != "C" && temp != "end")
          {
               errorMsg += "ERROR! Beginning of a statement must be: 'display', 'input', or a variable name.\n";
               errorMsg += "(Spaces need to be in between variables and operators)";
               error = true;

               next = words.front();
               while (next != ";")
               {
                    cout << next << " ";
                    words2.push(words.front());
                    words.pop();
                    next = words.front();
               }
               cout << next;
               words2.push(words.front());
               words.pop();
          }

          if (temp == "display")
          {
               cout << temp;
               words2.push(words.front());
               words.pop();
               next = words.front();

               if (next != "A" && next != "B" && next != "C"
                    && next[0] != '"')
               {
                    errorMsg += "ERROR! A variable or string must be after 'display'!";
                    error = true;

                    while (next != ";")
                    {
                         cout << " " << next;
                         words2.push(words.front());
                         words.pop();
                         next = words.front();
                    }
                    cout << next;
                    words2.push(words.front());
                    words.pop();
               }
               else if (next[0] == '"')
               {
                    if (next[next.length() - 1] != '"')
                    {
                         cout << " " << next;
                         errorMsg += "ERROR! Unclosed quotation!";
                         error = true;
                         words2.push(words.front());
                         words.pop();
                         next = words.front();

                         if (next != ";")
                         {
                              errorMsg += "ERROR! Missing semicolon!";
                              error = true;
                         }
                         else
                         {
                              cout << next;
                              words2.push(words.front());
                              words.pop();
                         }
                    }
                    else
                    {
                         cout << " " << next;
                         words2.push(words.front());
                         words.pop();
                         next = words.front();

                         if (next != ";")
                         {
                              errorMsg += "ERROR! Missing semicolon!";
                              error = true;
                         }
                         else
                         {
                              cout << next;
                              words2.push(words.front());
                              words.pop();
                         }
                    }
               }
               else if (next == "A" || next == "B" || next == "C")
               {
                    cout << " " << next;
                    if (next == "A")
                    {
                         if (var1 == false)
                         {
                              errorMsg += "ERROR! Variable has no value.";
                              error = true;
                         }
                    }
                    else if (next == "B")
                    {
                         if (var2 == false)
                         {
                              errorMsg += "ERROR! Variable has no value.";
                              error = true;
                         }
                    }
                    else if (next == "C")
                    {
                         if (var3 == false)
                         {
                              errorMsg += "ERROR! Variable has no value.";
                              error = true;
                         }
                    }


                    words2.push(words.front());
                    words.pop();
                    next = words.front();

                    if (next != ";")
                    {
                         errorMsg += "ERROR! Missing semicolon!";
                         error = true;
                    }
                    else
                    {
                         cout << next;
                         words2.push(words.front());
                         words.pop();
                    }
               }

          }
          else if (temp == "input")
          {
               cout << temp;
               words2.push(words.front());
               words.pop();
               next = words.front();
               if (next != "A" && next != "B" && next != "C")
               {
                    errorMsg += "ERROR! Only variables can be used with 'input'";
                    error = true;

                    while (next != ";")
                    {
                         cout << next << " ";
                         words2.push(words.front());
                         words.pop();
                         next = words.front();
                    }
                    cout << next;
                    words2.push(words.front());
                    words.pop();
               }
               else
               {
                    cout << " " << next;
                    if (next == "A")
                         var1 = true;
                    else if (next == "B")
                         var2 = true;
                    else if (next == "C")
                         var3 = true;

                    words2.push(words.front());
                    words.pop();
                    next = words.front();

                    if (next != ";")
                    {
                         errorMsg += "ERROR! Missing semicolon!";
                         error = true;
                    }
                    else
                    {
                         cout << next;
                         words2.push(words.front());
                         words.pop();
                    }
               }
          }
          else if (temp == "A" || temp == "B" || temp == "C")
          {
               cout << temp;
               words2.push(words.front());
               words.pop();
               next = words.front();

               if (next != "=")
               {
                    errorMsg += "ERROR! Statement beginning with a variable needs to be an assignment statement ('=')";
                    error = true;

                    while (next != ";")
                    {
                         cout << next << " ";
                         words2.push(words.front());
                         words.pop();
                         next = words.front();
                    }
                    cout << next;
                    words2.push(words.front());
                    words.pop();
               }
               else
               {
                    cout << " " << next;
                    words2.push(words.front());
                    words.pop();
                    next = words.front();

                    if (next != "A" && next != "B" && next != "C")
                    {
                         errorMsg += "ERROR! A variable can only be assigned with other variables.";
                         error = true;

                         while (next != ";")
                         {
                              cout << " " << next;
                              words2.push(words.front());
                              words.pop();
                              next = words.front();
                         }
                         cout << next;
                         words2.push(words.front());
                         words.pop();
                    }
                    else
                    {
                         cout << " " << next;
                         if (next == "A")
                         {
                              if (var1 == false)
                              {
                                   errorMsg += "ERROR! Variable has no value.";
                                   error = true;
                              }
                         }
                         else if (next == "B")
                         {
                              if (var2 == false)
                              {
                                   errorMsg += "ERROR! Variable has no value.";
                                   error = true;
                              }
                         }
                         else if (next == "C")
                         {
                              if (var3 == false)
                              {
                                   errorMsg += "ERROR! Variable has no value.";
                                   error = true;
                              }
                         }

                         words2.push(words.front());
                         words.pop();
                         next = words.front();

                         if (next != "+" && next != "-" && next != "*" && next != "/" && next != ";")
                         {

                              errorMsg += "ERROR! An expression can only be 'var (+ or - or * or /) var' or just a variable.";
                              error = true;

                              while (next != ";")
                              {
                                   cout << next << " ";
                                   words2.push(words.front());
                                   words.pop();
                                   next = words.front();
                              }
                              cout << next;
                              words2.push(words.front());
                              words.pop();
                         }
                         else if (next == "+" || next == "-" || next == "*" || next == "/")
                         {
                              cout << " " << next;
                              words2.push(words.front());
                              words.pop();
                              next = words.front();

                              if (next != "A" && next != "B" && next != "C")
                              {
                                   errorMsg += "ERROR! A variable can only be assigned with other variables.";
                                   error = true;

                                   while (next != ";")
                                   {
                                        cout << next << " ";
                                        words2.push(words.front());
                                        words.pop();
                                        next = words.front();
                                   }
                                   cout << next;
                                   words2.push(words.front());
                                   words.pop();
                              }
                              else
                              {
                                   if (next == "A")
                                   {
                                        if (var1 == false)
                                        {
                                             errorMsg += "ERROR! Variable has no value.";
                                             error = true;
                                        }
                                        else
                                        {
                                             if (temp == "A")
                                                  var1 = true;
                                             else if (temp == "B")
                                                  var2 = true;
                                             else if (temp == "C")
                                                  var3 = true;
                                        }
                                   }
                                   else if (next == "B")
                                   {
                                        if (var2 == false)
                                        {
                                             errorMsg += "ERROR! Variable has no value.";
                                             error = true;
                                        }
                                        else
                                        {
                                             if (temp == "A")
                                                  var1 = true;
                                             else if (temp == "B")
                                                  var2 = true;
                                             else if (temp == "C")
                                                  var3 = true;
                                        }
                                   }
                                   else if (next == "C")
                                   {
                                        if (var3 == false)
                                        {
                                             errorMsg += "ERROR! Variable has no value.";
                                             error = true;
                                        }
                                        else
                                        {
                                             if (temp == "A")
                                                  var1 = true;
                                             else if (temp == "B")
                                                  var2 = true;
                                             else if (temp == "C")
                                                  var3 = true;
                                        }
                                   }

                                   cout << " " << next;
                                   words2.push(words.front());
                                   words.pop();
                                   next = words.front();

                                   if (next != ";")
                                   {
                                        errorMsg += "ERROR! Missing semicolon!";
                                        error = true;
                                   }
                                   else
                                   {
                                        cout << next;
                                        words2.push(words.front());
                                        words.pop();
                                   }
                              }
                         }
                         else
                         {
                              if (temp == "A")
                                   var1 = true;
                              else if (temp == "B")
                                   var2 = true;
                              else if (temp == "C")
                                   var3 = true;

                              cout << next;
                              words2.push(words.front());
                              words.pop();
                         }
                    }
               }
          }

          if (temp == "end")
          {
               cout << temp << endl;
               words2.push(words.front());
               words.pop();
               break;
          }

          cout << endl;

          if (!errorMsg.empty())
          {
               cout << errorMsg << endl;
               errorMsg.clear();
          }
     }
     if (words2.back() != "end")
          cout << "ERROR! Missing 'end' statement!" << endl;

     return error;
}

/*
Function receives a queue of strings that contains a program and runs it.

Precondition:
Queue contains the program that is without any errors and that follows the syntax.

Postcondition:
Program executed correctly.
*/
void execution(queue<string> lines)
{
     string command;
     double variablea, variableb, variablec;
     variablea = variableb = variablec = 0;

     do
     {
          command = lines.front();
          lines.pop();
          string temp;
          if (command == "display")
          {
               string value;

               temp = lines.front();
               lines.pop();
               if (temp[0] == '"')
               {

                    for (int i = 1; i < temp.length() - 1; i++)
                    {
                         value.push_back(temp[i]);
                    }
                    cout << value << endl;
               }

               else if (temp == "A")
                    cout << variablea << endl;
               else if (temp == "B")
                    cout << variableb << endl;
               else if (temp == "C")
                    cout << variablec << endl;
          }

          else if (command == "input")
          {
               temp = lines.front();
               lines.pop();

               if (temp == "A")
                    cin >> variablea;
               else if (temp == "B")
                    cin >> variableb;
               else if (temp == "C")
                    cin >> variablec;
          }

          else if (command == "A")
          {
               lines.pop();
               int variable = 0;
               temp = lines.front();
               lines.pop();

               if (temp == "A")
                    variablea = variablea;
               else if (temp == "B")
                    variablea = variableb;
               else if (temp == "C")
                    variablea = variablec;

               temp = lines.front();
               lines.pop();

               while (temp != ";")
               {
                    if (temp == "+")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                              variablea += variablea;
                         else if (temp == "B")
                              variablea += variableb;
                         else if (temp == "C")
                              variablea += variablec;
                    }

                    else if (temp == "-")
                    {
                         temp = lines.front();
                         lines.pop();

                         if (temp == "A")
                              variablea -= variablea;
                         else if (temp == "B")
                              variablea -= variableb;
                         else if (temp == "C")
                              variablea -= variablec;
                    }
                    else if (temp == "*")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variablea *= variablea;
                         }

                         else if (temp == "B")
                         {
                              variablea *= variableb;
                         }
                         else if (temp == "C")
                         {
                              variablea *= variablec;
                         }
                    }

                    else if (temp == "/")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variablea /= variablea;
                         }

                         else if (temp == "B")
                         {
                              variablea /= variableb;
                         }
                         else if (temp == "C")
                         {
                              variablea /= variablec;
                         }
                    }
                    temp = lines.front();
                    lines.pop();
               }

          }


          else if (command == "B")
          {
               lines.pop();
               int variable = 0;
               temp = lines.front();
               lines.pop();


               if (temp == "A")
               {
                    variableb = variablea;
               }
               else if (temp == "B")
                    variableb = variableb;

               else if (temp == "C")
               {
                    variableb = variablec;
               }
               temp = lines.front();
               lines.pop();
               while (temp != ";")
               {
                    if (temp == "+")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variableb += variablea;
                         }

                         else if (temp == "B")
                         {
                              variableb += variableb;
                         }
                         else if (temp == "C")
                         {
                              variableb += variablec;
                         }
                    }

                    else if (temp == "-")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variableb -= variablea;
                         }
                         else if (temp == "B")
                         {
                              variableb -= variableb;
                         }
                         else if (temp == "C")
                         {
                              variableb -= variablec;
                         }
                    }
                    else if (temp == "*")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variableb *= variablea;
                         }

                         else if (temp == "B")
                         {
                              variableb *= variableb;
                         }
                         else if (temp == "C")
                         {
                              variableb *= variablec;
                         }
                    }

                    else if (temp == "/")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variableb /= variablea;
                         }

                         else if (temp == "B")
                         {
                              variableb /= variableb;
                         }
                         else if (temp == "C")
                         {
                              variableb /= variablec;
                         }
                    }
                    temp = lines.front();
                    lines.pop();
               }
          }

          else if (command == "C")
          {
               lines.pop();
               int variable = 0;
               temp = lines.front();
               lines.pop();

               if (temp == "A")
                    variablec = variablea;
               else if (temp == "B")
                    variablec = variableb;
               else if (temp == "C")
                    variablec = variablec;

               temp = lines.front();
               lines.pop();
               while (temp != ";")
               {
                    if (temp == "+")
                    {
                         temp = lines.front();
                         lines.pop();

                         if (temp == "A")
                         {
                              variablec += variablea;
                         }
                         else if (temp == "B")
                         {
                              variablec += variableb;
                         }
                         else if (temp == "C")
                         {
                              variablec += variablec;
                         }
                    }
                    else if (temp == "-")
                    {
                         temp = lines.front();
                         lines.pop();

                         if (temp == "A")
                         {
                              variablec -= variablea;
                         }
                         else if (temp == "B")
                         {
                              variablec -= variableb;
                         }
                         else if (temp == "C")
                         {
                              variablec -= variablec;
                         }
                    }
                    else if (temp == "*")
                    {
                         temp = lines.front();
                         lines.pop();

                         if (temp == "A")
                         {
                              variablec *= variablea;
                         }
                         else if (temp == "B")
                         {
                              variablec *= variableb;
                         }
                         else if (temp == "C")
                         {
                              variablec *= variablec;
                         }

                    }

                    else if (temp == "/")
                    {
                         temp = lines.front();
                         lines.pop();
                         if (temp == "A")
                         {
                              variablec /= variablea;
                         }

                         else if (temp == "B")
                         {
                              variablec /= variableb;
                         }
                         else if (temp == "C")
                         {
                              variablec /= variablec;
                         }
                    }
                    temp = lines.front();
                    lines.pop();
               }
          }
     } while (command != "end");
}


