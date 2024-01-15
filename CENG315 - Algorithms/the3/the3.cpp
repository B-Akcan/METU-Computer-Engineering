#include <string>
// do not add extra libraries, but you can define helper functions below.

/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/
int calculateHAS(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int &call_count, bool &stackOverflow)
{
    call_count++;
    if (call_count >= 1000000)
    {
        stackOverflow = true;
        return INT_MIN;
    }

    if (sequence_A.empty() || sequence_B.empty())
    {
        possible_alignment = std::string(sequence_A.length(), '.') + std::string(sequence_B.length(), '_');
        return -(gap * std::max(sequence_A.length(), sequence_B.length()));
    }

    int r1=0, r2=0, r3=0;
    std::string s1="", s2="", s3="";
    
    if (sequence_A.back() == sequence_B.back())
    {
        r1 = calculateHAS(sequence_A.substr(0, sequence_A.length()-1), sequence_B.substr(0, sequence_B.length()-1), gap, mismatch, match, s1, call_count, stackOverflow) + match;
        s1 += sequence_A.back();
    }
    else
    {
        r1 = calculateHAS(sequence_A.substr(0, sequence_A.length()-1), sequence_B.substr(0, sequence_B.length()-1), gap, mismatch, match, s1, call_count, stackOverflow) - mismatch;
        s1 += "!";
    }
    
    r2 = calculateHAS(sequence_A.substr(0, sequence_A.length()-1), sequence_B, gap, mismatch, match, s2, call_count, stackOverflow) - gap;
    s2 += ".";
    r3 = calculateHAS(sequence_A, sequence_B.substr(0, sequence_B.length()-1), gap, mismatch, match, s3, call_count, stackOverflow) - gap;
    s3 += "_";
    
    if (r1 >= r2 && r1 >= r3)
    {
        possible_alignment = s1;
        return r1;
    }
    else if (r2 >= r1 && r2 >= r3)
    {
        possible_alignment = s2;
        return r2;
    }
    else
    {
        possible_alignment = s3;
        return r3;
    }
}

int max(int a, int b, int c)
{
    if (a >= b && a >= c) return a;
    else if (b >= a && b >= c) return b;
    else return c;
}

int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    int highest_alignment_score;
    bool stackOverflow = false;
    
    highest_alignment_score = calculateHAS(sequence_A, sequence_B, gap, mismatch, match, possible_alignment, call_count, stackOverflow);
    
    if (stackOverflow)
    {
        possible_alignment = "STACK LIMIT REACHED";
        highest_alignment_score = INT_MIN;
    }
    
    return highest_alignment_score;
}

/* 
PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int A[10000][10000];
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    for (int i = 0; i < sequence_A.length() + 1; i++)
    {
        for (int j = 0; j < sequence_B.length() + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                A[i][j] = -std::max(i, j) * gap;
            }

            else
            {
                int res;
                if (sequence_A[i - 1] == sequence_B[j - 1])
                {
                    res = match;
                }
                else
                {
                    res = -mismatch;
                }

                A[i][j] = max(A[i - 1][j - 1] + res, A[i - 1][j] - gap, A[i][j - 1] - gap);
            }
        }
    }
    
    possible_alignment = "";
    int i = sequence_A.length(), j = sequence_B.length();
    while (i > 0 && j > 0)
    {
        if (A[i][j] == A[i - 1][j - 1] + ((sequence_A[i - 1] == sequence_B[j - 1]) ? match : -mismatch))
        {
            possible_alignment += (sequence_A[i - 1] == sequence_B[j - 1]) ? sequence_A[i - 1] : '!';
            i--;
            j--;
        }
        else if (A[i][j] == A[i - 1][j] - gap)
        {
            possible_alignment += '.';
            i--;
        }
        else
        {
            possible_alignment += '_';
            j--;
        }
    }
    
    while (i > 0)
    {
        possible_alignment += '.';
        i--;
    }
    while (j > 0)
    {
        possible_alignment += '_';
        j--;
    }
    
    reverse(possible_alignment.begin(), possible_alignment.end());
    return A[sequence_A.length()][sequence_B.length()];    
}
