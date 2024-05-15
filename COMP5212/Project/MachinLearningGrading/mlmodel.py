'''
Author: Kaizyn 2291443901@qq.com
Date: 2024-04-14 23:55:12
LastEditors: Kaizyn 2291443901@qq.com
LastEditTime: 2024-04-21 23:52:09
FilePath: \COMP5212\MachinLearningGrading\mlmodel.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
# from xgboost import XGBClassifier
# from imblearn.over_sampling import SMOTE, ADASYN
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, VotingClassifier
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler


import pandas as pd


# Here is only a template for your reference, you only need to ensure the predict function can
# receive the test dataset and return the prediction results.


class MachineLearningModel:
    def __init__(self):
        self.model = SVC(kernel="rbf", C=0.5, gamma="auto")

        df_train = pd.read_csv("../data/train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        # you can do your training here
        self.model = self.model.fit(data.drop("Label", axis=1), data["Label"])

    # def preprocess(self, data):
    # you can do your preprocessing here

    def predict(self, data: pd.DataFrame):
        # Apply any data preprocessing if you want, just to keep the test data in the same format as the training data
        return self.model.predict(data)

class SVCModel:
    def __init__(self):
        self.model = SVC(kernel="rbf", C=0.5, gamma="auto")

        df_train = pd.read_csv("../data/train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        self.model = self.model.fit(data.drop("Label", axis=1), data["Label"])

    def predict(self, data: pd.DataFrame):
        return self.model.predict(data)


class PCAModel:
    def __init__(self):
        self.model = SVC(kernel="rbf", C=0.5, gamma="auto")
        self.scaler = StandardScaler()
        self.pca = PCA(n_components=4)

        df_train = pd.read_csv("../data/train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        data_scaled = self.scaler.fit_transform(data.drop("Label", axis=1))
        data_pca = self.pca.fit_transform(data_scaled)
        self.model = self.model.fit(data_pca, data["Label"])

    def predict(self, data: pd.DataFrame):
        data_scaled = self.scaler.transform(data)
        data_pca = self.pca.transform(data_scaled)
        return self.model.predict(data_pca)


# class EnsembleModel:
class MachineLearningModel:
    def __init__(self):
        # 创建多个模型
        # clf1 = XGBClassifier()
        clf2 = RandomForestClassifier(n_estimators=50, random_state=1)
        clf3 = SVC(kernel="rbf", C=0.5, gamma="auto", probability=True)
        clf4 = KNeighborsClassifier()

        # 创建 VotingClassifier
        self.model = VotingClassifier(estimators=[
            # ("xgb", clf1), 
            ("rf", clf2), 
            ("svc", clf3), 
            ("knn", clf4)
        ], voting="soft")

        df_train = pd.read_csv("../data/train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        self.model = self.model.fit(data.drop("Label", axis=1), data["Label"])

    def predict(self, data: pd.DataFrame):
        return self.model.predict(data)