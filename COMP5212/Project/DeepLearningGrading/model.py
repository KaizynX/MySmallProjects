import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset
import numpy as np
import pandas as pd
import torch.optim as optim
from tqdm import tqdm
from sklearn.model_selection import KFold
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


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(7, 64),
            nn.ReLU(),
            nn.Linear(64, 32),
            nn.ReLU(),
            nn.Linear(32, 16),
            nn.ReLU(),
            nn.Linear(16, 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        x = x.view(-1, 7)
        return self.fc(x)

# sample test set, just same shape
class dataset(Dataset):
    def __init__(self, file_path = '../data/validation.csv'):
        data = pd.read_csv(file_path)
        self.X = torch.from_numpy(data.drop('Label', axis=1).values).float()
        self.y = torch.from_numpy(data[['Label']].values).float()

    def __len__(self):
        return len(self.X)

    def __getitem__(self, idx):
        return self.X[idx], self.y[idx]


if __name__ == '__main__':
    # # 创建数据集
    # datas = dataset('../data/train.csv')

    # # 定义K-fold交叉验证
    # kfold = KFold(n_splits=5, shuffle=True)

    # # 初始化最小验证损失为无穷大
    # min_val_loss = float('inf')

    # # 开始K-fold交叉验证
    # for fold, (train_ids, val_ids) in tqdm(enumerate(kfold.split(datas)), desc="fold: "):
    #     # 创建训练集和验证集数据加载器
    #     train_subsampler = torch.utils.data.SubsetRandomSampler(train_ids)
    #     val_subsampler = torch.utils.data.SubsetRandomSampler(val_ids)

    #     train_loader = torch.utils.data.DataLoader(datas, batch_size=32, sampler=train_subsampler)
    #     val_loader = torch.utils.data.DataLoader(datas, batch_size=32, sampler=val_subsampler)

    #     # 创建网络和优化器
    #     net = Net()
    #     criterion = nn.BCEWithLogitsLoss()
    #     optimizer = optim.Adam(net.parameters(), lr=0.01)

    #     # 训练网络
    #     for epoch in tqdm(range(10), desc="epoch: "):
    #         running_loss = 0.0
    #         for i, data in enumerate(train_loader, 0):
    #             inputs, labels = data

    #             # 清零梯度
    #             optimizer.zero_grad()

    #             # 前向传播，反向传播，优化
    #             outputs = net(inputs)
    #             loss = criterion(outputs, labels.view(-1, 1))
    #             loss.backward()
    #             optimizer.step()

    #             # 打印统计信息
    #             running_loss += loss.item()
    #             if i % 20 == 19:  # 每2000个mini-batches打印一次
    #                 print('[%d, %3d] loss: %.3f' %
    #                       (epoch + 1, i + 1, running_loss / 2000))
    #                 running_loss = 0.0

    #     # 在验证集上计算损失
    #     val_loss = 0.0
    #     with torch.no_grad():
    #         for data in val_loader:
    #             inputs, labels = data
    #             outputs = net(inputs)
    #             loss = criterion(outputs, labels.view(-1, 1))
    #             val_loss += loss.item()

    #     print(f'Fold {fold}, Validation loss {val_loss}')

    #     # 如果当前模型的验证损失比之前的最小验证损失还小，那么保存当前模型
    #     if val_loss < min_val_loss:
    #         min_val_loss = val_loss
    #         torch.save(net.state_dict(), './final_model.pth')

    # 创建数据集
    train_dataset = dataset('../data/train.csv')
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=32, shuffle=True)

    # 创建网络和优化器
    net = Net()
    criterion = nn.BCEWithLogitsLoss()
    optimizer = optim.Adam(net.parameters(), lr=0.01)
    scheduler = optim.lr_scheduler.ReduceLROnPlateau(optimizer, 'min')

    # 创建验证集数据加载器
    val_dataset = dataset('../data/validation.csv')
    val_loader = torch.utils.data.DataLoader(val_dataset, batch_size=320, shuffle=True)

    # 训练网络
    best_loss = float('inf')
    for epoch in tqdm(range(20), desc='epoch'):
        running_loss = 0.0
        for i, data in enumerate(train_loader, 0):
            inputs, labels = data

            # 清零梯度
            optimizer.zero_grad()

            # 前向传播，反向传播，优化
            outputs = net(inputs)
            loss = criterion(outputs, labels.view(-1, 1))
            loss.backward()
            optimizer.step()

            # 打印统计信息
            running_loss += loss.item()
            if i % 20 == 19:  # 每200个mini-batches打印一次
                print('[%d, %5d] loss: %.3f' %
                      (epoch + 1, i + 1, running_loss / 2000))
                running_loss = 0.0

        # 在验证集上计算损失
        val_loss = 0.0
        with torch.no_grad():
            for data in val_loader:
                inputs, labels = data
                outputs = net(inputs)
                loss = criterion(outputs, labels.view(-1, 1))
                val_loss += loss.item()

        # 如果验证损失下降，保存模型
        if val_loss < best_loss:
            best_loss = val_loss
            torch.save(net.state_dict(), './final_model.pth')

        # 更新学习率
        scheduler.step(val_loss)

    print('Finished Training')