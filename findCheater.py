import os
import pandas as pd

from sklearn.metrics import mean_squared_error 

data = pd.DataFrame(index=range(100))
count = 0 
directory = "./data"
for filename in os.listdir("./data"):
    count += 1
    if filename.endswith(".csv"):
        df = pd.read_csv(os.path.join(directory, filename))
        del df['Time']
        # df.columns = [filename]
        data[filename] = df
    else:
        continue
printomputed averages")
averages = data.mean(axis=1).to_numpy()
# print(averages)

mse = pd.DataFrame(index=data.columns, columns=["MSE"], dtype='float64')
for index in mse.index: 
    values = data[index].to_numpy()
    mse.at[index, "MSE"] =  mean_squared_error(averages, values)

# print(mse)
print(mse.idxmin())
print(mse.min())

    