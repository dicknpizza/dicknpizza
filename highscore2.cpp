#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

   



int main(int argc, char *argv[])
{

             
ifstream::pos_type size;
char * memblock;

                string names[10];
                     string scores[10];
       ifstream file ("data\\cars\\carup.raw", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
                     
    size = file.tellg();

    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    //cout << size << endl;
    int n = 0;
    for(int i = 0; i < size; i++)
    {
            
            if(memblock[i] != '%')
            {
            
            if(memblock[i] == '0' || memblock[i] == '1' || memblock[i] == '2' || memblock[i] == '3' || memblock[i] == '4' || memblock[i] == '5' || memblock[i] == '6' || memblock[i] == '7' || memblock[i] == '8' || memblock[i] == '9')
            {
            scores[n] += memblock[i];
            
                 
            } else names[n] += memblock[i];
            cout << memblock[i];
            }
            
            
            
            if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99) { n++; cout << endl; }
            
            
            
            }
             
            }
            
        
    

    delete[] memblock;  

   
   
   
   
   
    system("PAUSE");
    return EXIT_SUCCESS;
}
