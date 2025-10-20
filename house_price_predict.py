#!/usr/bin/env python
# coding: utf-8

# In[1]:


# 模型配置参数字典
# 这些超参数控制着模型的训练过程和网络结构
config = {
  'TEST_SIZE': 0.2,        # 验证集比例：20%的数据用于验证，80%用于训练
  'BATCH_SIZE': 32,        # 批次大小：每次训练使用32个样本
  'EPOCHS': 10,            # 训练轮数：整个数据集被训练的次数
  'LEARNING_RATE': 0.001,  # 学习率：控制参数更新的步长，越小训练越稳定但越慢
  'DROPOUT_RATE': 0.1      # Dropout比例：随机丢弃一定比例的神经元，防止过拟合
}


# In[2]:


# 导入必要的库
import pandas as pd  # 用于数据处理和分析
import warnings
warnings.filterwarnings("ignore")  # 忽略警告信息，保持输出清洁

# 读取数据集
# train.csv包含房屋特征和价格（用于训练模型）
# test.csv只包含房屋特征，需要预测价格（用于最终提交）
train = pd.read_csv("house_price_dataset/train.csv")
test = pd.read_csv("house_price_dataset/test.csv")

# 查看数据集的基本信息
print(f"训练集形状: {train.shape}")  # 显示训练集的行数和列数
print(f"测试集形状: {test.shape}")   # 显示测试集的行数和列数
print("列名预览:", list(train.columns[:10]))  # 显示前10个列名

# 显示前几行数据，了解数据结构
print(f"训练数据前5行预览:")
train.head()


# In[3]:


print(f"Train shape: {train.shape}")  # 训练集维度信息
print(f"Test shape: {test.shape}")    # 测试集维度信息

# 获取数据的详细信息：数据类型、非空值数量等
train.info()


# In[4]:


missing = train.isnull().sum()  # 计算每列的缺失值数量

# 筛选出有缺失值的列，并按缺失数量降序排列
missing = missing[missing > 0].sort_values(ascending=False)

# 显示缺失值最多的前10个特征
print(missing.head(10))


# In[5]:


# 数值型特征：可以直接进行数学运算（如面积、年份等）
num_features = train.select_dtypes(include=['int64', 'float64']).columns
print("Numerical Features:", list(num_features))

# 类别型特征：表示分类信息（如房屋类型、街道名等）
# 这些特征需要特殊处理（如one-hot编码）才能用于机器学习
cat_features = train.select_dtypes(include=['object']).columns
print("Categorical Features:", list(cat_features))


# In[6]:


# 数据清洗：删除缺失值过多的特征列
# 这些列缺失值超过90%，提供的信息有限，删除它们可以简化模型
cols_to_drop = ["PoolQC", "MiscFeature", "Alley", "Fence"]
train.drop(columns=cols_to_drop, inplace=True)  # inplace=True表示直接修改原数据


# In[7]:


# 这些特征的缺失值实际上表示"没有这个设施"，所以用"None"比删除更合理
none_fill_cols = [
    "FireplaceQu",
    "GarageType",
    "GarageFinish",
    "GarageQual",
    "GarageCond",
    "BsmtQual",
    "BsmtCond",
    "BsmtExposure",
    "BsmtFinType1",
    "BsmtFinType2",
    "MasVnrType",
]

# 批量填充这些列的缺失值
for col in none_fill_cols:
    train[col] = train[col].fillna("None")


# In[8]:


# LotFrontage: 临街宽度，用中位数填充（中位数对异常值不敏感）
train["LotFrontage"] = train["LotFrontage"].fillna(train["LotFrontage"].median())
# MasVnrArea: 石材贴面面积，缺失表示无石材贴面，用0填充
train["MasVnrArea"] = train["MasVnrArea"].fillna(0)
# GarageYrBlt: 车库建造年份，缺失表示无车库，用0填充
train["GarageYrBlt"] = train["GarageYrBlt"].fillna(0)


# In[9]:


# Electrical: 电气系统类型，只缺失1个值，用最常见的类型填充
# mode()[0] 获取众数（出现频率最高的值）
train["Electrical"] = train["Electrical"].fillna(train["Electrical"].mode()[0])


# In[10]:


# 验证缺失值处理效果：检查填充后还有哪些列存在缺失值
missing_after = train.isnull().sum()
missing_after = missing_after[missing_after > 0].sort_values(ascending=False)
print(missing_after)  # 理想情况下，这里应该没有输出，表示所有缺失值都已处理


# In[11]:


# 删除无关特征：ID列对预测房价没有意义
# ID只是数据的标识符，不包含有用的预测信息，保留会干扰模型学习
train.drop(['Id'], axis=1, inplace=True)


# In[12]:


# 特征和目标变量分离
# y: 目标变量（我们要预测的房价）
y = train['SalePrice']

# X: 特征矩阵（用于预测房价的所有输入特征）
# 删除目标列，剩下的都是特征
X = train.drop(['SalePrice'], axis=1)
X.shape, y.shape  # 查看特征矩阵和目标向量的维度


# In[13]:


# 特征编码：将类别型特征转换为数值型
# one-hot编码将每个类别转换为二进制向量
# 例如：颜色[红,绿,蓝] -> 红[1,0,0], 绿[0,1,0], 蓝[0,0,1]
X = pd.get_dummies(X)
X.shape  # one-hot编码后特征数量会大幅增加


# In[14]:


# 数据可视化：探索目标变量的分布特征
import seaborn as sns
import matplotlib.pyplot as plt

# 绘制房价分布直方图
# kde=True添加核密度估计曲线，更清楚地看出分布形状
sns.histplot(y, kde=True)
plt.title("SalePrice Distribution") 
plt.show()


# In[15]:


# 目标变量转换：处理偏斜分布
import numpy as np
# 房价分布右偏（少数高价房拉高了平均值），对其进行对数转换
# log1p = log(1 + x)，比log(x)更稳定，避免log(0)的问题
y = np.log1p(y)  # 转换后分布更接近正态分布，有利于模型训练

# 绘制转换后的分布图
sns.histplot(y, bins=30, kde=True)
plt.title("Log(SalePrice) Distribution")  # 转换后的分布
plt.show()


# In[16]:


# 特征标准化：将所有特征缩放到相同范围
from sklearn.preprocessing import StandardScaler

# StandardScaler将特征转换为标准正态分布（均值=0，标准差=1）
# 这很重要，因为不同特征的量级差异很大（如面积vs房间数）
# 标准化确保所有特征对模型的贡献是平等的
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)  # fit_transform先学习缩放参数，再应用变换
X_scaled.shape  # 形状不变，但数值已标准化


# In[17]:


# 数据集划分：分离训练集和验证集
from sklearn.model_selection import train_test_split

# 将数据按8:2比例分割
# 训练集用于训练模型参数，验证集用于评估模型性能
# random_state=42确保每次运行结果一致（可重复性）
X_train, X_valid, y_train, y_valid = train_test_split(
    X_scaled, y, test_size=config['TEST_SIZE'], random_state=42
)

# 查看划分后各数据集的维度和类型
print(f"X_train shape: {X_train.shape};", f"X_train type: {type(X_train)}")
print(f"X_valid shape: {X_valid.shape};", f"X_valid type: {type(X_valid)}")
print(f"y_train shape: {y_train.shape};", f"y_train type: {type(y_train)}")
print(f"y_valid shape: {y_valid.shape};", f"y_valid type: {type(y_valid)}")


# In[18]:


# PyTorch环境配置和数据类型转换
import torch
from torch.utils.data import Dataset, DataLoader
import numpy as np

# 设备配置：自动检测是否有GPU可用
# 如果有CUDA GPU则使用GPU训练（更快），否则使用CPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# 数据类型转换：将numpy数组转换为PyTorch张量
# 神经网络只能处理张量，不能直接处理numpy数组或pandas DataFrame
X_train = torch.tensor(X_train, dtype=torch.float32).to(device)
# .values将Series转为numpy数组，.unsqueeze(-1)在最后一维增加维度：(N,) -> (N,1)
y_train = torch.tensor(y_train.values, dtype=torch.float32).unsqueeze(-1).to(device) 

X_valid = torch.tensor(X_valid, dtype=torch.float32).to(device)
y_valid = torch.tensor(y_valid.values, dtype=torch.float32).unsqueeze(-1).to(device)

# 验证转换结果：检查张量的形状和类型
print(f"X_train shape: {X_train.shape};", f"X_train type: {type(X_train)}")
print(f"X_valid shape: {X_valid.shape};", f"X_valid type: {type(X_valid)}")
print(f"y_train shape: {y_train.shape};", f"y_train type: {type(y_train)}")
print(f"y_valid shape: {y_valid.shape};", f"y_valid type: {type(y_valid)}")


# In[19]:


# 自定义数据集类：封装数据以便批量加载
class HouseDataset(Dataset):
    """
    PyTorch数据集类，用于组织训练数据
    Dataset是PyTorch的抽象类，需要实现__len__和__getitem__方法
    """
    def __init__(self, X, y):
        self.X = X  # 特征数据
        self.y = y  # 目标数据

    def __len__(self):
        """返回数据集大小"""
        return len(self.X)

    def __getitem__(self, idx):
        """根据索引返回一个样本"""
        return self.X[idx], self.y[idx]


# 创建数据集对象
train_dataset = HouseDataset(X_train, y_train)
val_dataset = HouseDataset(X_valid, y_valid)

# 创建数据加载器：自动处理批量加载、打乱等操作
# shuffle=True: 训练时随机打乱样本顺序，提高模型泛化能力
# shuffle=False: 验证时保持固定顺序，确保结果可重复
train_loader = DataLoader(train_dataset, batch_size=config["BATCH_SIZE"], shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=config["BATCH_SIZE"], shuffle=False)


# In[20]:


import torch.nn as nn


# 定义神经网络模型类
class HousePriceModel(nn.Module):
    def __init__(self, input_dim):
        super().__init__()  # 调用父类初始化方法

        # 使用Sequential容器定义网络结构，数据会按顺序通过这些层
        self.net = nn.Sequential(
            nn.Linear(input_dim, 64),  # 全连接层1：输入维度 -> 64个神经元
            nn.ReLU(),  # ReLU激活函数：引入非线性，f(x) = max(0, x)
            nn.Dropout(config["DROPOUT_RATE"]),  # Dropout层：随机丢弃神经元，防止过拟合
            nn.Linear(64, 128),  # 全连接层2：64 -> 128个神经元
            nn.ReLU(),  # ReLU激活函数
            nn.Dropout(config["DROPOUT_RATE"]),  # Dropout层
            nn.Linear(128, 1),  # 输出层：128 -> 1个神经元（回归预测房价）
        )

    def forward(self, x):
        return self.net(x)  # 数据通过Sequential定义的网络结构


# In[21]:


# 模型实例化：创建神经网络对象
# X_train.shape[1]获取特征数量作为输入维度
model = HousePriceModel(X_train.shape[1])
model.to(device)  # 将模型移动到指定设备（GPU或CPU）
print(model)  # 打印网络结构，查看各层的参数数量


# In[22]:


# 导入PyTorch优化器模块
import torch.optim as optim

# 定义损失函数：衡量预测值与真实值的差距
criterion = nn.MSELoss()  # 均方误差损失，适用于回归问题：MSE = mean((pred - true)²)

# 定义优化器：负责更新网络参数以最小化损失
# Adam优化器结合了动量和自适应学习率，收敛速度快且稳定
optimizer = optim.Adam(model.parameters(), lr=config["LEARNING_RATE"])


# In[23]:


# 训练历史记录：保存每个epoch的损失值用于可视化
train_losses = []  # 记录训练损失
val_losses = []    # 记录验证损失

# 主训练循环：遍历指定的epoch数量
for epoch in range(1, config["EPOCHS"] + 1):

    # === 训练阶段 ===
    model.train()  # 设置模型为训练模式（启用Dropout）
    train_loss = 0  # 累积训练损失

    # 遍历训练数据的每个batch
    for X_batch, y_batch in train_loader:
        # 确保数据在正确的设备上（GPU/CPU）
        X_batch, y_batch = X_batch.to(device), y_batch.to(device)

        optimizer.zero_grad()  # 清零上一次的梯度（PyTorch会累积梯度）
        outputs = model(X_batch).squeeze()  # 前向传播：计算预测值，squeeze()移除多余维度
        loss = criterion(outputs, y_batch.squeeze())  # 计算损失：预测值vs真实值
        loss.backward()  # 反向传播：计算梯度
        optimizer.step()  # 参数更新：根据梯度更新网络权重

        # 累积加权损失（乘以batch大小，用于计算整体平均损失）
        train_loss += loss.item() * X_batch.shape[0]

    # 计算整个训练集的平均损失
    train_loss /= len(train_loader.dataset)
    train_losses.append(train_loss)  # 记录训练损失

    # === 验证阶段 ===
    model.eval()  # 设置模型为评估模式（禁用Dropout，固定BatchNorm参数）
    val_loss = 0   # 累积验证损失

    # 验证时不需要计算梯度，节省内存和计算时间
    with torch.no_grad():
        # 遍历验证数据的每个batch
        for X_batch, y_batch in val_loader:
            # 确保数据在正确的设备上
            X_batch, y_batch = X_batch.to(device), y_batch.to(device)

            outputs = model(X_batch).squeeze()  # 前向传播：仅预测，无反向传播
            loss = criterion(outputs, y_batch.squeeze())  # 计算验证损失

            # 累积加权验证损失
            val_loss += loss.item() * X_batch.shape[0]

    # 计算整个验证集的平均损失
    val_loss /= len(val_loader.dataset)
    val_losses.append(val_loss)  # 记录验证损失

    # 打印训练进度：监控模型性能
    print(f"Epoch {epoch}/{config['EPOCHS']}, Train Loss: {train_loss:.4f}, Val Loss: {val_loss:.4f}")


# In[24]:


# 训练过程可视化：绘制损失函数变化曲线
import matplotlib.pyplot as plt

# 绘制训练损失和验证损失的变化趋势
plt.plot(train_losses, label='Train Loss')      # 训练损失曲线
plt.plot(val_losses, label='Validation Loss')  # 验证损失曲线
plt.xlabel('Epoch')    # x轴标签：训练轮次
plt.ylabel('Loss')     # y轴标签：损失值
plt.legend()          # 显示图例
plt.title('Train vs Validation Loss')  # 图表标题
plt.show()

# 通过这个图可以判断：
# 1. 模型是否收敛（损失是否下降）
# 2. 是否过拟合（训练损失继续下降但验证损失上升）
# 3. 是否欠拟合（两个损失都很高且不再下降）


# In[25]:


# 模型保存：将训练好的模型参数保存到文件
# state_dict()包含了模型的所有可学习参数（权重和偏置）
# 保存模型可以避免重新训练，也便于模型部署和分享
torch.save(model.state_dict(), 'house_price_model.pth')


# In[26]:


# 模型加载：从保存的文件中恢复训练好的模型
import torch

# 重新创建模型结构（必须与训练时的结构完全一致）
model = HousePriceModel(X.shape[1])
# 加载保存的参数到模型中
model.load_state_dict(torch.load("house_price_model.pth"))
model.to(device)  # 将模型移动到指定设备
model.eval()      # 设置为评估模式，用于预测
print("Model loaded successfully.")  # 确认加载成功


# In[27]:


# 测试数据预处理：对测试集进行与训练集相同的数据处理
test = pd.read_csv("house_price_dataset/test.csv")  # 读取测试数据
id_col = test["Id"].copy()  # 保存ID列，用于最终提交文件
test.drop(["Id"], axis=1, inplace=True)  # 删除ID列（不用于预测）

# 必须使用与训练集相同的处理方式，确保数据一致性
for col in none_fill_cols:
    test[col] = test[col].fillna("None")
test.drop(columns=cols_to_drop, inplace=True)
test["LotFrontage"] = test["LotFrontage"].fillna(test["LotFrontage"].median())
test["MasVnrArea"] = test["MasVnrArea"].fillna(0)
test["GarageYrBlt"] = test["GarageYrBlt"].fillna(0)
test["Electrical"] = test["Electrical"].fillna(test["Electrical"].mode()[0])

test = pd.get_dummies(test)
test.shape  # 查看编码后的特征数量


# In[28]:


# 特征对齐：确保测试集与训练集具有相同的特征列
# one-hot编码可能导致训练集和测试集的列不完全相同

# 找出训练集有但测试集没有的列
missing_cols = set(X.columns) - set(test.columns)
# 为测试集添加缺失的列，并填充0（表示该类别不存在）
for col in missing_cols:
    test[col] = 0

# 按照训练集的列顺序重新排列测试集的列
# 这确保了特征的顺序与训练时完全一致，避免预测错误
test = test[X.columns]
test.shape  # 验证测试集形状与训练集特征数一致


# In[29]:


# 测试数据标准化：使用训练时的scaler对测试数据进行标准化
# 注意：只用transform()，不用fit_transform()
# 因为要使用训练集的均值和标准差，保持数据分布一致
test_scaled = scaler.transform(test)

# 数据类型转换：将测试数据转换为PyTorch张量并移动到设备
test_tensor = torch.tensor(test_scaled, dtype=torch.float32).to(device)

# 创建测试数据集：为测试数据创建虚拟标签（全零张量）
# 虚拟标签不会用于计算，只是为了匹配DataLoader的接口要求
test_dataset = HouseDataset(
    test_tensor, torch.zeros(test_tensor.shape[0], 1).to(device)
)

# 创建测试数据加载器：batch处理测试数据，shuffle=False保持顺序
test_loader = DataLoader(test_dataset, batch_size=config["BATCH_SIZE"], shuffle=False)

# 验证数据加载器：查看第一批数据的形状
for X_batch, _ in test_loader:
    print(f"X_batch shape: {X_batch.shape};", f"X_batch type: {type(X_batch)}")
    break  # 只查看第一批数据


# In[30]:


# 模型预测：使用训练好的模型对测试数据进行预测
model.eval()  # 确保模型处于评估模式
predictions = []  # 存储所有预测结果

# 禁用梯度计算以节省内存和加速推理
with torch.no_grad():
    # 批量处理测试数据
    for X_batch, _ in test_loader:
        X_batch = X_batch.to(device)  # 确保数据在正确设备上
        outputs = model(X_batch).squeeze()  # 前向传播获取预测值
        # 将预测结果从GPU移到CPU并转换为numpy数组
        predictions.append(outputs.cpu().numpy())

# 合并所有批次的预测结果
predictions = np.concatenate(predictions)

# 反向变换：将对数预测值转回原始房价
# 因为训练时对房价做了log1p变换，所以用expm1还原
predictions = np.expm1(predictions)  # expm1(x) = exp(x) - 1

# 创建提交文件：包含房屋ID和预测价格
submission = pd.DataFrame({"Id": id_col, "SalePrice": predictions})

# 处理可能的异常值：用中位数填充任何NaN预测值
submission['SalePrice'].fillna(submission['SalePrice'].median(), inplace=True)


# In[31]:


# 保存预测结果：将预测结果保存为CSV文件用于竞赛提交
# index=False表示不保存行索引，保持文件格式简洁
submission.to_csv('submission.csv', index=False)
print("Submission file created.")  # 确认文件创建成功

