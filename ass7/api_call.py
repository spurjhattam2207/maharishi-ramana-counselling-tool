from openai import OpenAI
import sys
client = OpenAI(api_key=sys.argv[1])



if __name__ == '__main__':
    
    # python3 <filename> API_KEY num_paragraphs query.txt
    if len(sys.argv) < 4:
        print("Usage: python3 api_call.py API_KEY num_paragraphs query.txt")
        sys.exit(1)

    # Read the API key from the command line
    
    num_paragraphs = int(sys.argv[2])
    print(num_paragraphs)

    # Read the paragraphs from the files
    paragraphs = []

    for i in range(num_paragraphs):
        filename = 'paragraph_' + str(i) + '.txt'
        # print(filename)
        with open(filename, 'r') as f:
            paragraphs.append(f.read())
            paragraphs.append('\n')
    
    # add query
    query_file = sys.argv[3]
    with open(query_file, 'r') as f:
        query = f.read()
        paragraphs.append(query)
        paragraphs.append('\n')

    # convert paragraphs to a single string
    paragraphs = '\n'.join(paragraphs)

    print(paragraphs)

    #this is the main query to chatgpt which gives reply
    query = {
        "role": "user", "content": paragraphs
    }

    chat = client.chat.completions.create(model="gpt-3.5-turbo",
    messages=[query])
    #this reply is the reply to the paragrapghs and modified query
    reply = chat.choices[0].message.content
    
    print(reply)
    #read the original question from file and append the answer given 
    # q_ans=[]
    # with open("answer.txt", 'r') as f:
    #     query = f.read()
    #     q_ans.append(query)
    #     q_ans.append("ANSWER: ")
    #     q_ans.append(reply)
    #     q_ans.append('\n')
    #     q_ans.append("The above is the question and answer to it. output the answer as it is ")

    # q_ans = '\n'.join(q_ans)  
    # print(q_ans)
    # query = {
    #     "role": "user", "content": q_ans
    # }

    # chat = client.chat.completions.create(model="gpt-3.5-turbo",
    # messages=[query])
    # #this reply is the final reply
    # reply = chat.choices[0].message.content  
    
    # print(reply)
    