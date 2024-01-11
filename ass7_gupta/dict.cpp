// Do NOT add any other includes
#include "dict.h"
// #include <bits/stdc++.h>
//. , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
const int M=1000000;

Dict::Dict()
{
    // Implement your function here
    vec.resize(1000001);
}
vector<string> convert_sentence(string s)
{
    int n = s.length();
    vector<string> words;
    string word = "";
    for (int i = 0; i < n; i++)
    {

        if ((s[i] == ' ' || s[i]=='.' || s[i]==',' || s[i]=='-' || s[i]==':' || s[i]=='!' || s[i]=='"' || s[i]=='\'' || s[i]=='(' || s[i]==')' || s[i]=='?' || s[i]=='—' || s[i]=='[' || s[i]==']' /*|| s[i]=='˙'*/ || s[i]==';' || s[i]=='@')  )
        {
           if(word.size()!=0) words.push_back(word);
            word = "";
        }
        else
        {
            if(s[i]>='A'&&s[i]<='Z') s[i] = s[i]-'A'+'a';
            word.push_back(s[i]);
            
        }
         if (i == n - 1)
        {
           if(word.size()!=0) words.push_back(word);
           
        }

    }
    return words;
}
// int Dict::hashvalue(string word)
// {
//     int ans = 0;
//     int n=word.size();
   
//     for(int i=0;i<n;i++)
//     {
//         if(word[i]>='0' && word[i]<='9')
//         {
//             ans=(ans + ((word[i]-'0') * power_of_3[i])) % M;
//         }
//         else
//         {
//             ans=(ans + (abs(word[i]-'a') * power_of_3[i]))%M;
//         }
//     }
//     return ans;
// }
int Dict:: hashvalue(string word)
{
    long long int m = 1000001;
    long long int ans = 0;
    long long int p = 31;
    long long int fac = 1;
    for (int i = 0; i < word.size(); i++)
    {
        ans = (ans + (word[i] * fac)) % m;
        fac = (fac * p) % m;
    }
    return ans;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here

    vector<string> words =convert_sentence(sentence);
    for (auto &x : words)
    {

        int hash = hashvalue(x);
        // cout<<hash<<endl;
        // if (vec.size() <= hash)
        // {

        //     vec.resize(hash + 1);
        // }
        bool found = false;
        for (int j = 0; j < vec[hash].size(); j++)
        {
            if (vec[hash][j].first == x)
            {
                found = true;
                vec[hash][j].second++;
                // if(x=="and")
                // {
                //     cout<<vec[hash][j].second<<" "<<sentence_no<<endl;
                // }
                break;
            }
        }
        if (!found)
        {
            vec[hash].push_back(make_pair(x, 1));
        }
    }

    return;
}

long long Dict::get_word_count(string word)
{
    // Implement your function here
    int hash = hashvalue(word);
    for (auto &x : vec[hash])
    {
        if (x.first == word)
        {
            return x.second;
        }
    }
    return 0;
}

void Dict::dump_dictionary(string filename)
{
    // Implement your function here
    ofstream ofile;
    ofile.open(filename);
  
    for (auto &x : vec)
    {
       
        for (auto &y : x)
        {
            ofile << y.first << ", " << y.second << endl;
        }
    }
    ofile.close();

    return;
}
Dict::~Dict()
{
    // Implement your function here
}