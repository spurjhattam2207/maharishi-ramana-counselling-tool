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
        q_paragraph.append("You are maharishi ramana's chatbot . You need to answer as if you were present before the person asking you question. you need to answer the question accordingly.")
        q_paragraph.append("The question is:")
        q_paragraph.append(query)  
        
        q_paragraph.append('\n')
     
    q_paragraph = '\n'.join(q_paragraph)    
    print (q_paragraph)
    query = {
        "role": "user", "content": q_paragraph
    }

    chat = client.chat.completions.create(model="gpt-3.5-turbo",
    messages=[query])

    reply = chat.choices[0].message.content
    
    print(reply)
    