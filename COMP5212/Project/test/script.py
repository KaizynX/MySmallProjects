'''
Author: Kaizyn 2291443901@qq.com
Date: 2024-04-21 23:57:01
LastEditors: Kaizyn 2291443901@qq.com
LastEditTime: 2024-04-22 00:00:52
FilePath: \COMP5212\script.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
import glob
import os
import shutil
import zipfile

import time

from torchsummary import summary
import torch
import torch.nn as nn
from torch.autograd import Variable

from collections import OrderedDict
import numpy as np
from torch.utils.data import Dataset

import pandas as pd
import numpy as np


'''
Here is the final grading script.

Submission file tree should be like this:
- dlmodel.py
- mlmodel.py
- final_model.pth
- training.csv
- report.pdf

Please extremely make sure that the file name is correct. The file name should be exactly the same as the above. The file name is case-sensitive.
We would output the result in the file. If no exception is raised, the code is correct, and the format is acceptable.

If you have any questions, please contact us via email or canvas.
'''


all_files = glob.glob("./*.zip") # get all zip files in the current directory, for your run locally, you can comment this line and use the following line
# all_files = ["you zip absolute path"]

os.makedirs("./unzip", exist_ok=True)
os.makedirs("./grade", exist_ok=True)
# move files to the target directory

def find_files(directory, name):
    os.makedirs(f"./{name}", exist_ok=True)
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file == 'dlmodel.py' or file == 'mlmodel.py' or file == "model.py" or file == 'final_model.pth' or file == 'training.csv' or file == 'train.csv':
                shutil.move(os.path.join(root, file), f"./{name}")

                
for file in all_files[0:1]:
    print(file)
    name = file.split("\\")[-1].split("/")[-1].split("_")[0].split(".")[0]
    shutil.rmtree("./unzip")
    try:
        ff = zipfile.ZipFile(file)
        for file in ff.namelist():
            ff.extract(file,"./unzip") # extract all files into the unzip directory
        ff.close()
        shutil.rmtree(f"./{name}", ignore_errors=True)
        find_files("./unzip", name)
        shutil.copy("./total_grading.py", f"./{name}")
        shutil.copy("./validation.csv", f"./{name}") # you can use validation.csv to test your model
        os.chdir(f"./{name}")
        os.system(f"python total_grading.py >> ../grade/{name}.txt")
        os.chdir("..")
    except Exception as e:
        print(e)
        continue