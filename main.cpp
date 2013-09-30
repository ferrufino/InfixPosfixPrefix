//
//  main.cpp
//  Tarea4
//
//  Created by Gustavo Ferrufino on 9/27/13.
//  Copyright (c) 2013 Gustavo Ferrufino. All rights reserved.
//
//No correr este codigo desde dropbox por el pwd para el archivo

#include <iostream>
using namespace std;
//#include <queue> //stl library
#include <stack> // stl library
#include <fstream>
//#include "Stack.h"
//#include "Node.h"
#include "Queue.h"

bool debug = true;



queue<char> finalQueue;
stack<char> PosfixStack;
stack<char> firstPrefixStack;
stack<char> secondPrefixStack;

char operators[10]={'*','/','%','+','-','<','>','=','&','|'};
int relation[10]={4,4,4,3,3,2,2,2,1,1};

void emptyPrefixStack(){
    
    
    while (!firstPrefixStack.empty()) {
        
        if (firstPrefixStack.top() == '(' || firstPrefixStack.top() == ')' ) {
            
            firstPrefixStack.pop();
            
        }
        else{
            
            char temp = firstPrefixStack.top();
            secondPrefixStack.push(temp);
            firstPrefixStack.pop();
            
        }
    }
    
    
}

void DEBUGSecondStackOUTPUT (){
    
    
    cout<<"Prefix: ";
    while (!secondPrefixStack.empty()) {
        
        cout<<secondPrefixStack.top();
        secondPrefixStack.pop();
        
    }
    cout<<endl;
    
    //cout<<endl<<"DEBUG: Shows finalQueue Output and Emptied finalQueue.";
    
}




void DEBUGQueueOUTPUT (){

    
    cout<<"Postfix: ";
    while (!finalQueue.empty()) {
       
        cout<<finalQueue.front();
        finalQueue.pop();
        
    }
    cout<<endl;

    //cout<<endl<<"DEBUG: Shows finalQueue Output and Emptied finalQueue.";
    
}

int relateOperatorPriority ( char temp  ){
    
    int num;
    if ( temp == '(') {
        return 0;
    }
    for (int i=0; i<10; i++) {
        
        if (temp == operators[i]) {
            
            num = relation[i];
            
        }
        
    }
    
    return num;
}

bool checkNumber( char num){
    
    return (num == '0'|| num == '1'|| num == '2'|| num == '3'|| num == '4'|| num == '5'
            || num == '6'|| num == '7'|| num == '8'|| num == '9');
    
}


void emptyStack(){ //for posfix use only
    

    while (!PosfixStack.empty()) {
        
        if (PosfixStack.top() == '(' || PosfixStack.top() == ')' ) {
           
            PosfixStack.pop();
            
        }
        else{
            
            char temp = PosfixStack.top();
            finalQueue.push(temp);
            PosfixStack.pop();

        }
    }


}
int main()
{
    string fileName;
    ifstream file;
    string aux;
    cout<<"Cual es el nombre del archivo?";
    cin>>fileName;
    // /Users/Ferrufino/Desktop/tutti.txt
    
    file.open(fileName.c_str());
    while (file>>aux) {
        
        //cout<<endl<<"DEBUG:  Entered file/new line."<<endl;
        
        int cont1=0;
       
        
        while (cont1<aux.length()) { ///infijo to posfijo
            
            switch (aux[cont1]) {
            
                case '(':{
                
                    PosfixStack.push(aux[cont1]);
                    //cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                    
                    break;
                }
                
                case ')':{
                
                    
                   
                  
                    if (!finalQueue.empty()) {
                        
                        emptyStack();
                                            }
                    else{
                       
                        while (!PosfixStack.empty()) {
                            
                            emptyStack();
                            
                        }
                       
                        
                    }
                        
                    
                    
                    
                    
                }
                    
                default:{
                    //Number?
                    if (checkNumber(aux[cont1])) {
                        finalQueue.push(aux[cont1]);
                        //cout<<"DEBUG: There is a new value in QUEUE and it is:"<<finalQueue.front()<<endl;
                    }
                    
                    else{//Empty?
                        if (PosfixStack.empty() && aux[cont1] != ')') {
                            PosfixStack.push(aux[cont1]);
                           // cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                        }
                        else{//Operator?
                            while ((PosfixStack.size()> 0) && ( relateOperatorPriority(PosfixStack.top()) >= relateOperatorPriority(aux[cont1]) ) ) {
                                
                                finalQueue.push(PosfixStack.top());
                                
                                PosfixStack.pop();
                            }
                          
                            PosfixStack.push(aux[cont1]);
                            
                            //cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                            
                        }
                    }
                           
                    break;
                           
                }
            
            }// End switch
        
            cont1++;
        
        }// End loop while with variable "cont"
        if (!PosfixStack.empty()) {
            emptyStack();
        }
        
        cout<<"Infix: "<<aux<<endl;
        DEBUGQueueOUTPUT(); //postfix output caller
        
        
    
        //Conversion from Infix to Prefix
        
        int cont2=(aux.length())-1;
        
        
        while (cont2>=0) { ///infix to prefix
            
            switch (aux[cont2]) {
                    
                case ')':{
                    
                    firstPrefixStack.push(aux[cont2]);
                    //cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                    
                    break;
                }
                    
                case '(':{
                    
                    
                    
                    
                    if (!secondPrefixStack.empty()) {
                        
                        emptyPrefixStack();
                    }
                    else{
                        
                        if (!firstPrefixStack.empty()) {
                            
                            emptyPrefixStack();
                            
                        }
                        
                        
                    }
                    
                    
                    
                    
                    
                }
                    
                default:{
                    //Number?
                    if (checkNumber(aux[cont2])) {
                        secondPrefixStack.push(aux[cont2]);
                        //cout<<"DEBUG: There is a new value in QUEUE and it is:"<<finalQueue.front()<<endl;
                    }
                    
                    else{//Empty?
                        if (firstPrefixStack.empty() && aux[cont2] != ')') {
                            firstPrefixStack.push(aux[cont2]);
                            // cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                        }
                        else{//Operator?
                            while ((firstPrefixStack.size()> 0) && ( relateOperatorPriority(firstPrefixStack.top()) >= relateOperatorPriority(aux[cont2]) ) ) {
                                
                                secondPrefixStack.push(firstPrefixStack.top());
                                
                                firstPrefixStack.pop();
                            }
                            
                            firstPrefixStack.push(aux[cont2]);
                            
                            //cout<<"DEBUG: there is a new value STACK and it is:"<<firstStack.top()<<endl;
                            
                        }
                    }
                    
                    break;
                    
                }
                    
            }// End switch
            
            cont2--;
            
            
        }// End loop while with variable "cont = aux.length()"
        if (!firstPrefixStack.empty()) {
            emptyPrefixStack();
        }
        DEBUGSecondStackOUTPUT(); //Prefix output caller
        
        //Evaluate from prefix

        
    }//End of loop while file for line read
    
    
    return 0;
}

