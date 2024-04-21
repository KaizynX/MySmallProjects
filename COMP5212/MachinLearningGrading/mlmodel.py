from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
# from xgboost import XGBClassifier


import pandas as pd


# Here is only a template for your reference, you only need to ensure the predict function can 
# receive the test dataset and return the prediction results.



class MachineLearningModel():
    def __init__(self):
        self.model = SVC(kernel='rbf', C=0.5, gamma='auto')

    def train(self, data: pd.DataFrame):
        #you can do your training here
        self.model = self.model.fit(data.drop('Label', axis=1), data['Label'])

    # def preprocess(self, data):
        # you can do your preprocessing here

    def predict(self, data):
        df_train = pd.read_csv('./train.csv')
        # Apply any data preprocessing if you want, just to keep the test data in the same format as the training data
        self.train(df_train)
        return self.model.predict(data)