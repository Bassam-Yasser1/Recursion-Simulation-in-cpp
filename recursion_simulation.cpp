// Names and IDs:
// Bassam Yasser - 20230089
// Mohamed Ashraf - 20230321
// Mariam Ayman - 20230390
// Samaa Mehrez - 20230177

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

// Stack Frame Structure
// Holds everything a single "activation record" would contain:
//   - n: the parameter passed to F
//   - a, b, c, d: local variables inside F
//   - pc: program counter (which step to execute next)
//   - return_value: the return value of this call (filled before popping)

struct Frame
{
    int n;
    int a;
    int b;
    int c;
    int d;
    int pc;
    int return_value;
};

// Program Counter (pc) step meanings:
//   0: Check base case; if not base, begin step 1
//   1: About to call F(n-2) -> push new frame for F(n-2)
//   2: F(n-2) returned; store result in a; about to call F(n/2)
//   3: F(n/2) returned; store result in b; compute c; about to call F(c)
//   4: F(c) returned; store result in d; compute and store return value

int F(int n)
{
    stack<Frame> my_stack;

    // Push the initial call frame
    Frame initFrame;
    initFrame.n = n;
    initFrame.a = 0;
    initFrame.b = 0;
    initFrame.c = 0;
    initFrame.d = 0;
    initFrame.pc = 0;
    initFrame.return_value = 0;
    my_stack.push(initFrame);

    // This holds the return value from the most recently completed sub-call
    int lastReturn = 0;

    while(!my_stack.empty())
    {
        // Work on the top frame (get a reference with copy-modify-replace pattern)
        Frame fr = my_stack.top();
        my_stack.pop();

        // Execute based on current program counter
        if(fr.pc == 0)
        {
            // Step 0: Check base case
            if(fr.n <= 1)
            {
                // Base case: return 1 to caller
                fr.return_value = 1;
                lastReturn = fr.return_value;
                // Do NOT push fr back; this frame is done
            }
            else
            {
                // Not base case: prepare to call F(n-2)
                // Suspend this frame at pc=1 (waiting for F(n-2) result)
                fr.pc = 1;
                my_stack.push(fr);

                // Push new frame for F(n-2)
                Frame newFr;
                newFr.n = fr.n - 2;
                newFr.a = 0;
                newFr.b = 0;
                newFr.c = 0;
                newFr.d = 0;
                newFr.pc = 0;
                newFr.return_value = 0;
                my_stack.push(newFr);
            }
        }
        else if(fr.pc == 1)
        {
            // Step 1: F(n-2) has just returned (result is in lastReturn)
            // Complete:  a = n + F(n-2)
            fr.a = fr.n + lastReturn;

            // Now prepare to call F(n/2)
            // Suspend this frame at pc=2
            fr.pc = 2;
            my_stack.push(fr);

            // Push new frame for F(n/2)
            Frame newFr;
            newFr.n = fr.n / 2;
            newFr.a = 0;
            newFr.b = 0;
            newFr.c = 0;
            newFr.d = 0;
            newFr.pc = 0;
            newFr.return_value = 0;
            my_stack.push(newFr);
        }
        else if(fr.pc == 2)
        {
            // Step 2: F(n/2) has just returned (result is in lastReturn)
            // Complete: b = (n-1) * F(n/2)
            fr.b = (fr.n - 1) * lastReturn;

            // Compute c
            fr.c = fr.n - 1 - (fr.a + fr.b) % 3;

            // Now prepare to call F(c)
            // Suspend this frame at pc=3
            fr.pc = 3;
            my_stack.push(fr);

            // Push new frame for F(c)
            Frame newFr;
            newFr.n = fr.c;
            newFr.a = 0;
            newFr.b = 0;
            newFr.c = 0;
            newFr.d = 0;
            newFr.pc = 0;
            newFr.return_value = 0;
            my_stack.push(newFr);
        }
        else if(fr.pc == 3)
        {
            // Step 3: F(c) has just returned (result is in lastReturn)
            // Complete:  d = F(c)
            fr.d = lastReturn;

            // Compute and store the return value: return a + b + d
            fr.return_value = fr.a + fr.b + fr.d;

            // Deliver return value to caller
            lastReturn = fr.return_value;
            // Frame is done; do NOT push back
        }
    }

    return lastReturn;
}

// Recursive reference implementation (used ONLY for testing)
int F_recursive(int n)
{
    if(n <= 1) return 1;
    int a = n + F_recursive(n - 2);
    int b = (n - 1) * F_recursive(n / 2);
    int c = n - 1 - (a + b) % 3;
    int d = F_recursive(c);
    return a + b + d;
}

int main()
{
    // 20 test cases
    printf("=== Test Cases: Iterative vs Recursive ===\n");
    bool allPassed = true;

    for(int i = 1; i <= 25; i++)
    {
        int iterResult = F(i);
        int recResult = F_recursive(i);
        bool passed = (iterResult == recResult);

        if(!passed) allPassed = false;
        printf("F(%2d) = %8d  [ref: %8d]  %s\n",
               i, iterResult, recResult, passed ? "PASS" : "FAIL");
    }

    printf("\nAll test cases passed: %s\n\n", allPassed ? "YES" : "NO");

    // Interactive input
    cout << "Enter n to compute F(n): ";
    fflush(stdout);
    int n;
    scanf("%d", &n);
    printf("F(%d) = %d\n", n, F(n));

    return 0;
}
