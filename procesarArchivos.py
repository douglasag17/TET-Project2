import pandas as pd
import glob

columns = ['id', 'title', 'content']
allFiles = glob.glob("*.csv")
frame = pd.DataFrame()
for file_ in allFiles:
    df = pd.read_csv(file_,index_col=None, header=0, usecols=columns)
    df['content'] = df['content'].str.lower()
    df.to_csv("P"+file_, sep=',', index=True, header=True)
