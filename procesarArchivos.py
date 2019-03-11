import pandas as pd
import glob

columns = ['id', 'title', 'content']
allFiles = glob.glob("/opt/datasets/*.csv")
frame = pd.DataFrame()
i = 1
for file_ in allFiles:
    df = pd.read_csv(file_,index_col=None, header=0, usecols=columns)
    df['content'] = df['content'].str.lower()
    df['content'] = df['content'].str.replace(',', ' ')
    df['content'] = df['content'].str.replace('.', ' ')
    df['content'] = df['content'].str.replace(';', ' ')
    df['content'] = df['content'].str.replace(':', ' ')
    df['content'] = df['content'].str.replace('?', ' ')
    df['content'] = df['content'].str.replace('!', ' ')
    df['content'] = df['content'].str.replace('"', ' ')
    df['content'] = df['content'].str.replace('#', ' ')
    df['content'] = df['content'].str.replace('”', ' ')
    df['content'] = df['content'].str.replace('’', ' ')
    df['content'] = df['content'].str.replace('[', ' ')
    df['content'] = df['content'].str.replace(']', ' ')
    df['content'] = df['content'].str.replace('(', ' ')
    df['content'] = df['content'].str.replace(')', ' ')
    df['content'] = df['content'].str.replace('“', ' ')
    df['content'] = df['content'].str.replace('‘', ' ')
    df['content'] = df['content'].str.replace('\t', ' ')
    df.to_csv("Particles"+str(i)+".csv", sep='\t', index=True, header=True)
    i+=1
