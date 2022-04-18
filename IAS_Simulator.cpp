#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll IR = 0, IBR = 0, MBR = 0, MAR = 0, AC = 0, MQ = 0;

int execute(ll memory[], ll PC)
{
    while (PC < 1000)
    {
        bool left = true;
        MAR = PC;
        MBR = *(memory + MAR);
        IBR = (MBR) % ((ll)1 << 20);
        IR = MBR >> 32;
        MAR = (MBR >> 20) % ((ll)1 << 12);
        NextInfo:;

        switch (IR)
        {
            case 0: // (0x00)
                cout << "HALT" << endl;
                return 0;

            case 1: // (0x01)
                cout << "LOAD M(" << MAR << ")" << endl;
                AC = *(memory + MAR);
                break;

            case 2: // (0x02)
                cout << "LOAD -M(" << MAR << ")" << endl;
                AC = 0 - (*(memory + MAR));
                break;

            case 3: // (0x03)
                cout << "LOAD |M(" << MAR << ")|" << endl;
                AC = (*(memory + MAR));
                if (AC > 0)
                    AC = AC;
                else
                    AC = -AC;
                break;

            case 4: // (0x04)
                cout << "LOAD -|M(" << MAR << ")|" << endl;
                AC = (*(memory + MAR));
                if (AC > 0)
                    AC = -AC;
                else
                    AC = AC;
                break;

            case 5: // (0x05)
                cout << "LOAD MQ" << endl;
                AC = MQ;
                break;

            case 6: // (0x06)
                cout << "LOAD MQ, M(" << MAR << ")" << endl;
                MQ = (*(memory + MAR));
                break;

            case 7: // (0x07)
                cout << "ADD M(" << MAR << ")" << endl;
                AC = AC + (*(MAR + memory));
                break;

            case 8: // (0x08)
                cout << "ADD |M(" << MAR << ")|" << endl;
                if (*(memory + MAR) > 0)
                    AC = AC + (*(memory + MAR));
                else
                    AC = AC - (*(memory + MAR));
                break;

            case 9: // (0x09)
                cout << "SUB M(" << MAR << ")" << endl;
                AC = AC - (*(MAR + memory));
                break;

            case 10: // (0x0A)
                cout << "SUB |M(" << MAR << ")|" << endl;
                if (*(memory + MAR) > 0)
                    AC = AC - (*(memory + MAR));
                else
                    AC = AC + (*(memory + MAR));
                break;

            case 11: // (0x0B)
            {
                cout << "DIV M(" << MAR << ")" << endl;
                ll quotient, remainder;
                quotient = AC / (*(MAR + memory));
                remainder = AC % (*(MAR + memory));
                AC = remainder;
                MQ = quotient;
                break;
            }

            case 12: // (0x0C)
                cout << "JUMP M(" << MAR << ", 0:19)" << endl;
                PC = MAR;
                MBR = *(memory + MAR);
                IR = (MBR >> 32);
                MAR = (MBR >> 20) % ((ll)1 << 12);
                IBR = MBR % ((ll)1 << 20);
                left = false;
                goto NextInfo;
                break;

            case 13: // (0x0D)
                cout << "JUMP M(" << MAR << ", 20:39)" << endl;
                PC = MAR;
                MBR = *(memory + MAR);
                IR = (MBR >> 12) % ((ll)1 << 8);
                MAR = MBR % ((ll)1 << 12);
                left = false;
                goto NextInfo;
                break;

            case 14: // (0x0E)
                cout << "JUMP + M(" << MAR << ", 0:19)" << endl;
                if (AC >= 0)
                {
                    PC = MAR;
                    MBR = *(memory + MAR);
                    IR = (MBR >> 32);
                    MAR = (MBR >> 20) % ((ll)1 << 12);
                    IBR = MBR % ((ll)1 << 20);
                    left = false;
                    goto NextInfo;
                }
                break;

            case 15: // (0x0F)
                cout << "JUMP + M(" << MAR << ", 20:39)" << endl;
                if (AC >= 0)
                {
                    PC = MAR;
                    MBR = *(memory + MAR);
                    IR = (MBR >> 12) % ((ll)1 << 8);
                    MAR = MBR % ((ll)1 << 12);
                    left = false;
                    goto NextInfo;
                }
                break;

            case 16: // (0x10)
            {
                cout << "STOR M(" << MAR << ")" << endl;
                (*(MAR + memory)) = AC;
                break;
            }

            case 17: // (0x11)
            {
                cout << "STOR M(" << MAR << ", 8:19)" << endl;
                ll t1 = (*(memory + MAR)) % (1 << 20), t2 = (*(MAR + memory)) >> 32;
                *(MAR + memory) = t1 << 32 + AC << 20 + t2;
                break;
            }

            case 18: // (0x12)
            {
                cout << "STOR M(" << MAR << ", 28:39)" << endl;
                ll te = (*(memory + MAR)) >> 12;
                *(MAR + memory) = te << 12 + AC;
                break;
            }

            case 19: // (0x13)
            {
                cout << "LSH" << endl;
                AC = AC << 1;
                break;
            }

            case 20: // (0x14)
            {
                cout << "RSH" << endl;
                AC = AC >> 1;
                break;
            }

            case 21: // (0x15)
            {
                cout<<"MUL M("<<MAR<<")"<<endl;
                ll MQ1 = MQ % (1<<20), MQ2 = MQ>>20, M1 = (*(memory + MAR)) % (1<<20), M2 = (*(memory + MAR))>>20;
                ll A0 = MQ2 * M2, A1 = MQ2 * M1, A2 = MQ1 * M2, A3 = MQ1 * M1;
                ll car = 0 , t= 0;
                
                MQ = A0;
                t = MQ;
                MQ = MQ + A1%(1<<20);
                
                if(t>MQ)
                    car++;
                
                t = MQ;
                MQ = MQ + A2%(1<<20);

                if(t>MQ)
                    car++;

                AC = car;
                AC = AC + A3;
                AC = AC + (A2>>20);
                AC = AC + (A1>>20);

                break;
            }

            case 22: // (0x16)
            {    
                cout << "STOR MQ, M(" << MAR << ")" << endl;
                (*(memory + MAR)) = MQ;
                break;
            }

            default :
            {
                continue;
            }
        } 
        
        if (left == true)
        {
            left = false;
            MAR = IBR % (1<<12);
            IR = IBR >> 12;
            goto NextInfo;
        }
        PC++;

        cout<<"AC : "<<AC<<endl;
        cout<<"PC : "<<PC<<endl;
        cout<<"MAR : "<<MAR<<endl;
        cout<<"MBR : "<<MBR<<endl;
        cout<<"IR : "<<IR<<endl;
        cout<<"IBR : "<<IBR<<endl;
        cout<<"MQ : "<<MQ<<endl;
    }
    return 0;
}

int main()
{
    bool check = true;
    ll loc = 0;
    ll memory[1000];
    for (int i = 0; i < 1000; i++)
    {
        memory[i] = 0;
    }

    int choice;

    cout << "\n 1 --> Simple Addition\n 2 --> Simple Subtraction (2nd Number - 1st Number)\n 3 --> Simple Multiplication\n 4 --> Simple Division (Displays Quotient) (2nd Number / 1st Number)\n 5 --> Example Program in Question pdf\n 6 --> Factorial of a number\n";
    cout << "\nEnter the choice of your operation between 1 to 6 : ";

    cin >> choice;

    switch (choice)
    {
        case 1: // Simple Adddition
            cout << "\nEnter first number : ";
            cin >> memory[0];
            cout << "Enter second number : ";
            cin >> memory[1];        
            memory[3] = 0x0100107000;
            memory[4] = 0x1000200000;
            break;


        case 2: // Simple Subtraction
            cout << "\nEnter first number : ";
            cin >> memory[0];
            cout << "Enter second number : ";
            cin >> memory[1];
            memory[3] = 0x0100109000;
            memory[4] = 0x1000200000;
            break;

        case 3: // Simple Multiplication
            cout << "\nEnter first number : ";
            cin >> memory[0];
            cout << "Enter second number : ";
            cin >> memory[1];
            memory[3] = 0x0600115000;
            memory[4] = 0x1000200000;
            break;

        case 4: // Simple Division
            cout << "\nEnter first number : ";
            cin >> memory[0];
            cout << "Enter second number : ";
            cin >> memory[1];
            memory[3] = 0x010010B000;
            memory[4] = 0x1600200000;
            break;

        case 5: // Example Program in Question pdf
            cout << "\nEnter first number : ";
            cin >> memory[0];
            cout << "Enter second number : ";
            cin >> memory[1];
            memory[3] = 0x0100009001; 
            memory[4] = 0x0F00601000; 
            memory[5] = 0x0700110002; 
            memory[6] = 0x0000001001; 
            memory[7] = 0x090000F008; 
            memory[8] = 0x0F00410002; 
            memory[9] = 0x0000000000; 
            break;
        
        case 6: // Factorial Of a number
            memory[0] = 1;
            cout<<"\nEnter a number to calculate factorial : ";
            cin>>memory[1];
            memory[2] = memory[1]; //Temp type
            memory[3] = 0x0600101002;
            memory[4] = 0x0900010002;
            memory[5] = 0x1500210001;
            memory[6] = 0x010020E003;
            memory[7] = 0x0000000000;
            break;

        default:
            cout<<"Invalid Choice "<<endl;
            goto Exit;
            break;
    }

    // 0b00000000; --> HALT
    // 0b00001010; --> LOAD MQ
    // 0b00001001; --> LOAD MQ,M(X)
    // 0b00100001; --> STOR M(X)
    // 0b00000001; --> LOAD M(X)
    // 0b00000010; --> LOAD -M(X)
    // 0b00000011; --> LOAD|M(X)|
    // 0b00000100; --> -LOAD|M(X)|
    // 0b00001101; --> JUMP M(X,0:19)
    // 0b00001110; --> JUMP M(X,10:39)
    // 0b00001111; --> JUMP + M(X,0:19)
    // 0b00010000; --> JUMP + M(X,20:39)
    // 0b00000101; --> ADD M(X)
    // 0b00000111; --> ADD |M(X)|
    // 0b00000110; --> SUB M(X)
    // 0b00001000; --> SUB |M(X)|
    // 0b00001011; --> MUL M(X)
    // 0b00001100; --> DIV M(X)
    // 0b00010100; --> LSH
    // 0b00010101; --> RSH


    while (check)
    {
        cout << "Memory loc : " << loc << endl;
        cout << "Memory Value : " << memory[loc] << endl;
        cout << "a:\t EXIT" << endl;
        cout << "b:\t INCREMENT" << endl;
        cout << "c:\t DECREMENT" << endl;
        cout << "d:\t EXECUTE" << endl;
        cout << "Enter your choice : ";

        char select;
        cin >> select;
        switch (select)
        {

            case 'a': // Exit
                check = false;
                break;

            case 'b': // Increment
                loc++;
                if (loc >= 1000)
                {
                    cout << "Memory Overflowed" << endl;
                    loc -= 1000;
                }
                break;

            case 'c': // Decrement
                loc--;
                if (loc < 0)
                {
                    cout << "Memory Underflowed" << endl;
                    loc += 1000;
                }
                break;

            case 'd': //Execute
                cout << endl;
                execute(memory, loc);
                break;

            default:
                cout<<"Invalid Choice "<<endl;
                goto Exit;
        }
        cout << endl;
    }

    Exit:;
    return 0;
}
