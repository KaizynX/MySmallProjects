import pandas as pd
import numpy as np
from mlmodel import MachineLearningModel

mlmodel = MachineLearningModel()
df = pd.read_csv('../data/validation.csv')
X_test = df.drop('Label', axis=1)
y_test = df['Label']
result = mlmodel.predict(X_test)
print('Accuracy: ', np.mean(result == y_test))