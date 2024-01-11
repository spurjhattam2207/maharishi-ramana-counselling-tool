from openai import OpenAI
import sys
client = OpenAI(api_key=sys.argv[1])



if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: python3 api_call.py API_KEY original_que.txt")
        sys.exit(1)
        
    q_paragraph = []    
    query_file = sys.argv[2]
    with open(query_file, 'r') as f:
        query = f.read()
        q_paragraph.append("You are maharishi ramana's chatbot and your purpose is to provide guidance to students. You are given an input ,if you feel it is a concern or problem that can be answered by maharishi ramana's teachings print 'y' else print 'n'. Don't print anything else.")
        q_paragraph.append("THE INPUT IS: ")
        q_paragraph.append(query)  
        q_paragraph.append("Again repeating DON'T PRINT ANYTHING ELSE ,EITHER ('y' OR 'n').")
        q_paragraph.append('\n')
     
    q_paragraph = '\n'.join(q_paragraph)    
    print (q_paragraph)
    query = {
        "role": "user", "content": q_paragraph
    }

    chat = client.chat.completions.create(model="gpt-3.5-turbo",
    messages=[query])

    reply = chat.choices[0].message.content
    
    with open("y_n.txt", 'w') as file:
        file.write(reply)   
    