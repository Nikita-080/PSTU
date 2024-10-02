import ollama
from os import listdir

START=0

data=""
pac_len=8000
path='./gost/'
for i in listdir(path):
    with open(path+i) as f:
        data+=f.read()
print(len(data))
#print(data[:100])
for i in range(START,len(data),pac_len):
    pac=data[i:i+pac_len]
    response = ollama.chat(model='llama3:8b', messages=[
      {
        'role': 'user',
        'content': "напиши рекомендации по написанию документации на основе этого текста: "+pac+", отвечай на русском языке в формате markdown "
      },
    ])
    with open("./gost.md",'a',encoding="utf-8") as f:
        f.write(response['message']['content'])
    print("Ready:",i)
