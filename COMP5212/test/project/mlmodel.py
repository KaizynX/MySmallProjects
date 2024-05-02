'''
Author: Kaizyn
Date: 2024-05-02 15:53:31
LastEditTime: 2024-05-02 15:54:10
'''
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, VotingClassifier


import pandas as pd


# Here is only a template for your reference, you only need to ensure the predict function can
# receive the test dataset and return the prediction results.

# class EnsembleModel:
class MachineLearningModel:
    def __init__(self):
        # 创建多个模型
        clf3 = SVC(kernel="rbf", C=0.5, gamma="auto", probability=True)
        clf4 = KNeighborsClassifier(n_neighbors=10, p=2, weights="distance")

        # 创建 VotingClassifier
        self.model = VotingClassifier(
            estimators=[
                ("svc", clf3),
                ("knn", clf4)
            ],
            voting="soft",
        )

        df_train = pd.read_csv("./train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        self.model = self.model.fit(data.drop("Label", axis=1), data["Label"])

    def predict(self, data: pd.DataFrame):
        return self.model.predict(data)
