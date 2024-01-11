#include <assert.h>
#include <sstream>
#include <cmath>
// #include <bits/stdc++.h>
#include "qna_tool.h"
using namespace std;

const int M = 1000001;
using ll = long long int;
#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

Dict dic;
class para
{
public:
    int bookcode, pg, parag;
    double score;
    para()
    {
        score = 0;
    }
};

vector<para> allparas;
vector<vector<vector<string>>> paras;
vector<vector<pair<string, ll>>> gencnt;

class priorityq
{
public:
    vector<pair<para, long double>> v;
    int size = 0;

    void heapifydown(int idx)
    {
        int minidx=idx;
        int pidx=idx;
        int leftc=2 * idx + 1;
        int rightc=2 * idx + 2;
        while(leftc<v.size()){
            if (v[leftc].second < v[minidx].second)
            {
                minidx = leftc;
            }
            if (rightc < v.size() && v[rightc].second < v[minidx].second)
            {
                minidx = rightc;
            }
            if(minidx==pidx){
                break;
            }
            swap(v[minidx], v[pidx]);
            pidx=minidx;
            leftc=2*pidx+1;
            rightc=2*pidx+2;
        }
    }
    void heapifyup(int idx)
    {
        while (idx > 0)
        {
            int p = (idx - 1) / 2;
            if (v[p].second > v[idx].second)
            {
                swap(v[p], v[idx]);
                idx = p;
            }
            else
            {
                break;
            }
        }
    }

    void insert(para p, long double score)
    {
        v.push_back({p, score});
        size++;
        heapifyup(size-1);
    }

    void deletemin()
    {
        if (size != 0)
        {
            v[0] = v[size - 1];
            v.pop_back();
            size--;
            heapifydown(0);
        }
    }
};

ll hval(string word)
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

ll hval2(string word)
{
    long long int m = 10001;
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

vector<string> change_sentence(string s)
{
    int n = s.length();
    vector<string> words;
    string word = "";
    for (int i = 0; i < n; i++)
    {

        if ((s[i] == ' ' || s[i] == '.' || s[i] == ',' || s[i] == '-' || s[i] == ':' || s[i] == '!' || s[i] == '"' || s[i] == '\'' || s[i] == '(' || s[i] == ')' || s[i] == '?' || s[i] == '—' || s[i] == '[' || s[i] == ']' /*|| s[i]=='˙'*/ || s[i] == ';' || s[i] == '@'))
        {
            if (word.size() != 0)
                words.push_back(word);
            word = "";
        }
        else
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
            word.push_back(s[i]);
        }
        if (i == n - 1)
        {
            if (word.size() != 0)
                words.push_back(word);
        }
    }
    return words;
}

QNA_tool::QNA_tool()
{
    // Implement your function here
    // gencnt.resize(10000001);
    // fstream fin;
    // fin.open("unigram_freq.csv", ios::in);
    // string sentence = "";
    // string word = "";
    // ll num = 0;
    // getline(fin, sentence);
    // while (fin.eof() == 0)
    // {
    //     getline(fin, sentence);
    //     word = "";
    //     num = 0;

    //     int i = 0;
    //     while (sentence[i] != ',')
    //     {
    //         word += sentence[i];
    //         i++;
    //     }
    //     i++;
    //     while (i < sentence.size())
    //     {
    //         num = num * 10 + (sentence[i] - '0');
    //         i++;
    //     }
    //     // cout << word << endl;
    //     int idx = hval(word);
    //     // cout << gencnt.size() << " " << idx << endl;
    //     if (idx > gencnt.size())
    //     {
    //         // cout << "rakshit" << idx << endl;
    //         gencnt.resize(idx * 2);
    //     }
    //     // if(word=="the"){
    //     // cout<<num<<endl;
    //     // break;}
    //     gencnt[idx].push_back({word, (num)});
    //     sentence = "";
    // }
}

QNA_tool::~QNA_tool()
{
    // Implement your function here
}

double QNA_tool:: getscore(vector<string> words, string p)
{
    vector<vector<pair<string, int>>> temphashtable;
    temphashtable.resize(10001);
    vector<string> ps = change_sentence(p);
    for (int j = 0; j < ps.size(); j++)
    {
        int hvalue = hval2(ps[j]);
        if (temphashtable.size() <= hvalue)
        {
            temphashtable.resize(2 * hvalue);
        }
        int matched = 0;
        for (int i = 0; i < temphashtable[hvalue].size(); i++)
        {
            if (temphashtable[hvalue][i].first == ps[j])
            {
                matched= 1;
                temphashtable[hvalue][i].second++;
            }
        }
        if (matched == 0)
        {
            temphashtable[hvalue].push_back({ps[j], 1});
        }
    }
    double finalans = 0;
    for (auto q : words)
    {
        double ans = 0;
        ll cnt = 0;
        int hvalue = hval2(q);
        if(hvalue<temphashtable.size()){
            for (auto i : temphashtable[hvalue])
            {
                if (i.first == q)
                {
                    cnt = i.second;
                    break;
                }
            }
        }
        if (cnt != 0)
        {
            ll num = dic.get_word_count(q);
            ll den = 0;
            int hvalue=hval(q);
            for (auto j : gencnt[hvalue]){
                if (j.first == q)
                {
                    den = j.second;
                    break;
                }
            }
            ans = num + 1;
            ans = ans / (den + 1);
            finalans += cnt * ans;
        }
    }
    return finalans;
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    dic.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    para temp2;
    temp2.bookcode = book_code;
    temp2.parag = paragraph;
    temp2.pg = page;
    if (allparas.size() == 0)
    {
        allparas.push_back(temp2);
        return;
    }
    para temp = allparas[allparas.size() - 1];
    if (temp.bookcode != book_code || temp.pg != page || temp.parag != paragraph)
    {
        allparas.push_back(temp2);
    }
    if(paras.size()<book_code+1){
        paras.resize(book_code+1);
    }
    if(paras[book_code].size()<page+1){
        paras[book_code].resize(page+1);
    }
    if(paras[book_code][page].size()<paragraph+1){
        paras[book_code][page].resize(paragraph+1);
    }
    paras[book_code][page][paragraph]+=sentence;
    return;
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    vector<string> words = change_sentence(question);
    priorityq ans;
    for (auto i : allparas)
    {
        string p = paras[i.bookcode][i.pg][i.parag];
        double s = getscore(words, p);
        if(ans.size<k){
            ans.insert(i,s);
        }
        else if(ans.v[0].second<s)
        {
            ans.deletemin();
            ans.insert(i,s);
        }
    }
    vector<Node *> a;
    vector<Node *> b;
    for (int j=ans.size-1;j>-1;j--)
    {
        string p = paras[ans.v[0].first.bookcode][ans.v[0].first.pg][ans.v[0].first.parag];
        double s = getscore(words, p);
        Node *temp2=new Node(ans.v[0].first.bookcode,ans.v[0].first.pg,ans.v[0].first.parag,0,0);
        a.push_back(temp2);
        ans.deletemin();
    }
    int n=a.size()-1;
    while(n>-1)
    {
        b.push_back(a[n]);
        n--;
    }
    if (b.size() != 0)
    {
        b[0]->left = NULL;
        b[b.size() - 1]->right = NULL;
        if (b.size() != 1)
        {
            for (int k = 0; k < b.size() - 1; k++)
            {
                b[k]->right = b[k + 1];
            }
        }
        return b[0];
    }
    return nullptr;
}

void QNA_tool::query(string question, string filename)
{
    // Implement your function here
    // question =
    ll total_para = allparas.size(); // log ka numerator

    string wo;
    vector<string> words = change_sentence(question);
    // while (iss >> wo)
    // {
    //     words.push_back(wo);
    // }
    vector<double> storing_tf;
    float k1=0.5;
    float b=0.2;
    float avg=20;
    for (auto w : words)
    {
        if(w.size()==1 || w=="gandhi" || w=="gandhiji"||w=="mahatama" || w == "a" || w == "about" || w == "above" || w == "after" || w == "again" ||  w == "all" || w == "am" || w == "an" || w == "and" || w == "any" || w == "are" || w == "aren" || w == "as" || w == "at" || w == "be" || w == "because" || w == "been" || w == "before" || w == "being" || w == "below" || w == "between" || w == "both" || w == "but" || w == "by" || w == "can" || w == "cannot" || w == "could" || w == "couldn" || w == "did" || w == "didn" || w == "do" || w == "does" || w == "doesn" || w == "doing" || w == "don" || w == "down" || w == "during" || w == "each" || w == "for" || w == "from" || w == "further" || w == "had" || w == "hadn" || w == "has" || w == "hasn" || w == "have" || w == "haven" || w == "having" || w == "he" || w == "he" || w == "d"|| w == "he" || w == "ll" || w == "he" || w == "her" || w == "here" || w == "here" || w == "hers" || w == "herself" || w == "him" || w == "himself" || w == "his" || w == "how" || w == "how's" || w == "i" || w == "i'd" || w == "i'll" || w == "i"|| w== "m" || w == "i" || w=="ve" || w == "if" || w == "in" || w == "into" || w == "is" || w == "isn't" || w == "it" || w == "it's" || w == "its" || w == "itself" || w == "let's" || w == "me" || w == "more" || w == "most" || w == "mustn't" || w == "my" || w == "myself" || w == "no" || w == "nor" || w == "not" || w == "of" || w == "off" || w == "on" || w == "once" || w == "only" || w == "or" || w == "other" || w == "ought" || w == "our" || w == "ours" || w == "ourselves" || w == "out" || w == "over" || w == "own" || w == "same" || w == "shan't" || w == "she" || w == "she'd" || w == "she'll" || w == "she's" || w == "should" || w == "shouldn't" || w == "so" || w == "some" || w == "such" || w == "than" || w == "that" || w == "that's" || w == "the" || w == "their" || w == "theirs" || w == "them" || w == "themselves" || w == "then" || w == "there" || w == "there's" || w == "these" || w == "they" || w == "they'd" || w == "they'll" || w == "they" || w == "re" || w == "they've" || w == "this" || w == "those" || w == "through" || w == "to" || w == "too" || w == "under" || w == "until" || w == "up" || w == "very" || w == "was" || w == "wasn't" || w == "we" || w == "we'd" || w == "we'll" || w == "we're" || w == "we've" || w == "were" || w == "weren't" || w == "what" || w == "what's" || w == "when" || w == "when's" || w == "where" || w == "where's" || w == "which" || w == "while" || w == "who" || w == "who's" || w == "whom" || w == "why" || w == "why's" || w == "with" || w == "won't" || w == "would" || w == "wouldn't" || w == "you" || w == "you'd" || w == "you'll" || w == "you're" || w == "you've" || w == "your" || w == "yours" || w == "yourself" || w == "yourselves"
) continue;
       // cout << w << endl;

        // double sum=0;
        int log_deno = 0; // log ka denominator // no. of para that have the word t
        // cout<<"word "<<w<<endl;
        for (auto p : allparas)
        {
            // string para = get_paragraph(p.bookcode, p.pg, p.parag);
            string para = paras[p.bookcode][p.pg][p.parag];
            vector<string> r = change_sentence(para);
            ll tf_deno = 0, tf_num = 0;
            tf_deno = r.size();
            bool is_present=false; //is the word w present in para p
            for(auto s:r){
                if(s==w) {
                    tf_num++;
                    is_present= true;
                }
            }
            if(is_present) log_deno++;
            // for (int k = 0; k < r.size(); k++)
            // {
            //     int n = r[k].size();
            //     string word = "";
            //     for (int i = 0; i < n; i++)
            //     {

            //         if (r[k][i] == ' ')
            //         {
            //             if (word == w)
            //             {
            //                 tf_num++;
            //             }
            //             tf_deno++;
            //             word = "";
            //         }
            //         else
            //         {
            //             word.push_back(r[k][i]);
            //         }
            //         if (i == n - 1)
            //         {
            //             if (word == w)
            //             {
            //                 tf_num++;
            //             }
            //             tf_deno++;
            //         }
            //     }
            // }
            // if (tf_num != 0)
            // {
            //     log_deno++;
            // }
            double tf = (double)(tf_num*(k1+1))*1.0/(tf_num+k1*(1-b + (b*(tf_deno*1.0)/avg)));
            storing_tf.push_back(tf);
            // sum+=tf;
        }
        // ***********make this below by your own
        ll N= total_para;
        ll Nq= log_deno;

        double idf = log2f(1+((N-Nq+0.5)*1.0/(Nq+0.5)));
        for (int i = 0; i < allparas.size(); i++)
        {
            allparas[i].score += storing_tf[i] * idf;
        }
        storing_tf.clear();
    }
    vector<pair<double, vector<int>>> ans;
    priorityq pq;
    int k=14;
    for (auto p : allparas)
    {
        // vector<int> m;
        // m.push_back(p.bookcode);
        // m.push_back(p.pg);
        // m.push_back(p.parag);
        // ans.push_back({p.score, m});
        if(pq.size<k){
            pq.insert(p,p.score);
        }
        else{
            pq.insert(p,p.score);
            pq.deletemin();
        }
    }
    vector<Node *> a;


    for(int i=0;i<k;i++)
    {
        Node* temp = new Node(pq.v[0].first.bookcode,pq.v[0].first.pg,pq.v[0].first.parag,0,0);
        a.push_back(temp);
        pq.deletemin();
    }
    for(int i=0;i<k/2;i++)
    {
        swap(a[i],a[k-i-1]);
    }
    // ***********make these below by your own
    // sort(ans.begin(), ans.end());
    // reverse(ans.begin(), ans.end());



    // for (auto x : ans)
    // {
    //     Node *temp2;
    //     temp2->book_code = x.second[0];
    //     temp2->page = x.second[1];
    //     temp2->paragraph = x.second[2];
    //     a.push_back(temp2);
    // }
    if (a.size() != 0)
    {
       // cout<<"linked list created"<<endl;
        a[0]->left = NULL;
        a[a.size() - 1]->right = NULL;
        if (a.size() != 1)
        {
            for (int i = 0; i < a.size() - 1; i++)
            {
                a[i]->right = a[i + 1];
            }
        }
    }

    // Node *ans = get_top_k_para(question, 5);
    // string q = "write a few lines about the Dandi march";
    std::cout << "Q: " << question << std::endl;
    query_llm(filename, a[0], k, "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", question);

   // std::cout << "A: "
    //          << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

  //  cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;

    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }

            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Maharishi's books.\nOn the basis of this, ";
    outfile << question;
   // outfile<<"To attain happiness.";
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}