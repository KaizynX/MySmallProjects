import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset
import numpy as np
'''
You need to implement the Net class and the dataset class for the model to work.

You can add additional classes or functions, but don't change the name or signature of the existing ones.

Note: we would only call the Net and dataset class, so other more class or functions should be called in this two class.

You must run the grading.py successfully to pass the homework.
'''

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.fc = nn.Linear(7, 1)

    def forward(self, x):
        x = x.view(-1, 1, 7)
        return self.fc(x)
    
# sample test set, just same shape
class dataset(Dataset):
    def __init__(self, file_path):
        self.X = torch.from_numpy(np.array([[1,1,1,1,1,1,1], [1,1,1,1,1,1,1]])).float()
        self.y = torch.from_numpy(np.array([[1], [1]])).float()

    def __len__(self):
        return len(self.X)

    def __getitem__(self, idx):
        return self.X[idx], self.y[idx]
    