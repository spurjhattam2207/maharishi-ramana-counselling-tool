#include<bits/stdc++.h>
#include "Node.h"
#include "qna_tool.h"

using namespace std;

int main(){
    QNA_tool qna_tool;

    int num_books = 2;
    
    for(int i = 1; i <= num_books; i++){

        std::cout << "Inserting book " << i << std::endl;

        std::string filename = "mahatma-gandhi-collected-works-volume-";
        filename += to_string(i);
        filename += ".txt";

        std::ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the input file mahatma-gandhi." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;

    // cout<<"hi";
        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
            // Get a line in the sentence
            
            tuple += ')';

            std::vector<int> metadata;    
            std::istringstream iss(tuple);

            // Temporary variables for parsing
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
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
                    metadata.push_back(num);
                } else {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            // Now we have the string in sentence
            // And the other info in metadata
            // Add to the dictionary

            // Insert in the qna_tool
            qna_tool.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        }

        inputFile.close();

    }

    //string question = "hi ! can you help me in finding why i get less marks";
    string question;
    getline(cin,question);
    ofstream ofile("original_que.txt");
    ofile<<question;
    ofile.close();

    // ofstream pfile("answer.txt");
    // pfile<<"Question: "<<question<<endl;
    // pfile.close();

    string API_KEY = "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";
    // first call to filter whether the query is to be answered by chatgpt or corpus
    cout<<"billo\n";

    string second_filename = "que_check.py";
    string command = "python3 ";
    command += second_filename;
    command += " ";
    command += API_KEY;
    command += " ";
    // command += to_string(k);
    // command += " ";

    command += "original_que.txt";

    system(command.c_str());

    string response;
    ifstream in_file("y_n.txt");
    in_file>>response;
    in_file.close();

    if(response[0]=='y'){

        string second_filename = "que_modify.py";
        string command = "python3 ";
        command += second_filename;
        command += " ";
        command += API_KEY;
        command += " ";
        // command += to_string(k);
        // command += " ";

        command += "original_que.txt";

        system(command.c_str());




        string modified_question = "";
        string temp;
        ifstream ifile("modified_question.txt");
        while(getline(ifile,temp)){
            modified_question += temp;
        }
        ifile.close();
        // second call
        qna_tool.query(modified_question, "api_call.py");
    } 

    else{
        string second_filename = "direct_response.py";
        string command = "python3 ";
        command += second_filename;
        command += " ";
        command += API_KEY;
        command += " ";
        // command += to_string(k);
        // command += " ";

        command += "original_que.txt";

        system(command.c_str());

    }


    // second call for question modification

    
    

    /*
        Part-1 : Get the top-k paragraphs
        Checking Correctness
    */

    // Let's try to ask a simple question to the qna_tool
    // cout<<"books succesfully inserted"<<endl;
    // Node* head = qna_tool.get_top_k_para(question, 5);
    // //cout<<"get top k passed"<<endl;
    // vector<string> paras;
    // while(head != nullptr){
    //     // cout<<"sahu"<<endl;
    //     string res = qna_tool.get_paragraph(head->book_code, head->page, head->paragraph);
    //     //cout<<head->book_code<<" "<<head->page<<" "<<head->paragraph<<endl;
    //     paras.push_back(res);
    //     head = head->right;
    // }

    // for(int i = 0; i < (int)paras.size(); i++){
    //     // cout << paras[i] << endl << endl << endl;
    // }

    /*
        Part-2 : Query the LLM
    */
    

    return 0;
}