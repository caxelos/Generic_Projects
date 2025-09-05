
# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from pandas import DataFrame as df

'''
******************************* Function Definition **********************
'''


'''
Function: parseDatabase
Input: filename
Output: panda's dataframe,including the paper id. For each paper
we also include the papers that cited that paper 
'''
def parseDatabase(filename):
    file = open(filename,"r")# errors='ignore','r')#, encoding='uth-8)
    numOfPapers=int(file.readline())
    df = pd.DataFrame(np.zeros((numOfPapers,3)),columns=['Year','Paper_id','References_ids'])
    df = df.astype('object')
    bytesPerRead=10485; 
    i=0;

    
    Lines=np.chararray(bytesPerRead+1024,itemsize=1)
    line=np.chararray(5000,itemsize=1)    
    Lines = file.readlines(bytesPerRead)    
    refids=[]
    while len(Lines) != 0:
        for line in Lines:
            if line=='\n':
                if len(refids)>0:
                    df.at[i,'References_ids']=refids#np.asarray(refids, dtype=np.int32)
                else:
                    df.at[i,'References_ids']=[]
                i+=1
                refids=[]
                if i%10000==0:
                    print(i)
            elif line[1]=='t':#Year
                df.at[i,'Year'] = int(line[2:].rstrip('\n'))
            elif 'i'==line[1]:#Paper_id
                df.at[i,'Paper_id'] = int(line[6:].rstrip('\n'))    
            elif line[1]=='%':#Reference_ids
                refids.append(int(line[2:].rstrip('\n')))
        Lines=file.readlines(bytesPerRead)
    return df

'''
Function: createTimeSeries
Input: a) df: panda's dataframe. The output of parseDatabase())
       b) timelen: size of time-series. In that project, we found that the optimal
    length for each time-serie is 15
       c) minRefPapers: We reject papers that have been cited less than 
    "minRefPapers" times. We found minRefPapers=1 as optimal value. The range from
    1 until 5 gives the best results
    
Output: timeSeries: the final time-series that are going to be the
    input to our network
'''
def createTimeSeries(df,timelen,minRefPapers):
    numOfPapers=629814
    df=df.sort_values('Year').reset_index(drop=True)
    citationId=[[] for _ in range(numOfPapers)]
    citationYear=[[] for _ in range(numOfPapers)]
    for curr in range(numOfPapers):
        for paperid in df.at[curr,'References_ids']:
            if df.at[curr,'Year'] > df.at[paperid,'Year']:
                citationId[paperid].append(df.at[curr,'Paper_id'])
                citationYear[paperid].append(df.at[curr,'Year'])
        
    
    timeSeries=[]
    for curr in range(0,numOfPapers-1):
        if citationYear[curr] != []:
            maxY=max(citationYear[curr])        
            if maxY-df.at[curr,'Year']>timelen:
                temp= np.zeros(maxY-df.at[curr,'Year'], dtype=int)
                for paperyear in citationYear[curr]:
                    temp[paperyear-df.at[curr,'Year']-1]+=1                
                firstNonZero = 0
                while temp[firstNonZero] == 0:
                    firstNonZero = firstNonZero+1
                if len(temp)-firstNonZero > timelen:
                    numOfLoops=len(temp)-firstNonZero-timelen
                    for j in range(numOfLoops):
                        if np.sum(temp[(firstNonZero+j):(firstNonZero+timelen+j)]) > minRefPapers:
                            timeSeries.append(temp[(j+firstNonZero):(firstNonZero+timelen+j+1)])
                            
    timeSeries=np.array(timeSeries)
    return timeSeries

'''
****************************** main script **************************** 
'''

df = parseDatabase('database.txt')
curr_timelen=15#=0.3775
curr_minRefPapers=1
curr_batch_size=64#512
timeSeries = createTimeSeries(df,timelen=curr_timelen,minRefPapers=curr_minRefPapers)


'''
create test and train data
'''
from sklearn.model_selection  import train_test_split
X=np.zeros((len(timeSeries),len(timeSeries[0,:])-1),dtype=float)
Y=np.zeros((len(timeSeries),1),dtype=float)#the value we need to predict
X=timeSeries[:,0:-1]
Y=timeSeries[:,-1]
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.2, random_state = 0)
X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))

from keras.layers import LSTM
from keras.layers import Dropout
from keras.models import Sequential
from keras.layers import Dense

'''
reshape is necessary in LSTMs to create time dimension. Not
needed in Feed Forward networks
'''
X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))



'''
Initialize network and add the layers
'''
regressor = Sequential()
regressor.add(LSTM(units = 64, return_sequences = True,input_shape = (X_train.shape[1], 1)))
regressor.add(Dropout(0.2))# 20%(so 10 neurons) dropout is recommended. Forward/Backward propagations ignored!!
regressor.add(LSTM(units = 64, return_sequences = True))
regressor.add(Dropout(0.2))
regressor.add(LSTM(units = 64, return_sequences = True))
regressor.add(Dropout(0.2))
regressor.add(LSTM(units = 64, return_sequences = True))
regressor.add(Dropout(0.2))
regressor.add(LSTM(units = 64)) 
regressor.add(Dropout(0.2))
regressor.add(Dense(units = 1))
regressor.compile(optimizer = 'adam', loss = 'mean_squared_error',metrics = ['accuracy'])

'''
measure the training time
'''
import timeit
start=timeit.default_timer()
regressor.fit(X_train, Y_train, batch_size=64, nb_epoch=25)
stop=timeit.default_timer()
total_time=stop-start

'''
make the predictions
'''
X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))
Y_pred = np.round(regressor.predict(X_test))
predictions=[]
for elem in Y_pred:
    predictions.append(int(round(elem[0])))
predictions=np.array(predictions)
   

'''
create mean squared error(mse) and standar deviation(std)
'''
from sklearn.metrics import mean_squared_error
mse=mean_squared_error(Y_test,predictions)
std=np.std(Y_test-predictions)


'''
save model's parameters 
'''
regressor.save('lstm_model_25_epochs.h5') 
