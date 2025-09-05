#from keras.layers import LSTM
#from keras.layers import Dropout
#from keras.models import Sequential
#from keras.layers import Dense
from keras.models import load_model
import numpy as np
regressor = load_model('model.h5')
with open('test_cases/timeseries01.txt','r') as f:
    values=f.readline()#list(reader)
    values=values.split(' ')[0:-1]
    

X_test=np.zeros(15,dtype=int)
padding_size=15-len(values)
predictions=[]
if padding_size>=0:     ##if timeseries has len less than 15
    for i in range(len(values)):
        X_test[padding_size+i]=int(values[i])
    
elif padding_size<0:   ##if timeseries has len more than 15
    for i in range(15):
        X_test[i]=int(values[abs(padding_size)+i])
 
for j in range(5):    ##loop for predicting the next 5 citations counts
    X_test_reshaped = X_test.reshape((1, 15, 1))
    Y_pred = int(np.round(regressor.predict(X_test_reshaped)))
    #edw mia print to 1st prediction
    X_test[0:-1]=X_test[1:]
    X_test[-1]=Y_pred
    if j == 0 or j == 4:   ##include only first and 5th prediction
        predictions.append(Y_pred)
