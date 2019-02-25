import pandas as pd
import glob
from time import time

tiempo_inicial = time()
#iloc: Select row by index label.
columns = ['id', 'title', 'content']
allFiles = glob.glob("*.csv")
frame = pd.DataFrame()
list_ = []
for file_ in allFiles:
    df = pd.read_csv(file_,index_col=None, header=0, usecols=columns)
    list_.append(df)
frame = pd.concat(list_)
word = input("Type the word: ") 
for i,content in enumerate(frame['content']):
    count = 0
    for article in content.split():
        if word == article:
            count+=1
    if count > 0:
        print(count, frame['id'].iloc[i],frame['title'].iloc[i])

    







tiempo_final = time()
tiempo_ejecucion = tiempo_final - tiempo_inicial
print ('El tiempo de ejecucion fue:',tiempo_ejecucion) #En segundos