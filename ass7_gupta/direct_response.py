# from openai import OpenAI
# import sys
# client = OpenAI(api_key=sys.argv[1])



# if __name__ == '__main__':
#     if len(sys.argv) < 3:
#         print("Usage: python3 api_call.py API_KEY original_que.txt")
#         sys.exit(1)
        
#     q_paragraph = []    
#     query_file = sys.argv[2]
#     with open(query_file, 'r') as f:
#         query = f.read()
#         q_paragraph.append("You are maharishi ramana's chatbot . You need to answer as if you were present before the person asking you question. you need to answer the question accordingly.")
#         q_paragraph.append("The question is:")
#         q_paragraph.append(query)  
        
#         q_paragraph.append('\n')
     
#     q_paragraph = '\n'.join(q_paragraph)    
#     print (q_paragraph)
#     query = {
#         "role": "user", "content": q_paragraph
#     }

#     chat = client.chat.completions.create(model="gpt-3.5-turbo",
#     messages=[query])

#     reply = chat.choices[0].message.content
    
#     print(reply)
    
import os
import sys
import replicate

#Set the REPLICATE_API_TOKEN environment variable

if __name__ == '__main__':
    
    # python3 <filename> API_KEY num_paragraphs query.txt
    if len(sys.argv) < 3:
        print("Usage: python3 api_call.py API_KEY num_paragraphs query.txt")
        sys.exit(1)

    # Read the API key from the command line
    
    q_paragraph = []    
    query_file = sys.argv[2]
    with open(query_file, 'r') as f:
        query = f.read()
        q_paragraph.append("You are maharishi ramana's chatbot . You need to answer as if you were present before the person asking you question. you need to answer the question accordingly.")
        q_paragraph.append("The question is:")
        q_paragraph.append(query)  
        
        q_paragraph.append('\n')
     
    q_paragraph = '\n'.join(q_paragraph)    
    print (q_paragraph)

    os.environ["REPLICATE_API_TOKEN"] = "r8_1gyt2Ieh5k2VfRBhTBWhclT6DlFm5uf1Gs3l2"
    output = replicate.run(
    "meta/llama-2-70b-chat:2d19859030ff705a87c746f7e96eea03aefb71f166725aee39692f1476566d48",
    input={
        "debug": False,
        "top_p": 1,
        "top_k":10,
        "return_full_text":False,
        "max_length":4096,
        "prompt": q_paragraph,
        "temperature": 0.9,
        # "system_prompt": "You are a helpful and respectful counseller. Always answer as helpfully and supportive as possible. Your answers should not include any harmful, unethical, racist, sexist, toxic, dangerous, or illegal content. Please ensure that your responses are positive in nature.\n\nIf a question does not make any sense, or is not factually or spiritually coherent, explain why instead of answering something not correct.",
        "max_new_tokens": 256,
        "min_new_tokens": -1
    }
    )
    print(*output)
        # file.write('\n'.join(output))
