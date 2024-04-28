from xgboost import XGBClassifier
from imblearn.over_sampling import SMOTE, ADASYN
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

# class EnsembleModel:
class MachineLearningModel:
    def __init__(self):
        # 创建多个模型
        clf1 = XGBClassifier(gamma=0, learning_rate=0.1, max_depth=10, n_estimators=200)
        clf2 = RandomForestClassifier(max_depth=20, min_samples_leaf=2, min_samples_split=2, n_estimators=100, random_state=0)
        clf3 = SVC(kernel="rbf", C=0.9, gamma="auto", probability=True)
        clf4 = KNeighborsClassifier(n_neighbors=10, p=2, weights="distance")

        # 创建 VotingClassifier
        self.model = VotingClassifier(
            estimators=[
                ("xgb", clf1),
                ("rf", clf2),
                ("svc", clf3),
                ("knn", clf4)
            ],
            voting="soft",
            weights=[0.8925, 0.8819, 0.9119, 0.8972],
        )

        df_train = pd.read_csv("./train.csv")
        self.train(df_train)

    def train(self, data: pd.DataFrame):
        self.model = self.model.fit(data.drop("Label", axis=1), data["Label"])

    def predict(self, data: pd.DataFrame):
        return self.model.predict(data)
